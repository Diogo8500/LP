/*
 * Main.c
 *
 *  Created on: Feb 15, 2019
 *      Author: Diogo
 */

#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
	ApLinkedList listA = linked_list_new();
	int b = 1;
	int c = 2;
	int d = 3;
	linked_list_add_tail(listA, &b);
	linked_list_add_tail(listA, &c);
	linked_list_add_tail(listA, &d);

	ApLinkedList listB = linked_list_new();
	int e = 10;
	int f = 11;
	int h = 12;
	linked_list_add_tail(listB, &e);
	linked_list_add_tail(listB, &f);
	linked_list_add_tail(listB, &h);

	/*
	linked_list_add_all(listA, listB);
	linked_list_add_all(listA, listB);
	linked_list_add_all(listA, listB);
	linked_list_add_all(listA, listB);
	linked_list_add_all(listA, listB);
	linked_list_add_all(listA, listB);
	linked_list_add_all(listA, listB);
	linked_list_add_all(listA, listB);
	linked_list_add_all(listB, listA);
	linked_list_add_all(listA, listB);
	*/

	printf("A= [ ");
	for(int i=0; i<linked_list_size(listA); i++)
		printf("%d ", *((int*) linked_list_get_index(listA, i)));
	printf("]\n");

	linked_list_add_all_index(listA, 1, listB);

	printf("A= [ ");
	for(int i=0; i<linked_list_size(listA); i++)
		printf("%d ", *((int*) linked_list_get_index(listA, i)));
	printf("]\n");

	linked_list_add_all_index(listB, 1, listA);




	linked_list_reset_iterator(listB);
	printf("B= [ ");
	while(linked_list_has_next(listB)){

		printf("%d ", *((int*) linked_list_next(listB)));

	}
	printf("]\n");

	int z = 99;
	linked_list_clear(listA);
	linked_list_add_tail(listA, &z);
	linked_list_reset_iterator(listA);
	printf("A= [ ");
	while(linked_list_has_next(listA)){

		printf("%d ", *((int*) linked_list_next(listA)));

	}
	printf("]\n");

	linked_list_add_all_index(listB, 1, listA);
	linked_list_reset_iterator(listB);
	printf("B= [ ");
	while(linked_list_has_next(listB)){

		printf("%d ", *((int*) linked_list_next(listB)));

	}
	printf("]\n");



	return 0;
}
