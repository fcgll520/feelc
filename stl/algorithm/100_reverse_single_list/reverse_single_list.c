#include <stdio.h>
#include <assert.h>
#include <malloc.h>


typedef int DataType;  
  
typedef struct LinkNode  
{  
    DataType data;  
    struct LinkNode* next;  
}LinkNode,*pLinkNode;//结点结构体  
  

void AddList(pLinkNode phead, DataType x)
{
    assert(phead);
    pLinkNode tmp = (pLinkNode)malloc(sizeof(LinkNode));
    assert(tmp != NULL);
    tmp->data = x;
    tmp->next = phead->next;
    phead->next = tmp;
}

void DisPlay(pLinkNode phead)
{
    pLinkNode tmp = phead->next;
    for (;tmp != NULL; tmp=tmp->next)
    {
        printf("%d ", tmp->data);
    }
    printf("\n\n");
}

void ReserveList(pLinkNode phead)
{
    pLinkNode next = NULL, front = NULL, cur = NULL, new_head = NULL;
    
    cur = phead->next;
    while (cur)
    {
        next = cur->next;
        new_head = cur;
        cur->next = front;
        front = cur;
        cur = next;
    }
    phead->next = new_head;
}

int main()
{
    pLinkNode phead = (pLinkNode)malloc(sizeof(LinkNode));
    phead->data = -1; //第一个节点为头
    phead->next = NULL;
    assert(phead != NULL);
    AddList(phead, 5);
    AddList(phead, 4);
    AddList(phead, 3);
    AddList(phead, 2);
    AddList(phead, 1);

    DisPlay(phead);
    ReserveList(phead);
    DisPlay(phead);


    return 0;
}

