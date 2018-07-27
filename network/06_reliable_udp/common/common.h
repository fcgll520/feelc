#include <stdint.h>


static const int32_t S_MAX_BUFF_SIZE = 1500+100;

#if 0
static const char * S_SEND_ADDR = "10.229.13.141";
static const char * S_RECV_ADDR = "10.61.84.139";
#else
static const char * S_SEND_ADDR = "10.27.13.159";
//static const char * S_RECV_ADDR = "10.27.13.159";
static const char * S_RECV_ADDR = "10.27.13.146";
#endif

static const uint16_t S_SEND_PORT = 8888;
static const uint16_t S_RECV_PORT = 9999;

int32_t create_socket(const char *my_str_ip, uint16_t my_port,
					  const char *peer_str_ip, uint16_t peer_port);

int32_t socket_set_nonblocking(int32_t fd);

int32_t get_file_size(const char *path);

uint64_t iclock64();

uint32_t iclock();
