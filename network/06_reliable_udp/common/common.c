#include "common.h"
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

int32_t create_socket(const char *my_str_ip, uint16_t my_port,
					  const char *peer_str_ip, uint16_t peer_port)
{
	int32_t ret = -1;
	int32_t sock = -1;
	struct sockaddr_in local_addr;
	struct sockaddr_in peer_addr;
	socklen_t addr_len = sizeof(local_addr);

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		perror("socket failed");
		goto ERR;
	}

	memset(&local_addr, addr_len, 0);
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(my_str_ip);
	local_addr.sin_port = htons(my_port);

	memset(&peer_addr, addr_len, 0);
	peer_addr.sin_family = AF_INET;
	peer_addr.sin_addr.s_addr = inet_addr(peer_str_ip);
	peer_addr.sin_port = htons(peer_port);

	ret = bind(sock, (struct sockaddr *)&local_addr, addr_len);
	if (ret < 0)
	{
		perror("bind failed");
		goto ERR;
	}

	ret = socket_set_nonblocking(sock);
	if (ret < 0)
	{
		perror("set nonblocking failed");
		goto ERR;
	}
	ret = connect(sock, (const struct sockaddr *)&peer_addr, addr_len);
	if (ret < 0)
	{
		perror("connect failed");
		goto ERR;
	}

	return sock;
ERR:
	if (sock >= 0)
	{
		close(sock);
	}
	assert(0);
	return -1;
}

int32_t socket_set_nonblocking(int32_t fd)
{
	int32_t flags;
	if ((flags = fcntl(fd, F_GETFL, NULL)) < 0)
	{
		return -1;
	}
	if (!(flags & O_NONBLOCK))
	{
		if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
		{
			return -1;
		}
	}
	return 0;
}


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

/* get clock in millisecond 64 */
uint64_t iclock64()
{
	long s, u;
	uint64_t value;
	itimeofday(&s, &u);
	value = ((uint64_t)s) * 1000 + (u / 1000);
	return value;
}

uint32_t iclock()
{
	return (uint32_t)(iclock64() & 0xfffffffful);
}
