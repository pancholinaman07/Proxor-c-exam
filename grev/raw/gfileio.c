#include<stdio.h>
#include<string.h>

int read_number(FILE *inf,int *result)
{
	if((fscanf(inf,"%d",result)!=EOF))return 1;
	return 0;	  //no int to be found	
}



int main(int argc, char* argv[])
{
	FILE *fp;
	fp = fopen("numbers.txt","r");
	int x;
	int sum = 0;

	while(!feof(fp))
		{

			int *val;
			val = &x;
			if(1==read_number(fp,val))
				{
					
					sum = sum + (*val);


				}

			
		}
printf("%ld",sum);	
fclose(fp);
return 0;
	
}

