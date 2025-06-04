/******************************************************************************
 *	Author: 	Eytan Peros			                                          *
 *	Reviewer:	  			                                                  *
 *	Date:					                                                  *
 *******************************************************************************/

#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h>
#include <assert.h> /*assert */
/*************************FOR UTILS *****************************/
typedef enum
{
	FAIL = -1,
	SUCCESS = 0
} status_t;
#define NULL_ASSERT(x) (assert(x != NULL))

/*************************FOR UTILS *****************************/

typedef size_t (*hash_func_t)(void *);
typedef int (*is_match_func_t)(void *, void *);
typedef int (*action_func_t)(void *, void *);

typedef struct hash hash_t;

/*
#include "dll.h"

struct hash
{
	dll_t **table;
	hash_func_t hash_func;
	is_match_func_t is_match;
	size_t table_size;
};
*/

/******************************************************************************
 *Description: Creates a new hash table.
 *Arguments: hash_func - function which hashes the given data.
 * 			 is_match - the function by which to find the data.
 *			 if is_match(data1, data2) == 0: data1 is different than data2,
 *			 if is_match(data1, data2) == 1: data1 is equal to data2.
			 table_size - range of the indexes which the hash func can map to.
 *Return Value: Pointer to the created hash table.
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes: Returns NULL if memory allocation fails.
 *       Undefined behavior if is_match is NULL or if size is mismatched.
 ******************************************************************************/
hash_t *HashCreate(hash_func_t hash_func, size_t table_size,
				   is_match_func_t is_match);

/******************************************************************************
 *Description: Destroys the hash table.
 *Arguments: Pointer to the hash table.
 *Return Value: None.
 *Time Complexity: O(n)
 *Space Complexity: O(1)
 *Notes: None.
 ******************************************************************************/
void HashDestroy(hash_t *hash);

/******************************************************************************
 *Description: Inserts the data to the hash table.
 *Arguments: The hash table and the data to be inserted.
 *Return Value: 0 if the insertion was successful, -1 otherwise.
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes:
 ******************************************************************************/
status_t HashInsert(hash_t *hash, const void *data);

/******************************************************************************
 *Description: Removes the element matching the given data from the hash table.
 *Arguments: The hash table and the data to be removed.
 *Return Value:
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes: Undefined behaviour if data is not in the hash table.
 ******************************************************************************/
void HashRemove(hash_t *hash, const void *data);

/******************************************************************************
 *Description: Finds the element with the matching data in the hash table.
 *Arguments: Pointer to the hash table and the data to find.
 *Return Value: The data of the found element, NULL otherwise.
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes:
 ******************************************************************************/
void *HashFind(const hash_t *hash, const void *data);

/******************************************************************************
 *Description: Returns the number of elements in the hash table.
 *Arguments: Pointer to the hash table.
 *Return Value: The number of elements in the hash table.
 *Time Complexity: O(n)
 *Space Complexity: O(1)
 *Notes:
 ******************************************************************************/
size_t HashSize(const hash_t *hash);

/******************************************************************************
 *Description: Checks if the hash table has no elements.
 *Arguments: Pointer to the hash table.
 *Return Value: 1 if the hash table is empty, 0 otherwise.
 *Time Complexity: O(n)
 *Space Complexity: O(1)
 *Notes:
 ******************************************************************************/
int HashIsEmpty(const hash_t *hash);

/******************************************************************************
 *Description: Iterates on all elements in the hash table and acts on the data.
 *Arguments:   Pointer to the hash table, the functions which acts on the data
 *			   and parameters for the function.
 *Return Value: 0 if the action was successful, -1 otherwise.
 *Time Complexity: O(n)
 *Space Complexity: O(1)
 *Notes: act_func must not change the result of the hash func which hashes the
 *		 data.
 ******************************************************************************/
status_t HashForEach(hash_t *hash, action_func_t act_func, const void *params);

/***********************my addition******************************************/
size_t getKey(hash_t *hash, void *data);


#endif /* __HASH_H__ */
