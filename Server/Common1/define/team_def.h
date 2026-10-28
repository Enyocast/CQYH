#ifndef _TEAM_DEF_H_
#define _TEAM_DEF_H_

#include "scene_def.h"

#define MAX_TEAM_MEMBER_COUNT					(20)
#define MAX_ADJACENT_ROLE_NOTEAM_COUNT			(32)
#define MAX_ADJACENT_TEAM_COUNT					(16)

#define TEAM_SYNC_MEMBERINFO_TO_MS			(GAME_FPS * 9)
#define TEAM_SYNC_MEMBERINFO_TO_CLIENT		(GAME_FPS * 2)
#define TEAM_SYNC_MEMBERINFO_STOP			(0xFFFF)

// Team Activity Related
#define	MAX_TEAM_COUNT_PER_PAGE	(10)
#define MAX_TEAM_PAGE_COUNT	(99)
#define MAX_TEAM_COUNT_PER_ACTIVITY	(MAX_TEAM_PAGE_COUNT*MAX_TEAM_COUNT_PER_PAGE)

#define	MAX_TEAM_ACTIVITY	(64)
#define	MAX_TEAM_DUNGEON	(64)

// Team Auction
#define  TEAM_AUCTION_BID_FRAME_INTERVAL	(20 * GAME_FPS)	// 出价时间间隔
#define	 TEAM_AUCTION_ITEM_INIT_INDEX	(1)		// 拍卖物品初始编号

enum TEAM_ANSWER_TYPE
{
    etatInvite,
    etatEnter,
};

enum TEAM_ANSWER_RESULT
{
    etarAgree = 0,
    etarDisAgree
};

enum TEAM_ASSIGN
{
	etaInvalid,

    etaFreeForAll,      //自由拾取
	etaTeamAuction,		//组队拍卖

	etaTotal
};

enum TEAM_MEMBER_STATE
{
    etsOnline = 0,
    etsOffline
};

enum TEAM_ACTIVITY_ACTION_TYPE
{
	etaatInvalid = 0,

	etaatActivity,
	etaatDungeon,

	etaatTotal
};

enum TEAM_BID_STATE
{
	etbsInvalid = 0,

	etbsBidding,
	etbsAbandon,

	etbsTotal
};

#endif