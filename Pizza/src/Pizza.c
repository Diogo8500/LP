/*
 * Pizza.c
 *
 *  Created on: Feb 25, 2019
 *      Author: Diogo Duarte
 *  Disclaimer: Functions strings_merge, strings_msort_i, stings_msort, groups_copy
 *  			groups_merge, groups_msort_i and groups_msort were all adapted from
 *  			professor Pedro Guerreiro's algorithms on merge sort.
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include "our_ints.h"
#include "our_strings.h"

#define MAX_INGREDIENTS 10000

char* ingredients[MAX_INGREDIENTS];
int total_words;
int current_count;
char *current_ingredient;
int stock_size;
typedef struct _group Group;

void test_read_write();
void test_mergesort();
void test_groups();
void test_used_ingredients();

void print_strings_c(const char **a, int n);
void print_groups_c(const Group *a, int n);

int strings_merge(const char **a, int n, const char **b, int m, char **c);
void strings_msort_i(char **a, int n, char **b);
void strings_msort(char **a, int n);
int strings_count_while(const char **a, int n);
void test_strings_count_while(void);

Group* groups_new(int n);
void group_setname(Group *group, char *name);
void group_setamount(Group *group, int amount);
int groups_set(Group *group, char **ingredients, int n);
void group_print(const Group *a);
void groups_print(const Group *a, int n, const char *separator);
void groups_println(const Group *a, int n, const char *separator);

int group_compare(const Group *a, const Group *b);
void test_group_compare(void);
int groups_copy(const Group *a, int n, const Group *b);
int groups_merge(const Group *a, int n, const Group *b, int m, Group *c);
void groups_msort_i(Group *a, int n, Group *b);
void groups_msort(Group *a, int n);

//--------------MAIN----------------------

int main(int argc, const char **argv)
{
	int x = 'Z';
	if (argc > 1)
		x = *argv[1];
	if (x == 'A')
		test_read_write();
	else if (x == 'B')
		test_mergesort();
	else if (x == 'C')
		test_groups();
	else if (x == 'D')
		test_used_ingredients();
	else if(x == 'Z')
	{
		test_strings_count_while();
		test_group_compare();
	}
	else
		printf("Illegal choice: %s\n", argv[1]);
	return 0;
}

//----------------------------------------

struct _group {
	char *name;
	int amount;
};

void test_read_write()
{
	total_words = strings_getwords(ingredients);
	print_strings_c(ingredients, total_words);
}

void test_mergesort()
{
	total_words = strings_getwords(ingredients);
	strings_msort(ingredients, total_words);
	print_strings_c(ingredients, total_words);
}

void test_groups()
{
	total_words = strings_getwords(ingredients);
	strings_msort(ingredients, total_words);
	Group* stock = groups_new(total_words);
	stock_size = groups_set(stock, ingredients, total_words);
	print_groups_c(stock, stock_size);
}

void test_used_ingredients()
{
	total_words = strings_getwords(ingredients);
	strings_msort(ingredients, total_words);
	Group* stock = groups_new(total_words);
	stock_size = groups_set(stock, ingredients, total_words);
	groups_msort(stock, stock_size);
	print_groups_c(stock, stock_size);
}

void print_strings_c(const char **a, int n)
{
	if(n<=20)
		strings_println(a, n, "\n");
	else
	{
		strings_println(a, 15, "\n");
		strings_println(a+n-5, 5, "\n");
	}
}

void print_groups_c(const Group *a, int n)
{
	if(n<=20)
		groups_println(a, n, "\n");
	else
	{
		groups_println(a, 15, "\n");
		groups_println(a+n-5, 5, "\n");
	}
}

// Merge sorted arrays `a` and `b`, yielding `c`.
int strings_merge(const char **a, int n, const char **b, int m, char **c)
{
  int result = 0;
  int i = 0;
  int j = 0;
  while (i < n && j < m)
    if (strcmp(a[i], b[j]) <= 0)
      c[result++] = a[i++];
    else
      c[result++] = b[j++];
  result += strings_copy(a + i, n - i, c+result);
  result += strings_copy(b + j, m - j, c+result);
  return result;
}

void strings_msort_i(char **a, int n, char **b)
{
  if (n > 1)
  {
    int m = n / 2;
    strings_msort_i(a, m, b);
    strings_msort_i(a+m, n-m, b);
    strings_merge(a, m, a+m, n-m, b);
    strings_copy(b, n, a);
  }
}

// Sort array `a` using mergesort.
void strings_msort(char **a, int n)
{
  char **b = strings_new(n);
  strings_msort_i(a, n, b);
}

int strings_count_while(const char **a, int n)
{
	int result = 1;
	const char *word = a[0];
	while(result<n && !strcmp(word, a[result]))
		result++;
	return result;
}

void test_strings_count_while(void)
{
	char* a[6];
	for(int i=0; i<2; i++)
		a[i] = "aaa";
	for(int i=2; i<5; i++)
		a[i] = "bbb";
	for(int i=5; i<6; i++)
		a[i] = "ccc";
	assert(strings_count_while(a, 6) == 2);
	assert(strings_count_while(a+2, 4) == 3);
	assert(strings_count_while(a+5, 1) == 1);
}

Group* groups_new(int n)
{
	return (Group*) malloc(n*sizeof(Group));
}

void group_setname(Group *group, char *name)
{
	group->name = name;
}
void group_setamount(Group *group, int amount)
{
	group->amount = amount;
}

int groups_set(Group *group, char **ingredients, int n)
{
	int current_index = 0;
	int size = 0;
	while(current_index < n)
	{
		int amount = strings_count_while(ingredients+current_index, n-current_index);
		group_setname(group+size, ingredients[current_index]);
		group_setamount(group+size, amount);
		size++;
		current_index += amount;
	}
	return size;
}

void group_print(const Group *a)
{
	printf("%s %d", a->name, a->amount);
}

void groups_print(const Group *a, int n, const char *separator)
{
	group_print(a);
	for(int i=1; i<n; i++)
	{
		printf("%s", separator);
		group_print(a+i);
	}
}
void groups_println(const Group *a, int n, const char *separator)
{
	groups_print(a, n, separator);
	printf("\n");
}

int group_compare(const Group *a, const Group *b)
{
	if(a->amount == b->amount)
		return strcmp(a->name, b->name);
	return a->amount < b->amount ? -1 : 1;
}

void test_group_compare(void)
{
	Group* a = groups_new(3);
	group_setname(a, "Diogo");
	group_setamount(a, 3);
	group_setname(a+1, "Diogo");
	group_setamount(a+1, 4);
	group_setname(a+2, "Duarte");
	group_setamount(a+2, 3);
	assert(group_compare(a, a+1) < 0);
	assert(group_compare(a+1, a) > 0);
	assert(group_compare(a, a+2) < 0);
}

int groups_copy(const Group *a, int n, const Group *b)
{
	if (n < 0)
		n = 0;
	memmove(b, a, n * sizeof(Group));  // Note: 3rd arg is unsigned.
	return n;
}

int groups_merge(const Group *a, int n, const Group *b, int m, Group *c)
{
	int result = 0;
	int i = 0;
	int j = 0;
	while (i < n && j < m)
		if (group_compare(a+i, b+j) <= 0)
			c[result++] = a[i++];
		else
			c[result++] = b[j++];
	result += groups_copy(a + i, n - i, c+result);
	result += groups_copy(b + j, m - j, c+result);
	return result;
}

void groups_msort_i(Group *a, int n, Group *b)
{
	if (n > 1)
	{
		int m = n / 2;
		groups_msort_i(a, m, b);
		groups_msort_i(a+m, n-m, b);
		groups_merge(a, m, a+m, n-m, b);
		groups_copy(b, n, a);
	}
}
void groups_msort(Group *a, int n)
{
	Group *b = groups_new(n);
	groups_msort_i(a, n, b);
}
