#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h> /*size_t*/

typedef struct node *dll_iter_t;
typedef struct dll dll_t;
typedef int (*is_match_t)(void *, void *);
typedef int (*action_t)(void *, void *);

/* struct node 

	void *data;
	struct node *next;
	struct node *prev;
*/

/* struct dll

	struct node head;
	struct node tail;
*/

/******************************************************************************
*Description: Creates a new doubly linked list.
*Return Value: Pointer to the created dll.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns NULL if memory allocation fails.
******************************************************************************/
dll_t *DLLCreate(void);

/******************************************************************************
*Description: Deletes the entire doubly linked list.
*Arguments: Pointer to a doubly linked list.
*Return Value: void.
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
void DLLDestroy(dll_t *dll);

/******************************************************************************
*Description: Checks whether the given doubly linked list is empty.
*Arguments: buffer - pointer to a doubly linked list.
*Return Value: 1 if the doubly linked list is empty, 0 otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int DLLIsEmpty(const dll_t *dll);

/******************************************************************************
*Description: Returns the amount of nodes in the given doubly linked list.
*Arguments: buffer - pointer to a doubly linked list.
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
size_t DLLSize(const dll_t *dll);

/******************************************************************************
*Description: Gets the data pointed to by the given iterator.
*Parameters: An iterator.
*Return Value: The data pointed to by the iterator.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Note: Calling the function on the end of the list leads to undefined behavior
******************************************************************************/
void *DLLGet(const dll_iter_t iter);

/******************************************************************************
*Description: Sets new data into the given iterator.
*Parameters: An iterator, and pointer to new data.
*Return Value: Void.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Note: Calling the function on the end of the list leads to undefined behavior
******************************************************************************/
void DLLSet(dll_iter_t iter, void *data);

/******************************************************************************
*Description: Creates a new node with the given data, and inserts it before
*			  the given iterator
*Parameters: Data to insert, and iterator that points to the insertion location.
*Return Value: Iterator pointing to the inserted node
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: If memory allocation fails, returns the end of the list.
******************************************************************************/
dll_iter_t DLLInsert(dll_t *dll_t, dll_iter_t iter, void *data);

/******************************************************************************
*Description: Removes the node that the given iterator points to from the list.
*Parameters: Iterator to be removed from the list.
*Return Value: Iterator that points to the next node.
*Time Complexity: O(1)
*Space Complexity: O(1)
Notes: Sending the end of the list as an argument will lead to 
*	   undefined behavior.
******************************************************************************/
dll_iter_t DLLRemove(dll_iter_t iter);

/******************************************************************************
*Description: Creates a new node with the given data and inserts it as the last
*			  node of the list.
*Parameters: Pointer to the list and data to insert.
*Return Value: Iterator pointing to the inserted node.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: If memory allocation fails, returns the end of the list.
******************************************************************************/
dll_iter_t DLLPushback(dll_t *dll, void *data);

/******************************************************************************
*Description: Creates a new node with the given data and inserts it as the head
*			  of the list.
*Parameters: Pointer to the list and data to insert.
*Return Value: Iterator pointing to the inserted node.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: If memory allocation fails, returns the end of the list.
******************************************************************************/
dll_iter_t DLLPushfront(dll_t *dll, void *data);

/******************************************************************************
*Description: Removes the current last node of the list.
*Parameters: Pointer to the list.
*Return Value: The data of the removed node
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Popping from an enpty list leads to undefined behavior.
******************************************************************************/
void *DLLPopback(dll_t *dll);

/******************************************************************************
*Description: Removes the current head of the list.
*Parameters: Pointer to the list.
*Return Value: The data of the removed node
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Popping from an enpty list leads to undefined behavior.
******************************************************************************/
void *DLLPopfront(dll_t *dll);

/******************************************************************************
*Description: Advances the iterator to the next node.
*Parameters: Iterator.
*Return Value: Iterator that points to the next node.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Inputting the end of a list leads to undefined behavior.
******************************************************************************/
dll_iter_t DLLNext(const dll_iter_t iter);

/******************************************************************************
*Description: Returns the iterator to the previous node.
*Parameters: Iterator.
*Return Value: Iterator that points to the previous node.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Inputting the head of a list leads to undefined behavior.
******************************************************************************/
dll_iter_t DLLPrev(const dll_iter_t iter);

/******************************************************************************
*Description: Updates the iterator to points to the beginning of the list
			  (a viable node)
*Parameters: Pointer to a list.
*Return Value: Iterator that points to the beginning of the list.
*Time Complexity: O(1)
*Space Complexity: O(1) 
******************************************************************************/
dll_iter_t DLLBegin(const dll_t *dll);

/******************************************************************************
*Description: Updates the iterator to point to the end of the list (a none-
			  viable node)
*Parameters: Pointer to a list.
*Return Value: Iterator that points to the end of the list.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
dll_iter_t DLLEnd(const dll_t *dll);

/******************************************************************************
*Description: Checks whether 2 iterators refer to the same point in the list.
*Parameters: 2 iterators to compare.
*Return Value: 1 if they point to the same node, 0 otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int DLLIsEqual(dll_iter_t iter1, dll_iter_t iter2);

/******************************************************************************
*Description: Iterates over the given range, from iterator "from" (inclusive)
*             to iterator "to" (non-inclusive) and acts on the data.
*Parameters: 2 iterators that mark the range, an operation function,
*			 and additional parameters.
*Return Value: 0 if the action was successfull, -1 otherwise
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: Sending "to" that comes before "from" as parameters will lead to 
* 		undefined behavior.
******************************************************************************/
int DLLForEach(dll_iter_t from, dll_iter_t to, action_t act_func,void *params);

/******************************************************************************
*Description: Finds a node with specific data in the given range, from iterator
*             "from" (inclusive) to iterator "to" (non-inclusive).
*Parameters: 2 iterators that mark the range, a comparison function,
*            and parameters to compare.
*Return Value: Iterator pointing to the matching data.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: returns "to" if no match was found.
* 		sending "to" that comes before "from" as parameters will lead to 
* 		undefined behavior.
******************************************************************************/
dll_iter_t DLLFind(dll_iter_t from, dll_iter_t to, is_match_t match_func,\
				   void *params);

/******************************************************************************
*Description: Transfers the range from iterator "from" (inclusive) to 
*			  iterator "to" (non-inclusive) into the position marked by
*			  iterator "where". The original data in iterator "where" will
*			  appear after the range.
*Parameters: 2 iterators that mark the range, and an iterator that points 
*			 to the insertion position.
*Return Value: Void. 
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Sending "to" that comes before "from" as parameters will lead to 
* 		undefined behavior. if "where" is in the midst of the range, the
*       behavior is undefined.
*       In the list from which the range "from" to "to" were transferred, the
*       nodes that came before "from" are connected to the nodes after "to" 
*       (including "to").
******************************************************************************/
void DLLSplice(dll_iter_t from, dll_iter_t to, dll_iter_t where);

/******************************************************************************
*Description: Finds any node that holds the specified data in the given 
*			  range, from iterator "from" (inclusive) to iterator "to" (
*			  non-inclusive), and inserts copies of the matching nodes in to 
*			  the given dll "output".
*Parameters: 2 iterators that mark the range, a comparison function,
*            parameters to compare, and a pointer to a dll which will store
*            the output.
*Return Value: Exit status - the function will an ERROR signal (-1) if it
*			   fails to allocate the new nodes into the output, SUCCESS (0)
*              otherwise
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: The user is responsible for properly destroying the given output.
* 		sending "to" that comes before "from" as parameters leads to undefined
* 		behavior.
******************************************************************************/
int DLLMultiFind(dll_iter_t from, dll_iter_t to, is_match_t is_match_func,\
				 void *params, dll_t *output);

#endif /*__DLL_H__*/
