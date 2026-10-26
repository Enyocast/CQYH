#include "stdafx.h"
#include "scene_data.h"
#include "script_mgr.h"


BOOL SCENE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, SCENE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("SceneID", nSceneID);
    LOG_PROCESS_ERROR(pData->nSceneID >= 0 && pData->nSceneID < MAX_SCENE_TEMPLATE_COUNT);

    READ_INT("Type", nType);
    LOG_PROCESS_ERROR(pData->nType > estInvalid && pData->nType < estTotal);

    READ_INT("FinishTarget", nFinishTarget);
    READ_INT("MaxRoleCount", nMaxRoleCount);
	READ_STR("ConfigName", szConfigName);
	READ_STR("MapDisplayName", szMapDisplayName);

	READ_INT("CannotUseScroll", bCannotUseScroll);
	READ_INT("CannotUseTeleportRing", bCannotUseTeleportRing);
	READ_INT("CannotBeRecalled", bCannotBeRecalled);
	READ_INT("CannotTrade", bCannotTrade);
//	READ_INT("CannotLoseDurability", bCannotLoseDurability);
	READ_INT("CannotSendMail", bCannotSendMail);
	READ_INT("CannotUseExchange", bCannotUseExchange);
	READ_INT("CannotUseAuction", bCannotUseAuction);
	READ_INT("CannotJoinTeam", bCannotJoinTeam);

	READ_INT("CannotGroupChat", bCannotGroupChat);
	READ_INT("CannotSceneChat", bCannotSceneChat);
	READ_INT("CannotScreenChat", bCannotScreenChat);
	READ_INT("CannotWhisperChat", bCannotWhisperChat);
	READ_INT("CannotTeamChat", bCannotTeamChat);
	READ_INT("CannotGuildChat", bCannotGuildChat);
	READ_INT("CannotFriendChat", bCannotFriendChat);

	READ_INT("EnableAntiCheat", bEnableAntiCheat);
	READ_INT("BlockRole", bBlockRole);

	READ_INT("MinPortalLevel", nMinPortalLevel);
	READ_INT("MaxPortalLevel", nMaxPortalLevel);

	READ_INT("MineItemID1", nMineItemID1);
	READ_INT("MineItemID2", nMineItemID2);
	READ_INT("MineItemID3", nMineItemID3);
	READ_INT("MineItemID4", nMineItemID4);
	READ_INT("MineDoodadID1", nMineDoodadID[1]);
	READ_INT("MineDoodadID2", nMineDoodadID[2]);
	READ_INT("MineDoodadChance1", nMineDoodadChance[1]);
	READ_INT("MineDoodadChance2", nMineDoodadChance[2]);
	for (INT32 nIndex = 0; nIndex < MAX_MINE_DROP_GROUP; nIndex++)
	{
		char szField[COMMON_NAME_LEN];

		snprintf(szField, COMMON_NAME_LEN, "MineDropGroup1%d", nIndex);
		READ_INT(szField, MineDrop[1][nIndex].nDropGroupID);

		snprintf(szField, COMMON_NAME_LEN, "MineDropChance1%d", nIndex);
		READ_INT(szField, MineDrop[1][nIndex].nDropChance);

		snprintf(szField, COMMON_NAME_LEN, "MineDropGroup2%d", nIndex);
		READ_INT(szField, MineDrop[2][nIndex].nDropGroupID);

		snprintf(szField, COMMON_NAME_LEN, "MineDropChance2%d", nIndex);
		READ_INT(szField, MineDrop[2][nIndex].nDropChance);
	}

    for (INT32 nIndex = 0; nIndex < MAX_RANDOM_WEATHER_COUNT; nIndex++)
    {
        char szField[COMMON_NAME_LEN];

        snprintf(szField, COMMON_NAME_LEN, "Weather%d", nIndex+1);
        READ_INT_EXPR(szField, WeatherData[nIndex].nWeather);

        snprintf(szField, COMMON_NAME_LEN, "Weather%dWeight", nIndex+1);
        READ_INT(szField, WeatherData[nIndex].nWeight);

        snprintf(szField, COMMON_NAME_LEN, "Weather%dMinDuration", nIndex+1);
        READ_INT(szField, WeatherData[nIndex].nMinDuration);

        snprintf(szField, COMMON_NAME_LEN, "Weather%dMaxDuration", nIndex+1);
        READ_INT(szField, WeatherData[nIndex].nMaxDuration);

        if (pData->WeatherData[nIndex].nWeight > 0)
        {
            LOG_PROCESS_ERROR(pData->WeatherData[nIndex].nWeather > swtInvalid &&
                pData->WeatherData[nIndex].nWeather < swtTotal);

            nRetCode = pData->RandWeather.Add(nIndex, pData->WeatherData[nIndex].nWeight);
            LOG_PROCESS_ERROR(nRetCode);
        }
    }
    READ_INT("MinWeatherRefreshInterval", nMinWeatherRefreshInterval);
    READ_INT("MaxWeatherRefreshInterval", nMaxWeatherRefreshInterval);

    READ_INT("MinPlayerLevel", nMinPlayerLevel);
    READ_INT("MaxPlayerLevel", nMaxPlayerLevel);
    READ_INT("InitLineCount", nInitCount);
	if (pData->nType == estStatic || pData->nType == estUnique)
		LOG_PROCESS_ERROR(pData->nInitCount <= 1);

    READ_INT("BattleSideCount", nSideCount);
    READ_INT("BattleType", nBattleType);
    READ_INT("MinLimitPerSide", nMinRoleLimitPerSide);
    READ_INT("MaxLimitPerSide", nMaxRoleLimitPerSide);

	READ_INT("LoginJumpSceneTempID", nLoginJumpSceneTempID);
	READ_INT("LoginJumpX", nLoginJumpX);
	READ_INT("LoginJumpY", nLoginJumpY);
	READ_INT("LoginJumpZ", nLoginJumpZ);

	ConvertCoordO2N(pData->nLoginJumpX, pData->nLoginJumpY, pData->nLoginJumpZ);
	pData->nLoginJumpX = pData->nLoginJumpX * POINT_PER_CM;
	pData->nLoginJumpY = pData->nLoginJumpY * POINT_PER_CM;
	pData->nLoginJumpZ = pData->nLoginJumpZ * POINT_PER_CM;

	READ_INT("EnableIntimacy", bEnableIntimacy);

	READ_INT("GpkPunish", bGpkPunish);
	READ_INT("GpkKick", bGpkKick);

    READ_END(nSceneID);
}
