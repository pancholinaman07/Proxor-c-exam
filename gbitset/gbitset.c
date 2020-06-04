#include <stdio.h>
#ifndef MAX_BSET_SIZE
#define MAX_BSET_SIZE 5
#endif


typedef struct{
	unsigned int bit:1;
}onebit;

typedef struct{
	onebit arr[MAX_BSET_SIZE];
}bset;

#include "gbitset.h"


void print_bset(bset a)
{

	for(int i =0;i<MAX_BSET_SIZE;i++){
		printf("%d",a.arr[i].bit);
}
printf("\n");

}

bset bset_union(bset a, bset b)
{
	bset x;
	for(int i =0;i<MAX_BSET_SIZE;i++){
		
		x.arr[i].bit=a.arr[i].bit|b.arr[i].bit;	
	}
	return x;
}



bset bset_intersection( bset a, bset b)
{
	bset x;
	for(int i =0;i<MAX_BSET_SIZE;i++){
		
		x.arr[i].bit=a.arr[i].bit&b.arr[i].bit;	
	}
	return x;

}



bset bset_insert(int i, bset s)
{
	s.arr[i].bit=s.arr[i].bit|1;
	return s;
}


int bset_test(int i, bset s)
{
	if(s.arr[i].bit==1)
		return 1;
	else
		return 0;
}



bset bset_delete(int i,  bset s)
{
	s.arr[i].bit=s.arr[i].bit&0;
	return s;
}



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
