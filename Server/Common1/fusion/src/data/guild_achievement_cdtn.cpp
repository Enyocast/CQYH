#include "stdafx.h"
#include "guild_achievement_cdtn.h"


BOOL GUILD_ACHI_CDTN::ReadLine(INT32& rnID, const char*& rpcszName, GUILD_ACHI_CDTN* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT_EXPR("CdtnType", nCdtnType);
    READ_INT("Param", nParam1);
    READ_INT("Pos", nPos);

    rnID = GACDTN_ID(pData->nCdtnType, pData->nParam1);

    return TRUE;
Exit0:
    return FALSE;
}

const GUILD_ACHI_CDTN * GetGuildAchiCdtn(INT32 nCdtnType, INT32 nParam1)
{
    return CDataManager<GUILD_ACHI_CDTN>::GetInstance().GetData(GACDTN_ID(nCdtnType, nParam1));
}