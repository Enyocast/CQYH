#ifndef _MODIFIER_FILE_DEF_H_
#define _MODIFIER_FILE_DEF_H_

#include "modifier_def.h"

#define MODIFIER_FILE_EXT_NAME		"mdf"
#define MODIFIER_FILE_TAG			0x46434B4D
#define MODIFIER_FILE_VERSION		(4)
#define MODIFIER_MAX_NAME			(128)


#pragma pack(push, 1)

struct MODIFIER_FILE_HEADER
{
    UINT32	dwTag;				// MODIFIER_FILE_TAG
    UINT32	dwVersion;			// MODIFIER_FILE_VERSION
    INT32	nBlockCount;
};


//struct MODIFIER_PARAM
//{
//	INT32 nParam;
//	INT32 nXType;
//	char szEnumName[128];
//};

struct MODIFIER_PARAM_NEW
{
	INT32 nXType;
	char szParam[1024];
};

//struct MODIFIER_FILE_NODE
//{
//	INT32	nType;				// in modifier_def.h, MODIFIER_TARGET_TYPE
//	INT32	nParentNode;
//	INT32	nTrueRetNode;
//	INT32	nFalseRetNode;
//	INT32	nNextNode;
//	INT32	nKey;
//	MODIFIER_PARAM Param[3];
//};

struct MODIFIER_FILE_NODE_NEW
{
	INT32	nType;				// in modifier_def.h, MODIFIER_TARGET_TYPE
	INT32	nParentNode;
	INT32	nTrueRetNode;
	INT32	nFalseRetNode;
	INT32	nNextNode;
	INT32	nKey;
	char	szObjName[MODIFIER_MAX_NAME];
	MODIFIER_PARAM_NEW Param[MODIFIER_PARAM_COUNT];
};

#pragma pack(pop)
// File Content:
//	|- MODIFIER_FILE_HEADER -|- MODIFIER_NODE(0) -|- MODIFIER_NODE(1) -|- MODIFIER_NODE(2) -|........|- MODIFIER_NODE(n) -|

#endif // _modifier_file_def_h__

