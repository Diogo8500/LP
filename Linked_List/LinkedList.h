/*
 * LinkedList.h
 *
 *  Created on: Feb 15, 2019
 *      Author: Diogo
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Node.h"

typedef struct _linked_list LinkedList, *ApLinkedList;

ApLinkedList linked_list_new();
unsigned int linked_list_free(ApLinkedList list, void (*element_free_func)(void*));
unsigned int linked_list_clear(ApLinkedList list);

unsigned int linked_list_size(ApLinkedList list);

void linked_list_add_tail(ApLinkedList list, void* element);
void linked_list_add_head(ApLinkedList list, void* element);
void linked_list_add_index(ApLinkedList list, unsigned int index, void* element);
unsigned int linked_list_add_all(ApLinkedList list, const ApLinkedList to_add);
unsigned int linked_list_add_all_index(ApLinkedList list, unsigned int index, const ApLinkedList to_add);
void* linked_list_set(ApLinkedList list, unsigned int index, void* element);


ApLinkedList linked_list_shallow_copy(ApLinkedList list);
ApLinkedList linked_list_deep_copy(ApLinkedList list, void (*elem_copy_func)(void*));

void* linked_list_get_head(ApLinkedList list);
void* linked_list_get_tail(ApLinkedList list);
void* linked_list_get_index(ApLinkedList list, unsigned int index);

void* linked_list_remove_head(ApLinkedList list);
void* linked_list_remove_tail(ApLinkedList list);
void* linked_list_remove_index(ApLinkedList list, unsigned int index);

void linked_list_reset_iterator(ApLinkedList list);
int linked_list_has_next(ApLinkedList list);
void* linked_list_next(ApLinkedList list);

#endif /* LINKEDLIST_H_ */
