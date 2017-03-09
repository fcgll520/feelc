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

#include <linux/ip.h>
#include <linux/tcp.h>

#define SERVER_PORT 8899

struct packet_t
{
    struct iphdr ip;
    struct tcphdr tcp;
};
                                                                     
struct pseudo_header_t
{
    unsigned int source_address;
    unsigned int dest_address;
    unsigned char placeholder;
    unsigned char protocol;
    unsigned short tcp_length;
    struct tcphdr tcp;
};

uint16_t in_cksum(const unsigned char *addr, int len)
{
    int nleft = len;
    const uint16_t *w = (const uint16_t *)addr;
    uint32_t sum = 0;
    uint16_t answer = 0;

    /*
     * Our algorithm is simple, using a 32 bit accumulator (sum), we add
     * sequential 16 bit words to it, and at the end, fold back all the
     * carry bits from the top 16 bits into the lower 16 bits.
     */
    while (nleft > 1)  {
    sum += *w++;
    nleft -= 2;
    }

    /* mop up an odd byte, if necessary */
    if (nleft == 1) {
    *(unsigned char *)(&answer) = *(const unsigned char *)w ;
    sum += answer;
    }

    /* add back carry outs from top 16 bits to low 16 bits */
    sum = (sum & 0xffff) + (sum >> 16);
    sum += (sum >> 16);
    /* guaranteed now that the lower 16 bits of sum are correct */

    answer = ~sum;              /* truncate to 16 bits */
    return answer;
}

void set_ip_and_tcp(struct packet_t *ppacket)
{
    ppacket->ip.ihl = 5;
    ppacket->ip.version = 4;
    ppacket->ip.tos = 0;
    ppacket->ip.tot_len = htons(40);
    ppacket->ip.id = getpid();
    ppacket->ip.frag_off = 0;
    ppacket->ip.ttl = 255;
    ppacket->ip.protocol = IPPROTO_TCP;
    ppacket->ip.check = 0;
    ppacket->ip.saddr = inet_addr("8.8.8.8");
    ppacket->ip.daddr = inet_addr("127.0.0.1");
    ppacket->tcp.source = getpid();
    ppacket->tcp.dest = htons(SERVER_PORT);
    ppacket->tcp.seq = getpid();
    ppacket->tcp.ack_seq = 0;
    ppacket->tcp.res1 = 0;
    ppacket->tcp.doff = 5;
    ppacket->tcp.fin = 0;
    ppacket->tcp.syn = 1;
    ppacket->tcp.rst = 0;
    ppacket->tcp.psh = 0;
    ppacket->tcp.ack = 0;
    ppacket->tcp.urg = 0;
    ppacket->tcp.window = htons(512);
    ppacket->tcp.check = 0;
    ppacket->tcp.urg_ptr = 0;
}

int main()
{
    
    int sock = -1;
    int send_len = 0;
    socklen_t addr_len = 0;
    struct sockaddr_in server_addr;
    struct packet_t packet;
    struct pseudo_header_t pseudo_header;
                                                                     
    set_ip_and_tcp(&packet);

    addr_len = sizeof(server_addr);
    memset(&server_addr, 0, addr_len);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = packet.tcp.source;
    server_addr.sin_addr.s_addr = packet.ip.daddr;
                                                                     
    if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
    {
        printf("create socket failed, err: %s\n", strerror(errno));
        return -1;
    }
            
    int i = 0;                                                        
    while(1)
    {
        packet.tcp.source++;
        packet.ip.id++;
        packet.tcp.seq++;
        packet.tcp.check = 0;
        packet.ip.check = 0;
        packet.ip.check = in_cksum((unsigned short *)&packet.ip, 20);
        pseudo_header.source_address = packet.ip.saddr;
        pseudo_header.dest_address = packet.ip.daddr;
        pseudo_header.placeholder = 0;
        pseudo_header.protocol = IPPROTO_TCP;
        pseudo_header.tcp_length = htons(20);

        memcpy(&(packet.tcp), &(pseudo_header.tcp), 20);
        packet.tcp.check = in_cksum((unsigned short *)&pseudo_header, 32);
       
        send_len = sendto(sock, &packet, 40, 0, (struct sockaddr *)&server_addr, addr_len);
        if (send_len == -1)
        {
            printf("sendto failed, err: %s\n", strerror(errno));
            return -1;
        }
        printf("send_len: %d\n", send_len);
        i++;
        if (i >= 100000)
        {
            break;
        }
    }
    shutdown(sock, SHUT_RDWR);
    return 0;
}



#if 0
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
        //client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        client_addr.sin_addr.s_addr = inet_addr("167.8.9.10");  //16777343 + i; //inet_addr("127.0.0.1");
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
        break;
    }
    close(sock);
    return sock;
}
#endif