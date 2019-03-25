/*
 * node.c
 *
 *  Created on: Mar 22, 2019
 *      Author: Diogo
 */

#include "node.h"
#include <string.h>

struct _s_node {
	S_NODE linked_node;
	char *element;
} S_NODE_SIZE;

struct _d_node {
	D_NODE next, previous;
	char *element;
} D_NODE_SIZE;

S_NODE s_node_new()
{
	S_NODE to_return = (S_NODE) malloc(sizeof(S_NODE_SIZE));
	to_return->element = NULL;
	to_return->linked_node = NULL;
	return to_return;
}
void s_node_delete(S_NODE node, void (*destructor_f)(void*))
{
	destructor_f(node->element);
	free(node);
}

void s_node_set(S_NODE node, void *element)
{
	node->element = element;
}
void* s_node_get(S_NODE node)
{
	return node->element;
}

void s_node_set_link(S_NODE node, S_NODE to_link)
{
	node->linked_node = to_link;
}
S_NODE s_node_get_link(S_NODE node)
{
	return node->linked_node;
}

//---------------------------------------------------------------------

D_NODE d_node_new()
{
	D_NODE to_return = (D_NODE) malloc(sizeof(D_NODE_SIZE));
	to_return->next = NULL;
	to_return->previous = NULL;
	to_return->element = NULL;
	return to_return;
}
void d_node_delete(D_NODE node, void (*destructor_f)(void*))
{
	destructor_f(node->element);
	free(node);
}

void d_node_set_element(D_NODE node, void *element)
{
	node->element = element;
}
void* d_node_get_element(D_NODE node)
{
	return node->element;
}

void d_node_set_next(D_NODE node, D_NODE to_link)
{
	node->next = to_link;
}
void d_node_set_previous(D_NODE node, D_NODE to_link)
{
	node->previous = to_link;
}
D_NODE d_node_get_next(D_NODE node)
{
	return node->next;
}
D_NODE d_node_get_previous(D_NODE node)
{
	return node->previous;
}
