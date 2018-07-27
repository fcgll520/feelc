#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../common/common.h"
#include "common_internal.h"
#include "event.h"

struct file_opt_t
{
	FILE		*file_handle;

	int32_t		file_size;
	int32_t		total_recv;
};
static struct file_opt_t s_file_opt;


static struct event_base *s_base = NULL;

static int32_t s_sock = -1;

static ikcpcb *s_kcp_handle = NULL;

static char s_sock_buffer[S_MAX_BUFF_SIZE];
static char s_kcp_buffer[S_MAX_BUFF_SIZE];

static uint64_t s_start_time = -1;
static uint64_t s_end_time = -1;

void timer_callback(evutil_socket_t, short, void *)
{
	ikcp_update(s_kcp_handle, iclock());

	if (s_file_opt.total_recv == s_file_opt.file_size)
	{
		s_end_time = iclock64();
		uint64_t cost_time = s_end_time-s_start_time;
		double speed = ((double)s_file_opt.total_recv * 8 * 1000) / ((double)cost_time*1024);
		printf("recv_length: %d, cost: %llu ms, speed: %.0lf Kb/s\n",
			s_file_opt.total_recv, cost_time, speed);
		event_base_loopbreak(s_base);
	}
}

void read_callback(evutil_socket_t, short, void *)
{
	static int32_t sock_recv_count = 0;
	static int32_t kcp_recv_count = 0;

	int32_t sock_recv_len = recv(s_sock, s_sock_buffer, S_MAX_BUFF_SIZE, 0);
	//printf("real_recv_len: %d\n", sock_recv_len);
	assert(sock_recv_len != S_MAX_BUFF_SIZE);
	if (sock_recv_len < 0)
	{
		if (errno == ECONNREFUSED)
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
	else if (sock_recv_len == 0)
	{
		printf("socket shutdown\n");
		event_base_loopbreak(s_base);
		return ;
	}
	sock_recv_count++;

	int ret = ikcp_input(s_kcp_handle, s_sock_buffer, sock_recv_len);	
	if (ret < 0)
	{
		printf("ikcp_input failed, ret: %d\n", ret);
		assert(0);
	}
	while (1) {
		int kcp_recv_len = ikcp_recv(s_kcp_handle, s_kcp_buffer, S_MAX_BUFF_SIZE);
		if (kcp_recv_len < 0)
		{
			//printf("ikcp_recv() failed, kcp_recv_len: %d\n", kcp_recv_len);			
			ikcp_update(s_kcp_handle, iclock());
			break;
		}
		ikcp_update(s_kcp_handle, iclock());
		kcp_recv_count++;

		if (s_start_time == -1)
		{
			s_start_time = iclock64();
		}

		int32_t real_write_len = fwrite(s_kcp_buffer, 1, kcp_recv_len, s_file_opt.file_handle);
		fflush(s_file_opt.file_handle);
		assert(real_write_len == kcp_recv_len);

		s_file_opt.total_recv += real_write_len;
		/*printf("sock_recv_count: %d, kcp_recv_count: %d, kcp_recv_len: %d, total_recv: %d, file_size: %d\n",
			sock_recv_count, kcp_recv_count, kcp_recv_len,
			s_file_opt.total_recv,s_file_opt.file_size);	*/
	}
}

int32_t udp_output(const char *buf, int len, ikcpcb *kcp, void *user)
{
	int32_t send_len = send(s_sock, buf, len, 0);
	assert(send_len == len);
	if (send_len < 0)
	{
		perror("sendto failed");
		assert(0);
	}
	//printf("send_len: %d\n", send_len);
	ikcp_update(s_kcp_handle, iclock());
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
		printf("usage: ./recv file_size\n");   //必须./send的参数文件的大小
		return -1;
	}

	s_kcp_handle = ikcp_create(0x11223344, NULL);
	s_kcp_handle->output = udp_output;
	s_kcp_handle->writelog = writelog;
	//s_kcp_handle->logmask = IKCP_LOG_OUTPUT | IKCP_LOG_INPUT | IKCP_LOG_SEND  | IKCP_LOG_RECV | IKCP_LOG_IN_DATA  | IKCP_LOG_IN_ACK  | IKCP_LOG_IN_PROBE | IKCP_LOG_IN_WINS | IKCP_LOG_OUT_DATA | IKCP_LOG_OUT_ACK | IKCP_LOG_OUT_PROBE | IKCP_LOG_OUT_WINS;
	set_kcp(s_kcp_handle);

	s_sock = create_socket(S_RECV_ADDR, S_RECV_PORT, S_SEND_ADDR, S_SEND_PORT);

	const char *file_path = "./test.mp4.recv";
	unlink(file_path);
	s_file_opt.file_handle = fopen(file_path, "w");
	assert(s_file_opt.file_handle != NULL);

	s_file_opt.file_size = atoi(argv[1]);
	assert(s_file_opt.file_size != -1);


	struct event *sock_event = NULL;
	struct event *timer_event = NULL;
	struct timeval timeout = { 0, S_KCP_UPDATE_TIMEO};

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
	fclose(s_file_opt.file_handle);

	printf("end\n");
	return 0;
}