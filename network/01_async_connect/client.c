#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <fcntl.h>
#include <errno.h>
#include <strings.h>
#include <string.h>

#define SERVER_PORT 8899

int main(int argc, char **argv)
{
    int old;
    int err;
    int errlen = sizeof(err);
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);
    int sock; 
    struct pollfd pfd;
    int ret;

    if (argc != 2) 
    {
        printf("Usage %s ip\n", argv[0]);
        return -1; 
    }
    sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock < 0)
    {
            printf("create socket failed, err: %s\n", strerror(errno));
            return -1; 
    } 

    memset(&addr, sizeof(addr), 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(SERVER_PORT);

    old = fcntl(sock, F_GETFL, 0); 
    if (fcntl(sock, F_SETFL, old|O_NONBLOCK) < 0) {
            printf("setting sock error: errno,%s\n", errno,strerror(errno));
            close(sock);
             return -1;
    }

    if (connect(sock, (struct sockaddr*)&addr, len) == -1 && errno != EINPROGRESS)
    {
        printf("error in connect, err: %s\n", errno,strerror(errno));
        goto ERR;
    }

    pfd.fd = sock;
    pfd.events = POLLOUT | POLLERR | POLLHUP | POLLNVAL;
    errno = 0;

    ret = poll(&pfd, 1, -1);

    if (ret < 0)
    {
        if (errno == EINTR)
        {
            goto ERR;
        }
        goto ERR;
    }
    else if (0 == ret) 
    {
        goto ERR;
    }

    if (pfd.revents & (POLLERR | POLLHUP | POLLNVAL)) {
        goto ERR;
    }
    if (getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, (socklen_t*)&errlen) == -1)
    {
        goto ERR;
    }
    if (err != 0)
    {
        printf("async connect failed, err: %s", strerror(err));
        goto ERR;
    }
    printf("Connect real OK\n");

    close(sock);
    return 0;

ERR:
    printf("err\n");
    if (sock != -1)
    {
        close(sock);
        return -1;
    }
}