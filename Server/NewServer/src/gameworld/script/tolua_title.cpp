/*
** Lua binding: title
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_title_open (lua_State* tolua_S);

#include "title.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CTitle");
 tolua_usertype(tolua_S,"CRole");
}

/* method: Init of class  CTitle */
#ifndef TOLUA_DISABLE_tolua_title_CTitle_Init00
static int tolua_title_CTitle_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTitle",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTitle* self = (CTitle*)  tolua_tousertype(tolua_S,1,0);
  CRole* role = ((CRole*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Init'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Init(role);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  CTitle */
#ifndef TOLUA_DISABLE_tolua_title_CTitle_clear00
static int tolua_title_CTitle_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTitle",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTitle* self = (CTitle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
 {
 int tolua_ret = (int)
self->clear();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOwner of class  CTitle */
#ifndef TOLUA_DISABLE_tolua_title_CTitle_SetOwner00
static int tolua_title_CTitle_SetOwner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTitle",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTitle* self = (CTitle*)  tolua_tousertype(tolua_S,1,0);
  CRole* role = ((CRole*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOwner'", NULL);
#endif
 {
  self->SetOwner(role);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOwner'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEquipedTitleID of class  CTitle */
#ifndef TOLUA_DISABLE_tolua_title_CTitle_GetEquipedTitleID00
static int tolua_title_CTitle_GetEquipedTitleID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTitle",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTitle* self = (CTitle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEquipedTitleID'", NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->GetEquipedTitleID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEquipedTitleID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddTitle of class  CTitle */
#ifndef TOLUA_DISABLE_tolua_title_CTitle_AddTitle00
static int tolua_title_CTitle_AddTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTitle",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTitle* self = (CTitle*)  tolua_tousertype(tolua_S,1,0);
  unsigned char titleTemplateID = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddTitle'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddTitle(titleTemplateID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DeleteTitle of class  CTitle */
#ifndef TOLUA_DISABLE_tolua_title_CTitle_DeleteTitle00
static int tolua_title_CTitle_DeleteTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTitle",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTitle* self = (CTitle*)  tolua_tousertype(tolua_S,1,0);
  unsigned char titleTemplateID = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char nDelType = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DeleteTitle'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DeleteTitle(titleTemplateID,nDelType);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DeleteTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EquipTile of class  CTitle */
#ifndef TOLUA_DISABLE_tolua_title_CTitle_EquipTile00
static int tolua_title_CTitle_EquipTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTitle",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTitle* self = (CTitle*)  tolua_tousertype(tolua_S,1,0);
  unsigned char titleTemplateID = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EquipTile'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->EquipTile(titleTemplateID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EquipTile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnEquipTitle of class  CTitle */
#ifndef TOLUA_DISABLE_tolua_title_CTitle_UnEquipTitle00
static int tolua_title_CTitle_UnEquipTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTitle",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTitle* self = (CTitle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnEquipTitle'", NULL);
#endif
 {
 int tolua_ret = (int)
self->UnEquipTitle();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnEquipTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsTitleExist of class  CTitle */
#ifndef TOLUA_DISABLE_tolua_title_CTitle_IsTitleExist00
static int tolua_title_CTitle_IsTitleExist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTitle",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTitle* self = (CTitle*)  tolua_tousertype(tolua_S,1,0);
  unsigned char wTitleTemplateID = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsTitleExist'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsTitleExist(wTitleTemplateID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsTitleExist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_title_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CTitle","CTitle","",NULL);
 tolua_beginmodule(tolua_S,"CTitle");
#ifndef TOLUA_DISABLE_tolua_title_CTitle_Init00
  tolua_function(tolua_S,"Init",tolua_title_CTitle_Init00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_title_CTitle_clear00
  tolua_function(tolua_S,"clear",tolua_title_CTitle_clear00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_title_CTitle_SetOwner00
  tolua_function(tolua_S,"SetOwner",tolua_title_CTitle_SetOwner00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_title_CTitle_GetEquipedTitleID00
  tolua_function(tolua_S,"GetEquipedTitleID",tolua_title_CTitle_GetEquipedTitleID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_title_CTitle_AddTitle00
  tolua_function(tolua_S,"AddTitle",tolua_title_CTitle_AddTitle00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_title_CTitle_DeleteTitle00
  tolua_function(tolua_S,"DeleteTitle",tolua_title_CTitle_DeleteTitle00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_title_CTitle_EquipTile00
  tolua_function(tolua_S,"EquipTile",tolua_title_CTitle_EquipTile00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_title_CTitle_UnEquipTitle00
  tolua_function(tolua_S,"UnEquipTitle",tolua_title_CTitle_UnEquipTitle00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_title_CTitle_IsTitleExist00
  tolua_function(tolua_S,"IsTitleExist",tolua_title_CTitle_IsTitleExist00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_title (lua_State* tolua_S) {
 return tolua_title_open(tolua_S);
};
#endif

