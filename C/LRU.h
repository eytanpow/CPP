
#pragma once
#include "dll.h"
#include "hash.h"
#include <stdio.h>

typedef struct LRUCache
{
    int hash_size;
    int current_size;
    dll_t *data_list;
    hash_t *hash;
} LRU;

// struct for the data of the "priority" dll
typedef struct ListVAl
{
    void *data; // data user inserted

} listValue;

// data should be first this is mandatory
typedef struct HashData
{
    dll_iter_t p_todll;
} hashEntry; // hash entry

/******************************************************************************
 *Description: Creates a new LRU cache with a specified size.
 *Parameters: Size of the LRU cache (maximum number of items to store).
 *Return Value: Pointer to the newly created LRU cache.
 *Time Complexity: O(1)
 *Space Complexity: O(n), where n is the size of the cache.
 *Notes: Returns NULL if memory allocation fails.
 ******************************************************************************/
LRU *CreateLRU(size_t size);

/******************************************************************************/
void putLRUValue(LRU *lru, void *data);

/******************************************************************************
 *Description: Retrieves a value from the LRU cache and marks it as most
 *             recently used.
 *Parameters: lru - pointer to the LRU cache.
 *            data - pointer to the data to retrieve.
 *Return Value: Pointer to the data if found, NULL otherwise.
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 ******************************************************************************/
void *getLRUValue(LRU *lru, void *data);

/******************************************************************************
 *Description: Returns the most recently used value in the LRU cache without
 *             modifying the order of elements.
 *Parameters: lru - pointer to the LRU cache.
 *Return Value: Pointer to the most recently used value.
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes: Returns NULL if the cache is empty.
 ******************************************************************************/
void *seeRecentUsed(LRU *lru);

/******************************************************************************
 *Description: Prints the current state of the LRU cache from most recently
 *             used to least recently used.
 *Parameters: lru - pointer to the LRU cache.
 *Return Value: None.
 *Time Complexity: O(n)
 *Space Complexity: O(1)
 ******************************************************************************/
void PrintLRUStatus(const LRU *lru);