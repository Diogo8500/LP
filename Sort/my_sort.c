/*
 * my_sort.c
 *
 *  Created on: Mar 19, 2019
 *      Author: Diogo
 */

#include "my_sort.h"
#include <string.h>

void swap(void *a, size_t index_a, size_t index_b, size_t object_size){
	void *aux = malloc(object_size);
	memmove(aux, a + index_a * object_size, object_size);
	memmove(a + index_a * object_size, a + index_b * object_size, object_size);
	memmove(a + index_b * object_size, aux, object_size);
	free(aux);
}

//--------------------------------------------------------------------------------------------------------------------------

void insertionSort(void* base, size_t size, size_t object_size, int (*cmp)(const void*, const void*))
{
	int j;
	void* V = malloc(object_size);
	for(size_t i=1; i < size; i++){
		memmove(V, base + i * object_size, object_size);
		j = i - 1;
		while(j >= 0 && cmp(base + j * object_size, V) > 0){
			memmove(base + (j + 1) * object_size, base + j * object_size, object_size);
			j--;
		}
		memmove(base + (j + 1) * object_size, V, object_size);
	}
	free(V);
}

//---------------------------------------------------------------------------------------------------------------------------
void merge(void *base, int start, int half, int end, size_t object_size, int (*cmp)(const void*, const void*))
{
    int com1 = start, com2 = half+1, comAux = 0, size = end-start+1;
    void *vetAux = malloc(size * object_size);
    while(com1 <= half && com2 <= end){
    	if(cmp(base + com1 * object_size, base + com2 * object_size) < 0) {
    		memmove(vetAux + comAux * object_size, base + com1 * object_size, object_size);
            com1++;
        } else {
        	memmove(vetAux + comAux * object_size, base + com2 * object_size, object_size);
            com2++;
        }
        comAux++;
    }
    while(com1 <= half){  //Caso ainda haja elementos na primeira metade
    	memmove(vetAux + comAux * object_size, base + com1 * object_size, object_size);
        comAux++;
        com1++;
    }
    while(com2 <= end) {   //Caso ainda haja elementos na segunda metade
    	memmove(vetAux + comAux * object_size, base + com2 * object_size, object_size);
        comAux++;
        com2++;
    }
    for(comAux = start; comAux <= end; comAux++)   //Move os elementos de volta para o vetor original
    	memmove(base + comAux * object_size, vetAux + (comAux-start) * object_size, object_size);
    free(vetAux);
}

void mergeSort_i(void *base, int start, int end, size_t object_size, int (*cmp)(const void*, const void*)){
    if (start < end) {
        int half = (end+start)/2;
        mergeSort_i(base, start, half, object_size, cmp);
        mergeSort_i(base, half+1, end, object_size, cmp);
        merge(base, start, half, end, object_size, cmp);
    }
}

void mergeSort(void *base, size_t size, size_t object_size, int (*cmp)(const void*, const void*)){
	mergeSort_i(base, 0, size-1, object_size, cmp);
}

//-------------------------------------------------------------------------------------------------------------------------------

void quickSort_i(void *base, int began, int end, size_t object_size, int (*cmp)(const void*, const void*))
{
	int i, j;
	void *pivo = malloc(object_size);
	i = began;
	j = end-1;
	memmove(pivo, base + ((began + end) / 2) * object_size, object_size);
	while(i <= j)
	{
		while(cmp(base + i * object_size, pivo) < 0 && i < end)
			i++;
		while(cmp(base + j * object_size, pivo) > 0 && j > began)
			j--;
		if(i <= j)
		{
			swap(base, i, j, object_size);
			i++;
			j--;
		}
	}
	if(j > began)
		quickSort_i(base, began, j+1, object_size, cmp);
	if(i < end)
		quickSort_i(base, i, end, object_size, cmp);
	free(pivo);
}

void quickSort(void *base, size_t size, size_t object_size, int (*cmp)(const void*, const void*))
{
	quickSort_i(base, 0, size, object_size, cmp);
}

//----------------------------------------------------------------------------------------------------------------------

void bubbleSort(void *base, size_t size, size_t object_size, int (*cmp)(const void*, const void*)){
	size_t n = size;
	while(n > 1){
		size_t newn = 0;
		for(size_t i = 1; i < n; i++){
			if(cmp(base + i * object_size, base + (i + 1) * object_size) > 0){
				swap(base, i, i+1, object_size);
				newn = i;
			}
		}
		n = newn;
	}
}
