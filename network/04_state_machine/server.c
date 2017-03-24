#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <assert.h>
#include <event.h>


#define SERVER_LISTEN_PORT  (8899)

enum conn_states
{
    CONN_LISTENING,
    CONN_READ,
    CONN_WRITE,
    CONN_CLOSING,
    CONN_MAX_STATE,
};

struct conn_t
{
    struct event    event;
    int             event_flags;
    int             sock;
};


int set_noblack(int sock)
{
    int flags;

    flags = fcntl(sock, F_GETFL, 0);
    if (flags < 0)
    {
        printf("call fcntl() failed, F_GETFL failed, err: %s\n", strerror(errno));
        return -1;
    }
    if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        printf("call fcntl() failed, set O_NONBLOCK failed, err: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

void *event_handler(int sock, short event_flags, void * arg)
{
    printf("event_handler\n");
    return NULL;
}

int conn_new(struct conn_t *pconn, int sock, int event_flags)
{
    pconn->sock = sock;
    pconn->event_flags = event_flags;

    event_set(&(pconn->event), pconn->sock, pconn->event_flags, event_handler, pconn);
    if (event_add(&(pconn->event), NULL))
    {
        printf("call event_add() failed\n");
        return -1;
    }

    return 0;
}

int main()
{
    int sock = -1;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    struct conn_t conn;

    if (NULL == event_init())
    {
        printf("call event_init() failed\n");
        goto ERR;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        printf("create socket failed, err: %s\n", strerror(errno));
        goto ERR;
    }

    memset(&server_addr, 0, addr_len);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_LISTEN_PORT);
    if (-1 == bind(sock, (struct sockaddr *)&server_addr, addr_len))
    {
        printf("socket bind failed, err: %s\n", strerror(errno));
        goto ERR;
    }
    // if (-1 == set_noblack(sock))
    // {
    //     goto ERR;
    // }

    (void)conn_new(&conn, sock, EV_READ|EV_PERSIST);

    if (event_dispatch())
    {
        printf("call event_dispatch() failed\n");
        goto ERR;
    }

    close(sock);
    printf("end\n");
    return 0;
ERR:
    if (sock != -1)
    {
        close(sock);
    }
    return -1;
}