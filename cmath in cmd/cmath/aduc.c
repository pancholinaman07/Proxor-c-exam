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

/* Define new commands, cmd_add here: */

/* cmd_add adds two signed long int values in the first two elements of 
 *   the array parms. The output should look like:
[Math:Add]
3456
 *   where "3456" is the actual sum.
 */
void cmd_add()
{
    long int a = parms[0];
    long int b = parms[1];
    printf("%s\n", "[Math:Add]");
    long int c = a+b;
	printf("%ld\n",c);
    
}

void cmd_mult()
{
    long int a = parms[0];
    long int b = parms[1];
    printf("%s\n", "[Math:Mult]");
    long int c = a*b;
	printf("%ld\n",c);
    
}
/* HINT: additional command(s) can be defined here */

/*----------------------------------------------------------------------------
 * Init command interpreter
 */
void initialize_interpreter(void) {
    cmdb_init(TRUE);    // init a new command instance
    /* HINT: add command interpreter commands here */
    cmdb_add_cmd("Math", "", "", "Math Subsystem", "", NULL);
    cmdb_add_cmd("Add", "Math", "%ld %ld", "Adds two ints", "", cmd_add);
    cmdb_add_cmd("Mult", "Math", "%ld %ld", "Multiplies two ints", "", cmd_mult);
}
/*----------------------------------------------------------------------------
 * MAIN FUNCTION
 */
int main(void)
{
    IOsetup(0); // non-blocking raw read on console input

    initialize_interpreter();    // Init Command Interpreter

    printf("\n%s.\n",Welcome); // Display startup message

    cmdb_prompt();

    while (TRUE)
    {
        int ch = getchar();
        if (ch == EOF) break;

        cmdb_scan(ch);

        while (macro_ptr!=-1 && macro_buf[macro_ptr]) {
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
        macro_ptr=-1;

    } //while
    return 0;
}
