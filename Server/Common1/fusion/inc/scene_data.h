#ifndef _SCENE_DATA_H_
#define _SCENE_DATA_H_

#include "string_def.h"
#include "scene_def.h"
#include "data_manager.h"
#include "lua_script.h"
#include "score_def.h"
#include "item_def.h"
#include "weight_rand.h"
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
	BOOL	bEnableAntiCheat;

	BOOL	bCannotGroupChat;
	BOOL	bCannotSceneChat;
	BOOL	bCannotScreenChat;
	BOOL	bCannotWhisperChat;
	BOOL	bCannotTeamChat;
	BOOL	bCannotGuildChat;
	BOOL	bCannotFriendChat;

	INT32	nMineItemID1;
	INT32	nMineItemID2;
	INT32	nMineDoodadID;
	INT32	nMineDoodadChance;
	DROP_CHANCE_DATA	MineDrop[MAX_MINE_DROP_GROUP];

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

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SCENE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif	// _SCENE_DATA_H_