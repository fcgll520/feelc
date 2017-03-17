#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int s_len = 0;

void swap(int *p, int *q)
{
    int tmp = *p;
    *p = *q;
    *q = tmp;
}

void display(int a[])
{
    int i = 0;

    for (i = 0; i < s_len; ++i)
    {
        printf("%d  ", a[i]);
    }
    printf("\n");
}

int Partition(int a[], int low, int high)
{
    int pivotkey;

    pivotkey = a[low];
    while (low < high)
    {
        while (low < high && a[high] >= pivotkey)
        {
            high--;
        }
        swap(&a[low], &a[high]);
        while (low < high && a[low] <= pivotkey)
        {
            low++;
        }
        swap(&a[low], &a[high]);
    }
    //printf("pivotkey: %d, low: %d.\n", pivotkey, low);
    return low;
}

void QuickSort(int a[], int low, int high)
{
    int pivot;
    if (low < high)
    {
        pivot = Partition(a, low, high);
        //display(a);
        QuickSort(a, low, pivot - 1);
        QuickSort(a, pivot + 1, high);
    }
}

int main()
{
    int array[] = { 8, 15, 6, 20, 25, 3, 1};
    int i = 0;

    s_len = sizeof(array) / sizeof(int);

    QuickSort(array, 0, s_len-1);

    display(array);

    return 0;
}
