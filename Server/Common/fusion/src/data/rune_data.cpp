#include "stdafx.h"
#include "rune_data.h"

BOOL RUNE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, RUNE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("RuneID", nRuneID);
    READ_INT("SpellID", nSpellID);
    READ_INT("RuneSlot", nRuneSlot);
    READ_INT("Weight", dwWeight[0][0]);
    READ_INT("BossWeight1", dwWeight[1][0]);
    READ_INT("BossWeight2", dwWeight[2][0]);
    READ_INT("BossWeight3", dwWeight[3][0]);
    READ_INT("BossWeight4", dwWeight[4][0]);
    READ_INT("WorldWeight", dwWeight[5][0]);
    READ_INT("Weight_1", dwWeight[0][1]);
    READ_INT("BossWeight1_1", dwWeight[1][1]);
    READ_INT("BossWeight2_1", dwWeight[2][1]);
    READ_INT("BossWeight3_1", dwWeight[3][1]);
    READ_INT("BossWeight4_1", dwWeight[4][1]);
    READ_INT("WorldWeight_1", dwWeight[5][1]);
    READ_INT_EXPR("Class", nClass);
    READ_INT("Level", nLevel);
    READ_INT("Priority", nPriority);
    READ_INT("BroadCast", nBroadCast);
    READ_INT("LimitDuration", nDropLimitDuration);
    READ_INT("LimitCount", nDropLimitCount);
    READ_INT("Group", nGroup);
    READ_INT("Rarity", nRarity);
    READ_STR("RuneName", szRuneName);
    READ_INT("ClearGambleCount", nClearGambleCount);

	pData->nHandbookType = 0;
	pData->nHandbookIndex = 0;

    READ_END(nRuneID);
}

