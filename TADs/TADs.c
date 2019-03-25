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
	int _a = **((int**)a);
	int _b = **((int**)b);
	return _a < _b ? -1 : _a == _b ? 0 : 1;
}

int main(void) {
	//int sz = 3;
	int a = 5,
		b = 15,
		c = 10,
		d = 3;

	SL_LIST l = sl_list_new();
	sl_list_add(l, 0, &a);
	sl_list_add(l, 1, &b);
	sl_list_add(l, 2, &c);
	sl_list_add(l, 3, &d);
	sl_list_addTail(l, &d);
	sl_list_addTail(l, &d);
	sl_list_addTail(l, &c);
	sl_list_addTail(l, &d);
	sl_list_addTail(l, &a);

	int_print(sl_list_get(l, 0));
	printf(" ");
	int_print(sl_list_get(l, 1));
	printf(" ");
	int_print(sl_list_get(l, 2));
	printf(" ");
	int_print(sl_list_get(l, 3));
	printf("\n");

	sl_list_sort(l, compare_int);

	int_print(sl_list_get(l, 0));
	printf(" ");
	int_print(sl_list_get(l, 1));
	printf(" ");
	int_print(sl_list_get(l, 2));
	printf(" ");
	int_print(sl_list_get(l, 3));
	printf("\n");
	return EXIT_SUCCESS;
}
