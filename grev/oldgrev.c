/* gfileio.c 
 *
 * Roger Dannenberg
 * Aug 2014, Proxor
 */

#include <stdio.h>
#include<errno.h>

/* read_number reads a long int
 * parameters:
 *    inf - an opened input file 
 *    result - address where to store the int, if any
 * returns:
 *    1 if an integer was read
 *    0 if not, e.g. upon end-of-file
 * read_number can be called repeatedly to read
 *    successive integers from the file
 */
int read_number(FILE *inf, int *result)
{
    
    if(1==fscanf(inf,"%d",result))
    	return 1;
	return 0;
}


/* main expects a file name to be passed on the command line.
   The file is opened and integers are read from the file. The
   sum of the integers is printed to the console (to stdout),
   or zero is printed if there are no integers in the file.
   main() returns 0.
 */
int main(int argc, char *argv[])
{
    
    FILE *fp;
    fp=fopen("numbers.txt","r");
    
    if(fp == NULL){
    	printf("no contents in the file passed as argument\n");
    	return 0;
	}
    
    fseek(fp, 0, SEEK_END);                  //fseek() - It is used to moves the reading control to different positions using fseek function.
    int size = ftell(fp);                   //ftell() - It tells the byte location of current position in file pointer.
    rewind(fp);                             //rewind() - It moves the control to beginning of a file.
    
	int res[size];
    int* ip=res;
    int i, cnt=0, sum=0; 
    
    while(read_number(fp,ip)){
    	cnt++;
    	ip++;
	} 
   
	for(i=cnt-1; i>=0; i--){
		printf("%d\n",res[i]);
	}
	                      

    return 0;
}
