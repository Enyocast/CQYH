/******************************************************************************
            Copyright (C) Shanda Corporation. All rights reserved.

 This file defines SGDP basic types, including signed and unsigned 1-, 2-, 4- and 8-byte types.
 SGDP uses these types to avoid errors caused by basic types such as int having inconsistent
 sizes across platforms.

******************************************************************************/

#ifndef SGDP_SDTYPE_H_20070601
#define SGDP_SDTYPE_H_20070601

#include <stdlib.h>
//
// 1-byte signed type
//
typedef signed char         INT8;

//
// 1-byte unsigned type
//
typedef unsigned char       UINT8;

//
// 2-byte signed type
//
typedef signed short        INT16;

//
// 2-byte unsigned type
//
typedef unsigned short      UINT16;

//
// 4-byte signed type
//
typedef signed int          INT32;

//
// 4-byte unsigned type
//
typedef unsigned int        UINT32;

//
// 4-byte unsigned type
//
typedef long   LONG;

//
// 4-byte unsigned type
//
typedef long unsigned    ULONG;

#ifdef WIN32
//
// 8-byte signed type
//
typedef signed __int64		INT64;

//
// 8-byte unsigned type
//
typedef unsigned __int64	UINT64;
#else
//
// 8-byte signed type
//
typedef signed long long	INT64;

//
// 8-byte unsigned type
//
typedef unsigned long long	UINT64;
#endif

//
// Format string definitions for printf, for example
// printf("The int64 number is: "FMT_I64, llNumber);
// printf("The uint64 number is: "FMT_U64, qwNumber);
// printf("The uint64 number is: "FMT_64X, qwNumber);
//
#ifdef WIN32
    #define FMT_I64 "%I64"
    #define FMT_U64 "%I64u"
    #define FMT_64X "%I64x"
#else
    #define FMT_I64 "%ll"
    #define FMT_U64 "%llu"
    #define FMT_64X "%llx"
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#endif
