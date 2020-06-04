#include<stdio.h>
#include<string.h>
#include<math.h>
int main(void)
{
	char s[4] = "1010";
	int x =0;
	for(int i = 0;i<strlen(s);i++)
	{

	x = x+(s[i]-48)*pow(2,strlen(s)-i);

	}
	printf("%d",x);

}
