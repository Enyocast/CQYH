#ifndef _RANKLIST_DEF_
#define _RANKLIST_DEF_

#define MAX_RANK_LIST_NODE_COUNT 5000
#define	MAX_RANK_NODE_NUM_PER_PAGE 10

enum RANK_LIST
{
	rlInvalid = -1,
    rlBegin,

    // Individual rankings
    rlRoleBegin = rlBegin,

	rlLevel = rlRoleBegin,			// Level rankings
	rlLevelWarrior,
	rlLevelMage,
	rlLevelTaoist,
	rlLevelRogue,
	rlLevelArcher,	

	rlPower,					    // Combat power rankings
	rlPowerWarrior,
	rlPowerMage,
	rlPowerTaoist,
	rlPowerRogue,
	rlPowerArcher,	

	rlMoney,					    // Wealth rankings
	rlAchievement,				    // Achievement point rankings
	rlMaster,					    // Mentor point rankings
	rlPkValue,					    // PvP value rankings
	rlTotalKillCount,			    // Total kill count

	rlActivity01,
	rlActivity02,
	rlActivity03,
	rlActivity04,

    rlRoleEnd,

	// Guild rankings
    rlGuildBegin = rlRoleEnd,

    rlGuild_Level = rlGuildBegin,   // Guild level rankings
	rlGuild_Money,				    // Guild money rankings
	rlGuild_Resource_Herb,		    // Guild resource 01
	rlGuild_Resource_Wood,		    // Guild resource 02
	rlGuild_Resource_Crystal,	    // Guild resource 03
	rlGuild_Resource_Silver,	    // Guild resource 04
	rlGuild_Pow,					// Total guild combat power

    rlGuildEnd,

	// Arena rankings
 //   rlArenaBegin = rlGuildEnd,

 //   rlArenaScore = rlArenaBegin,    //Arena 5v5 points
	//rlRoleArenaScore,			    // Arena 1v1 points rankings

 //   rlArenaEnd,

	rlTotal,
};

#define MAKE_RANKLIST_EXP_KEY(_level_, _exp_) ((_level_<< 32) | _exp_)
#define GET_RANKLIST_EXP_FROM_KEY(_key_) (_key_ & 0xFFFFFFFF)

#endif //_RANKLIST_DEF_
