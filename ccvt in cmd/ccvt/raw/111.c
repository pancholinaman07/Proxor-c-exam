#include<stdio.h>
#include<string.h>


int val(char c)
{
	 if(c>='0' && c<='9')
	 	return (int)c - '0';
	 	
	 else
	 		return (int)c - 'a' + 10;	


}

int todeci(char *str,int base)
{
	int len = strlen(str);
	int power = 1;
	int num = 0;
	int i;
	
	
	for(i = len -1 ; i>=0 ; i--)
	{
		if(val(str[i])>=base)
		{
			printf("invalid number");
			return -1;
		}
		
		num += val(str[i]) * power;
		power = power * base;
	
	}
	
	return num;
}

int main()
{	
	char str[10000];
	printf("write the binary form : ");
	scanf("%s",&str);
	

	int base = 16;
	printf("decimal equivalent of %s in base %d is %d\n",str,base,todeci(str,base));
	
	
return 0;	


}
