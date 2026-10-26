#ifndef _VARIABLE_DEF_H_
#define _VARIABLE_DEF_H_

///@file variable_def.h
///@brief define game variable constants

// tolua_begin

#define MAX_SCENE_VARIABLE_COUNT    (32)        ///< @line
#define MAX_ROLE_VARIABLE_COUNT     (512)		///< @line
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
	svtBegin = 128,
	svtSabacWinner0 = svtBegin,
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

	svtEnd
};

inline UINT32 MakeVariableID(UINT32 dwType, UINT32 dwIndex)
{
	return ((dwIndex & VARIABLE_ID_MASK) | (dwType << 28));
}
// tolua_end

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
	esvtDefault,
	esvtItemDrop,
	esvtItemDropRefreshTime,
	esvtRune,
	esvtRuneRefreshTime
};

inline UINT64 MakeServerKey(UINT32 type, UINT32 id)
{
	return (((UINT64)type) << 32) | id;
}

#endif  // _VARIABLE_DEF_H_