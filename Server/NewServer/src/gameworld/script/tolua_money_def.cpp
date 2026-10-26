/*
** Lua binding: money_def
** Generated automatically by tolua++-1.0.92 on 04/26/25 21:55:58.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_money_def_open (lua_State* tolua_S);

#include "../../../Common/define/money_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_money_def_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"MONEYTYPE_INVALID",MONEYTYPE_INVALID);
  tolua_constant(tolua_S,"MONEYTYPE_01",MONEYTYPE_01);
  tolua_constant(tolua_S,"MONEYTYPE_02",MONEYTYPE_02);
  tolua_constant(tolua_S,"MONEYTYPE_03",MONEYTYPE_03);
  tolua_constant(tolua_S,"MONEYTYPE_04",MONEYTYPE_04);
  tolua_constant(tolua_S,"MONEYTYPE_FATIGUE",MONEYTYPE_FATIGUE);
  tolua_constant(tolua_S,"MONEYTYPE_SOUL_PTS",MONEYTYPE_SOUL_PTS);
  tolua_constant(tolua_S,"MONEYTYPE_MASTER_EXP",MONEYTYPE_MASTER_EXP);
  tolua_constant(tolua_S,"MONEYTYPE_AIR",MONEYTYPE_AIR);
  tolua_constant(tolua_S,"MONEYTYPE_BF",MONEYTYPE_BF);
  tolua_constant(tolua_S,"MONEYTYPE_GUILD",MONEYTYPE_GUILD);
  tolua_constant(tolua_S,"MONEYTYPE_SPELL_PTS",MONEYTYPE_SPELL_PTS);
  tolua_constant(tolua_S,"MONEYTYPE_MORAL",MONEYTYPE_MORAL);
  tolua_constant(tolua_S,"MONEYTYPE_ARENA",MONEYTYPE_ARENA);
  tolua_constant(tolua_S,"MONEYTYPE_ACHIEVEMENTPTS",MONEYTYPE_ACHIEVEMENTPTS);
  tolua_constant(tolua_S,"MONEYTYPE_COUNT",MONEYTYPE_COUNT);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_money_def (lua_State* tolua_S) {
 return tolua_money_def_open(tolua_S);
};
#endif

