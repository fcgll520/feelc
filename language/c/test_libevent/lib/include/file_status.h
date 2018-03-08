#ifndef _FILE_STATUS_H_
#define _FILE_STATUS_H_

#include <stdint.h>
#include <fstream>
#include <string>
#include <cstring>

std::string byte_desc(int64_t len);
std::string limit_decimal(double d, int32_t places_after_decimal);

class FileStatus
{
public:
    enum TYPE
    {
        DIR_TYPE = 0,
        NORMAL_FILE_TYPE = 1,
        APPEND_FILE_TYPE = 2
    };
    FileStatus();

    int64_t get_len() const;
    void set_len(int64_t new_len);
    bool is_dir() const;
    void set_is_dir(bool is_dir);
    int32_t type() const;
    void type(int32_t new_type);
    friend std::ostream &operator<<(std::ostream &os, const FileStatus &file_status);
private:
    int64_t     _length;
    int32_t     _type;
    bool        _is_opened;
};

inline
int64_t FileStatus::get_len() const
{
    return _length;
}

inline
void FileStatus::set_len(int64_t new_len)
{
    _length = new_len;
}

inline
bool FileStatus::is_dir() const
{
    return _type == DIR_TYPE;
}

inline
void FileStatus::set_is_dir(bool is_dir)
{
    if (is_dir)
    {
        _type = DIR_TYPE;
    }
}

inline
int32_t FileStatus::type() const
{
    return _type;
}

inline
void FileStatus::type(int32_t new_type)
{
    _type = new_type;
}

#endif

