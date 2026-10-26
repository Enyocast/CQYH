#ifndef _NPC_PATTERN_H_
#define _NPC_PATTERN_H_

#include "data_manager.h"
#include "attribute_def.h"

struct NPC_PATTERN_DATA
{
	INT32 nPatternID;
	INT32 nExp;
	INT32 nSoul;
	INT32 nAttrListA[catTotal];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, NPC_PATTERN_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif	// _NPC_PATTERN_H_