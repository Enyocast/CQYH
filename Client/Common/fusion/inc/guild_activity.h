#ifndef _H_GUILD_ACTIVITY_DATA_H_
#define _H_GUILD_ACTIVITY_DATA_H_

#include "data_manager.h"

#define GUILD_ACTIVITY_ID(type, level)      ((type << 16) + level)

// tolua_begin
struct GUILD_ACTIVITY_DATA
{
    INT32       nType;
    INT32       nLevel;
    INT32       nGuildVariableIndex;
    INT32       nLastTime;
    INT32       nRepeatNum;
    INT32       nBaseBuildingType;
    INT32       nBaseBuildingLevel;
    INT32       nConsumeMoney;
    INT32       nConsumeHerb;
    INT32       nConsumeWood;
    INT32       nConsumeCrystal;
    INT32       nConsumeSilver;
    INT32       ncltLightingID;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, GUILD_ACTIVITY_DATA* pData, CTabFile* pTabConfig, INT32 nRow);

};

// tolua_end


#endif // _H_GUILD_ACTIVITY_DATA_H_
