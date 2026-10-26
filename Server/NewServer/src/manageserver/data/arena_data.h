#ifndef _ARENA_DATA_H_
#define _ARENA_DATA_H_

#include "data_manager.h"
#include "read_data_helper.h"

struct ARENA_SCORE
{
	INT32 nScoreDiff;
	INT32 nGainScore;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, ARENA_SCORE* pData, CTabFile* poTabConfig, INT32 nRow);
};


#endif // _arena_data_h__
