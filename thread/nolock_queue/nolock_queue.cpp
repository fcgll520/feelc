#include <stdio.h>

struct Node
{
    int key;
};

class Queue
{
    int enqueue();

    int dequeue();


private:
    int             max_size;
    int             used_size;
    struct Node     queue;
    int             in;
    int             out;
};

int main(int argc, char const *argv[])
{
    return 0;
}