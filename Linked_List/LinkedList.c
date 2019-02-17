/*
 * LinkedList.c
 *
 *  Created on: Feb 15, 2019
 *      Author: Diogo
 */

#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct _linked_list {
	unsigned int size, current;
	ApNode head, tail;
};

ApNode private_get_node(ApLinkedList list, unsigned int index){
	ApNode aux;
	if(index < list->size / 2){
		aux = list->head;
		for(int i=0; i<index; i++)
			aux = node_get_next(aux);
	}
	else{
		aux = list->tail;
		for(int i=list->size-1; i>index; i--)
			aux = node_get_previous(aux);
	}
	return aux;
}

ApLinkedList linked_list_new(){
	ApLinkedList l = (ApLinkedList) malloc(sizeof(LinkedList));
	if(l == NULL){
		fprintf(stderr, "Couldn't allocate memory for this list!\n");
		return NULL;
	}
	l->size = 0;
	l->current = 0;
	return l;
}

unsigned int linked_list_free(ApLinkedList list, void (*element_free_func)(void*)){
	ApNode aux = list->head;
	unsigned int num_elem_freed = 0;
	while(aux){
		ApNode next = node_get_next(aux);
		node_free(aux, element_free_func);
		aux = next;
		num_elem_freed++;
	}
	free(list);
	return num_elem_freed;
}

unsigned int linked_list_clear(ApLinkedList list){
	ApNode aux = list->head;
	unsigned int num_elem_cleared = 0;
	while(aux){
		ApNode next = node_get_next(aux);
		free(aux);
		aux = next;
		num_elem_cleared++;
	}
	list->size = 0;
	return num_elem_cleared;
}

unsigned int linked_list_size(ApLinkedList list){
	return list->size;
}

void linked_list_add_tail(ApLinkedList list, void* element){
	ApNode to_add = node_new();
	node_set_data(to_add, element);
	if(!list->size){
		list->head = to_add;
	}else{
		node_set_next(list->tail, to_add);
		node_set_previous(to_add, list->tail);
	}
	list->tail = to_add;
	list->size++;
}
void linked_list_add_head(ApLinkedList list, void* element){
	ApNode to_add = node_new();
	node_set_data(to_add, element);
	if(!list->size){
		list->tail = to_add;
	}else{
		node_set_next(to_add, list->head);
		node_set_previous(list->head, to_add);
	}
	list->head = to_add;
	list->size++;
}

void linked_list_add_index(ApLinkedList list, unsigned int index, void* element){
	if(index > list->size){
		fprintf(stderr, "Index is out of bounds!\n");
		exit(-1);
	}
	if(!index)
		linked_list_add_head(list, element);
	else if(index == list->size)
		linked_list_add_tail(list, element);
	else{
		ApNode to_add = node_new();
		node_set_data(to_add, element);
		ApNode aux = private_get_node(list, index);
		ApNode previous = node_get_previous(aux);
		node_set_next(previous, to_add);
		node_set_previous(to_add, previous);
		node_set_next(to_add, aux);
		node_set_previous(aux, to_add);
		list->size++;
	}
}

unsigned int linked_list_add_all(ApLinkedList list, const ApLinkedList to_add){
	unsigned int count = 0;
	ApNode aux = to_add->head;
	while(aux){
		linked_list_add_tail(list, node_get_data(aux));
		count++;
		aux = node_get_next(aux);
	}
	return count;
}

unsigned int linked_list_add_all_index(ApLinkedList list, unsigned int index, const ApLinkedList to_add){
	unsigned int count = 0;
	ApNode aux = to_add->head;
	while(aux){
		linked_list_add_index(list, index+count,  node_get_data(aux));
		count++;
		aux = node_get_next(aux);
	}
	return count;
}

void* linked_list_set(ApLinkedList list, unsigned int index, void* element);

ApLinkedList linked_list_shallow_copy(ApLinkedList list);
ApLinkedList linked_list_deep_copy(ApLinkedList list, void (*elem_copy_func)(void*));

void* linked_list_get_head(ApLinkedList list){
	return node_get_data(list->head);
}

void* linked_list_get_tail(ApLinkedList list){
	return node_get_data(list->tail);
}

void* linked_list_get_index(ApLinkedList list, unsigned int index){
	if(index >= list->size){
		fprintf(stderr, "Index out of bounds!\n");
		exit(-1);
	}
	return node_get_data(private_get_node(list, index));
}

void* linked_list_remove_head(ApLinkedList list){
	void* to_return = linked_list_get_head(list);
	ApNode next = node_get_next(list->head);
	node_set_previous(next, NULL);
	free(list->head);
	list->head = next;
	list->size--;
	return to_return;
}

void* linked_list_remove_tail(ApLinkedList list){
	void* to_return = linked_list_get_tail(list);
	ApNode previous = node_get_previous(list->tail);
	node_set_next(previous, NULL);
	free(list->tail);
	list->tail = previous;
	list->size--;
	return to_return;
}

void* linked_list_remove_index(ApLinkedList list, unsigned int index){
	ApNode to_remove = private_get_node(list, index);
	void* to_return = node_get_data(to_remove);
	node_set_next(node_get_previous(to_remove), node_get_next(to_remove));
	node_set_previous(node_get_next(to_remove), node_get_previous(to_remove));
	free(to_remove);
	list->size--;
	return to_return;
}

void linked_list_reset_iterator(ApLinkedList list){
	list->current = 0;
}
int linked_list_has_next(ApLinkedList list){
	return list->current < list->size;
}
void* linked_list_next(ApLinkedList list){
	return linked_list_get_index(list, list->current++);
}

//------------------------------TESTS-----------------------------------

void unit_test_new(){


}


