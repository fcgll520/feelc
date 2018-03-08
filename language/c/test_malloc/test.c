#include <malloc.h>
#include <stdio.h>
#include <errno.h>
int main()
{
    void *p = malloc(1024*1024*1024*10);
    if (NULL == p)
    {
        printf("err: %s", strerror(errno));
    }
    printf("%p\n", p);
    gets(NULL);
    free(p);
    return 0;
}
