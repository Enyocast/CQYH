#ifndef __LINUX_COMPATIBLE_H__
#define __LINUX_COMPATIBLE_H__

#if defined(WIN32)

    #include <conio.h>
    #include <signal.h>

#elif defined(__linux__)

    #include <string.h>
    #include <stdio.h>

    #include <strings.h>
    #define strnicmp(str1, str2, n ) strncasecmp( str1, str2, n )

    #include <sys/types.h>
    #include <unistd.h>
    #define GetCurrentProcessId() getpid()  // for getpid()

    #define Sleep( Sec ) usleep( (Sec) * 1000 )

    typedef unsigned long       DWORD;
    typedef unsigned short      WORD;
    #define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD)(b)) & 0xff))) << 8))
    #define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD)(b)) & 0xffff))) << 16))
    #define LOWORD(l)           ((WORD)(((DWORD)(l)) & 0xffff))
    #define HIWORD(l)           ((WORD)((((DWORD)(l)) >> 16) & 0xffff))

    int kbhit(void);
    int getch(void);

    unsigned GetTickCount(void);// or use SDGetTickCount() as substitution

    #ifndef INT_MAX
        #define INT_MAX ((1<<31)-1)
    #endif
    #ifndef LLONG_MAX
        #define LLONG_MAX ((1LL<<63)-1)
    #endif

#endif // WIN32

#endif //__LINUX_COMPATIBLE_H__
