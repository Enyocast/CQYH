/*
** Lua binding: quest_def
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:30.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_quest_def_open (lua_State* tolua_S);

#include "../../../Common/define/quest_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_quest_def_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_NORMAL_QUEST_COUNT",MAX_NORMAL_QUEST_COUNT);
 tolua_constant(tolua_S,"MAX_NORMAL_QUEST_BYTE_SIZE",MAX_NORMAL_QUEST_BYTE_SIZE);
 tolua_constant(tolua_S,"REPEAT_QUEST_START_ID",REPEAT_QUEST_START_ID);
 tolua_constant(tolua_S,"MAX_REPEAT_QUEST_COUNT",MAX_REPEAT_QUEST_COUNT);
 tolua_constant(tolua_S,"MAX_REPEAT_QUEST_CYCLE",MAX_REPEAT_QUEST_CYCLE);
 tolua_constant(tolua_S,"MAX_ACCEPTED_NORMAL_QUEST_COUNT",MAX_ACCEPTED_NORMAL_QUEST_COUNT);
 tolua_constant(tolua_S,"MAX_ACCEPTED_EMERGENCY_QUEST_COUNT",MAX_ACCEPTED_EMERGENCY_QUEST_COUNT);
 tolua_constant(tolua_S,"MAX_CONDITION_PER_QUEST",MAX_CONDITION_PER_QUEST);
 tolua_constant(tolua_S,"MAX_REWARD_PER_QUEST",MAX_REWARD_PER_QUEST);
 tolua_constant(tolua_S,"MAX_SELECTABLE_REWARD_COUNT",MAX_SELECTABLE_REWARD_COUNT);
 tolua_constant(tolua_S,"MAX_DIALOG_CONTENT_LEN",MAX_DIALOG_CONTENT_LEN);
 tolua_constant(tolua_S,"INVALID_QUEST_ID",INVALID_QUEST_ID);
 tolua_constant(tolua_S,"MAX_FLY_SPOT_PER_QUEST",MAX_FLY_SPOT_PER_QUEST);
 tolua_constant(tolua_S,"CIRCLE_QUEST_START_ID",CIRCLE_QUEST_START_ID);
 tolua_constant(tolua_S,"EMERGENCY_QUEST_START_ID",EMERGENCY_QUEST_START_ID);
 tolua_constant(tolua_S,"MAX_EMERGENCY_QUEST_COUNT",MAX_EMERGENCY_QUEST_COUNT);
 tolua_constant(tolua_S,"MAX_EMERGENCY_QUEST_COMPLETE_PER_DAY",MAX_EMERGENCY_QUEST_COMPLETE_PER_DAY);
 tolua_constant(tolua_S,"MAX_EMERGENCY_QUEST_PER_ROLE",MAX_EMERGENCY_QUEST_PER_ROLE);
 tolua_constant(tolua_S,"MAX_CHECK_VAR_COUNT",MAX_CHECK_VAR_COUNT);
 tolua_constant(tolua_S,"MAX_KILL_NPC_QUEST_COUNT",MAX_KILL_NPC_QUEST_COUNT);
 tolua_constant(tolua_S,"MAX_KILL_COUNT_PER_NPC",MAX_KILL_COUNT_PER_NPC);
  tolua_constant(tolua_S,"qatInvalid",qatInvalid);
  tolua_constant(tolua_S,"qatNpc",qatNpc);
  tolua_constant(tolua_S,"qatShare",qatShare);
  tolua_constant(tolua_S,"qatPublish",qatPublish);
  tolua_constant(tolua_S,"qatEmegency",qatEmegency);
  tolua_constant(tolua_S,"qatItem",qatItem);
  tolua_constant(tolua_S,"qatTotal",qatTotal);
  tolua_constant(tolua_S,"qttInvalid",qttInvalid);
  tolua_constant(tolua_S,"qttNoReset",qttNoReset);
  tolua_constant(tolua_S,"qttDay",qttDay);
  tolua_constant(tolua_S,"qttWeek",qttWeek);
  tolua_constant(tolua_S,"qttTotal",qttTotal);
  tolua_constant(tolua_S,"qrtInvalid",qrtInvalid);
  tolua_constant(tolua_S,"qrtMaster",qrtMaster);
  tolua_constant(tolua_S,"qrtDisciple",qrtDisciple);
  tolua_constant(tolua_S,"qrtHusband",qrtHusband);
  tolua_constant(tolua_S,"qrtWife",qrtWife);
  tolua_constant(tolua_S,"qrtGuildLeader",qrtGuildLeader);
  tolua_constant(tolua_S,"qrtGuildMember",qrtGuildMember);
  tolua_constant(tolua_S,"qrtTeamMaster",qrtTeamMaster);
  tolua_constant(tolua_S,"qrtTeamHusband",qrtTeamHusband);
  tolua_constant(tolua_S,"qrtTeamGuild",qrtTeamGuild);
  tolua_constant(tolua_S,"qrtTotal",qrtTotal);
  tolua_constant(tolua_S,"qtInvalid",qtInvalid);
  tolua_constant(tolua_S,"qtTrunk",qtTrunk);
  tolua_constant(tolua_S,"qtBranch",qtBranch);
  tolua_constant(tolua_S,"qtDaily",qtDaily);
  tolua_constant(tolua_S,"qtReward",qtReward);
  tolua_constant(tolua_S,"qtCircle",qtCircle);
  tolua_constant(tolua_S,"qtActivity",qtActivity);
  tolua_constant(tolua_S,"qtGuild",qtGuild);
  tolua_constant(tolua_S,"qtMaster",qtMaster);
  tolua_constant(tolua_S,"qtWedding",qtWedding);
  tolua_constant(tolua_S,"qtAdventure",qtAdventure);
  tolua_constant(tolua_S,"qtGuide",qtGuide);
  tolua_constant(tolua_S,"qtEmegency",qtEmegency);
  tolua_constant(tolua_S,"qtTotal",qtTotal);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_quest_def (lua_State* tolua_S) {
 return tolua_quest_def_open(tolua_S);
};
#endif

