#ifndef _STD_TYPE_H_
#define _STD_TYPE_H_

#ifdef _M_X64
    #ifndef WIN64
        #define WIN64
    #endif
#endif

#if defined(__linux__)
    #define LINUX32
        #if defined(__x86_64__)
        #undef  LINUX32
        #define LINUX64
    #endif
#endif //__linux__

#if defined(WIN32) | defined(WIN64)
    #include <wtypes.h>
    #pragma warning(disable:4996) // suppress VS 2005 deprecated function warnings
    #pragma warning(disable:4786) // for string

    typedef UINT64   NAMEID;
#endif  // WIN32

#endif  // _STD_TYPE_H_