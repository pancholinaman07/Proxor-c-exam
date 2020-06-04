#define IO_NOCHAR -2

extern int IOinputfd;

int IOsetup(int inputfd);
void IOcleanup();
int IOgetchar();
int IOwaitchar();
