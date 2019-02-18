/*
 * Main.c
 *
 *  Created on: Feb 18, 2019
 *      Author: Diogo
 */

#include "LinkedList.h"
#include <stdio.h>

void print_int(void* a){

	printf("%d", *((int*)a)); //NO ENTIENDO!
}

int main(void)
{
	ApLinkedList list = linked_list_new();
	int a = 4;
	int b = 5;
	linked_list_addIndex(list, 0, &a);
	linked_list_addIndex(list, 0, &b);
	linked_list_print(list, print_int);
	return 0;
}
