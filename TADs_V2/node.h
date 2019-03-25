/*
 * node.h
 *
 *  Created on: Mar 22, 2019
 *      Author: Diogo
 */

#ifndef NODE_H_
#define NODE_H_

#include <stdlib.h>

typedef struct _s_node *S_NODE;
typedef struct _d_node *D_NODE;

S_NODE s_node_new();
void s_node_delete(S_NODE node, void (*destructor_f)(void*));

void s_node_set(S_NODE node, void *element);
void* s_node_get(S_NODE node);

void s_node_set_link(S_NODE node, S_NODE to_link);
S_NODE s_node_get_link(S_NODE node);

//-------------------------------------------------------------------

D_NODE d_node_new();
void d_node_delete(D_NODE node, void (*destructor_f)(void*));

void d_node_set_element(D_NODE node, void *element);
void* d_node_get_element(D_NODE node);

void d_node_set_next(D_NODE node, D_NODE to_link);
void d_node_set_previous(D_NODE node, D_NODE to_link);
D_NODE d_node_get_next(D_NODE node);
D_NODE d_node_get_previous(D_NODE node);

#endif /* NODE_H_ */
