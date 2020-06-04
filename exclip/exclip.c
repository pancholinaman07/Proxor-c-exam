/*
 * exclip.c
 *
 * Created on: Sep 7, 2014
 * exclip -- clip a value between min and max limits
 *
 * Copyright 2014, Proxor
 *
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * clip -- clip value between min and max limits inclusive
 * parameters:
 *    val -- value to be clipped
 *    min -- the lowest value allowed
 *    max -- the highest value allowed
 * returns:
 *    min if val is lower than min, max if val is greater than max, 
 *        and otherwise val
 */
signed int clip(signed int val,signed int min,signed int max)
{
if(max>min)
{
 if(val>max)
	return max;
 else if(val<min)
	return min;
 else
	return val;
}
else
	return -1;
}

/*
 * main -- the main program. You may insert test code here.
 */
int main(void) 
{
  signed  int t = clip(3,-1,5);
printf("%d",t);
    return EXIT_SUCCESS;
}
