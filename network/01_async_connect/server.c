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

int main(int argc, char **argv)
{
    int sock = -1;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(server_addr);

    memset(&server_addr, 0, addr_len);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("call socket() failed, err: %s\n", strerror(errno));
        return -1;
    }
    
    if (-1 == bind(sock, (const struct sockaddr *)&server_addr, addr_len))
    {
        printf("call bind() failed, err: %s\n", strerror(errno));
        return -1;
    }

    if (-1 == listen(sock, 1000))
    {
        printf("call listen() failed, err:%s\n", strerror(errno));
        return -1;
    }

    memset(&client_addr, 0, addr_len);

    int conn_sock = accept(sock, (struct sockaddr *)&client_addr, &addr_len);
    if (-1 == conn_sock)
    {
        printf("call accept() failed, err:%s\n", strerror(errno));
        close(sock);
        return -1;        
    }
    printf("call accept() success, client_addr: %s\n", inet_ntoa(client_addr.sin_addr));
    

    close(sock);
    return 0;
}