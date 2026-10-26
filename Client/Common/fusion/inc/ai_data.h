#ifndef _AI_DATA_H_
#define _AI_DATA_H_

#include "lua_script.h"     //SCRIPT_NAME_LEN
#include "data_manager.h"

//tolua_begin
#define MAX_AI_ID   (10000)
#define MAX_AI_INIT_AURA_COUNT  (3)
#define MAX_AI_DATA_PARAM_COUNT     (8)

enum NEW_AI_SPELL_TYPE
{
    nastInvalid,

    nastNormalSpell1,
    nastNormalSpell2,
    nastHelpFriendSpell1,
    nastHelpFriendSpell2,
    nastCorpseSpell,
    nastSignalIssuerSpell,
    nastSignalTargetSpell,
    nastNormalSpell3,
    nastNormalSpell4,
    nastEnterFightSpell,
    nastChaseSpell,
    nastInitSpell1,
    nastInitSpell2,
    nastInitSpell3,
    nastDeadSpell,
    nastIdleSpell,

    nastTotal,

    nastGlobalCDTimer, 
    nastLiveTimer,
    nastFleeTimer,
    nastThreatSingalTimer,
    nastChanceTargetTimer,
    nastScanNearbyTimer,
    nastStepAroundTimer,
    nastWithdrawTimer,

    nastCustom
};

struct NEW_AI_DATA
{
    INT32	nAIID;
    char    szScriptName[SCRIPT_NAME_LEN];

    INT32   nWalkSpeed;                 // unit: cm/s, table unit: cm/s
    INT32   nRunSpeed;                  // unit: cm/s, table unit: cm/s
    INT32   nRotateSpeed;               // unit: degree/s, table unit: degree/s
    BOOL    bPatrol;
    BOOL    bFollow;
	BOOL	bCanRun;
	BOOL	bAlwaysRun;

    INT32   nScanEnemyRange;            // unit: cm, table unit: cm
    INT32   nScanFriendRange;           // unit: cm, table unit: cm
    INT32   nChaseRange;                // unit: cm, table unit: cm
    INT32   nPreferDistance;            // unit: cm, table unit: cm
    INT32   nWithdrawThreshold;         // unit: cm, table unit: cm
    INT32   nChaseThreshold;            // unit: cm, table unit: cm
    INT32   nChaseDelayTime;            // unit: ms, table unit: ms

    INT32   nInitAuraID[MAX_AI_INIT_AURA_COUNT];
    INT32   nLiveTime;                  // unit: ms, table unit: ms -- 0 means no limit
	BOOL	bDisappearOnTimeout;

    INT32   nWanderRange;               // unit: cm, table unit: cm
    INT32   nWanderInterval;            // unit: ms, table unit: ms

    INT32   nSpellID[nastTotal];
    INT32   nSpellChance[nastTotal];
    INT32   nSpellCDTime[nastTotal];    // unit: ms, table unit: ms
    INT32   nSelfHpPercent[nastTotal];  // unit: percent, table unit: percent
    INT32   nGlobalCDTime;              // unit: ms, table unit: ms
    INT32   nFriendlyNpcTemplateID;
    BOOL    bFriendlyCorpse;
    INT32   nCorpseTemplateID;
    INT32   nIssuerSpellSignalType;
    INT32   nIssuerSpellSignalRange;
    INT32   nTargetSpellSignalType;
    INT32   nTargetSpellSignalRange;

    INT32   nFleeHpPercent;             // unit: percent, table unit: percent
    INT32   nFleeChance;
    INT32   nFleeDuration;              // unit: ms, table unit: ms

    INT32   nStepAroundChance;    
    INT32   nStepAroundCDTime;          // unit: ms, table unit: ms
    INT32   nChangeTargetChance;        // unit: ms, table unit: ms 
    INT32   nChangeTargetCDTime;        // unit: ms, table unit: ms
    INT32   nSpreadThreatCount;

    INT32   nParam[MAX_AI_DATA_PARAM_COUNT];

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, NEW_AI_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

//tolua_end

#endif  // _AI_DATA_H_
