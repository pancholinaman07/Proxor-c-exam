 
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

/* This is the array accessed by new Save and Get commande */
long int array[100];

/* Define new commands, cmd_save here: */

/* cmd_save uses the first value in the array parms
 *   as an array index and the second value is 
 *   stored in array at the location given by index.
 *   If index is out of range, print "Out of range: "
 *   and the index
 */
void cmd_save()
{
    long int index = parms[0];
    long int value = parms[1];
    printf("%s\n", "[Array:Save]");

    if (index >= 100 || index < 0) {
      printf("Out of range: %ld\n", index);
    } else {
      printf("%ld %ld\n", index, value);
      array[parms[0]] = parms[1];
    }
}

void cmd_get()
{
    long int index = parms[0];
    printf("%s\n", "[Array:Get]");

    if (index >= 100 || index < 0) {
      printf("Out of range: %ld\n", index);
    } else {
      long int value = array[index];
      printf("%ld %ld\n", index, value);
    }
}

/* HINT: additional command(s) can be defined here */

/*----------------------------------------------------------------------------
 * Init command interpreter
 */
void initialize_interpreter(void) {
    cmdb_init(TRUE);    // init a new command instance
    /* HINT: add command interpreter commands here */
    cmdb_add_cmd("Array", "", "", "Array Subsystem", "", NULL);
    cmdb_add_cmd("Save", "Array", "%ld %ld", "save 2 integers index and its value", "", cmd_save);
    cmdb_add_cmd("Get", "Array", "%ld ", "gets the value of that index", "", cmd_get);
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
