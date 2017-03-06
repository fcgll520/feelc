#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

const static int S_MAX_SIZE = 11;
const static int S_THREAD_NUM = 10;

class Queue
{
public:
    Queue()
    {
        in = out = 0;
        size = S_MAX_SIZE;
        mask = size - 1;

        pdata = new int[size];
    }
    ~Queue()
    {
        delete[] pdata;
        pdata = NULL;
    }

    int enqueue(int val)
    {
        if (is_full())
        {
            return -1;
        }

        int success = 0;
        int old_in = -1, new_in = -1;

        do {
            old_in = in;
            new_in = in;
            //printf("tid: %ld, enqueue, new_in: %d, old_in: %d, val: %d\n", pthread_self(), new_in, old_in, val);
            pdata[new_in] = val;
            new_in = (new_in+1) % size;

            success = __sync_bool_compare_and_swap(&in, old_in, new_in);
        } while(success == 0);

        return old_in;
    }

    int dequeue()
    {
        if (is_empty())
        {
            return -1;
        }

        int success = 0;
        int old_out = -1, new_out = -1;

        do {
            old_out = out;
            new_out = out;
            new_out = (new_out+1) % size;
            success = __sync_bool_compare_and_swap(&out, old_out, new_out);
        } while(success == 0);

        return old_out;
    }
    int get_val(int pos)
    {
        return pdata[pos];
    }
private:
    int get_free_num()
    {
        return (mask + out - in);
    }
    bool is_empty()
    {
        return get_free_num() == mask ? true : false;
    }
    bool is_full()
    {
        return get_free_num() == 0 ? true : false;
    }
private:
    /*
        此队列对浪费一个位置，最多可以存储mask个元素即就是(size-1)个
        如果不浪费一个是无法区分队列的空和满的
     */
    int             size;   //最多可以存放的元素
    int             mask;   // size-1
    volatile int    in;
    volatile int    out;
    int             *pdata;
};

static Queue s_queue;

void * producer(void * arg)
{
    int i = *(int *)arg * 10000;
    int pos = -1;
    int sleep_time = 0;

    srand((int)time(0));

    while (1)
    {
        sleep_time = rand() % 1000;
        usleep(sleep_time);
        pos = s_queue.enqueue(i);
        if (-1 == pos)
        {
            printf("tid: %ld, enqueue failed, %d\n", pthread_self(), pos);
            usleep(1000);
        }
        else
        {
            printf("tid: %ld, enqueue, pos: %d -> %d\n", pthread_self(), pos, i);
            i++;
        }
    }
    return NULL;
}

void * consumer(void *)
{   
    int pos;
    int total = 0;
    int sleep_time = 0;

    srand((int)time(0));

    while (1)
    {
        sleep_time = rand() % 1000;
        usleep(sleep_time*2);
        pos = s_queue.dequeue();
        if (pos != -1)
        {
            printf("            consumer tid: %ld, dequeue, %d -> %d\n", pthread_self(), pos, s_queue.get_val(pos));
            total += 1;
        }
    }
    return NULL;
}



int main()
{
    int i = 0;
    pthread_t *pproducerTid = NULL, *pconsumerTid = NULL;

    pproducerTid = new pthread_t[S_THREAD_NUM];
    pconsumerTid = new pthread_t[S_THREAD_NUM];

    for (i = 0; i < S_THREAD_NUM; i++)
    {
        pthread_create(&pproducerTid[i], NULL, producer, &i);
        pthread_create(&pconsumerTid[i], NULL, consumer, &i);
        sleep(1);
    }

    for (i = 0; i < S_THREAD_NUM; i++)
    {
        pthread_join(pproducerTid[i], NULL);
        pthread_join(pconsumerTid[i], NULL);
    }

    delete[] pproducerTid;
    delete[] pconsumerTid;
    return 0;
}
