

#include "LRU.h"
#include <stdlib.h>

static size_t hashFunc(void *val)
{
    return (*(((hashEntry *)val)->data)) % 3;
}

static int matchFunc(void *data1, void *data2)
{
    return DLLGet((dll_iter_t)data1) == DLLGet((dll_iter_t)data2);
}

LRU *CreateLRU(size_t lruSize)
{

    LRU *lru;

    lru = (LRU *)malloc(sizeof(LRU));

    if (lru == NULL)
    {
        printf("lru allocation failed");
        return NULL;
    }

    lru->current_size = 0;
    lru->hash_size = lruSize;
    lru->data_list = DLLCreate();
    lru->hash = HashCreate(hashFunc, lru->hash_size, matchFunc);

    return lru;
}

void *seeRecentUsed(LRU *lru)
{
    hashEntry *leastUsed = DLLGet(DLLBegin(lru->data_list));

    return leastUsed->data;
}

void *getLRUValue(LRU *lru, void *data)
{
    hashEntry *entry = (hashEntry *)malloc(sizeof(hashEntry));
    entry->data = data;
    hashEntry *foundHashEntry = HashFind(lru->hash, entry);

    if (foundHashEntry == NULL)
    {
        printf("getLRUValue is NULL \n");
        return NULL;
    }

    entry->p_todll = DLLPushfront(lru->data_list, entry);
    DLLRemove(((hashEntry *)foundHashEntry)->p_todll);

    return foundHashEntry->data;
}

void putLRUValue(LRU *lru, void *data)
{
    // value that will be inserted to list
    // listValue *valueToInsert = (listValue *)malloc(sizeof(valueToInsert));
    // entry be inserted to the hash_table
    hashEntry *entry = (hashEntry *)malloc(sizeof(hashEntry));
    entry->data = data;

    hashEntry *found = HashFind(lru->hash, entry);

    if (found != NULL)
    {
        printf("data alredy in LRU \n");
        DLLRemove(found->p_todll);
        found->p_todll = DLLPushfront(lru->data_list, found);
        return;
    }

    if (lru->current_size == lru->hash_size)
    {
        printf("remove LRU from Cache");
        hashEntry *leastUsedData = DLLGet(DLLPrev(DLLEnd(lru->data_list)));
        HashRemove(lru->hash, leastUsedData);
        DLLPopback(lru->data_list);
        lru->current_size--;
    }

    entry->data = data;
    entry->p_todll = DLLPushfront(lru->data_list, entry);
    HashInsert(lru->hash, entry);

    lru->current_size++;
}

void PrintLRUStatus(const LRU *lru)
{
    if (!lru || DLLIsEmpty(lru->data_list))
    {
        puts("[LRU empty]");
        return;
    }

    printf("LRU state  (MRU → LRU): ");

    dll_iter_t it = DLLBegin(lru->data_list);       /* first real node */
    while (!DLLIsEqual(it, DLLEnd(lru->data_list))) /* until sentinel  */
    {
        hashEntry *entry = (hashEntry *)DLLGet(it); /* node payload    */
        printf("%d ", *(int *)entry->data);         /* user’s value    */
        it = DLLNext(it);
    }
    putchar('\n');
}