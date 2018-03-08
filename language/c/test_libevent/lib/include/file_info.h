#ifndef _FILE_INFO_H_
#define _FILE_INFO_H_

#include <fstream>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include "limit.h"

class FileInfo
{
public:
    enum TYPE
    {
        DIR_TYPE = 0,
        NORMAL_FILE_TYPE = 1,
        APPEND_FILE_TYPE = 2
    };

    FileInfo()
        : _creat_time(0)
        , _chunk_num(0)
        , _type(-1)
    {
        _pathname[0] = 0;
    }

    FileInfo(const FileInfo &rhs)
        : _creat_time(rhs._creat_time)
        , _chunk_num(rhs._chunk_num)
        , _type(rhs._type)
    {
        memcpy(_pathname, rhs._pathname, sizeof(_pathname));
    }
    char        _pathname[MAX_PATH_LENGTH + 1];
    uint64_t    _creat_time;
    int32_t     _chunk_num;
//  int64_t     _length;    //file_length
    int32_t     _type;

    char *name();

    bool is_dir();

    uint64_t creat_time();

    friend std::ostream &operator<<(std::ostream &os, const FileInfo &file_info);

    bool operator<(const FileInfo &rhs) const
    {
        return _creat_time < rhs._creat_time;
    }

    void reset()
    {
        memset(_pathname, 0, sizeof(_pathname));
        _creat_time = 0;
        _chunk_num = 0;
        _type = -1;
    }

    template<typename Archive>
    void serialize(Archive &ar)
    {
        ar &_pathname;
        ar &_creat_time;
        ar &_chunk_num;
        ar &_type;
    }
};

inline
char *FileInfo::name()
{
    return _pathname;
}

inline
bool FileInfo::is_dir()
{
    return _type == DIR_TYPE;
}

inline
uint64_t FileInfo::creat_time()
{
    return _creat_time;
}


class FileInfos
{
public:
    FileInfos()
        : _num(0)
    {
    }
    FileInfos(const FileInfos &rhs)
        : _num(rhs._num)
    {
        memcpy(_infos, rhs._infos, sizeof(_infos));
    }

    int32_t     _num;
    FileInfo    _infos[MAX_FILE_NUM_PER_DIR];

    FileInfo &operator[](size_t i);
    int32_t append(FileInfo &fileinfo);

    int32_t size();

    void reset()
    {
        for (int32_t i = 0; i < _num; i++)
        {
            _infos[i].reset();
        }

        _num = 0;
    }

    template<typename Archive>
    void serialize(Archive &ar)
    {
        ar &_num;

        for (int32_t i = 0; i < _num; i++)
        {
            ar &_infos[i];
        }
    }
};

inline
int32_t FileInfos::size()
{
    return _num;
}

#endif

