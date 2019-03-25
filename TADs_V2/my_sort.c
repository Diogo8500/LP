/*
 * my_sort.c
 *
 *  Created on: Mar 19, 2019
 *      Author: Diogo
 */

#include "my_sort.h"
#include <string.h>

void swap(void *a[], size_t index_a, size_t index_b){
	char **array = (char**)a;
	char *aux = array[index_a];
	array[index_a] = array[index_b];
	array[index_b] = aux;
}

//--------------------------------------------------------------------------------------------------------------------------

void v_insertionSort(void* base[], size_t size, int (*cmp)(const void*, const void*))
{
	char **array = (char**)base;
	int j;
	char *V;
	for(size_t i = 1; i < size; i++)
	{
		V = array[i];
		j = i - 1;
		while(j >= 0 && cmp(array[j], V))
			array[j + 1] = array[j--];
		array[j + 1] = V;
	}
}

//---------------------------------------------------------------------------------------------------------------------------
void merge(void *base[], int start, int half, int end, int (*cmp)(const void*, const void*))
{
	char **array = (char**)base;
	int com1 = start, com2 = half+1, comAux = 0, size = end-start+1;
	char *vetAux[size];
	while(com1 <= half && com2 <= end)
		if(cmp(array[com1], array[com2]) < 0)
			vetAux[comAux++] = array[com1++];
		else
			vetAux[comAux++] = array[com2++];
	while(com1 <= half) //Caso ainda haja elementos na primeira metade
		vetAux[comAux++] = array[com1++];
	while(com2 <= end)  //Caso ainda haja elementos na segunda metade
		vetAux[comAux++] = array[com2++];
	for(comAux = start; comAux <= end; comAux++)   //Move os elementos de volta para o vetor original
		array[comAux] = vetAux[comAux - start];
}

void mergeSort_i(void *base[], int start, int end, int (*cmp)(const void*, const void*)){
    if (start < end) {
        int half = (end+start)/2;
        mergeSort_i(base, start, half, cmp);
        mergeSort_i(base, half+1, end, cmp);
        merge(base, start, half, end, cmp);
    }
}

void v_mergeSort(void *base[], size_t size, int (*cmp)(const void*, const void*)){
	mergeSort_i(base, 0, size-1, cmp);
}

//-------------------------------------------------------------------------------------------------------------------------------

void quickSort_i(void *base[], int began, int end, int (*cmp)(const void*, const void*))
{
	char **array = (char**)base;
	int i, j;
	char *pivo;
	i = began;
	j = end - 1;
	pivo = array[(began + end) / 2];
	while(i <= j)
	{
		while(cmp(array[i], pivo) < 0 && i < end)
			i++;
		while(cmp(array[j], pivo) > 0 && j > began)
			j--;
		if(i <= j)
			swap(array, i++, j--);
	}
	if(j > began)
		quickSort_i(array, began, j + 1, cmp);
	if(i < end)
		quickSort_i(array, i, end, cmp);
}

void v_quickSort(void *base[], size_t size, int (*cmp)(const void*, const void*))
{
	quickSort_i(base, 0, size, cmp);
}

//----------------------------------------------------------------------------------------------------------------------

void v_bubbleSort(void *base[], size_t size, int (*cmp)(const void*, const void*)){
	char **array = (char**)base;
	size_t n = size;
	while(n > 1){
		size_t newn = 0;
		for(size_t i = 1; i < n; i++){
			if(cmp(base[i], base[i + 1]) > 0){
				swap(array, i, i + 1);
				newn = i;
			}
		}
		n = newn;
	}
}
