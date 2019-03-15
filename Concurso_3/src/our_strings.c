//
//  our_strings.c
//
//  Created by Pedro Guerreiro on 10/12/2018.
//  Copyright © 2018 Pedro Guerreiro. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

#include "our_strings.h"

#define MAX_LINE_LENGTH 10000

char *str_dup(const char *s)
{
  char *result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}

char *str_ndup(const char *s, int n)
{
  char *result = (char *) malloc(n + 1);
  strncpy(result, s, n);
  result[n] = '\0';
  return result;
}

int str_readline(FILE *f, char *s)
{
  int result = EOF;
  char *p = fgets(s, INT_MAX, f);
  if (p != NULL)
  {
    result = (int) strlen(s);
    if (result > 0 && s[result-1] == '\n')
      s[--result] = '\0';
  }
  return result;
}

int str_getline(char *s)
{
  return str_readline(stdin, s);
}

char **strings_new(int n)
{
  return (char **) malloc (n * sizeof(char *));
}

const char **strings_new_c(int n)
{
  return (const char **) malloc (n * sizeof(char *));
}

int strings_read(FILE *f, const char **a)
{
  int result = 0;
  char line[MAX_LINE_LENGTH];
  while (str_readline(f, line) != EOF)
    a[result++] = str_dup(line);
  return result;
}

int strings_readwords(FILE *f, const char **a)
{
  int result = 0;
  char word[MAX_LINE_LENGTH];
  while (fscanf(f, "%s", word) != EOF)
    a[result++] = str_dup(word);
  return result;
}

int strings_getwords(const char **a)
{
  return strings_readwords(stdin, a);
}

int strings_get(const char **a)
{
  return strings_read(stdin, a);
}

void strings_write(FILE *f, const char **s, int n, const char *separator)
{
  if (n > 0)
  {
    fprintf(f, "%s", s[0]);
    for (int i = 1; i < n; i++)  // i = 1
      fprintf(f, "%s%s", separator, s[i]);
  }
}

void strings_writeln(FILE *f, const char **s, int n, const char *separator)
{
  strings_write(f, s, n, separator);
  fprintf(f, "\n");
}

void strings_print(const char **s, int n, const char *separator)
{
  strings_write(stdout, s, n, separator);
}

void strings_println(const char **s, int n, const char *separator)
{
  strings_writeln(stdout, s, n, separator);
}

void strings_fprintf(FILE *f, const char **s, int n, const char *fmt)
{
  for (int i = 0; i < n; i++)
    fprintf(f, fmt, s[i]);
}

void strings_fprintfln(FILE *f, const char **s, int n, const char *fmt)
{
  strings_fprintf(f, s, n, fmt);
  fprintf(f, "\n");
}

void strings_printf(const char **s, int n, const char *fmt)
{
  strings_fprintf(stdout, s, n, fmt);
}

void strings_printfln(const char **s, int n, const char *fmt)
{
  strings_fprintfln(stdout, s, n, fmt);
}

int strings_find(const char **s, int n, const char *x)
{
  for (int i = 0; i < n; i++)
    if (strcmp(s[i], x) == 0)
      return i;
  return -1;
}

int strings_count(const char **s, int n, const char *x)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    if (strcmp(s[i], x) == 0)
      result++;
  return result;
}

int strings_equal(const char **a, const int n, const char **b, int m)
{
  int result = n == m;
  int i = 0;
  while (result && i < n)
    if (strcmp(a[i], b[i]) != 0)
      result = 0;
    else
      i++;
  return result;
}


int strings_rank(const char **s, int n, const char *x)
{
  int result = 0;
  while (n > 0)
  {
    int m = n / 2;
    if (strcmp(x, s[m]) <= 0)
      n = m;
    else
    {
      result += m+1;
      s += m+1;
      n -= m+1;
    }
  }
  return result;
}

int strings_bfind(const char **s, int n, const char *x)
{
  int r = strings_rank(s, n, x);
  return r < n && strcmp(s[r], x) == 0 ? r : -1;
}

void strings_exchange(const char **a, int x, int y)
{
  const char *m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void strings_sort_last(const char **a, int n)
{
  int i = n-1;
  while (i > 0 && strcmp(a[i-1], a[i]) > 0)
  {
    strings_exchange(a, i-1, i);
    i--;
  }
}

void strings_isort(const char **a, int n)
{
  for (int i = 2; i <= n; i++)
    strings_sort_last(a, i);
}

int strings_copy(const char **a, int n, const char **b)
{
  if (n < 0)
    n = 0;
  memmove(b, a, n * sizeof(char *));  // Note: 3rd arg is unsigned.
  return n;
}
