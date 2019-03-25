/*
 * my_lists.h
 *
 *  Created on: Mar 22, 2019
 *      Author: Diogo
 *
 *  Due to the nature of data types in C, its possible to store different types of elements in
 *  a list as long has their sizes (in bytes) match. This obviously could have unexpected
 *  results later.
 */

#ifndef MY_LISTS_H_
#define MY_LISTS_H_

#include <stdlib.h>

//====================================================================================================================================
/*
 * Function declarations for vector lists
 */

typedef struct _vector_list *V_LIST;
typedef struct _vector_it *V_IT;

V_LIST v_list_new(size_t init_size);
void v_list_delete(V_LIST list, void (*destructor)(const void*));

int v_list_assureSize(V_LIST list, size_t size);

int v_list_addTail(V_LIST list, void *object);
int v_list_addHead(V_LIST list, void *object);
int v_list_add(V_LIST list, size_t index, void *object);

void* v_list_getTail(V_LIST list);
void* v_list_getHead(V_LIST list);
void* v_list_get(V_LIST list, size_t index);

void* v_list_removeTail(V_LIST list);
void* v_list_removeHead(V_LIST list);
void* v_list_remove(V_LIST list, size_t index);

void v_list_sort(V_LIST list, int (*cmp)(const void*, const void*));
size_t v_list_size(V_LIST list);
int v_list_isEmpty(V_LIST list);

V_IT v_list_it_new(V_LIST list);
void v_it_delete(V_IT list_it);
void v_it_reset(V_IT list_it);
int v_it_hasNext(V_IT list_it);
void* v_it_next(V_IT list_it);


/*
 * End of function declarations for vector lists
 */
//====================================================================================================================================

//====================================================================================================================================
/*
 * Function declarations for SIMPLY LINKED lists
 */

typedef struct _simply_linked_list *SL_LIST;
typedef struct _simply_linked_it *SL_IT;

SL_LIST sl_list_new();
void sl_list_delete(SL_LIST list, void (*destructor)(void*));

int sl_list_addTail(SL_LIST list, void *element);
int sl_list_addHead(SL_LIST list, void *element);
int sl_list_add(SL_LIST list, size_t index, void *element);

void* sl_list_getTail(SL_LIST list);
void* sl_list_getHead(SL_LIST list);
void* sl_list_get(SL_LIST list, size_t index);

void* sl_list_removeTail(SL_LIST list);
void* sl_list_removeHead(SL_LIST list);
void* sl_list_remove(SL_LIST list, size_t index);

void sl_list_sort(SL_LIST list, int (*cmp)(const void*, const void*));
size_t sl_list_size(SL_LIST list);
int sl_list_isEmpty(SL_LIST list);

SL_IT sl_list_it_new(SL_LIST list);
void sl_it_delete(SL_IT list_it);
void sl_it_reset(SL_IT list_it);
int sl_it_hasNext(SL_IT list_it);
void* sl_it_next(SL_IT list_it);

/*
 * End of function declarations for SIMPLY LINKED lists
 */
//====================================================================================================================================

//====================================================================================================================================
/*
 * Function declarations for DOUBLE LINKED lists
 */

typedef struct _double_linked_list *DL_LIST;
typedef struct _double_linked_it *DL_IT;

DL_LIST dl_list_new();
void dl_list_delete(DL_LIST list, void (*destructor)(const void*));

/*
 * End of function declarations for DOUBLE LINKED lists
 */

#endif /* MY_LISTS_H_ */
