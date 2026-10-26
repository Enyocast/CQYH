/*
** Lua binding: id_def
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:30.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_id_def_open (lua_State* tolua_S);

#include "../../../Common/define/id_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* function: MakeObjectID */
#ifndef TOLUA_DISABLE_tolua_id_def_MakeObjectID00
static int tolua_id_def_MakeObjectID00(lua_State* tolua_S)
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
  unsigned int tolua_ret = ( unsigned int)  MakeObjectID(dwType,dwIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeObjectID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetTypeFromID */
#ifndef TOLUA_DISABLE_tolua_id_def_GetTypeFromID00
static int tolua_id_def_GetTypeFromID00(lua_State* tolua_S)
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
  unsigned int dwObjID = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  signed int tolua_ret = ( signed int)  GetTypeFromID(dwObjID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTypeFromID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetIndexFromID */
#ifndef TOLUA_DISABLE_tolua_id_def_GetIndexFromID00
static int tolua_id_def_GetIndexFromID00(lua_State* tolua_S)
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
  unsigned int dwObjID = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  signed int tolua_ret = ( signed int)  GetIndexFromID(dwObjID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIndexFromID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_id_def_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"INVALID_OBJECT_ID",INVALID_OBJECT_ID);
 tolua_constant(tolua_S,"OBJECT_TYPE_MASK",OBJECT_TYPE_MASK);
 tolua_constant(tolua_S,"OBJECT_ID_MASK",OBJECT_ID_MASK);
 tolua_constant(tolua_S,"MAX_OBJECT_ID",MAX_OBJECT_ID);
  tolua_constant(tolua_S,"otInvalid",otInvalid);
  tolua_constant(tolua_S,"otRole",otRole);
  tolua_constant(tolua_S,"otNpc",otNpc);
  tolua_constant(tolua_S,"otHero",otHero);
  tolua_constant(tolua_S,"otDoodad",otDoodad);
  tolua_constant(tolua_S,"otMissile",otMissile);
  tolua_constant(tolua_S,"otDrop",otDrop);
  tolua_constant(tolua_S,"otGuild",otGuild);
  tolua_constant(tolua_S,"otTeam",otTeam);
  tolua_constant(tolua_S,"otBattleTeam",otBattleTeam);
  tolua_constant(tolua_S,"otChannel",otChannel);
  tolua_constant(tolua_S,"otTrumpet",otTrumpet);
  tolua_constant(tolua_S,"otTotal",otTotal);
#ifndef TOLUA_DISABLE_tolua_id_def_MakeObjectID00
 tolua_function(tolua_S,"MakeObjectID",tolua_id_def_MakeObjectID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_id_def_GetTypeFromID00
 tolua_function(tolua_S,"GetTypeFromID",tolua_id_def_GetTypeFromID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_id_def_GetIndexFromID00
 tolua_function(tolua_S,"GetIndexFromID",tolua_id_def_GetIndexFromID00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_id_def (lua_State* tolua_S) {
 return tolua_id_def_open(tolua_S);
};
#endif

