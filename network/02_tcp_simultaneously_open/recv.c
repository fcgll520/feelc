
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    int sock = -1;
    struct sockaddr_in peer_addr;
    struct sockaddr_in local_addr;
    socklen_t addr_len = sizeof(peer_addr);
    int retry = 10;

    memset(&local_addr, 0, addr_len);
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    local_addr.sin_port = htons(atoi(argv[1]));

    memset(&peer_addr, 0, addr_len);
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    peer_addr.sin_port = htons(atoi(argv[2]));

    printf("local port:%d, peer port:%d\n", local_addr.sin_port, peer_addr.sin_port);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("call socket() failed, err: %s\n", strerror(errno));
        return -1;
    }
    if (-1 == bind(sock, (const struct sockaddr *)&local_addr, addr_len))
    {
        printf("call bind() failed, err: %s\n", strerror(errno));
        return -1;
    }

    char recv_buf[64] = { '0' };
    while (1)
    {
        if (-1 == connect(sock, (const struct sockaddr *)&peer_addr, addr_len))
        {
            printf("call connect() failed, port: %d, errno: %d, err: %s\n",
                ntohs(peer_addr.sin_port), errno, strerror(errno));
            continue;
        }
        if (-1 == recv(sock, recv_buf, 64, 0))
        {
            printf("recv failed, err:%s\n", strerror(errno));
            return -1;
        }
        printf("buf: %s", recv_buf);
        break;
    }
    close(sock);
    return 0;
}
