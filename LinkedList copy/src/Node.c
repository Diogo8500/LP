/*
 * Node.c
 *
 *  Created on: Feb 18, 2019
 *      Author: Diogo
 */

#include "Node.h"
#include <stdlib.h>
#include <stdio.h>

struct _node
{
	ApNode next;
	void* data;
};

ApNode node_new(void)
{
	ApNode n = (ApNode) malloc(sizeof(Node));
	n->next = NULL;
	n->data = NULL;
	return n;
}
void* node_free_shallow(ApNode node)
{
	void* to_return = node->data;
	free(node);
	return to_return;
}
void node_free_deep(ApNode node, void (*data_free_function)(void*))
{
	data_free_function(node->data);
	free(node);
}

ApNode node_set_next(ApNode node, ApNode next)
{
	ApNode to_return = node->next;
	node->next = next;
	return to_return;
}
void* node_set_data(ApNode node, void* data)
{
	void* to_return = node->data;
	node->data = data;
	return to_return;
}

ApNode node_get_next(ApNode node)
{
	return node->next;
}
void* node_get_data(ApNode node)
{
	return node->data;
}

void node_print(ApNode node, void (*print_function)(void*))
{
	print_function(node->data);
}
