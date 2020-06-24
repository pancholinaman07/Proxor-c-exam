#include <stdio.h>
int read_number(FILE *inf,int *result)
{
	if((fscanf(inf,"%d",result)!=EOF))return 1;
	return 0;	  //no int to be found	
}

int main(int argc, char *argv[])
{

    FILE *fp;
    fp=fopen(argv[1],"r");
    

    
    fseek(fp, 0, SEEK_END);                 
    int size = ftell(fp);                   
    rewind(fp);                             
    
    int res[size];
    int *ip=res;
    int i, cnt=0; 
    
    while(read_number(fp,ip)){
    	cnt++;
    	ip++;
	} 
	ip--;
   
	for(i=0;i<cnt; i++){
		printf("%d\n",*ip);
		ip--;
	}
	                      
		fclose(fp);
    return 0;
}
