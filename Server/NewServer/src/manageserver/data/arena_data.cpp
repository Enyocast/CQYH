#include "stdafx.h"
#include "arena_data.h"

BOOL ARENA_SCORE::ReadLine(INT32& rnID, const char*& rpcszName, ARENA_SCORE* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

	READ_INT("ScoreDiff", nScoreDiff);
	READ_INT("GainScore", nGainScore);

    READ_END(nScoreDiff);
}
