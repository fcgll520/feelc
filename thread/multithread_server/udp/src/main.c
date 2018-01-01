#include "query_thread.h"
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

const static int32_t S_PORT = 55555;


int main(int argc, char const *argv[])
{
	pthread_t tlog[10];
	pthread_t tid[10];

	for (int32_t i = 0; i < 10; ++i)
	{
		tlog[i] = i;
		pthread_create(&tid[i], NULL, query_thread_cb, &tlog[i]);
		usleep(2000);
	}

	sleep(3);

	for (int i = 0; i < 10; ++i)
	{
		pthread_join(tid[i], NULL);
	}
	
	return 0;
}