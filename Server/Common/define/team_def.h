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
#define  TEAM_AUCTION_BID_FRAME_INTERVAL	(20 * GAME_FPS)	// Bid interval
#define	 TEAM_AUCTION_ITEM_INIT_INDEX	(1)		// Initial auction item index

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

    etaFreeForAll,      //Free-for-all loot
	etaTeamAuction,		//Team auction
	etaLeaderPick,		//Leader loot

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

enum TEAM_AUCTION_ACTION
{
	TAA_ADDITEM = 0,
	TAA_START_AUCTION,
	TAA_BID,
	TAA_ABANDON_SELF_REQUEST,
	TAA_ABANDON_LEAVE_SCENE,
	TAA_REWARD_MONEY,
	TAA_WIN_ITEM,
	TAA_LEADER_GOT_ITEM,
	TAA_RETURN_DEPOSIT,
	TAA_FINISH_AUCTION,

	TAA_TOTAL,
};

enum TEAM_AUCTION_MONEY_REASON
{
	TAMR_NO_CHANGE = 0,
	TAMR_OFFER_PRICE,
	TAMR_ABANDON,
	TAMR_REWARD,
	TAMR_RETURN_DEPOSITE,
};

#endif