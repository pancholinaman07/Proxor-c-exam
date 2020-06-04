#include <stdlib.h>      
#include <stdio.h>         
#include <string.h>



int val(char c)
{
	 if(c>='0' && c<='9')
	 	return (int)c - '0';
	 	
	 else
	 		return (int)c - 'a' + 10;	


}



int main(void)
{
char a;
printf("enter string : ");
scanf("%s",&a);
int c = atoi(a);
printf("\n%d\n",c);

}
