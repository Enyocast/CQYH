#ifndef _GAME_WORLD_CONFIG_H_
#define _GAME_WORLD_CONFIG_H_

#include "string_def.h"
#include "npc_def.h"
#include "role_def.h"
#include "score_def.h"

// tolua_begin
#pragma pack(push, 8)

struct GAME_WORLD_CONFIG
{
	char        szConfigPath[COMMON_NAME_LEN];

	// distance limit
	INT32       nForceSyncDistance;
	INT32       nNpcInteractDistance;
	INT32       nEmergencyNpcInteractDistance;
	INT32       nDoodadOperateDistance;
	INT32       nLootDistance;
	INT32       nCompareAchievementDistance;
	INT32       nExpShareDistance;
	INT32		nLevelLimit;
	INT32       nTeamAuctionTimeout;
	INT32       nTeamAuctionTax;

	INT32		nInstantJumpRange;

	INT32       nAdjacentDataTimeLimit;
	INT32       nSceneLoadTimeOut;
	INT32       nSaveRoleCountPerSecond;
	INT32       nSaveRoleMinTime;
	INT32		nLoginRoleCountPer10Second;
	INT32		nEnterSceneBuffID;
	INT32		nSceneFinishBuffID;
	INT32       nLootTimeLimit;

	INT32       nPkProtectLevel;
	INT32		nGainPkValueChance;
	INT32		nGainPkValue;
	INT32       nYellowNamePkValueLimit;
	INT32		nRedNamePkValueLimit;
	INT32		nGreyNameDuration;
	INT32       nBagNormalItemDropRateByPlayer[rncTotal];
	INT32       nBagExpensiveItemDropRateByPlayer[rncTotal];
    INT32       nBagNormalItemDropRateByNonPlayer[rncTotal];
    INT32       nBagExpensiveItemDropRateByNonPlayer[rncTotal];
	INT16       shRefineFxLevel1;
	INT16       shRefineFxLevel2;
	INT32       nStallDistance;
    INT32       nStallTax[3];
	INT32		nDynamicRespawnPercent;
	INT32		nRespawnTimeRate;
    INT32       nBagSlotCost[32];
    INT32       nBankSlotCost[56];

	INT32		nWeaponOverWeightAuraID;
	INT32		nArmorOverWeightAuraID;
	INT32		nBagOverWeightAuraID;
	INT32		nGMAuraID;

    struct      LuckModifier
    {
        INT32   nModifier[4];
    };
    LuckModifier nEquipLevelupLuckModifier[7];
    struct      PurityModifier
    {
        INT32   nModifier[4];
    };
    PurityModifier nEquipLevelupPurityModifier[6];

	INT32		nThreatFadeTime;
	INT32		nRageRecoveryParam;
	INT32		nFearDist;

	INT32		nAbilityPtsToPerProgressPts;
	INT32		nBaseSecondsConvertingPerAbilityPts;

	INT32		nKnockBackDistance;
	INT32		nKnockBackSpeed;

	INT32		nDmgToNpcParam1;
	INT32		nDmgToNpcParam2;

	INT32		nHpRecoveryParam;
	INT32		nMpRecoveryParam;

	INT32		nHpTapWalk;
	INT32		nMpTapWalk;
	INT32		nHpTapRun;
	INT32		nMpTapRun;
	INT32		nHpTapPhyAtk;
	INT32		nMpTapPhyAtk;
	INT32		nHpTapMagAtk;
	INT32		nMpTapMagAtk;
	INT32		nHpTapDig;
	INT32		nMpTapDig;
	INT32		nCureParam1;
	INT32		nCureParam2;
	INT32		nHpSpellCureMax;
	INT32		nHpSpellCure;

	INT32		nStiffParamA;
	INT32		nStiffParamB;
	INT32		nStiffIntervalB;

	INT32		nControlParamA;
	INT32		nControlParamB;
	INT32		nControlIntervalB;

	INT32		nHardParamA;
	INT32		nHardParamB;
	INT32		nHardParamC;
	INT32		nHardParamD;

	INT32		nGlobalSubstituteAuraID;

	INT32		nHeroExpGainRate;
	INT32		nHeroExpSubRate;

	INT32		nAIIDWhenSeduced;
	INT32		nLastHurtResetTime;

	struct NPC_QUALITY_REPUATION
	{
		INT32   nReputation;
		INT32   nMaxReputation;
	};
	NPC_QUALITY_REPUATION   AddReputation[nqTotal];
	INT32   SubReputation[nqTotal];

	struct HERO_AI
	{
		INT32 AiId[5];
	};

	HERO_AI HeroAiId[5];

	struct HERO_DEFAULT_NAME_SEX
	{
		char szName[COMMON_NAME_LEN];
	};

	struct HERO_DEFAULT_NAME
	{
		HERO_DEFAULT_NAME_SEX Sex[3];
	};

	HERO_DEFAULT_NAME HeroDefaultName[5];

	INT32	BaseWeaponSpeed[18];
	INT32	BaseWeaponStiffFactor[18];

	INT32	DodgeConst;
	INT32	CritConst[3];
	INT32	DefConst[3];

	INT32	MagHitRateToRunningTarget[13];
	INT32	PhyHitRateToWalkingTarget[13];
	INT32	PhyHitRateToRunningTarget[13];

	struct REVIVE_PARAM
	{
		INT32 nRequireItemID;
		INT32 nRequireItemCount;
//		INT32 nRequireItemMaxCount;
//		INT32 nDelayTime;
		INT32 nHpPercent;
	};

	REVIVE_PARAM ReviveParam[4];

	INT32 nInstantReviveResetTime;

	INT32 nReviveTimesResetTime;
	INT32 nFreeReviveParam1;
	INT32 nFreeReviveParam2;

	struct NORMAL_PRACTICE_PARAM
	{
		INT32	nSeconds;
		INT32	nConvertedAbilityPts;
	};

	NORMAL_PRACTICE_PARAM NormalPracticeParam[4];

	INT32		nFastPracticeRate;
	INT32		FastPracticeMoneyCost[3];

	struct FAST_PRACTICE_ITEM_SPEEDUP_COST
	{
		INT32	nMoneyType;
		INT32	nMoneyCount;
		INT32	nRate;
	};

	FAST_PRACTICE_ITEM_SPEEDUP_COST FastPracticeSpeedupCost[4];

	struct POS
	{
		INT32 x;
		INT32 y;
		INT32 z;
	};

	INT32       nErrorReturnSceneTempID;
	POS			ErrorReturnPos;

	INT32		nRedNameSceneTempID;
	POS			RedNameReturnPos;

    INT32		nDefaultReviveSceneTempID;
	POS			DefaultRevivePos;

	char		TeamDefaultName[COMMON_NAME_LEN];

	struct VIP_DATA
	{
		INT32       nDecreasePkValuePer5Min;
		INT32       nRewardQuestCount;
		INT32       nDailyFatigue;
		INT32       nDailyUseMoneyType01Percent;
	};
	VIP_DATA    VIPData[vlTotal];

	INT32       nTeamExpRate[21];
	INT32       nLevelExpRate[31];
	INT32		nTeacherExpRate;
	INT32		nStudentExpRate;
	INT32       nExtraExpRate;
	INT32       nGlobalExpRate;

	INT32		nLevelDiffExtraExpRate[MAX_ROLE_LEVEL];

	INT32       nDropChanceRate[MAX_ROLE_LEVEL];
	INT32       nGlobalDropRate;

    INT32       nFreeRoleLevel;
    INT32       nFreeRoleTime;
    INT32       nFreeRoleSceneID, nFreeRoleScenePosX, nFreeRoleScenePosY, nFreeRoleScenePosZ, nFreeRoleSceneFaceDirection;
    INT32       nFreeModeCheckTimePeriod;

	// master
    INT32       nMasterRewardExpPunishRate;
    INT32       nMasterFindTeacherLevelLimit;
    INT32       nMasterTwitterCD;
	INT32       nMasterLvlOneStudentNum;
	INT32       nMasterLevelTwoStudentNum;
	INT32       nMasterLevelThreeStudentNum;

	INT32       nMasterLvlTwoExp;
	INT32       nMasterLvlThreeExp;

	INT32       nMasterGradGiftMailIDForS;
	INT32       nMasterGradGiftMailIDForT;

    INT32       nMasterFireStudentPercent;

	INT32		nTeacherExpRewardRate;
	INT32		nStudentExpRewardRate;
	INT32		nTeacherExp2MoneyRate;
	INT32		nStudentExp2MoneyRate;
	INT32		nMoralRate;
	INT32		nMasterExpRate;

	// dungeon score
	struct DUNGEON_SCORE
	{
		INT32       nTimeScoreRate[edsTotal];
		INT32       nAttackScoreRate[edsTotal];
		INT32       nTotalAttackValue[edsTotal];
		INT32       nKillBossScore;
		INT32       nKillEliteNpcScore;
		INT32       nSwiftTimeScore;
		INT32       nNeverDieScore;
		INT32       nGoalScoreDiff[edsTotal];
		INT32       nTotalScore[edsTotal];
	}           DungeonScore;

	struct DEBUG_OPTION
	{
		BOOL        debugai;
		BOOL        bShowErrorDialog;
		BOOL        debugsp;
		BOOL        dropstat;
		BOOL		anticheat;
	}           DebugOption;


	// arena 
	UINT32          dwArenaSceneTemplateID;
	INT32           nArenaWinIncHpPercent;      // RATE_MAX
	struct ARENA_COMMON_REWARD
	{
		INT32       nFundLimit;
		UINT32      dwItemID;
	};
	ARENA_COMMON_REWARD     ArenaReward[4];

	INT32			nAntiCheatInterval[MAX_ROLE_ANTI_CHEAT_LEVEL];
	INT32			nAntiCheatPunishTime[MAX_ROLE_ANTI_CHEAT_PUNISH_LEVEL];
	INT32			nAntiCheatTimeout;
	INT32			nAntiCheatIntervalFloatPct;
	INT32			nAntiCheatKickRole;

	struct SABAC
	{
		BOOL		bEnabled;
		INT32		nSceneTempID;
		POS			OccupiedZoneLeftTop;
		POS			OccupiedZoneRightBottom;
		POS			WarZone1LeftTop;
		POS			WarZone1RightBottom;
		POS			WarZone2LeftTop;
		POS			WarZone2RightBottom;

		POS			DefendRevivePos;
		INT32		nAttackReviveSceneID;
		POS			AttackRevivePos;
		INT32		nOtherReviveSceneID;
		POS			OtherRevivePos;

		INT32		nStartTime;
		INT32		nStartOccupyTime;
		INT32		nEndTime;
		INT32		nEnrollCost;
		INT32		nEnrollItemID;
		INT32		nEnrollItemCount;
		INT32		nLeaderAwardItemID;
		INT32		nMemberAwardItemID;

		INT32		nAwardMailTitleStringID;
		INT32		nAwardMailContentStringID;

		INT32		nErectStatusCost;
	};
	SABAC			Sabac;

	struct SURVEY
	{
		INT32	nMaxLevel;
		char	szSurveyPath[MAX_SURVEY_PATH_LEN];
	};

	SURVEY			Survey[MAX_SURVEY_COUNT];

	char			szCensoredWordList[65536];

	INT32			nSceneBusyPercent;
	INT32			nSceneFullPercent;
	BOOL			bFilterCensoredWord;

    INT32           nWashoutDeletedGuildTime;
    INT32           nWashoutDeletedMasterTime;

	INT32			nTeleportRingCDTime;
	INT32			nProbeNecklaceCDTime;
	INT32			nMemoSuitCDTime;
	char			szRecallFailMessage[COMMON_NAME_LEN];

	INT32			nMineInterval;
	INT32			nMineMaxValue;
	INT32			nMineCDTime;

	struct CHAT_CONFIG
	{
		INT32		nNormalMsgInterval;
		INT32		nGroupMsgInterval;
		INT32		nMaxDailyGroupMsg;
		INT32		nTrumpetItemID;
		INT32       nGroupChatLevel;
		INT32       nGroupChatCost;
	}				ChatConfig;

	struct ARREST_CONFIG
	{
		INT32		nSceneTempID;
		POS			Pos;
	}				ArrestConfig;

	struct DISTRIBUTE_EXP
	{
		INT32 nRoleCountTable[101];
		INT32 nLevelTable[101];
	};

	DISTRIBUTE_EXP DistributeExp[2];

    // pet
    INT32       nPetDisappearTime;

    // exp_bottle
    INT32       nExpBottlePortion;
    INT32       nExpBottleFactor;

    // low level
    INT32       nRoleLowLevel;
};

extern GAME_WORLD_CONFIG g_GWConfig;

#pragma pack(pop)
// tolua_end

#endif  // _GAME_WORLD_CONFIG_H_