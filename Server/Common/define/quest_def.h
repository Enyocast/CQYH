#ifndef _QUEST_DEF_H_
#define _QUEST_DEF_H_

#define FLY_TO_QUEST_ZONE_COST				(2)
#define FLY_TO_QUEST_ZONE_FIRST_COST		(199)				// Cost of the first few tutorial quest teleports

/******************************************************/

#define CHECK_KILL_PLAYER_CONDITION		(2)
#define CHECK_KILL_PLAYER_LEVEL_DUARION	(20)

#define MAKE_QUEST_CYCLE_KEY(_level_, _color_, _subtype_) ((_level_ << 16) | (_color_ << 8) | _subtype_)

/********************circle quest**********************************/

#define MAKE_CIRCLE_QUEST_KEY(_circleID_, _circleNum_, _level_) ((_circleID_ << 24) | (_circleNum_ << 16) | _level_)
#define	MAX_CIRCLE_COUNT					(32)
#define CIRCLE_QUEST_LEVEL_PER_GRADE		(5)
#define GENERATE_CIRCLE_QUEST_LEVEL			(18)
#define MAX_CIRCLE_QUEST_COUNT				(1024)
#define MAX_QUEST_PER_CIRCLE				(20)

/********************reward quest**********************************/

#define GENERATE_REWARD_QUEST_LEVEL					(25)		// Level at which bounty quests unlock
#define MAX_REWARD_QUEST_DAILY_COMPLETE_COUNT		(3)			// Number of free bounty quests per day
#define MAX_REWARD_QUEST_COUNT_PER_ROLE				(3)
#define REWARD_QUEST_BUY_COMPLETE_ONETIME_COST		(1000)		// Cost to increase the daily bounty completion limit by one
#define REWARD_QUEST_BUY_COMPLETE_ONSHOT_COST		(1000)		// Per-quest cost of completing daily quests in one click
#define REWARD_QUEST_BRUSH_COST						(1000)		// Cost to refresh quests
#define REWARD_QUEST_BRUSH_CD_INTERVAL				(7200)		// Daily quest refresh cooldown: two hours
#define MAX_REWARD_QUEST_COUNT_PER_GROUP			(64)		// Maximum number of quests maintained per level bracket
#define MAX_REWARD_QUEST_DAILY_COMPLETE_TIME		(30)		// Total daily bounty quest completion limit

#define MAX_REWARD_QUEST_COUNT						(1024)
#define REWARD_QUEST_START_ID						(CIRCLE_QUEST_START_ID + MAX_CIRCLE_QUEST_COUNT)

/********************normal quest**********************************/
#define MAX_NORMAL_QUEST_COUNT	    (2048)
#define MAX_NORMAL_QUEST_BYTE_SIZE  (MAX_NORMAL_QUEST_COUNT / 8)
#define REPEAT_QUEST_START_ID       (10000000)
#define MAX_REPEAT_QUEST_COUNT      (256)
#define MAX_REPEAT_QUEST_CYCLE      (255)
#define MAX_ACCEPTED_NORMAL_QUEST_COUNT	(15)
#define MAX_ACCEPTED_EMERGENCY_QUEST_COUNT	(10)
#define MAX_CONDITION_PER_QUEST     (4)
#define MAX_REWARD_PER_QUEST		(5)
#define MAX_SELECTABLE_REWARD_COUNT (16)

#define MAX_DIALOG_CONTENT_LEN      (1024)
#define INVALID_QUEST_ID			(0)

#define	MAX_FLY_SPOT_PER_QUEST		(8)

#define CIRCLE_QUEST_START_ID		(4096)

#define EMERGENCY_QUEST_START_ID	(MAX_NORMAL_QUEST_COUNT)
#define MAX_EMERGENCY_QUEST_COUNT	(1024)
#define MAX_EMERGENCY_QUEST_COMPLETE_PER_DAY	(20)
#define MAX_EMERGENCY_QUEST_PER_ROLE (10)
#define MAX_CHECK_VAR_COUNT			(4)

/************************************************************************/
// kill npc quest
#define MAX_KILL_NPC_QUEST_COUNT	(256)
#define MAX_KILL_COUNT_PER_NPC		(8)
/************************************************************************/

enum QUEST_ACCEPT_TYPE
{
	qatInvalid,

	qatNpc,
	qatShare,	// Accepted through quest sharing
	qatPublish, // Mentor-student shared quest
	qatEmegency,// Accepted as an emergency quest
    qatItem,    // Accepted by right-clicking an item

	qatTotal
};

/// @enum QUEST_TIME_TYPE
enum QUEST_TIME_TYPE
{
    qttInvalid = -1,	///< @line

    qttNoReset,			///< @line
    qttDay,				///< @line
    qttWeek,			///< @line

    qttTotal			///< @line
};

/// @enum QUEST_RELATION_TYPE
enum QUEST_RELATION_TYPE
{
    qrtInvalid,			///< @line

    qrtMaster,			///< @line
    qrtDisciple,		///< @line

    qrtHusband,			///< @line
    qrtWife,			///< @line

    qrtGuildLeader,		///< @line
    qrtGuildMember,		///< @line

	qrtTeamMaster,		///< @line
	qrtTeamHusband,		///< @line
	qrtTeamGuild,		///< @line

    qrtTotal			///< @line
};

/// @enum QUEST_TYPE
enum QUEST_TYPE
{
	qtInvalid = -1,		///< @line

	qtTrunk,			///< @line
	qtBranch,			///< @line
	qtDaily,			///< @line
    qtReward,           ///< @line
    qtCircle,           ///< @line
    qtActivity,         ///< @line
    qtGuild,            ///< @line
    qtMaster,           ///< @line
    qtWedding,          ///< @line
    qtAdventure,        ///< @line
	qtGuide,			///< @line
	qtEmegency,			///< @line

	qtTotal,			///< @line
};

#endif	// _QUEST_DEF_H_
