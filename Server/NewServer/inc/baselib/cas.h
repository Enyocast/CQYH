#ifndef _CAS_H_
#define _CAS_H_

#if defined(WIN32)
	inline INT32 _EVA32(INT32 volatile* pDest, INT32 Value)
	{
		return InterlockedExchange((LONG*)pDest, Value);
	}
    inline INT32 _CAS32(INT32 volatile* pDestination, INT32 Exchange, INT32 Comparand)
    {
        return InterlockedCompareExchange((LONG*)pDestination, Exchange, Comparand);
    }
    inline INT64 _CAS(INT64 volatile* pDestination, INT64 Exchange, INT64 Comparand)
    {
        return InterlockedCompareExchange64(pDestination, Exchange, Comparand);
    }

//#elif defined(LINUX32) 
#elif defined(__linux__) 
    inline INT32 _EVA32(INT32 volatile* pDest, INT32 Value)
    {
        return __sync_lock_test_and_set(pDest, Value);
    }
    inline INT32 _CAS32(INT32 volatile* pDestination, INT32 Exchange, INT32 Comparand)
    {
        return 0;
    }
    inline INT64 _CAS(INT64 volatile* pDestination, INT64 Exchange, INT64 Comparand)
    {
		return __sync_val_compare_and_swap(pDestination, Comparand, Exchange );
    }
#else
    #error("unknown os")
#endif 

#endif  // _CAS_H_
