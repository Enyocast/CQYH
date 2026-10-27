/*
** Lua binding: trade
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_trade_open (lua_State* tolua_S);

#include "scene_object.h"
#include "scene_object.h"
#include "character.h"
#include "aura_instance.h"
#include "spell_instance.h"
#include "../../../common/define/role_def.h"
#include "role.h"
#include "reputation.h"
#include "trade.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CTargetScanner (lua_State* tolua_S)
{
 CTargetScanner* self = (CTargetScanner*) tolua_tousertype(tolua_S,1,0);
 Mtolua_delete(self);
 return 0;
}

static int tolua_collect_CSpellSlot (lua_State* tolua_S)
{
 CSpellSlot* self = (CSpellSlot*) tolua_tousertype(tolua_S,1,0);
 Mtolua_delete(self);
 return 0;
}

static int tolua_collect_CSpellInstance (lua_State* tolua_S)
{
 CSpellInstance* self = (CSpellInstance*) tolua_tousertype(tolua_S,1,0);
 Mtolua_delete(self);
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CRoleGuildData");
 tolua_usertype(tolua_S,"CSpellInstance");
 tolua_usertype(tolua_S,"CTrade");
 tolua_usertype(tolua_S,"Item");
 tolua_usertype(tolua_S,"GRID_INSTANCE_DATA");
 tolua_usertype(tolua_S,"CRegion");
 tolua_usertype(tolua_S,"GRID_DATA");
 tolua_usertype(tolua_S,"CCoolDown");
 tolua_usertype(tolua_S,"CAIProcessor");
 tolua_usertype(tolua_S,"CSceneObject");
 tolua_usertype(tolua_S,"CFriend");
 tolua_usertype(tolua_S,"CMaster");
 tolua_usertype(tolua_S,"CNpc");
 tolua_usertype(tolua_S,"CTitle");
 tolua_usertype(tolua_S,"CReputation");
 tolua_usertype(tolua_S,"RUNE_DATA");
 tolua_usertype(tolua_S,"ISpellBook");
 tolua_usertype(tolua_S,"CHero");
 tolua_usertype(tolua_S,"CRole");
 tolua_usertype(tolua_S,"ZONE_DATA");
 tolua_usertype(tolua_S,"CAttrList");
 tolua_usertype(tolua_S,"CSpirit");
 tolua_usertype(tolua_S,"CScene");
 tolua_usertype(tolua_S,"CArena");
 tolua_usertype(tolua_S,"ABSOLUTE_SCENE_POS");
 tolua_usertype(tolua_S,"CAsimovRole");
 tolua_usertype(tolua_S,"CStall");
 tolua_usertype(tolua_S,"CShieldList");
 tolua_usertype(tolua_S,"CSpellSlot");
 tolua_usertype(tolua_S,"CAura");
 tolua_usertype(tolua_S,"CAchievementsList");
 tolua_usertype(tolua_S,"CCharacter");
 tolua_usertype(tolua_S,"CQuestList");
 tolua_usertype(tolua_S,"CAuraInstance");
 tolua_usertype(tolua_S,"CItemBag");
 tolua_usertype(tolua_S,"ExtraParam");
 tolua_usertype(tolua_S,"CFlagBits");
 tolua_usertype(tolua_S,"CTargetScanner");
}

/* method: GetObjID of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetObjID00
static int tolua_trade_CSceneObject_GetObjID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetObjID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetObjID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetObjID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetObjType of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetObjType00
static int tolua_trade_CSceneObject_GetObjType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetObjType'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetObjType();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetObjType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScene of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetScene00
static int tolua_trade_CSceneObject_GetScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScene'", NULL);
#endif
 {
  CScene* tolua_ret = (CScene*)  self->GetScene();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CScene");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRegion of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetRegion00
static int tolua_trade_CSceneObject_GetRegion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRegion'", NULL);
#endif
 {
  CRegion* tolua_ret = (CRegion*)  self->GetRegion();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CRegion");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRegion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetZone of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetZone00
static int tolua_trade_CSceneObject_GetZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetZone'", NULL);
#endif
 {
  const ZONE_DATA* tolua_ret = (const ZONE_DATA*)  self->GetZone();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"const ZONE_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetZone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGrid of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetGrid00
static int tolua_trade_CSceneObject_GetGrid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGrid'", NULL);
#endif
 {
  const GRID_DATA* tolua_ret = (const GRID_DATA*)  self->GetGrid();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"const GRID_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGrid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGridInstance of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetGridInstance00
static int tolua_trade_CSceneObject_GetGridInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGridInstance'", NULL);
#endif
 {
  GRID_INSTANCE_DATA* tolua_ret = (GRID_INSTANCE_DATA*)  self->GetGridInstance();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GRID_INSTANCE_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGridInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetX of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetX00
static int tolua_trade_CSceneObject_SetX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
  signed int fX = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetX'", NULL);
#endif
 {
  self->SetX(fX);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetY of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetY00
static int tolua_trade_CSceneObject_SetY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
  signed int fY = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetY'", NULL);
#endif
 {
  self->SetY(fY);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetZ of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetZ00
static int tolua_trade_CSceneObject_SetZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
  signed int fZ = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetZ'", NULL);
#endif
 {
  self->SetZ(fZ);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetX of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetX00
static int tolua_trade_CSceneObject_GetX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetX'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetX();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetY of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetY00
static int tolua_trade_CSceneObject_GetY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetY'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetY();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetZ of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetZ00
static int tolua_trade_CSceneObject_GetZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetZ'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetZ();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFaceDirection of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetFaceDirection00
static int tolua_trade_CSceneObject_SetFaceDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
  signed int nFaceDirection = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFaceDirection'", NULL);
#endif
 {
  self->SetFaceDirection(nFaceDirection);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFaceDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFaceDirection of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetFaceDirection00
static int tolua_trade_CSceneObject_GetFaceDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFaceDirection'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetFaceDirection();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFaceDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBodyType of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetBodyType00
static int tolua_trade_CSceneObject_SetBodyType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
  signed int nBodyType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBodyType'", NULL);
#endif
 {
  self->SetBodyType(nBodyType);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBodyType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBodyType of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetBodyType00
static int tolua_trade_CSceneObject_GetBodyType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBodyType'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetBodyType();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBodyType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanTeleport of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_CanTeleport00
static int tolua_trade_CSceneObject_CanTeleport00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanTeleport'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CanTeleport();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanTeleport'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetObjID of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetObjID01
static int tolua_trade_CSceneObject_GetObjID01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetObjID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetObjID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_GetObjID00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetObjType of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetObjType01
static int tolua_trade_CSceneObject_GetObjType01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetObjType'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetObjType();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_GetObjType00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScene of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetScene01
static int tolua_trade_CSceneObject_GetScene01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScene'", NULL);
#endif
 {
  CScene* tolua_ret = (CScene*)  self->GetScene();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CScene");
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_GetScene00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRegion of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetRegion01
static int tolua_trade_CSceneObject_GetRegion01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRegion'", NULL);
#endif
 {
  CRegion* tolua_ret = (CRegion*)  self->GetRegion();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CRegion");
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_GetRegion00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetZone of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetZone01
static int tolua_trade_CSceneObject_GetZone01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetZone'", NULL);
#endif
 {
  const ZONE_DATA* tolua_ret = (const ZONE_DATA*)  self->GetZone();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"const ZONE_DATA");
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_GetZone00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGrid of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetGrid01
static int tolua_trade_CSceneObject_GetGrid01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGrid'", NULL);
#endif
 {
  const GRID_DATA* tolua_ret = (const GRID_DATA*)  self->GetGrid();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"const GRID_DATA");
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_GetGrid00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGridInstance of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetGridInstance01
static int tolua_trade_CSceneObject_GetGridInstance01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGridInstance'", NULL);
#endif
 {
  GRID_INSTANCE_DATA* tolua_ret = (GRID_INSTANCE_DATA*)  self->GetGridInstance();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GRID_INSTANCE_DATA");
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_GetGridInstance00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetX of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetX01
static int tolua_trade_CSceneObject_SetX01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
  signed int fX = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetX'", NULL);
#endif
 {
  self->SetX(fX);
 }
 }
 return 0;
tolua_lerror:
 return tolua_trade_CSceneObject_SetX00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetY of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetY01
static int tolua_trade_CSceneObject_SetY01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
  signed int fY = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetY'", NULL);
#endif
 {
  self->SetY(fY);
 }
 }
 return 0;
tolua_lerror:
 return tolua_trade_CSceneObject_SetY00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetZ of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetZ01
static int tolua_trade_CSceneObject_SetZ01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
  signed int fZ = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetZ'", NULL);
#endif
 {
  self->SetZ(fZ);
 }
 }
 return 0;
tolua_lerror:
 return tolua_trade_CSceneObject_SetZ00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetX of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetX01
static int tolua_trade_CSceneObject_GetX01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetX'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetX();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_GetX00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetY of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetY01
static int tolua_trade_CSceneObject_GetY01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetY'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetY();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_GetY00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetZ of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetZ01
static int tolua_trade_CSceneObject_GetZ01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetZ'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetZ();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_GetZ00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFaceDirection of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetFaceDirection01
static int tolua_trade_CSceneObject_SetFaceDirection01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
  signed int nFaceDirection = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFaceDirection'", NULL);
#endif
 {
  self->SetFaceDirection(nFaceDirection);
 }
 }
 return 0;
tolua_lerror:
 return tolua_trade_CSceneObject_SetFaceDirection00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFaceDirection of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetFaceDirection01
static int tolua_trade_CSceneObject_GetFaceDirection01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFaceDirection'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetFaceDirection();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_GetFaceDirection00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBodyType of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetBodyType01
static int tolua_trade_CSceneObject_SetBodyType01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
  signed int nBodyType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBodyType'", NULL);
#endif
 {
  self->SetBodyType(nBodyType);
 }
 }
 return 0;
tolua_lerror:
 return tolua_trade_CSceneObject_SetBodyType00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBodyType of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetBodyType01
static int tolua_trade_CSceneObject_GetBodyType01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBodyType'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetBodyType();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_GetBodyType00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanTeleport of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_CanTeleport01
static int tolua_trade_CSceneObject_CanTeleport01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSceneObject* self = (CSceneObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanTeleport'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CanTeleport();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CSceneObject_CanTeleport00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstanceID of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_trade_CAuraInstance_GetInstanceID00
static int tolua_trade_CAuraInstance_GetInstanceID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraInstance* self = (CAuraInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInstanceID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetInstanceID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstanceID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Add of class  CCoolDown */
#ifndef TOLUA_DISABLE_tolua_trade_CCoolDown_Add00
static int tolua_trade_CCoolDown_Add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCoolDown",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCoolDown* self = (CCoolDown*)  tolua_tousertype(tolua_S,1,0);
  signed int nKey = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nInterval = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Add'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Add(nKey,nInterval);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reset of class  CCoolDown */
#ifndef TOLUA_DISABLE_tolua_trade_CCoolDown_Reset00
static int tolua_trade_CCoolDown_Reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCoolDown",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCoolDown* self = (CCoolDown*)  tolua_tousertype(tolua_S,1,0);
  signed int nKey = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Reset'", NULL);
#endif
 {
  self->Reset(nKey);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckReady of class  CCoolDown */
#ifndef TOLUA_DISABLE_tolua_trade_CCoolDown_CheckReady00
static int tolua_trade_CCoolDown_CheckReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCoolDown",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCoolDown* self = (CCoolDown*)  tolua_tousertype(tolua_S,1,0);
  signed int nKey = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckReady'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CheckReady(nKey);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRemainFrm of class  CCoolDown */
#ifndef TOLUA_DISABLE_tolua_trade_CCoolDown_GetRemainFrm00
static int tolua_trade_CCoolDown_GetRemainFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCoolDown",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCoolDown* self = (CCoolDown*)  tolua_tousertype(tolua_S,1,0);
  signed int nKey = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRemainFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetRemainFrm(nKey);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRemainFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Enable of class  CCoolDown */
#ifndef TOLUA_DISABLE_tolua_trade_CCoolDown_Enable00
static int tolua_trade_CCoolDown_Enable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCoolDown",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCoolDown* self = (CCoolDown*)  tolua_tousertype(tolua_S,1,0);
   bool bEnabled = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Enable'", NULL);
#endif
 {
  self->Enable(bEnabled);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Enable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_trade_CTargetScanner_new00
static int tolua_trade_CTargetScanner_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CTargetScanner* tolua_ret = (CTargetScanner*)  Mtolua_new((CTargetScanner)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTargetScanner");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_trade_CTargetScanner_new00_local
static int tolua_trade_CTargetScanner_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CTargetScanner* tolua_ret = (CTargetScanner*)  Mtolua_new((CTargetScanner)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTargetScanner");
 tolua_register_gc(tolua_S,lua_gettop(tolua_S));
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_trade_CTargetScanner_delete00
static int tolua_trade_CTargetScanner_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
 Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTargetX of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_trade_CTargetScanner_GetTargetX00
static int tolua_trade_CTargetScanner_GetTargetX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTargetX'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetTargetX();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTargetX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTargetY of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_trade_CTargetScanner_GetTargetY00
static int tolua_trade_CTargetScanner_GetTargetY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTargetY'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetTargetY();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTargetY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTargetZ of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_trade_CTargetScanner_GetTargetZ00
static int tolua_trade_CTargetScanner_GetTargetZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTargetZ'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetTargetZ();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTargetZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_trade_CSpellInstance_new00
static int tolua_trade_CSpellInstance_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CSpellInstance* tolua_ret = (CSpellInstance*)  Mtolua_new((CSpellInstance)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpellInstance");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_trade_CSpellInstance_new00_local
static int tolua_trade_CSpellInstance_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CSpellInstance* tolua_ret = (CSpellInstance*)  Mtolua_new((CSpellInstance)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpellInstance");
 tolua_register_gc(tolua_S,lua_gettop(tolua_S));
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_trade_CSpellInstance_delete00
static int tolua_trade_CSpellInstance_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
 Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScanner of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_trade_CSpellInstance_GetScanner00
static int tolua_trade_CSpellInstance_GetScanner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScanner'", NULL);
#endif
 {
  CTargetScanner& tolua_ret = (CTargetScanner&)  self->GetScanner();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CTargetScanner");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScanner'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: JumpTo of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_JumpTo00
static int tolua_trade_CCharacter_JumpTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
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
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int llX = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int llY = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int llZ = (( signed int)  tolua_tonumber(tolua_S,4,0));
  signed int nFaceDirection = (( signed int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'JumpTo'", NULL);
#endif
 {
 int tolua_ret = (int)
self->JumpTo(llX,llY,llZ,nFaceDirection);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'JumpTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetClass of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetClass00
static int tolua_trade_CCharacter_GetClass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClass'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetClass();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSex of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetSex00
static int tolua_trade_CCharacter_GetSex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSex'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetSex();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevel of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetLevel00
static int tolua_trade_CCharacter_GetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetName of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetName00
static int tolua_trade_CCharacter_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetName'", NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->GetName();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetClass of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetClass00
static int tolua_trade_CCharacter_SetClass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nClass = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetClass'", NULL);
#endif
 {
  self->SetClass(nClass);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetClass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSex of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetSex00
static int tolua_trade_CCharacter_SetSex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nSex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSex'", NULL);
#endif
 {
  self->SetSex(nSex);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLevel of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetLevel00
static int tolua_trade_CCharacter_SetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLevel'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetLevel(nLevel);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
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

/* method: GetAttr of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetAttr00
static int tolua_trade_CCharacter_GetAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetAttrList of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetAttrList00
static int tolua_trade_CCharacter_GetAttrList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAttrList'", NULL);
#endif
 {
  CAttrList& tolua_ret = (CAttrList&)  self->GetAttrList();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CAttrList");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAttrList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInCutScene of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetInCutScene00
static int tolua_trade_CCharacter_SetInCutScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
   bool bInCutScene = ((  bool)  tolua_toboolean(tolua_S,2,0));
  signed int nDurationFrm = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInCutScene'", NULL);
#endif
 {
  self->SetInCutScene(bInCutScene,nDurationFrm);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInCutScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MoveTo of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_MoveTo00
static int tolua_trade_CCharacter_MoveTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nDestX = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nDestY = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MoveTo'", NULL);
#endif
 {
 int tolua_ret = (int)
self->MoveTo(nDestX,nDestY);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MoveTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Die of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_Die00
static int tolua_trade_CCharacter_Die00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nParam = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Die'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Die(nParam);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Die'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Revive of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_Revive00
static int tolua_trade_CCharacter_Revive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nParam = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nHpPercent = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Revive'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Revive(nParam,nHpPercent);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Revive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RotateTo of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_RotateTo00
static int tolua_trade_CCharacter_RotateTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nFaceDirection = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nDurationFrm = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RotateTo'", NULL);
#endif
 {
  self->RotateTo(nFaceDirection,nDurationFrm);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RotateTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCanRun of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetCanRun00
static int tolua_trade_CCharacter_SetCanRun00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
   bool bCanRun = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCanRun'", NULL);
#endif
 {
  self->SetCanRun(bCanRun);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCanRun'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMoveState of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetMoveState00
static int tolua_trade_CCharacter_GetMoveState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMoveState'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMoveState();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMoveState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHome of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetHome00
static int tolua_trade_CCharacter_SetHome00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
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
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nSceneID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nHomeX = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nHomeY = (( signed int)  tolua_tonumber(tolua_S,4,0));
  signed int nHomeZ = (( signed int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHome'", NULL);
#endif
 {
  self->SetHome(nSceneID,nHomeX,nHomeY,nHomeZ);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHome'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHomeX of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetHomeX00
static int tolua_trade_CCharacter_GetHomeX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHomeX'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetHomeX();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHomeX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHomeY of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetHomeY00
static int tolua_trade_CCharacter_GetHomeY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHomeY'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetHomeY();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHomeY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHomeZ of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetHomeZ00
static int tolua_trade_CCharacter_GetHomeZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHomeZ'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetHomeZ();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHomeZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CancelCast of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_CancelCast00
static int tolua_trade_CCharacter_CancelCast00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CancelCast'", NULL);
#endif
 {
  self->CancelCast();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CancelCast'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsCasting of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_IsCasting00
static int tolua_trade_CCharacter_IsCasting00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsCasting'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsCasting();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsCasting'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EquipRune of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_EquipRune00
static int tolua_trade_CCharacter_EquipRune00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const RUNE_DATA",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"Item",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  const RUNE_DATA* pRuneData = ((const RUNE_DATA*)  tolua_tousertype(tolua_S,2,0));
  Item* poItem = ((Item*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EquipRune'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->EquipRune(pRuneData,poItem);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EquipRune'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnEquipRune of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_UnEquipRune00
static int tolua_trade_CCharacter_UnEquipRune00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const RUNE_DATA",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"Item",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  const RUNE_DATA* pRuneData = ((const RUNE_DATA*)  tolua_tousertype(tolua_S,2,0));
  Item* poItem = ((Item*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnEquipRune'", NULL);
#endif
 {
 int tolua_ret = (int)
self->UnEquipRune(pRuneData,poItem);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnEquipRune'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpellSlot of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetSpellSlot00
static int tolua_trade_CCharacter_GetSpellSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpellSlot'", NULL);
#endif
 {
  CSpellSlot* tolua_ret = (CSpellSlot*)  self->GetSpellSlot(nIndex);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpellSlot");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpellSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CastSpell of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_CastSpell00
static int tolua_trade_CCharacter_CastSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nSpellID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  CCharacter* poTarget = ((CCharacter*)  tolua_tousertype(tolua_S,3,0));
  signed int nTargetX = (( signed int)  tolua_tonumber(tolua_S,4,0));
  signed int nTargetY = (( signed int)  tolua_tonumber(tolua_S,5,0));
  signed int nTargetZ = (( signed int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CastSpell'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->CastSpell(nSpellID,poTarget,nTargetX,nTargetY,nTargetZ);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CastSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlayAction of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_PlayAction00
static int tolua_trade_CCharacter_PlayAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwActionID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlayAction'", NULL);
#endif
 {
 int tolua_ret = (int)
self->PlayAction(dwActionID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCastingSpell of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetCastingSpell00
static int tolua_trade_CCharacter_GetCastingSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCastingSpell'", NULL);
#endif
 {
  CSpellInstance* tolua_ret = (CSpellInstance*)  self->GetCastingSpell();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpellInstance");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCastingSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHp of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetHp00
static int tolua_trade_CCharacter_GetHp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHp'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetHp();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHp of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetHp00
static int tolua_trade_CCharacter_SetHp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nHp = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHp'", NULL);
#endif
 {
  self->SetHp(nHp);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChangeHp of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_ChangeHp00
static int tolua_trade_CCharacter_ChangeHp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nValue = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nReason = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChangeHp'", NULL);
#endif
 {
  self->ChangeHp(nValue,nReason);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChangeHp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMp of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetMp00
static int tolua_trade_CCharacter_GetMp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMp'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMp();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChangeMp of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_ChangeMp00
static int tolua_trade_CCharacter_ChangeMp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nValue = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChangeMp'", NULL);
#endif
 {
  self->ChangeMp(nValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChangeMp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanAttack of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_CanAttack00
static int tolua_trade_CCharacter_CanAttack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  CCharacter* poChar = ((CCharacter*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanAttack'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CanAttack(poChar);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanAttack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpellBook of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetSpellBook00
static int tolua_trade_CCharacter_GetSpellBook00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpellBook'", NULL);
#endif
 {
  ISpellBook& tolua_ret = (ISpellBook&)  self->GetSpellBook();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"ISpellBook");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpellBook'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AppendAura of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_AppendAura00
static int tolua_trade_CCharacter_AppendAura00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CAura",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,5,"ExtraParam",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  CAura* pAuraInfo = ((CAura*)  tolua_tousertype(tolua_S,2,0));
  CCharacter* poCaster = ((CCharacter*)  tolua_tousertype(tolua_S,3,0));
  unsigned int dwFromObjID = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
  ExtraParam* pExParam = ((ExtraParam*)  tolua_tousertype(tolua_S,5,0));
  signed int nNewDurationFrm = (( signed int)  tolua_tonumber(tolua_S,6,0));
  signed int nNewStackCount = (( signed int)  tolua_tonumber(tolua_S,7,0));
  signed int nSpellID = (( signed int)  tolua_tonumber(tolua_S,8,0));
  signed int nSpellLevel = (( signed int)  tolua_tonumber(tolua_S,9,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AppendAura'", NULL);
#endif
 {
  CAuraInstance* tolua_ret = (CAuraInstance*)  self->AppendAura(pAuraInfo,poCaster,dwFromObjID,pExParam,nNewDurationFrm,nNewStackCount,nSpellID,nSpellLevel);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAuraInstance");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AppendAura'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFirstAura of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetFirstAura00
static int tolua_trade_CCharacter_GetFirstAura00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nAuraID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFirstAura'", NULL);
#endif
 {
  CAuraInstance* tolua_ret = (CAuraInstance*)  self->GetFirstAura(nAuraID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAuraInstance");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFirstAura'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAura of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_RemoveAura00
static int tolua_trade_CCharacter_RemoveAura00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CAuraInstance",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  CAuraInstance* pAura = ((CAuraInstance*)  tolua_tousertype(tolua_S,2,0));
   bool bTrigOnRemove = ((  bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAura'", NULL);
#endif
 {
  self->RemoveAura(pAura,bTrigOnRemove);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAura'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAuraByType of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_RemoveAuraByType00
static int tolua_trade_CCharacter_RemoveAuraByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAuraByType'", NULL);
#endif
 {
 int tolua_ret = (int)
self->RemoveAuraByType(nType);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAuraByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAuraBySubType of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_RemoveAuraBySubType00
static int tolua_trade_CCharacter_RemoveAuraBySubType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nSubType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAuraBySubType'", NULL);
#endif
 {
 int tolua_ret = (int)
self->RemoveAuraBySubType(nSubType);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAuraBySubType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDead of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_IsDead00
static int tolua_trade_CCharacter_IsDead00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDead'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsDead();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDead'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFlag of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetFlag00
static int tolua_trade_CCharacter_GetFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFlag'", NULL);
#endif
 {
  CFlagBits& tolua_ret = (CFlagBits&)  self->GetFlag();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CFlagBits");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetExFlag of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetExFlag00
static int tolua_trade_CCharacter_GetExFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetExFlag'", NULL);
#endif
 {
  CFlagBits& tolua_ret = (CFlagBits&)  self->GetExFlag();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CFlagBits");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetExFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCCFlag of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetCCFlag00
static int tolua_trade_CCharacter_GetCCFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCCFlag'", NULL);
#endif
 {
  CFlagBits& tolua_ret = (CFlagBits&)  self->GetCCFlag();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CFlagBits");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCCFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IncControlCount of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_IncControlCount00
static int tolua_trade_CCharacter_IncControlCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nControlType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IncControlCount'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IncControlCount(nControlType);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IncControlCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DecControlCount of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_DecControlCount00
static int tolua_trade_CCharacter_DecControlCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nControlType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DecControlCount'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DecControlCount(nControlType);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DecControlCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetControlCount of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetControlCount00
static int tolua_trade_CCharacter_GetControlCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nControlType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetControlCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetControlCount(nControlType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetControlCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLastCasterID of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetLastCasterID00
static int tolua_trade_CCharacter_SetLastCasterID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLastCasterID'", NULL);
#endif
 {
  self->SetLastCasterID(dwID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLastCasterID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLastCasterID of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetLastCasterID00
static int tolua_trade_CCharacter_GetLastCasterID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLastCasterID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetLastCasterID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLastCasterID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLastCasterTimer of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetLastCasterTimer00
static int tolua_trade_CCharacter_GetLastCasterTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLastCasterTimer'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetLastCasterTimer();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLastCasterTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLastTargetID of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetLastTargetID00
static int tolua_trade_CCharacter_SetLastTargetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwObjID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLastTargetID'", NULL);
#endif
 {
  self->SetLastTargetID(dwObjID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLastTargetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLastTargetID of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetLastTargetID00
static int tolua_trade_CCharacter_GetLastTargetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLastTargetID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetLastTargetID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLastTargetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLastTargetTimer of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetLastTargetTimer00
static int tolua_trade_CCharacter_GetLastTargetTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLastTargetTimer'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetLastTargetTimer();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLastTargetTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDropOwnerID of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetDropOwnerID00
static int tolua_trade_CCharacter_SetDropOwnerID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDropOwnerID'", NULL);
#endif
 {
  self->SetDropOwnerID(dwID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDropOwnerID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDropOwnerID of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetDropOwnerID00
static int tolua_trade_CCharacter_GetDropOwnerID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDropOwnerID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetDropOwnerID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDropOwnerID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SelectFocus of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SelectFocus00
static int tolua_trade_CCharacter_SelectFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTargetID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SelectFocus'", NULL);
#endif
 {
  self->SelectFocus(dwTargetID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SelectFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFocusID of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetFocusID00
static int tolua_trade_CCharacter_GetFocusID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFocusID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetFocusID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFocusID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Say of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_Say00
static int tolua_trade_CCharacter_Say00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isstring(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTargetID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwLocation = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  const char* pcszMessage = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Say'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->Say(dwTargetID,dwLocation,pcszMessage);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Say'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendMail of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SendMail00
static int tolua_trade_CCharacter_SendMail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  signed int nMailTemplateID = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendMail'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SendMail(dwRoleID,nMailTemplateID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendMail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendMail of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SendMail01
static int tolua_trade_CCharacter_SendMail01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  signed int nMailTemplateID = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nItemID = (( signed int)  tolua_tonumber(tolua_S,4,0));
  signed int nItemCount = (( signed int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendMail'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SendMail(dwRoleID,nMailTemplateID,nItemID,nItemCount);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_trade_CCharacter_SendMail00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAIProcessor of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetAIProcessor00
static int tolua_trade_CCharacter_SetAIProcessor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nAIID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAIProcessor'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetAIProcessor(nAIID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAIProcessor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAIProcessor of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetAIProcessor00
static int tolua_trade_CCharacter_GetAIProcessor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAIProcessor'", NULL);
#endif
 {
  CAIProcessor* tolua_ret = (CAIProcessor*)  self->GetAIProcessor();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAIProcessor");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAIProcessor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOriginalAiID of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetOriginalAiID00
static int tolua_trade_CCharacter_GetOriginalAiID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOriginalAiID'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetOriginalAiID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOriginalAiID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGlobalCDDelayFrame of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetGlobalCDDelayFrame00
static int tolua_trade_CCharacter_SetGlobalCDDelayFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int nFrame = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGlobalCDDelayFrame'", NULL);
#endif
 {
  self->SetGlobalCDDelayFrame(nFrame);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGlobalCDDelayFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGlobalCDDelayFrame of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetGlobalCDDelayFrame00
static int tolua_trade_CCharacter_GetGlobalCDDelayFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGlobalCDDelayFrame'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetGlobalCDDelayFrame();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGlobalCDDelayFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCoolDown of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetCoolDown00
static int tolua_trade_CCharacter_GetCoolDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCoolDown'", NULL);
#endif
 {
  CCoolDown& tolua_ret = (CCoolDown&)  self->GetCoolDown();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CCoolDown");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCoolDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHostID of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetHostID00
static int tolua_trade_CCharacter_GetHostID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHostID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetHostID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHostID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Mine of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_Mine00
static int tolua_trade_CCharacter_Mine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  signed int llDestX = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int llDestY = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Mine'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Mine(llDestX,llDestY);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Mine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CFlagBits */
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_new00
static int tolua_trade_CFlagBits_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CFlagBits",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CFlagBits* tolua_ret = (CFlagBits*)  Mtolua_new((CFlagBits)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CFlagBits");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CFlagBits */
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_new00_local
static int tolua_trade_CFlagBits_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CFlagBits",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CFlagBits* tolua_ret = (CFlagBits*)  Mtolua_new((CFlagBits)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CFlagBits");
 tolua_register_gc(tolua_S,lua_gettop(tolua_S));
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckFlag of class  CFlagBits */
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_CheckFlag00
static int tolua_trade_CFlagBits_CheckFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CFlagBits",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CFlagBits* self = (CFlagBits*)  tolua_tousertype(tolua_S,1,0);
  unsigned int eBit = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckFlag'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CheckFlag(eBit);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFlag of class  CFlagBits */
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_SetFlag00
static int tolua_trade_CFlagBits_SetFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CFlagBits",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CFlagBits* self = (CFlagBits*)  tolua_tousertype(tolua_S,1,0);
  unsigned int eBit = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFlag'", NULL);
#endif
 {
  self->SetFlag(eBit);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearFlag of class  CFlagBits */
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_ClearFlag00
static int tolua_trade_CFlagBits_ClearFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CFlagBits",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CFlagBits* self = (CFlagBits*)  tolua_tousertype(tolua_S,1,0);
  unsigned int eBit = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearFlag'", NULL);
#endif
 {
  self->ClearFlag(eBit);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetFlag of class  CFlagBits */
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_ResetFlag00
static int tolua_trade_CFlagBits_ResetFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CFlagBits",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CFlagBits* self = (CFlagBits*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetFlag'", NULL);
#endif
 {
  self->ResetFlag();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FlagIncludeBits of class  CFlagBits */
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_FlagIncludeBits00
static int tolua_trade_CFlagBits_FlagIncludeBits00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CFlagBits",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CFlagBits* self = (CFlagBits*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwMask = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FlagIncludeBits'", NULL);
#endif
 {
 int tolua_ret = (int)
self->FlagIncludeBits(dwMask);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FlagIncludeBits'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FlagNotIncludeBits of class  CFlagBits */
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_FlagNotIncludeBits00
static int tolua_trade_CFlagBits_FlagNotIncludeBits00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CFlagBits",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CFlagBits* self = (CFlagBits*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwMask = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FlagNotIncludeBits'", NULL);
#endif
 {
 int tolua_ret = (int)
self->FlagNotIncludeBits(dwMask);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FlagNotIncludeBits'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFlag of class  CFlagBits */
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_GetFlag00
static int tolua_trade_CFlagBits_GetFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CFlagBits",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CFlagBits* self = (CFlagBits*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFlag'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetFlag();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CSpellSlot */
#ifndef TOLUA_DISABLE_tolua_trade_CSpellSlot_new00
static int tolua_trade_CSpellSlot_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CSpellSlot",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CSpellSlot* tolua_ret = (CSpellSlot*)  Mtolua_new((CSpellSlot)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpellSlot");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CSpellSlot */
#ifndef TOLUA_DISABLE_tolua_trade_CSpellSlot_new00_local
static int tolua_trade_CSpellSlot_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CSpellSlot",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CSpellSlot* tolua_ret = (CSpellSlot*)  Mtolua_new((CSpellSlot)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpellSlot");
 tolua_register_gc(tolua_S,lua_gettop(tolua_S));
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CSpellSlot */
#ifndef TOLUA_DISABLE_tolua_trade_CSpellSlot_delete00
static int tolua_trade_CSpellSlot_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellSlot",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellSlot* self = (CSpellSlot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
 Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMainSpellID of class  CSpellSlot */
#ifndef TOLUA_DISABLE_tolua_trade_CSpellSlot_GetMainSpellID00
static int tolua_trade_CSpellSlot_GetMainSpellID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellSlot",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellSlot* self = (CSpellSlot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMainSpellID'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMainSpellID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMainSpellID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Init of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_Init00
static int tolua_trade_CRole_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwObjID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwSessionID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Init'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Init(dwObjID,dwSessionID);
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

/* method: UnInit of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_UnInit00
static int tolua_trade_CRole_UnInit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnInit'", NULL);
#endif
 {
 int tolua_ret = (int)
self->UnInit();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnInit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetName of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetName00
static int tolua_trade_CRole_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetName'", NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->GetName();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSessionID of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetSessionID00
static int tolua_trade_CRole_GetSessionID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSessionID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetSessionID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSessionID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetServerGroup of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetServerGroup00
static int tolua_trade_CRole_GetServerGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetServerGroup'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetServerGroup();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetServerGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSceneTempID of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetSceneTempID00
static int tolua_trade_CRole_GetSceneTempID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSceneTempID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetSceneTempID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSceneTempID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSceneID of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetSceneID00
static int tolua_trade_CRole_GetSceneID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSceneID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetSceneID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSceneID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LearnSpell of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_LearnSpell00
static int tolua_trade_CRole_LearnSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nSpellID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nSpellLevel = (( signed int)  tolua_tonumber(tolua_S,3,0));
   bool bNeedSave = ((  bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LearnSpell'", NULL);
#endif
 {
 int tolua_ret = (int)
self->LearnSpell(nSpellID,nSpellLevel,bNeedSave);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LearnSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EquipSpell of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_EquipSpell00
static int tolua_trade_CRole_EquipSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nSlotID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nSpellID = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EquipSpell'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->EquipSpell(nSlotID,nSpellID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EquipSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnlockSpellSlot of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_UnlockSpellSlot00
static int tolua_trade_CRole_UnlockSpellSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nSlotID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnlockSpellSlot'", NULL);
#endif
 {
 int tolua_ret = (int)
self->UnlockSpellSlot(nSlotID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnlockSpellSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpellSlot of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetSpellSlot00
static int tolua_trade_CRole_GetSpellSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nSlotID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpellSlot'", NULL);
#endif
 {
  CSpellSlot* tolua_ret = (CSpellSlot*)  self->GetSpellSlot(nSlotID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpellSlot");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpellSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSpellPts of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddSpellPts00
static int tolua_trade_CRole_AddSpellPts00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nSpellID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nPts = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSpellPts'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddSpellPts(nSpellID,nPts);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSpellPts'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveSpell of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_RemoveSpell00
static int tolua_trade_CRole_RemoveSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nSpellID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveSpell'", NULL);
#endif
 {
 int tolua_ret = (int)
self->RemoveSpell(nSpellID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EquipRune of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_EquipRune00
static int tolua_trade_CRole_EquipRune00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nSpell = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nRuneSlot = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EquipRune'", NULL);
#endif
 {
 int tolua_ret = (int)
self->EquipRune(nSpell,nRuneSlot);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EquipRune'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLastSlot of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetLastSlot00
static int tolua_trade_CRole_SetLastSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nSlotID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLastSlot'", NULL);
#endif
 {
  self->SetLastSlot(nSlotID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLastSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLastSlot of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetLastSlot00
static int tolua_trade_CRole_GetLastSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLastSlot'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetLastSlot();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLastSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearAllCooldown of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_ClearAllCooldown00
static int tolua_trade_CRole_ClearAllCooldown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearAllCooldown'", NULL);
#endif
 {
  self->ClearAllCooldown();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearAllCooldown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItemBag of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetItemBag00
static int tolua_trade_CRole_GetItemBag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItemBag'", NULL);
#endif
 {
  CItemBag* tolua_ret = (CItemBag*)  self->GetItemBag();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CItemBag");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItemBag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStall of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetStall00
static int tolua_trade_CRole_GetStall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStall'", NULL);
#endif
 {
  CStall* tolua_ret = (CStall*)  self->GetStall();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CStall");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetQuestList of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetQuestList00
static int tolua_trade_CRole_GetQuestList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetQuestList'", NULL);
#endif
 {
  CQuestList& tolua_ret = (CQuestList&)  self->GetQuestList();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CQuestList");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetQuestList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFreeMode of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetFreeMode00
static int tolua_trade_CRole_SetFreeMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  unsigned char byFreeMode = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFreeMode'", NULL);
#endif
 {
  self->SetFreeMode(byFreeMode);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFreeMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFreeMode of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_IsFreeMode00
static int tolua_trade_CRole_IsFreeMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFreeMode'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsFreeMode();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFreeMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFaction of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFaction00
static int tolua_trade_CRole_GetFaction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFaction'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetFaction();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFaction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFaction of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetFaction00
static int tolua_trade_CRole_SetFaction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nFaction = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFaction'", NULL);
#endif
 {
  self->SetFaction(nFaction);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFaction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetReputation of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetReputation00
static int tolua_trade_CRole_GetReputation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetReputation'", NULL);
#endif
 {
  CReputation& tolua_ret = (CReputation&)  self->GetReputation();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CReputation");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetReputation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTeamID of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetTeamID00
static int tolua_trade_CRole_GetTeamID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTeamID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetTeamID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTeamID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTrade of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetTrade00
static int tolua_trade_CRole_GetTrade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTrade'", NULL);
#endif
 {
  CTrade* tolua_ret = (CTrade*)  self->GetTrade();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTrade");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTrade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTitle of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetTitle00
static int tolua_trade_CRole_GetTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTitle'", NULL);
#endif
 {
  CTitle& tolua_ret = (CTitle&)  self->GetTitle();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CTitle");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaster of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetMaster00
static int tolua_trade_CRole_GetMaster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaster'", NULL);
#endif
 {
  CMaster& tolua_ret = (CMaster&)  self->GetMaster();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CMaster");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGuildID of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetGuildID00
static int tolua_trade_CRole_GetGuildID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGuildID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetGuildID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGuildID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoleGuildData of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetRoleGuildData00
static int tolua_trade_CRole_GetRoleGuildData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoleGuildData'", NULL);
#endif
 {
  CRoleGuildData& tolua_ret = (CRoleGuildData&)  self->GetRoleGuildData();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CRoleGuildData");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRoleGuildData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAsimovRole of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetAsimovRole00
static int tolua_trade_CRole_GetAsimovRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAsimovRole'", NULL);
#endif
 {
  CAsimovRole* tolua_ret = (CAsimovRole*)  self->GetAsimovRole();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAsimovRole");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAsimovRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFriend of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFriend00
static int tolua_trade_CRole_GetFriend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFriend'", NULL);
#endif
 {
  CFriend* tolua_ret = (CFriend*)  self->GetFriend();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CFriend");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFriend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShieldList of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetShieldList00
static int tolua_trade_CRole_GetShieldList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShieldList'", NULL);
#endif
 {
  CShieldList* tolua_ret = (CShieldList*)  self->GetShieldList();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CShieldList");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShieldList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetArena of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetArena00
static int tolua_trade_CRole_GetArena00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetArena'", NULL);
#endif
 {
  CArena& tolua_ret = (CArena&)  self->GetArena();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CArena");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetArena'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHero of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetHero00
static int tolua_trade_CRole_GetHero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHero'", NULL);
#endif
 {
  CHero* tolua_ret = (CHero*)  self->GetHero();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CHero");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddExp of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddExp00
static int tolua_trade_CRole_AddExp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nExp = (( signed int)  tolua_tonumber(tolua_S,2,0));
   bool bByKillNpc = ((  bool)  tolua_toboolean(tolua_S,3,0));
   bool byDailyLimitExp = ((  bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddExp'", NULL);
#endif
 {
  self->AddExp(nExp,bByKillNpc,byDailyLimitExp);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddExp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetExp of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetExp00
static int tolua_trade_CRole_GetExp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetExp'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetExp();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetExp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetExtraExp of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetExtraExp00
static int tolua_trade_CRole_GetExtraExp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetExtraExp'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetExtraExp();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetExtraExp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddExtraExp of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddExtraExp00
static int tolua_trade_CRole_AddExtraExp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nExp = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddExtraExp'", NULL);
#endif
 {
  self->AddExtraExp(nExp);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddExtraExp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TryRevive of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_TryRevive00
static int tolua_trade_CRole_TryRevive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TryRevive'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->TryRevive(nType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TryRevive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ActivateMount of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_ActivateMount00
static int tolua_trade_CRole_ActivateMount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nMountID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ActivateMount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->ActivateMount(nMountID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ActivateMount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMount of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_OnMount00
static int tolua_trade_CRole_OnMount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nMountID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMount'", NULL);
#endif
 {
 int tolua_ret = (int)
self->OnMount(nMountID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OffMount of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_OffMount00
static int tolua_trade_CRole_OffMount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OffMount'", NULL);
#endif
 {
  self->OffMount();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OffMount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVIPLevel of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetVIPLevel00
static int tolua_trade_CRole_GetVIPLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVIPLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetVIPLevel();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVIPLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SubscribeVIP of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SubscribeVIP00
static int tolua_trade_CRole_SubscribeVIP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nVIPLevel = (( signed int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwMonth = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SubscribeVIP'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->SubscribeVIP(nVIPLevel,dwMonth);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SubscribeVIP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVIPTime of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetVIPTime00
static int tolua_trade_CRole_GetVIPTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nVIPLevel = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVIPTime'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetVIPTime(nVIPLevel);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVIPTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTotalOnlineTime of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetTotalOnlineTime00
static int tolua_trade_CRole_GetTotalOnlineTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTotalOnlineTime'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetTotalOnlineTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTotalOnlineTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevelOnlineTime of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetLevelOnlineTime00
static int tolua_trade_CRole_GetLevelOnlineTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevelOnlineTime'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetLevelOnlineTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLevelOnlineTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChangePkMode of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_ChangePkMode00
static int tolua_trade_CRole_ChangePkMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nMode = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChangePkMode'", NULL);
#endif
 {
  self->ChangePkMode(nMode);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChangePkMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsRedName of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_IsRedName00
static int tolua_trade_CRole_IsRedName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsRedName'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsRedName();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsRedName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetState of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetState00
static int tolua_trade_CRole_GetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetState'", NULL);
#endif
 {
  ERoleState tolua_ret = (ERoleState)  self->GetState();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVariable of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetVariable00
static int tolua_trade_CRole_SetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nValue = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVariable'", NULL);
#endif
 {
  self->SetVariable(nIndex,nValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVariable of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetVariable00
static int tolua_trade_CRole_GetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVariable'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetVariable(nIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetClientVariable of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetClientVariable00
static int tolua_trade_CRole_GetClientVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClientVariable'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetClientVariable(nIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClientVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetClientVariable of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetClientVariable00
static int tolua_trade_CRole_SetClientVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nValue = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetClientVariable'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetClientVariable(nIndex,nValue);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetClientVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPkValue of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetPkValue00
static int tolua_trade_CRole_GetPkValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPkValue'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetPkValue();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPkValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPkValue of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetPkValue00
static int tolua_trade_CRole_SetPkValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwPkValue = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPkValue'", NULL);
#endif
 {
  self->SetPkValue(dwPkValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPkValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAchievementList of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetAchievementList00
static int tolua_trade_CRole_GetAchievementList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAchievementList'", NULL);
#endif
 {
  CAchievementsList& tolua_ret = (CAchievementsList&)  self->GetAchievementList();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CAchievementsList");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAchievementList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HireHero of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_HireHero00
static int tolua_trade_CRole_HireHero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,7,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nClass = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nSex = (( signed int)  tolua_tonumber(tolua_S,4,0));
  unsigned int dwHeroExp = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
  signed int eAiType = (( signed int)  tolua_tonumber(tolua_S,6,0));
   bool bFirstTime = ((  bool)  tolua_toboolean(tolua_S,7,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HireHero'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->HireHero(nLevel,nClass,nSex,dwHeroExp,eAiType,bFirstTime);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HireHero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FireHero of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_FireHero00
static int tolua_trade_CRole_FireHero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FireHero'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->FireHero();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FireHero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SummonHero of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SummonHero00
static int tolua_trade_CRole_SummonHero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SummonHero'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->SummonHero();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SummonHero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RecallHero of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_RecallHero00
static int tolua_trade_CRole_RecallHero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
   bool bNotify = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RecallHero'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->RecallHero(bNotify);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RecallHero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpirit of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetSpirit00
static int tolua_trade_CRole_GetSpirit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpirit'", NULL);
#endif
 {
  CSpirit& tolua_ret = (CSpirit&)  self->GetSpirit();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CSpirit");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpirit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckDistance of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_CheckDistance00
static int tolua_trade_CRole_CheckDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CSceneObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  CSceneObject* poSceneObject = ((CSceneObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckDistance'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CheckDistance(poSceneObject);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInteractNpc of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetInteractNpc00
static int tolua_trade_CRole_GetInteractNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInteractNpc'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetInteractNpc();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInteractNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Interact of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_Interact00
static int tolua_trade_CRole_Interact00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CNpc",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  CNpc* poNpc = ((CNpc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Interact'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Interact(poNpc);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Interact'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddActivity of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddActivity00
static int tolua_trade_CRole_AddActivity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nActivity = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddActivity'", NULL);
#endif
 {
  self->AddActivity(nActivity);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddActivity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetActivity of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetActivity00
static int tolua_trade_CRole_GetActivity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetActivity'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetActivity();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetActivity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddActivityReward of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddActivityReward00
static int tolua_trade_CRole_AddActivityReward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nActivityRewardIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddActivityReward'", NULL);
#endif
 {
  self->AddActivityReward(nActivityRewardIndex);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddActivityReward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetActivityRewardByIndex of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetActivityRewardByIndex00
static int tolua_trade_CRole_GetActivityRewardByIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nActivityRewardIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetActivityRewardByIndex'", NULL);
#endif
 {
 int tolua_ret = (int)
self->GetActivityRewardByIndex(nActivityRewardIndex);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetActivityRewardByIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetActivityReward of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetActivityReward00
static int tolua_trade_CRole_GetActivityReward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetActivityReward'", NULL);
#endif
 {
 int tolua_ret = (int)
self->GetActivityReward();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetActivityReward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearActivity of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_ClearActivity00
static int tolua_trade_CRole_ClearActivity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearActivity'", NULL);
#endif
 {
  self->ClearActivity();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearActivity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFirstMail of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFirstMail00
static int tolua_trade_CRole_GetFirstMail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CRole* self = (const CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFirstMail'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetFirstMail();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFirstMail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFirstAttach of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFirstAttach00
static int tolua_trade_CRole_GetFirstAttach00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CRole* self = (const CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFirstAttach'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetFirstAttach();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFirstAttach'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRandomAuctionItemID of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetRandomAuctionItemID00
static int tolua_trade_CRole_GetRandomAuctionItemID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CRole* self = (const CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRandomAuctionItemID'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetRandomAuctionItemID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRandomAuctionItemID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFirstSellingAuction of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFirstSellingAuction00
static int tolua_trade_CRole_GetFirstSellingAuction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CRole* self = (const CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFirstSellingAuction'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetFirstSellingAuction();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFirstSellingAuction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFirstBuyingAuction of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFirstBuyingAuction00
static int tolua_trade_CRole_GetFirstBuyingAuction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CRole* self = (const CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFirstBuyingAuction'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetFirstBuyingAuction();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFirstBuyingAuction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Hide of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_Hide00
static int tolua_trade_CRole_Hide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
   bool bHidden = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Hide'", NULL);
#endif
 {
  self->Hide(bHidden);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Hide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsHidden of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_IsHidden00
static int tolua_trade_CRole_IsHidden00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsHidden'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsHidden();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsHidden'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGMLevel of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetGMLevel00
static int tolua_trade_CRole_GetGMLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGMLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetGMLevel();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGMLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGMLevel of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetGMLevel00
static int tolua_trade_CRole_SetGMLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nGMLevel = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGMLevel'", NULL);
#endif
 {
  self->SetGMLevel(nGMLevel);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGMLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFcmState of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetFcmState00
static int tolua_trade_CRole_SetFcmState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  unsigned char eFcmState = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFcmState'", NULL);
#endif
 {
  self->SetFcmState(eFcmState);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFcmState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFcmState of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFcmState00
static int tolua_trade_CRole_GetFcmState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFcmState'", NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->GetFcmState();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFcmState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Kick of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_Kick00
static int tolua_trade_CRole_Kick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Kick'", NULL);
#endif
 {
  self->Kick();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Kick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Kick of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_Kick01
static int tolua_trade_CRole_Kick01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isstring(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int eKickType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  const char* pcszFileName = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* pcszFuncName = ((const char*)  tolua_tostring(tolua_S,4,0));
  signed int nLineNum = (( signed int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Kick'", NULL);
#endif
 {
  self->Kick(eKickType,pcszFileName,pcszFuncName,nLineNum);
 }
 }
 return 0;
tolua_lerror:
 return tolua_trade_CRole_Kick00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ErrorCodeNotify of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_ErrorCodeNotify00
static int tolua_trade_CRole_ErrorCodeNotify00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nErrCode = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nParam1 = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nParam2 = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ErrorCodeNotify'", NULL);
#endif
 {
 int tolua_ret = (int)
self->ErrorCodeNotify(nErrCode,nParam1,nParam2);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ErrorCodeNotify'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ForceSyncPos of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_ForceSyncPos00
static int tolua_trade_CRole_ForceSyncPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ForceSyncPos'", NULL);
#endif
 {
 int tolua_ret = (int)
self->ForceSyncPos();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ForceSyncPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TransferRole of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_TransferRole00
static int tolua_trade_CRole_TransferRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int llDestX = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int llDestY = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int llDestZ = (( signed int)  tolua_tonumber(tolua_S,4,0));
  signed int nRange = (( signed int)  tolua_tonumber(tolua_S,5,0));
  signed int nCount = (( signed int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TransferRole'", NULL);
#endif
 {
 int tolua_ret = (int)
self->TransferRole(llDestX,llDestY,llDestZ,nRange,nCount);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TransferRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRevivePos of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetRevivePos00
static int tolua_trade_CRole_GetRevivePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRevivePos'", NULL);
#endif
 {
  const ABSOLUTE_SCENE_POS& tolua_ret = (const ABSOLUTE_SCENE_POS&)  self->GetRevivePos();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ABSOLUTE_SCENE_POS");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRevivePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GenerateAntiCheatJigsaw of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GenerateAntiCheatJigsaw00
static int tolua_trade_CRole_GenerateAntiCheatJigsaw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GenerateAntiCheatJigsaw'", NULL);
#endif
 {
  self->GenerateAntiCheatJigsaw();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GenerateAntiCheatJigsaw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPetState of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetPetState00
static int tolua_trade_CRole_GetPetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPetState'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetPetState();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPetState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPetState of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetPetState00
static int tolua_trade_CRole_SetPetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nState = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPetState'", NULL);
#endif
 {
  self->SetPetState(nState);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPetState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddPet of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddPet00
static int tolua_trade_CRole_AddPet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwNpcID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  signed int nPetType = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddPet'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddPet(dwNpcID,nPetType);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddPet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPetCount of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetPetCount00
static int tolua_trade_CRole_GetPetCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPetCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetPetCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPetCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxPetCount of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetMaxPetCount00
static int tolua_trade_CRole_GetMaxPetCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxPetCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMaxPetCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxPetCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPetNpcID of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetPetNpcID00
static int tolua_trade_CRole_GetPetNpcID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPetNpcID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetPetNpcID(nIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPetNpcID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GMCreateGuild of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GMCreateGuild00
static int tolua_trade_CRole_GMCreateGuild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  char* pszGuildName = ((char*)  tolua_tostring(tolua_S,2,0));
  char* pszAnnounce = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GMCreateGuild'", NULL);
#endif
 {
 int tolua_ret = (int)
self->GMCreateGuild(pszGuildName,pszAnnounce);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GMCreateGuild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetJumpRandomNumber of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetJumpRandomNumber00
static int tolua_trade_CRole_GetJumpRandomNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetJumpRandomNumber'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetJumpRandomNumber();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetJumpRandomNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: QueryRoleLocation of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_QueryRoleLocation00
static int tolua_trade_CRole_QueryRoleLocation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  const char* pcszRoleName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'QueryRoleLocation'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->QueryRoleLocation(pcszRoleName);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'QueryRoleLocation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RecallTeamMember of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_RecallTeamMember00
static int tolua_trade_CRole_RecallTeamMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RecallTeamMember'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->RecallTeamMember();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RecallTeamMember'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsSabacGuildMember of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_IsSabacGuildMember00
static int tolua_trade_CRole_IsSabacGuildMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsSabacGuildMember'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsSabacGuildMember();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsSabacGuildMember'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckIn of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_CheckIn00
static int tolua_trade_CRole_CheckIn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckIn'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->CheckIn();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckIn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStartExerciseTime of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetStartExerciseTime00
static int tolua_trade_CRole_GetStartExerciseTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CRole* self = (const CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStartExerciseTime'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetStartExerciseTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStartExerciseTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStartExerciseTime of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetStartExerciseTime00
static int tolua_trade_CRole_SetStartExerciseTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStartExerciseTime'", NULL);
#endif
 {
  self->SetStartExerciseTime(dwTime);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStartExerciseTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdateRankListNode of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_UpdateRankListNode00
static int tolua_trade_CRole_UpdateRankListNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nRankListType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nValue1 = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nValue2 = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdateRankListNode'", NULL);
#endif
 {
 int tolua_ret = (int)
self->UpdateRankListNode(nRankListType,nValue1,nValue2);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdateRankListNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GenerateAntiCheatJigsaw of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GenerateAntiCheatJigsaw01
static int tolua_trade_CRole_GenerateAntiCheatJigsaw01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GenerateAntiCheatJigsaw'", NULL);
#endif
 {
  self->GenerateAntiCheatJigsaw();
 }
 }
 return 0;
tolua_lerror:
 return tolua_trade_CRole_GenerateAntiCheatJigsaw00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAntiCheatLevel of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetAntiCheatLevel00
static int tolua_trade_CRole_SetAntiCheatLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAntiCheatLevel'", NULL);
#endif
 {
  self->SetAntiCheatLevel(nLevel);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAntiCheatLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGameTimeCard_UINT32 of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetGameTimeCard_UINT3200
static int tolua_trade_CRole_GetGameTimeCard_UINT3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGameTimeCard_UINT32'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetGameTimeCard_UINT32();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGameTimeCard_UINT32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddGameTimeCard of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddGameTimeCard00
static int tolua_trade_CRole_AddGameTimeCard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  unsigned int time = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddGameTimeCard'", NULL);
#endif
 {
  self->AddGameTimeCard(time);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddGameTimeCard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NotifyRole_GameTimeCard of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_NotifyRole_GameTimeCard00
static int tolua_trade_CRole_NotifyRole_GameTimeCard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NotifyRole_GameTimeCard'", NULL);
#endif
 {
  self->NotifyRole_GameTimeCard();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NotifyRole_GameTimeCard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRuneRootCount of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetRuneRootCount00
static int tolua_trade_CRole_GetRuneRootCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int cls = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRuneRootCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetRuneRootCount(nType,cls);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRuneRootCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IncRuneRootCount of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_IncRuneRootCount00
static int tolua_trade_CRole_IncRuneRootCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int cls = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IncRuneRootCount'", NULL);
#endif
 {
  self->IncRuneRootCount(nType,cls);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IncRuneRootCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NotifyRole_RuneRootCount of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_NotifyRole_RuneRootCount00
static int tolua_trade_CRole_NotifyRole_RuneRootCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int cls = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NotifyRole_RuneRootCount'", NULL);
#endif
 {
  self->NotifyRole_RuneRootCount(nType,cls);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NotifyRole_RuneRootCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLuckRootCount of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetLuckRootCount00
static int tolua_trade_CRole_GetLuckRootCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLuckRootCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetLuckRootCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLuckRootCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IncLuckRootCount of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_IncLuckRootCount00
static int tolua_trade_CRole_IncLuckRootCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IncLuckRootCount'", NULL);
#endif
 {
  self->IncLuckRootCount();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IncLuckRootCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NotifyRole_LuckRootCount of class  CRole */
#ifndef TOLUA_DISABLE_tolua_trade_CRole_NotifyRole_LuckRootCount00
static int tolua_trade_CRole_NotifyRole_LuckRootCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRole* self = (CRole*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NotifyRole_LuckRootCount'", NULL);
#endif
 {
  self->NotifyRole_LuckRootCount();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NotifyRole_LuckRootCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetValue of class  CReputation */
#ifndef TOLUA_DISABLE_tolua_trade_CReputation_GetValue00
static int tolua_trade_CReputation_GetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CReputation",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CReputation* self = (CReputation*)  tolua_tousertype(tolua_S,1,0);
  signed int nForceID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetValue'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetValue(nForceID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetValue of class  CReputation */
#ifndef TOLUA_DISABLE_tolua_trade_CReputation_SetValue00
static int tolua_trade_CReputation_SetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CReputation",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CReputation* self = (CReputation*)  tolua_tousertype(tolua_S,1,0);
  signed int nForceID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nNewValue = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetValue'", NULL);
#endif
 {
  self->SetValue(nForceID,nNewValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ModifyValue of class  CReputation */
#ifndef TOLUA_DISABLE_tolua_trade_CReputation_ModifyValue00
static int tolua_trade_CReputation_ModifyValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CReputation",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CReputation* self = (CReputation*)  tolua_tousertype(tolua_S,1,0);
  signed int nForceID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nValue = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ModifyValue'", NULL);
#endif
 {
  self->ModifyValue(nForceID,nValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ModifyValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ActiveForce of class  CReputation */
#ifndef TOLUA_DISABLE_tolua_trade_CReputation_ActiveForce00
static int tolua_trade_CReputation_ActiveForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CReputation",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CReputation* self = (CReputation*)  tolua_tousertype(tolua_S,1,0);
  signed int nForceID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ActiveForce'", NULL);
#endif
 {
  self->ActiveForce(nForceID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ActiveForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReceiveAward of class  CReputation */
#ifndef TOLUA_DISABLE_tolua_trade_CReputation_ReceiveAward00
static int tolua_trade_CReputation_ReceiveAward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CReputation",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CReputation* self = (CReputation*)  tolua_tousertype(tolua_S,1,0);
  signed int nForceID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReceiveAward'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->ReceiveAward(nForceID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReceiveAward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_new00
static int tolua_trade_CTrade_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CTrade",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CTrade* tolua_ret = (CTrade*)  Mtolua_new((CTrade)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTrade");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_new00_local
static int tolua_trade_CTrade_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CTrade",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CTrade* tolua_ret = (CTrade*)  Mtolua_new((CTrade)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTrade");
 tolua_register_gc(tolua_S,lua_gettop(tolua_S));
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_Clear00
static int tolua_trade_CTrade_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTrade",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTrade* self = (CTrade*)  tolua_tousertype(tolua_S,1,0);
   bool bClearTarget = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clear'", NULL);
#endif
 {
  self->Clear(bClearTarget);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOwner of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_SetOwner00
static int tolua_trade_CTrade_SetOwner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTrade",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTrade* self = (CTrade*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AskTrade of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_AskTrade00
static int tolua_trade_CTrade_AskTrade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTrade",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTrade* self = (CTrade*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AskTrade'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->AskTrade(dwRoleID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AskTrade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AcceptTrade of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_AcceptTrade00
static int tolua_trade_CTrade_AcceptTrade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTrade",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTrade* self = (CTrade*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AcceptTrade'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->AcceptTrade(dwRoleID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AcceptTrade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetItem of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_SetItem00
static int tolua_trade_CTrade_SetItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTrade",0,&tolua_err) ||
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
  CTrade* self = (CTrade*)  tolua_tousertype(tolua_S,1,0);
  unsigned char byTradeSlot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char bAdd = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
  unsigned char byConSlot = (( unsigned char)  tolua_tonumber(tolua_S,4,0));
  unsigned char byItemSlot = (( unsigned char)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetItem'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->SetItem(byTradeSlot,bAdd,byConSlot,byItemSlot);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMoney of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_SetMoney00
static int tolua_trade_CTrade_SetMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTrade",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTrade* self = (CTrade*)  tolua_tousertype(tolua_S,1,0);
  signed int nCount = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMoney'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->SetMoney(nCount);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LockTrade of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_LockTrade00
static int tolua_trade_CTrade_LockTrade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTrade",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTrade* self = (CTrade*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LockTrade'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->LockTrade();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LockTrade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ConfirmTrade of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_ConfirmTrade00
static int tolua_trade_CTrade_ConfirmTrade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTrade",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTrade* self = (CTrade*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ConfirmTrade'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->ConfirmTrade();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ConfirmTrade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnlockTrade of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_UnlockTrade00
static int tolua_trade_CTrade_UnlockTrade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTrade",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTrade* self = (CTrade*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnlockTrade'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->UnlockTrade();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnlockTrade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CancelTrade of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_CancelTrade00
static int tolua_trade_CTrade_CancelTrade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTrade",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTrade* self = (CTrade*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CancelTrade'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->CancelTrade();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CancelTrade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsTrading of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_IsTrading00
static int tolua_trade_CTrade_IsTrading00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTrade",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTrade* self = (CTrade*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsTrading'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsTrading();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsTrading'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsTradeItem of class  CTrade */
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_IsTradeItem00
static int tolua_trade_CTrade_IsTradeItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CTrade",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CTrade* self = (const CTrade*)  tolua_tousertype(tolua_S,1,0);
  unsigned char byContainerSlot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char byItemSlot = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsTradeItem'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsTradeItem(byContainerSlot,byItemSlot);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsTradeItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_trade_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CSceneObject","CSceneObject","",NULL);
 tolua_beginmodule(tolua_S,"CSceneObject");
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetObjID00
  tolua_function(tolua_S,"GetObjID",tolua_trade_CSceneObject_GetObjID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetObjType00
  tolua_function(tolua_S,"GetObjType",tolua_trade_CSceneObject_GetObjType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetScene00
  tolua_function(tolua_S,"GetScene",tolua_trade_CSceneObject_GetScene00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetRegion00
  tolua_function(tolua_S,"GetRegion",tolua_trade_CSceneObject_GetRegion00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetZone00
  tolua_function(tolua_S,"GetZone",tolua_trade_CSceneObject_GetZone00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetGrid00
  tolua_function(tolua_S,"GetGrid",tolua_trade_CSceneObject_GetGrid00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetGridInstance00
  tolua_function(tolua_S,"GetGridInstance",tolua_trade_CSceneObject_GetGridInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetX00
  tolua_function(tolua_S,"SetX",tolua_trade_CSceneObject_SetX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetY00
  tolua_function(tolua_S,"SetY",tolua_trade_CSceneObject_SetY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetZ00
  tolua_function(tolua_S,"SetZ",tolua_trade_CSceneObject_SetZ00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetX00
  tolua_function(tolua_S,"GetX",tolua_trade_CSceneObject_GetX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetY00
  tolua_function(tolua_S,"GetY",tolua_trade_CSceneObject_GetY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetZ00
  tolua_function(tolua_S,"GetZ",tolua_trade_CSceneObject_GetZ00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetFaceDirection00
  tolua_function(tolua_S,"SetFaceDirection",tolua_trade_CSceneObject_SetFaceDirection00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetFaceDirection00
  tolua_function(tolua_S,"GetFaceDirection",tolua_trade_CSceneObject_GetFaceDirection00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetBodyType00
  tolua_function(tolua_S,"SetBodyType",tolua_trade_CSceneObject_SetBodyType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetBodyType00
  tolua_function(tolua_S,"GetBodyType",tolua_trade_CSceneObject_GetBodyType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_CanTeleport00
  tolua_function(tolua_S,"CanTeleport",tolua_trade_CSceneObject_CanTeleport00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetObjID01
  tolua_function(tolua_S,"GetObjID",tolua_trade_CSceneObject_GetObjID01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetObjType01
  tolua_function(tolua_S,"GetObjType",tolua_trade_CSceneObject_GetObjType01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetScene01
  tolua_function(tolua_S,"GetScene",tolua_trade_CSceneObject_GetScene01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetRegion01
  tolua_function(tolua_S,"GetRegion",tolua_trade_CSceneObject_GetRegion01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetZone01
  tolua_function(tolua_S,"GetZone",tolua_trade_CSceneObject_GetZone01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetGrid01
  tolua_function(tolua_S,"GetGrid",tolua_trade_CSceneObject_GetGrid01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetGridInstance01
  tolua_function(tolua_S,"GetGridInstance",tolua_trade_CSceneObject_GetGridInstance01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetX01
  tolua_function(tolua_S,"SetX",tolua_trade_CSceneObject_SetX01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetY01
  tolua_function(tolua_S,"SetY",tolua_trade_CSceneObject_SetY01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetZ01
  tolua_function(tolua_S,"SetZ",tolua_trade_CSceneObject_SetZ01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetX01
  tolua_function(tolua_S,"GetX",tolua_trade_CSceneObject_GetX01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetY01
  tolua_function(tolua_S,"GetY",tolua_trade_CSceneObject_GetY01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetZ01
  tolua_function(tolua_S,"GetZ",tolua_trade_CSceneObject_GetZ01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetFaceDirection01
  tolua_function(tolua_S,"SetFaceDirection",tolua_trade_CSceneObject_SetFaceDirection01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetFaceDirection01
  tolua_function(tolua_S,"GetFaceDirection",tolua_trade_CSceneObject_GetFaceDirection01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_SetBodyType01
  tolua_function(tolua_S,"SetBodyType",tolua_trade_CSceneObject_SetBodyType01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_GetBodyType01
  tolua_function(tolua_S,"GetBodyType",tolua_trade_CSceneObject_GetBodyType01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSceneObject_CanTeleport01
  tolua_function(tolua_S,"CanTeleport",tolua_trade_CSceneObject_CanTeleport01);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CAuraInstance","CAuraInstance","CAura",NULL);
 tolua_beginmodule(tolua_S,"CAuraInstance");
#ifndef TOLUA_DISABLE_tolua_trade_CAuraInstance_GetInstanceID00
  tolua_function(tolua_S,"GetInstanceID",tolua_trade_CAuraInstance_GetInstanceID00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CCoolDown","CCoolDown","",NULL);
 tolua_beginmodule(tolua_S,"CCoolDown");
#ifndef TOLUA_DISABLE_tolua_trade_CCoolDown_Add00
  tolua_function(tolua_S,"Add",tolua_trade_CCoolDown_Add00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCoolDown_Reset00
  tolua_function(tolua_S,"Reset",tolua_trade_CCoolDown_Reset00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCoolDown_CheckReady00
  tolua_function(tolua_S,"CheckReady",tolua_trade_CCoolDown_CheckReady00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCoolDown_GetRemainFrm00
  tolua_function(tolua_S,"GetRemainFrm",tolua_trade_CCoolDown_GetRemainFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCoolDown_Enable00
  tolua_function(tolua_S,"Enable",tolua_trade_CCoolDown_Enable00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 #ifdef __cplusplus
 tolua_cclass(tolua_S,"CTargetScanner","CTargetScanner","",tolua_collect_CTargetScanner);
 #else
 tolua_cclass(tolua_S,"CTargetScanner","CTargetScanner","",NULL);
 #endif
 tolua_beginmodule(tolua_S,"CTargetScanner");
#ifndef TOLUA_DISABLE_tolua_trade_CTargetScanner_new00
  tolua_function(tolua_S,"new",tolua_trade_CTargetScanner_new00);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_trade_CTargetScanner_new00_local);
  tolua_function(tolua_S,".call",tolua_trade_CTargetScanner_new00_local);
#ifndef TOLUA_DISABLE_tolua_trade_CTargetScanner_delete00
  tolua_function(tolua_S,"delete",tolua_trade_CTargetScanner_delete00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTargetScanner_GetTargetX00
  tolua_function(tolua_S,"GetTargetX",tolua_trade_CTargetScanner_GetTargetX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTargetScanner_GetTargetY00
  tolua_function(tolua_S,"GetTargetY",tolua_trade_CTargetScanner_GetTargetY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTargetScanner_GetTargetZ00
  tolua_function(tolua_S,"GetTargetZ",tolua_trade_CTargetScanner_GetTargetZ00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 #ifdef __cplusplus
 tolua_cclass(tolua_S,"CSpellInstance","CSpellInstance","",tolua_collect_CSpellInstance);
 #else
 tolua_cclass(tolua_S,"CSpellInstance","CSpellInstance","",NULL);
 #endif
 tolua_beginmodule(tolua_S,"CSpellInstance");
#ifndef TOLUA_DISABLE_tolua_trade_CSpellInstance_new00
  tolua_function(tolua_S,"new",tolua_trade_CSpellInstance_new00);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_trade_CSpellInstance_new00_local);
  tolua_function(tolua_S,".call",tolua_trade_CSpellInstance_new00_local);
#ifndef TOLUA_DISABLE_tolua_trade_CSpellInstance_delete00
  tolua_function(tolua_S,"delete",tolua_trade_CSpellInstance_delete00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSpellInstance_GetScanner00
  tolua_function(tolua_S,"GetScanner",tolua_trade_CSpellInstance_GetScanner00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CCharacter","CCharacter","CSceneObject",NULL);
 tolua_beginmodule(tolua_S,"CCharacter");
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_JumpTo00
  tolua_function(tolua_S,"JumpTo",tolua_trade_CCharacter_JumpTo00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetClass00
  tolua_function(tolua_S,"GetClass",tolua_trade_CCharacter_GetClass00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetSex00
  tolua_function(tolua_S,"GetSex",tolua_trade_CCharacter_GetSex00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetLevel00
  tolua_function(tolua_S,"GetLevel",tolua_trade_CCharacter_GetLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetName00
  tolua_function(tolua_S,"GetName",tolua_trade_CCharacter_GetName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetClass00
  tolua_function(tolua_S,"SetClass",tolua_trade_CCharacter_SetClass00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetSex00
  tolua_function(tolua_S,"SetSex",tolua_trade_CCharacter_SetSex00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetLevel00
  tolua_function(tolua_S,"SetLevel",tolua_trade_CCharacter_SetLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetAttr00
  tolua_function(tolua_S,"GetAttr",tolua_trade_CCharacter_GetAttr00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetAttrList00
  tolua_function(tolua_S,"GetAttrList",tolua_trade_CCharacter_GetAttrList00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetInCutScene00
  tolua_function(tolua_S,"SetInCutScene",tolua_trade_CCharacter_SetInCutScene00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_MoveTo00
  tolua_function(tolua_S,"MoveTo",tolua_trade_CCharacter_MoveTo00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_Die00
  tolua_function(tolua_S,"Die",tolua_trade_CCharacter_Die00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_Revive00
  tolua_function(tolua_S,"Revive",tolua_trade_CCharacter_Revive00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_RotateTo00
  tolua_function(tolua_S,"RotateTo",tolua_trade_CCharacter_RotateTo00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetCanRun00
  tolua_function(tolua_S,"SetCanRun",tolua_trade_CCharacter_SetCanRun00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetMoveState00
  tolua_function(tolua_S,"GetMoveState",tolua_trade_CCharacter_GetMoveState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetHome00
  tolua_function(tolua_S,"SetHome",tolua_trade_CCharacter_SetHome00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetHomeX00
  tolua_function(tolua_S,"GetHomeX",tolua_trade_CCharacter_GetHomeX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetHomeY00
  tolua_function(tolua_S,"GetHomeY",tolua_trade_CCharacter_GetHomeY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetHomeZ00
  tolua_function(tolua_S,"GetHomeZ",tolua_trade_CCharacter_GetHomeZ00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_CancelCast00
  tolua_function(tolua_S,"CancelCast",tolua_trade_CCharacter_CancelCast00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_IsCasting00
  tolua_function(tolua_S,"IsCasting",tolua_trade_CCharacter_IsCasting00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_EquipRune00
  tolua_function(tolua_S,"EquipRune",tolua_trade_CCharacter_EquipRune00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_UnEquipRune00
  tolua_function(tolua_S,"UnEquipRune",tolua_trade_CCharacter_UnEquipRune00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetSpellSlot00
  tolua_function(tolua_S,"GetSpellSlot",tolua_trade_CCharacter_GetSpellSlot00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_CastSpell00
  tolua_function(tolua_S,"CastSpell",tolua_trade_CCharacter_CastSpell00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_PlayAction00
  tolua_function(tolua_S,"PlayAction",tolua_trade_CCharacter_PlayAction00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetCastingSpell00
  tolua_function(tolua_S,"GetCastingSpell",tolua_trade_CCharacter_GetCastingSpell00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetHp00
  tolua_function(tolua_S,"GetHp",tolua_trade_CCharacter_GetHp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetHp00
  tolua_function(tolua_S,"SetHp",tolua_trade_CCharacter_SetHp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_ChangeHp00
  tolua_function(tolua_S,"ChangeHp",tolua_trade_CCharacter_ChangeHp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetMp00
  tolua_function(tolua_S,"GetMp",tolua_trade_CCharacter_GetMp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_ChangeMp00
  tolua_function(tolua_S,"ChangeMp",tolua_trade_CCharacter_ChangeMp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_CanAttack00
  tolua_function(tolua_S,"CanAttack",tolua_trade_CCharacter_CanAttack00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetSpellBook00
  tolua_function(tolua_S,"GetSpellBook",tolua_trade_CCharacter_GetSpellBook00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_AppendAura00
  tolua_function(tolua_S,"AppendAura",tolua_trade_CCharacter_AppendAura00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetFirstAura00
  tolua_function(tolua_S,"GetFirstAura",tolua_trade_CCharacter_GetFirstAura00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_RemoveAura00
  tolua_function(tolua_S,"RemoveAura",tolua_trade_CCharacter_RemoveAura00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_RemoveAuraByType00
  tolua_function(tolua_S,"RemoveAuraByType",tolua_trade_CCharacter_RemoveAuraByType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_RemoveAuraBySubType00
  tolua_function(tolua_S,"RemoveAuraBySubType",tolua_trade_CCharacter_RemoveAuraBySubType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_IsDead00
  tolua_function(tolua_S,"IsDead",tolua_trade_CCharacter_IsDead00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetFlag00
  tolua_function(tolua_S,"GetFlag",tolua_trade_CCharacter_GetFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetExFlag00
  tolua_function(tolua_S,"GetExFlag",tolua_trade_CCharacter_GetExFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetCCFlag00
  tolua_function(tolua_S,"GetCCFlag",tolua_trade_CCharacter_GetCCFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_IncControlCount00
  tolua_function(tolua_S,"IncControlCount",tolua_trade_CCharacter_IncControlCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_DecControlCount00
  tolua_function(tolua_S,"DecControlCount",tolua_trade_CCharacter_DecControlCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetControlCount00
  tolua_function(tolua_S,"GetControlCount",tolua_trade_CCharacter_GetControlCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetLastCasterID00
  tolua_function(tolua_S,"SetLastCasterID",tolua_trade_CCharacter_SetLastCasterID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetLastCasterID00
  tolua_function(tolua_S,"GetLastCasterID",tolua_trade_CCharacter_GetLastCasterID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetLastCasterTimer00
  tolua_function(tolua_S,"GetLastCasterTimer",tolua_trade_CCharacter_GetLastCasterTimer00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetLastTargetID00
  tolua_function(tolua_S,"SetLastTargetID",tolua_trade_CCharacter_SetLastTargetID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetLastTargetID00
  tolua_function(tolua_S,"GetLastTargetID",tolua_trade_CCharacter_GetLastTargetID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetLastTargetTimer00
  tolua_function(tolua_S,"GetLastTargetTimer",tolua_trade_CCharacter_GetLastTargetTimer00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetDropOwnerID00
  tolua_function(tolua_S,"SetDropOwnerID",tolua_trade_CCharacter_SetDropOwnerID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetDropOwnerID00
  tolua_function(tolua_S,"GetDropOwnerID",tolua_trade_CCharacter_GetDropOwnerID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SelectFocus00
  tolua_function(tolua_S,"SelectFocus",tolua_trade_CCharacter_SelectFocus00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetFocusID00
  tolua_function(tolua_S,"GetFocusID",tolua_trade_CCharacter_GetFocusID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_Say00
  tolua_function(tolua_S,"Say",tolua_trade_CCharacter_Say00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SendMail00
  tolua_function(tolua_S,"SendMail",tolua_trade_CCharacter_SendMail00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SendMail01
  tolua_function(tolua_S,"SendMail",tolua_trade_CCharacter_SendMail01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetAIProcessor00
  tolua_function(tolua_S,"SetAIProcessor",tolua_trade_CCharacter_SetAIProcessor00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetAIProcessor00
  tolua_function(tolua_S,"GetAIProcessor",tolua_trade_CCharacter_GetAIProcessor00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetOriginalAiID00
  tolua_function(tolua_S,"GetOriginalAiID",tolua_trade_CCharacter_GetOriginalAiID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_SetGlobalCDDelayFrame00
  tolua_function(tolua_S,"SetGlobalCDDelayFrame",tolua_trade_CCharacter_SetGlobalCDDelayFrame00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetGlobalCDDelayFrame00
  tolua_function(tolua_S,"GetGlobalCDDelayFrame",tolua_trade_CCharacter_GetGlobalCDDelayFrame00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetCoolDown00
  tolua_function(tolua_S,"GetCoolDown",tolua_trade_CCharacter_GetCoolDown00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_GetHostID00
  tolua_function(tolua_S,"GetHostID",tolua_trade_CCharacter_GetHostID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CCharacter_Mine00
  tolua_function(tolua_S,"Mine",tolua_trade_CCharacter_Mine00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CFlagBits","CFlagBits","",NULL);
 tolua_beginmodule(tolua_S,"CFlagBits");
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_new00
  tolua_function(tolua_S,"new",tolua_trade_CFlagBits_new00);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_trade_CFlagBits_new00_local);
  tolua_function(tolua_S,".call",tolua_trade_CFlagBits_new00_local);
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_CheckFlag00
  tolua_function(tolua_S,"CheckFlag",tolua_trade_CFlagBits_CheckFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_SetFlag00
  tolua_function(tolua_S,"SetFlag",tolua_trade_CFlagBits_SetFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_ClearFlag00
  tolua_function(tolua_S,"ClearFlag",tolua_trade_CFlagBits_ClearFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_ResetFlag00
  tolua_function(tolua_S,"ResetFlag",tolua_trade_CFlagBits_ResetFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_FlagIncludeBits00
  tolua_function(tolua_S,"FlagIncludeBits",tolua_trade_CFlagBits_FlagIncludeBits00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_FlagNotIncludeBits00
  tolua_function(tolua_S,"FlagNotIncludeBits",tolua_trade_CFlagBits_FlagNotIncludeBits00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CFlagBits_GetFlag00
  tolua_function(tolua_S,"GetFlag",tolua_trade_CFlagBits_GetFlag00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"MAX_ROLE_FRACTION_ID",MAX_ROLE_FRACTION_ID);
 tolua_constant(tolua_S,"MAX_ROLE_LEVEL",MAX_ROLE_LEVEL);
 tolua_constant(tolua_S,"MAX_PK_VALUE",MAX_PK_VALUE);
 tolua_constant(tolua_S,"MIN_REPUTATION",MIN_REPUTATION);
 tolua_constant(tolua_S,"MAX_ACTIVITY_LEVEL",MAX_ACTIVITY_LEVEL);
 tolua_constant(tolua_S,"MAX_USABLE_ROLE_PER_USER",MAX_USABLE_ROLE_PER_USER);
 tolua_constant(tolua_S,"MAX_DELETE_ROLE_PER_USER",MAX_DELETE_ROLE_PER_USER);
 tolua_constant(tolua_S,"MAX_ROLE_PER_USER",MAX_ROLE_PER_USER);
 tolua_constant(tolua_S,"MAX_ROLE_HAIR_TYPE",MAX_ROLE_HAIR_TYPE);
 tolua_constant(tolua_S,"MAX_ROLE_HAIR_COLOR",MAX_ROLE_HAIR_COLOR);
 tolua_constant(tolua_S,"MAX_ROLE_FACE_TYPE",MAX_ROLE_FACE_TYPE);
 tolua_constant(tolua_S,"MAX_ROLE_SKIN_COLOR",MAX_ROLE_SKIN_COLOR);
 tolua_constant(tolua_S,"MOMENTARY_KILL_NPC_TIEM",MOMENTARY_KILL_NPC_TIEM);
 tolua_constant(tolua_S,"MIN_MOMENTARY_KILL_NPC_COUNT",MIN_MOMENTARY_KILL_NPC_COUNT);
 tolua_constant(tolua_S,"MIN_CONSECUTIVE_KILL_NPC_COUNT",MIN_CONSECUTIVE_KILL_NPC_COUNT);
 tolua_constant(tolua_S,"MAX_CONSECUTIVE_KILL_NPC_FRAME",MAX_CONSECUTIVE_KILL_NPC_FRAME);
 tolua_constant(tolua_S,"MAX_CONSECTIVE_KILL_PLAYER_FRAME",MAX_CONSECTIVE_KILL_PLAYER_FRAME);
 tolua_constant(tolua_S,"MAX_CONSECUTIVE_KILL_PLAYER_COUNT",MAX_CONSECUTIVE_KILL_PLAYER_COUNT);
 tolua_constant(tolua_S,"MAX_QUERY_ROLE_INFO_PER_SEC",MAX_QUERY_ROLE_INFO_PER_SEC);
 tolua_constant(tolua_S,"MAX_VIP_MONTH",MAX_VIP_MONTH);
 tolua_constant(tolua_S,"MAX_GM_LEVEL",MAX_GM_LEVEL);
 tolua_constant(tolua_S,"MAX_PET_PER_ROLE",MAX_PET_PER_ROLE);
 tolua_constant(tolua_S,"MAX_REPUTATION_AWARD_COUNT",MAX_REPUTATION_AWARD_COUNT);
 tolua_constant(tolua_S,"ROLE_DELAY_LOGOUT_FRAME",ROLE_DELAY_LOGOUT_FRAME);
 tolua_constant(tolua_S,"ROLE_DELAY_LOGOUT_FRAME_ABNORMAL",ROLE_DELAY_LOGOUT_FRAME_ABNORMAL);
 tolua_constant(tolua_S,"ROLE_DELAY_LOGOUT_FRAME",ROLE_DELAY_LOGOUT_FRAME);
 tolua_constant(tolua_S,"ROLE_DELAY_LOGOUT_FRAME_ABNORMAL",ROLE_DELAY_LOGOUT_FRAME_ABNORMAL);
 tolua_constant(tolua_S,"DEFAULT_ROLE_ANTI_CHEAT_LEVEL",DEFAULT_ROLE_ANTI_CHEAT_LEVEL);
 tolua_constant(tolua_S,"MAX_ROLE_ANTI_CHEAT_LEVEL",MAX_ROLE_ANTI_CHEAT_LEVEL);
 tolua_constant(tolua_S,"MAX_ROLE_ANTI_CHEAT_PUNISH_LEVEL",MAX_ROLE_ANTI_CHEAT_PUNISH_LEVEL);
 tolua_constant(tolua_S,"MAX_ROLE_GPK_PUNISH_LEVEL",MAX_ROLE_GPK_PUNISH_LEVEL);
  tolua_constant(tolua_S,"rltInvalid",rltInvalid);
  tolua_constant(tolua_S,"rltReturnLogin",rltReturnLogin);
  tolua_constant(tolua_S,"rltReturnSelectRole",rltReturnSelectRole);
  tolua_constant(tolua_S,"rltDisconnect",rltDisconnect);
  tolua_constant(tolua_S,"rltKickout",rltKickout);
  tolua_constant(tolua_S,"rltTotal",rltTotal);
  tolua_constant(tolua_S,"rsInvalid",rsInvalid);
  tolua_constant(tolua_S,"rsPreEntered",rsPreEntered);
  tolua_constant(tolua_S,"rsWaitRoleData",rsWaitRoleData);
  tolua_constant(tolua_S,"rsWaitMSApprove",rsWaitMSApprove);
  tolua_constant(tolua_S,"rsWaitClientLoad",rsWaitClientLoad);
  tolua_constant(tolua_S,"rsPlaying",rsPlaying);
  tolua_constant(tolua_S,"rsInJump",rsInJump);
  tolua_constant(tolua_S,"rsJumpInGSWaitClientLoad",rsJumpInGSWaitClientLoad);
  tolua_constant(tolua_S,"rsWaitUnlockRoleData",rsWaitUnlockRoleData);
  tolua_constant(tolua_S,"rsLogout",rsLogout);
  tolua_constant(tolua_S,"rsTotal",rsTotal);
  tolua_constant(tolua_S,"fcmsFull",fcmsFull);
  tolua_constant(tolua_S,"fcmsHalf",fcmsHalf);
  tolua_constant(tolua_S,"fcmsNone",fcmsNone);
  tolua_constant(tolua_S,"fcmsTotal",fcmsTotal);
  tolua_constant(tolua_S,"faceInvalid",faceInvalid);
  tolua_constant(tolua_S,"faceTotal",faceTotal);
  tolua_constant(tolua_S,"rpmInvalid",rpmInvalid);
  tolua_constant(tolua_S,"rpmPeace",rpmPeace);
  tolua_constant(tolua_S,"rpmGuild",rpmGuild);
  tolua_constant(tolua_S,"rpmTeam",rpmTeam);
  tolua_constant(tolua_S,"rpmSlayer",rpmSlayer);
  tolua_constant(tolua_S,"rpmJustice",rpmJustice);
  tolua_constant(tolua_S,"rpmMaster",rpmMaster);
  tolua_constant(tolua_S,"rpmTotal",rpmTotal);
  tolua_constant(tolua_S,"rprInvalid",rprInvalid);
  tolua_constant(tolua_S,"rprNormal",rprNormal);
  tolua_constant(tolua_S,"rprRedName",rprRedName);
  tolua_constant(tolua_S,"rprCounterStrike",rprCounterStrike);
  tolua_constant(tolua_S,"rprOpponentGuildMember",rprOpponentGuildMember);
  tolua_constant(tolua_S,"rprLuckyKill",rprLuckyKill);
  tolua_constant(tolua_S,"rprNoPunishment",rprNoPunishment);
  tolua_constant(tolua_S,"rprTotal",rprTotal);
  tolua_constant(tolua_S,"rncInvalid",rncInvalid);
  tolua_constant(tolua_S,"rncWhite",rncWhite);
  tolua_constant(tolua_S,"rncYellow",rncYellow);
  tolua_constant(tolua_S,"rncRed",rncRed);
  tolua_constant(tolua_S,"rncTotal",rncTotal);
  tolua_constant(tolua_S,"ervtInvalid",ervtInvalid);
  tolua_constant(tolua_S,"ervtTotal",ervtTotal);
  tolua_constant(tolua_S,"rfrInvalid",rfrInvalid);
  tolua_constant(tolua_S,"rfrDefault",rfrDefault);
  tolua_constant(tolua_S,"rfrFriend",rfrFriend);
  tolua_constant(tolua_S,"rfrEnemy",rfrEnemy);
  tolua_constant(tolua_S,"rfrTotal",rfrTotal);
  tolua_constant(tolua_S,"vlLevel0",vlLevel0);
  tolua_constant(tolua_S,"vlLevel1",vlLevel1);
  tolua_constant(tolua_S,"vlLevel2",vlLevel2);
  tolua_constant(tolua_S,"vlLevel3",vlLevel3);
  tolua_constant(tolua_S,"vlTotal",vlTotal);
  tolua_constant(tolua_S,"MSG_PP_PERSONAL_ENEMY",MSG_PP_PERSONAL_ENEMY);
  tolua_constant(tolua_S,"aprInvalid",aprInvalid);
  tolua_constant(tolua_S,"aprWuDouChang",aprWuDouChang);
  tolua_constant(tolua_S,"aprBaoku",aprBaoku);
  tolua_constant(tolua_S,"aprYanWuChang",aprYanWuChang);
  tolua_constant(tolua_S,"aprPray",aprPray);
  tolua_constant(tolua_S,"aprEscort",aprEscort);
  tolua_constant(tolua_S,"aprGuildBoss",aprGuildBoss);
  tolua_constant(tolua_S,"aprSpring",aprSpring);
  tolua_constant(tolua_S,"aprQuest",aprQuest);
  tolua_constant(tolua_S,"aprYaoTa",aprYaoTa);
  tolua_constant(tolua_S,"aprYouMingSea",aprYouMingSea);
  tolua_constant(tolua_S,"aprTotal",aprTotal);
 #ifdef __cplusplus
 tolua_cclass(tolua_S,"CSpellSlot","CSpellSlot","",tolua_collect_CSpellSlot);
 #else
 tolua_cclass(tolua_S,"CSpellSlot","CSpellSlot","",NULL);
 #endif
 tolua_beginmodule(tolua_S,"CSpellSlot");
#ifndef TOLUA_DISABLE_tolua_trade_CSpellSlot_new00
  tolua_function(tolua_S,"new",tolua_trade_CSpellSlot_new00);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_trade_CSpellSlot_new00_local);
  tolua_function(tolua_S,".call",tolua_trade_CSpellSlot_new00_local);
#ifndef TOLUA_DISABLE_tolua_trade_CSpellSlot_delete00
  tolua_function(tolua_S,"delete",tolua_trade_CSpellSlot_delete00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CSpellSlot_GetMainSpellID00
  tolua_function(tolua_S,"GetMainSpellID",tolua_trade_CSpellSlot_GetMainSpellID00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CRole","CRole","CCharacter",NULL);
 tolua_beginmodule(tolua_S,"CRole");
#ifndef TOLUA_DISABLE_tolua_trade_CRole_Init00
  tolua_function(tolua_S,"Init",tolua_trade_CRole_Init00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_UnInit00
  tolua_function(tolua_S,"UnInit",tolua_trade_CRole_UnInit00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetName00
  tolua_function(tolua_S,"GetName",tolua_trade_CRole_GetName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetSessionID00
  tolua_function(tolua_S,"GetSessionID",tolua_trade_CRole_GetSessionID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetServerGroup00
  tolua_function(tolua_S,"GetServerGroup",tolua_trade_CRole_GetServerGroup00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetSceneTempID00
  tolua_function(tolua_S,"GetSceneTempID",tolua_trade_CRole_GetSceneTempID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetSceneID00
  tolua_function(tolua_S,"GetSceneID",tolua_trade_CRole_GetSceneID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_LearnSpell00
  tolua_function(tolua_S,"LearnSpell",tolua_trade_CRole_LearnSpell00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_EquipSpell00
  tolua_function(tolua_S,"EquipSpell",tolua_trade_CRole_EquipSpell00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_UnlockSpellSlot00
  tolua_function(tolua_S,"UnlockSpellSlot",tolua_trade_CRole_UnlockSpellSlot00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetSpellSlot00
  tolua_function(tolua_S,"GetSpellSlot",tolua_trade_CRole_GetSpellSlot00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddSpellPts00
  tolua_function(tolua_S,"AddSpellPts",tolua_trade_CRole_AddSpellPts00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_RemoveSpell00
  tolua_function(tolua_S,"RemoveSpell",tolua_trade_CRole_RemoveSpell00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_EquipRune00
  tolua_function(tolua_S,"EquipRune",tolua_trade_CRole_EquipRune00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetLastSlot00
  tolua_function(tolua_S,"SetLastSlot",tolua_trade_CRole_SetLastSlot00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetLastSlot00
  tolua_function(tolua_S,"GetLastSlot",tolua_trade_CRole_GetLastSlot00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_ClearAllCooldown00
  tolua_function(tolua_S,"ClearAllCooldown",tolua_trade_CRole_ClearAllCooldown00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetItemBag00
  tolua_function(tolua_S,"GetItemBag",tolua_trade_CRole_GetItemBag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetStall00
  tolua_function(tolua_S,"GetStall",tolua_trade_CRole_GetStall00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetQuestList00
  tolua_function(tolua_S,"GetQuestList",tolua_trade_CRole_GetQuestList00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetFreeMode00
  tolua_function(tolua_S,"SetFreeMode",tolua_trade_CRole_SetFreeMode00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_IsFreeMode00
  tolua_function(tolua_S,"IsFreeMode",tolua_trade_CRole_IsFreeMode00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFaction00
  tolua_function(tolua_S,"GetFaction",tolua_trade_CRole_GetFaction00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetFaction00
  tolua_function(tolua_S,"SetFaction",tolua_trade_CRole_SetFaction00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetReputation00
  tolua_function(tolua_S,"GetReputation",tolua_trade_CRole_GetReputation00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetTeamID00
  tolua_function(tolua_S,"GetTeamID",tolua_trade_CRole_GetTeamID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetTrade00
  tolua_function(tolua_S,"GetTrade",tolua_trade_CRole_GetTrade00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetTitle00
  tolua_function(tolua_S,"GetTitle",tolua_trade_CRole_GetTitle00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetMaster00
  tolua_function(tolua_S,"GetMaster",tolua_trade_CRole_GetMaster00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetGuildID00
  tolua_function(tolua_S,"GetGuildID",tolua_trade_CRole_GetGuildID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetRoleGuildData00
  tolua_function(tolua_S,"GetRoleGuildData",tolua_trade_CRole_GetRoleGuildData00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetAsimovRole00
  tolua_function(tolua_S,"GetAsimovRole",tolua_trade_CRole_GetAsimovRole00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFriend00
  tolua_function(tolua_S,"GetFriend",tolua_trade_CRole_GetFriend00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetShieldList00
  tolua_function(tolua_S,"GetShieldList",tolua_trade_CRole_GetShieldList00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetArena00
  tolua_function(tolua_S,"GetArena",tolua_trade_CRole_GetArena00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetHero00
  tolua_function(tolua_S,"GetHero",tolua_trade_CRole_GetHero00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddExp00
  tolua_function(tolua_S,"AddExp",tolua_trade_CRole_AddExp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetExp00
  tolua_function(tolua_S,"GetExp",tolua_trade_CRole_GetExp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetExtraExp00
  tolua_function(tolua_S,"GetExtraExp",tolua_trade_CRole_GetExtraExp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddExtraExp00
  tolua_function(tolua_S,"AddExtraExp",tolua_trade_CRole_AddExtraExp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_TryRevive00
  tolua_function(tolua_S,"TryRevive",tolua_trade_CRole_TryRevive00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_ActivateMount00
  tolua_function(tolua_S,"ActivateMount",tolua_trade_CRole_ActivateMount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_OnMount00
  tolua_function(tolua_S,"OnMount",tolua_trade_CRole_OnMount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_OffMount00
  tolua_function(tolua_S,"OffMount",tolua_trade_CRole_OffMount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetVIPLevel00
  tolua_function(tolua_S,"GetVIPLevel",tolua_trade_CRole_GetVIPLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SubscribeVIP00
  tolua_function(tolua_S,"SubscribeVIP",tolua_trade_CRole_SubscribeVIP00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetVIPTime00
  tolua_function(tolua_S,"GetVIPTime",tolua_trade_CRole_GetVIPTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetTotalOnlineTime00
  tolua_function(tolua_S,"GetTotalOnlineTime",tolua_trade_CRole_GetTotalOnlineTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetLevelOnlineTime00
  tolua_function(tolua_S,"GetLevelOnlineTime",tolua_trade_CRole_GetLevelOnlineTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_ChangePkMode00
  tolua_function(tolua_S,"ChangePkMode",tolua_trade_CRole_ChangePkMode00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_IsRedName00
  tolua_function(tolua_S,"IsRedName",tolua_trade_CRole_IsRedName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetState00
  tolua_function(tolua_S,"GetState",tolua_trade_CRole_GetState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetVariable00
  tolua_function(tolua_S,"SetVariable",tolua_trade_CRole_SetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetVariable00
  tolua_function(tolua_S,"GetVariable",tolua_trade_CRole_GetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetClientVariable00
  tolua_function(tolua_S,"GetClientVariable",tolua_trade_CRole_GetClientVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetClientVariable00
  tolua_function(tolua_S,"SetClientVariable",tolua_trade_CRole_SetClientVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetPkValue00
  tolua_function(tolua_S,"GetPkValue",tolua_trade_CRole_GetPkValue00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetPkValue00
  tolua_function(tolua_S,"SetPkValue",tolua_trade_CRole_SetPkValue00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetAchievementList00
  tolua_function(tolua_S,"GetAchievementList",tolua_trade_CRole_GetAchievementList00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_HireHero00
  tolua_function(tolua_S,"HireHero",tolua_trade_CRole_HireHero00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_FireHero00
  tolua_function(tolua_S,"FireHero",tolua_trade_CRole_FireHero00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SummonHero00
  tolua_function(tolua_S,"SummonHero",tolua_trade_CRole_SummonHero00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_RecallHero00
  tolua_function(tolua_S,"RecallHero",tolua_trade_CRole_RecallHero00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetSpirit00
  tolua_function(tolua_S,"GetSpirit",tolua_trade_CRole_GetSpirit00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_CheckDistance00
  tolua_function(tolua_S,"CheckDistance",tolua_trade_CRole_CheckDistance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetInteractNpc00
  tolua_function(tolua_S,"GetInteractNpc",tolua_trade_CRole_GetInteractNpc00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_Interact00
  tolua_function(tolua_S,"Interact",tolua_trade_CRole_Interact00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddActivity00
  tolua_function(tolua_S,"AddActivity",tolua_trade_CRole_AddActivity00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetActivity00
  tolua_function(tolua_S,"GetActivity",tolua_trade_CRole_GetActivity00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddActivityReward00
  tolua_function(tolua_S,"AddActivityReward",tolua_trade_CRole_AddActivityReward00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetActivityRewardByIndex00
  tolua_function(tolua_S,"GetActivityRewardByIndex",tolua_trade_CRole_GetActivityRewardByIndex00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetActivityReward00
  tolua_function(tolua_S,"GetActivityReward",tolua_trade_CRole_GetActivityReward00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_ClearActivity00
  tolua_function(tolua_S,"ClearActivity",tolua_trade_CRole_ClearActivity00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFirstMail00
  tolua_function(tolua_S,"GetFirstMail",tolua_trade_CRole_GetFirstMail00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFirstAttach00
  tolua_function(tolua_S,"GetFirstAttach",tolua_trade_CRole_GetFirstAttach00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetRandomAuctionItemID00
  tolua_function(tolua_S,"GetRandomAuctionItemID",tolua_trade_CRole_GetRandomAuctionItemID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFirstSellingAuction00
  tolua_function(tolua_S,"GetFirstSellingAuction",tolua_trade_CRole_GetFirstSellingAuction00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFirstBuyingAuction00
  tolua_function(tolua_S,"GetFirstBuyingAuction",tolua_trade_CRole_GetFirstBuyingAuction00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_Hide00
  tolua_function(tolua_S,"Hide",tolua_trade_CRole_Hide00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_IsHidden00
  tolua_function(tolua_S,"IsHidden",tolua_trade_CRole_IsHidden00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetGMLevel00
  tolua_function(tolua_S,"GetGMLevel",tolua_trade_CRole_GetGMLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetGMLevel00
  tolua_function(tolua_S,"SetGMLevel",tolua_trade_CRole_SetGMLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetFcmState00
  tolua_function(tolua_S,"SetFcmState",tolua_trade_CRole_SetFcmState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetFcmState00
  tolua_function(tolua_S,"GetFcmState",tolua_trade_CRole_GetFcmState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_Kick00
  tolua_function(tolua_S,"Kick",tolua_trade_CRole_Kick00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_Kick01
  tolua_function(tolua_S,"Kick",tolua_trade_CRole_Kick01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_ErrorCodeNotify00
  tolua_function(tolua_S,"ErrorCodeNotify",tolua_trade_CRole_ErrorCodeNotify00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_ForceSyncPos00
  tolua_function(tolua_S,"ForceSyncPos",tolua_trade_CRole_ForceSyncPos00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_TransferRole00
  tolua_function(tolua_S,"TransferRole",tolua_trade_CRole_TransferRole00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetRevivePos00
  tolua_function(tolua_S,"GetRevivePos",tolua_trade_CRole_GetRevivePos00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GenerateAntiCheatJigsaw00
  tolua_function(tolua_S,"GenerateAntiCheatJigsaw",tolua_trade_CRole_GenerateAntiCheatJigsaw00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetPetState00
  tolua_function(tolua_S,"GetPetState",tolua_trade_CRole_GetPetState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetPetState00
  tolua_function(tolua_S,"SetPetState",tolua_trade_CRole_SetPetState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddPet00
  tolua_function(tolua_S,"AddPet",tolua_trade_CRole_AddPet00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetPetCount00
  tolua_function(tolua_S,"GetPetCount",tolua_trade_CRole_GetPetCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetMaxPetCount00
  tolua_function(tolua_S,"GetMaxPetCount",tolua_trade_CRole_GetMaxPetCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetPetNpcID00
  tolua_function(tolua_S,"GetPetNpcID",tolua_trade_CRole_GetPetNpcID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GMCreateGuild00
  tolua_function(tolua_S,"GMCreateGuild",tolua_trade_CRole_GMCreateGuild00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetJumpRandomNumber00
  tolua_function(tolua_S,"GetJumpRandomNumber",tolua_trade_CRole_GetJumpRandomNumber00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_QueryRoleLocation00
  tolua_function(tolua_S,"QueryRoleLocation",tolua_trade_CRole_QueryRoleLocation00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_RecallTeamMember00
  tolua_function(tolua_S,"RecallTeamMember",tolua_trade_CRole_RecallTeamMember00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_IsSabacGuildMember00
  tolua_function(tolua_S,"IsSabacGuildMember",tolua_trade_CRole_IsSabacGuildMember00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_CheckIn00
  tolua_function(tolua_S,"CheckIn",tolua_trade_CRole_CheckIn00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetStartExerciseTime00
  tolua_function(tolua_S,"GetStartExerciseTime",tolua_trade_CRole_GetStartExerciseTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetStartExerciseTime00
  tolua_function(tolua_S,"SetStartExerciseTime",tolua_trade_CRole_SetStartExerciseTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_UpdateRankListNode00
  tolua_function(tolua_S,"UpdateRankListNode",tolua_trade_CRole_UpdateRankListNode00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GenerateAntiCheatJigsaw01
  tolua_function(tolua_S,"GenerateAntiCheatJigsaw",tolua_trade_CRole_GenerateAntiCheatJigsaw01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_SetAntiCheatLevel00
  tolua_function(tolua_S,"SetAntiCheatLevel",tolua_trade_CRole_SetAntiCheatLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetGameTimeCard_UINT3200
  tolua_function(tolua_S,"GetGameTimeCard_UINT32",tolua_trade_CRole_GetGameTimeCard_UINT3200);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_AddGameTimeCard00
  tolua_function(tolua_S,"AddGameTimeCard",tolua_trade_CRole_AddGameTimeCard00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_NotifyRole_GameTimeCard00
  tolua_function(tolua_S,"NotifyRole_GameTimeCard",tolua_trade_CRole_NotifyRole_GameTimeCard00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetRuneRootCount00
  tolua_function(tolua_S,"GetRuneRootCount",tolua_trade_CRole_GetRuneRootCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_IncRuneRootCount00
  tolua_function(tolua_S,"IncRuneRootCount",tolua_trade_CRole_IncRuneRootCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_NotifyRole_RuneRootCount00
  tolua_function(tolua_S,"NotifyRole_RuneRootCount",tolua_trade_CRole_NotifyRole_RuneRootCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_GetLuckRootCount00
  tolua_function(tolua_S,"GetLuckRootCount",tolua_trade_CRole_GetLuckRootCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_IncLuckRootCount00
  tolua_function(tolua_S,"IncLuckRootCount",tolua_trade_CRole_IncLuckRootCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CRole_NotifyRole_LuckRootCount00
  tolua_function(tolua_S,"NotifyRole_LuckRootCount",tolua_trade_CRole_NotifyRole_LuckRootCount00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CReputation","CReputation","",NULL);
 tolua_beginmodule(tolua_S,"CReputation");
#ifndef TOLUA_DISABLE_tolua_trade_CReputation_GetValue00
  tolua_function(tolua_S,"GetValue",tolua_trade_CReputation_GetValue00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CReputation_SetValue00
  tolua_function(tolua_S,"SetValue",tolua_trade_CReputation_SetValue00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CReputation_ModifyValue00
  tolua_function(tolua_S,"ModifyValue",tolua_trade_CReputation_ModifyValue00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CReputation_ActiveForce00
  tolua_function(tolua_S,"ActiveForce",tolua_trade_CReputation_ActiveForce00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CReputation_ReceiveAward00
  tolua_function(tolua_S,"ReceiveAward",tolua_trade_CReputation_ReceiveAward00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CTrade","CTrade","",NULL);
 tolua_beginmodule(tolua_S,"CTrade");
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_new00
  tolua_function(tolua_S,"new",tolua_trade_CTrade_new00);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_trade_CTrade_new00_local);
  tolua_function(tolua_S,".call",tolua_trade_CTrade_new00_local);
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_Clear00
  tolua_function(tolua_S,"Clear",tolua_trade_CTrade_Clear00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_SetOwner00
  tolua_function(tolua_S,"SetOwner",tolua_trade_CTrade_SetOwner00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_AskTrade00
  tolua_function(tolua_S,"AskTrade",tolua_trade_CTrade_AskTrade00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_AcceptTrade00
  tolua_function(tolua_S,"AcceptTrade",tolua_trade_CTrade_AcceptTrade00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_SetItem00
  tolua_function(tolua_S,"SetItem",tolua_trade_CTrade_SetItem00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_SetMoney00
  tolua_function(tolua_S,"SetMoney",tolua_trade_CTrade_SetMoney00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_LockTrade00
  tolua_function(tolua_S,"LockTrade",tolua_trade_CTrade_LockTrade00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_ConfirmTrade00
  tolua_function(tolua_S,"ConfirmTrade",tolua_trade_CTrade_ConfirmTrade00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_UnlockTrade00
  tolua_function(tolua_S,"UnlockTrade",tolua_trade_CTrade_UnlockTrade00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_CancelTrade00
  tolua_function(tolua_S,"CancelTrade",tolua_trade_CTrade_CancelTrade00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_IsTrading00
  tolua_function(tolua_S,"IsTrading",tolua_trade_CTrade_IsTrading00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_trade_CTrade_IsTradeItem00
  tolua_function(tolua_S,"IsTradeItem",tolua_trade_CTrade_IsTradeItem00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_trade (lua_State* tolua_S) {
 return tolua_trade_open(tolua_S);
};
#endif

