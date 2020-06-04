#ifndef   __CMD_H__
#define   __CMD_H__

#define MAX_CMD_LEN 132
#define MAX_ESC_LEN   5

#define FALSE 0
#define TRUE  1

/*----------------------------------------------------------------------------
 * Command Interpreter & Handling.
 */
#define DELETE 127
#define BELL 7

#define MAX_CMDS 50

struct cmd_st {
    const char *cmdstr;
    const char *subs;
    const char *parms;
    const char *cmddescr;
    const char *parmdescr;
    void (*cmd_ptr)();
};

//eight parms is max (limit of scanf)...
#define MAXARGS 8
long parms[MAXARGS];              // Parsed Parameters
char argstr_buf[1 + MAX_CMD_LEN]; // argument string (see cmd_add_cmd 
                          //   documentation in cmd.c and README.txt)
// how to access the parm data
#define CHARPARM(ndx)      *(char*)&parms[ndx]
#define LONGPARM(ndx)       *(long*)&parms[ndx]
#define ULONGPARM(ndx)  *(unsigned long int*)&parms[ndx]
#define DOUBLEPARM(ndx)     *(double*)&parms[ndx]


/*------------------------------------------------------------------------------
 * Escape Codes
 */
enum {
    EID_CURSOR_UP,
    EID_CURSOR_DOWN,
    EID_CURSOR_RIGHT,
    EID_CURSOR_LEFT,
    EID_LAST
};

struct esc_st {
    const char *escstr;
    unsigned char id;
};

#define ESC_TBL_LEN  4

void cmdb_init(unsigned char full);
void cmdb_prompt(void);
void cmdb_scan(char c);
/* cmdb_add_cmd - see cmd.c for documentation */
int cmdb_add_cmd(char *name, char *subs, char *parms, char *desc, 
                 char *pdesc, void (*func)());

extern char macro_buf[1 + MAX_CMD_LEN];
extern int  macro_ptr;

/*----------------------------------------------------------------------------*/

#endif
