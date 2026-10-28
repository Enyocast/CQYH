#ifndef _VARIABLE_DEF_H_
#define _VARIABLE_DEF_H_

///@file variable_def.h
///@brief define game variable constants

#define MAX_SCENE_VARIABLE_COUNT    (32)        ///< @line
#define MAX_ROLE_VARIABLE_COUNT     (2048)		///< @line
#define MAX_CLIENT_VARIABLE_COUNT   (128)       ///< @line
#define MAX_GUILD_VARIABLE_COUNT    (256)       ///< @line
#define MAX_VARIABLE_PER_QUEST      (4)         ///< @line
#define MAX_AI_VARIABLE_COUNT       (8)         ///< @line

#define VARIABLE_ID_MASK        (0x0FFFFFFF)
#define INVALID_VARIABLE_ID     (-1)			///< @line

/// @enum VARIABLE_TYPE
enum VARIABLE_TYPE
{
    vtInvalid,			///< @line

    vtRole,				///< @line
    vtScene,			///< @line
    vtGuild,			///< @line
    vtQuest,			///< @line
	vtItemRecycle,		///< @line
    vtKillNpcCount,		///< @line
	vtClient,			///< @line
    vtAI,				///< @line
    vtAISpell,			///< @line
    vtServer,           ///< @line
	vtKillDoodad,		///< @line
	vtAchievement,		///< @line
	vtKillPlayerCount,	///< @line
	vtKillItemNpcCount, ///< @line

    vtTotal,			///< @line

    vRole   = vtRole    << 28,  ///< @line
    vScene  = vtScene   << 28,  ///< @line
    vGuild  = vtGuild   << 28,  ///< @line
    vQuest  = vtQuest   << 28,  ///< @line
    vClient = vtClient  << 28,  ///< @line
    vAI     = vtAI      << 28,  ///< @line
    vServer = vtServer  << 28,  ///< @line 
};

enum SERVER_VAR_TYPE
{
	svtHighPrice = 1,
	svtLowPrice = 2,
	svtMaxSingleCount = 3,
	svtMaxDailyCount = 4,
	svtAutoOrderEnabled = 5,
	svtMaxCountPerPrice = 6,
	svtActiveOrderEnabled = 7,

	svtNextMonthlyUpdateTime = 21,
	svtServerStartIndex = 22,
	svtStartRewardRate = 23,
	svtSabacWinner0 = 128,
	svtSabacWinner1,
	svtSabacWinner2,
	svtSabacWinner3,
	svtSabacWinner4,
	svtSabacWinner5,
	svtSabacDoor,
	svtSabacWall1,
	svtSabacWall2,
	svtSabacWall3,
	svtSabacArcher1,
	svtSabacArcher2,
	svtSabacArcher3,
	svtSabacArcher4,
	svtSabacArcher5,
	svtSabacArcher6,
	svtSabacArcher7,
	svtSabacArcher8,
	svtSabacArcher9,
	svtSabacArcher10,
	svtSabacArcher11,
	svtSabacArcher12,

    svtArenaFund = 155,

	svtEnd
};

inline UINT32 MakeVariableID(UINT32 dwType, UINT32 dwIndex)
{
	return ((dwIndex & VARIABLE_ID_MASK) | (dwType << 28));
}

inline INT32 GetVarTypeFromID(UINT32 dwVarID)
{
	return (dwVarID >> 28);
}

inline INT32 GetVarIndexFromID(UINT32 dwVarID)
{
	return (dwVarID & VARIABLE_ID_MASK);
}

enum SERVER_VARIABLE_TYPE
{
	esvtInvalid = 0,

	esvtDefault = esvtInvalid,

	esvtRune,				// 铭文洗练限制
	esvtRuneRefreshTime,    // 

	esvtItemDropLimitType0,				  // 怪物掉落限制
    esvtItemDropLimitType0RefreshTime,	  // 
    esvtItemDropLimitType1,				  // 
    esvtItemDropLimitType1RefreshTime,	  // 
    esvtItemDropLimitType2,				  // 
    esvtItemDropLimitType2RefreshTime,    // 

	esvtItemDropLimitLuck2Necklace,       // 运2项链限制专用
	esvtItemDropLimitLuck2NecklaceRefreshTime,       // 运2项链限制专用, 刷新时间

    esvtWorldGambleCount,			 // 当前全区重铸数量
    esvtPreviousWorldGambleCount,    // 上一次全区重铸数量

    esvtArena,    // 竞技场
    esvtGuild,	  // 公会

	esvtSceneLostFaction,    // 场景迷失派系?

	esvtTotal
};

inline UINT64 MakeServerKey(UINT32 type, UINT32 id)
{
	return (((UINT64)type) << 32) | id;
}

static const INT32 nItemDropLimitType[3] = { esvtItemDropLimitType0, esvtItemDropLimitType1, esvtItemDropLimitType2 };
static const INT32 nItemDropLimitRefreshTime[3] = { esvtItemDropLimitType0RefreshTime, esvtItemDropLimitType1RefreshTime, esvtItemDropLimitType2RefreshTime };

#endif  // _VARIABLE_DEF_H_