#ifndef _CHUNK_DETAIL_H_
#define _CHUNK_DETAIL_H_

#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <memory.h>
#include <fcntl.h>

class ChunkDetail
{
public:
    static const int32_t ChunkDetail_Max_Replica_Num = 10;
    static const int32_t ChunkDetail_Max_Rrefetch_Num = 16;
public:
    ChunkDetail()
        : _chunk_id(0)
        , _version_number(0)
        , _replica_num(0)
    {
        memset(_hostname, 0, ChunkDetail_Max_Replica_Num * ChunkDetail_Max_Rrefetch_Num);
    }
public:
    int64_t     _chunk_id;      //chunk��id
    int64_t _version_number;
    int32_t         _replica_num;
    char            _hostname[ChunkDetail_Max_Replica_Num][ChunkDetail_Max_Rrefetch_Num]; //chunk��ip��ַ
};


class ChunkDetails
{
public:
    static const int32_t Max_Prefetch_Num = 10;
public:
    ChunkDetails():_chunk_num(0) {};
public:
    int32_t     _chunk_num;
    ChunkDetail _infos[Max_Prefetch_Num];
};

#endif

