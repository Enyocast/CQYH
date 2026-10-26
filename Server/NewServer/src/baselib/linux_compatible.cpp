#include "stdafx.h"
#include "linux_compatible.h"

#if defined(__linux__)

#include <sys/select.h>
#include <sys/time.h>
int kbhit(void)
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    fd_set fdset;
    FD_ZERO( &fdset );
    FD_SET( STDIN_FILENO, &fdset );

    select( STDIN_FILENO+1, &fdset, NULL, NULL, &tv );

    return FD_ISSET( STDIN_FILENO, &fdset );
}

#include <termios.h>
int getch()
{
    struct termios oldt;
    struct termios newt;

    int ch = 0;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO  );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

    return ch;
}

#include <sys/time.h>
unsigned GetTickCount(void)
{
    struct timeval tv;
    if( gettimeofday(&tv,NULL) != 0 )
    {
        return 0;
    }

    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#endif // __linux__