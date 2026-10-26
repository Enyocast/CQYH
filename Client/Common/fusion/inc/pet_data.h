#ifndef _PET_DATA_H_
#define _PET_DATA_H_

#include "tabfile.h"

#define PET_ID(__type__, __level__)		(((__type__) << 16) | (__level__))

// tolua_begin

struct PET_DATA
{
	INT32	nID;
    INT32   nAIID;
    INT32   nBornType;
	INT32	nLevel;
    INT32   nAccurate;
    INT32   nBonusphyAtkMax;
    INT32   nBonusHPMaxA;
    INT32   nBonusHPMaxB;
    INT32   nMagDef;
    INT32   nMagDefMax;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, PET_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

const PET_DATA* GetPetData(INT32 nType, INT32 nLevel);

// tolua_end

#endif	// _PET_DATA_H_