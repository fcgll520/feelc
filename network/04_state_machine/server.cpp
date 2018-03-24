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
#include <malloc.h>
#include <list>
#include <arpa/inet.h>

using std::list;

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
    int             state;

    char            recv_buf[512];
    int             recv_len;
    char            send_buf[512];
    int             send_len;
};

list<struct conn_t *> s_conn_list_head;

void drive_machine(struct conn_t *pconn);

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

void *event_handler(int sock, short event_flags, void *arg)
{
    struct conn_t *pconn = (struct conn_t *)arg;
    drive_machine(pconn);
    return NULL;
}
int conn_new(int sock, int event_flags, int conn_state)
{
    struct conn_t *pconn = NULL;

    pconn = (struct conn_t *)calloc(1, sizeof(struct conn_t));
    assert(pconn);

    pconn->sock = sock;
    pconn->event_flags = event_flags;
    pconn->state = conn_state;

    event_set(&(pconn->event), pconn->sock, pconn->event_flags, event_handler, pconn);
    if (event_add(&(pconn->event), NULL))
    {
        printf("call event_add() failed\n");
        goto ERR;
    }
    s_conn_list_head.push_back(pconn);
    return 0;
ERR:
    if (NULL != pconn)
    {
        free(pconn);
    }
    return -1;
}

void conn_free(struct conn_t *pconn)
{
    s_conn_list_head.remove(pconn);
    if (pconn)
    {
        event_del(&(pconn->event));
        free(pconn);
    }
}
void drive_machine(struct conn_t *pconn)
{
    int stop = false;
    int exit = false;
    int conn_sock = -1;
    int recv_len = -1, send_len = -1;
    struct sockaddr_in client_addr;
    socklen_t addrlen;

    while (!stop)
    {
        switch(pconn->state)
        {
            case CONN_LISTENING:
                printf("accept, sock: %d\n", pconn->sock);
                memset(&client_addr, 0, sizeof(struct sockaddr_in));
                conn_sock = accept(pconn->sock, (struct sockaddr *)(&client_addr), &addrlen);
                if (-1 == conn_sock)
                {
                    if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
                    {
                        stop = false;
                    }
                    else
                    {
                        printf("call accept() failed, sock: %d, err: %s\n",
                               pconn->sock, strerror(errno));
                        stop = true;
                    }
                    break;
                }
                //TODO:不知道为什么这里输出不了客户端的地址
                printf("new connect, sock: %d, client_addr: %s, client_port: %d, addrlen: %d\n",
                       conn_sock, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port),
                       addrlen);
                if (-1 == conn_new(conn_sock, EV_READ|EV_PERSIST, CONN_READ))
                {
                    printf("call conn_new() failed, sock: %d\n");
                }
                stop = true;
                break;
            case CONN_READ:
                printf("read, sock: %d\n", pconn->sock);
                recv_len = recv(pconn->sock, pconn->recv_buf, sizeof(pconn->recv_buf)-1, 0);
                if (-1 == recv_len)
                {
                    if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
                    {
                        stop = false;
                    }
                    else
                    {
                        printf("recv failed, sock: %d, err: %s\n", pconn->sock, strerror(errno));
                    }
                    stop = true;
                    break;
                }
                else if (0 == recv_len)
                {
                    pconn->state = CONN_CLOSING;
                    break;
                }
                if (0 == strcmp(pconn->recv_buf, "quit"))
                {
                    exit = true;
                    pconn->state = CONN_CLOSING;                    
                    break;
                }
                pconn->recv_len = recv_len;
                memcpy(pconn->send_buf, pconn->recv_buf, recv_len);
                pconn->send_len = pconn->recv_len;
                pconn->state = CONN_WRITE;
                break;
            case CONN_WRITE:
                printf("write, sock: %d\n", pconn->sock);
                send_len = send(pconn->sock, pconn->send_buf, pconn->send_len, 0);
                if (-1 == send_len)
                {
                    if (errno == EAGAIN || errno == EWOULDBLOCK)
                    {
                        stop = false;
                    }
                    else
                    {
                        printf("send failed, sock: %d, send_len: %d, err: %s\n",
                               pconn->sock, send_len, strerror(errno));
                        stop = true;
                    }
                    break;
                }
                stop = true;
                pconn->state = CONN_READ;
                break;
            case CONN_CLOSING:
                printf("connect close, sock: %d\n", pconn->sock);
                if (pconn->sock > -1)
                {
                    close(pconn->sock);
                    pconn->sock = -1;
                }
                stop = true;
                conn_free(pconn);
                if (exit)
                {
                    event_loopbreak();
                }
                break;
            default:
                printf("unknown state, state: %d\n", pconn->state);
                break;
        }
    }

}



int main()
{
    int sock = -1;
    struct sockaddr_in server_addr;
    socklen_t addrlen = sizeof(struct sockaddr_in);

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
    printf("listen sock: %d\n", sock);

    if (-1 == set_noblack(sock))
    {
        goto ERR;
    }
    memset(&server_addr, 0, addrlen);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_LISTEN_PORT);
    if (-1 == bind(sock, (struct sockaddr *)&server_addr, addrlen))
    {
        printf("socket bind failed, err: %s\n", strerror(errno));
        goto ERR;
    }

    if (-1 == listen(sock, 100))
    {
        printf("listen socket failed,err: %s\n", strerror(errno));
        goto ERR;
    }
    if (-1 == conn_new(sock, EV_READ|EV_PERSIST, CONN_LISTENING))
    {
        printf("call conn_new() failed\n");
        goto ERR;
    }
    printf("into dispatch...\n");
    if (0 != event_dispatch())
    {
        printf("call event_dispatch() failed\n");
        goto ERR;
    }

    {
        list<struct conn_t*>::iterator it;

        for (it = s_conn_list_head.begin(); it != s_conn_list_head.end();it++)
        {
            //TODO:存在内存泄漏的问题，等熟悉了STL后再来处理
            //conn_free(*it);
            //it = s_conn_list_head.erase(it);
        }   
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
