#include "stdafx.h"
#include "guild_achievement.h"


BOOL GUILD_ACHIEVEMENT::ReadLine(INT32& rnID, const char*& rpcszName, GUILD_ACHIEVEMENT* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT_EXPR("ID", nID);

    for (INT32 i = 0; i < GuildAchiCdtnTableSize; ++i)
    {
        char szFieldName[256];
        snprintf(szFieldName, 256, "ConditionType%d", i + 1);
        READ_INT_EXPR(szFieldName, CdtnData[i].nCdtnType);

        memset(szFieldName, 0, 256);
        snprintf(szFieldName, 256, "Param%d", i + 1);
        READ_INT(szFieldName, CdtnData[i].nParam1);
    }

    for (INT32 i = 0; i < GuildAchiAwardTableSize; ++i)
    {
        char szFieldName[256];
        snprintf(szFieldName, 256, "AwardType%d", i + 1);
        READ_INT_EXPR(szFieldName, AwardData[i].nAwardType);

        memset(szFieldName, 0, 256);
        snprintf(szFieldName, 256, "TemplateID%d", i + 1);
        READ_INT(szFieldName, AwardData[i].dwTemplateID);

        memset(szFieldName, 0, 256);
        snprintf(szFieldName, 256, "Num%d", i + 1);
        READ_INT(szFieldName, AwardData[i].nNum);
    }

    READ_END(nID);
}


const GUILD_ACHIEVEMENT * GetGuildAchievement(INT32 nID)
{
    return CDataManager<GUILD_ACHIEVEMENT>::GetInstance().GetData(nID);
}




