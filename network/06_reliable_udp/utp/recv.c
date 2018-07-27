#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "../common/common.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "utp.h"
#include "event.h"


static struct event_base *s_base = NULL;

static utp_context *s_utp_ctx = NULL;

static int32_t s_sock = -1;

static uint8_t s_buff[S_MAX_BUFF_SIZE];

static FILE *s_file_handle = NULL;

static int32_t s_file_size = -1;

static int32_t s_real_recv_length = 0;

static uint64_t s_start_time = -1;
static uint64_t s_end_time = -1;


uint64 callback_on_read(utp_callback_arguments *a)
{
	if (s_start_time == -1)
	{
		s_start_time = iclock64();
	}

	//printf("len: %d\n", a->len);
	int32_t real_write_len = fwrite(a->buf, 1, a->len, s_file_handle);
	fflush(s_file_handle);
	assert(real_write_len == a->len);

	s_real_recv_length += real_write_len;

	//printf("recv_length: %d, file_size: %d\n", s_real_recv_length, s_file_size);

	if (s_real_recv_length == s_file_size)
	{
		s_end_time = iclock64();
		uint64_t cost_time = s_end_time-s_start_time;
		double speed = ((double)s_real_recv_length * 8 * 1000) / ((double)cost_time*1024);
		printf("recv_length: %d, cost: %llu ms, speed: %.0lf Kb/s\n",
			s_real_recv_length, cost_time, speed);
		event_base_loopbreak(s_base);
	}
	return 0;
}

uint64 callback_on_firewall(utp_callback_arguments *a)
{
	return 0;
}

uint64 callback_on_accept(utp_callback_arguments *a)
{
	return 0;
}

uint64 callback_on_error(utp_callback_arguments *a)
{
	printf("%s be called\n", __FUNCTION__);
	return 0;
}

uint64 callback_on_state_change(utp_callback_arguments *a)
{
	printf("%s be called, state: %d\n", __FUNCTION__, a->state);
	return 0;
}

uint64 callback_sendto(utp_callback_arguments *a)
{
	int32_t send_len = send(s_sock, a->buf, a->len, 0);
	assert(send_len == a->len);
	return 0;
}

uint64 callback_log(utp_callback_arguments *a)
{
	//printf("%s\n", a->buf);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////
void read_callback(evutil_socket_t, short, void *)
{
	int32_t recv_len = recv(s_sock, s_buff, S_MAX_BUFF_SIZE, 0);
	if (recv_len < 0)
	{
		if (errno == ECONNREFUSED)
		{
			printf("connect refused\n");
			event_base_loopbreak(s_base);
		}
		else
		{
			printf("recv failed, recv_len: %d, err: %s\n", recv_len, strerror(errno));
			assert(0);
		}
	}
	else if (recv_len == 0)
	{
		printf("socket shutdown\n");
		event_base_loopbreak(s_base);
	}

	struct sockaddr_in peer_addr;
	socklen_t addr_len = sizeof(peer_addr);
	memset(&peer_addr, addr_len, 0);
	peer_addr.sin_family = AF_INET;
	peer_addr.sin_addr.s_addr = inet_addr(S_SEND_ADDR);
	peer_addr.sin_port = htons(S_SEND_PORT);
	
	utp_process_udp(s_utp_ctx, s_buff, recv_len, (const struct sockaddr*)&peer_addr, addr_len);
	utp_issue_deferred_acks(s_utp_ctx);
}

void timer_callback(evutil_socket_t, short, void *)
{
	if (NULL != s_utp_ctx)
	{
		utp_check_timeouts(s_utp_ctx);
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("usage: ./recv file_size\n");   //必须./send的参数文件的大小
		return -1;
	}

	s_utp_ctx = utp_init(2);
	assert(s_utp_ctx != NULL);
	utp_context_set_userdata(s_utp_ctx, NULL);
	utp_set_callback(s_utp_ctx, UTP_LOG,				&callback_log);
	utp_set_callback(s_utp_ctx, UTP_SENDTO,				&callback_sendto);
	utp_set_callback(s_utp_ctx, UTP_ON_ERROR,			&callback_on_error);
	utp_set_callback(s_utp_ctx, UTP_ON_STATE_CHANGE,	&callback_on_state_change);
	utp_set_callback(s_utp_ctx, UTP_ON_READ,			&callback_on_read);
	utp_set_callback(s_utp_ctx, UTP_ON_FIREWALL,		&callback_on_firewall);
	utp_set_callback(s_utp_ctx, UTP_ON_ACCEPT,			&callback_on_accept);
	utp_context_set_option(s_utp_ctx, UTP_LOG_NORMAL, 1);
	utp_context_set_option(s_utp_ctx, UTP_LOG_MTU,    1);
	utp_context_set_option(s_utp_ctx, UTP_LOG_DEBUG,  1);

	s_sock = create_socket(S_RECV_ADDR, S_RECV_PORT, S_SEND_ADDR, S_SEND_PORT);

	const char *file_path = "./test.mp4.recv";
	unlink(file_path);
	s_file_handle = fopen(file_path, "w");
	assert(s_file_handle != NULL);

	s_file_size = atoi(argv[1]);
	assert(s_file_size != -1);

	
	struct event *sock_event = NULL;
	struct event *timer_event = NULL;
	struct timeval timeout = { 0, 500*1000 };

	s_base = event_base_new();
	assert(s_base != NULL);

	sock_event = event_new(s_base, s_sock, EV_READ|EV_PERSIST, read_callback, NULL);
	assert(sock_event != NULL);
	event_add(sock_event, NULL);

	timer_event = event_new(s_base, -1, EV_TIMEOUT|EV_PERSIST, timer_callback, NULL);
	assert(timer_event != NULL);
	event_add(timer_event, &timeout);


	event_base_dispatch(s_base);

	event_del(sock_event);
	event_del(timer_event);
	event_base_free(s_base);
	fclose(s_file_handle);

	printf("end\n");
	return 0;
}