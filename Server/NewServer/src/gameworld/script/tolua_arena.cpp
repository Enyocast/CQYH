/*
** Lua binding: arena
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:28.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_arena_open (lua_State* tolua_S);

#include "../../../Common/define/arena_def.h"
#include "../../inc/gameworld/arena.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ARENA_RANK_DATA (lua_State* tolua_S)
{
 ARENA_RANK_DATA* self = (ARENA_RANK_DATA*) tolua_tousertype(tolua_S,1,0);
 Mtolua_delete(self);
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"ARENA_DB_DATA");
 tolua_usertype(tolua_S,"CArena");
 tolua_usertype(tolua_S,"ARENA_RANK_DATA");
}

/* get function: dwRoleID of class  ARENA_RANK_DATA */
#ifndef TOLUA_DISABLE_tolua_get_ARENA_RANK_DATA_unsigned_dwRoleID
static int tolua_get_ARENA_RANK_DATA_unsigned_dwRoleID(lua_State* tolua_S)
{
  ARENA_RANK_DATA* self = (ARENA_RANK_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwRoleID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwRoleID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwRoleID of class  ARENA_RANK_DATA */
#ifndef TOLUA_DISABLE_tolua_set_ARENA_RANK_DATA_unsigned_dwRoleID
static int tolua_set_ARENA_RANK_DATA_unsigned_dwRoleID(lua_State* tolua_S)
{
  ARENA_RANK_DATA* self = (ARENA_RANK_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwRoleID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byPointSeasonVictoryTimes of class  ARENA_RANK_DATA */
#ifndef TOLUA_DISABLE_tolua_get_ARENA_RANK_DATA_unsigned_byPointSeasonVictoryTimes
static int tolua_get_ARENA_RANK_DATA_unsigned_byPointSeasonVictoryTimes(lua_State* tolua_S)
{
  ARENA_RANK_DATA* self = (ARENA_RANK_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byPointSeasonVictoryTimes'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byPointSeasonVictoryTimes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byPointSeasonVictoryTimes of class  ARENA_RANK_DATA */
#ifndef TOLUA_DISABLE_tolua_set_ARENA_RANK_DATA_unsigned_byPointSeasonVictoryTimes
static int tolua_set_ARENA_RANK_DATA_unsigned_byPointSeasonVictoryTimes(lua_State* tolua_S)
{
  ARENA_RANK_DATA* self = (ARENA_RANK_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byPointSeasonVictoryTimes'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byPointSeasonVictoryTimes = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nPointSeasonEndTime of class  ARENA_RANK_DATA */
#ifndef TOLUA_DISABLE_tolua_get_ARENA_RANK_DATA_nPointSeasonEndTime
static int tolua_get_ARENA_RANK_DATA_nPointSeasonEndTime(lua_State* tolua_S)
{
  ARENA_RANK_DATA* self = (ARENA_RANK_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nPointSeasonEndTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nPointSeasonEndTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nPointSeasonEndTime of class  ARENA_RANK_DATA */
#ifndef TOLUA_DISABLE_tolua_set_ARENA_RANK_DATA_nPointSeasonEndTime
static int tolua_set_ARENA_RANK_DATA_nPointSeasonEndTime(lua_State* tolua_S)
{
  ARENA_RANK_DATA* self = (ARENA_RANK_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nPointSeasonEndTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nPointSeasonEndTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rankData of class  ARENA_DB_DATA */
#ifndef TOLUA_DISABLE_tolua_get_arena_ARENA_DB_DATA_rankData
static int tolua_get_arena_ARENA_DB_DATA_rankData(lua_State* tolua_S)
{
 int tolua_index;
  ARENA_DB_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ARENA_DB_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_ARENA_RANK_NUM)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->rankData[tolua_index],"ARENA_RANK_DATA");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rankData of class  ARENA_DB_DATA */
#ifndef TOLUA_DISABLE_tolua_set_arena_ARENA_DB_DATA_rankData
static int tolua_set_arena_ARENA_DB_DATA_rankData(lua_State* tolua_S)
{
 int tolua_index;
  ARENA_DB_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ARENA_DB_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_ARENA_RANK_NUM)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->rankData[tolua_index] = *((ARENA_RANK_DATA*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInSeason of class  CArena */
#ifndef TOLUA_DISABLE_tolua_arena_CArena_IsInSeason00
static int tolua_arena_CArena_IsInSeason00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CArena",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CArena* self = (CArena*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInSeason'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsInSeason();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInSeason'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: JoinNewSeason of class  CArena */
#ifndef TOLUA_DISABLE_tolua_arena_CArena_JoinNewSeason00
static int tolua_arena_CArena_JoinNewSeason00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CArena",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CArena* self = (CArena*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'JoinNewSeason'", NULL);
#endif
 {
 int tolua_ret = (int)
self->JoinNewSeason();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'JoinNewSeason'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: QuitSeason of class  CArena */
#ifndef TOLUA_DISABLE_tolua_arena_CArena_QuitSeason00
static int tolua_arena_CArena_QuitSeason00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CArena",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CArena* self = (CArena*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'QuitSeason'", NULL);
#endif
 {
 int tolua_ret = (int)
self->QuitSeason();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'QuitSeason'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSeasonNum of class  CArena */
#ifndef TOLUA_DISABLE_tolua_arena_CArena_GetSeasonNum00
static int tolua_arena_CArena_GetSeasonNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CArena",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CArena* self = (CArena*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSeasonNum'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetSeasonNum();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSeasonNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanGetCommonReward of class  CArena */
#ifndef TOLUA_DISABLE_tolua_arena_CArena_CanGetCommonReward00
static int tolua_arena_CArena_CanGetCommonReward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CArena",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CArena* self = (CArena*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanGetCommonReward'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CanGetCommonReward();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanGetCommonReward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCommonReward of class  CArena */
#ifndef TOLUA_DISABLE_tolua_arena_CArena_GetCommonReward00
static int tolua_arena_CArena_GetCommonReward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CArena",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CArena* self = (CArena*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwItemID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  signed int nMoney = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCommonReward'", NULL);
#endif
 {
 int tolua_ret = (int)
self->GetCommonReward(dwItemID,nMoney);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCommonReward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Win of class  CArena */
#ifndef TOLUA_DISABLE_tolua_arena_CArena_Win00
static int tolua_arena_CArena_Win00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CArena",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CArena* self = (CArena*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Win'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Win();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Win'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Defeated of class  CArena */
#ifndef TOLUA_DISABLE_tolua_arena_CArena_Defeated00
static int tolua_arena_CArena_Defeated00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CArena",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CArena* self = (CArena*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Defeated'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Defeated();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Defeated'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHP of class  CArena */
#ifndef TOLUA_DISABLE_tolua_arena_CArena_GetHP00
static int tolua_arena_CArena_GetHP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CArena",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CArena* self = (CArena*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHP'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetHP();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHP of class  CArena */
#ifndef TOLUA_DISABLE_tolua_arena_CArena_SetHP00
static int tolua_arena_CArena_SetHP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CArena",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CArena* self = (CArena*)  tolua_tousertype(tolua_S,1,0);
  signed int nHp = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHP'", NULL);
#endif
 {
  self->SetHP(nHp);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_arena_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"ARENA_REWARD_COUNT",ARENA_REWARD_COUNT);
 tolua_constant(tolua_S,"ARENA_FIRST_WAIT_TIME",ARENA_FIRST_WAIT_TIME);
 tolua_constant(tolua_S,"ARENA_WEEKLY_DAY_ONE",ARENA_WEEKLY_DAY_ONE);
 tolua_constant(tolua_S,"ARENA_WEEKLY_DAY_TWO",ARENA_WEEKLY_DAY_TWO);
 tolua_constant(tolua_S,"ARENA_WEEKLY_DAY_THREE",ARENA_WEEKLY_DAY_THREE);
 tolua_constant(tolua_S,"ARENA_APPLY_HOUR_BEGIN",ARENA_APPLY_HOUR_BEGIN);
 tolua_constant(tolua_S,"ARENA_APPLY_HOUR_END",ARENA_APPLY_HOUR_END);
 tolua_constant(tolua_S,"ARENA_MATCH_HOUR_BEGIN",ARENA_MATCH_HOUR_BEGIN);
 tolua_constant(tolua_S,"ARENA_MATCH_HOUR_END",ARENA_MATCH_HOUR_END);
 tolua_constant(tolua_S,"ARENA_GET_REWARD_MINUTE",ARENA_GET_REWARD_MINUTE);
 tolua_constant(tolua_S,"ARENA_MAX_SEASON_NUM",ARENA_MAX_SEASON_NUM);
 tolua_constant(tolua_S,"ARENA_JOIN_SEASON_MONEY_CONSUMPTION",ARENA_JOIN_SEASON_MONEY_CONSUMPTION);
 tolua_constant(tolua_S,"ARENA_JOIN_SEASON_LVL_LIMIT",ARENA_JOIN_SEASON_LVL_LIMIT);
 tolua_constant(tolua_S,"ARENA_SPECIAL_REWARD_RANK_LIMIT",ARENA_SPECIAL_REWARD_RANK_LIMIT);
 tolua_constant(tolua_S,"ARENA_SPECIAL_REWARD_PERCENT",ARENA_SPECIAL_REWARD_PERCENT);
 tolua_constant(tolua_S,"ARENA_FIRST_REWARD_RANK_LIMIT",ARENA_FIRST_REWARD_RANK_LIMIT);
 tolua_constant(tolua_S,"ARENA_FIRST_REWARD_PERCENT",ARENA_FIRST_REWARD_PERCENT);
 tolua_constant(tolua_S,"ARENA_SECOND_REWARD_RANK_LIMIT",ARENA_SECOND_REWARD_RANK_LIMIT);
 tolua_constant(tolua_S,"ARENA_SECOND_REWARD_PERCENT",ARENA_SECOND_REWARD_PERCENT);
 tolua_constant(tolua_S,"ARENA_THIRD_REWARD_RANK_LIMIT",ARENA_THIRD_REWARD_RANK_LIMIT);
 tolua_constant(tolua_S,"ARENA_THIRD_REWARD_PERCENT",ARENA_THIRD_REWARD_PERCENT);
 tolua_constant(tolua_S,"MAX_ARENA_RANK_NUM",MAX_ARENA_RANK_NUM);
 tolua_constant(tolua_S,"MAX_ARENA_MATCH_NUM",MAX_ARENA_MATCH_NUM);
 tolua_constant(tolua_S,"ARENA_MATCH_WAIT_TIME",ARENA_MATCH_WAIT_TIME);
 tolua_constant(tolua_S,"ARENA_WEEK_SECOND",ARENA_WEEK_SECOND);
 tolua_constant(tolua_S,"ARENA_TUESDAY_SETTLE_TIME",ARENA_TUESDAY_SETTLE_TIME);
 tolua_constant(tolua_S,"ARENA_THURSDAY_SETTLE_TIME",ARENA_THURSDAY_SETTLE_TIME);
 tolua_constant(tolua_S,"ARENA_SATURDAY_SETTLE_TIME",ARENA_SATURDAY_SETTLE_TIME);
  tolua_constant(tolua_S,"AMVI_JJC_BEGIN_TIME",AMVI_JJC_BEGIN_TIME);
  tolua_constant(tolua_S,"AMVI_JJC_END_TIME",AMVI_JJC_END_TIME);
  tolua_constant(tolua_S,"AMVI_JJC_STATUS",AMVI_JJC_STATUS);
  tolua_constant(tolua_S,"AMVI_JJC_ROLE_NUM",AMVI_JJC_ROLE_NUM);
  tolua_constant(tolua_S,"AMVI_JJC_ROLE_ID_1",AMVI_JJC_ROLE_ID_1);
  tolua_constant(tolua_S,"AMVI_JJC_ROLE_ID_2",AMVI_JJC_ROLE_ID_2);
  tolua_constant(tolua_S,"AMVI_JJC_POTION_STAT_1",AMVI_JJC_POTION_STAT_1);
  tolua_constant(tolua_S,"AMVI_JJC_POTION_STAT_2",AMVI_JJC_POTION_STAT_2);
  tolua_constant(tolua_S,"ARENA_STAT_NONE",ARENA_STAT_NONE);
  tolua_constant(tolua_S,"ARENA_STAT_WAIT",ARENA_STAT_WAIT);
  tolua_constant(tolua_S,"ARENA_STAT_READY",ARENA_STAT_READY);
  tolua_constant(tolua_S,"ARENA_STAT_FIGHT",ARENA_STAT_FIGHT);
  tolua_constant(tolua_S,"ARENA_STAT_END",ARENA_STAT_END);
  tolua_constant(tolua_S,"ARENA_STAT_CLEAR",ARENA_STAT_CLEAR);
  tolua_constant(tolua_S,"avArenaFundLow",avArenaFundLow);
  tolua_constant(tolua_S,"avArenaFundHigh",avArenaFundHigh);
  tolua_constant(tolua_S,"avArenaTicketRewardLow",avArenaTicketRewardLow);
  tolua_constant(tolua_S,"avArenaTicketRewardHigh",avArenaTicketRewardHigh);
  tolua_constant(tolua_S,"avArenaSystemFollowNum",avArenaSystemFollowNum);
  tolua_constant(tolua_S,"avArenaTicketsCount",avArenaTicketsCount);
  tolua_constant(tolua_S,"avArenaCanOpen",avArenaCanOpen);
  tolua_constant(tolua_S,"avArenaOpenTime",avArenaOpenTime);
  tolua_constant(tolua_S,"avArenaIsOpen",avArenaIsOpen);
  tolua_constant(tolua_S,"avArenaRewardCanOpen",avArenaRewardCanOpen);
  tolua_constant(tolua_S,"avArenaRewardIsOpen",avArenaRewardIsOpen);
  tolua_constant(tolua_S,"FIRST_ARENA_MATCH",FIRST_ARENA_MATCH);
  tolua_constant(tolua_S,"SECOND_ARENA_MATCH",SECOND_ARENA_MATCH);
  tolua_constant(tolua_S,"THIRD_ARENA_MATCH",THIRD_ARENA_MATCH);
  tolua_constant(tolua_S,"FOURTH_ARENA_MATCH",FOURTH_ARENA_MATCH);
  tolua_constant(tolua_S,"ARENA_MATCH_COUNT",ARENA_MATCH_COUNT);
  tolua_constant(tolua_S,"ARENA_RES_WIN",ARENA_RES_WIN);
  tolua_constant(tolua_S,"ARENA_RES_DEFEAT",ARENA_RES_DEFEAT);
  tolua_constant(tolua_S,"ARENA_RES_TIE",ARENA_RES_TIE);
 #ifdef __cplusplus
 tolua_cclass(tolua_S,"ARENA_RANK_DATA","ARENA_RANK_DATA","",tolua_collect_ARENA_RANK_DATA);
 #else
 tolua_cclass(tolua_S,"ARENA_RANK_DATA","ARENA_RANK_DATA","",NULL);
 #endif
 tolua_beginmodule(tolua_S,"ARENA_RANK_DATA");
  tolua_variable(tolua_S,"dwRoleID",tolua_get_ARENA_RANK_DATA_unsigned_dwRoleID,tolua_set_ARENA_RANK_DATA_unsigned_dwRoleID);
  tolua_variable(tolua_S,"byPointSeasonVictoryTimes",tolua_get_ARENA_RANK_DATA_unsigned_byPointSeasonVictoryTimes,tolua_set_ARENA_RANK_DATA_unsigned_byPointSeasonVictoryTimes);
  tolua_variable(tolua_S,"nPointSeasonEndTime",tolua_get_ARENA_RANK_DATA_nPointSeasonEndTime,tolua_set_ARENA_RANK_DATA_nPointSeasonEndTime);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"ARENA_DB_DATA","ARENA_DB_DATA","",NULL);
 tolua_beginmodule(tolua_S,"ARENA_DB_DATA");
  tolua_array(tolua_S,"rankData",tolua_get_arena_ARENA_DB_DATA_rankData,tolua_set_arena_ARENA_DB_DATA_rankData);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CArena","CArena","",NULL);
 tolua_beginmodule(tolua_S,"CArena");
#ifndef TOLUA_DISABLE_tolua_arena_CArena_IsInSeason00
  tolua_function(tolua_S,"IsInSeason",tolua_arena_CArena_IsInSeason00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_arena_CArena_JoinNewSeason00
  tolua_function(tolua_S,"JoinNewSeason",tolua_arena_CArena_JoinNewSeason00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_arena_CArena_QuitSeason00
  tolua_function(tolua_S,"QuitSeason",tolua_arena_CArena_QuitSeason00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_arena_CArena_GetSeasonNum00
  tolua_function(tolua_S,"GetSeasonNum",tolua_arena_CArena_GetSeasonNum00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_arena_CArena_CanGetCommonReward00
  tolua_function(tolua_S,"CanGetCommonReward",tolua_arena_CArena_CanGetCommonReward00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_arena_CArena_GetCommonReward00
  tolua_function(tolua_S,"GetCommonReward",tolua_arena_CArena_GetCommonReward00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_arena_CArena_Win00
  tolua_function(tolua_S,"Win",tolua_arena_CArena_Win00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_arena_CArena_Defeated00
  tolua_function(tolua_S,"Defeated",tolua_arena_CArena_Defeated00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_arena_CArena_GetHP00
  tolua_function(tolua_S,"GetHP",tolua_arena_CArena_GetHP00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_arena_CArena_SetHP00
  tolua_function(tolua_S,"SetHP",tolua_arena_CArena_SetHP00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_arena (lua_State* tolua_S) {
 return tolua_arena_open(tolua_S);
};
#endif

