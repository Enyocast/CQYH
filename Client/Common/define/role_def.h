#ifndef _ROLE_DEF_H_
#define _ROLE_DEF_H_

#include "scene_def.h"

/// @file role_def.h

// tolua_begin

#define MAX_ROLE_FRACTION_ID			    (16)                    ///< @line
#define MAX_ROLE_LEVEL					    (100)                   ///< @line
#define MAX_PK_VALUE					    (100000)                ///< @line
#define MIN_REPUTATION					    (-19999)                ///< @line
#define MAX_ACTIVITY_LEVEL                  (5)                     ///< @line

#define MAX_USABLE_ROLE_PER_USER            (4)
#define MAX_DELETE_ROLE_PER_USER            (4)
#define MAX_ROLE_PER_USER					(MAX_USABLE_ROLE_PER_USER + MAX_DELETE_ROLE_PER_USER)

#define MAX_ROLE_HAIR_TYPE                  (12)                     ///< @line
#define MAX_ROLE_HAIR_COLOR                 (8)                     ///< @line
#define MAX_ROLE_FACE_TYPE                  (8)                     ///< @line
#define MAX_ROLE_SKIN_COLOR                 (5)                     ///< @line

#define MOMENTARY_KILL_NPC_TIEM		        (3)						///< @line
#define MIN_MOMENTARY_KILL_NPC_COUNT	    (10)					///< @line

#define MIN_CONSECUTIVE_KILL_NPC_COUNT	    (10)					///< @line
#define MAX_CONSECUTIVE_KILL_NPC_FRAME	    (4*GAME_FPS)

#define MAX_CONSECTIVE_KILL_PLAYER_FRAME	(30*GAME_FPS)
#define MAX_CONSECUTIVE_KILL_PLAYER_COUNT	(3)

#define MAX_QUERY_ROLE_INFO_PER_SEC         (256)

#define MAX_VIP_MONTH						(36)
#define MAX_GM_LEVEL						(100)

#define MAX_PET_PER_ROLE					(6)

// moved from init_reputation_data.h by zhangrui05
#define MAX_REPUTATION_AWARD_COUNT			(8)

#ifdef _DEBUG
#define ROLE_DELAY_LOGOUT_FRAME			    (GAME_FPS * 1)         ///< @line
#define ROLE_DELAY_LOGOUT_FRAME_ABNORMAL	(GAME_FPS * 1)         ///< @line
#else
#define ROLE_DELAY_LOGOUT_FRAME			    (GAME_FPS * 1)         ///< @line
#define ROLE_DELAY_LOGOUT_FRAME_ABNORMAL	(GAME_FPS * 1)        ///< @line
#endif

#define DEFAULT_ROLE_ANTI_CHEAT_LEVEL		2	
#define MAX_ROLE_ANTI_CHEAT_LEVEL			6
#define MAX_ROLE_ANTI_CHEAT_PUNISH_LEVEL	4
#define MAX_ROLE_GPK_PUNISH_LEVEL			4

enum ERoleLogoutType
{
    rltInvalid,

    rltReturnLogin,
	rltReturnSelectRole,
	rltDisconnect,
    rltKickout,

    rltTotal
};

enum ERoleState
{
    rsInvalid, 

    rsPreEntered,
    rsWaitRoleData ,  
    rsWaitMSApprove,      
    rsWaitClientLoad, 
    rsPlaying,
    rsInJump,
	rsJumpInGSWaitClientLoad,
	rsWaitUnlockRoleData,
	rsLogout,

    rsTotal
};

enum EFcmState
{
    fcmsFull,
    fcmsHalf,
    fcmsNone,

    fcmsTotal
};

enum ROLE_FACE_TYPE
{
    faceInvalid,

    faceTotal
};

enum ERolePkMode
{
	rpmInvalid = -1,

	rpmPeace,
	rpmGuild,
	rpmTeam,
	rpmSlayer,
	rpmJustice,
	rpmMaster,

	rpmTotal
};

enum ROLE_PK_RESULT
{
    rprInvalid,

    rprNormal,
    rprRedName,
    rprCounterStrike,
    rprOpponentGuildMember,
    rprLuckyKill,
    rprNoPunishment,

    rprTotal
};

enum ERoleNameColor
{
    rncInvalid = -1,

    rncWhite,
    rncYellow,
    rncRed,

    rncTotal
};

enum ERoleVarType
{
    ervtInvalid = -1,

    ervtTotal
};

enum ROLE_FACTION_RELATION
{
    rfrInvalid = -1,

    rfrDefault,
    rfrFriend,
    rfrEnemy,

    rfrTotal
};

enum VIP_LEVEL
{
    vlLevel0,

    vlLevel1,
    vlLevel2,
    vlLevel3,

    vlTotal
};

enum MSG_PAOPAO_TYPE
{
    MSG_PP_PERSONAL_ENEMY       = 1,
};

enum EActivityPtsReason 
{
	aprInvalid = 0,

	aprWuDouChang,
	aprBaoku,
	aprYanWuChang,
	aprPray,
	aprEscort,
	aprGuildBoss,
	aprSpring,
	aprQuest,
	aprYaoTa,
	aprYouMingSea,

	aprTotal,
};

// tolua_end

#endif	// _ROLE_DEF_H_
