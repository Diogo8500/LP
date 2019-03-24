/*
 ============================================================================
 Name        : List.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "my_lists.h"

void int_print(const void* a)
{
	printf("%d", *((int*)a));
}

int compare_int(const void *a, const void *b){
	int _a = *((int*)a);
	int _b = *((int*)b);
	return _a < _b ? -1 : _a == _b ? 0 : 1;
}

int main(void) {
	int sz = 3;
	int a = 5,
		b = 10,
		c = 15;

	SL_LIST l = sl_list_new();
	sl_list_add(l, 0, &a);
	sl_list_add(l, 1, &b);
	sl_list_add(l, 2, &c);

	int_print(sl_list_get(l, 0));

	sl_list_remove(l, 1);
	int_print(sl_list_get(l, 1));
	return EXIT_SUCCESS;
}
