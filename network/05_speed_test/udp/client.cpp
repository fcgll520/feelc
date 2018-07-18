#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
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
    int sockfd, num;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in server, peer;
    if(argc != 3)
    {
        printf("Usage: %s <IP address> <PORT>\n", argv[0]);
        exit(1);
    }

    if((sockfd=socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket() error\n");
        exit(1);
    }
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));

    server.sin_addr.s_addr = inet_addr(argv[1]);
    if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("connect() error.\n");
        exit(1);
    }

    uint64_t seq = 0;
    size_t send_len = sizeof(ping_req_t);
    ping_req_t *preq = (ping_req_t *)buf;
    preq->seq = seq++;
    preq->send_stamp = getTickCount();
    printf("send request\n");
    send(sockfd, preq, send_len, 0);
    printf("send data, recv data\n");

    uint64_t cycle_recv_size = 0;
    uint64_t last_stamp = getTickCount();
    while(1)
    {
        if((num = recv(sockfd, buf, MAXDATASIZE, 0)) == -1)
        {
            printf("recv() error, err:%s\n", strerror(errno));
            break;
        }
        cycle_recv_size += num;

        uint64_t now = getTickCount();
        uint64_t interval = now - last_stamp;
        if (interval >= 1000)    
        {
            printf("interval:%llu, bandwidth: %lluKbps\n", interval, (cycle_recv_size*8*1000)/(interval*1024));
            cycle_recv_size = 0;
            last_stamp = now;
        }
    }
    close(sockfd);
    return 0;
}    