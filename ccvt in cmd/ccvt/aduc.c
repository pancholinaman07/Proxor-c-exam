/*----------------------------------------------------------------------------
 * Header files
 */
#include <stdlib.h>        // Standard Lib header file
#include <stdio.h>         // Standard I/O header file
#include <string.h>
#include "aduc.h"          // Main
#include "cmd.h"           // Command interpreter
#include "cmtio.h"

static char Welcome[] = "Command Interpreter\0";

/* max binary digits */
#define size_int 64

char* ip;
/* hex_to_int converts one hexadecimal digit passed in c into
 *   an integer. E.g. hex_to_int('0') == 0, hex_to_int('5') == 5,
 *   hex_to_int('a') == 10.
 * Assume c is one of '0'-'9' or 'a'-'f' (you do not have to handle
 *   upper case 'A'-'F' or other characters
 * Return the integer corresponding to the hexadecimal digit.
 */


//The val function convert postive decimal string to integer form and convert characters. 							 
int val(char c)
{
	 if(c>='0' && c<='9')
	 	return (int)c - '0';  		
						
	 else
	 	return (int)c - 'a' + 10;	


}
// todeci convert takes two parameters string and the base of that form and convert it into decimal by changing each char from back of the string by formulae => num += val(str[i]) * power , power = power * base
		 															  

unsigned long int todeci(char *str,unsigned long int base)
{
	int len = strlen(str);
	unsigned long int power = 1;
	unsigned long int num = 0;
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

// reval function its like opposite function takes decimal form and convert it into string.
char reval(int num)
{
	if(num >= 0 && num<= 9)
		return (char)(num + '0');
	
	else
		return (char)(num - 10 + 'a');	
}


// strev function takes string and reverse it.
void strev(char *str)
{
	int len = strlen(str);
	int i;
	for(i = 0;i<len/2;i++)
	{
		char temp = str[i];
		str[i] = str[len - i - 1];
		str[len-i-1] = temp; 
	} 
	

}


typedef struct	{
	size_t b : 1;
}onebit;

typedef struct {
	char id[2];
	onebit bit[size_int];
}binary_rep;





void binary_print(unsigned long int n,binary_rep B)
{
	printf("%c%c",B.id[0],B.id[1]);
		if(n==0){printf("0");return;}
	int i = 0;
	while ((B.bit[i].b==0) && (i<size_int))i++;
	if(i==size_int)return;
	for(;i<size_int;i++)printf("%d",B.bit[i].b);
	return;

}


binary_rep itob(unsigned long int n)
{

	unsigned long int norignal = n;
	if (0 > n) {n = -1*n;n=n-1;}
	binary_rep B;
	B.id[0] = '0';
	B.id[1] = 'b';
	for(int i = size_int-1;i>=0;i--)
	{
		B.bit[i].b = n%2;
		n = n/2;
	}
	if(0>norignal) {
	
	B.bit[0].b=1;
	for (int i =1;i<size_int;i++)	{
		
		if(B.bit[i].b==0) {
				B.bit[i].b=1;
			} else {
				B.bit[i].b=0;
			}
		
		}
	
	}
return B;

}


// it convet negative integers to its unsigned hexadecimal form.

char * toHex(unsigned long int num){
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
        buff[index++] = reval(x);
        num = num>> 4;
    }
    
    strev(buff);
    
    return buff;
}
// it will delete the first two characters of the string.
void delete(char a[],int n,int x)
{

	for(int i = 0;i<n-x;i++){
		a[i] = a[i+x];
	}		

for(int y=1;y<=x;y++)
{
a[n-x] = '\0';
}
}
// to check if given string is a proper number of not.

char isNumber(char *text)
{
int x;
if(text[0]=='+'|text[0]=='-')
{
 x = 1;
}
else
	 x = 0;

int n = strlen(text);
for(int i = x; i<n;i++)
{
	if(text[i]>= '0' && text[i]<='9')
		continue;
	

	return 0;

}
return 1;

}
/*
 * Other support functions for cmd_cvt can be added here
 */

/* cmd_cvt parses the string argument as a
 *   signed decimal integer, unsigned binary,
 *   or hexadecimal integer and prints the value
 *   in all three formats. A binary representation
 *   starts with "0b" and a hexadecimal representation
 *   starts with "0x". See README.txt for example input
 *   and output. On output, leading zeros should not be
 *   printed.
 */
void cmd_cvt()
{
    /* 
     * implement cmd_cvt here
     */
int count =0;
ip = argstr_buf;
while(*ip==' ') {ip++;count++;}
delete(argstr_buf,strlen(argstr_buf),count);

  if(argstr_buf[0]=='0' && argstr_buf[1]=='b')		
               {	
		printf("[Convert]\n");
   		delete(argstr_buf,strlen(argstr_buf),2);
   		printf("%lu",todeci(argstr_buf,2));
   		printf(" ");
 		printf("0b%s",argstr_buf);
   		printf(" ");
		char* b= toHex(todeci(argstr_buf,2));
		printf("0x");
		printf("%s\n",b);
   		}



  else if(argstr_buf[0]=='0' && argstr_buf[1]=='x')
		{
		printf("[Convert]\n");
   		delete(argstr_buf,strlen(argstr_buf),2);
   		printf("%lu",todeci(argstr_buf,16));
   		printf(" ");
   		unsigned long int n = todeci(argstr_buf,16);
		binary_print(n,itob(n));
   		printf(" ");
   		printf("0x%s\n",argstr_buf);
   		}



else if(isNumber(argstr_buf))
{
		
   		printf("[Convert]\n");
		printf("%lld",atoll(argstr_buf));
		printf(" ");
		unsigned long int n = strtoul(argstr_buf,NULL,0);
		binary_print(n,itob(n));
		printf(" ");
		char* b= toHex(strtoul(argstr_buf,NULL,0));
		printf("0x");
		printf("%s\n",b);
}




else
	{printf("%s is not a digit\n",argstr_buf);}
	
}

/*----------------------------------------------------------------------------
 * Init command interpreter
 */
void initialize_interpreter(void) {
    cmdb_init(TRUE);    // init a new command instance
    /* HINT: add command interpreter commands here */
	cmdb_add_cmd("Cvt","Global","%s","input integer in base {2,10,16}","",cmd_cvt);
}

/*----------------------------------------------------------------------------
 * MAIN FUNCTION
 */
int main(void)
{
    IOsetup(0); // non-blocking raw read on console input

    initialize_interpreter();    // Init Command Interpreter

    printf("\n%s.\n", Welcome); // Display startup message

    cmdb_prompt();

    while (TRUE) {
        int ch = getchar();
        if (ch == EOF) break;

        cmdb_scan(ch);

        while (macro_ptr != -1 && macro_buf[macro_ptr]) {
            switch (macro_buf[macro_ptr]) {
                case '|': cmdb_scan('\n');
                          break;
                case '_': cmdb_scan(' ');
                          break;
            default:      cmdb_scan(macro_buf[macro_ptr]);
            }
            macro_ptr++;

            if (!macro_buf[macro_ptr]) {
                   cmdb_scan('\n');
            }
        }
        macro_ptr = -1;

    } //while
    return 0;
}
