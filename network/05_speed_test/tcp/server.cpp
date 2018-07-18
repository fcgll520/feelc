#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <errno.h>

#define PORT 12340
#define MAXDATASIZE (1024+100)

struct ping_req_t
{
    uint64_t    seq;
    uint64_t    send_stamp;
};

struct ping_rsp_t
{
    uint64_t    seq;
    uint64_t    send_stamp;
};

uint64_t getTickCount()
{
    struct timespec tsNowTime;
    clock_gettime(CLOCK_MONOTONIC, &tsNowTime);
    return (uint64_t)((uint64_t)tsNowTime.tv_sec * 1000 + (uint64_t)tsNowTime.tv_nsec / 1000000);
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    socklen_t addrlen;
    int num, rsp_len;
    char buf[MAXDATASIZE];

    if(argc != 2)
    {
        printf("Usage: %s <PORT>\n", argv[0]);
        exit(1);
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Creating socket failed.\n");
        exit(1);
    }

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("Bind() error.\n");
        exit(1);
    }
    if (listen(sockfd, 5) == -1)
    {
        perror("listen error\n");
        exit(1);
    }
    printf("accept...\n");
    int conn_sock = accept(sockfd, (struct sockaddr *)&client, &addrlen);
    printf("accept ok, conn_sock:%u\n", conn_sock);

    uint64_t last_stamp = getTickCount();
    uint64_t cycle_recv_size = 0;
    addrlen = sizeof(client);
    while (1)
    {
        uint64_t seq = 0;
        size_t send_len = sizeof(ping_req_t) + 1024;
        ping_req_t *preq = (ping_req_t *)buf;
        preq->seq = seq++;
        preq->send_stamp = getTickCount();
        int real_send_len = send(conn_sock, preq, send_len, 0);
        if (send_len != real_send_len)
        {
            printf("sendto failed, real_send_len:%d, err:%s\n", real_send_len, strerror(errno));
            break;
        }
    }
    close(conn_sock);
    close(sockfd);
    return 0;
}

#if 0
        cycle_recv_size += num;
        ping_req_t *preq = (ping_req_t *)buf;

        /*printf("recv message(%d) from client(%s:%d), seq:%llu, stamp:%llu\n", num,
            inet_ntoa(client.sin_addr), htons(client.sin_port),
            preq->seq, preq->send_stamp);*/

        //ping_rsp_t *rsp = (ping_rsp_t *)preq;
        //sendto(sockfd, rsp, rsp_len, 0, (struct sockaddr *)&client, len);

        uint64_t now = getTickCount();
        uint64_t interval = now - last_stamp;
        if (interval >= 1000)    
        {
            printf("interval:%llu, bandwidth: %lluKbps\n", interval, (cycle_recv_size*8*1000)/(interval*1024));
            cycle_recv_size = 0;
            last_stamp = now;
        }
#endif