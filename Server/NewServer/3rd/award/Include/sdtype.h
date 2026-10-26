/******************************************************************************
            Copyright (C) Shanda Corporation. All rights reserved.

 该文件中定义了SGDP中的的基本数据类型，包括1、2、4、8字节有符号及无符号数据类型.
 SGDP中的所有数据类型将使用这里定义的类型，以避免int之类基础类型在各平台上长度不
 统一造成的错误。

******************************************************************************/

#ifndef SGDP_SDTYPE_H_20070601
#define SGDP_SDTYPE_H_20070601

#include <stdlib.h>
//
// 1字节有符号类型
//
typedef signed char         INT8;

//
// 1字节无符号类型
//
typedef unsigned char       UINT8;

//
// 2字节有符号类型
//
typedef signed short        INT16;

//
// 2字节无符号类型
//
typedef unsigned short      UINT16;

//
// 4字节有符号类型
//
typedef signed int          INT32;

//
// 4字节无符号类型
//
typedef unsigned int        UINT32;

//
// 4字节无符号类型
//
typedef long   LONG;

//
// 4字节无符号类型
//
typedef long unsigned    ULONG;

#ifdef WIN32
//
// 8字节有符号类型
//
typedef signed __int64		INT64;

//
// 8字节无符号类型
//
typedef unsigned __int64	UINT64;
#else
//
// 8字节有符号类型
//
typedef signed long long	INT64;

//
// 8字节无符号类型
//
typedef unsigned long long	UINT64;
#endif

//
// printf 中的格式字符串定义，例如
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
