#ifndef _LIMIT_H_
#define _LIMIT_H_

#include <stdint.h>

const int32_t MAX_HOSTNAME_LEN = 16;
const int32_t MAX_HOST_NUM = 256;

const int32_t MAX_SHADOW_NUM = 10;

const int32_t MAX_TIME_LENGTH = 128;

const int32_t MAX_PATH_LENGTH = 512;
const int32_t MAX_PATH_DEPTH = 1000;
/*
* @date     2012-08-31
* @comment  MAX_PATH_LENGTH is used as the total length including '\0',
*            thus use a new variable MAX_PATH_SIZE with the value instead
*/
const int32_t MAX_PATH_SIZE  = MAX_PATH_LENGTH;

const int32_t MAX_CHUNKSERVER_NAME_LENGTH=512;

const int32_t MAX_REPLICA_NUM = 100;
const int32_t MAX_PREFETCH_NUM = 10;
//const int32_t MAX_CHUNK_NUM_PER_FILE = 160;       //10g max file, 64M chunksize
//modify by chenxd 2009-04-07
const int32_t MAX_CHUNK_NUM_PER_FILE = 0xFFFF;

const int32_t MAX_FILE_NUM_PER_DIR = 512;           //..

const int64_t MAX_CHUNK_NUM = 0x7FFFFFFFFFFFFFFFLL; //待修正
const int64_t MAX_FILE_NUM = 0x7FFFFFFFFFFFFFFFLL;

const int32_t MAX_CHUNK_INFO_PER_LINE = 1024;//镜像文件中每个chunk最大字节数
const uint32_t MAX_REPORT_OR_DELETE_CHUNK_NUM = 1024;//每次上报或者删除chunk数

//2007-11-26
//Long Shubing add
const int32_t MAX_LOCAL_NAME_LENGTH = 512;
const int64_t MAX_DEAD_INTERVAL = 300000; //6mins
//end

//2008-04-01
const int32_t MAX_DATA_ARRAY_SIZE = 512;
const int32_t MAX_COPY_ARRAY_SIZE = 32;
//end

//2009-03-21
//add by chenxd
const int32_t MAX_SEND_ARRAY_ONCE_NUM = 16;//读写线程累计16*128K=2M，可开始发送，形成pipe line
//end

//add by manzr
const int32_t MAX_CHUNK_INFO_UPDATE_ARRAY_NUM=512;
const int32_t MAX_MONITOR_FILE_SYSTEM_EVENTS_NUM=1024;
//end

const int32_t MAX_COPYMOVE_LIMIT = 24;


#endif

