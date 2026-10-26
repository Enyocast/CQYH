/********************************************************************
	created:	1:7:2014   15:44
	file:		arena_def.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_ARENA_DEF_H_
#define _H_ARENA_DEF_H_


#define ARENA_WEEKLY_DAY_ONE    (2)
#define ARENA_WEEKLY_DAY_TWO    (4)
#define ARENA_WEEKLY_DAY_THREE  (6)

#define ARENA_APPLY_HOUR_BEGIN  (0)
#define ARENA_APPLY_HOUR_END    (21)

#define ARENA_MATCH_HOUR_BEGIN  (20)
#define ARENA_MATCH_HOUR_END    (21)

#define ARENA_GET_REWARD_MINUTE    (15)


#define ARENA_MAX_SEASON_NUM    (251)


#define ARENA_JOIN_SEASON_MONEY_CONSUMPTION    (5000)
#define ARENA_JOIN_SEASON_LVL_LIMIT     (30)


#define ARENA_SPECIAL_REWARD_RANK_LIMIT (1)
#define ARENA_SPECIAL_REWARD_PERCENT (20)

#define ARENA_FIRST_REWARD_RANK_LIMIT (6)
#define ARENA_FIRST_REWARD_PERCENT (6)

#define ARENA_SECOND_REWARD_RANK_LIMIT (16)
#define ARENA_SECOND_REWARD_PERCENT (3)

#define ARENA_THIRD_REWARD_RANK_LIMIT (36)
#define ARENA_THIRD_REWARD_PERCENT (1)

#define MAX_ARENA_RANK_NUM  (36)
#define MAX_ARENA_MATCH_NUM (20)


#define ARENA_MATCH_WAIT_TIME   (30)




// server use
#define ARENA_WEEK_SECOND (604800)
#define ARENA_TUESDAY_SETTLE_TIME (248400)
#define ARENA_THURSDAY_SETTLE_TIME (421200)
#define ARENA_SATURDAY_SETTLE_TIME (594000)


#pragma pack(push, 1)

struct ARENA_RANK_DATA 
{
    UINT32          dwRoleID;
    UINT8           byPointSeasonVictoryTimes;
    INT32           nPointSeasonEndTime;
};

struct ARENA_DB_DATA
{
    ARENA_RANK_DATA     rankData[MAX_ARENA_RANK_NUM];
};

#pragma pack(pop)



#endif //_H_ARENA_DEF_H_






