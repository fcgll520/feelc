#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
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
#include <fcntl.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>


static const char *S_SVR_ADDR = "10.27.13.146";
static const uint16_t S_SVR_PORT = 9999;

static uint64_t s_start_time = -1;
static uint64_t s_end_time = -1;

struct file_opt_t
{
	FILE		*file_handle;

	int32_t		file_size;
	int32_t		total_recv;
	char		*buff;
};
static struct file_opt_t s_file_opt;

int32_t get_file_size(const char *path)
{
	int32_t filesize = -1;
	struct stat statbuff;
	if(stat(path, &statbuff) < 0){
		return filesize;
	}else{
		filesize = statbuff.st_size;
	}
	return filesize;
}

/* get system time */
void itimeofday(long *sec, long *usec)
{
	assert(sec != NULL);
	assert(usec != NULL);

	struct timeval time;
	gettimeofday(&time, NULL);
	*sec = time.tv_sec;
	*usec = time.tv_usec;
}

uint64_t iclock64(void)
{
	long s, u;
	uint64_t value;
	itimeofday(&s, &u);
	value = ((uint64_t)s) * 1000 + (u / 1000);
	return value;
}


int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("usage: ./recv file_size\n");   //必须./send的参数文件的大小
		return -1;
	}

	const char *file_path = "./test.mp4.recv";
	unlink(file_path);
	s_file_opt.file_handle = fopen(file_path, "w");
	assert(s_file_opt.file_handle != NULL);

	s_file_opt.file_size = atoi(argv[1]);
	s_file_opt.buff = (char *)malloc(s_file_opt.file_size);
	if (NULL == s_file_opt.buff)
	{
		perror("malloc failed");
		assert(0);
	}

	int32_t ret = -1;
	int32_t sock = -1;
	struct sockaddr_in local_addr;
	socklen_t addr_len = sizeof(local_addr);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("socket failed");
		assert(0);
	}

	memset(&local_addr, addr_len, 0);
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(S_SVR_ADDR);
	local_addr.sin_port = htons(S_SVR_PORT);

	ret = bind(sock, (const struct sockaddr *)&local_addr, addr_len);
	if (ret < 0)
	{
		perror("bind failed");
		assert(0);
	}

	ret = listen(sock, 5);
	if (ret < 0)
	{
		perror("listen failed");
		assert(0);
	}

	int32_t new_sock = accept(sock, NULL, NULL);
	if (new_sock < 0)
	{
		perror("accept failed");
		assert(0);
	}

	while (1)
	{
		int32_t real_recv_len = recv(new_sock, s_file_opt.buff, s_file_opt.file_size, 0);
		if (real_recv_len < 0)
		{
			perror("recv failed");
			assert(0);
		}
		else if (real_recv_len == 0)
		{
			printf("client socket shutdown\n");
			break;
		}
		else
		{
			int32_t real_write_len = fwrite(s_file_opt.buff, 1, real_recv_len, s_file_opt.file_handle);
			assert(real_write_len == real_recv_len);

			if (s_start_time == -1)
			{
				s_start_time = iclock64();
			}

			s_file_opt.total_recv += real_recv_len;
			if (s_file_opt.total_recv == s_file_opt.file_size)
			{
				s_end_time = iclock64();
				uint64_t cost_time = s_end_time-s_start_time;
				double speed = ((double)s_file_opt.total_recv * 8 * 1000) / ((double)cost_time*1024);
				printf("recv_length: %d, cost: %llu ms, speed: %.0lf Kb/s\n",
					s_file_opt.total_recv, cost_time, speed);
				break;
			}
		}
	}
	close(new_sock);
	close(sock);

	free(s_file_opt.buff);
	fclose(s_file_opt.file_handle);
	printf("end\n");
	return 0;
}