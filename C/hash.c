
#include <stdlib.h>
#include <stdio.h>
#include "dll.h"
#include "hash.h"
/******************************************************************************
 *                          Typedef , Enum, Structs  			              *
 ******************************************************************************/

struct hash
{
	dll_t **table;
	hash_func_t hash_func;
	is_match_t is_match;
	size_t table_size;
};

/******************************************************************************
							 Static Functions Definitions
******************************************************************************/

#define DLL_In_INdex(hash, i) ((hash->table[i]))

dll_t *FindList(hash_t *hash, void *data);
/******************************************************************************
							Main Implementation
******************************************************************************/

hash_t *HashCreate(hash_func_t hash_func, size_t table_size,
				   is_match_t is_match)
{
	hash_t *hash_table = NULL;

	hash_table = malloc(sizeof(hash_t));

	assert(NULL != hash_table);
	if (NULL == hash_table)
	{
		return (NULL);
	}

	hash_table->table = calloc(sizeof(dll_t *), table_size);

	assert(NULL != hash_table->table);
	if (NULL == hash_table->table)
	{
		free(hash_table);
		return (NULL);
	}

	hash_table->hash_func = hash_func;
	hash_table->is_match = is_match;
	hash_table->table_size = table_size;

	return (hash_table);
}

void HashDestroy(hash_t *hash)
{
	size_t index = 0;

	for (index = 0; index < hash->table_size; ++index)
	{
		if (NULL != (hash->table[index]))
		{
			DLLDestroy(hash->table[index]);
		}
	}
	free(hash->table);
	free(hash);
}

status_t HashInsert(hash_t *hash, const void *data)
{
	size_t index = 0;
	dll_iter_t iter = NULL;

	index = hash->hash_func((void *)data);
	
	if (NULL == DLL_In_INdex(hash, index))
	{
		DLL_In_INdex(hash, index) = DLLCreate();
	}

	iter = DLLInsert(DLL_In_INdex(hash, index), DLLBegin(DLL_In_INdex(hash, index)), (void *)data);

	if (iter == DLLEnd(DLL_In_INdex(hash, index)))
	{
		return (FAIL);
	}

	return (SUCCESS);
}

void HashRemove(hash_t *hash, const void *data)
{
	size_t index = 0;
	dll_iter_t iter = NULL;

	index = hash->hash_func((void *)data);

	NULL_ASSERT(DLL_In_INdex(hash, index));

	iter = DLLFind(DLLBegin(DLL_In_INdex(hash, index)),
				   DLLEnd(DLL_In_INdex(hash, index)), hash->is_match, (void *)data);

	if (iter == DLLEnd(DLL_In_INdex(hash, index)))
	{
		printf("not found what to remove \n");
		return;
	}
	DLLRemove(iter);
}

void *HashFind(const hash_t *hash, const void *data)
{

	dll_t *dll = NULL;
	dll_iter_t iter = NULL;

	dll = FindList((hash_t *)hash, (void *)data);

	if (dll == NULL)
	{
		printf("Hash Find did not found data \n");
		return NULL;
	}

	iter = DLLFind(DLLBegin(dll), DLLEnd(dll), hash->is_match, (void *)data);

	if (DLLIsEqual(iter, DLLEnd(dll)))
	{
		return NULL;
	}

	return DLLGet(iter);
}

size_t HashSize(const hash_t *hash)
{
	size_t index = 0;
	size_t count = 0;

	for (index = 0; index < hash->table_size; ++index)
	{
		if (NULL != DLL_In_INdex(hash, index) && 0 != DLLSize(DLL_In_INdex(hash, index)))
		{
			count += DLLSize(DLL_In_INdex(hash, index));
		}
	}

	return (count);
}

int HashIsEmpty(const hash_t *hash)
{
	return HashSize(hash) == 0;
}

status_t HashForEach(hash_t *hash, action_func_t act_func, const void *params)
{
	status_t status = SUCCESS;
	size_t index = 0;

	for (index = 0; index < hash->table_size; ++index)
	{
		if (NULL != DLL_In_INdex(hash, index))
		{
			status = DLLForEach(DLLBegin(DLL_In_INdex(hash, index)), DLLEnd(DLL_In_INdex(hash, index)),
								act_func, (void *)params);
			if (SUCCESS != status)
			{
				return (status);
			}
		}
	}

	return (status);
}

size_t getKey(hash_t *hash, void *data)
{
	return hash->hash_func(data);
}

/******************************************************************************
							Static Functions Implementation
******************************************************************************/

dll_t *FindList(hash_t *hash, void *data)
{
	size_t index = 0;
	index = hash->hash_func(data);

	return DLL_In_INdex(hash, index);
}

void HashPrintAll(const hash_t *hash, void (*print_func)(void *))
{
	size_t i = 0;

	assert(hash != NULL);
	assert(print_func != NULL);

	for (i = 0; i < hash->table_size; ++i)
	{
		if (hash->table[i] != NULL && !DLLIsEmpty(hash->table[i]))
		{
			printf("Bucket %lu:\n", i);
			DLLForEach(DLLBegin(hash->table[i]), DLLEnd(hash->table[i]),
					   (action_func_t)print_func, NULL);
			printf("\n");
		}
	}
}