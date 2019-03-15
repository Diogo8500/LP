/*
 ============================================================================
 Name        : Concurso_3.c
 Author      : Diogo_Duarte
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "our_strings.h"
#include "our_ints.h"

const int max_members = 20000;
const int max_category = 50;
const int max_votes = 100000;
const int max_cat_size = 100;
const int max_nominee_size = 1000;
typedef struct _data Data;
typedef struct _data_n Data_N;

void task_a();
void task_b();
void task_c(char *a);

Data* new_data_array(int n);
Data_N* new_data_n_array(int n);
int read_data_f(FILE *f, Data *data_array);
int get_data(Data *data_array);

void print_data_f(FILE *f, const Data *data);
void print_data_f(FILE *f, const Data *data);
void print_data_array_f(FILE *f, const Data *data_array, int n);
void print_data(const Data *data);
void print_data_array(const Data *data_array, int n);

int compare_data_number(const Data *a, const Data *b);
int compare_data_category(const Data *a, const Data *b);
int compare_data_nominee(const Data *a, const Data *b);
int compare_data(const Data *a, const Data *b);
int data_copy(const Data *a, int n, Data *b);
int data_merge(const Data *a, int n, const Data *b, int m, Data *c);
void data_msort_i(Data *a, int n, Data *b);
void data_msort(Data *a, int n);

int count_while(const Data *data_array, int n);

int main(int argc, char **argv)
{
  char x = ' ';
  if (argc >= 2)
    x = *argv[1];
  char *filename = NULL;
  if (argc >= 3)
    filename = argv[2];
  if (x == 'A')
    task_a();
  else if (x == 'B')
    task_b();
  else if (x == 'C')
    task_c(filename);
  else
    printf("%c Invalid option.\n", x);
  return 0;
}

struct _data {
	int number;
	char* category;
	char* nominee;
};

struct _data_n {
	Data data_struct;
	int number;
};

void task_a(){
	Data *votes = new_data_array(max_votes);
	int num_votes = get_data(votes);
	print_data_array((const Data*)votes, num_votes);
}
void task_b(){
	Data *votes = new_data_array(max_votes);
	int num_votes = get_data(votes);
	data_msort(votes, num_votes);
	Data_N *to_print = new_data_n_array(num_votes);
	int current_index = 0;
	while(current_index < num_votes){
		int num_ocurrences = count_while(votes+current_index, num_votes-current_index);
		if(num_ocurrences >= 1){
			to_print[current_index].data_struct = votes[num_ocurrences-1];
		}


	}
	print_data_array((const Data*)(to_print), current_index);
}
void task_c(char* a){

}

Data* new_data_array(int n){
	return (Data*) malloc(n*sizeof(Data));
}

Data_N* new_data_n_array(int n){
	return (Data_N*) malloc(n*sizeof(Data_N));
}

int read_data_f(FILE *f, Data *data_array){

	int result = 0;
	int member_number;
	char category[max_cat_size];
	char nominee[max_nominee_size];
	while(fscanf(f, "%d %s %s", &member_number, category, nominee) != EOF){
		data_array[result].number = member_number;
		data_array[result].category = str_dup((const char*)category);
		data_array[result++].nominee = str_dup((const char*)nominee);
	}
	return result;
}

int get_data(Data *data_array){
	return read_data_f(stdin, data_array);
}

void print_data_f(FILE *f, const Data *data){
	fprintf(f, "[%d][%s][%s]", data->number, data->category, data->nominee);
}
void print_data_array_f(FILE *f, const Data *data_array, int n){
	for(int i=0; i<n; i++){
		print_data_f(f, data_array+i);
		fprintf(f, "\n");
	}
}
void print_data(const Data *data){
	print_data_f(stdout, data);
}
void print_data_array(const Data *data_array, int n){
	print_data_array_f(stdout, data_array, n);
}

int compare_data_number(const Data *a, const Data *b){
	return a->number < b->number;
}
int compare_data_category(const Data *a, const Data *b){
	return strcmp(a->category, b->category);
}
int compare_data_nominee(const Data *a, const Data *b){
	return strcmp(a->nominee, b->nominee);
}
int compare_data(const Data *a, const Data *b){
	if(compare_data_number(a, b) < 0) return -1;
	else if(compare_data_number(a, b) > 0) return 1;
	else if(compare_data_category(a, b) < 0) return -1;
	else if(compare_data_category(a, b) > 0) return 1;
	else if(compare_data_nominee(a, b) < 0) return -1;
	else if(compare_data_nominee(a, b) > 0) return 1;
	else return 0;
}

int data_copy(const Data *a, int n, Data *b){
	if (n < 0) n = 0;
	memmove(b, a, n * sizeof(Data));  // Note: 3rd arg is unsigned.
	return n;
}
int data_merge(const Data *a, int n, const Data *b, int m, Data *c){
	int result = 0;
	int i = 0;
	int j = 0;
	while (i < n && j < m)
		if (compare_data(a+i, b+j) <= 0)
			c[result++] = a[i++];
		else
			c[result++] = b[j++];
	result += data_copy(a + i, n - i, c+result);
	result += data_copy(b + j, m - j, c+result);
	return result;
}
void data_msort_i(Data *a, int n, Data *b){
	if (n > 1)
	{
		int m = n / 2;
		data_msort_i(a, m, b);
		data_msort_i(a+m, n-m, b);
		data_merge(a, m, a+m, n-m, b);
		data_copy(b, n, a);
	}
}
void data_msort(Data *a, int n){
	Data *b = new_data_array(n);
	data_msort_i(a, n, b);
}

int count_while(const Data *data_array, int n){
	int result = 1;
	while(result < n && !compare_data_number(data_array, data_array+result) && !compare_data_category(data_array, data_array+result)){
		result++;
	}
	return result-1;
}
