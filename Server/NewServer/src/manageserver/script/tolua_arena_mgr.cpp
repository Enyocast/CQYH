/*
** Lua binding: arena_mgr
** Generated automatically by tolua++-1.0.92 on 05/30/18 13:59:44.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_arena_mgr_open (lua_State* tolua_S);

#include "../../../Common/define/arena_def.h"
#include "./arena/arena_mgr.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CArenaMgr");
}

/* method: GetInstance of class  CArenaMgr */
#ifndef TOLUA_DISABLE_tolua_arena_mgr_CArenaMgr_GetInstance00
static int tolua_arena_mgr_CArenaMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CArenaMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CArenaMgr& tolua_ret = (CArenaMgr&)  CArenaMgr::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CArenaMgr");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaBroadcastArenaBegin of class  CArenaMgr */
#ifndef TOLUA_DISABLE_tolua_arena_mgr_CArenaMgr_LuaBroadcastArenaBegin00
static int tolua_arena_mgr_CArenaMgr_LuaBroadcastArenaBegin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CArenaMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CArenaMgr* self = (CArenaMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaBroadcastArenaBegin'", NULL);
#endif
 {
 int tolua_ret = (int)
self->LuaBroadcastArenaBegin();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaBroadcastArenaBegin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_arena_mgr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"ARENA_REWARD_COUNT",ARENA_REWARD_COUNT);
 tolua_constant(tolua_S,"ARENA_FIRST_WAIT_TIME",ARENA_FIRST_WAIT_TIME);
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
 tolua_cclass(tolua_S,"CArenaMgr","CArenaMgr","",NULL);
 tolua_beginmodule(tolua_S,"CArenaMgr");
#ifndef TOLUA_DISABLE_tolua_arena_mgr_CArenaMgr_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_arena_mgr_CArenaMgr_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_arena_mgr_CArenaMgr_LuaBroadcastArenaBegin00
  tolua_function(tolua_S,"LuaBroadcastArenaBegin",tolua_arena_mgr_CArenaMgr_LuaBroadcastArenaBegin00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_arena_mgr (lua_State* tolua_S) {
 return tolua_arena_mgr_open(tolua_S);
};
#endif

