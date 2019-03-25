/*
 * my_sort.h
 *
 *  Created on: Mar 19, 2019
 *      Author: Diogo
 */

#ifndef MY_SORT_H_
#define MY_SORT_H_

#include <stdlib.h>

void v_insertionSort(void* base, size_t size, size_t object_size, int (*cmp)(const void*, const void*));

void v_mergeSort(void *base, size_t size, size_t object_size, int (*cmp)(const void*, const void*));

void v_quickSort(void *base, size_t size, size_t object_size, int (*cmp)(const void*, const void*));

void v_bubbleSort(void *base, size_t size, size_t object_size, int (*cmp)(const void*, const void*));

//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------



#endif /* MY_SORT_H_ */
