#include <stdio.h>
#include "cJSON.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    cJSON *proot = NULL;

    proot = cJSON_CreateObject();

    cJSON_AddStringToObject(proot, "ip", "192.168.1.1");

    cJSON *pip = cJSON_GetObjectItem(proot, "ip");
    printf("ip: %s\n", cJSON_Print(pip));
    printf("ip: %u\n", inet_addr(cJSON_Print(pip)));
    return 0;
}
