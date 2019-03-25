/*
 * my_lists.c
 *
 *  Created on: Mar 22, 2019
 *      Author: Diogo
 */

#include <stdlib.h>
#include <string.h>
#include "my_lists.h"
#include "node.h"
#include "my_sort.h"

//====================================================================================================================================
/*
 * Function implementations for vector lists
 */

const size_t DEFAULT_INCREASE_STEP = 10;

struct _vector_list {
	size_t size, max_size;
	char **base;
}V_LIST_SIZE;

struct _vector_it {
	V_LIST list;
	int current;
}V_IT_SIZE;

// START Private functions------------------------

//Shifts all elements in the direction of 'direction' one index (index inclusive)
//-1 = left
//1 = right
void shift_elems(V_LIST list, size_t index, int direction)
{
	if(index != list->size){
		if(direction > 0)
			memmove(list->base + index + 1, list->base + index, (list->size - index) * sizeof(char*)); //PRE: list->size < list->max_size
		else
			memmove(list->base + index - 1, list->base + index, (list->size - index) * sizeof(char*)); //PRE: index != 0
	}
}
// END Private functions------------------------

V_LIST v_list_new(size_t init_size)
{
	V_LIST l = (V_LIST) malloc(sizeof(V_LIST_SIZE));
	if(!l) return NULL;
	l->base = (char**) malloc(init_size * sizeof(char*));
	if(!l->base) return NULL;
	l->size = 0;
	l->max_size = init_size;
	return l;
}
void v_list_delete(V_LIST list, void (*destructor)(const void*))
{
	if(list){
		if(destructor)
			for(size_t i = 0; i < list->size; i++)
				destructor(list->base[i]);
		free(list->base);
		free(list);
	}
}

int v_list_assureSize(V_LIST list, size_t size)
{
	if(size <= list->max_size)
		return 0;
	char **new_base = (char**) malloc(size * sizeof(char*));
	if(!new_base)
		return -1;
	memmove(new_base, list->base, list->size * sizeof(char*));
	free(list->base);
	list->base = new_base;
	return 1;
}

int v_list_addTail(V_LIST list, void *object)
{
	return v_list_add(list, list->size, object);
}
int v_list_addHead(V_LIST list, void *object)
{
	return v_list_add(list, 0, object);
}
int v_list_add(V_LIST list, size_t index, void *object)
{
	if(index > list->size) //Checks if index is valid
		return 0;
	if(v_list_assureSize(list, list->size + 1) == -1) //Makes sure there are enough space to add object
		return -1;
	shift_elems(list, index, 1);
	list->base[index] = (char*)object;
	list->size++;
	return 1;
}

void* v_list_getTail(V_LIST list)
{
	return v_list_get(list, list->size - 1);
}
void* v_list_getHead(V_LIST list)
{
	return v_list_get(list, 0);
}
void* v_list_get(V_LIST list, size_t index)
{
	if(index >= list->size)
		return NULL;
	return list->base[index];
}

void* v_list_removeTail(V_LIST list)
{
	return v_list_remove(list, list->size - 1);
}
void* v_list_removeHead(V_LIST list)
{
	return v_list_remove(list, 0);
}
void* v_list_remove(V_LIST list, size_t index)
{
	if(index >= list->size)
		return NULL;
	void *to_return = (void*)list->base[index];
	shift_elems(list, index + 1, -1);
	list->size--;
	return to_return;
}

void v_list_sort(V_LIST list, int (*cmp)(const void*, const void*))
{
	v_mergeSort(list->base, list->size, sizeof(char*), cmp);
}
size_t v_list_size(V_LIST list)
{
	return list->size;
}
int v_list_isEmpty(V_LIST list)
{
	return !list->size;
}

V_IT v_list_it_new(V_LIST list)
{
	V_IT it = (V_IT) malloc(sizeof(V_IT_SIZE));
		if(!it) return NULL;
	it->list = list;
	it->current = -1;
	return it;
}
void v_it_delete(V_IT list_it)
{
	free(list_it);
}
void v_it_reset(V_IT list_it)
{
	list_it->current = 0;
}
int v_it_hasNext(V_IT list_it)
{
	if(list_it->current == -1) return 0;
	return list_it->current < list_it->list->size;
}
void* v_it_next(V_IT list_it)
{
	return v_list_get(list_it->list, list_it->current++);
}

/*
 * End of function implementations for vector lists
 */
//====================================================================================================================================

//====================================================================================================================================
/*
 * Function implementations for SIMPLY LINKED LISTS
 */
struct _simply_linked_list {
	S_NODE head;
	size_t size;
} SL_LIST_SIZE;

struct _simply_linked_it {
	SL_LIST list;
	int current;
} SL_IT_SIZE;

SL_LIST sl_list_new()
{
	SL_LIST l = (SL_LIST) malloc(sizeof(SL_LIST_SIZE));
		if(!l) return NULL;
	l->head = NULL;
	l->size = 0;
	return l;
}
void sl_list_delete(SL_LIST list, void (*destructor)(void*))
{
	S_NODE current = list->head;
	while(current)
	{
		S_NODE aux = s_node_get_link(current);
		s_node_delete(current, destructor);
		current = aux;
	}
	free(list);
}

int sl_list_addTail(SL_LIST list, void *element)
{
	return sl_list_add(list, list->size, element);
}
int sl_list_addHead(SL_LIST list, void *element)
{
	return sl_list_add(list, 0, element);
}
int sl_list_add(SL_LIST list, size_t index, void *element)
{
	if(index > list->size) return 0;
	S_NODE to_add = s_node_new();
	if(!to_add) return -1;
	s_node_set(to_add, element);
	if(!index)
	{
		s_node_set_link(to_add, list->head);
		list->head = to_add;
	}
	else
	{
		S_NODE current = list->head;
		while(--index)
			current = s_node_get_link(current);
		S_NODE next = s_node_get_link(current);
		s_node_set_link(to_add, next);
		s_node_set_link(current, to_add);
	}
	list->size++;
	return 1;
}

void* sl_list_getTail(SL_LIST list)
{
	return sl_list_get(list, list->size - 1);
}
void* sl_list_getHead(SL_LIST list)
{
	return sl_list_get(list, 0);
}
void* sl_list_get(SL_LIST list, size_t index)
{
	if(index >= list->size) return NULL;
	S_NODE current = list->head;
	while(index--)
		current = s_node_get_link(current);
	return s_node_get(current);
}

void* sl_list_removeTail(SL_LIST list)
{
	return sl_list_remove(list, list->size - 1);
}
void* sl_list_removeHead(SL_LIST list)
{
	return sl_list_remove(list, 0);
}
void* sl_list_remove(SL_LIST list, size_t index)
{
	if(index >= list->size) return NULL;
	S_NODE current = list->head;
	void* to_return;
	if(!index)
	{
		to_return = s_node_get(current);
		list->head = s_node_get_link(current);
	}
	else
	{
		while(--index)
			current = s_node_get_link(current);
		S_NODE to_remove = s_node_get_link(current);
		to_return = s_node_get(to_remove);
		s_node_set_link(current, s_node_get_link(to_remove));
		free(to_remove);
	}
	list->size--;
	return to_return;
}

void sl_list_sort(SL_LIST list, int (*cmp)(const void*, const void*))
{
	char* array[list->size];
	SL_IT it = sl_list_it_new(list);
	sl_it_reset(it);
	size_t i=0;
	while(sl_it_hasNext(it))
		array[i++] = (char*)sl_it_next(it);
	v_mergeSort(array, i, sizeof(char*), cmp);
	sl_it_delete(it);
	i=0;
	S_NODE aux = list->head;
	while(aux)
	{
		s_node_set(aux, array[i++]);
		aux = s_node_get_link(aux);
	}
}
size_t sl_list_size(SL_LIST list)
{
	return list->size;
}
int sl_list_isEmpty(SL_LIST list)
{
	return !list->size;
}

SL_IT sl_list_it_new(SL_LIST list)
{
	SL_IT it = (SL_IT) malloc(sizeof(SL_IT_SIZE));
		if(!it) return NULL;
	it->list = list;
	it->current = -1;
	return it;
}
void sl_it_delete(SL_IT list_it)
{
	free(list_it);
}
void sl_it_reset(SL_IT list_it)
{
	list_it->current = 0;
}
int sl_it_hasNext(SL_IT list_it)
{
	if(list_it->current == -1) return 0;
	return list_it->current < list_it->list->size;
}
void* sl_it_next(SL_IT list_it)
{
	return sl_list_get(list_it->list, list_it->current++);
}
