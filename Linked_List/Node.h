/*
 * Node.h
 *
 *  Created on: Feb 15, 2019
 *      Author: Diogo
 */

#ifndef NODE_H_
#define NODE_H_

typedef struct _node Node, *ApNode;

ApNode node_new();
void node_free(ApNode node, void (*data_free_func)(void*));

void node_set_next(ApNode node, ApNode next_node);
void node_set_previous(ApNode node, ApNode previous_node);
void node_set_data(ApNode node, void* data);

ApNode node_get_next(ApNode node);
ApNode node_get_previous(ApNode node);
void* node_get_data(ApNode node);

#endif /* NODE_H_ */
