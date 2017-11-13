#include "add/add.h"
#include "sub/sub.h"
#include <stdio.h>

int main()
{
    Add add_tmp;
    printf("add: %d\n", add_tmp.add(1, 1));
    
    Sub sub_tmp;
    printf("sub: %d\n", sub_tmp.sub(1, 1));
    return 0;
}
