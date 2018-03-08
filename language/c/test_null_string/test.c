
#include <stdarg.h> /* for va_list */
#include <stdio.h> /* for size_t */ 
#define __ANDROID_LOG_PRINT__
#define LOGID_COMMON        0 //"common"
#define LOGID_COMMON_DESC   "livesdk_common"

#define LOGID_HTTPSERVER    1
#define LOGID_HTTPSERVER_DESC "livesdk_httpserver"

#define LOGID_TASK 2
#define LOGID_TASK_DESC "livesdk_task"

#define LOGID_P2P 3
#define LOGID_P2P_DESC "livesdk_p2p"

#define LOGID_PROTOCOL 4
#define LOGID_PROTOCOL_DESC "livesdk_protocol"

#define LOGID_PUSHSRV 5
#define LOGID_PUSHSRV_DESC "livesdk_pushsrv"

#define LOGID_SDK 6
#define LOGID_SDK_DESC "livesdk_sdk"

#define LOGID_LAUNCH_TASK 7
#define LOGID_LAUNCH_TASK_DESC "livesdk_launch_task"

#define LOGID_TRACKER 8
#define LOGID_TRACKER_DESC "livetask_tracker"
#define MAX_CNT 9

static char * s_module_name[MAX_CNT] = {
    (char *)LOGID_COMMON_DESC,
    (char *)LOGID_HTTPSERVER_DESC,
    (char *)LOGID_TASK_DESC,
    (char *)LOGID_P2P_DESC,
    (char *)LOGID_PROTOCOL_DESC,
    (char *)LOGID_PUSHSRV_DESC,
    (char *)LOGID_SDK_DESC
};

int main()
{
    printf("%s\n", s_module_name[3]);
    printf("%s\n", s_module_name[7]);
    return 0;
}
