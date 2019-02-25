//
//  our_ints.h
//
//  Created by Pedro Guerreiro on 01/11/2018.
//  Copyright © 2018 Pedro Guerreiro. All rights reserved.
//

#ifndef our_ints_h
#define our_ints_h

void ints_println_basic(const int *a, int n);
void ints_println_special(const int *a, int n);
void ints_fprint(FILE *f, const int *a, int n, const char *separator);
void ints_fprintln(FILE *f, const int *a, int n, const char *separator);
void ints_print(const int *a, int n, const char *separator);
void ints_println(const int *a, int n, const char *separator);

int ints_get(int *a);
int ints_get_until(int terminator, int *a);
int ints_get_some(int *a, int n);

int *ints_new(int n);

int ints_fill(int x, int n, int *a);
int ints_count(const int *a, int n, int x);
int ints_sum(const int *a, int n);
int ints_mean(const int *a, int n);
int ints_remove(const int *a, int n, int x, int *b);
int ints_max(const int *a, int n);
int ints_min(const int *a, int n);
int ints_argmax(const int *a, int n);
int ints_argmin(const int *a, int n);
int ints_indices(const int *a, int n, int x, int* b);
int ints_find(const int *a, int n, int x);
int ints_find_last(const int *a, int n, int x);
int ints_nub(const int *a, int n, int *b);

int ints_equal(const int *a, const int n, const int *b, int m);

int ints_copy(const int *a, int n, int *b);

int rand_to(int n);
int ints_random(int x, int n, int *a);

int ints_count_while(const int *a, int n, int x);
int ints_count_while_not(const int *a, int n, int x);
int ints_unique(const int *a, int n, int *b);
int ints_groups(const int *a, int n, int *b);
int ints_runs(const int *a, int n, int x, int *b);
int ints_runs_starts(const int *a, int n, int x, int *b, int *c);

int ints_is_sorted(int *a, int n);
int ints_rank(const int *a, int n, int x);
int ints_bfind(const int *a, int n, int x);
void ints_exchange(int *a, int x, int y);
int ints_insert(int *a, int n, int x);
void ints_isort(int *a, int n);
int ints_merge(const int *a, int n, const int *b, int m, int *c);
// Sort array `a` using mergesort
void ints_msort(int *a, int n);


void unit_test_ints_count(void);
void unit_test_ints_sum(void);
void unit_test_ints_remove(void);
void unit_test_ints_max(void);
void unit_test_ints_min(void);
void unit_test_ints_argmax(void);
void unit_test_ints_argmin(void);
void unit_test_ints_indices(void);
void unit_test_ints_find(void);
void unit_test_ints_find_last(void);
void unit_test_ints_nub(void);

void unit_test_ints_equal(void);

void unit_test_ints_count_while(void);
void unit_test_ints_count_while_not(void);
void unit_test_ints_insert(void);
void unit_test_ints_unique(void);
void unit_test_ints_groups(void);
void unit_test_ints_runs(void);
void unit_test_ints_runs_starts(void);

void unit_test_ints_is_sorted(void);
void unit_test_ints_rank(void);
void unit_test_ints_bfind(void);
void unit_test_ints_insert(void);
void unit_test_ints_isort(void);
void unit_test_ints_merge(void);
void unit_test_ints_msort(void);

void ints_unit_tests(void);

#endif
