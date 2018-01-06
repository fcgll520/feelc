#include "query_thread.h"
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

const static int32_t S_PORT = 55555;

int main(int argc, char const *argv[])
{
	const static int32_t thread_num = 10;
	pthread_t tlog[thread_num];
	pthread_t tid[thread_num];

	for (int32_t i = 0; i < thread_num; ++i)
	{
		tlog[i] = i;
		pthread_create(&tid[i], NULL, query_thread_cb, &tlog[i]);
		usleep(2000);
	}

	sleep(3);

	for (int i = 0; i < thread_num; ++i)
	{
		pthread_join(tid[i], NULL);
	}
	
	return 0;
}
