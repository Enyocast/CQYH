#ifndef _SCORE_DEF_H_
#define _SCORE_DEF_H_

// tolua_begin

#define MAX_SCORE_REWARD_COUNT 3
#define SCORE_REWARD_MAX_TIME (GAME_FPS * 150)
#define NORMAl_EXP 100

enum ENUM_DUNGEON_STATE
{
    edstInvalid = -1,
    edstRuning,
	edstPreClosing,
    edstClosing,
    edstTotal
};

enum ENUM_DUNGEON_REWARD
{
    edrInvalid = -1,
    edrFirst,
    edrSecond,
    edrThird,
    edrTotal
};

enum ENUM_DUNGEON_SCORE
{
    edsInvalid,

    edsC,
    edsB,
    edsA,
    edsS,
    edsSS,
    edsSSS,
    
    edsTotal
};

// tolua_end

#endif	// _SCORE_DEF_H_