#include "stdafx.h"
#include "rune_data.h"

BOOL RUNE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, RUNE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("RuneID", nRuneID);
    READ_INT("SpellID", nSpellID);
    READ_INT("RuneSlot", nRuneSlot);
    READ_INT("Weight", dwWeight);
    READ_INT_EXPR("Class", nClass);
    READ_INT("Level", nLevel);
    READ_INT("Priority", nPriority);
    READ_INT("BroadCast", nBroadCast);
    READ_INT("LimitDuration", nDropLimitDuration);
    READ_INT("LimitCount", nDropLimitCount);
    READ_INT("Group", nGroup);
    READ_STR("RuneName", szRuneName);

	pData->nHandbookType = 0;
	pData->nHandbookIndex = 0;

    READ_END(nRuneID);
}

