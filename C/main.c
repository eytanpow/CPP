#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "LRU.h"

/* ---------- tiny helpers ---------- */
static void PrintRecent(LRU *lru)
{
    printf("MRU : %d\n", *(int *)seeRecentUsed(lru));
}

/* expects the returned pointer to equal key_ptr */
static void MustGet(LRU *lru, int *key_ptr)
{
    int *ret = (int *)getLRUValue(lru, key_ptr);
    assert(ret && ret == key_ptr);
    PrintRecent(lru);
}

/* inserts and returns whether size changed */
static size_t Put(LRU *lru, int *key_ptr)
{
    size_t before = lru->current_size;

    putLRUValue(lru, key_ptr);
    size_t after = lru->current_size;
    assert(after == before || after == before + 1); /* sanity */
    // PrintRecent(lru);
    return after - before;
}

int main(void)
{
    int a = 0, b = 1, c = 2, d = 3, e = 4;

    puts("\n=== Duplicate after full ===");
    LRU *cap3 = CreateLRU(3);
    Put(cap3, &a);
    Put(cap3, &b);
    // Put(cap3, &c); /* cache full */
    // assert(cap3->current_size == 3);
    PrintLRUStatus(cap3);

    /* reinserting ‘b’ must only promote, no eviction, size remains 3 */

    printf("\n\n\n*******************\n");
    assert(Put(cap3, &a) == 0);
    PrintLRUStatus(cap3);
    // assert(cap3->current_size == 3);
    assert(Put(cap3, &d) == 0);
    PrintLRUStatus(cap3);
    // assert(cap3->current_size == 3);
    // PrintLRUStatus(cap3);
    // /* verify original keys still present */
    // // PrintLRUStatus(cap3);
    MustGet(cap3, &a);
    // MustGet(cap3, &c);

    return 0;
}