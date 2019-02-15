/*
 * Radar_ZEE.c
 *
 *  Created on: Feb 11, 2019
 *      Author: Diogo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define LEFT -3
#define RIGHT 7
#define BOTTOM -4
#define UPPER 6

typedef struct {
	int x, y;
}Point, *ApPoint;

int get_point(ApPoint p){
	return fscanf(stdin, "%d %d", &p->x, &p->y);
}

//Expands the allocated memory for an array of Points by 2 times
int resize_array(ApPoint a, int n){
	a = (ApPoint) realloc(a, (2*n) * sizeof(Point));
	return 2*n;
}

//Reads an array of points into "array_points" and
//returns the number of points read
int get_array_points(ApPoint array_points, int n) {
	Point aux_point;
	int array_max_size = n;
	int i=0;
	while(get_point(&aux_point) != EOF){
		if(i == array_max_size)
			array_max_size = resize_array(array_points, array_max_size);
		array_points[i].x = aux_point.x;
		array_points[i++].y = aux_point.y;
	}
	return i;
}

//Prints the "x y" coordinates of a point
void print_point(ApPoint p){
	fprintf(stdout, "%d %d", p->x, p->y);
}

//Same as print_point but adds a new line
void println_point(ApPoint p){
	print_point(p);
	fprintf(stdout, "\n");
}

//Returns a number != 0 if point p is inside the boundaries
//Returns 0  if not
int inside(ApPoint p){
	return p->x >= LEFT && p->x <= RIGHT && p->y >= BOTTOM && p->y <= UPPER;
}

//Returns a number != 0 if point a and b are collinear with the origin (0,0)
//Returns 0 if they are not
int collinear(ApPoint a, ApPoint b){
	return (a->x * b->y) - (a->y * b->x) == 0;
}

//Returns the distance of point a to the origin
double distance(ApPoint a){
	return sqrt(a->x*a->x + a->y*a->y);
}

//Created by Pedro Guerreiro
//Returns -1 if number is negative, 1 if positive and 0 if number is 0
int sign(int x) {
  return (x >= 0) - (x <= 0);
}

//Returns a number != 0 if the 2 points are on the same quadrant
//Returns 0 if not
int same_quadrant(ApPoint a, ApPoint b){
	return sign(a->x) == sign(b->x) && sign(a->y) == sign(b->y);
}

//Returns a number != 0 if point a is hidden by b
//Returns 0 if not
int hidden(ApPoint a, ApPoint b){
	return distance(a) > distance(b) && same_quadrant(a, b) != 0 && collinear(a, b) != 0;
}

//Returns 1 if point a is hidden behind any of the points in swarm
//Returns 0 otherwise
int hidden_swarm(ApPoint a, ApPoint swarm, int n){
	for(int i=0; i<n; i++){
		if(hidden(a, swarm+i) != 0)
			return 1;
	}
	return 0;
}

// ------------------

void unit_test_resize_array(void){
	ApPoint a = (ApPoint) malloc(2*sizeof(Point));

	a[0].x = 1; a[0].y = 1;
	a[1].x = 2; a[1].y = 2;

	resize_array(a, 2); //array will be 4 units long

	assert(a[0].x == 1); assert(a[0].y == 1);
	assert(a[1].x == 2); assert(a[1].y == 2);

	a[2].x = 3; a[2].y = 3;
	a[3].x = 4; a[3].y = 4;

	assert(a[0].x == 1); assert(a[0].y == 1);
	assert(a[1].x == 2); assert(a[1].y == 2);
	assert(a[2].x == 3); assert(a[2].y == 3);
	assert(a[3].x == 4); assert(a[3].y == 4);

	resize_array(a, 4); //array will be 8 units long

	a[3].x = 4; a[3].y = 4;
	a[4].x = 5; a[4].y = 5;
	a[5].x = 6; a[5].y = 6;
	a[6].x = 7; a[6].y = 7;
	a[7].x = 8; a[7].y = 8;

	assert(a[0].x == 1); assert(a[0].y == 1);
	assert(a[1].x == 2); assert(a[1].y == 2);
	assert(a[2].x == 3); assert(a[2].y == 3);
	assert(a[3].x == 4); assert(a[3].y == 4);
	assert(a[3].x == 4); assert(a[3].y == 4);
	assert(a[4].x == 5); assert(a[4].y == 5);
	assert(a[5].x == 6); assert(a[5].y == 6);
	assert(a[6].x == 7); assert(a[6].y == 7);
	assert(a[7].x == 8); assert(a[7].y == 8);
}

void unit_test_inside(ApPoint a){
	assert(inside(a) != 0);
	assert(inside(a+1) != 0);
	assert(inside(a+2) == 0);
	assert(inside(a+3) != 0);
	assert(inside(a+4) != 0);
	assert(inside(a+5) == 0);
	assert(inside(a+6) == 0);
	assert(inside(a+7) != 0);
	assert(inside(a+8) != 0);
	assert(inside(a+9) != 0);
}

void unit_test_collinear(ApPoint a){
	assert(collinear(a, a+7) != 0);
	assert(collinear(a, a+4) == 0);
	assert(collinear(a+8, a+9) != 0);
	assert(collinear(a+1, a+2) == 0);
}

void unit_test_distance(ApPoint a){
	assert(distance(a+4) == 1);
	assert(distance(a+3) == 2);
}

void unit_test_same_quadrant(ApPoint a){
	assert(same_quadrant(a, a+7) != 0);
	assert(same_quadrant(a, a+3) == 0);
	assert(same_quadrant(a+1, a+8) == 0);
	assert(same_quadrant(a+1, a+5) != 0);
}

void unit_test_hidden(ApPoint a){
	assert(hidden(a+3, a+4) == 0);
	assert(hidden(a+7, a) != 0);
	assert(hidden(a, a+7) == 0);
	assert(hidden(a+9, a+8) != 0);
}

void unit_test_hidden_swarm(ApPoint a, int n){
	assert(hidden_swarm(a, a, n) == 0);
	assert(hidden_swarm(a+7, a, n) != 0);
	assert(hidden_swarm(a+2, a, n) == 0);
	assert(hidden_swarm(a+9, a, n) != 0);
}

void unit_tests(void)
{
	const int num_points = 10;

	//Creating an array with some points
	Point a[num_points];
	a[0].x = 2; a[0].y = 2;
	a[1].x = 2; a[1].y = -2;
	a[2].x = -4; a[2].y = 1;
	a[3].x = 0; a[3].y = 2;
	a[4].x = 1; a[4].y = 0;
	a[5].x = 7; a[5].y = -5;
	a[6].x = 10; a[6].y = -3;
	a[7].x = 3; a[7].y = 3;
	a[8].x = -1; a[8].y = 2;
	a[9].x = -2; a[9].y = 4;

	//Testing
	unit_test_resize_array();
	unit_test_inside(a);
	unit_test_collinear(a);
	unit_test_distance(a);
	unit_test_same_quadrant(a);
	unit_test_hidden(a);
	unit_test_hidden_swarm(a, num_points);
}

// ------------------

void question_A(void)
{
	ApPoint planes = (ApPoint) malloc(sizeof(Point));
	int number_planes = get_array_points(planes, 1);
	for(int i=0; i<number_planes; i++)
		if(hidden_swarm(planes+i, planes, number_planes) != 0)
			println_point(planes+i);
}

void question_B(void)
{
	ApPoint ships = (ApPoint) malloc(sizeof(Point));
	int number_ships = get_array_points(ships, 1);
	for(int i=0; i<number_ships; i++){
		if(inside(ships+i) != 0)
			println_point(ships+i);
	}
}

// ------------------

int main(int argc, char **argv)
{
	unit_tests();
	assert(argc > 1);
	int x = *argv[1];
	if (x == 'A')
		question_A();
	else if (x == 'B')
		question_B();
	else
		printf("Invalid option: %c\n", x);
	return 0;
}


