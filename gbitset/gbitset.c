/* gbitset.c -- bitset implementation task */

#include <stdio.h>


/* do not change anything in this code block except possibly "100" */
#ifndef MAX_BSET_SIZE
/* for testing, you can change the value 100 to something different here */
#  define MAX_BSET_SIZE 100
#endif

/* CHANGE THIS TYPEDEF to define bset -- although it is 
 * conventional to put this in gbitset.h, leave it here instead:
 */
typedef struct{
	unsigned int bit:1;
}onebit;

typedef struct{
	onebit arr[MAX_BSET_SIZE];
}bset;

/* Do not remove this include or alter gbitset.h
 * gbitset.h uses bset, defined above, so it would be incorrect to
 * put this include at the top of the file.
 */
#include "gbitset.h"

void print_bset(bset a)
{

	for(int i =0;i<MAX_BSET_SIZE;i++){
		printf("%d",a.arr[i].bit);
}
printf("\n");

}

/* compute the set union of a and b */
bset bset_union(bset a, bset b)
{
	bset x;
	for(int i =0;i<MAX_BSET_SIZE;i++){
		
		x.arr[i].bit=a.arr[i].bit|b.arr[i].bit;	
	}
	return x;
}


/* compute the intersection of a and b */
bset bset_intersection(const bset a,const bset b)
{
	bset x;
	for(int i =0;i<MAX_BSET_SIZE;i++){
		
		x.arr[i].bit=a.arr[i].bit&b.arr[i].bit;	
	}
	return x;

}


/* add element i to set s. If i < 0 or i >= MAX_BSET_SIZE,
   return s. Otherwise return the union of s with {i}, the
   set containing i.
 */
bset bset_insert(int i, const bset s)
{
	bset y;
	for(int x=0;x<MAX_BSET_SIZE;x++)
	{
	y.arr[x].bit=s.arr[x].bit;
	}
	y.arr[i].bit=y.arr[i].bit|1;
	return y;
}


/* return 1 if i is an element of s; otherwise return 0.
 * i can be any integer value
 */
int bset_test(int i, const bset s)
{
	if(s.arr[i].bit==1)
		return 1;
	else
		return 0;
}


/* return set s after removing element i. If i is not
   an element of s, simply return s */
bset bset_delete(int i,const  bset s)
{
	bset y;
	for(int x=0;x<MAX_BSET_SIZE;x++)
	{
	y.arr[x].bit=s.arr[x].bit;
	}
	y.arr[i].bit=y.arr[i].bit&0;
	return y;
}


/* return an empty set */
bset bset_empty()
{
	bset x;
	for(int i =0;i<MAX_BSET_SIZE;i++){
		onebit y;
		y.bit=0;
		x.arr[i]=y;	
	}
	return x;
}


/* main performs some simple tests on some of your functions.
   You can change main as long as this file still compiles.
   Additional testing will be performed by Proxor, so passing
   the tests here do not guarantee a good grade on this task.
 */
int main()
{
    int pass = 1;
    bset evens = bset_empty();
    bset low = bset_empty();
    bset low_even;
    bset low_or_even;
    int i;

    /* insert even numbers into bset evens */
    for (i = 0; i < MAX_BSET_SIZE; i += 2) {
        evens = bset_insert(i, evens);
    }

    /* insert numbers less than MAX/2 into low */
    for (i = 0; i < MAX_BSET_SIZE / 2; i++) {
        low = bset_insert(i, low);
    }

    /* form the intersection and test result */
    low_even = bset_intersection(low, evens);
    for (i = 0; i < MAX_BSET_SIZE; i++) {
        /* make sure members are all low and even */
        pass &= (bset_test(i, low_even) == 
                 (i < MAX_BSET_SIZE/2 && ((i & 1) == 0)));
    }

    /* form the union and test result */
    low_or_even = bset_union(low, evens);
    for (i = 0; i < MAX_BSET_SIZE; i++) {
        /* make sure members are all low and even */
        pass &= (bset_test(i, low_or_even) == 
                 (i < MAX_BSET_SIZE/2 || ((i & 1) == 0)));
    }

    /* print a success or fail message */
    if (pass) {
        printf("gbset has passed some simple tests\n");
    } else {
        printf("gbset appears to have errors\n");
    }
    return 0;
}
