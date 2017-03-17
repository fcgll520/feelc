#include <stdio.h>

class Deque
{
public:
    void push_back(int x)
    {
        printf("Deque push_back\n");
    }
    void push_front(int x)
    {
        printf("Deque push_front\n");
    }
    void pop_back()
    {
        printf("Deque pop_back\n");
    }
    void pop_front()
    {
        printf("Deque pop_front\n");
    }
};

class Sequence
{
public:
    virtual void push(int x) = 0;
    virtual void pop() = 0;
};

class Stack : public Sequence
{
public:
    void push(int x)
    {
        mDeque.push_back(x);
    }
    void pop()
    {
        mDeque.pop_back();
    }
private:
    Deque mDeque;
};

class Queue : public Sequence
{
public:
    void push(int x)
    {
        mDeque.push_back(x);
    }
    void pop()
    {
        mDeque.pop_front();
    }
private:
    Deque mDeque;
};

int main()
{
    Sequence *s1 = new Stack();
    Sequence *s2 = new Queue();

    s1->push(10);
    s1->pop();

    s2->push(10);
    s2->pop();

    return 0;
}