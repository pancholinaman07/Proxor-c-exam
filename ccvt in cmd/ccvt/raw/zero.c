#include<stdio.h>
#include<string.h>
int zero(char res[])
{
int count = 0;
for(int i=0;i<strlen(res);i++)
{
	if(res[i]=='0') 
{
	count++;
}
}
if(count == strlen(res)) 
{
return 1;
}

else
{
return 0;
}

}

int main(void)
{
char x[100] = "0000000001";

int t = zero(x);
printf("%d",t);


}
