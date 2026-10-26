#ifndef _CAS_H_
#define _CAS_H_

#pragma warning(push)
#pragma warning(disable:4731)

#if defined(WIN32)
	INT32 _ASN32(volatile INT32* pDest, INT32 Value);
	INT32 _CAS32(volatile INT32* pDestination, INT32 Exchange, INT32 Comparand);
    INT64 _CAS(volatile INT64* pDestination, INT64 Exchange, INT64 Comparand);
#elif defined(LINUX32) 
    INT32 _CAS32(INT32* pDestination, INT32 Exchange, INT32 Comparand);
    INT64 _CAS(INT64* pDestination, INT64 Exchange, INT64 Comparand);
#else
    #error("unknown os")
#endif 

#pragma warning(pop)

#endif  // _CAS_H_