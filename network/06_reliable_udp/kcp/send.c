#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include "../common/common.h"
#include "common_internal.h"
#include <errno.h>

#include "event.h"
#include "ikcp.h"

struct file_opt_t
{
	FILE		*file_handle;

	int32_t		file_size;
	int32_t		total_sent;
	char		*buff;
};
static struct file_opt_t s_file_opt;

static char s_sock_buffer[S_MAX_BUFF_SIZE];
static char s_kcp_buffer[S_MAX_BUFF_SIZE];

static ikcpcb *s_kcp_handle = NULL;

static struct event_base *s_base = NULL;

static int32_t s_sock = -1;

// 总共发送出去的字节数
static int32_t s_total_sent = 0;  


void timer_callback(evutil_socket_t, short, void *)
{
	ikcp_update(s_kcp_handle, iclock());
}

void signal_callback(evutil_socket_t, short, void *)
{
	event_base_loopbreak(s_base);
}

void read_callback(evutil_socket_t, short, void *)
{
	int32_t sock_recv_len = recv(s_sock, s_sock_buffer, S_MAX_BUFF_SIZE, 0);
	//printf("sock_recv_len: %d\n", sock_recv_len);
	assert(sock_recv_len != S_MAX_BUFF_SIZE);
	if (sock_recv_len < 0)
	{
		if (ECONNREFUSED == errno)
		{
			printf("connect refused\n");
			event_base_loopbreak(s_base);
		}
		else
		{
			printf("sock_recv_len: %d, err: %s\n", sock_recv_len, strerror(errno));
			assert(0);
		}
		return ;
	}
	else if (0 == sock_recv_len)
	{
		printf("socket shutdown\n");
		event_base_loopbreak(s_base);
		return ;
	}

	int ret = ikcp_input(s_kcp_handle, s_sock_buffer, sock_recv_len);
	if (ret < 0)
	{
		printf("ikcp_input failed, ret: %d\n", ret);
		assert(0);
	}
	ikcp_update(s_kcp_handle, iclock());
}

int32_t udp_output(const char *buf, int len, ikcpcb *kcp, void *user)
{
	int32_t send_len = send(s_sock, buf, len, 0);
	if (send_len < 0)
	{
		printf("send_len: %d, len: %d\n", send_len, len);
		perror("sendto failed");
		if (ECONNREFUSED == errno)
		{
			event_base_loopbreak(s_base);
			return 0;
		}
	}
	if (send_len == 1048)
	{
		s_total_sent += send_len;
	}
	//printf("send_len: %d, s_total_sent: %d\n", send_len, s_total_sent);
	return 0;
}

void writelog(const char *log, struct IKCPCB *kcp, void *user)
{
	printf("%s\n", log);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("usage: ./send file_path\n");
		return -1;
	}

	s_sock = create_socket(S_SEND_ADDR, S_SEND_PORT, S_RECV_ADDR, S_RECV_PORT);

	s_kcp_handle = ikcp_create(0x11223344, NULL);
	s_kcp_handle->output = udp_output;
	s_kcp_handle->writelog = writelog;
	//s_kcp_handle->logmask = IKCP_LOG_OUTPUT | IKCP_LOG_INPUT | IKCP_LOG_SEND  | IKCP_LOG_RECV | IKCP_LOG_IN_DATA  | IKCP_LOG_IN_ACK  | IKCP_LOG_IN_PROBE | IKCP_LOG_IN_WINS | IKCP_LOG_OUT_DATA | IKCP_LOG_OUT_ACK | IKCP_LOG_OUT_PROBE | IKCP_LOG_OUT_WINS;
	set_kcp(s_kcp_handle);
	set_kcp_other(s_kcp_handle);

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
	struct event *signal_event = NULL;
	struct timeval timeout = { 0, S_KCP_UPDATE_TIMEO };

	s_base = event_base_new();
	assert(s_base != NULL);

	sock_r_event = event_new(s_base, s_sock, EV_READ|EV_PERSIST, read_callback, NULL);
	assert(sock_r_event != NULL);
	event_add(sock_r_event, NULL);

	timer_event = event_new(s_base, -1, EV_TIMEOUT|EV_PERSIST, timer_callback, NULL);
	assert(timer_event != NULL);
	event_add(timer_event, &timeout);

	signal_event = event_new(s_base, SIGINT, EV_SIGNAL|EV_PERSIST, signal_callback, NULL);
	assert(signal_event != NULL);
	event_add(signal_event, NULL);

	while (1)
	{
		int32_t send_len_once = s_file_opt.file_size - s_file_opt.total_sent;
		send_len_once = send_len_once > 1024 ? 1024 : send_len_once;
		int ret = ikcp_send(s_kcp_handle, s_file_opt.buff+s_file_opt.total_sent, send_len_once);
		assert(ret >= 0);
		s_file_opt.total_sent += send_len_once;
		if (s_file_opt.total_sent == s_file_opt.file_size)
		{
			break;
		}
		ikcp_update(s_kcp_handle, iclock());
	}

	event_base_dispatch(s_base);

	printf("\ntotal_sent: %d\n", s_total_sent);

	event_del(timer_event);
	event_del(sock_r_event);
	fclose(s_file_opt.file_handle);
	ikcp_release(s_kcp_handle);
	close(s_sock);
	printf("end\n");
	return 0;
}