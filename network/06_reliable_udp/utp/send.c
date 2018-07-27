#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "../common/common.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "utp.h"
#include "event.h"

static struct event_base *s_base = NULL;

static utp_context *s_utp_ctx = NULL;

static utp_socket *s_utp_socket = NULL;

static int32_t s_sock = -1;

static uint8_t s_buff[S_MAX_BUFF_SIZE];

// 总共发送出去的字节数
static int32_t s_total_sent = 0;  

struct file_opt_t
{
	FILE		*file_handle;

	int32_t		file_size;
	int32_t		total_sent;
	char		*buff;
};
static struct file_opt_t s_file_opt;

void send_data()
{
	while (1)
	{
		int32_t max_sent_once = s_file_opt.file_size-s_file_opt.total_sent;
		//max_sent_once = max_sent_once > 1024 ? 1024 : max_sent_once;
		int32_t real_sent_once = utp_write(s_utp_socket, s_file_opt.buff+s_file_opt.total_sent,
			max_sent_once);
		if (0 == real_sent_once)
		{
			break;
		}
		s_file_opt.total_sent += real_sent_once;
		//printf("real_sent_once: %d, total_sent: %d, file_size: %d\n", real_sent_once,
		//	s_file_opt.total_sent, s_file_opt.file_size);		
	}
}

uint64 callback_on_read(utp_callback_arguments *a)
{
	printf("%s be called\n", __FUNCTION__);
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
	switch (a->state)
	{
	case UTP_STATE_CONNECT:
		send_data();
		break;
	case UTP_STATE_WRITABLE:
		send_data();
		break;
	case UTP_STATE_EOF:
		break;
	case UTP_STATE_DESTROYING:
		break;
	default:
		break;
	}
	return 0;
	return 0;
}

uint64 callback_sendto(utp_callback_arguments *a)
{
	int32_t send_len = send(s_sock, a->buf, a->len, 0);
	assert(send_len == a->len);
	if (send_len != 20)  //utp的自定义的包长度是20
	{
		//printf("%llu, send_len: %d\n", iclock64(), send_len);
		s_total_sent += (send_len - 20);
	}
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
	//printf("recv_len: %d\n", recv_len);
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
		return ;
	}
	else if (recv_len == 0)
	{
		printf("socket shutdown\n");
		event_base_loopbreak(s_base);
		return ;
	}

	struct sockaddr_in peer_addr;
	socklen_t addr_len = sizeof(peer_addr);
	memset(&peer_addr, addr_len, 0);
	peer_addr.sin_family = AF_INET;
	peer_addr.sin_addr.s_addr = inet_addr(S_RECV_ADDR);
	peer_addr.sin_port = htons(S_RECV_PORT);

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
		printf("usage: ./send file_path\n");
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

	s_sock = create_socket(S_SEND_ADDR, S_SEND_PORT, S_RECV_ADDR, S_RECV_PORT);

	const char *file_path = argv[1];
	s_file_opt.file_handle = fopen(file_path, "r");
	assert(s_file_opt.file_handle != NULL);

	s_file_opt.file_size = get_file_size(file_path);
	assert(s_file_opt.file_size != -1);
	printf("file_size: %d\n", s_file_opt.file_size);

	s_file_opt.buff = (char *)malloc(s_file_opt.file_size);
	if (NULL == s_file_opt.buff)
	{
		perror("malloc failed");
		assert(0);
	}
	int32_t real_read_len = fread(s_file_opt.buff, 1, s_file_opt.file_size, s_file_opt.file_handle);
	assert(real_read_len == s_file_opt.file_size);
	
	struct event *sock_r_event = NULL;
	struct event *timer_event = NULL;
	struct timeval timeout = { 0, 500*1000 };

	s_base = event_base_new();
	assert(s_base != NULL);

	sock_r_event = event_new(s_base, s_sock, EV_READ|EV_PERSIST, read_callback, NULL);
	assert(sock_r_event != NULL);
	event_add(sock_r_event, NULL);

	timer_event = event_new(s_base, -1, EV_TIMEOUT|EV_PERSIST, timer_callback, NULL);
	assert(timer_event != NULL);
	event_add(timer_event, &timeout);
	
	s_utp_socket = utp_create_socket(s_utp_ctx);
	assert(s_utp_socket != NULL);

	struct sockaddr_in peer_addr;
	socklen_t addr_len = sizeof(peer_addr);
	memset(&peer_addr, addr_len, 0);
	peer_addr.sin_family = AF_INET;
	peer_addr.sin_addr.s_addr = inet_addr(S_RECV_ADDR);
	peer_addr.sin_port = htons(S_RECV_PORT);

	int ret = utp_connect(s_utp_socket, (const struct sockaddr *)&peer_addr, addr_len);
	assert(ret >= 0);

	event_base_dispatch(s_base);

	printf("sent length: %d\n", s_total_sent);

	event_del(sock_r_event);
	event_del(timer_event);
	event_base_free(s_base);
	free(s_file_opt.buff);
	fclose(s_file_opt.file_handle);
	printf("end\n");
	return 0;
}