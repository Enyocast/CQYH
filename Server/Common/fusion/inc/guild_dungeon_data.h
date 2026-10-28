/********************************************************************
	created:	15:10:2013   13:41
	file:		guild_dungeon_data.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_GUILD_DUNGEON_H_
#define _H_GUILD_DUNGEON_H_

#include "string_def.h"
#include "data_manager.h"
#include "guild_def.h"

static const INT16  GuildDungeonDropGroupCount = GUILD_DUNGEON_AWARD_NUM;
static const INT16  GuildDungeonAwardTableSize = 5; 

struct GUILD_DUNGEON_DATA 
{
    struct GD_DROUP_GROUP 
    {
        INT32       nChance;
        UINT32      dwGroupID;
    };

    UINT32      dwSceneTemplateID;
    INT32       nFatigueComsume;
    INT32       nConditionLevel;
    UINT32      dwConditionBuildingID;
    INT32       nConditionBuildingLevel;
    INT32       nConditionMoney;
    INT32       nBestTeammateNum;
    INT32       nPosX;
    INT32       nPosY;
    INT32       nPosZ;
    INT32       nDirection;
    GD_DROUP_GROUP  arrDropGroup[GuildDungeonDropGroupCount];
    UINT32      arrAwardID[GuildDungeonAwardTableSize];

    static BOOL HasName(void)	{ return FALSE; }

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, GUILD_DUNGEON_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

const GUILD_DUNGEON_DATA * GetGuildDungeonData(UINT32 dwTemplateID);



#endif //_H_GUILD_DUNGEON_H_




