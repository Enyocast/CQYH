#ifndef __MMOSTATS_H__
#define __MMOSTATS_H__

// Stat Groups for MMO
enum EMMOStatGroups
{
	MMOSTATGROUP_Default = STATGROUP_LicenseeFirstStatGroup,
	MMOSTATGROUP_Logic,
	MMOSTATGROUP_Network,
};

// Stat Items for MMO
enum EMMOStats
{
	MMOSTAT_Start = STAT_LicenseeFirstStat,
	MMOSTAT_PickActor,
	
	// Network
	MMOSTAT_Network_NetDelay,
	MMOSTAT_Network_GameDelay,
	MMOSTAT_Network_Upload,
	MMOSTAT_Network_Download,
	MMOSTAT_Network_ProcMsgBuf,

    //DropItem
    STAT_DropItemSystemTime,
    STAT_DropItemManagerTime,
    STAT_DropItemTipsTime,

	//MMOSTAT_Network_ElapsedTime,

	//MMOSTAT_Network_SentBytes,
	//MMOSTAT_Network_SentMsgCount,
	//MMOSTAT_Network_AvgSentMsgSize,
	//MMOSTAT_Network_AvgSentBandwidthCost,
	//MMOSTAT_Network_AvgSentBandwidthCostMax,

	//MMOSTAT_Network_ReceivedBytes,
	//MMOSTAT_Network_ReceivedMsgCount,
	//MMOSTAT_Network_AvgRcvMsgSize,
	//MMOSTAT_Network_AvgRcvBandwidthCost,
	//MMOSTAT_Network_AvgRcvBandwidthCostMax,

	//
	STAT_MMOMinimap,
	STAT_MMOMinimap_UpdateMapStaticMarks,
	STAT_MMOMinimap_UpdateMapNearPlayer,
	STAT_MMOMinimap_UpdateMapNearPlayer_SetMapMarkIcon,
	STAT_MMOMinimap_UpdateMapGlobalPlayer,
	STAT_MMOMinimap_UpdateMapPath,
	STAT_MMOWorldmap,
	STAT_MMOWorldmap_UpdateMapStaticMarks,
	STAT_MMOWorldmap_UpdateMapStaticMarks_CreateMapMarkUIObject,
	STAT_MMOWorldmap_UpdateMapStaticMarks_eventInitMapMark,
	STAT_MMOWorldmap_UpdateMapStaticMarks_NavPoint,
	STAT_MMOWorldmap_UpdateMarksGlobalPlayer,
	STAT_MMOWorldmap_UpdateMarksNearPlayer,
	STAT_MMOWorldmap_UpdatePlayerMarksInMap,
	STAT_MMOWorldmap_UpdateMapPath,
	STAT_MMOWorldmap_UpdateMapMarksInfomation,

	// ability/effect
	STAT_AbilitySystemTime,
	STAT_AbilityParticleTime,
	STAT_AbilityParticleSpawnTime,
	STAT_AbilityParticleActiveTime,
	STAT_AbilityEmitterTickTime,
	STAT_MoveDeltaTime,

	// add by zhangrui05@snda
	STAT_AchievementTime,
	STAT_QuestTime,
	STAT_GuideTime,
	STAT_GuildTime,
	STAT_GuildTime_UpdateStatue,
	STAT_GuildTime_UpdateGuildForeignTime,
	STAT_GuildTime_EGET_UpdateGuildAllyList,
	STAT_GuildTime_EGET_UpdateGuildEnemyList,
	STAT_GuildTime_EGET_UpdateGuildApplyAllyList,

	STAT_UI_SceneHint,
	STAT_UI_SceneHint_NPC,
	STAT_UI_SceneHint_Player,

	STAT_Load_ProcessCharData,
	STAT_Load_ProcessCharData_NPC,
	STAT_Load_ProcessCharData_EventAppear,
};

#endif
