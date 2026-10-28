#ifndef _SPIRIT_DATA_H_
#define _SPIRIT_DATA_H_

#include "data_manager.h"
#include "spirit_def.h"
#include "string_def.h"
#include "role_def.h"

struct SPIRIT_DATA
{
	// base
	INT32 nLevel;
	INT32 nNextLevelExp;										// Experience required to level up
	INT32 nSoulCost;											// Soul consumed per conversion
	INT32 nAddExp;												// Experience gained per conversion
	INT32 nAddSpiritPts;										// Cultivation points gained per conversion
	INT32 nPower;												// Combat power
	INT32 nAttrTemplateNodeID[MAX_SPIRIT_NODE_PER_LEVEL];		// Attribute template ID
	INT32 nAttrNodeID[MAX_SPIRIT_NODE_PER_LEVEL];				
	BOOL  nBroadcastStringID;									// Whether a screen announcement is required

	// Exp2Pts
	UINT32	dwDailyChangeCDTime;								// Conversion cooldown
	INT32	nOfflineChangeDiscount[vlTotal-1];					// VIP offline conversion discount
	INT32	nVipOnlineChangeDiscount[vlTotal-1];				// VIP online conversion bonus
	INT32	nMoneyCostOneShot;									// Gold cost of one-click conversion
	INT32	nDailyExp2PtsMoneyCost;								// Maximum daily cost of converting soul to cultivation points
	INT32	nDailyExp2PtsMaxCount;								// Maximum daily soul-to-cultivation conversions

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SPIRIT_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct SPIRIT_CHANGE_DATA
{
	INT32	nIndex;
	INT32	nDailyChangeTime;					// Daily completion count
	INT32	nMoneyCostDiscount;					// Gold bonus

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SPIRIT_CHANGE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct AIR_LEVEL_DATA							// Qi cultivation stage data
{
	INT32	nLevel;								// Qi cultivation stage
	INT32	nPtsCost;
	INT32	nNextLevelRate;
	INT32	nSpiritLevelLimit;					// Spirit level requirement
	INT32	nDropMoneyCount;					// Arcane qi quantity
	INT32	nClassLimit;						// Class restriction (controls the type of qi dropped)
	BOOL	nBroadcastStringID;					// Whether an announcement is required

	INT32	nDropAirID[MAX_DROP_AIR_COUNT];
	INT32	nDropAirRate[MAX_DROP_AIR_COUNT];   

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, AIR_LEVEL_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct AIR_DATA						// Qi attribute template
{
	INT32	nAirID;
	INT32	nColor;
	INT32	nLevel;					// Qi level
	INT32	nExp;					// Initial experience
	INT32	nNextLevelExp;			// Experience required to level up
	INT32	nNextLevelID;
	INT32	nExchangeCount;			// Arcane qi exchange quantity
	INT32	nGroupID;				// Group ID; only one qi from the same group can be equipped
	INT32	nBroadcastStringID;			// Whether an announcement is required

	INT32	nHandbookType;	
	INT32	nHandbookIndex;		

	INT32	nNodeTemplateID[MAX_ATTR_PER_NODE];
	INT32	nNodeID[MAX_ATTR_PER_NODE];
	char	szAirname[AIR_NAME_LEN];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, AIR_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct BLOOD_DATA												// Bloodline
{
	INT32	nPage;
	INT32	nSlot;
	INT32	nNumber;

	INT32	nSpiritPtsCost;
	INT32	nRate;												// Probability of rolling 10
	INT32	nLevelLimit;										// Required spirit level

	INT32	nPageLevelLimit;									// Character level required to unlock this bloodline

	INT32	nAttrTemplateNodeID[MAX_BLOODSEA_ATTR_PER_SLOT];	// Attributes
	INT32	nNodeID[MAX_BLOODSEA_ATTR_PER_SLOT];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, BLOOD_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct SPIRIT_SLOT_DATA
{
	INT32	nSlotIndex;
	INT32	nLevelLimit;
	INT32	nMoneyCost;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SPIRIT_SLOT_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _SPIRIT_DATA_H_