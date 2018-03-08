#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */
#include "uthash.h"
#include <assert.h>
#include <errno.h>
struct my_struct
{
    char            key[20];
    char            val[20];
    UT_hash_handle  hh;
};

struct my_struct * find_from_hash(struct my_struct *head, const char *key)
{
    assert(key != NULL);

    struct my_struct * pbucket_head = NULL, *pindex = NULL, *pnext = NULL;
    HASH_FIND_STR(head, key, pbucket_head);
    if (NULL == pbucket_head)
    {
        return NULL;
    }
    HASH_ITER(hh, pbucket_head, pindex, pnext)
    {
        if (0 == strcmp(pindex->key, key))
        {
            //printf("%s-%s\n", pindex->key, pindex->val);
            return pindex;
        }
    }
    assert(0);
    return NULL;
}

int main(int argc, char *argv[])
{
    struct my_struct *s, *tmp, *next, *head = NULL;
    int i = 0;

    for (int i = 0; i < 1000; ++i)
    {
        s = (struct my_struct *)calloc(1, sizeof(struct my_struct));
        assert(s != NULL);
        sprintf(s->key, "%d", i);
        sprintf(s->val, "%d", i);
        HASH_ADD_STR(head, key, s);
    }
    tmp = find_from_hash(head, "888");
    if (NULL != tmp)
    {
        printf("%s-%s\n", tmp->key, tmp->val);
    }


    HASH_ITER(hh, head, tmp, next)
    {
        //printf("%s-%s\n", tmp->key, tmp->val);
    }
    return 0;
}

