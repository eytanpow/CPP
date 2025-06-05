

#include "LRU.h"
#include <stdlib.h>

void PrintPointer(void *data)
{
    printf("%p ", (dll_iter_t)data);
}

static size_t hashFunc(void *val)
{
    return (*((int *)val)) % 3;
}

// called in hash find
// compares data of the dll to data recieved
// data of the dll is of type hash entry which holds the pointer to the "Priority"
static int matchFunc(void *data1, void *data2)
{
    return DLLGet(((hashEntry *)data1)->p_todll) == data2;
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

    return DLLGet(DLLBegin(lru->data_list));
}

void *getLRUValue(LRU *lru, void *data)
{
    hashEntry *foundHashEntry = HashFind(lru->hash, data);
    if (foundHashEntry == NULL)
    {
        printf("getLRUValue is NULL \n");
        return NULL;
    }

    dll_iter_t nodeToRemove = foundHashEntry->p_todll;
    // DLLRemove((foundHashEntry)->p_todll);
    foundHashEntry->p_todll = DLLPushfront(lru->data_list, data);

    return DLLGet(foundHashEntry->p_todll);
}

void putLRUValue(LRU *lru, void *data)
{

    hashEntry *entry = (hashEntry *)malloc(sizeof(hashEntry));

    hashEntry *found = HashFind(lru->hash, data);

    if (found != NULL)
    {
        printf("data alredy in LRU \n");
        DLLRemove(found->p_todll);
        found->p_todll = DLLPushfront(lru->data_list, data);
        return;
    }

    if (lru->current_size == lru->hash_size)
    {
        printf("remove LRU from Cache \n");
        void *leastUsedData = DLLGet(DLLPrev(DLLEnd(lru->data_list)));
        HashRemove(lru->hash, leastUsedData);
        DLLPopback(lru->data_list);
        lru->current_size--;
    }

    entry->p_todll = DLLPushfront(lru->data_list, data);
    // printf("p_dll  is %p \n", entry->p_todll);
    HashInsert(lru->hash, entry);

    HashPrintAll(lru->hash, PrintPointer);
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
        void *data = DLLGet(it);     /* node payload    */
        printf("%d ", *(int *)data); /* user’s value    */
        it = DLLNext(it);
    }
    putchar('\n');
}