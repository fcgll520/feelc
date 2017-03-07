#include <stdio.h>

void swap(int *p, int *q)
{
    int tmp = *p;
    *p = *q;
    *q = tmp;
}

int main()
{
    int array[] = { 8, 15, 6, 20, 25, 5, 3, 13, 19, 1};

    int i = 0, j = 0, min;
    int len = sizeof(array)/sizeof(array[0]);

    for (i = 0; i < len; i++)
    {
        min = i;
        for (j = i+1; j < len; j++)
        {
            if (array[min] > array[j])
            {
                min = j;
            }
        }
        swap(&array[i], &array[min]);
    }

    for (i = 0; i < len; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}