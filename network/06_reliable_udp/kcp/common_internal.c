#include "common_internal.h"
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void set_kcp(ikcpcb *kcp_handle)
{
	int32_t mode = 0;

	ikcp_wndsize(kcp_handle, 128, 128);

	switch (mode)
	{
	case 0:
		// 默认模式
		ikcp_nodelay(kcp_handle, 0, 10, 0, 0);
		ikcp_nodelay(kcp_handle, 0, 10, 0, 0);
		break;
	case 1:
		// 普通模式，关闭流控
		ikcp_nodelay(kcp_handle, 0, 10, 0, 1);
		ikcp_nodelay(kcp_handle, 0, 10, 0, 1);
		break;
	case 2:
		// 启动快速模式
		// 第二个参数 nodelay-启用以后若干常规加速将启动    //减少重传时间
		// 第三个参数 interval为内部处理时钟，默认设置为 10ms
		// 第四个参数 resend为快速重传指标，设置为2
		// 第五个参数 为是否禁用常规流控，这里禁止		   //拥塞窗口大小，对速度最重要的影响
		ikcp_nodelay(kcp_handle, 1, 10, 2, 1);			//2206 Kb/s  75%
		//ikcp_nodelay(kcp_handle, 0, 10, 2, 1);		//1782 Kb/s  50%
		//ikcp_nodelay(kcp_handle, 1, 10, 0, 1);		//1015 Kb/s  39%
		//ikcp_nodelay(kcp_handle, 1, 10, 2, 0);		//65Kb/s     36%
		break;
	default:
		break;
	}
}

void set_kcp_other(ikcpcb *kcp_handle)
{
//	kcp_handle->rx_minrto = 10;		//设置更小的最小重传时间
}
