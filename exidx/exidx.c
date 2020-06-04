/*
 *
 * exidx.c
 *
 *  Created on: Sep 7, 2014
 * exidx -- locate the index of a character in a one dimensional array
 *
 * Copyright 2014, Proxor
 *
 */

#include <stdio.h>
#include <stdlib.h>


/*
 * return the index of the first occurrence of character ch in
 * the array list with length size.
 * Return the index of ch on success, -1 if not found
 */
int find_idx(char ch, char list[], int size)
{
   for(int i=0;i<size;i++)
{	if(ch==list[i])
	return i;
}
return -1;
}

int main(void) {
   char list[3]={'a','b','c'};
int t = find_idx('b',list,3);
printf("%d",t);
    return EXIT_SUCCESS;
}
