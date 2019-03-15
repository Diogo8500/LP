/*
 * LinkedList.h
 *
 *  Created on: Feb 18, 2019
 *      Author: Diogo
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Node.h"
#include <stdlib.h>

typedef struct _linked_list LinkedList, *ApLinkedList;

ApLinkedList linked_list_new(void);
void linked_list_freeShallow(ApLinkedList list);
void linked_list_freeDeep(ApLinkedList list, void (*data_free_function)(void*));

void linked_list_clear(ApLinkedList list);

size_t linked_list_size(ApLinkedList list);

void linked_list_addFirst(ApLinkedList list, void* data);
void linked_list_addLast(ApLinkedList list, void* data);
void linked_list_addIndex(ApLinkedList list, size_t index, void* data);
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

void linked_list_print(ApLinkedList list, void (*print_function)(void*));

#endif /* LINKEDLIST_H_ */
