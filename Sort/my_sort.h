/*
 * insertionSort.h
 *
 *  Created on: Mar 19, 2019
 *      Author: Diogo
 */

#ifndef MY_SORT_H_
#define MY_SORT_H_

#include <stdlib.h>

void insertionSort(void* base, size_t size, size_t object_size, int (*cmp)(const void*, const void*));

void mergeSort(void *base, size_t size, size_t object_size, int (*cmp)(const void*, const void*));

void quickSort(void *base, size_t size, size_t object_size, int (*cmp)(const void*, const void*));

void bubbleSort(void *base, size_t size, size_t object_size, int (*cmp)(const void*, const void*));

#endif /* MY_SORT_H_ */
