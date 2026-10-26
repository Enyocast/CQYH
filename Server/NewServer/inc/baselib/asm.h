#ifndef _ASM_H_
#define _ASM_H_

#if defined(WIN32) | defined(WIN64)
#include <Windows.h>

inline unsigned long long RDTSC(void)
{
    return __rdtsc();
}

inline void INT3(void)
{
	__debugbreak();
}

#ifdef _DEBUG
#define INT3_DBG()	INT3()
#else
#define INT3_DBG()
#endif	// _DEBUG

#else  // !WIN32

#endif  // !WIN32

#endif  //_ASM_H_
