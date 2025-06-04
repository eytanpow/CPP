
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
    int key;
    void *data;
} listValue;

// data should be first this is mandatory
typedef struct HashData
{
    int *data;
    dll_iter_t p_todll;
} hashEntry;

LRU *CreateLRU(size_t size);

void putLRUValue(LRU *lru, void *data);
void *getLRUValue(LRU *lru, void *data);
void *seeRecentUsed(LRU *lru);
void PrintLRUStatus(const LRU *lru);
