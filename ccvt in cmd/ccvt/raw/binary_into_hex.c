#include<stdio.h>
#include<string.h>

void main()
{
int hexadecimal[]={0,1,10,11,100,101,110,111,1000,1001,1010,1011,1100,1101,1110,1111};
int temp,index,digit;
char s = "0b10010";
int binaryform=atoi(s);
char hexaconverted[20];
temp=binaryform;
index=0;

while(temp!=0)
{
    digit=temp%10000;

    for(int i=0;i<16;i++)
    {
        if(hexadecimal[i]==digit)
        {
            if(i<10)
            {
                hexaconverted[index]=(char)(i+48);
            }

            else
            {
                hexaconverted[index]=(char)((i-10)+65);
            }
        }

        index++;
        break;
    }

    temp=temp/10000;
}

hexaconverted[index]='\0';


}
