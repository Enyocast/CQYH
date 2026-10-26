#include "stdafx.h"
#include "guild_activity.h"

BOOL GUILD_ACTIVITY_DATA::ReadLine(INT32& rnID, const char*& rpcszName, GUILD_ACTIVITY_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("Type", nType);
    READ_INT("Level", nLevel);
    READ_INT("GuildVariableIndex", nGuildVariableIndex);
    READ_INT("LastTime", nLastTime);
    READ_INT("RepeatNum", nRepeatNum);
    READ_INT("BaseBuildingType", nBaseBuildingType);
    READ_INT("BaseBuildingLevel", nBaseBuildingLevel);
    READ_INT("ConsumeMoney", nConsumeMoney);
    READ_INT("ConsumeHerb", nConsumeHerb);
    READ_INT("ConsumeWood", nConsumeWood);
    READ_INT("ConsumeCrystal", nConsumeCrystal);
    READ_INT("ConsumeSilver", nConsumeSilver);
    READ_INT("CLTLightingID", ncltLightingID);

    rnID = GUILD_ACTIVITY_ID(pData->nType, pData->nLevel);
    return TRUE;
Exit0:
    return FALSE;
}

