#ifndef   __ADUC_H__
#define   __ADUC_H__

#include <string.h>
#include <ctype.h>

#define BYTE unsigned char
#define WORD unsigned short

/*----------------------------------------------------------------------------
 * No Trace Output on ONBOARD Serial Port
 */
#undef TRACE

#define ADUC_VER  "1.0.0"

/*----------------------------------------------------------------------------
 * Support Function Prototypes
 */
extern char         ReadIntCh(void);
extern void         WriteIntCh(unsigned char ch);

extern void         reset(void);         // Resets Program
extern void         ZeroMemory(unsigned char *p,unsigned int siz);
extern void         delay(unsigned int ms);
extern void         GetBuildNumber(char *build);

extern BYTE         commask;            // Actual Commask

#endif
