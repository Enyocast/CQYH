#ifndef _NPC_DATA_H_
#define _NPC_DATA_H_

#include "data_manager.h"
#include "string_def.h"
#include "attribute_def.h"

struct SHOP_DATA;
struct ADVENTURE_DATA;

struct NPC_DATA
{
	INT32		            nTemplateID;
	INT32					nClientTemplateID;
    char                    szDisplayName[MAX_NPC_NAME_LEN];
    char                    szName[MAX_NPC_NAME_LEN];
	INT32					nLevel;
    INT32				    nPatternID;
	INT32					nQuality;
    INT32                   nBroadcast;
    INT32                   nForceID;
    BOOL                    bReduceReputation;
	INT32				    nSpecies;
    INT32                   nRivalForceID;
	INT32					nGroupID;
	INT32					nBodyType;
	INT32					nSpellEffectGroup;

    INT32                   nSpawnTime;                 // unit: frame, table unit: ms
    INT32                   nReviveTime;                // unit: frame, table unit: ms
    INT32                   nCorpseTime;                // unit: frame
    INT32                   nMinRespawnTime;            // unit: frame
	INT32                   nMaxRespawnTime;            // unit: frame

    INT32                   nAIID;
	BOOL				    bImmunePassiveMove;
    BOOL                    bInvincible;
    BOOL                    bAlwaysRun;
	BOOL					bCanbeThrown;
	BOOL					bIgnoreInvisible;
	BOOL					bCounterInvisible;
    INT32                   nAttackRange;
    BOOL                    bExclusive;
	BOOL					bNeverBeHit;

    BOOL                    bProfit;                    //Controls whether items, experience, and soul are dropped
	INT32                   nExpRate;
    INT32                   nSoulRate;
    BOOL                    bDailyExp;                  //Controls whether experience counts toward the daily limit
	BOOL					bAuraInvalid;

	INT32					nKillPlayerVarIndex;		
	INT32					nBeKilledVarIndex;			// Player variable corresponding to killing a monster with the specified ID

    INT32                   nShopID;
    INT32                   nBlackMarketID;
	BOOL					bInteractBank;
	BOOL					bInteractGuildBank;
	BOOL					bInteractRewardQuest;
	BOOL					bInteractCreateGuild;
	BOOL					bInteractGuildSalary;
	BOOL					bInteractAuction;
	BOOL					bInteractRune;
	BOOL					bInteractSoul;
	BOOL					bInteractWeaponLevelUpPutIn;
	BOOL					bInteractWeaponLevelUpTakeOut;
	BOOL					bInteractSpecialRepair;
    BOOL                    bInteractGamble;
    BOOL                    bInteractExercise;
    BOOL                    bInteractSpellBookGamble;
    BOOL                    bInteractArenaReward;
	INT32					nCorpseDoodadID;
	BOOL					bDieIDMonitor;
    BOOL                    bStatMoney;
    INT32                   nBigDropInterval;
    INT32                   nRuneGroup;

	INT32					nHandbookType;
	INT32					nHandbookIndex;

	INT32					nKillNpcQuestID;

    const ADVENTURE_DATA*   pAdventureData;

    char                    szScriptName[COMMON_NAME_LEN];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, NPC_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif	// _NPC_DATA_H_