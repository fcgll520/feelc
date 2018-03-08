#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_

#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <fast_lock.hpp>
#include "chunk_detail.h"
#include "system_resources.h"

class FileSystemImpl;
class File;
class Directory;
class FileStatus;
class FocusHostInfo;

class FileSystem
{
public:
    File *open(const char *pathname, int32_t flags, int32_t replica_num = 0);
    File *creat(const char *pathname, int32_t replica_num = 0);
    int32_t unlink(const char *pathname);
    int32_t rename(const char *old_path, const char *new_path);

    int32_t mkdir(const char *pathname);
    Directory *opendir(const char *pathname, int32_t sort_flag = 0);
    int32_t closedir(Directory *direc);
    //FileInfos* ls(const char* pathname);

    int32_t exists(const char *pathname);
    int32_t stat(const char *pathname, FileStatus *file_status, bool get_exact_len = false);

    int32_t copy_from_local_file(const char *src, const char *dstf, bool delete_local = false);
    int32_t copy_to_local_file(const char *srcf, const char *dst, bool delete_source = false);

    int32_t close(File *file);

    // add by liubiao 20101221
    void set_use_shadow_master(bool use_shadow_master);
    bool get_use_shadow_master();

    // add by director 20120530
    // ���������߳��Ƿ�ʹ��shadow master �ı�־λ�� Ĭ��Ϊtrue
    // ���ҽ���ȫ�ֿ��غ��߳̿��ض�Ϊtrue ʱ��ʹ��shadowmaster
    // �˽ӿ�����ȫ��ʹ��shadow������ĳ���̲߳���ʹ��shadow�����Ÿ�xbase ʹ��
    void set_thread_use_shadow_master( bool use_shadow_master );
    bool get_thread_use_shadow_master();

    int32_t get_replica_num(const char *pathname);
    int32_t set_replica_num(const char *pathname, uint32_t replica_num);

    int32_t focus_chunks(const char *pathname);
    int32_t get_focus_info(const char *pathname, FocusHostInfo *focus_host_info);

    static FileSystem *get(bool is_multithread = false);
    static FileSystem *get(const char *pathname, bool is_multithread = false);
    static FileSystem *multithread_get();
    static FileSystem *multithread_get(const char *pathname);
    static void destroy(FileSystem *file_system);

    // add by lml 20111108
    // ���ڽ������ڶ������ģ�飬��Ƶ���򿪹ر�ĳһ�ļ���Ӧ��(��httpdown)���Ե��øýӿ�
    // �ýӿڿ��ܵ��¸������ݵ����ݣ� ��ʱ�䲻�ܼ�⵽�� ����������ݣ� cache_valid_secondsԽ�������ݿ�����Խ��
    int set_chunkinfo_cache_param(int cache_valid_seconds, int max_cache_files);

    // add by lml 20111110 �˽ӿ���ñ����, �Ỻ���ļ���С����Ϣ, ��ʱ���Ÿ�httpdownʹ��
    // �˽ӿ�Ҳ������ֻ���ڶ�Ӧ��(��д����)�ĳ������
    int enable_fileinfo_cache();

    // add by lml 20111110
    int enable_stat_dump();

    // add by lml 20120105
    // �˽ӿ��������ó�ʱ��������������chunk server, ��д���ݣ��Լ����Դ���
    // ����Ŀǰ��ʱʱ�䲻̫��������httpdown��˵����Ҫ�϶̵ĳ�ʱ(����Ӧ�ÿ��Բ�����)
    int set_conn_cs_param(int connect_cs_timeout_ms, int rw_cs_timeout_ms, int read_cs_retry_times);


    // �����ӿڸ�����ƽ̨ʹ��
    int get_read_chunk_info(const char *filename, int32_t chunk_idx, ChunkDetails &chunk_infos_ret,int32_t &max_chunk_idx);

    // ����df �ӿ� �����߷�����������ȫ�ֵ���
    int df( SystemResources &sys_resource );

    Directory *ls(const char *path);
public:
    int32_t nread_get_active_file(File **file);
protected:
    FileSystem(FileSystemImpl *file_system_impl)
        : _file_system_impl(file_system_impl)
    {
    }
    ~FileSystem();
private:
    FileSystemImpl *_file_system_impl;
    static FileSystem *_instance;
    static FastLock _lock;

};

#endif

