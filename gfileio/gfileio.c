#include <stdio.h>
int read_number(FILE *inf,int *result)
{
    // read from file and store in pointer result and will return 1 if a integer is stored in result
    if((fscanf(inf,"%d",result)!=EOF)) return 1; 

 	// no int to be found
	return 0; 
}

int main(int argc, char *argv[])
{
    // declare a file pointer fp
    FILE *fp; 

    // open file and set it to read mode
    fp=fopen(argv[1],"r");

    //fseek() - It is used to moves the reading control to different positions using fseek function. 
    fseek(fp, 0, SEEK_END);         
       
    //ftell() - It tells the byte location of current position in file pointer.
    int size = ftell(fp);

    //rewind() - It moves the control to beginning of a file.
    rewind(fp);                   
                               
    // declared an array named as res of size = total integers gfileio consist;
    int res[size];

    // declared and int pointer pointing towards 0th index of res
    int *ip=res;

    int i, cnt=0, sum=0; 

    // stores all integers in array res    
    while(read_number(fp,ip)){
    	cnt++;
	ip++;
	}
	ip--;
	
   // sum of all integers
	for(i=0; i<cnt; i++){
		sum = sum + (*ip);
		ip--;
	}
// close the file pointer fp
fclose(fp);

// print the sum
printf("%d\n",sum);
	                      

    return 0;
}
