/*
 * exdst.c
 *
 * Created on: Sep 7, 2014
 * exdst -- calculate the distance between 2 coordinates
 *
 * Copyright 2014, Proxor
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* dst -- compute the distance from x1, y1 to x2, y2
 * parameters:
 *    x1 and y1 -- coordinates of point 1
 *    x2 and y2 -- coordinates of point 2
 * returns:
 *    distance between points calculated using double precision 
 *        floating point numbers
 */
double dst(int x1, int y1, int x2, int y2)
{
   double t = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	return t;
}


int main(void) 
{
    double t=dst(1,2,3,4);
	printf("%lf",t);

    return EXIT_SUCCESS;
}
