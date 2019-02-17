/*
 * Node.c
 *
 *  Created on: Feb 15, 2019
 *      Author: Diogo
 */

#include <stdlib.h>
#include <stdio.h>
#include "Node.h"

struct _node{
	ApNode previous;
	ApNode next;
	void* data;
};

ApNode node_new(){
	ApNode n = (ApNode) malloc(sizeof(Node));
	if(n == NULL)
		fprintf(stderr, "Error allocating memory for this node!\n");
	n->next = NULL;
	n->previous = NULL;
	n->data = NULL;
	return n;
}

void node_free(ApNode node, void (*data_free_func)(void*)){
	data_free_func(node->data);
	free(node);
}

void node_set_next(ApNode node, ApNode next_node){
	node->next = next_node;
}

void node_set_previous(ApNode node, ApNode previous_node){
	node->previous = previous_node;
}

void node_set_data(ApNode node, void* data){
	node->data = data;
}

ApNode node_get_next(ApNode node){
	return node->next;
}

ApNode node_get_previous(ApNode node){
	return node->previous;
}

void* node_get_data(ApNode node){
	return node->data;
}
