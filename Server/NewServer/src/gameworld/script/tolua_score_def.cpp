/*
** Lua binding: score_def
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:31.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_score_def_open (lua_State* tolua_S);

#include "scene_def.h"
#include "../../../Common/define/score_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_score_def_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_SCORE_REWARD_COUNT",MAX_SCORE_REWARD_COUNT);
 tolua_constant(tolua_S,"SCORE_REWARD_MAX_TIME",SCORE_REWARD_MAX_TIME);
 tolua_constant(tolua_S,"NORMAl_EXP",NORMAl_EXP);
  tolua_constant(tolua_S,"edstInvalid",edstInvalid);
  tolua_constant(tolua_S,"edstRuning",edstRuning);
  tolua_constant(tolua_S,"edstPreClosing",edstPreClosing);
  tolua_constant(tolua_S,"edstClosing",edstClosing);
  tolua_constant(tolua_S,"edstTotal",edstTotal);
  tolua_constant(tolua_S,"edrInvalid",edrInvalid);
  tolua_constant(tolua_S,"edrFirst",edrFirst);
  tolua_constant(tolua_S,"edrSecond",edrSecond);
  tolua_constant(tolua_S,"edrThird",edrThird);
  tolua_constant(tolua_S,"edrTotal",edrTotal);
  tolua_constant(tolua_S,"edsInvalid",edsInvalid);
  tolua_constant(tolua_S,"edsC",edsC);
  tolua_constant(tolua_S,"edsB",edsB);
  tolua_constant(tolua_S,"edsA",edsA);
  tolua_constant(tolua_S,"edsS",edsS);
  tolua_constant(tolua_S,"edsSS",edsSS);
  tolua_constant(tolua_S,"edsSSS",edsSSS);
  tolua_constant(tolua_S,"edsTotal",edsTotal);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_score_def (lua_State* tolua_S) {
 return tolua_score_def_open(tolua_S);
};
#endif

