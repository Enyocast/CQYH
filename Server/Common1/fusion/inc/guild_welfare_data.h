/********************************************************************
	created:	2:9:2013   15:51
	file:		guild_welfare.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_GUILD_WELFARE_H_
#define _H_GUILD_WELFARE_H_

#include "string_ex.h"
#include "data_manager.h"
struct GUILD_WELFARE_DATA 
{ 
    UINT32      dwID;
    INT32       nLevel;
    UINT32      dwAuraID;
    INT32       nKind;
    
    INT32       nMaxLevel;
    INT32       nUpgradeTime;

    UINT32      dwConditionBuildingID;
    INT32       nConditionBuildingLvl;

    INT32       nPurchaseLevelRequirement;
    INT32       nPurchaseMoneyConsumption;
    INT32       nPurchaseGuildCurrencyConsumption;
    //INT32       nPurchaseLimit;         // ´ÎÊý
    INT32       arrVipPurchaseLimit[4];

    INT32       nUpgradeMoneyConsumption;
    INT32       nUpgradeHerbConsumption;
    INT32       nUpgradeWoodConsumption;
    INT32       nUpgradeCrystalConsumption;
    INT32       nUpgradeSilverConsumption;

    static BOOL HasName(void)	{ return FALSE; }

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, GUILD_WELFARE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};


const GUILD_WELFARE_DATA* GetGuildWelfareData(INT32 nType, INT32 nLevel);



#endif //_H_GUILD_WELFARE_H_




