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


static const char *S_SVR_ADDR = "10.27.13.146";
static const uint16_t S_SVR_PORT = 9999;


struct file_opt_t
{
	FILE		*file_handle;

	int32_t		file_size;
	int32_t		total_sent;
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

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("usage: ./send file_path\n");
		return -1;
	}

	int32_t ret = -1;
	int32_t sock = -1;
	struct sockaddr_in svr_addr;
	socklen_t addr_len = sizeof(svr_addr);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("socket failed");
		assert(0);
	}

	memset(&svr_addr, addr_len, 0);
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_addr.s_addr = inet_addr(S_SVR_ADDR);
	svr_addr.sin_port = htons(S_SVR_PORT);

	ret = connect(sock, (const struct sockaddr *)&svr_addr, addr_len);
	if (ret < 0)
	{
		perror("connect failed");
		assert(0);
	}

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

	int32_t real_send_len = send(sock, s_file_opt.buff, s_file_opt.file_size, 0);
	printf("real_send_len: %d\n", real_send_len);
	assert(real_send_len == s_file_opt.file_size);
	
	free(s_file_opt.buff);
	fclose(s_file_opt.file_handle);
	printf("end\n");
	return 0;
}