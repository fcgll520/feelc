#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    struct in_addr addr = { atoi(argv[1]) };
    printf("%s\n", inet_ntoa(addr));
    return 0;
}

