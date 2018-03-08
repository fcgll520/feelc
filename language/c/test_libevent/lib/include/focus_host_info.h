#ifndef _FOCUS_HOST_INFO_H_
#define _FOCUS_HOST_INFO_H_

#include <stdint.h>
#include <vector>
#include <string>

class HostChunkInfo
{
public:
    std::string _host_ip;
    int32_t _chunk_num;
};

class FocusHostInfo
{
public:
    FocusHostInfo();
    virtual ~FocusHostInfo();

    int32_t size();
    bool empty();
    void clear();
    HostChunkInfo &operator[](int32_t i);

    void push_back(HostChunkInfo &host_info);
    void sort();

protected:
    std::vector<HostChunkInfo> _host_infos;
};

inline
int32_t FocusHostInfo::size()
{
    return (int32_t)_host_infos.size();
}

inline
void FocusHostInfo::push_back(HostChunkInfo &host_info)
{
    _host_infos.push_back(host_info);
}

inline
bool FocusHostInfo::empty()
{
    return _host_infos.empty();
}

inline
HostChunkInfo &FocusHostInfo::operator[](int32_t i)
{
    return _host_infos[i];
}

#endif

