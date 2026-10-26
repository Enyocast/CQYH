#ifndef _RUNE_DATA_H_
#define _RUNE_DATA_H_

#include "data_manager.h"

struct RUNE_DATA
{
    INT32 nRuneID;
    INT32 nSpellID;
    INT32 nRuneSlot;
    UINT32 dwWeight;
    INT32 nClass;
    INT32 nLevel;
	INT32 nPriority;
    INT32 nBroadCast;
    INT32 nDropLimitDuration;
    INT32 nDropLimitCount;
    INT32 nGroup;
    char szRuneName[256];
	INT32 nHandbookType;
	INT32 nHandbookIndex;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, RUNE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _RUNE_DATA_H_
