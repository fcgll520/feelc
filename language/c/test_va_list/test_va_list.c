#include <stdarg.h>
#include <stdio.h>


int AveInt(int,...);

void main()
{
    printf("%d\n",AveInt(2,'a', 'b'));
    printf("%d\n",AveInt(4,'a', 'b', 'c', 'd'));
    return;
}
int AveInt(int v,...)
{
    printf("v: %d\n", v);
    char ReturnValue = 0;
    int i=v;
    va_list ap ;
    va_start(ap,v);
    while(i>0)
    {
        ReturnValue = va_arg(ap, int);
        printf("%c ", ReturnValue);
        i--;
    }
    va_end(ap);
    return 0;
}
