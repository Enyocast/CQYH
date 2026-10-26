/********************************************************************
	created:	2:9:2013   15:13
	file:		guild_building_data.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_GUILD_BUILDING_DATA_H_
#define _H_GUILD_BUILDING_DATA_H_


#include "string_def.h"
#include "data_manager.h"


//tolua_begin

struct GUILD_BUILDING_DATA 
{
    UINT32      dwID;
    INT32       nLevel;
    INT32       nMaxLevel;
    INT32       nMaxNum;
    INT32       nProsperity;
    INT32       nMoneyConsumption;
    INT32       nTotalMoneyConsumption;
    INT32       nHerbConsumption;
    INT32       nTotalHerbConsumption;
    INT32       nWoodConsumption;
    INT32       nTotalWoodConsumption;
    INT32       nCrystalConsumption;
    INT32       nTotalCrystalConsumption;
    INT32       nSilverConsumption;
    INT32       nTotalSilverConsumption;
    INT32       nUpgradeTime;
    INT32       nRoutineConsumption;
    UINT32      dwCdtnBaseNpcID;
    UINT32      dwConditionBuildingID;
    INT32       nConditionBuildingLvl;
    UINT32      dwUpgradingSpellID;
    UINT32      dwNpcTemplateID;
    UINT32      dwDeadNpcTemplateID;
    UINT32      nReviveTime;
    INT32       nParam1;
    INT32       nParam2;
    INT32       nParam3;
    INT32       nParam4;
    INT32       nParam5;
    UINT32      dwIntruderMsgID;
    UINT32      dwDefenderMsgID;
    UINT32      dwFewMembersReward;
    UINT32      dwSomeMembersReward;
    UINT32      dwManyMembersReward;

    static BOOL HasName(void)	{ return FALSE; }

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, GUILD_BUILDING_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};



//tolua_end


const GUILD_BUILDING_DATA * GetGuildBuildingData(UINT32 dwType, INT32 nLevel);



#endif //_H_GUILD_BUILDING_DATA_H_



