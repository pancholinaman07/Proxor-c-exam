#include<stdio.h>
#include<string.h>

void int_into_binary(int n)
{
	int binaryNum[32];
	int i = 0;
	while (n>0)
	{
		binaryNum[i] = n%2;
		n = n/2;
		i++;
	}
	
	
	for(int j = i-1; j>=0; j--)
			printf("%d",binaryNum[j]);
			
}
int main()
{
char c[3] = "354";
int i,j = 0;
char x[1000];
if (c[1] == -1){
	    for(i = 1;c[i] != '\0';i++)
    {
    	x[j] = c[i];
    	
    	if(c[i] == ' ' && c[i+1] != ' ' )
    	{
    	
    	i++;
    	}
    	  j++;
    }
    
    int a = atoi(x);
  int binaryNum[32];
	int i = 0;
	while (n>0)
	{
		binaryNum[i] = n%2;
		n = n/2;
		i++;
	}
	
	
	for(int j = i-1; j>=0; j--)
			printf("%d",binaryNum[j]);
    
    
	
	}





int a = atoi(c);
printf("%d\n",a);
int_into_binary(a);
}
