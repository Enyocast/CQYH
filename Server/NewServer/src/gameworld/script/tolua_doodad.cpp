/*
** Lua binding: doodad
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_doodad_open (lua_State* tolua_S);

#include "doodad.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CSceneObject");
 tolua_usertype(tolua_S,"CCharacter");
 tolua_usertype(tolua_S,"CDoodad");
 tolua_usertype(tolua_S,"DOODAD_DATA");
}

/* method: GetDoodadData of class  CDoodad */
#ifndef TOLUA_DISABLE_tolua_doodad_CDoodad_GetDoodadData00
static int tolua_doodad_CDoodad_GetDoodadData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CDoodad",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CDoodad* self = (CDoodad*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDoodadData'", NULL);
#endif
 {
  const DOODAD_DATA* tolua_ret = (const DOODAD_DATA*)  self->GetDoodadData();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"const DOODAD_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDoodadData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOpenCount of class  CDoodad */
#ifndef TOLUA_DISABLE_tolua_doodad_CDoodad_GetOpenCount00
static int tolua_doodad_CDoodad_GetOpenCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CDoodad",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CDoodad* self = (CDoodad*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOpenCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetOpenCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOpenCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnOpen of class  CDoodad */
#ifndef TOLUA_DISABLE_tolua_doodad_CDoodad_OnOpen00
static int tolua_doodad_CDoodad_OnOpen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CDoodad",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CDoodad* self = (CDoodad*)  tolua_tousertype(tolua_S,1,0);
  CCharacter* poChar = ((CCharacter*)  tolua_tousertype(tolua_S,2,0));
  signed int nDelayFrame = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnOpen'", NULL);
#endif
 {
  self->OnOpen(poChar,nDelayFrame);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnOpen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_doodad_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CDoodad","CDoodad","CSceneObject",NULL);
 tolua_beginmodule(tolua_S,"CDoodad");
#ifndef TOLUA_DISABLE_tolua_doodad_CDoodad_GetDoodadData00
  tolua_function(tolua_S,"GetDoodadData",tolua_doodad_CDoodad_GetDoodadData00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_doodad_CDoodad_GetOpenCount00
  tolua_function(tolua_S,"GetOpenCount",tolua_doodad_CDoodad_GetOpenCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_doodad_CDoodad_OnOpen00
  tolua_function(tolua_S,"OnOpen",tolua_doodad_CDoodad_OnOpen00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_doodad (lua_State* tolua_S) {
 return tolua_doodad_open(tolua_S);
};
#endif

