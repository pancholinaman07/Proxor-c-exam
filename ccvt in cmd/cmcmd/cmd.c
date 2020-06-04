#include <stdlib.h>
#include <stdio.h>                       // Standard I/O header file
#include <ctype.h>                       // for isprint()
#include <string.h>                      // String library

#include "cmd.h"                         // Command Interpreter Prototypes
#ifdef HEXDUMP
#include "intelhex.h"                    // Intel Hex Formatted Memory Dumps
#endif
#include "aduc.h"                        // Main Program

char          escbuf[1 + MAX_ESC_LEN];   // escape sequence buffer
int           escndx;                    // escape sequence index

char          cmdbuf[1 + MAX_CMD_LEN];   // command buffer
int           cmdndx;                    // command index

int           argfnd;                    // how many args found

char          lstbuf[1 + MAX_CMD_LEN];   // last command buffer

signed char   subsystem = -1;


extern long Bytes2Long (unsigned char b1,unsigned char b2,unsigned char b3,unsigned char b4);
extern int  Bytes2Word (unsigned char b1,unsigned char b2);
extern long Words2Long(unsigned int w1,unsigned int w2);

static char prompt[] = "CMD> ";
static char bs[]     = "\b \b";
static char cls[]    = "\033[J\0"; // VT100 clear screen sequence


void          cmd_proc(const char *cmd);
unsigned char escid_search(const char *escstr);

//macro buffer
char          macro_buf[1 + MAX_CMD_LEN];
int           macro_ptr = -1;



/*----------------------------------------------------------------------------
 * Command Definition
 */
void cmd_test_hello();
void cmd_test_cmdline();
void cmd_quit();
void cmd_commands();
void cmd_macro();
void cmd_run();
void cmd_macros();
void cmd_cls();
void cmd_exit();
void cmd_help();

#define MAX_CMD 50


/* --------------------------------------------------------------------------------------------------*/
/*    cmdstr     subs     parms  cmddescr           parmdesc cmd_ptr */
/* --------------------------------------------------------------------------------------------------*/
static struct cmd_st cmd_tbl[MAX_CMD] = {
    { "Test",    "",       "",   "Test Subsystem",  "",      NULL},
    { "Hello",   "Test",   "%s", "Hello",           "world", cmd_test_hello},
    { "CmdLine", "Test",   "%lu %lu %lu %lu %lu %lu", "Test Commandline","delay breakpoint velocity1 endpos velocity2 channel", cmd_test_cmdline},
    { "Quit",    "Global", "",   "Quit",            "",      cmd_quit},
    { "Commands","Global", "",   "Dump Commands",   "",      cmd_commands},
#ifdef HEXDUMP
    { "HexDump", "Global", "%lu %lu %lu",             "Dump Intel Hex",  "start length base"},
#endif
    { "Macro",   "Global", "%s", "Define a macro",  "",      cmd_macro},
    { "Run",     "Global", "",   "Run a macro",     "",      cmd_run},
    { "Macros",  "Global", "",   "List macro(s)",   "",      cmd_macros},
#ifdef CLEARSCREEN
    { "Cls",     "Global", "",   "Clear Screen",    "",      cmd_cls},
#endif
    { "Exit",    "Global", "",   "Exit Subsystem",  "",      cmd_exit},
    { "Help",    "Global", "%s", "Help",            "",      cmd_help}
};

static int cmd_last = 10; // number of commands in cmd_tbl

static struct esc_st esc_tbl[ESC_TBL_LEN] = {
    { "\033[A",    EID_CURSOR_UP    },
    { "\033[B",    EID_CURSOR_DOWN  },
    { "\033[C",    EID_CURSOR_RIGHT },
    { "\033[D",    EID_CURSOR_LEFT  }
};


/*-----------------------------------------------------------------------------
 * Dump a line of help
 */
void DumpHelpLine(const char *pre,int ndx) {
    int  j;
    int  k=0;
    int  lastmod = 0;

    fputs(pre, stdout);
    k+=strlen(pre);

    if (k==0) {
        printf("%12s",cmd_tbl[ndx].cmdstr);
        k+=12;
    } else {
        printf("%s",cmd_tbl[ndx].cmdstr);
        k+=strlen(cmd_tbl[ndx].cmdstr);
    }

    if (strlen(cmd_tbl[ndx].parms)) {
        printf(" ");
        k++;
    }

    for (j=0;j<strlen(cmd_tbl[ndx].parms);j++) {
           switch (cmd_tbl[ndx].parms[j]) {
        case '%' :  lastmod=0;
                    break;

        case 'l' :  break;

        case 'd' :
        case 'i' :  printf("longint");
                    k+=7;
                    break;

        case 'u' :  printf("ulongint");
                    k+=8;
                    break;

        case 'g' : printf("double");
                    k+=6;
                    break;

        case 'c' :  printf("char");
                    k+=4;
                    break;

        case 's':   printf("string");
                    k+=6;
                    break;

        case ' ' :  printf(" ");
                    k++;
                    break;
        }
    }

    for (j=k;j<40;j++) printf(" ");

    if (cmd_tbl[ndx].subs[0] == '\0') {
        if (ndx==subsystem) {
            printf("- %s (active subsystem)\n",cmd_tbl[ndx].cmddescr);
        } else {
            printf("- %s (dormant subsystem)\n",cmd_tbl[ndx].cmddescr);
        }
    } else if (isa_global_cmd(ndx)) {
        printf("- %s (global command)\n",cmd_tbl[ndx].cmddescr);
    } else {
        printf("- %s\n",cmd_tbl[ndx].cmddescr);
    }

    if (strlen(pre)>0 && strlen(cmd_tbl[ndx].parmdescr)) {
        printf("Params: %s",cmd_tbl[ndx].parmdescr);
        printf("\n");
    }
}

/*------------------------------------------------------------------------------
 * Write the commands to the console in Windows ini file format
 */
void dumpcommands() {
    int  ndx;
    int  j;
    int  k=0;
    int  lastmod = 0;

    for (ndx=0;ndx<cmd_last;ndx++) {
        printf("[command%2.2d]\n",ndx+1);

        if (isa_subsystem_cmd(ndx)) {
            printf("type=Subsystem\n");
            printf("subsystem=Global\n");
        } else if (isa_global_cmd(ndx)) {
            printf("type=GlobalCommand\n");
            printf("subsystem=Global\n");
        } else {
            printf("type=Command\n");
            printf("subsystem=%s\n",cmd_tbl[ndx].subs);
        }
        printf("command=%s\n",cmd_tbl[ndx].cmdstr);
        printf("helpmsg=%s\n",cmd_tbl[ndx].cmddescr);
        printf("parameters=");
        for (j=0;j<strlen(cmd_tbl[ndx].parms);j++) {
               switch (cmd_tbl[ndx].parms[j]) {
            case '%' :  lastmod=0;
                        break;

            case 'b' :     lastmod=8;
                        break;
            case 'h' :     lastmod=16;
                        break;
            case 'l' :     lastmod=32;
                        break;

            case 'd' :
            case 'i' :     {
                            switch (lastmod) {
                            case  0 :
                            case 16 :     printf("int");
                                         k+=3;
                                         break;
                            case  8 :     printf("shortint");
                                         k+=8;
                                         break;
                            case 32:     printf("longint");
                                         k+=7;
                                         break;
                            }
                            break;
                        }

            case 'u' :
            case 'o' :
            case 'x' :     {
                            switch (lastmod) {
                            case  0 :
                            case 16 :     printf("word");
                                         k+=4;
                                         break;
                            case  8 :     printf("byte");
                                         k+=4;
                                         break;
                            case 32 :     printf("dword");
                                         k+=5;
                                         break;
                            }

                            switch (cmd_tbl[ndx].parms[j]) {
                            case 'o' :     printf("[o]");
                                        k+=3;
                                        break;
                            case 'x' :     printf("[h]");
                                        k+=3;
                                        break;
                            }

                            break;
                        }

            case 'e' :
            case 'f' :
            case 'g' :     printf("float");
                        k+=5;
                        break;

            case 'c' :     printf("char");
                        k+=4;
                        break;

            case 's' :     printf("string");
                        k+=6;
                        break;

            case ' ' :     printf(" ");
                        k++;
                        break;
            }
        }
        printf("\n");
        printf("syntax=%s\n",cmd_tbl[ndx].parmdescr);
    }
}

/*------------------------------------------------------------------------------
 * Initialize the command buffer and index.
 */
void cmdb_init(unsigned char full) {
    cmdndx = 0;
    cmdbuf[cmdndx] = '\0';

    if (full) {
        lstbuf[cmdndx] = '\0';
        macro_ptr         = -1;
        macro_buf[0]     = '\0';
    }

    escndx = 0;
    escbuf[escndx] = '\0';
}

/*------------------------------------------------------------------------------
 * Prompt for a command and display the current command buffer.
 */
void cmdb_prompt(void) {
    if (subsystem!=-1) {
        printf("%s> ",cmd_tbl[subsystem].cmdstr);
    } else {
        fputs(prompt, stdout);
    }
}

/*------------------------------------------------------------------------------
 * Build a command string.  This functions gets characters from the serial buffer
 * and appends them to the end of the command buffer.  If no character is available
 * the function returns NULL.  If a newline character is read, a pointer to the
 * buffer is returned.  Do NOT reinvoke this function before extracting the command
 * from the buffer.
 */
void cmdb_scan(char c) {
    // printf("|%c=%d|", c, c);
    if (c == '\n') {                    // Newline?
        putchar('\n');
        if (cmdndx) {
            strncpy(lstbuf,cmdbuf,cmdndx);
            lstbuf[cmdndx]='\0';
            cmd_proc(cmdbuf);
        }
        cmdb_init(FALSE);
        cmdb_prompt();
        return;                         // Return the buffer address
    }

    if (c == '\b' || c == DELETE) {
        if (cmdndx != 0) {              // Backspace?
            fputs(bs, stdout);
            cmdbuf[--cmdndx] = '\0';
        } else {
            putchar(BELL);              // Output char
        }
        return;
    }

    if (c == '\033' || escndx ) {                     // Wait for escape
        escbuf[escndx++] = (unsigned char) c;         // Add to the buffer
        if (escndx >= MAX_ESC_LEN)                    // avoid buffer overflow
            escndx = MAX_ESC_LEN - 1;
        escbuf[escndx]   = '\0';                      // NULL-Terminate buffer
        if (isalpha(c)) {
            switch (escid_search(escbuf)) {
            case EID_CURSOR_LEFT    : {
                                        if (cmdndx != 0) {   // Backspace?
                                            fputs(bs, stdout);
                                            cmdbuf[--cmdndx] = '\0';
                                        } else {
                                            putchar(BELL);   // Output char
                                        }
                                        break;
                                      }
            case EID_CURSOR_UP      : {
                                        int i;
                                        for (i=0;i<cmdndx;i++) {
                                            fputs(bs, stdout);
                                        }
                                        cmdndx=strlen(lstbuf);
                                        strncpy(cmdbuf,lstbuf,cmdndx);
                                        cmdbuf[cmdndx]='\0';
                                        fputs(cmdbuf, stdout);
                                        break;
                                      }
            case EID_CURSOR_RIGHT   : break;
            case EID_CURSOR_DOWN    : break;
            case EID_LAST           : break;
            }
            escndx=0;
            escbuf[escndx]   = '\0';        // NULL-Terminate buffer
        }
        return;
    }

    if (!isprint (c)) {                     // Printable character?
        putchar(BELL);
        return;
    }

    if (cmdndx >= MAX_CMD_LEN) {            // Past buffer length?
        putchar(BELL);
        return;
    }

    cmdbuf[cmdndx++] = (unsigned char) c;   // Add to the buffer
    cmdbuf[cmdndx]   = '\0';                // NULL-Terminate buffer
    putchar(c);
}


/* add a new command to the command set
 *  name - the name of the command
 *  subs - the subsystem containing the command, if any, otherwise "Global"
 *  parms - format string to parse parameters. %s, %g, and %lu are supported.
 *  desc - description of the command printed by Help
 *  pdesc - description of the parameters
 *  func - implementation of the command. func will be called with no
 *           parameters when the command is invoked. parms[] contains
 *           integer parameters (if any), and argstr_buf contains a
 *           string parameter. This implementation supports either one
 *           string parameter or up to 8 long and double parameters.
 * returns: 1 if successful, 0 if command table is full
 */
int cmdb_add_cmd(char *name, char *subs, char *parms, char *desc, 
                 char *pdesc, void (*func)())
{
    if (cmd_last < MAX_CMD) {
        cmd_tbl[cmd_last].cmdstr = name;
        cmd_tbl[cmd_last].subs = subs;
        cmd_tbl[cmd_last].parms = parms;
        cmd_tbl[cmd_last].cmddescr = desc;
        cmd_tbl[cmd_last].parmdescr = pdesc;
        cmd_tbl[cmd_last].cmd_ptr = func;
        cmd_last++;
        return 1;
    }
    return 0;
}


/*------------------------------------------------------------------------------
 * determine if an index is that of a global command
 */
int isa_global_cmd(int i)
{
    return (i >= 0 && strcmp(cmd_tbl[i].subs, "Global") == 0);
}


/*------------------------------------------------------------------------------
 * determine if an index is that of an enter subsystem command
 */
int isa_subsystem_cmd(int i)
{
    return (i >= 0 && cmd_tbl[i].subs[0] == '\0');
}


/*------------------------------------------------------------------------------
 * determine if an index is that of a subsystem command
 */
int is_subcommand_of(int i, int subsystem)
{
    return (subsystem > -1 && // subsystem is active and this cmd is in it
            strcmp(cmd_tbl[i].subs, cmd_tbl[subsystem].cmdstr) == 0);
}


/*------------------------------------------------------------------------------
 * determine if an index is that of a subsystem command for currently 
 *   active subsystem
 */
int is_active_subsystem_cmd(int i)
{
    return is_subcommand_of(i, subsystem);
}


/*------------------------------------------------------------------------------
 * This function searches the cmd_tbl for a specific command and returns the 
 * index associated with that command or cmd_last if there is no matching 
 * command. Assuming the command name matches, we accept it if it is a 
 * subcommand of the currently active subsystem, or, if there is no active 
 * subsystem, the command can be either a subsystem name (enter that 
 * subsystem) or a global command.
 */
static unsigned char cmdid_search (char *cmdstr)
{
    unsigned char i;

    for (i=0; i<cmd_last; i++) {
        if ((strcasecmp(cmd_tbl[i].cmdstr, cmdstr) == 0) && 
            (is_active_subsystem_cmd(i) || isa_global_cmd(i) ||
             (subsystem == -1 && // we're in global mode
              isa_subsystem_cmd(i))))
            return i;
    }

    return cmd_last;
}

unsigned char escid_search (const char *escstr) {
      unsigned char i;

    for (i=0; i<ESC_TBL_LEN; i++) {
          if (strcmp (esc_tbl[i].escstr, escstr) == 0)
               return (esc_tbl[i].id);
      }

    return (EID_LAST);
}

/*------------------------------------------------------------------------------
 * This function processes the cmd command.
 */
#define MIN_BYTE  -128
#define MAX_BYTE  +127

#define MIN_SHORT -32768
#define MAX_SHORT +32767

#define MIN_INT   -32768
#define MAX_INT   +32767

void cmd_test_hello()
{
    fputs("[Test:Hello]\n", stdout);
    printf("Hello %s\n", argstr_buf);
}


void cmd_test_cmdline()
{
    //%lu %lu %lu %lu %lu %bu
    fputs("[Test:CmdLine]\n", stdout);
    printf("0=%lu\n",ULONGPARM(0));
    printf("1=%lu\n",ULONGPARM(1));
    printf("2=%lu\n",ULONGPARM(2));
    printf("3=%lu\n",ULONGPARM(3));
    printf("4=%lu\n",ULONGPARM(4));
    printf("5=%lu\n",ULONGPARM(5));
}


void cmd_quit()
{
    IOcleanup();
    exit(0);
}


void cmd_commands()
{
    dumpcommands();
}


#ifdef HEXDUMP
void cmd_hexdump()
{
    //Intel Hexdump
    WriteIntelHex((void *)0+ULONGPARM(0),ULONGPARM(1),ULONGPARM(2));
}
#endif


void cmd_macro()
{
    macro_ptr=-1;
    strncpy(macro_buf, argstr_buf, sizeof(macro_buf) - 1);
}


void cmd_run()
{
    macro_ptr=0;
}


void cmd_macros()
{
    fputs("[Macro]\n", stdout);
    if (macro_buf[0]) {
        printf("Macro is: %s\n",macro_buf);
    } else {
        fputs(";No Macro Defined\n", stdout);
    }
}


#ifdef CLEARSCREEN
void cmd_cls()
{
    //Send VT-100 ClearScreen
    // (only works for terminals with VT100 emulation)
    fputs(cls, stdout);
}
#endif


void cmd_exit()
{
    //Returns to CMD> prompt where most commands are disabled.
    subsystem = -1;
}


void cmd_help()
{
    int cmd_index;
    int i;

    fputs("\n", stdout);

    if (argfnd>0) {
        cmd_index = cmdid_search(argstr_buf);
    } else {
        cmd_index=cmd_last;
    }

    if (argfnd>0 && cmd_index!=cmd_last) {
        //Help with a valid command as first parameter

        if (isa_subsystem_cmd(cmd_index)) {
            printf("%s subsystem commands:\n\n",cmd_tbl[cmd_index].cmdstr);
            for (i=0;i<cmd_last;i++) {
                if (is_subcommand_of(i, cmd_index)) {
                    DumpHelpLine("",i);
                }
            }
        } else if (isa_global_cmd(cmd_index)) {
            //Dump command only
            DumpHelpLine("Syntax: ",cmd_index);
        } else {            
            printf("%s subsystem command:\n\n",cmd_tbl[cmd_index].subs);
            DumpHelpLine("Syntax: ",cmd_index);
        }
    } else {
        if (argfnd>0) {
            //Help with invalid command as first parameter
            printf("Unknown command \"%s\", type \"Help\" for a list of available commands.\n",
                  argstr_buf);
        } else {
            //Dump Active Subsystem, Global & Other (dormant) Subsystems
            for (i=0;i<cmd_last;i++) {
                if (isa_subsystem_cmd(i) || isa_global_cmd(i) ||
                    is_active_subsystem_cmd(i)) {
                    DumpHelpLine("",i);
                }
            }
        }
    }
    fputs("\n", stdout);
}


void cmd_proc(const char *cmd)
{
    //Command
    char cmdstr_buf[1 + MAX_CMD_LEN];

    //Parameters
    char *argsep;

    int  argcnt;

    unsigned char id;
    unsigned int  i,j;
    unsigned int cmd_index;

    ////////////////////////////////////////////
    ////////////// PARSE COMMAND ///////////////
    ////////////////////////////////////////////

    //Watch out, sscanf fails without this
    memset(cmdstr_buf, 0, sizeof(cmdstr_buf));
    memset(argstr_buf, 0, sizeof(argstr_buf));

    //Make it worse in Lint
    for (i=0;i<MAXARGS;i++) {
        parms[i]=0;
    }

    /*------------------------------------------------
    First, copy the command and convert it to all
    uppercase.
    ------------------------------------------------*/

    strncpy(cmdstr_buf, cmd, sizeof(cmdstr_buf) - 1);
    cmdstr_buf[sizeof(cmdstr_buf) - 1] = '\0';

    /*------------------------------------------------
    Next, find the end of the first thing in the
    buffer.  Since the command ends with a space,
    we'll look for that.  NULL-Terminate the command
    and keep a pointer to the arguments.
    ------------------------------------------------*/

    argsep = strchr(cmdstr_buf, ' ');

    if (argsep == NULL) {
        argstr_buf[0] = '\0';
    } else {
        strcpy(argstr_buf, argsep + 1);
        *argsep = '\0';
    }

    /*------------------------------------------------
    Search for a command ID, then switch on it.  Note
    that I removed my action items for each command,
    but you would invoke each function here.
    ------------------------------------------------*/

    cmd_index = cmdid_search(cmdstr_buf);

    ////////////////////////////////////////////
    ////////// PARSE & TEST ARGUMENTS //////////
    ////////////////////////////////////////////

    if (strlen(cmdstr_buf)) {

        //zero argument count
        argcnt=0;
        argfnd=0;

        if (cmd_index<cmd_last) {
            int len = strlen(cmd_tbl[cmd_index].parms);
            int stringparam = 0; // is the parameter a string?
            for (j=0;j<len;j++) {
                if (cmd_tbl[cmd_index].parms[j]=='%') {
                    argcnt++;
                }
                if (cmd_tbl[cmd_index].parms[j]=='s') {
                    stringparam = 1;
                }
            }

            // TODO Strings only allowed as the only parameter
            if (!stringparam) {
                argfnd=sscanf(argstr_buf,cmd_tbl[cmd_index].parms,&parms[0],&parms[1],
                              &parms[2],&parms[3],&parms[4],&parms[5],&parms[6],
                              &parms[7]);
            } else { // string param (if any) is already in argstr_buf
                argfnd = (argstr_buf[0] ? 1 : 0);
            }

            // printf("argcnt=%d,argfnd=%d\n",argcnt,argfnd);

            if (strlen(cmd_tbl[cmd_index].parms)==0 && strlen(argstr_buf)!=0 ) {
                //printf("Warning: Command doesn't take parameters.\n");
                //Force Command Syntax Display by makeing argcnt<>argfnd.
                argfnd=argcnt+1;
            }

            ////////////////////////////////////////////
            /////// COMMAND IMPLEMENTATION AHEAD ///////
            ////////////////////////////////////////////

            //test for more commandline than allowed too.
            //i.e. run 1 is wrong.
            // Always accept "Help ...", otherwise requre parameter count match
            if ((strcmp(cmd_tbl[cmd_index].cmdstr, "Help") == 0) || (argcnt==argfnd)) {
                if (cmd_tbl[cmd_index].subs[0] == '\0') { // this is a subsystem
                    subsystem = cmd_index;
                } else {
                    (*cmd_tbl[cmd_index].cmd_ptr)();
                }
            } else {
                fputs("Incorrect number of parameters.\n", stdout);
            }
        } else {
          fputs("Unknown command, type \"Help\" for a list of available commands.\n", stdout);
        }
    }
}
