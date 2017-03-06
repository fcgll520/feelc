#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

const static int S_MAX_SIZE = 100;

class Queue
{
public:
    Queue()
    {
        //printf("Queue\n");
        in = out = used_size = 0;        
        max_size = S_MAX_SIZE;
        pdata = new int[max_size];

    }
    ~Queue()
    {
        //printf("~Queue\n");
        delete[] pdata;
        pdata = NULL;
    }

    int enqueue(int val)
    {
        if (used_size == max_size)
        {
            return -1;
        }
        //printf("enqueue, in: %d, val: %d\n", in, val);
        pdata[in] = val;
        in = (in+1) % max_size;
        used_size += 1;

        return in;
    }

    int dequeue()
    {
        if (used_size == 0)
        {
            return -1;
        }
        used_size -= 1;
        int pos = out;
        //printf("dequeue, out: %d, val: %d\n", out, pdata[out]);
        out = (out+1) % max_size;
        return pos;
    }
    int get_val(int pos)
    {
        return pdata[pos];
    }

private:
    int             max_size;
    int             used_size;
    int             *pdata;
    int             in;
    int             out;
};


void * producer(void * arg)
{
    Queue *q = (Queue *)arg;
    int i = 0;
    int sleep_time = 0;

    srand((int)time(0));

    for (i = 0; i < S_MAX_SIZE; i++)
    {
        sleep_time = rand() % 1000;
        usleep(sleep_time);
        if (-1 == q->enqueue(i*100))
        {
            printf("tid: %ld, enqueue failed, %d\n", pthread_self(), i);
        }
        else
        {
            //printf("tid: %ld, enqueue, %d\n", pthread_self(), i);
        }
    }
    return NULL;
}

void * consumer(void *arg)
{
    Queue *q = (Queue *)arg;
    int pos;
    int total = 0;
    int sleep_time = 0;

    srand((int)time(0));

    while (1)
    {
        sleep_time = rand() % 1000;
        usleep(sleep_time * 2);
        pos = q->dequeue();
        if (pos != -1)
        {
            //printf("tid: %ld, dequeue, %d -> %d\n", pthread_self(), pos, q->get_val(pos));
            printf("dequeue, %d -> %d\n", pos, q->get_val(pos));
            total += 1;
        }
        else
        {
            if (total == S_MAX_SIZE)
            {
                break;
            }
        }
    }
    return NULL;
}

int main()
{
    pthread_t producerTid = -1, consumerTid = -1;
    Queue q;

    pthread_create(&producerTid, NULL, producer, &q);
    pthread_create(&consumerTid, NULL, consumer, &q);

    pthread_join(producerTid, NULL);
    pthread_join(consumerTid, NULL);
    return 0;
}