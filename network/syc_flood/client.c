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

#define SERVER_PORT 8899
#define CLIENT_PORT 7777

int main(int argc, char **argv)
{
    int sock = -1;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(server_addr);
    int retry = 10;

    memset(&server_addr, 0, addr_len);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(SERVER_PORT);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("call socket() failed, err: %s\n", strerror(errno));
        return -1;
    }
    
    int i = 0;
    while (1)
    {
        i++;
        memset(&client_addr, 0, addr_len);
        client_addr.sin_family = AF_INET;
        client_addr.sin_addr.s_addr = 16777343 + i; //inet_addr("127.0.0.1");
        client_addr.sin_port = htons(CLIENT_PORT);

        if (-1 == bind(sock, (const struct sockaddr *)&client_addr, addr_len))
        {
            printf("call bind() failed, client_addr: %s, err: %s\n", inet_ntoa(client_addr.sin_addr), strerror(errno));
            return -1;
        }

        if (-1 == connect(sock, (const struct sockaddr *)&server_addr, addr_len))
        {
            printf("call connect() failed, port: %d, errno: %d, err: %s\n",
                ntohs(server_addr.sin_port), errno, strerror(errno));
        }
        else
        {
            printf("call connect() success\n");
        }
    }
    close(sock);
    return sock;
}