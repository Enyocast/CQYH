/*
** Lua binding: string_table
** Generated automatically by tolua++-1.0.92 on 11/08/18 22:50:33.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_string_table_open (lua_State* tolua_S);

#include "../../define/string_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_string_table_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"SERVER_STRING_START_ID",SERVER_STRING_START_ID);
 tolua_constant(tolua_S,"STRING_TABLE_STR_LEN",STRING_TABLE_STR_LEN);
 tolua_constant(tolua_S,"STRING_TABLE_STR_COUNT",STRING_TABLE_STR_COUNT);
  tolua_constant(tolua_S,"essInvalid",essInvalid);
  tolua_constant(tolua_S,"essItemRefineSuccess",essItemRefineSuccess);
  tolua_constant(tolua_S,"essItemComposeSuccess",essItemComposeSuccess);
  tolua_constant(tolua_S,"essItemComposeSuccessDouble",essItemComposeSuccessDouble);
  tolua_constant(tolua_S,"essItemRuneSuccess",essItemRuneSuccess);
  tolua_constant(tolua_S,"essItemMaterial",essItemMaterial);
  tolua_constant(tolua_S,"essItemLevelUp",essItemLevelUp);
  tolua_constant(tolua_S,"essItemLuckOil",essItemLuckOil);
  tolua_constant(tolua_S,"essItemGambleSuccess",essItemGambleSuccess);
  tolua_constant(tolua_S,"essItemSpellBookGambleSuccess",essItemSpellBookGambleSuccess);
  tolua_constant(tolua_S,"essItemDropByNpc",essItemDropByNpc);
  tolua_constant(tolua_S,"essBossKilled",essBossKilled);
  tolua_constant(tolua_S,"essAwardOpenDialog",essAwardOpenDialog);
  tolua_constant(tolua_S,"essRoleKilled",essRoleKilled);
  tolua_constant(tolua_S,"essSceneLineRecycleWarning",essSceneLineRecycleWarning);
  tolua_constant(tolua_S,"essTotal",essTotal);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_string_table (lua_State* tolua_S) {
 return tolua_string_table_open(tolua_S);
};
#endif

