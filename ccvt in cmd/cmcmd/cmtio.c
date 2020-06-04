/*
 **********************************************************************
 *              cmtio.c
 **********************************************************************
 *
 * Non blocking input routines.
 * 
 * IOsetup(inputfd) - start non-blocking terminal input
 * IOcleanup() - restore normal terminal input
 * IOgetchar() - get char or return IO_NOCHAR if none
 * IOwaitchar() - do a blocking input
 *
 * Works by puttng the terminal in CBREAK mode and using the FIONREAD
 * ioctl call to determine the number of characters in the input queue
 */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "cmtio.h"

int IOinputfd;  /* input file descriptor (usually 0) */

static void IOdiegracefully(int i)
{
    write(2, "\nBye\n", 5);
    IOcleanup();
    exit(2);
}

/*
 * IOwaitchar()
 *   Returns:
 *      A character of input.  Waits if necessary.
 *      If read fails, returns IO_NOCHAR.
 *      On end-of-file, returns EOF.
 */
int IOwaitchar()
{
    char c;
	int r = read(IOinputfd, &c, 1);
	if (r == 1) return c;
	else if (r == 0) return IO_NOCHAR;
    else if (r < 1) return r;
}



#ifdef __MACH__

#include <sys/types.h>
#include <sys/time.h>
#include <sgtty.h>


static  struct sgttyb IOoldmodes, IOcurrentmodes;
                /* Initial and current tty modes */

/*
 * IOsetup(inputfd)
 *   Args:
 *      inputfd - input file descriptor (should be zero for standard input)
 *   Returns:
 *      0 - if all goes well
 *      -1 - if an ioctl fails (also calls perror)
 *   Side Effects:
 *      Puts the terminal in CBREAK mode - before process termination
 *      IOcleanup() should be called to restore old terminal modes
 *      Catch's interrupts (if they are not already being caught) and
 *      calls IOcleanup before exiting
 */

#define ERROR(s) perror(s)
static void IOdiegracefully(int);

int IOsetup(int inputfd)
{
    void (*interrupt_handler)(int);

    IOinputfd = inputfd;
    if (ioctl(IOinputfd, TIOCGETP,  &IOoldmodes) < 0) {
        ERROR("IOsetup");
        return -1;
    }
    IOcurrentmodes = IOoldmodes;
    IOcurrentmodes.sg_flags |= CBREAK;
    IOcurrentmodes.sg_flags &= ~ECHO;
    if (ioctl(IOinputfd, TIOCSETP,  &IOcurrentmodes)) {
        ERROR("IOsetup-2");
        return -1;
    }
    if ((interrupt_handler = signal(SIGINT, IOdiegracefully)) != 0)
        signal(SIGINT, interrupt_handler);
    return 0;
}

/*
 * IOcleanup()
 *   Returns:
 *      0 - if all goes well
 *      -1 - if an ioctl fails (also calls perror)
 *   Side Effects:
 *      Restores initial terminal modes
 */

void IOcleanup()
{
    if (ioctl(IOinputfd, TIOCSETP,  &IOoldmodes) < 0)
        ERROR("IOclean");
}


/*
 * IOgetchar()
 *    Returns:
 *      A character off the input queue if there is one,
 *      IO_NOCHAR if there is no character waiting to be read,
 *      -1 if an ioctl fails (shouldn't happen if IOsetup went OK)
 */


int IOgetchar()
{
    int n;
    char c;

    if (ioctl(IOinputfd, FIONREAD, &n) < 0) {
        ERROR("IOgetchar");
        return -1;
    }
    if (n <= 0)
        return IO_NOCHAR;
    switch(read(IOinputfd, &c, 1)) {
    case 1:
        return c;
    case 0:
        return EOF;
    default:
        ERROR("IOgetchar-read");
        return -1;
    }
}

#ifdef IOGETCHAR2
/* This is an alternate implementation. It is here for reference or
 * future use.
 */
int IOgetchar2()
{
    int nfds, readfds = 1 << IOinputfd;
    char c;
    static struct timeval zero;

    if (IOinputfd < 0 || IOinputfd >= 32) {
        printf("IOgetchar2: bad IOinputfd (%d)%s\n", IOinputfd,
            IOinputfd == -1 ? "Did you call IOsetup(fd)?" : "");
    }
    nfds = select(32, &readfds, 0, 0, &zero);
    if (nfds > 0) {
        switch(read(IOinputfd, &c, 1)) {
        case 0:
            return EOF;
        case 1:
            return c;
        default:
            printf("IOgetchar2: read failed!\n");
            return IO_NOCHAR;
        }
    }
    else if (nfds < 0)
        printf("IOgetchar2: select failed!\n");
    return IO_NOCHAR;
}
#endif

#else /* not __MACH__ so we will assume Linux */

/* based on stackoverflow.com/questions/448944 */

#include <string.h> /* for memcpy */
#include <termios.h>

struct termios orig_termios;

void IOcleanup()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

int IOsetup(inputfd)
{
    void (*interrupt_handler)(int);
    struct termios new_termios;

    IOinputfd = inputfd;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(IOcleanup);
    if ((interrupt_handler = signal(SIGINT, IOdiegracefully)) != 0)
        signal(SIGINT, interrupt_handler);
    new_termios.c_oflag &= (OPOST | ONLCR); /* map NL to CR-NL on output */ 
    new_termios.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
    tcsetattr(0, TCSANOW, &new_termios);
	return 0;
}

int IOgetchar()
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    if (select(1, &fds, NULL, NULL, &tv)) {
        int r;
        char c;
        r = read(IOinputfd, &c, sizeof(c));
        if (r < 0) return r;
        else if (r > 0) return c;
    }
    return IO_NOCHAR;
}    
    
#endif /* __MACH__ */
