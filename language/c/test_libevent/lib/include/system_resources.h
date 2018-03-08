#ifndef __SYSTEM_RESOURCES_H_
#define __SYSTEM_RESOURCES_H_

#include <stdint.h>
#include <ostream>
#include "limit.h"
#include <cstring>
#include <cstddef>

class SystemResources
{
public:
    class SingleChunkServer
    {
    public:
        SingleChunkServer()
            : _exist_chunk_num(0)
            , _avail_chunk_num(0)
            , _last_heart_beat_time(0)
            , _status(0)
            , _active_read_fsm_num(0)
            , _active_write_fsm_num(0)
            , _active_copy_move_fsm_num(0)
            , _active_lease_fsm_num(0)
            ,_exist_disk_size(0)
            ,_avail_disk_size(0)
            ,_use_disk_size(0)
            ,_online(1)
            ,_left_time_s(0)
        {
            memset(_hostname, 0, sizeof(_hostname));
        }

        SingleChunkServer(const SingleChunkServer &rhs)
            : _exist_chunk_num(rhs._exist_chunk_num)
            , _avail_chunk_num(rhs._avail_chunk_num)
            , _last_heart_beat_time(rhs._last_heart_beat_time)
            , _status(rhs._status)
            , _active_read_fsm_num(rhs._active_read_fsm_num)
            , _active_write_fsm_num(rhs._active_write_fsm_num)
            , _active_copy_move_fsm_num(rhs._active_copy_move_fsm_num)
            , _active_lease_fsm_num(rhs._active_lease_fsm_num)
            ,_exist_disk_size(rhs._exist_disk_size)
            ,_avail_disk_size(rhs._avail_disk_size)
            ,_use_disk_size(rhs._use_disk_size)
            ,_online(rhs._online)
            ,_left_time_s(rhs._left_time_s)
        {
            memcpy(_hostname, rhs._hostname, sizeof(_hostname));
        }
        void set(char *hostname
                 , uint32_t exist_chunk_num
                 , uint32_t avail_chunk_num
                 , uint64_t last_heart_beat_time
                 , int32_t status
                 , uint32_t active_read_fsm_num
                 , uint32_t active_write_fsm_num
                 , uint32_t active_copy_move_fsm_num
                 , uint32_t active_lease_fsm_num);

        void set(char *hostname
                 , uint32_t exist_chunk_num
                 , uint32_t avail_chunk_num
                 , uint64_t last_heart_beat_time
                 , int32_t status
                 , uint32_t active_read_fsm_num
                 , uint32_t active_write_fsm_num
                 , uint32_t active_copy_move_fsm_num
                 , uint32_t active_lease_fsm_num
                 , uint64_t exist_disk_size
                 , uint64_t avail_disk_size
                 , uint64_t use_disk_size);
        void set(char *hostname
                 , uint32_t exist_chunk_num
                 , uint32_t avail_chunk_num
                 , uint64_t last_heart_beat_time
                 , int32_t status
                 , uint32_t active_read_fsm_num
                 , uint32_t active_write_fsm_num
                 , uint32_t active_copy_move_fsm_num
                 , uint32_t active_lease_fsm_num
                 , uint64_t exist_disk_size
                 , uint64_t avail_disk_size
                 , uint64_t use_disk_size
                 , int64_t online
                 , int64_t left_time);
        friend std::ostream &operator<<(std::ostream &os, const SingleChunkServer &);

        template<typename Archive>
        void serialize(Archive &ar)
        {
            ar &_hostname;
            ar &_exist_chunk_num;
            ar &_avail_chunk_num;
            ar &_last_heart_beat_time;
            ar &_status;
            ar &_active_read_fsm_num;
            ar &_active_write_fsm_num;
            ar &_active_copy_move_fsm_num;
            ar &_active_lease_fsm_num;
            ar &_exist_disk_size;
            ar &_avail_disk_size;
            ar &_use_disk_size;
            ar &_online;
            ar &_left_time_s;

        }
    public:
        char            _hostname[MAX_HOSTNAME_LEN];
        uint32_t        _exist_chunk_num;
        uint32_t        _avail_chunk_num;
        uint64_t        _last_heart_beat_time;
        int32_t         _status;
        uint32_t        _active_read_fsm_num;
        uint32_t        _active_write_fsm_num;
        uint32_t        _active_copy_move_fsm_num;
        uint32_t        _active_lease_fsm_num;
        uint64_t        _exist_disk_size;
        uint64_t        _avail_disk_size;
        uint64_t        _use_disk_size;
        int64_t         _online;
        int64_t         _left_time_s;
    };

    enum
    {
        DEFAULT_MAX_CHUNK_SERVER_NUM = 2048
    };

    SystemResources();
    SystemResources(const SystemResources &rhs);
    void set(uint64_t master_time
             , int32_t total_file_num
             , int32_t total_chunk_num
             , int32_t total_chunk_server_num
             , int32_t total_lease_num
             , int32_t copy_move_num
             , int32_t broken_num
             , int32_t check_queue
             , int32_t miss_replicas
             , int32_t miss_chunks);
    void reset();
    int32_t total_used() const;
    int32_t total_available() const;

    int64_t total_used_disk_size() const;
    int64_t total_available_disk_size() const;

    SingleChunkServer &operator[](std::size_t idx);
    const SingleChunkServer &operator[](std::size_t idx) const;
    friend std::ostream &operator<<(std::ostream &, const SystemResources &);
    void sort();

    template<typename Archive>
    void serialize(Archive &ar)
    {
        int32_t chunk_server_num = 0;

        ar &_master_time;
        ar &_last_backup_time;
        ar &_total_file_num;
        ar &_total_chunk_num;
        ar &_total_chunk_server_num;
        chunk_server_num =
            _total_chunk_server_num < DEFAULT_MAX_CHUNK_SERVER_NUM ? \
            _total_chunk_server_num : DEFAULT_MAX_CHUNK_SERVER_NUM;

        for (int32_t i = 0; i < chunk_server_num; i++)
        {
            ar &_chunk_servers[i];
        }

        ar &_total_lease_num;
        ar &_copy_move_num;
        ar &_broken_num;
        ar &_check_queue;
        ar &_miss_replicas;
        ar &_miss_chunks;
    }
public:
    uint64_t    _master_time;
    uint64_t    _last_backup_time;
    int32_t     _total_file_num;
    int32_t     _total_chunk_num;
    int32_t     _total_chunk_server_num;
    SingleChunkServer   _chunk_servers[DEFAULT_MAX_CHUNK_SERVER_NUM];
    int32_t     _total_lease_num;
    int32_t     _copy_move_num;    //master copy move fsm
    int32_t     _broken_num; // lease失败的状态机
    int32_t     _check_queue;  //等待检查的chunk id的队列
    int32_t     _miss_replicas;  //丢了多少副本
    int32_t     _miss_chunks;    //丢了多少个chunk，也就是完全没有副本了

};

#endif

