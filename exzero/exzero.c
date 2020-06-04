/*
 * exzero.c
 *
 * Created on: Sep 7, 2014
 * exzero -- count number of zeros in an array
 * Copyright 2014, Proxor
 */

#include <stdio.h>
#include <stdlib.h>


/*
 * count_zeros -- count the number of zeros in an array of length size
 * parameters:
 *    array -- array of integers
 *    size -- the number of integers in the array (>= 0)
 * returns:
 *    number of zeros
 *    -1 on invalid arguments: either array is NULL or size < 0
 */

int count_zeros(int array[], int size)
{
if (array != NULL)
{
   int x =0;
	for(int i = 0;i<size;i++)
	{ if(array[i]==0)
		x=x+1;
	}
return x;
}
else
	 return -1;
}


int main(void) 
{
 int  array[5]={1,0,3,5,2};
int size = 5;
int t = count_zeros(array,5);
printf("%d\n",t);	
    
}
