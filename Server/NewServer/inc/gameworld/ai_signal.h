#ifndef _AI_SIGNAL_H_
#define _AI_SIGNAL_H_

/// @file ai_signal.h 
/// @brief Signal used by collaborative AI
/// 
#include "base_list.h"

//tolua_begin

struct stSignal 
{
    INT8    nType;          // SIGNAL_TYPE
    INT8    nParam;
    INT16   nRemainTimes;
    INT32   nExpiredFrame;
    UINT32  dwIssuerID;
    BASE_LIST_NODE  ListNode;
};

//tolua_end

#define SIGNAL_MAX_LIVE_FRAME ( 8 * GAME_FPS )
#define SIGNAL_MAX_PROCESS_TIMES 16
#define SIGNAL_MAX_NUM_PER_REGION 64
#define SIGNAL_MAX_NUM_PER_CHARACTER 4


#endif  // _AI_SIGNAL_H_