#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERVER_LISTEN_PORT (8899)

int main(int argc, char **argv)
{
    int sock = -1;
    int send_len = -1, recv_len = -1;
    struct sockaddr_in server_addr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    char recv_buf[512] = { '\0' };

    if (argc < 2)
    {
        printf("Usage: ./client msg\n");
        return -1;
    }
    char *send_buf = argv[1]; 
    
    memset(&server_addr, 0, addrlen);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_LISTEN_PORT);
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.200");

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        printf("create socket failed, err: %s\n", strerror(errno));
        goto ERR;
    }

    if (-1 == connect(sock, (struct sockaddr *)&server_addr, addrlen))
    {
        printf("connect socket failed, server_addr: %s, server_port: %s, err: %s\n",
                inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port), strerror(errno));
        goto ERR;
    }
    send_len = send(sock, send_buf, strlen(send_buf)+1, 0);
    if (-1 == send_len)
    {
        printf("send failed, send_len: %d, err: %s\n", send_len, strerror(errno));
        goto ERR;
    }
    printf("send success\n");
    if (0 == strcmp(send_buf, "quit"))
    {
        goto EXIT;
    }
    recv_len = recv(sock, recv_buf, sizeof(recv_buf)-1, 0);
    if (-1 == recv_len)
    {
        printf("recv failed, recv_len: %d, err: %s\n", strerror(errno));
        goto ERR;
    }
    printf("echo: %s\n", recv_buf);
    sleep(3);
EXIT:
    close(sock);
    return 0;
ERR:
    if (sock > -1)
    {
        close(sock);
    }
    return 0;
}
