#ifndef _SCENE_DATA_H_
#define _SCENE_DATA_H_

#include "string_def.h"
#include "scene_def.h"
#include "data_manager.h"
#include "lua_script.h"
#include "score_def.h"
#include "item_def.h"
#include "weight_rand.h"

//tolua_begin

struct SCENE_DATA
{
	INT32	nSceneID;
	char	szConfigName[PATH_LEN];
	char	szMapDisplayName[COMMON_NAME_LEN];
	INT32	nType;
    INT32   nMaxRoleCount;
	INT32   nFinishTarget;

	BOOL	bCannotUseScroll;
	BOOL	bCannotUseTeleportRing;
	BOOL	bCannotBeRecalled;
	BOOL	bCannotTrade;
	BOOL	bCannotLoseDurability;
	BOOL	bCannotSendMail;
	BOOL	bCannotUseExchange;
	BOOL	bCannotUseAuction;
	BOOL	bCannotJoinTeam;
	BOOL	bEnableAntiCheat;
	BOOL	bBlockRole;

	BOOL	bCannotGroupChat;
	BOOL	bCannotSceneChat;
	BOOL	bCannotScreenChat;
	BOOL	bCannotWhisperChat;
	BOOL	bCannotTeamChat;
	BOOL	bCannotGuildChat;
	BOOL	bCannotFriendChat;

	INT32	nMinPortalLevel;
	INT32	nMaxPortalLevel;

//tolua_end
	INT32	nMineItemID1;
	INT32	nMineItemID2;
	INT32	nMineItemID3;
	INT32	nMineItemID4;
	INT32	nMineDoodadID[MAX_MINE_LEVEL];
	INT32	nMineDoodadChance[MAX_MINE_LEVEL];
	DROP_CHANCE_DATA	MineDrop[MAX_MINE_LEVEL][MAX_MINE_DROP_GROUP];
//tolua_begin

	struct WEATHER_DATA
	{
		INT32	nWeather;
		INT32	nWeight;
		INT32	nMinDuration;
		INT32	nMaxDuration;
	};
	
	WEATHER_DATA	WeatherData[MAX_RANDOM_WEATHER_COUNT];
	INT32			nMinWeatherRefreshInterval;
	INT32			nMaxWeatherRefreshInterval;
	CWeightRand		RandWeather;

    INT32   nMinPlayerLevel;
    INT32   nMaxPlayerLevel;
    INT32   nInitCount;

    INT32	nSideCount;
    INT32	nBattleType;
    INT32	nMinRoleLimitPerSide;
    INT32	nMaxRoleLimitPerSide;

	INT32	nHandbookType;
	INT32	nHandbookIndex;

	INT32	nLoginJumpSceneTempID;
	INT32	nLoginJumpX;
	INT32	nLoginJumpY;
	INT32	nLoginJumpZ;

	BOOL	bEnableIntimacy;

	BOOL	bGpkPunish;
	BOOL	bGpkKick;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SCENE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};
//tolua_end

#endif	// _SCENE_DATA_H_