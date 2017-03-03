#include <stdio.h>

int main()
{
    int array[] = { 8, 15, 6, 20, 25, 3, 1};

    int i = 0, j = 0, tmp;
    int len = sizeof(array)/sizeof(array[0]);

    for (i = 0; i < len; i++)
    {
        for (j = i+1; j < len; j++)
        {
            if (array[i] > array[j])
            {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }

    for (i = 0; i < len; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}