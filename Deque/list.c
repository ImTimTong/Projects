/*
Filename: list.c
Author: Timothy Tong
Date: 3/24/2023
Description: Source file with functions for a list data structure that has stack, queue, and index operations and that stores elements of a generic datatype. Uses a linked list, with each node itself containing a circular queue array. Implementation for creating and destroying list; counting items in list; adding items to and removing items from the start and end of the list (as well as getting items from start and end of list); and getting and setting items at a given index in the list.

I tested my code by making sure qsort, maze and radix programs were all working. Also, I was able to successfully demo my code during office hours.
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct list 
{
	int count; //element count
	int node_count;
	int length; //max capacity of elts
	struct node *head;
};

typedef struct node
{
	void **data;
	int length;
	int count;
	int start;
	struct node *next;
	struct node *prev;
}NODE;

//Description: Creates a pointer to a circular doubly linked list with sentinel node. Initializes elt count, node count, and max length for list to 0, and sets elt count and length for sentinel node to 0 (always 0; this is for checking conditions later).
//Big-O: O(1)
LIST *createList(void)
{
	LIST *lp;
	lp = (LIST *)malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->count = 0; //element count, see list struct
	lp->length = 0; //max capacity of elts
	lp->node_count = 0;
	NODE *sentinel = (NODE *)malloc(sizeof(NODE));
	assert(sentinel != NULL);
	lp->head = sentinel;
	lp->head->count = 0;
	lp->head->length = 0;
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;
}

//Description: Frees all memory allocated for list. 
//Big-O: O(n) 
void destroyList(LIST *lp)
{
	assert(lp != NULL);
	int i;
	for (i=0; i<lp->node_count; i++)
	{
		lp->head->next = lp->head->next->next;
		free(lp->head->next->prev);
	}
	free(lp->head);
	free(lp);
}

//Description: Returns number of items in linked list.
//Big-O: O(1)
int numItems(LIST *lp)
{
	assert(lp != NULL);
	return lp->count;
}

//Description: If no nodes in list (ie just sentinel, count and length are 0) creates new node with capacity of 10. Otherwise, if first node is full, creates and adds new first node with double the prior first node's capacity (incrementing node count and list length). Adds elt to front of list. Starts adding from end of array and shifts start pointer towards beginning of array as more elts added (right to left; pointer can wrap around array in a circular manner). Increments elt count for first node and elt count for list. 
//Big-O: O(1)
void addFirst(LIST *lp, void *item)
{
	assert(lp != NULL);
	assert(item != NULL);
	if (lp->head->next->count == lp->head->next->length)
	{
		NODE *new = (NODE *)malloc(sizeof(NODE));
		assert(new != NULL);
		int length;
		if (lp->head->next->length == 0)
			length = 10;
		else
			length = lp->head->next->length * 2;
		new->data = (void *)malloc(sizeof(void *) * length);
		assert(new->data != NULL);
		new->length = length;
		new->count = 0;
		new->start = 0;
		new->next = lp->head->next;
		new->prev = lp->head;
		lp->head->next->prev = new;
		lp->head->next = new;
		lp->length += new->length;
		lp->node_count++;
	}
	lp->head->next->start = (lp->head->next->start -1) % lp->head->next->length;
	if (lp->head->next->start == -1)
		lp->head->next->start += lp->head->next->length;
	lp->head->next->data[lp->head->next->start] = item;
	lp->head->next->count++;
	lp->count++;
}

//Description: If no nodes in list (ie just sentinel, count and length are 0) creates new node with capacity of 10. Otherwise, if last node is full, creates and adds new last node with double the prior last node's capacity (incrementing node count and list length). Adds elt to end of list. Starts adding from beginning of array and shifts list end towards end of array as more elts added (left to right; pointer can wrap around array in a circular manner). Increments elt count for last node and elt count for list. 
//Big-O: O(1)
void addLast(LIST *lp, void *item)
{
	assert(lp != NULL);
	assert(item != NULL);
	if (lp->head->prev->count == lp->head->prev->length)
	{
		NODE *new = (NODE *)malloc(sizeof(NODE));
		assert(new != NULL);
		int length;
		if (lp->head->prev->length == 0)
			length = 10;
		else
			length = lp->head->prev->length * 2;
		new->data = (void *)malloc(sizeof(void *) * length);
		assert(new->data != NULL);
		new->length = length;
		new->count = 0;
		new->start = 0;
		new->prev = lp->head->prev;
		new->next = lp->head;
		lp->head->prev->next = new;
		lp->head->prev = new;
		lp->length += new->length;
		lp->node_count++;
	}
	lp->head->prev->data[(lp->head->prev->count + lp->head->prev->start) % lp->head->prev->length] = item;
	lp->head->prev->count++;
	lp->count++;
}

//Description: Breaks if list is empty. If first node is empty, remove node, decrementing list length and node count. Remove & return first item in list, incrementing start pointer from left to right in array (wraps circularly). Decrement first node elt count and list elt count.
//Big-O: O(1)
void *removeFirst(LIST *lp)
{
	assert(lp != NULL);
	assert(lp->count > 0);
	if (lp->head->next->count == 0)
	{
		NODE *temp = lp->head->next;
		lp->head->next->next->prev = lp->head;
		lp->head->next = lp->head->next->next;
		lp->length -= temp->length;
		free(temp);
		lp->node_count--;
	}
	void *data = lp->head->next->data[lp->head->next->start];
	lp->head->next->start = (lp->head->next->start + 1) % lp->head->next->length;
	lp->head->next->count--;
	lp->count--;
	return data;
}	

//Description: Breaks if list is empty. If last node is empty, remove node, decrementing list length and node count. Remove & return last item in list, moving array end from right to left in array (wraps circularly). Decrement last node elt count and list elt count.
//Big-O: O(1)
void *removeLast(LIST *lp)
{
	assert(lp != NULL);
	assert(lp->count > 0);
	if (lp->head->prev->count == 0)
	{
		NODE *temp = lp->head->prev;
		lp->head->prev->prev->next = lp->head;
		lp->head->prev = lp->head->prev->prev;
		lp->length -= temp->length;
		free(temp);
		lp->node_count--;
	}
	void *data = lp->head->prev->data[((lp->head->prev->start + --lp->head->prev->count) % lp->head->prev->length)];
	lp->count--;
	return data;
}

//Description: Returns item at given index in list. (Index must be within list length.)
//Big-O: O(n)
void *getItem(LIST *lp, int index)
{
	assert(lp != NULL);
	assert(index < lp->length);
	NODE *p;
	int idx = index;
	if (idx < lp->length/2)
	{
		p = lp->head->next;
		while (idx >= p->length)
		{
			idx -= p->length;
			p = p->next;
		}
	}
	else
	{
		p = lp->head->prev;
		idx = lp->length - 1 - idx;	
		while (idx >= p->length)
		{
			idx -= p->length;
			p = p->prev;
		}
		idx = p->length - 1 - idx;
	}
	return p->data[idx];
}

//Description: Sets (writes) an item at given index in list. (Index must be within list length.)
//Big-O: O(n)
void setItem(LIST *lp, int index, void *item)
{
	assert(lp != NULL);
	assert(item != NULL);
	assert(index < lp->length);
	NODE *p;
	int idx = index;
	if (idx < lp->length/2)
	{
		p = lp->head->next;
		while (idx >= p->length)
		{
			idx -= p->length;
			p = p->next;
		}
	}
	else
	{
		p = lp->head->prev;
		idx = lp->length - 1 - idx;	
		while (idx >= p->length)
		{
			idx -= p->length;
			p = p->prev;
		}
		idx = p->length - 1 - idx;
	}
	p->data[idx] = item;
}

//Description: Breaks if list is empty. If first node is empty, remove node, decrementing list length and node count. Return first item in list.
//Big-O: O(1)
void *getFirst(LIST *lp)
{
	assert(lp != NULL);
	assert(lp->count > 0);
	if (lp->head->next->count == 0)
	{
		NODE *temp = lp->head->next;
		lp->head->next->next->prev = lp->head;
		lp->head->next = lp->head->next->next;
		lp->length -= temp->length;
		free(temp);
		lp->node_count--;
	}
	void *data = lp->head->next->data[lp->head->next->start];
	return data;
}	

//Description: Breaks if list is empty. If last node is empty, remove node, decrementing list length and node count. Return last item in list.
//Big-O: O(1)
void *getLast(LIST *lp)
{
	assert(lp != NULL);
	assert(lp->count > 0);
	if (lp->head->prev->count == 0)
	{
		NODE *temp = lp->head->prev;
		lp->head->prev->prev->next = lp->head;
		lp->head->prev = lp->head->prev->prev;
		lp->length -= temp->length;
		free(temp);
		lp->node_count--;
	}
	void *data = lp->head->prev->data[((lp->head->prev->start + lp->head->prev->count - 1) % lp->head->prev->length)];
	return data;
}
