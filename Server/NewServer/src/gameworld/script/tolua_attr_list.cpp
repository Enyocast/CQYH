/*
** Lua binding: attr_list
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_attr_list_open (lua_State* tolua_S);

#include "attr_list.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CAttrList");
 tolua_usertype(tolua_S,"CCharacter");
}

/* method: GetAttr of class  CAttrList */
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_GetAttr00
static int tolua_attr_list_CAttrList_GetAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAttrList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAttrList* self = (CAttrList*)  tolua_tousertype(tolua_S,1,0);
  signed int eAttrType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAttr'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetAttr(eAttrType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAttrBase of class  CAttrList */
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_SetAttrBase00
static int tolua_attr_list_CAttrList_SetAttrBase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAttrList",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAttrList* self = (CAttrList*)  tolua_tousertype(tolua_S,1,0);
  CCharacter* pSelf = ((CCharacter*)  tolua_tousertype(tolua_S,2,0));
  signed int eAttrType = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nValue = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAttrBase'", NULL);
#endif
 {
  self->SetAttrBase(pSelf,eAttrType,nValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAttrBase'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAttrA of class  CAttrList */
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_SetAttrA00
static int tolua_attr_list_CAttrList_SetAttrA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAttrList",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAttrList* self = (CAttrList*)  tolua_tousertype(tolua_S,1,0);
  CCharacter* pSelf = ((CCharacter*)  tolua_tousertype(tolua_S,2,0));
  signed int eAttrType = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nValue = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAttrA'", NULL);
#endif
 {
  self->SetAttrA(pSelf,eAttrType,nValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAttrA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAttrB of class  CAttrList */
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_SetAttrB00
static int tolua_attr_list_CAttrList_SetAttrB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAttrList",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAttrList* self = (CAttrList*)  tolua_tousertype(tolua_S,1,0);
  CCharacter* pSelf = ((CCharacter*)  tolua_tousertype(tolua_S,2,0));
  signed int eAttrType = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nValue = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAttrB'", NULL);
#endif
 {
  self->SetAttrB(pSelf,eAttrType,nValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAttrB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EnableAttr of class  CAttrList */
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_EnableAttr00
static int tolua_attr_list_CAttrList_EnableAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAttrList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAttrList* self = (CAttrList*)  tolua_tousertype(tolua_S,1,0);
  signed int eAttrType = (( signed int)  tolua_tonumber(tolua_S,2,0));
   bool bEnable = ((  bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EnableAttr'", NULL);
#endif
 {
  self->EnableAttr(eAttrType,bEnable);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EnableAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddAttrA of class  CAttrList */
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_AddAttrA00
static int tolua_attr_list_CAttrList_AddAttrA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAttrList",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAttrList* self = (CAttrList*)  tolua_tousertype(tolua_S,1,0);
  CCharacter* pSelf = ((CCharacter*)  tolua_tousertype(tolua_S,2,0));
  signed int eAttrType = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nValue = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddAttrA'", NULL);
#endif
 {
  self->AddAttrA(pSelf,eAttrType,nValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddAttrA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddAttrB of class  CAttrList */
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_AddAttrB00
static int tolua_attr_list_CAttrList_AddAttrB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAttrList",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAttrList* self = (CAttrList*)  tolua_tousertype(tolua_S,1,0);
  CCharacter* pSelf = ((CCharacter*)  tolua_tousertype(tolua_S,2,0));
  signed int eAttrType = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nValue = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddAttrB'", NULL);
#endif
 {
  self->AddAttrB(pSelf,eAttrType,nValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddAttrB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CalculateAll of class  CAttrList */
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_CalculateAll00
static int tolua_attr_list_CAttrList_CalculateAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAttrList",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAttrList* self = (CAttrList*)  tolua_tousertype(tolua_S,1,0);
  CCharacter* pSelf = ((CCharacter*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CalculateAll'", NULL);
#endif
 {
  self->CalculateAll(pSelf);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CalculateAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReCalculateAttr of class  CAttrList */
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_ReCalculateAttr00
static int tolua_attr_list_CAttrList_ReCalculateAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAttrList",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAttrList* self = (CAttrList*)  tolua_tousertype(tolua_S,1,0);
  CCharacter* pSelf = ((CCharacter*)  tolua_tousertype(tolua_S,2,0));
  signed int eAttrType = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReCalculateAttr'", NULL);
#endif
 {
  self->ReCalculateAttr(pSelf,eAttrType);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReCalculateAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_attr_list_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CAttrList","CAttrList","",NULL);
 tolua_beginmodule(tolua_S,"CAttrList");
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_GetAttr00
  tolua_function(tolua_S,"GetAttr",tolua_attr_list_CAttrList_GetAttr00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_SetAttrBase00
  tolua_function(tolua_S,"SetAttrBase",tolua_attr_list_CAttrList_SetAttrBase00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_SetAttrA00
  tolua_function(tolua_S,"SetAttrA",tolua_attr_list_CAttrList_SetAttrA00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_SetAttrB00
  tolua_function(tolua_S,"SetAttrB",tolua_attr_list_CAttrList_SetAttrB00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_EnableAttr00
  tolua_function(tolua_S,"EnableAttr",tolua_attr_list_CAttrList_EnableAttr00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_AddAttrA00
  tolua_function(tolua_S,"AddAttrA",tolua_attr_list_CAttrList_AddAttrA00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_AddAttrB00
  tolua_function(tolua_S,"AddAttrB",tolua_attr_list_CAttrList_AddAttrB00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_CalculateAll00
  tolua_function(tolua_S,"CalculateAll",tolua_attr_list_CAttrList_CalculateAll00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_attr_list_CAttrList_ReCalculateAttr00
  tolua_function(tolua_S,"ReCalculateAttr",tolua_attr_list_CAttrList_ReCalculateAttr00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_attr_list (lua_State* tolua_S) {
 return tolua_attr_list_open(tolua_S);
};
#endif

