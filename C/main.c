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
    PrintRecent(lru);
    return after - before;
}

#define min(a, b) (((a) < (b)) ? (a) : (b))

int maxArea(int *height, int heightSize)
{

    int p1 = 0, p2 = 1;
    int maxShape = 0;
    int curMinHeight = height[0], curMinHeightIndex = 0;
    for (int i = 1; i < heightSize; i++)
    {
        if (abs(curMinHeight - height[i]) * (i - curMinHeightIndex) > maxShape)
        {
            maxShape = abs(curMinHeight - height[i]) * (i - curMinHeightIndex);
        }

        if (height[i] > curMinHeight)
        {
            curMinHeight = height[i];
            curMinHeightIndex = i;
        }
    }

    return maxShape;
}

// int main()
// {
//     LRU *lru = CreateLRU(3);
//     int key1 = 1;
//     int a = 0, b = 1, c = 2, d = 3;
//     printf("hello\n");

//     putLRUValue(lru, &a);
//     printf("recentUsed is %d\n", *(int *)seeRecentUsed(lru));
//     putLRUValue(lru, &b);
//     printf("recentUsed is %d\n", *(int *)seeRecentUsed(lru));
//     putLRUValue(lru, &c);
//     printf("recentUsed is %d\n", *(int *)seeRecentUsed(lru));
//     putLRUValue(lru, &d);
//     printf("recentUsed is %d\n", *(int *)seeRecentUsed(lru));
//     hashEntry *get = getLRUValue(lru, &b);
//     printf("value is %d\n", *(int *)get);
//     printf("recentUsed is %d\n", *(int *)seeRecentUsed(lru));
//     getLRUValue(lru, &d);
//     getLRUValue(lru, &a);
//     printf("recentUsed is %d\n", *(int *)seeRecentUsed(lru));

//     //   getLRUValue(lru, &key1);
//     // printf("bye - bye\n");

//     return 0;
// }

int main(void)
{
    int a = 0, b = 1, c = 2, d = 3, e = 4;

    /**********************************************************************
     * 1. Duplicate before cache is full (cap 4)                          *
     *********************************************************************/
    puts("\n=== Duplicate before full ===");
    LRU *cap4 = CreateLRU(4);

    assert(Put(cap4, &a) == 1); /* size 1 */
    assert(Put(cap4, &b) == 1); /* size 2 */
    PrintLRUStatus(cap4);
    assert(Put(cap4, &a) == 0); /* duplicate – size still 2 */
    assert(cap4->current_size == 2);
    MustGet(cap4, &a); /* MRU moved but still size-2 */
    PrintLRUStatus(cap4);

    /**********************************************************************
     * 2. Duplicate after cache is full (cap 3)                           *
     *********************************************************************/
    puts("\n=== Duplicate after full ===");
    LRU *cap3 = CreateLRU(3);
    Put(cap3, &a);
    Put(cap3, &b);
    Put(cap3, &c); /* cache full */
    assert(cap3->current_size == 3);

    /* reinserting ‘b’ must only promote, no eviction, size remains 3 */
    assert(Put(cap3, &b) == 0);
    assert(cap3->current_size == 3);
    /* verify original keys still present */
    MustGet(cap3, &a);
    MustGet(cap3, &c);

    /**********************************************************************
     * 3. Hammer duplicate 1 000× (cap 10)                                *
     *********************************************************************/
    // puts("\n=== Hammer duplicate 1 000× ===");
    // LRU *cap10 = CreateLRU(10);
    // Put(cap10, &d); /* first insert */
    // for (int i = 0; i < 1000; ++i)
    // {
    //     assert(Put(cap10, &d) == 0); /* never grows   */
    // }
    // assert(cap10->current_size == 1);
    // MustGet(cap10, &d);

    /**********************************************************************
     * 4. Mixed unique / duplicate pattern                                *
     *********************************************************************/
    puts("\n=== Mixed unique + duplicate pattern ===");
    LRU *mix = CreateLRU(3);
    Put(mix, &a); /* [a]             */
    Put(mix, &b); /* [b,a]           */
    Put(mix, &c); /* [c,b,a]         */
    assert(mix->current_size == 3);

    /* duplicate b  (no eviction) -> [b,c,a] */
    assert(Put(mix, &b) == 0);
    assert(mix->current_size == 3);
    MustGet(mix, &b);

    /* new key d should evict *a* (LRU) -> [d,b,c] */
    Put(mix, &d);
    assert(mix->current_size == 3);
    assert(getLRUValue(mix, &a) == NULL); /* a was evicted */

    puts("\nALL NEW TESTS PASSED.\n");
    return 0;
}