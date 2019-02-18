/*
 ============================================================================
 Name        : LinkedList.c
 Author      : Diogo Duarte
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

struct _linked_list
{
	size_t size, current;
	ApNode head;
};

ApLinkedList linked_list_new(void)
{
	ApLinkedList list = (ApLinkedList) malloc(sizeof(LinkedList));
	list->size = 0;
	list->current = 0;
	list->head = NULL;
	return list;
}
void linked_list_freeShallow(ApLinkedList list)
{
	ApNode aux = list->head;
	while(aux)
	{
		node_free_shallow(aux);
		aux = node_get_next(aux);
	}
	free(list);
}
void linked_list_freeDeep(ApLinkedList list, void (*data_free_function)(void*))
{
	ApNode aux = list->head;
	while(aux)
	{
		node_free_deep(aux, data_free_function);
		aux = node_get_next(aux);
	}
	free(list);
}

void linked_list_clear(ApLinkedList list)
{
	ApNode aux = list->head;
	while(aux)
	{
		node_free_shallow(aux);
		aux = node_get_next(aux);
	}
}

size_t linked_list_size(ApLinkedList list)
{
	return list->size;
}

void linked_list_addFirst(ApLinkedList list, void* data)
{
	ApNode aux = node_new();
	node_set_next(aux, list->head);
	list->head = aux;
	list->size++;
}
void linked_list_addLast(ApLinkedList list, void* data)
{
	ApNode aux = list->head;
	for(size_t i=1; i<list->size; i++)
		aux = node_get_next(aux);
	ApNode to_add = node_new();
	node_set_next(aux, to_add);
	list->size++;
}
void linked_list_addIndex(ApLinkedList list, size_t index, void* data)
{
	if(index > list->size)
	{
		fprintf(stderr, "Index %lu is not a valid index! (@Function %s)\n", index, __func__);
		exit(-1);
	}
	if(!index)
		linked_list_addFirst(list, data);
	else
	{
		ApNode aux = list->head;
		for(size_t i=1; i<index; i++)
			aux = node_get_next(aux);
		ApNode next = node_get_next(aux);
		ApNode to_add = node_new();
		node_set_data(to_add, data);
		node_set_next(to_add, next);
		node_set_next(aux, to_add);
	}
	list->size++;
}
void linked_list_addAll(ApLinkedList list, ApLinkedList to_add);
void linked_list_addAllIndex(ApLinkedList list, size_t index, ApLinkedList to_add);
void linked_list_set(ApLinkedList list, size_t index, void* data);

void* linked_list_getFirst(ApLinkedList list);
void* linked_list_getLast(ApLinkedList list);
void* linked_list_getIndex(ApLinkedList list, size_t index);

void* linked_list_removeFirst(ApLinkedList list);
void* linked_list_removeFirstOcurrence(ApLinkedList list, void* data, void (*equals)(void*, void*));
void* linked_list_removeLast(ApLinkedList list);
void* linked_list_removeLastOcurrence(ApLinkedList list, void* data, void (*equals)(void*, void*));
void* linked_list_removeIndex(ApLinkedList list, size_t index);
void* linked_list_removeAll(ApLinkedList list, void* data, void (*equals)(void*, void*));

int linked_list_contains(ApLinkedList list, void* data, void (*equals)(void*, void*));
size_t linked_list_indexOf(ApLinkedList list, void* data, void (*equals)(void*, void*));
size_t linked_list_indexOfLast(ApLinkedList list, void* data, void (*equals)(void*, void*));

void linked_list_resetIterator(ApLinkedList list);
int linked_list_hasNext(ApLinkedList list);
void* linked_list_next(ApLinkedList list);

void linked_list_print(ApLinkedList list, void (*print_function)(void*))
{
	ApNode aux = list->head;
	while(aux)
	{
		node_print(aux, print_function);
		printf("\n");
		aux = node_get_next(aux);
	}
	printf("\n");
}
