#ifndef _GFS_ERRNO_H_
#define _GFS_ERRNO_H_

#include <stdint.h>

const int32_t   ERR_NOENT = 2;
const int32_t   ERR_NOSPACE = 3;
const int32_t   ERR_FILE_LARGE = 4;
const int32_t   ERR_NETWORK = 5;
const int32_t   ERR_MAX_FILE_NUM = 6;
const int32_t   ERR_READ_BEYOND_FILE = 7;
const int32_t   ERR_OLDVERSION = 8;
const int32_t   ERR_BUSY = 9;
const int32_t   ERR_TIMEOUT = 10;
const int32_t   ERR_AGAIN = 11;
const int32_t   ERR_NOAGAIN = 12;
const int32_t   ERR_NOTDIR = 13;
const int32_t   ERR_LOCAL = 14;
const int32_t   ERR_DATA = 15;
const int32_t   ERR_NULL_FILE_PTR = 16;
const int32_t   ERR_MUTEX = 17;

//add by bing 2008-02-29
const int32_t ERR_NOROOT = 20;
const int32_t ERR_PATH_INVALID = 21;
const int32_t ERR_LOG_QUEUE_FULL = 22;
const int32_t ERR_POOL_CONSTRUCT = 23;
const int32_t ERR_NOLEASE = 24;
const int32_t ERR_EXIST = 25;
const int32_t ERR_NODE_NOEXIST = 26;
const int32_t ERR_CHUNK_NOEXIST = 27;
const int32_t ERR_MODE = 28;
const int32_t ERR_LOCKED = 29;
const int32_t ERR_LOWER_LEVEL = 30;
const int32_t ERR_CHUNK_INDEX = 31;
const int32_t ERR_NOPRIMARY = 32;
const int32_t ERR_LEASE_GET = 33;
const int32_t ERR_LEASE_GRANT = 34;
const int32_t ERR_LEASE_STATE = 35;
const int32_t ERR_LEASE_REVOKE = 36;
const int32_t ERR_LEASE_DESTROY = 37;
const int32_t ERR_OPERATION = 38;
const int32_t ERR_CHUNK_ALLOCATE = 39;
//end

//write read chunk error no add by linri 2008-02-22
const int32_t   ERR_FILE_SEEK = 40; //lseek error
const int32_t   ERR_FILE_READ_ZERO = 41; //Ҫ�����ļ��ֽڲ�Ϊ��
const int32_t   ERR_FILE_OPEN = 42;
const int32_t   ERR_FILE_READ = 43;
const int32_t   ERR_FSM_NO_EXIST = 44;
const int32_t   ERR_DATA_NO_SAME_SIZE = 45;
const int32_t   ERR_LARGE_THAN_CHUNK = 46;//����д���ݻᳬ��64M
const int32_t   ERR_FILE_WRITE = 47;
const int32_t   ERR_WRITE_DISK_FULL = 48;
const int32_t   ERR_PRE_WRITE_OP_FAILED = 49;//��ʾ�ڴ˴�д����ǰ��д����ʧ��
const int32_t   ERR_OLD_LEASE = 50;//��ʾ�˴�д������lease������
const int32_t   ERR_TIME_OUT = 51; //һ�β���ʱ���������ʱ
const int32_t   ERR_CHUNK_ALREADY_EXIST = 52;
const int32_t   ERR_INSERT_ARRAY = 53;
const int32_t   ERR_FILE_CREATE = 54;
const int32_t   ERR_NO_DATA_FSM = 55;
const int32_t   ERR_NOT_GOOD_START_POS = 56;//�ֲ�дû������start_pos
const int32_t   ERR_RESOURCE_LIMIT = 57;
const int32_t   ERR_GET_NEAREST_HOST = 58;
const int32_t   ERR_CONNECT_MYSELF = 59;//ת����ip���Լ�
const int32_t   ERR_DATA_FSM_STATE = 60;
const int32_t   ERR_BUFFER_USEDUP = 61; //data pool used up
//end

//add by bing 2008-03-31 rw thread
const int32_t   ERR_EXIST_2 = 70;   //chunk�Ѵ�����chunk����
const int32_t   ERR_CHUNK_NOEXIST_2 = 71;   //��chunk�������Ҳ�����Ӧchunk  ��chunk�ļ�������
const int32_t   ERR_CHUNK_INVALID_2 = 72;   //chunk id �� version num ��chunk�����в��Ϸ�
const int32_t   ERR_CHUNK_IMAGE_INSERT_2 = 73;  //�޷���chunk�����в����µ�chunk
const int32_t   ERR_CHUNK_PART_2 = 74;      //���ֶ�ȡ/����д��
const int32_t   ERR_LARGE_THAN_CHUNK_2 = 75;    //������chunk file��󳤶�����,append��ʱ�� �Ų���Ҫappend������
const int32_t   ERR_LOWER_LEVEL_2 = 76;     //ʵ��chunk�ļ�����ʧ�ܵ�
//end

// add by guoshiwei 2008-09-05 log
const int32_t ERR_LOG_FAILED = 77;
const int32_t ERR_DO_NOT_SUPPORT =78;

// end add by guoshiwei

const int32_t ERR_EIO = 79;

//extern int32_t gfs_errno;

/********** add by LUIS ***********/
const int32_t ERR_DECODE_DATAGRAM = 80;
/********** end add ***************/

/********* add by chenxd ***********/
const int32_t WARN_CHUNK_VERSION_LARGE = 101;  //����chunk��version num ����master��
/********* end add ****************/


//add by bing
const int32_t ERR_LOG_STATE = 102;
const int32_t ERR_LOG_TIMEOUT = 103;
const int32_t ERR_QUEUE_FULL = 104;
//end

//add by manzr
const int32_t ERR_SLEEP_TIMEOUT=105;
const int32_t ERR_SLEEP_CHUNKSERVER_NOEXIST=106;
const int32_t ERR_SLEEP_CHUNKSERVERID_NOEXIST=107;
const int32_t ERR_SLEEP_CHUNKSERVER_NOT_ONLINE=108;
const int32_t ERR_SLEEP_ILLEGALPARAM=109;

//add by chenhetian @2011-01-20
const int32_t   ERR_COPY_WRITE_DEST_EXIST_2 = 170;  //copy move Ŀ���chunk�Ѵ�����chunk����
const int32_t   ERR_COPY_WRITE_DEST_CHUNK_NOEXIST_2 = 171;  //copy move Ŀ�����chunk�������Ҳ�����Ӧchunk
const int32_t   ERR_COPY_WRITE_DEST_CHUNK_INVALID_2 = 172;  //copy move Ŀ���chunk id �� version num ��chunk�����в��Ϸ�
const int32_t   ERR_COPY_WRITE_DEST_CHUNK_IMAGE_INSERT_2 = 173;     //copy move Ŀ����޷���chunk�����в����µ�chunk
const int32_t   ERR_COPY_WRITE_DEST_CHUNK_PART_2 = 174;     //copy move Ŀ������ֶ�ȡ/����д��
const int32_t   ERR_COPY_WRITE_DEST_LARGE_THAN_CHUNK_2 = 175;   //copy move Ŀ���������chunk file��󳤶�����,append��ʱ�� �Ų���Ҫappend������
const int32_t   ERR_COPY_WRITE_DEST_LOWER_LEVEL_2 = 176;        //copy move Ŀ���ʵ��chunk�ļ�����ʧ�ܵ�
//end

//add by byz
const int32_t ERR_NEW_CHUNKID_ARRAY=110;
const int32_t ERR_GET_PARENT_NODE=111;
const int32_t ERR_HOST_NOT_ENOUGH=112;
const int32_t ERR_HOST_NOT_EXIST=113;
const int32_t ERR_OVER_FILE_SIZE=114;
const int32_t ERR_LOG_NETWORK=115;
const int32_t ERR_CS_NETWORK=116;
const int32_t ERR_CHUNK_INFOS_QUEUE_FULL=117;
const int32_t ERR_MUTATION_FSM_CONSTRUCT=118;
const int32_t ERR_INFOS_FSM_CONSTRUCT=119;
const int32_t ERR_CHUNK_MISSCHUNK=120;
const int32_t ERR_NO_FREE_READ_FSM=121;
const int32_t ERR_ALLOCATE_TIMEOUT=122;
const int32_t ERR_INODE_POOL_CONSTRUCT=123;
const int32_t ERR_DELETABLE_TIME=124;

//end

const int32_t ERR_CANNT_DELETE=125;

const int32_t ERR_GENERIC_NACK = 1000;

extern int32_t *__get_gfs_errno_location(void);
#define gfs_errno (*__get_gfs_errno_location())

#endif

