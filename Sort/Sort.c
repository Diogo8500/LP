/*
 ============================================================================
 Name        : Sort.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "my_sort.h"

void print_int(const void *a){
	printf("%d", *((int*)a));
}

void print_string(const void* string){
	printf("%s", *((char**)string));
}

void print_double(const void* a){
	printf("%.3f", *((double*)a));
}

typedef struct _myStruct{
	char* name;
	int age;
} MYSTRUCT;

void print_struct(const void *str){
	printf("%s %d", ((MYSTRUCT*)str)->name, ((MYSTRUCT*)str)->age);
}

void print_generic_array(const void* array, size_t size, size_t object_size, void (*print_f)(const void*), const char* seperator){
	if(size > 0){
		print_f(array);
		for(size_t i=1; i<size; i++){
			printf(seperator);
			print_f(array + i * object_size);
		}
		printf("\n");
	}
}

int compare_int(const void *a, const void *b){
	int _a = *((int*)a);
	int _b = *((int*)b);
	return _a < _b ? -1 : _a == _b ? 0 : 1;
}

int compare_double(const void *a, const void *b){
	double _a = *((double*)a);
	double _b = *((double*)b);
	return _a < _b ? -1 : _a == _b ? 0 : 1;
}

int compare_string(const void *a, const void *b){
	return strcmp(*((char**)a), *((char**)b));
}

int compare_struct(const void *a, const void *b){
	MYSTRUCT *_a = (MYSTRUCT*)a;
	MYSTRUCT *_b = (MYSTRUCT*)b;
	if(strcmp(_a->name, _b->name) < 0) return -1;
	if(!strcmp(_a->name, _b->name)) return compare_int(&(_a->age), &(_b->age));
	return 1;
}

int main(void) {
	size_t array_size = 1000;
	struct timeval stop, start;
	srand((unsigned) time(NULL));

	int array_int[array_size];
	double array_double[array_size];
	for(int i=0; i<array_size; i++){
		int num = rand() % 101;
		array_int[i] = num;
		array_double[i] = (double)num;
	}

	gettimeofday(&start, NULL);
	quickSort(array_int, array_size, sizeof(int), compare_int);
	gettimeofday(&stop, NULL);
	print_generic_array(array_int, array_size, sizeof(int), print_int, " ");
	printf("%.4f miliseconds\n", (stop.tv_usec - start.tv_usec)/1000.0);

	gettimeofday(&start, NULL);
	bubbleSort(array_double, array_size, sizeof(double), compare_double);
	gettimeofday(&stop, NULL);
	print_generic_array(array_double, array_size, sizeof(double), print_double, " ");
	printf("%.4f miliseconds\n", (stop.tv_usec - start.tv_usec)/1000.0);

	/*
	int array_int[] = {3, 5, 30, 9, 21, 1, 1, 10};
	quickSort(array_int, 8, sizeof(int), compare_int);
	print_generic_array(array_int, array_size, sizeof(int), print_int, " ");

	double array_double[] = {3.1, 2.0, 1.98, 10, 21.3, 21.45, 4.987, 0.12};
	quickSort(array_double, 8, sizeof(double), compare_double);
	print_generic_array(array_double, array_size, sizeof(double), print_double, " ");

	char* array_string[] = {"zebra", "burro", "duarte", "diogo", "gato", "cao", "cadele", "palavraenorme"};
	quickSort(array_string, 8, sizeof(char*), compare_string);
	print_generic_array(array_string, array_size, sizeof(char*), print_string, "\n");

	MYSTRUCT array_struct[] = {{"Diogo Duarte", 27},{"Tiago Serralheiro", 10},{"Joana Duarte", 19},{"Adriana Valentim", 26},
			{"Eugenia Valentim", 60},{"Velhota Velha", 90},{"Zebra Zebro", 45},{"Diogo Duarte", 29}};
	quickSort(array_struct, 8, sizeof(MYSTRUCT), compare_struct);
	print_generic_array(array_struct, array_size, sizeof(MYSTRUCT), print_struct, "\n");
	*/



	return EXIT_SUCCESS;
}
