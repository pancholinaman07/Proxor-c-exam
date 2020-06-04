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

/* hex_to_int converts one hexadecimal digit passed in c into
 *   an integer. E.g. hex_to_int('0') == 0, hex_to_int('5') == 5,
 *   hex_to_int('a') == 10.
 * Assume c is one of '0'-'9' or 'a'-'f' (you do not have to handle
 *   upper case 'A'-'F' or other characters
 * Return the integer corresponding to the hexadecimal digit.
 */
int val(char c)
{
	 if(c>='0' && c<='9')
	 	return (int)c - '0';
	 	
	 else
	 		return (int)c - 'a' + 10;	


}

int todeci(char* str,int base)
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

void delete(char a[],int n)
{

	for(int i = 0;i<n-2;i++){
		a[i] = a[i+2];		

	}
	
 a[n-1] = '\0';
 a[n-2] = '\0';	
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

	
	delete(argstr_buf,strlen(argstr_buf));
	int base = 2;
	printf("decimal equivalent of %s in base %d is %d\n",argstr_buf,base,todeci(argstr_buf,base));
}
/*----------------------------------------------------------------------------
 * Init command interpreter
 */
void initialize_interpreter(void) {
    cmdb_init(TRUE);    // init a new command instance
    /* HINT: add command interpreter commands here */
	cmdb_add_cmd("Cvt","Global","%s","convert","",cmd_cvt);
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
