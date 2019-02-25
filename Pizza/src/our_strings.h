//
//  our_strings.h
//
//  Created by Pedro Guerreiro on 10/12/2018.
//  Copyright © 2018 Pedro Guerreiro. All rights reserved.
//

#ifndef our_strings_h
#define our_strings_h

char *str_dup(const char *s);
char *str_ndup(const char *s, int n);
int str_readline(FILE *f, char *s);
int str_getline(char *s);

char **strings_new(int n);

int strings_read(FILE *f, const char **a);
int strings_readwords(FILE *f, const char **a);
int strings_getwords(const char **a);
int strings_get(const char **a);

void strings_write(FILE *f, const char **s, int n, const char *separator);
void strings_writeln(FILE *f, const char **s, int n, const char *separator);
void strings_print(const char **s, int n, const char *separator);
void strings_println(const char **s, int n, const char *separator);
void strings_fprintf(FILE *f, const char **s, int n, const char *fmt);
void strings_fprintfln(FILE *f, const char **s, int n, const char *fmt);
void strings_printf(const char **s, int n, const char *fmt);
void strings_printfln(const char **s, int n, const char *fmt);

int strings_find(const char **s, int n, const char *x);
int strings_count(const char **s, int n, const char *x);
int strings_equal(const char **a, const int n, const char **b, int m);
int strings_rank(const char **s, int n, const char *x);
int strings_bfind(const char **s, int n, const char *x);

void strings_exchange(const char **a, int x, int y);
void strings_sort_last(const char **a, int n);
void strings_isort(const char **a, int n);

int strings_copy(const char **a, int n, const char **b);

#endif
