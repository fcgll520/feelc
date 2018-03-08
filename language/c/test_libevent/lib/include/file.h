#ifndef _FILE_H_
#define _FILE_H_

#include <sys/types.h>
#include <sys/uio.h>
#include <stdint.h>

class FileImpl;
class FileSystem;

class File
{
public:
    int32_t nread_init(void *buf, size_t count);
    int32_t nread_destroy();
    int32_t nread_cancel();
    int32_t nread_continue();
    int32_t nread_readed_count();
    int32_t nread_result();
    ssize_t write(const void *buf, size_t count);
    int64_t lseek(int64_t offset, int32_t whence);

    int32_t get_cache_timeout();
    void set_cache_timeout(int32_t timeout);
    bool eof();

private:
    ssize_t read(void *buf, size_t count);
    int64_t append(const void *buf, size_t count);
    ssize_t writev(const struct iovec *vector, int32_t count);
    int32_t truncate(uint64_t filesize);
    int32_t set_target_hostname(char *hostname, size_t len);
protected:
    File(FileImpl *file_impl);
    ~File();

    FileImpl *_file_impl;

    friend class FileSystem;
};

#endif

