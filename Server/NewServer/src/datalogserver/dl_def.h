#ifndef _LOG_SERVER_DEFINE_H_
#define _LOG_SERVER_DEFINE_H_

#include "id_def.h"
#include "chat_def.h"
#include "item_def.h"
#include "quest_def.h"
#include "char_def.h"
#include "money_def.h"

#define MAX_DL_RECORD_FRIEND_COUNT	(32)
#define MAX_DL_RECORD_ITEM_COUNT	(64)
#define MAX_DL_RECORD_MESSAGE_LEN	(1024 * 16)
#define MAX_DL_FILE_CHECK_TIME_INTERVAL	(300)

enum DL_CHAT_TYPE
{
	dctInvalid = -1,

	dctRole,
	dctGuild,
	dctTeam,
	dctScreen,
	dctScene,
	dctGroup,
	dctServer,	

	dctTotal,
};

enum DL_QUEST_TYPE
{
	dqtInvalid = -1,

	dqtAccept,
	dqtComplete,
	dqtAbandon,

	dqtTotal,
};

enum DL_SCENE_STATE_TYPE
{
	dsstInvalid = -1,

	dsstCreate,
	dsstEnter,
	dsstLeave,
	dsstDestory,

	dsstTotal,
};

enum DL_ITEM_SOURCE
{
	disInvalid = -1,

	disGenerate,
	disTrade,
	disDestory,
	disSplit,

	disTotal,
};

enum DL_LOGIN
{
	dlInvalid = -1,

	dlLogin,
	dlLogout,

	dlTotal,
};

enum DL_TEAM_ACTION_TYPE
{
	dtatInvalid = -1,

	dtatCreateTeam,
	dtatJoinTeam,
	dtatLeaveTeam,
	dtatBreakDownTeam,

	dtatTotal,
};

enum DL_LOG_MODULE_TYPE
{
	dlmtInvalid = -1,

	dlmtItem,								// 道具流转
	dlmtChat,								// 聊天
	dlmtQuest,								// 任务
	dlmtAchievement,						// 成就
	dlmtLevelUp,							// 升级
	dlmtDie,								// 死亡
	dlmtScene,								// 场景创建销毁
	dlmtConSlot,							// 包裹格子
	dlmtRoleLogout_basic,					// 角色下线基本信息
	//dlmtRoleLogout_friend,					// 角色下线好友信息
	//dlmtRoleLogout_master,					// 角色下线师徒信息
	dlmtRoleLogout_itembag_default,			// 角色下线默认包裹信息
	dlmtRoleLogout_itembag_equipped,		// 角色下线已装备信息
	dlmtLogin,								// 账号登陆登出
	//dlmtGmCommand,							// GM命令
	dlmtSubMoney,							// 金币交易记录
	dlmtTeam,								// 组队
	dlmtRolePosition,						// 玩家位置信息
	dlmtClientHardwareInfo,					// 玩家硬件信息
	dlmtClientFpsInfo,						// 玩家显示器帧数信息
	dlmtSpellEffect,						// 技能释放
	dlmtCastSpell,							// 释放技能
	dlmtLearnSpell,							// 释放技能
    dlmtGuildEvent,                         // 公会事件
    dlmtGuildChest,                         // 公会资金
    dlmtGuildNumStat,                       // 公会统计
    dlmtGuildMoneyStat,                     // 公会统计
    dlmtGuildRiceStat,                      // 公会统计
    dlmtGuildWoodStat,                      // 公会统计
    dlmtGuildStoneStat,                     // 公会统计
    dlmtGuildMetalStat,                     // 公会统计
    dlmtGuildBuildingStat,                  // 公会统计
    dlmtBillingRequest,                     // 计费请求
    dlmtBillingResult,                      // 计费结果
    dlmtRuneItem,                           // 洗铭文
    dlmtChangeItem,                         // 物品改变

    dlmtStatRealMoney,                      // 统计：消耗点券
    dlmtStatQuestComplete,                  // 统计：任务完成
    dlmtStatNpcDie,                         // 统计：NPC死亡
    dlmtStatNpcMoney,                       // 统计：NPC掉落金币
    dlmtStatMoney,                          // 统计：货币
    dlmtStatMomentaryKillNpc,               // 统计：
    dlmtStatConsecutiveKillNpc,             // 统计：
    dlmtStatItem,                           // 物品产出消耗数量
	dlmtAntiCheat,							// 反外挂

	dlmtTotal
};

static char* s_pcszModuleName[] = {
	"Item",
	"Chat",
	"Quest",
	"Achievement",
	"LevelUp",
	"Die",
	"Scene",
	"BagSlot",
	"RoleLogout_Basic",
	//"RoleLogout_Friend",
	//"RoleLogout_Master",
	"RoleLogout_Itembag_Default",
	"RoleLogout_Itembag_Equipped",
	"AccountLogin",
	//"GM",
	"Money",
	"Team",
	"Position",
	"ClientHardwareInfo",
	"ClientFpsInfo",
	"SpellEffect",
	"CastSpell",
	"LearnSpell",
    "GuildEvent",
    "GuildChest",
    "GuildNumStat",
    "GuildMoneyStat",
    "GuildRiceStat",
    "GuildWoodStat",
    "GuildStoneStat",
    "GuildMetalStat",
    "GuildBuildingStat",
    "BillingRequest",
    "BillingResult",
    "RuneItem",
    "ChangeItem",

    "StatRealMoney",
    "StatQuestComplete",
    "StatNpcDie",
    "StatNpcMoney",
    "StatMoney",
    "StatMomentaryKillNpc",
    "StatConsecutiveKillNpc",
    "StatItem",
	"AntiCheat",
};

static char* s_pcszLoginName[] = {
	"Login",
	"Logout"
};

static char* s_pcszTeamAction[] = {
	"CreateTeam",
	"JoinTeam",
	"LeaveTeam",
	"BreakDownTeam",
};

static char* s_pcszQuestAction[dqtTotal] = {
	"Accept",
	"Complete",
	"Abandon",
};

static char* s_pcszSceneStateType[] = {
	"Create",
	"Enter",
	"Leave",
	"Destory",
};

inline char* GetDLChatTypeFromID(INT32 nTargetID)
{
	switch (GetTypeFromID(nTargetID))
	{
	case otRole:
		return "Role";
		break;
	case otChannel:
		return "Channel";
		break;
	case otGuild:
		return "Guild";
		break;
	case otTeam:
		return "Team";
		break;
	default:
		LOG_PROCESS_ERROR(FALSE);
		break;
	}

	switch(nTargetID)
	{
	case cctScreen:
		return "Nearby";
		break;
	case cctScene:
		return "Scene";
		break;
	case cctGroup:
		return "Group";
		break;
	case cctServer:
		return "Server";
		break;
	default:
		LOG_PROCESS_ERROR(FALSE);
		break;
	}
Exit0:
	return "error";
}

inline char* GetLoginStringByType(INT32 nType)
{
	LOG_PROCESS_ERROR(nType >= 0 && nType < sizeof(s_pcszLoginName) / sizeof(s_pcszLoginName[0]));
	
	return s_pcszLoginName[nType];
Exit0:
	return "error";
}

inline char* GetTeamActionByType(INT32 nType)
{
	LOG_PROCESS_ERROR(nType >= 0 && nType < sizeof(s_pcszTeamAction) / sizeof(s_pcszTeamAction[0]));

	return s_pcszTeamAction[nType];
Exit0:
	return "error";
}

inline char* GetQuestActionByType(INT32 nType)
{
	LOG_PROCESS_ERROR(nType >= 0 && nType < sizeof(s_pcszQuestAction) / sizeof(s_pcszQuestAction[0]));

	return s_pcszQuestAction[nType];
Exit0:
	return "error";
}

//inline char* GetQuestTypeByType(INT32 nType)
//{
//	LOG_PROCESS_ERROR(nType > 0 && nType < sizeof(s_pcszQuestType) / sizeof(s_pcszQuestType[0]));
//
//	return s_pcszQuestType[nType];
//Exit0:
//	return "error";
//}

inline char* GetSceneTypeTypeByType(INT32 nType)
{
	LOG_PROCESS_ERROR(nType >= 0 && nType < sizeof(s_pcszSceneStateType) / sizeof(s_pcszSceneStateType[0]));

	return s_pcszSceneStateType[nType];
Exit0:
	return "error";
}

//inline char* GetConSlotByType(INT32 nType)
//{
//	LOG_PROCESS_ERROR(nType > 0 && nType < sizeof(s_pcszConSlotType) / sizeof(s_pcszConSlotType[0]));
//
//	return s_pcszConSlotType[nType];
//Exit0:
//	return "error";
//}
//
//inline char* GetItemSourceByType(INT32 nType)
//{
//	LOG_PROCESS_ERROR(nType >= 0 && nType < sizeof(s_pcszItemSourceType) / sizeof(s_pcszItemSourceType[0]));
//
//	return s_pcszItemSourceType[nType];
//Exit0:
//	return "error";
//}

//inline char* GetObjectTypeByType(INT32 nType)
//{
//	LOG_PROCESS_ERROR(nType > 0 && nType < sizeof(s_pcszObjectType) / sizeof(s_pcszObjectType[0]));
//
//	return s_pcszObjectType[nType];
//Exit0:
//	return "error";
//}

//inline char* GetItemLogByType(INT32 nType)
//{
//	LOG_PROCESS_ERROR(nType > 0 && nType < sizeof(s_pcszItemLogType) / sizeof(s_pcszItemLogType[0]));
//
//	return s_pcszItemLogType[nType];
//Exit0:
//	return "error";
//}

//inline char* GetMoneyLogByType(INT32 nType)
//{
//	LOG_PROCESS_ERROR(nType > 0 && nType < sizeof(s_pcszMoneyLogType) / sizeof(s_pcszMoneyLogType[0]));
//
//	return s_pcszMoneyLogType[nType];
//Exit0:
//	return "error";
//}

//inline char* GetClassTypeByType(INT32 nType)
//{
//	LOG_PROCESS_ERROR(nType > 0 && nType < sizeof(s_pcszClassType) / sizeof(s_pcszClassType[0]));
//
//	return s_pcszClassType[nType];
//Exit0:
//	return "error";
//}

//inline char* GetSexTypeByType(INT32 nType)
//{
//	LOG_PROCESS_ERROR(nType > 0 && nType < sizeof(s_pcszSexType) / sizeof(s_pcszSexType[0]));
//
//	return s_pcszSexType[nType];
//Exit0:
//	return "error";
//}

//inline char* GetMoneyTypeByType(INT32 nType)
//{
//	LOG_PROCESS_ERROR(nType > 0 && nType < sizeof(s_pcszMoneyType) / sizeof(s_pcszMoneyType[0]));
//
//	return s_pcszMoneyType[nType];
//Exit0:
//	return "error";
//}

#endif // _LOG_SERVER_DEFINE_H_
