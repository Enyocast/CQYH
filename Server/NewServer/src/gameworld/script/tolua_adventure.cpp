/*
** Lua binding: adventure
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:28.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_adventure_open (lua_State* tolua_S);

#include "../../../common/define/adventure_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_adventure_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_ADVENTURE_TRIGGER_PARAM",MAX_ADVENTURE_TRIGGER_PARAM);
 tolua_constant(tolua_S,"MAX_ADVENTURE_REWARD_PARAM",MAX_ADVENTURE_REWARD_PARAM);
  tolua_constant(tolua_S,"attInvalid",attInvalid);
  tolua_constant(tolua_S,"attKillNpc",attKillNpc);
  tolua_constant(tolua_S,"attDestoryDoodad",attDestoryDoodad);
  tolua_constant(tolua_S,"attRefineEquip",attRefineEquip);
  tolua_constant(tolua_S,"attAddSoul",attAddSoul);
  tolua_constant(tolua_S,"attRandomizeEquip",attRandomizeEquip);
  tolua_constant(tolua_S,"att5MinOnlineTime",att5MinOnlineTime);
  tolua_constant(tolua_S,"attServerTime",attServerTime);
  tolua_constant(tolua_S,"attTotal",attTotal);
  tolua_constant(tolua_S,"adrInvalid",adrInvalid);
  tolua_constant(tolua_S,"adrSpawnNpcAtPoint",adrSpawnNpcAtPoint);
  tolua_constant(tolua_S,"adrSpawnNpcNearby",adrSpawnNpcNearby);
  tolua_constant(tolua_S,"adrSpawnNpcSurround",adrSpawnNpcSurround);
  tolua_constant(tolua_S,"adrSpawnDoodadAtPoint",adrSpawnDoodadAtPoint);
  tolua_constant(tolua_S,"adrSpawnDoodadNearby",adrSpawnDoodadNearby);
  tolua_constant(tolua_S,"adrSendMail",adrSendMail);
  tolua_constant(tolua_S,"adrTotal",adrTotal);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_adventure (lua_State* tolua_S) {
 return tolua_adventure_open(tolua_S);
};
#endif

