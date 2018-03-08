#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <stdint.h>
#include <vector>
#include <iostream>
#include "file_info.h"

class FileInfo;
class FileInfos;
class FileSystemImpl;

class Directory
{
public:
    enum SoryType
    {
        NONE_SORT = 0,
        SORT_BY_CREAT_TIME = 1
    };
    typedef FileInfo *iterator;

    void begin() const;
    void begin();
    iterator next() const;
    iterator next();
    bool done() const;
    bool done();
    bool empty() const;
    bool empty();
    void push_back(FileInfos *file_infos);

    void sort();

    void clear();
    int32_t size() const;
    int32_t size();

    friend std::ostream &operator<<(std::ostream &os, const Directory &direc);
private:
    Directory();
    ~Directory();

    mutable int32_t _dir_id;
    mutable int32_t _file_id;

    std::vector<FileInfos *> _directory;

    std::vector<FileInfo *> _sorted_result;
    bool _is_sorted;
    mutable int32_t _sorted_id;

    friend class FileSystemImpl;
};

inline
void Directory::push_back(FileInfos *file_infos)
{
    _directory.push_back(file_infos);
}

inline
void Directory::begin() const
{
    _dir_id = 0;
    _file_id = 0;
    _sorted_id = 0;
}

inline
void Directory::begin()
{
    _dir_id = 0;
    _file_id = 0;
    _sorted_id = 0;
}

#endif

