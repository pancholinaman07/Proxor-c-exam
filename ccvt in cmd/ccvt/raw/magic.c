#include<stdio.h>



int main(void)
{

int i = 0;
unsigned int u_i=0;
int j =0;
int b[8] = {0};


printf("input number ");
scanf("%d",&i);

u_i = (unsigned int) i;

for(j=15;j>=0;j--)
{
	b[j] = u_i & 0x1;
	u_i = u_i >> 1;

}

for(j=0;j<=15;j++)
	printf("%d",b[j]);
	
	
	printf("\n");
	return 0;


}



