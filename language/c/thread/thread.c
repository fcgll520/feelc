 
#include<stdio.h>
#include<stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/syscall.h>

void*  thread1(void* arg)
{
    pid_t tid = syscall(SYS_gettid);  
    printf("%llu\n", pthread_self());
    printf("%lu\n", tid);
    prctl(PR_SET_NAME,"THREAD1");
    while(1)
    {
        printf("thread1\n");
        sleep(1000);
    }
}

void thread2(void)
{
  while(1)
{
   printf("thread2\n");
  sleep(1000);
}
}
int main()
{
    printf("%d", sizeof(unsigned long));
  pthread_t th1,th2;
  void* retval;
   pthread_create(&th1,NULL,thread1,NULL);
  pthread_create(&th2,NULL,thread2,NULL);

  printf("main thread\n");
   pthread_join(&th1,&retval);
   pthread_join(&th2,&retval);
}
