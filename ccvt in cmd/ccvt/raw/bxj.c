#include<stdio.h>
#include<string.h>
#include<stdlib.h>


char map_x(int x)
{
    if(x <= 9)
    {
        return '0'+x;
    }
    
    switch(x)
    {
        case 10:
            return 'a';
        case 11:
            return 'b';
        case 12:
            return 'c';
        case 13:
            return 'd';
        case 14:
            return 'e';
        case 15:
            return 'f';
        default:
            return '0';
    }
}

void reverse(char* str)
{
    int len = strlen(str);
    int i = 0;
    int j = len-1;
    
    while(i < j)
    {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

char * toHex(int num){
    char* buff = (char*)malloc(17);
    memset(buff, '\0', 17);
    int index = 0;
    
    if(num == 0)
    {
        buff[0] = '0';
        return buff;
    }
    
    while(num && index < 16)
    {
        int x = num & 0xf;
        buff[index++] = map_x(x);
        num = num>> 4;
    }
    
    reverse(buff);
    
    return buff;
}


int main(void)
{

char* b= toHex(-15217);
printf("%s",b);


}
