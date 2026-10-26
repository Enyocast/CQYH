#include "stdafx.h"
#include "pet_data.h"
#include "read_data_helper.h"
#include "data_manager.h"

BOOL PET_DATA::ReadLine(INT32& rnID, const char*& rpcszName, PET_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("ID", nID);
    READ_INT("AIID", nAIID);
    READ_INT_EXPR("BornType", nBornType);
    READ_INT("Level", nLevel);
    READ_INT("HitRate", nAccurate);
    READ_INT("BonusphyAtkMax", nBonusphyAtkMax);
    READ_INT("BonusHPMaxA", nBonusHPMaxA);
    READ_INT("BonusHPMaxB", nBonusHPMaxB);
    READ_INT("MagDef", nMagDef);
    READ_INT("MagDefMax", nMagDefMax);

    rnID = PET_ID(pData->nID, pData->nLevel);
    return TRUE;
Exit0:
    return FALSE;
}

const PET_DATA* GetPetData(INT32 nType, INT32 nLevel)
{
    return CDataManager<PET_DATA>::GetInstance().GetData(PET_ID(nType, nLevel));
}
