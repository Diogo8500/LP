/*
 * Node.h
 *
 *  Created on: Feb 18, 2019
 *      Author: Diogo
 */

#ifndef NODE_H_
#define NODE_H_

typedef struct _node Node, *ApNode;

ApNode node_new(void);
void* node_free_shallow(ApNode node);
void node_free_deep(ApNode node, void (*data_free_function)(void*));

ApNode node_set_next(ApNode node, ApNode next);
void* node_set_data(ApNode node, void* data);

ApNode node_get_next(ApNode node);
void* node_get_data(ApNode node);

void node_print(ApNode node, void (*print_function)(void*));

#endif /* NODE_H_ */
