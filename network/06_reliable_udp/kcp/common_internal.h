#include <ikcp.h>

static const int32_t S_KCP_UPDATE_TIMEO = 10 * 1000;

void set_kcp(ikcpcb *kcp_handle);
void set_kcp_other(ikcpcb *kcp_handle);