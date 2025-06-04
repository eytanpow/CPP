#include <stdlib.h> /* malloc size_t */
#include <assert.h> /*assert */
#include "dll.h"

#define NULLASSERT(x) (assert(NULL != x))
#define TRUE 1
#define FALSE 0

enum
{
	SUCCESS = 0,
	FAILURE = -1
};

static int Counter(void *data, void *count);

struct node
{
	void *data;
	struct node *next;
	struct node *prev;
};

struct dll
{
	struct node head;
	struct node tail;
};

dll_t *DLLCreate(void)
{
	dll_t *dll = NULL;

	dll = (dll_t *)malloc(sizeof(dll_t));
	if (NULL == dll)
	{
		return NULL;
	}

	dll->head.next = &dll->tail;
	dll->head.prev = NULL;
	dll->head.data = NULL;

	dll->tail.next = NULL;
	dll->tail.prev = &dll->head;
	dll->tail.data = NULL;

	return dll;
}

void DLLDestroy(dll_t *dll)
{
	NULLASSERT(dll);

	while (!DLLIsEmpty(dll))
	{
		DLLRemove(dll->head.next);
	}

	free(dll);
}

int DLLIsEmpty(const dll_t *dll)
{
	return (DLLIsEqual(DLLEnd(dll), DLLBegin(dll)));
}

size_t DLLSize(const dll_t *dll)
{
	size_t counter = 0;

	NULLASSERT(dll);

	DLLForEach(DLLBegin(dll), DLLEnd(dll), Counter, &counter);

	return counter;
}

void *DLLGet(const dll_iter_t iter)
{
	NULLASSERT(iter);

	return (iter->data);
}

void DLLSet(dll_iter_t iter, void *data)
{
	NULLASSERT(iter);

	iter->data = data;
}

dll_iter_t DLLInsert(dll_t *dll, dll_iter_t iter, void *data)
{
	dll_iter_t ins = NULL;
	(void)dll;
	NULLASSERT(iter);

	ins = (dll_iter_t)malloc(sizeof(struct node));
	if (NULL == ins)
	{
		return (DLLEnd(dll));
	}

	ins->data = data;

	/*set prev and next of new NODE */
	ins->prev = iter->prev;
	ins->next = iter;

	/*insert new node to list by arrange next and prev */
	ins->prev->next = ins;
	iter->prev = ins;

	return ins;
}

dll_iter_t DLLRemove(dll_iter_t iter)
{
	dll_iter_t temp = NULL;

	NULLASSERT(iter);
	NULLASSERT(iter->next);

	temp = iter->next;

	iter->prev->next = iter->next;
	iter->next->prev = iter->prev;

	free(iter);

	return (temp);
}

dll_iter_t DLLPushback(dll_t *dll, void *data)
{
	NULLASSERT(dll);

	return DLLInsert(dll, &dll->tail, data);
}

dll_iter_t DLLPushfront(dll_t *dll, void *data)
{
	NULLASSERT(dll);

	return DLLInsert(dll, dll->head.next, data);
}

void *DLLPopback(dll_t *dll)
{
	void *ret = dll->tail.prev->data;

	NULLASSERT(dll);

	DLLRemove(dll->tail.prev);

	return ret;
}

void *DLLPopfront(dll_t *dll)
{
	void *ret = dll->head.next->data;

	assert(!DLLIsEmpty(dll));

	DLLRemove(dll->head.next);

	return (ret);
}

dll_iter_t DLLNext(const dll_iter_t iter)
{
	NULLASSERT(iter->next);
	return (iter->next);
}

dll_iter_t DLLPrev(const dll_iter_t iter)
{
	NULLASSERT(iter->prev->prev);
	return (iter->prev);
}

dll_iter_t DLLBegin(const dll_t *dll)
{
	NULLASSERT(dll);
	return (dll->head.next);
}

dll_iter_t DLLEnd(const dll_t *dll)
{
	NULLASSERT(dll);
	return ((dll_iter_t)&dll->tail);
}

int DLLIsEqual(dll_iter_t iter1, dll_iter_t iter2)
{
	NULLASSERT(iter1);
	NULLASSERT(iter2);
	return (iter1 == iter2);
}

int DLLForEach(dll_iter_t from, dll_iter_t to, action_t act_func, void *params)
{
	int status = SUCCESS;

	NULLASSERT(from);
	NULLASSERT(to);

	while (to != from && (SUCCESS == status))
	{
		status = act_func(DLLGet(from), params);

		from = DLLNext(from);
	}

	return (status);
}

dll_iter_t DLLFind(dll_iter_t from, dll_iter_t to, is_match_t match_func,
				   void *params)
{
	NULLASSERT(from);
	NULLASSERT(to);

	while (to != from)
	{
		if (TRUE == match_func(DLLGet(from), params))
		{
			return (from);
		}
		from = DLLNext(from);
	}

	return (to);
}

void DLLSplice(dll_iter_t from, dll_iter_t to, dll_iter_t where)
{
	dll_iter_t temp = NULL;

	NULLASSERT(from);
	NULLASSERT(to);
	NULLASSERT(where);

	if (DLLIsEqual(to, from))
	{
		return;
	}
	temp = to->prev;

	where->prev->next = from;
	from->prev->next = to;
	to->prev->next = where;

	to->prev = from->prev;
	from->prev = where->prev;
	where->prev = temp;
}

int DLLMultiFind(dll_iter_t from, dll_iter_t to, is_match_t match_func,
				 void *params, dll_t *output)
{
	dll_iter_t found = NULL;
	dll_iter_t test = NULL;

	NULLASSERT(from);
	NULLASSERT(to);
	NULLASSERT(output);

	found = from;
	while (FALSE == DLLIsEqual(found, to))
	{
		if (to != (found = DLLFind(found, to, match_func, params)))
		{

			test = DLLPushback(output, params);
			if (NULL == test)
			{
				return (FAILURE);
			}
			found = DLLNext(found);
		}
	}
	return (SUCCESS);
}

static int Counter(void *data, void *count)
{
	(void)data;

	++(*(size_t *)count);

	return SUCCESS;
}
