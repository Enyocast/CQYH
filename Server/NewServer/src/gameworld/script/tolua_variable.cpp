/*
** Lua binding: variable
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_variable_open (lua_State* tolua_S);

#include "../../../Common/define/variable_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* function: MakeVariableID */
#ifndef TOLUA_DISABLE_tolua_variable_MakeVariableID00
static int tolua_variable_MakeVariableID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int dwType = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int dwIndex = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 {
  unsigned int tolua_ret = ( unsigned int)  MakeVariableID(dwType,dwIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeVariableID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetVarTypeFromID */
#ifndef TOLUA_DISABLE_tolua_variable_GetVarTypeFromID00
static int tolua_variable_GetVarTypeFromID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int dwVarID = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  signed int tolua_ret = ( signed int)  GetVarTypeFromID(dwVarID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVarTypeFromID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetVarIndexFromID */
#ifndef TOLUA_DISABLE_tolua_variable_GetVarIndexFromID00
static int tolua_variable_GetVarIndexFromID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int dwVarID = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  signed int tolua_ret = ( signed int)  GetVarIndexFromID(dwVarID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVarIndexFromID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MakeServerKey */
#ifndef TOLUA_DISABLE_tolua_variable_MakeServerKey00
static int tolua_variable_MakeServerKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int type = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int id = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 {
  unsigned int tolua_ret = ( unsigned int)  MakeServerKey(type,id);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeServerKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_variable_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_SCENE_VARIABLE_COUNT",MAX_SCENE_VARIABLE_COUNT);
 tolua_constant(tolua_S,"MAX_ROLE_VARIABLE_COUNT",MAX_ROLE_VARIABLE_COUNT);
 tolua_constant(tolua_S,"MAX_CLIENT_VARIABLE_COUNT",MAX_CLIENT_VARIABLE_COUNT);
 tolua_constant(tolua_S,"MAX_GUILD_VARIABLE_COUNT",MAX_GUILD_VARIABLE_COUNT);
 tolua_constant(tolua_S,"MAX_VARIABLE_PER_QUEST",MAX_VARIABLE_PER_QUEST);
 tolua_constant(tolua_S,"MAX_AI_VARIABLE_COUNT",MAX_AI_VARIABLE_COUNT);
 tolua_constant(tolua_S,"VARIABLE_ID_MASK",VARIABLE_ID_MASK);
 tolua_constant(tolua_S,"INVALID_VARIABLE_ID",INVALID_VARIABLE_ID);
  tolua_constant(tolua_S,"vtInvalid",vtInvalid);
  tolua_constant(tolua_S,"vtRole",vtRole);
  tolua_constant(tolua_S,"vtScene",vtScene);
  tolua_constant(tolua_S,"vtGuild",vtGuild);
  tolua_constant(tolua_S,"vtQuest",vtQuest);
  tolua_constant(tolua_S,"vtItemRecycle",vtItemRecycle);
  tolua_constant(tolua_S,"vtKillNpcCount",vtKillNpcCount);
  tolua_constant(tolua_S,"vtClient",vtClient);
  tolua_constant(tolua_S,"vtAI",vtAI);
  tolua_constant(tolua_S,"vtAISpell",vtAISpell);
  tolua_constant(tolua_S,"vtServer",vtServer);
  tolua_constant(tolua_S,"vtKillDoodad",vtKillDoodad);
  tolua_constant(tolua_S,"vtAchievement",vtAchievement);
  tolua_constant(tolua_S,"vtKillPlayerCount",vtKillPlayerCount);
  tolua_constant(tolua_S,"vtKillItemNpcCount",vtKillItemNpcCount);
  tolua_constant(tolua_S,"vtTotal",vtTotal);
  tolua_constant(tolua_S,"vRole",vRole);
  tolua_constant(tolua_S,"vScene",vScene);
  tolua_constant(tolua_S,"vGuild",vGuild);
  tolua_constant(tolua_S,"vQuest",vQuest);
  tolua_constant(tolua_S,"vClient",vClient);
  tolua_constant(tolua_S,"vAI",vAI);
  tolua_constant(tolua_S,"vServer",vServer);
  tolua_constant(tolua_S,"svtHighPrice",svtHighPrice);
  tolua_constant(tolua_S,"svtLowPrice",svtLowPrice);
  tolua_constant(tolua_S,"svtMaxSingleCount",svtMaxSingleCount);
  tolua_constant(tolua_S,"svtMaxDailyCount",svtMaxDailyCount);
  tolua_constant(tolua_S,"svtAutoOrderEnabled",svtAutoOrderEnabled);
  tolua_constant(tolua_S,"svtMaxCountPerPrice",svtMaxCountPerPrice);
  tolua_constant(tolua_S,"svtActiveOrderEnabled",svtActiveOrderEnabled);
  tolua_constant(tolua_S,"svtNextMonthlyUpdateTime",svtNextMonthlyUpdateTime);
  tolua_constant(tolua_S,"svtServerStartIndex",svtServerStartIndex);
  tolua_constant(tolua_S,"svtStartRewardRate",svtStartRewardRate);
  tolua_constant(tolua_S,"svtSabacWinner0",svtSabacWinner0);
  tolua_constant(tolua_S,"svtSabacWinner1",svtSabacWinner1);
  tolua_constant(tolua_S,"svtSabacWinner2",svtSabacWinner2);
  tolua_constant(tolua_S,"svtSabacWinner3",svtSabacWinner3);
  tolua_constant(tolua_S,"svtSabacWinner4",svtSabacWinner4);
  tolua_constant(tolua_S,"svtSabacWinner5",svtSabacWinner5);
  tolua_constant(tolua_S,"svtSabacDoor",svtSabacDoor);
  tolua_constant(tolua_S,"svtSabacWall1",svtSabacWall1);
  tolua_constant(tolua_S,"svtSabacWall2",svtSabacWall2);
  tolua_constant(tolua_S,"svtSabacWall3",svtSabacWall3);
  tolua_constant(tolua_S,"svtSabacArcher1",svtSabacArcher1);
  tolua_constant(tolua_S,"svtSabacArcher2",svtSabacArcher2);
  tolua_constant(tolua_S,"svtSabacArcher3",svtSabacArcher3);
  tolua_constant(tolua_S,"svtSabacArcher4",svtSabacArcher4);
  tolua_constant(tolua_S,"svtSabacArcher5",svtSabacArcher5);
  tolua_constant(tolua_S,"svtSabacArcher6",svtSabacArcher6);
  tolua_constant(tolua_S,"svtSabacArcher7",svtSabacArcher7);
  tolua_constant(tolua_S,"svtSabacArcher8",svtSabacArcher8);
  tolua_constant(tolua_S,"svtSabacArcher9",svtSabacArcher9);
  tolua_constant(tolua_S,"svtSabacArcher10",svtSabacArcher10);
  tolua_constant(tolua_S,"svtSabacArcher11",svtSabacArcher11);
  tolua_constant(tolua_S,"svtSabacArcher12",svtSabacArcher12);
  tolua_constant(tolua_S,"svtArenaFund",svtArenaFund);
  tolua_constant(tolua_S,"svtEnd",svtEnd);
#ifndef TOLUA_DISABLE_tolua_variable_MakeVariableID00
 tolua_function(tolua_S,"MakeVariableID",tolua_variable_MakeVariableID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_variable_GetVarTypeFromID00
 tolua_function(tolua_S,"GetVarTypeFromID",tolua_variable_GetVarTypeFromID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_variable_GetVarIndexFromID00
 tolua_function(tolua_S,"GetVarIndexFromID",tolua_variable_GetVarIndexFromID00);
#endif //#ifndef TOLUA_DISABLE
  tolua_constant(tolua_S,"esvtInvalid",esvtInvalid);
  tolua_constant(tolua_S,"esvtDefault",esvtDefault);
  tolua_constant(tolua_S,"esvtRune",esvtRune);
  tolua_constant(tolua_S,"esvtRuneRefreshTime",esvtRuneRefreshTime);
  tolua_constant(tolua_S,"esvtItemDropLimitType0",esvtItemDropLimitType0);
  tolua_constant(tolua_S,"esvtItemDropLimitType0RefreshTime",esvtItemDropLimitType0RefreshTime);
  tolua_constant(tolua_S,"esvtItemDropLimitType1",esvtItemDropLimitType1);
  tolua_constant(tolua_S,"esvtItemDropLimitType1RefreshTime",esvtItemDropLimitType1RefreshTime);
  tolua_constant(tolua_S,"esvtItemDropLimitType2",esvtItemDropLimitType2);
  tolua_constant(tolua_S,"esvtItemDropLimitType2RefreshTime",esvtItemDropLimitType2RefreshTime);
  tolua_constant(tolua_S,"esvtItemDropLimitLuck2Necklace",esvtItemDropLimitLuck2Necklace);
  tolua_constant(tolua_S,"esvtItemDropLimitLuck2NecklaceRefreshTime",esvtItemDropLimitLuck2NecklaceRefreshTime);
  tolua_constant(tolua_S,"esvtWorldGambleCount",esvtWorldGambleCount);
  tolua_constant(tolua_S,"esvtPreviousWorldGambleCount",esvtPreviousWorldGambleCount);
  tolua_constant(tolua_S,"esvtArena",esvtArena);
  tolua_constant(tolua_S,"esvtGuild",esvtGuild);
  tolua_constant(tolua_S,"esvtSceneLostFaction",esvtSceneLostFaction);
  tolua_constant(tolua_S,"esvtTotal",esvtTotal);
#ifndef TOLUA_DISABLE_tolua_variable_MakeServerKey00
 tolua_function(tolua_S,"MakeServerKey",tolua_variable_MakeServerKey00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_variable (lua_State* tolua_S) {
 return tolua_variable_open(tolua_S);
};
#endif

