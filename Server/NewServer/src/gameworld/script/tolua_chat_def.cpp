/*
** Lua binding: chat_def
** Generated automatically by tolua++-1.0.92 on 09/29/25 00:22:31.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_chat_def_open (lua_State* tolua_S);

#include "../../../Common/define/chat_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_chat_def_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_CHAT_MESSAGE_LEN",MAX_CHAT_MESSAGE_LEN);
 tolua_constant(tolua_S,"CHAT_SYSTEM_ID",CHAT_SYSTEM_ID);
  tolua_constant(tolua_S,"cctInvalid",cctInvalid);
  tolua_constant(tolua_S,"cctScreen",cctScreen);
  tolua_constant(tolua_S,"cctScene",cctScene);
  tolua_constant(tolua_S,"cctGroup",cctGroup);
  tolua_constant(tolua_S,"cctServer",cctServer);
  tolua_constant(tolua_S,"cctTotal",cctTotal);
  tolua_constant(tolua_S,"cltInvalid",cltInvalid);
  tolua_constant(tolua_S,"cltNormal",cltNormal);
  tolua_constant(tolua_S,"cltLighting",cltLighting);
  tolua_constant(tolua_S,"cltTvShow",cltTvShow);
  tolua_constant(tolua_S,"cltUrl",cltUrl);
  tolua_constant(tolua_S,"cltDialog",cltDialog);
  tolua_constant(tolua_S,"cltTrumpet",cltTrumpet);
  tolua_constant(tolua_S,"cltGMTrumpet",cltGMTrumpet);
  tolua_constant(tolua_S,"cltTotal",cltTotal);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_chat_def (lua_State* tolua_S) {
 return tolua_chat_def_open(tolua_S);
};
#endif

