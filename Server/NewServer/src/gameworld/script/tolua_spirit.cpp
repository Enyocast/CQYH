/*
** Lua binding: spirit
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:31.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_spirit_open (lua_State* tolua_S);

#include "spirit.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CSpirit");
 tolua_usertype(tolua_S,"CAir");
}

/* method: SetLevel of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_SetLevel00
static int tolua_spirit_CSpirit_SetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->SetLevel(nLevel);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetProductAirLevel of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_SetProductAirLevel00
static int tolua_spirit_CSpirit_SetProductAirLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetProductAirLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->SetProductAirLevel(nLevel);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetProductAirLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevel of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetLevel00
static int tolua_spirit_CSpirit_GetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetLevel();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNextExp2PtsTime of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetNextExp2PtsTime00
static int tolua_spirit_CSpirit_GetNextExp2PtsTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNextExp2PtsTime'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetNextExp2PtsTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNextExp2PtsTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetProductAirLevel of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_SetProductAirLevel01
static int tolua_spirit_CSpirit_SetProductAirLevel01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetProductAirLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->SetProductAirLevel(nLevel);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_spirit_CSpirit_SetProductAirLevel00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ProductAir of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_ProductAir00
static int tolua_spirit_CSpirit_ProductAir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ProductAir'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->ProductAir(nIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ProductAir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddAir of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_AddAir00
static int tolua_spirit_CSpirit_AddAir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nTemplateID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int Exp = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddAir'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->AddAir(nTemplateID,Exp);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddAir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MergeAir of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_MergeAir00
static int tolua_spirit_CSpirit_MergeAir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nSrcCon = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MergeAir'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->MergeAir(nSrcCon);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MergeAir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MoveAir of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_MoveAir00
static int tolua_spirit_CSpirit_MoveAir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int SrcType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int SrcIndex = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int TarType = (( signed int)  tolua_tonumber(tolua_S,4,0));
  signed int TarIndex = (( signed int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MoveAir'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->MoveAir(SrcType,SrcIndex,TarType,TarIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MoveAir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ExchangeAir of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_ExchangeAir00
static int tolua_spirit_CSpirit_ExchangeAir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nAirID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ExchangeAir'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->ExchangeAir(nAirID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ExchangeAir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSlot of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_AddSlot00
static int tolua_spirit_CSpirit_AddSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nCount = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSlot'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->AddSlot(nType,nCount);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHigherAirLevelIndex of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetHigherAirLevelIndex00
static int tolua_spirit_CSpirit_GetHigherAirLevelIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHigherAirLevelIndex'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetHigherAirLevelIndex();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHigherAirLevelIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBagContainerSize of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetBagContainerSize00
static int tolua_spirit_CSpirit_GetBagContainerSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBagContainerSize'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetBagContainerSize();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBagContainerSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStallContainerSize of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetStallContainerSize00
static int tolua_spirit_CSpirit_GetStallContainerSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStallContainerSize'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetStallContainerSize();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStallContainerSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEquipContainerSize of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetEquipContainerSize00
static int tolua_spirit_CSpirit_GetEquipContainerSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEquipContainerSize'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetEquipContainerSize();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEquipContainerSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAir of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetAir00
static int tolua_spirit_CSpirit_GetAir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nBagType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nBagIndex = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAir'", NULL);
#endif
 {
  CAir* tolua_ret = (CAir*)  self->GetAir(nBagType,nBagIndex);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAir");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BrushBloodSlot of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_BrushBloodSlot00
static int tolua_spirit_CSpirit_BrushBloodSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nPage = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BrushBloodSlot'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->BrushBloodSlot(nPage,nIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BrushBloodSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OpenBlood of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_OpenBlood00
static int tolua_spirit_CSpirit_OpenBlood00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nPage = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OpenBlood'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->OpenBlood(nPage);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OpenBlood'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBlood of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_SetBlood00
static int tolua_spirit_CSpirit_SetBlood00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nPage = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nSlot = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nNewNumber = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBlood'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->SetBlood(nPage,nSlot,nNewNumber);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBlood'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBloodOpen of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_IsBloodOpen00
static int tolua_spirit_CSpirit_IsBloodOpen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nPage = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBloodOpen'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->IsBloodOpen(nPage);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBloodOpen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBlood of class  CSpirit */
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetBlood00
static int tolua_spirit_CSpirit_GetBlood00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpirit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpirit* self = (CSpirit*)  tolua_tousertype(tolua_S,1,0);
  signed int nPage = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nSlot = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBlood'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetBlood(nPage,nSlot);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBlood'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_spirit_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CSpirit","CSpirit","",NULL);
 tolua_beginmodule(tolua_S,"CSpirit");
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_SetLevel00
  tolua_function(tolua_S,"SetLevel",tolua_spirit_CSpirit_SetLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_SetProductAirLevel00
  tolua_function(tolua_S,"SetProductAirLevel",tolua_spirit_CSpirit_SetProductAirLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetLevel00
  tolua_function(tolua_S,"GetLevel",tolua_spirit_CSpirit_GetLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetNextExp2PtsTime00
  tolua_function(tolua_S,"GetNextExp2PtsTime",tolua_spirit_CSpirit_GetNextExp2PtsTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_SetProductAirLevel01
  tolua_function(tolua_S,"SetProductAirLevel",tolua_spirit_CSpirit_SetProductAirLevel01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_ProductAir00
  tolua_function(tolua_S,"ProductAir",tolua_spirit_CSpirit_ProductAir00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_AddAir00
  tolua_function(tolua_S,"AddAir",tolua_spirit_CSpirit_AddAir00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_MergeAir00
  tolua_function(tolua_S,"MergeAir",tolua_spirit_CSpirit_MergeAir00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_MoveAir00
  tolua_function(tolua_S,"MoveAir",tolua_spirit_CSpirit_MoveAir00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_ExchangeAir00
  tolua_function(tolua_S,"ExchangeAir",tolua_spirit_CSpirit_ExchangeAir00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_AddSlot00
  tolua_function(tolua_S,"AddSlot",tolua_spirit_CSpirit_AddSlot00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetHigherAirLevelIndex00
  tolua_function(tolua_S,"GetHigherAirLevelIndex",tolua_spirit_CSpirit_GetHigherAirLevelIndex00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetBagContainerSize00
  tolua_function(tolua_S,"GetBagContainerSize",tolua_spirit_CSpirit_GetBagContainerSize00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetStallContainerSize00
  tolua_function(tolua_S,"GetStallContainerSize",tolua_spirit_CSpirit_GetStallContainerSize00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetEquipContainerSize00
  tolua_function(tolua_S,"GetEquipContainerSize",tolua_spirit_CSpirit_GetEquipContainerSize00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetAir00
  tolua_function(tolua_S,"GetAir",tolua_spirit_CSpirit_GetAir00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_BrushBloodSlot00
  tolua_function(tolua_S,"BrushBloodSlot",tolua_spirit_CSpirit_BrushBloodSlot00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_OpenBlood00
  tolua_function(tolua_S,"OpenBlood",tolua_spirit_CSpirit_OpenBlood00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_SetBlood00
  tolua_function(tolua_S,"SetBlood",tolua_spirit_CSpirit_SetBlood00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_IsBloodOpen00
  tolua_function(tolua_S,"IsBloodOpen",tolua_spirit_CSpirit_IsBloodOpen00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_CSpirit_GetBlood00
  tolua_function(tolua_S,"GetBlood",tolua_spirit_CSpirit_GetBlood00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_spirit (lua_State* tolua_S) {
 return tolua_spirit_open(tolua_S);
};
#endif

