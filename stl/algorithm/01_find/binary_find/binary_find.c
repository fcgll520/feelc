#include <stdio.h>

int binary_find(int array[], int low, int high, int key)
{
    int mid;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if (key == array[mid])
            return mid;

        if(key < array[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int binary_find1(int array[], int low, int high, int key)
{
    int mid;
    if(low == high)
    {
        if(array[low] == key)
            return low;
        else
            return -1;
    }
    else
    {
        mid = (low + high) / 2;
        if(mid == low);
            mid++;
        if(key < array[mid])
            return binary_find1(array, low, mid - 1, key);
        else
            return binary_find1(array, mid, high, key);
    }
}

int main()
{
    int array[] = {1, 3, 5, 6, 8, 13, 15, 19, 20, 25};
    int len = sizeof(array)/sizeof(array[0]);

    int pos = binary_find(array, 0, len-1, 3);
    if (-1 == pos)
    {
        printf("not find\n");
    }
    else
    {
        printf("find, %d\n", array[pos]);
    }

    pos = binary_find1(array, 0, len-1, 3);
    if (-1 == pos)
    {
        printf("not find\n");
    }
    else
    {
        printf("find, %d\n", array[pos]);
    }


    return 0;
}
