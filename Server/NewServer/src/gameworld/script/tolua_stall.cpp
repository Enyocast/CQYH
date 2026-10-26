/*
** Lua binding: stall
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:31.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_stall_open (lua_State* tolua_S);

#include "scene_object.h"
#include "scene_object.h"
#include "character.h"
#include "aura_instance.h"
#include "spell_instance.h"
#include "../../../common/define/role_def.h"
#include "role.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CSpellInstance (lua_State* tolua_S)
{
 CSpellInstance* self = (CSpellInstance*) tolua_tousertype(tolua_S,1,0);
 Mtolua_delete(self);
 return 0;
}

static int tolua_collect_CTargetScanner (lua_State* tolua_S)
{
 CTargetScanner* self = (CTargetScanner*) tolua_tousertype(tolua_S,1,0);
 Mtolua_delete(self);
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CSpellInstance");
 tolua_usertype(tolua_S,"CSpellSlot");
 tolua_usertype(tolua_S,"RUNE_DATA");
 tolua_usertype(tolua_S,"Item");
 tolua_usertype(tolua_S,"GRID_INSTANCE_DATA");
 tolua_usertype(tolua_S,"ZONE_DATA");
 tolua_usertype(tolua_S,"CScene");
 tolua_usertype(tolua_S,"CAuraInstance");
 tolua_usertype(tolua_S,"CCoolDown");
 tolua_usertype(tolua_S,"CStall");
 tolua_usertype(tolua_S,"CTargetScanner");
 tolua_usertype(tolua_S,"CAttrList");
 tolua_usertype(tolua_S,"CAura");
 tolua_usertype(tolua_S,"CSceneObject");
 tolua_usertype(tolua_S,"CCharacter");
 tolua_usertype(tolua_S,"CAIProcessor");
 tolua_usertype(tolua_S,"GRID_DATA");
 tolua_usertype(tolua_S,"ISpellBook");
 tolua_usertype(tolua_S,"ExtraParam");
 tolua_usertype(tolua_S,"CFlagBits");
 tolua_usertype(tolua_S,"CRegion");
}

/* method: GetObjID of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetObjID00
static int tolua_stall_CSceneObject_GetObjID00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetObjType00
static int tolua_stall_CSceneObject_GetObjType00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetScene00
static int tolua_stall_CSceneObject_GetScene00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetRegion00
static int tolua_stall_CSceneObject_GetRegion00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetZone00
static int tolua_stall_CSceneObject_GetZone00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetGrid00
static int tolua_stall_CSceneObject_GetGrid00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetGridInstance00
static int tolua_stall_CSceneObject_GetGridInstance00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetX00
static int tolua_stall_CSceneObject_SetX00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetY00
static int tolua_stall_CSceneObject_SetY00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetZ00
static int tolua_stall_CSceneObject_SetZ00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetX00
static int tolua_stall_CSceneObject_GetX00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetY00
static int tolua_stall_CSceneObject_GetY00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetZ00
static int tolua_stall_CSceneObject_GetZ00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetFaceDirection00
static int tolua_stall_CSceneObject_SetFaceDirection00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetFaceDirection00
static int tolua_stall_CSceneObject_GetFaceDirection00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetBodyType00
static int tolua_stall_CSceneObject_SetBodyType00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetBodyType00
static int tolua_stall_CSceneObject_GetBodyType00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_CanTeleport00
static int tolua_stall_CSceneObject_CanTeleport00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetObjID01
static int tolua_stall_CSceneObject_GetObjID01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_GetObjID00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetObjType of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetObjType01
static int tolua_stall_CSceneObject_GetObjType01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_GetObjType00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScene of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetScene01
static int tolua_stall_CSceneObject_GetScene01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_GetScene00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRegion of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetRegion01
static int tolua_stall_CSceneObject_GetRegion01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_GetRegion00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetZone of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetZone01
static int tolua_stall_CSceneObject_GetZone01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_GetZone00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGrid of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetGrid01
static int tolua_stall_CSceneObject_GetGrid01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_GetGrid00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGridInstance of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetGridInstance01
static int tolua_stall_CSceneObject_GetGridInstance01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_GetGridInstance00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetX of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetX01
static int tolua_stall_CSceneObject_SetX01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_SetX00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetY of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetY01
static int tolua_stall_CSceneObject_SetY01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_SetY00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetZ of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetZ01
static int tolua_stall_CSceneObject_SetZ01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_SetZ00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetX of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetX01
static int tolua_stall_CSceneObject_GetX01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_GetX00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetY of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetY01
static int tolua_stall_CSceneObject_GetY01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_GetY00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetZ of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetZ01
static int tolua_stall_CSceneObject_GetZ01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_GetZ00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFaceDirection of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetFaceDirection01
static int tolua_stall_CSceneObject_SetFaceDirection01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_SetFaceDirection00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFaceDirection of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetFaceDirection01
static int tolua_stall_CSceneObject_GetFaceDirection01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_GetFaceDirection00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBodyType of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetBodyType01
static int tolua_stall_CSceneObject_SetBodyType01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_SetBodyType00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBodyType of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetBodyType01
static int tolua_stall_CSceneObject_GetBodyType01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_GetBodyType00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanTeleport of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_CanTeleport01
static int tolua_stall_CSceneObject_CanTeleport01(lua_State* tolua_S)
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
 return tolua_stall_CSceneObject_CanTeleport00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstanceID of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_stall_CAuraInstance_GetInstanceID00
static int tolua_stall_CAuraInstance_GetInstanceID00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCoolDown_Add00
static int tolua_stall_CCoolDown_Add00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCoolDown_Reset00
static int tolua_stall_CCoolDown_Reset00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCoolDown_CheckReady00
static int tolua_stall_CCoolDown_CheckReady00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCoolDown_GetRemainFrm00
static int tolua_stall_CCoolDown_GetRemainFrm00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCoolDown_Enable00
static int tolua_stall_CCoolDown_Enable00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CTargetScanner_new00
static int tolua_stall_CTargetScanner_new00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CTargetScanner_new00_local
static int tolua_stall_CTargetScanner_new00_local(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CTargetScanner_delete00
static int tolua_stall_CTargetScanner_delete00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CTargetScanner_GetTargetX00
static int tolua_stall_CTargetScanner_GetTargetX00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CTargetScanner_GetTargetY00
static int tolua_stall_CTargetScanner_GetTargetY00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CTargetScanner_GetTargetZ00
static int tolua_stall_CTargetScanner_GetTargetZ00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSpellInstance_new00
static int tolua_stall_CSpellInstance_new00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSpellInstance_new00_local
static int tolua_stall_CSpellInstance_new00_local(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSpellInstance_delete00
static int tolua_stall_CSpellInstance_delete00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CSpellInstance_GetScanner00
static int tolua_stall_CSpellInstance_GetScanner00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_JumpTo00
static int tolua_stall_CCharacter_JumpTo00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetClass00
static int tolua_stall_CCharacter_GetClass00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetSex00
static int tolua_stall_CCharacter_GetSex00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetLevel00
static int tolua_stall_CCharacter_GetLevel00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetName00
static int tolua_stall_CCharacter_GetName00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetClass00
static int tolua_stall_CCharacter_SetClass00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetSex00
static int tolua_stall_CCharacter_SetSex00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetLevel00
static int tolua_stall_CCharacter_SetLevel00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetAttr00
static int tolua_stall_CCharacter_GetAttr00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetAttrList00
static int tolua_stall_CCharacter_GetAttrList00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetInCutScene00
static int tolua_stall_CCharacter_SetInCutScene00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_MoveTo00
static int tolua_stall_CCharacter_MoveTo00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_Die00
static int tolua_stall_CCharacter_Die00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_Revive00
static int tolua_stall_CCharacter_Revive00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_RotateTo00
static int tolua_stall_CCharacter_RotateTo00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetCanRun00
static int tolua_stall_CCharacter_SetCanRun00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetMoveState00
static int tolua_stall_CCharacter_GetMoveState00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetHome00
static int tolua_stall_CCharacter_SetHome00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetHomeX00
static int tolua_stall_CCharacter_GetHomeX00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetHomeY00
static int tolua_stall_CCharacter_GetHomeY00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetHomeZ00
static int tolua_stall_CCharacter_GetHomeZ00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_CancelCast00
static int tolua_stall_CCharacter_CancelCast00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_IsCasting00
static int tolua_stall_CCharacter_IsCasting00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_EquipRune00
static int tolua_stall_CCharacter_EquipRune00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_UnEquipRune00
static int tolua_stall_CCharacter_UnEquipRune00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetSpellSlot00
static int tolua_stall_CCharacter_GetSpellSlot00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_CastSpell00
static int tolua_stall_CCharacter_CastSpell00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_PlayAction00
static int tolua_stall_CCharacter_PlayAction00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetCastingSpell00
static int tolua_stall_CCharacter_GetCastingSpell00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetHp00
static int tolua_stall_CCharacter_GetHp00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetHp00
static int tolua_stall_CCharacter_SetHp00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_ChangeHp00
static int tolua_stall_CCharacter_ChangeHp00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetMp00
static int tolua_stall_CCharacter_GetMp00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_ChangeMp00
static int tolua_stall_CCharacter_ChangeMp00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_CanAttack00
static int tolua_stall_CCharacter_CanAttack00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetSpellBook00
static int tolua_stall_CCharacter_GetSpellBook00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_AppendAura00
static int tolua_stall_CCharacter_AppendAura00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetFirstAura00
static int tolua_stall_CCharacter_GetFirstAura00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_RemoveAura00
static int tolua_stall_CCharacter_RemoveAura00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_RemoveAuraByType00
static int tolua_stall_CCharacter_RemoveAuraByType00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_RemoveAuraBySubType00
static int tolua_stall_CCharacter_RemoveAuraBySubType00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_IsDead00
static int tolua_stall_CCharacter_IsDead00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetFlag00
static int tolua_stall_CCharacter_GetFlag00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetExFlag00
static int tolua_stall_CCharacter_GetExFlag00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetCCFlag00
static int tolua_stall_CCharacter_GetCCFlag00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_IncControlCount00
static int tolua_stall_CCharacter_IncControlCount00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_DecControlCount00
static int tolua_stall_CCharacter_DecControlCount00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetControlCount00
static int tolua_stall_CCharacter_GetControlCount00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetLastCasterID00
static int tolua_stall_CCharacter_SetLastCasterID00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetLastCasterID00
static int tolua_stall_CCharacter_GetLastCasterID00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetLastCasterTimer00
static int tolua_stall_CCharacter_GetLastCasterTimer00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetLastTargetID00
static int tolua_stall_CCharacter_SetLastTargetID00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetLastTargetID00
static int tolua_stall_CCharacter_GetLastTargetID00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetLastTargetTimer00
static int tolua_stall_CCharacter_GetLastTargetTimer00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetDropOwnerID00
static int tolua_stall_CCharacter_SetDropOwnerID00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetDropOwnerID00
static int tolua_stall_CCharacter_GetDropOwnerID00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SelectFocus00
static int tolua_stall_CCharacter_SelectFocus00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetFocusID00
static int tolua_stall_CCharacter_GetFocusID00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_Say00
static int tolua_stall_CCharacter_Say00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SendMail00
static int tolua_stall_CCharacter_SendMail00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SendMail01
static int tolua_stall_CCharacter_SendMail01(lua_State* tolua_S)
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
 return tolua_stall_CCharacter_SendMail00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAIProcessor of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetAIProcessor00
static int tolua_stall_CCharacter_SetAIProcessor00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetAIProcessor00
static int tolua_stall_CCharacter_GetAIProcessor00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetOriginalAiID00
static int tolua_stall_CCharacter_GetOriginalAiID00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetGlobalCDDelayFrame00
static int tolua_stall_CCharacter_SetGlobalCDDelayFrame00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetGlobalCDDelayFrame00
static int tolua_stall_CCharacter_GetGlobalCDDelayFrame00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetCoolDown00
static int tolua_stall_CCharacter_GetCoolDown00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetHostID00
static int tolua_stall_CCharacter_GetHostID00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_Mine00
static int tolua_stall_CCharacter_Mine00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_new00
static int tolua_stall_CFlagBits_new00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_new00_local
static int tolua_stall_CFlagBits_new00_local(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_CheckFlag00
static int tolua_stall_CFlagBits_CheckFlag00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_SetFlag00
static int tolua_stall_CFlagBits_SetFlag00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_ClearFlag00
static int tolua_stall_CFlagBits_ClearFlag00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_ResetFlag00
static int tolua_stall_CFlagBits_ResetFlag00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_FlagIncludeBits00
static int tolua_stall_CFlagBits_FlagIncludeBits00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_FlagNotIncludeBits00
static int tolua_stall_CFlagBits_FlagNotIncludeBits00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_GetFlag00
static int tolua_stall_CFlagBits_GetFlag00(lua_State* tolua_S)
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

/* method: GetStallState of class  CStall */
#ifndef TOLUA_DISABLE_tolua_stall_CStall_GetStallState00
static int tolua_stall_CStall_GetStallState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CStall",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CStall* self = (const CStall*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStallState'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetStallState();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStallState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStallName of class  CStall */
#ifndef TOLUA_DISABLE_tolua_stall_CStall_GetStallName00
static int tolua_stall_CStall_GetStallName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CStall",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CStall* self = (const CStall*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStallName'", NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->GetStallName();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStallName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStallLevelUpExpireTime of class  CStall */
#ifndef TOLUA_DISABLE_tolua_stall_CStall_GetStallLevelUpExpireTime00
static int tolua_stall_CStall_GetStallLevelUpExpireTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CStall",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CStall* self = (const CStall*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStallLevelUpExpireTime'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetStallLevelUpExpireTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStallLevelUpExpireTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFirstGoodSolt of class  CStall */
#ifndef TOLUA_DISABLE_tolua_stall_CStall_GetFirstGoodSolt00
static int tolua_stall_CStall_GetFirstGoodSolt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CStall",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CStall* self = (CStall*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFirstGoodSolt'", NULL);
#endif
 {
  signed char tolua_ret = ( signed char)  self->GetFirstGoodSolt();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFirstGoodSolt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFirstGoodModifyFrame of class  CStall */
#ifndef TOLUA_DISABLE_tolua_stall_CStall_GetFirstGoodModifyFrame00
static int tolua_stall_CStall_GetFirstGoodModifyFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CStall",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CStall* self = (CStall*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFirstGoodModifyFrame'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetFirstGoodModifyFrame();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFirstGoodModifyFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNextAddGoodSolt of class  CStall */
#ifndef TOLUA_DISABLE_tolua_stall_CStall_GetNextAddGoodSolt00
static int tolua_stall_CStall_GetNextAddGoodSolt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CStall",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CStall* self = (CStall*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNextAddGoodSolt'", NULL);
#endif
 {
  signed char tolua_ret = ( signed char)  self->GetNextAddGoodSolt();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNextAddGoodSolt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsItemAlreadyInStall of class  CStall */
#ifndef TOLUA_DISABLE_tolua_stall_CStall_IsItemAlreadyInStall00
static int tolua_stall_CStall_IsItemAlreadyInStall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CStall",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CStall* self = (CStall*)  tolua_tousertype(tolua_S,1,0);
  unsigned char byConSlot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char byItemSlot = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsItemAlreadyInStall'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsItemAlreadyInStall(byConSlot,byItemSlot);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsItemAlreadyInStall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_stall_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CSceneObject","CSceneObject","",NULL);
 tolua_beginmodule(tolua_S,"CSceneObject");
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetObjID00
  tolua_function(tolua_S,"GetObjID",tolua_stall_CSceneObject_GetObjID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetObjType00
  tolua_function(tolua_S,"GetObjType",tolua_stall_CSceneObject_GetObjType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetScene00
  tolua_function(tolua_S,"GetScene",tolua_stall_CSceneObject_GetScene00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetRegion00
  tolua_function(tolua_S,"GetRegion",tolua_stall_CSceneObject_GetRegion00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetZone00
  tolua_function(tolua_S,"GetZone",tolua_stall_CSceneObject_GetZone00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetGrid00
  tolua_function(tolua_S,"GetGrid",tolua_stall_CSceneObject_GetGrid00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetGridInstance00
  tolua_function(tolua_S,"GetGridInstance",tolua_stall_CSceneObject_GetGridInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetX00
  tolua_function(tolua_S,"SetX",tolua_stall_CSceneObject_SetX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetY00
  tolua_function(tolua_S,"SetY",tolua_stall_CSceneObject_SetY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetZ00
  tolua_function(tolua_S,"SetZ",tolua_stall_CSceneObject_SetZ00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetX00
  tolua_function(tolua_S,"GetX",tolua_stall_CSceneObject_GetX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetY00
  tolua_function(tolua_S,"GetY",tolua_stall_CSceneObject_GetY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetZ00
  tolua_function(tolua_S,"GetZ",tolua_stall_CSceneObject_GetZ00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetFaceDirection00
  tolua_function(tolua_S,"SetFaceDirection",tolua_stall_CSceneObject_SetFaceDirection00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetFaceDirection00
  tolua_function(tolua_S,"GetFaceDirection",tolua_stall_CSceneObject_GetFaceDirection00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetBodyType00
  tolua_function(tolua_S,"SetBodyType",tolua_stall_CSceneObject_SetBodyType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetBodyType00
  tolua_function(tolua_S,"GetBodyType",tolua_stall_CSceneObject_GetBodyType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_CanTeleport00
  tolua_function(tolua_S,"CanTeleport",tolua_stall_CSceneObject_CanTeleport00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetObjID01
  tolua_function(tolua_S,"GetObjID",tolua_stall_CSceneObject_GetObjID01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetObjType01
  tolua_function(tolua_S,"GetObjType",tolua_stall_CSceneObject_GetObjType01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetScene01
  tolua_function(tolua_S,"GetScene",tolua_stall_CSceneObject_GetScene01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetRegion01
  tolua_function(tolua_S,"GetRegion",tolua_stall_CSceneObject_GetRegion01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetZone01
  tolua_function(tolua_S,"GetZone",tolua_stall_CSceneObject_GetZone01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetGrid01
  tolua_function(tolua_S,"GetGrid",tolua_stall_CSceneObject_GetGrid01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetGridInstance01
  tolua_function(tolua_S,"GetGridInstance",tolua_stall_CSceneObject_GetGridInstance01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetX01
  tolua_function(tolua_S,"SetX",tolua_stall_CSceneObject_SetX01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetY01
  tolua_function(tolua_S,"SetY",tolua_stall_CSceneObject_SetY01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetZ01
  tolua_function(tolua_S,"SetZ",tolua_stall_CSceneObject_SetZ01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetX01
  tolua_function(tolua_S,"GetX",tolua_stall_CSceneObject_GetX01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetY01
  tolua_function(tolua_S,"GetY",tolua_stall_CSceneObject_GetY01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetZ01
  tolua_function(tolua_S,"GetZ",tolua_stall_CSceneObject_GetZ01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetFaceDirection01
  tolua_function(tolua_S,"SetFaceDirection",tolua_stall_CSceneObject_SetFaceDirection01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetFaceDirection01
  tolua_function(tolua_S,"GetFaceDirection",tolua_stall_CSceneObject_GetFaceDirection01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_SetBodyType01
  tolua_function(tolua_S,"SetBodyType",tolua_stall_CSceneObject_SetBodyType01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_GetBodyType01
  tolua_function(tolua_S,"GetBodyType",tolua_stall_CSceneObject_GetBodyType01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSceneObject_CanTeleport01
  tolua_function(tolua_S,"CanTeleport",tolua_stall_CSceneObject_CanTeleport01);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CAuraInstance","CAuraInstance","CAura",NULL);
 tolua_beginmodule(tolua_S,"CAuraInstance");
#ifndef TOLUA_DISABLE_tolua_stall_CAuraInstance_GetInstanceID00
  tolua_function(tolua_S,"GetInstanceID",tolua_stall_CAuraInstance_GetInstanceID00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CCoolDown","CCoolDown","",NULL);
 tolua_beginmodule(tolua_S,"CCoolDown");
#ifndef TOLUA_DISABLE_tolua_stall_CCoolDown_Add00
  tolua_function(tolua_S,"Add",tolua_stall_CCoolDown_Add00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCoolDown_Reset00
  tolua_function(tolua_S,"Reset",tolua_stall_CCoolDown_Reset00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCoolDown_CheckReady00
  tolua_function(tolua_S,"CheckReady",tolua_stall_CCoolDown_CheckReady00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCoolDown_GetRemainFrm00
  tolua_function(tolua_S,"GetRemainFrm",tolua_stall_CCoolDown_GetRemainFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCoolDown_Enable00
  tolua_function(tolua_S,"Enable",tolua_stall_CCoolDown_Enable00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 #ifdef __cplusplus
 tolua_cclass(tolua_S,"CTargetScanner","CTargetScanner","",tolua_collect_CTargetScanner);
 #else
 tolua_cclass(tolua_S,"CTargetScanner","CTargetScanner","",NULL);
 #endif
 tolua_beginmodule(tolua_S,"CTargetScanner");
#ifndef TOLUA_DISABLE_tolua_stall_CTargetScanner_new00
  tolua_function(tolua_S,"new",tolua_stall_CTargetScanner_new00);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_stall_CTargetScanner_new00_local);
  tolua_function(tolua_S,".call",tolua_stall_CTargetScanner_new00_local);
#ifndef TOLUA_DISABLE_tolua_stall_CTargetScanner_delete00
  tolua_function(tolua_S,"delete",tolua_stall_CTargetScanner_delete00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CTargetScanner_GetTargetX00
  tolua_function(tolua_S,"GetTargetX",tolua_stall_CTargetScanner_GetTargetX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CTargetScanner_GetTargetY00
  tolua_function(tolua_S,"GetTargetY",tolua_stall_CTargetScanner_GetTargetY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CTargetScanner_GetTargetZ00
  tolua_function(tolua_S,"GetTargetZ",tolua_stall_CTargetScanner_GetTargetZ00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 #ifdef __cplusplus
 tolua_cclass(tolua_S,"CSpellInstance","CSpellInstance","",tolua_collect_CSpellInstance);
 #else
 tolua_cclass(tolua_S,"CSpellInstance","CSpellInstance","",NULL);
 #endif
 tolua_beginmodule(tolua_S,"CSpellInstance");
#ifndef TOLUA_DISABLE_tolua_stall_CSpellInstance_new00
  tolua_function(tolua_S,"new",tolua_stall_CSpellInstance_new00);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_stall_CSpellInstance_new00_local);
  tolua_function(tolua_S,".call",tolua_stall_CSpellInstance_new00_local);
#ifndef TOLUA_DISABLE_tolua_stall_CSpellInstance_delete00
  tolua_function(tolua_S,"delete",tolua_stall_CSpellInstance_delete00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CSpellInstance_GetScanner00
  tolua_function(tolua_S,"GetScanner",tolua_stall_CSpellInstance_GetScanner00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CCharacter","CCharacter","CSceneObject",NULL);
 tolua_beginmodule(tolua_S,"CCharacter");
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_JumpTo00
  tolua_function(tolua_S,"JumpTo",tolua_stall_CCharacter_JumpTo00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetClass00
  tolua_function(tolua_S,"GetClass",tolua_stall_CCharacter_GetClass00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetSex00
  tolua_function(tolua_S,"GetSex",tolua_stall_CCharacter_GetSex00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetLevel00
  tolua_function(tolua_S,"GetLevel",tolua_stall_CCharacter_GetLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetName00
  tolua_function(tolua_S,"GetName",tolua_stall_CCharacter_GetName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetClass00
  tolua_function(tolua_S,"SetClass",tolua_stall_CCharacter_SetClass00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetSex00
  tolua_function(tolua_S,"SetSex",tolua_stall_CCharacter_SetSex00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetLevel00
  tolua_function(tolua_S,"SetLevel",tolua_stall_CCharacter_SetLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetAttr00
  tolua_function(tolua_S,"GetAttr",tolua_stall_CCharacter_GetAttr00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetAttrList00
  tolua_function(tolua_S,"GetAttrList",tolua_stall_CCharacter_GetAttrList00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetInCutScene00
  tolua_function(tolua_S,"SetInCutScene",tolua_stall_CCharacter_SetInCutScene00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_MoveTo00
  tolua_function(tolua_S,"MoveTo",tolua_stall_CCharacter_MoveTo00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_Die00
  tolua_function(tolua_S,"Die",tolua_stall_CCharacter_Die00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_Revive00
  tolua_function(tolua_S,"Revive",tolua_stall_CCharacter_Revive00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_RotateTo00
  tolua_function(tolua_S,"RotateTo",tolua_stall_CCharacter_RotateTo00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetCanRun00
  tolua_function(tolua_S,"SetCanRun",tolua_stall_CCharacter_SetCanRun00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetMoveState00
  tolua_function(tolua_S,"GetMoveState",tolua_stall_CCharacter_GetMoveState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetHome00
  tolua_function(tolua_S,"SetHome",tolua_stall_CCharacter_SetHome00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetHomeX00
  tolua_function(tolua_S,"GetHomeX",tolua_stall_CCharacter_GetHomeX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetHomeY00
  tolua_function(tolua_S,"GetHomeY",tolua_stall_CCharacter_GetHomeY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetHomeZ00
  tolua_function(tolua_S,"GetHomeZ",tolua_stall_CCharacter_GetHomeZ00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_CancelCast00
  tolua_function(tolua_S,"CancelCast",tolua_stall_CCharacter_CancelCast00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_IsCasting00
  tolua_function(tolua_S,"IsCasting",tolua_stall_CCharacter_IsCasting00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_EquipRune00
  tolua_function(tolua_S,"EquipRune",tolua_stall_CCharacter_EquipRune00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_UnEquipRune00
  tolua_function(tolua_S,"UnEquipRune",tolua_stall_CCharacter_UnEquipRune00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetSpellSlot00
  tolua_function(tolua_S,"GetSpellSlot",tolua_stall_CCharacter_GetSpellSlot00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_CastSpell00
  tolua_function(tolua_S,"CastSpell",tolua_stall_CCharacter_CastSpell00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_PlayAction00
  tolua_function(tolua_S,"PlayAction",tolua_stall_CCharacter_PlayAction00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetCastingSpell00
  tolua_function(tolua_S,"GetCastingSpell",tolua_stall_CCharacter_GetCastingSpell00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetHp00
  tolua_function(tolua_S,"GetHp",tolua_stall_CCharacter_GetHp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetHp00
  tolua_function(tolua_S,"SetHp",tolua_stall_CCharacter_SetHp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_ChangeHp00
  tolua_function(tolua_S,"ChangeHp",tolua_stall_CCharacter_ChangeHp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetMp00
  tolua_function(tolua_S,"GetMp",tolua_stall_CCharacter_GetMp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_ChangeMp00
  tolua_function(tolua_S,"ChangeMp",tolua_stall_CCharacter_ChangeMp00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_CanAttack00
  tolua_function(tolua_S,"CanAttack",tolua_stall_CCharacter_CanAttack00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetSpellBook00
  tolua_function(tolua_S,"GetSpellBook",tolua_stall_CCharacter_GetSpellBook00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_AppendAura00
  tolua_function(tolua_S,"AppendAura",tolua_stall_CCharacter_AppendAura00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetFirstAura00
  tolua_function(tolua_S,"GetFirstAura",tolua_stall_CCharacter_GetFirstAura00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_RemoveAura00
  tolua_function(tolua_S,"RemoveAura",tolua_stall_CCharacter_RemoveAura00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_RemoveAuraByType00
  tolua_function(tolua_S,"RemoveAuraByType",tolua_stall_CCharacter_RemoveAuraByType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_RemoveAuraBySubType00
  tolua_function(tolua_S,"RemoveAuraBySubType",tolua_stall_CCharacter_RemoveAuraBySubType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_IsDead00
  tolua_function(tolua_S,"IsDead",tolua_stall_CCharacter_IsDead00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetFlag00
  tolua_function(tolua_S,"GetFlag",tolua_stall_CCharacter_GetFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetExFlag00
  tolua_function(tolua_S,"GetExFlag",tolua_stall_CCharacter_GetExFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetCCFlag00
  tolua_function(tolua_S,"GetCCFlag",tolua_stall_CCharacter_GetCCFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_IncControlCount00
  tolua_function(tolua_S,"IncControlCount",tolua_stall_CCharacter_IncControlCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_DecControlCount00
  tolua_function(tolua_S,"DecControlCount",tolua_stall_CCharacter_DecControlCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetControlCount00
  tolua_function(tolua_S,"GetControlCount",tolua_stall_CCharacter_GetControlCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetLastCasterID00
  tolua_function(tolua_S,"SetLastCasterID",tolua_stall_CCharacter_SetLastCasterID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetLastCasterID00
  tolua_function(tolua_S,"GetLastCasterID",tolua_stall_CCharacter_GetLastCasterID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetLastCasterTimer00
  tolua_function(tolua_S,"GetLastCasterTimer",tolua_stall_CCharacter_GetLastCasterTimer00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetLastTargetID00
  tolua_function(tolua_S,"SetLastTargetID",tolua_stall_CCharacter_SetLastTargetID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetLastTargetID00
  tolua_function(tolua_S,"GetLastTargetID",tolua_stall_CCharacter_GetLastTargetID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetLastTargetTimer00
  tolua_function(tolua_S,"GetLastTargetTimer",tolua_stall_CCharacter_GetLastTargetTimer00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetDropOwnerID00
  tolua_function(tolua_S,"SetDropOwnerID",tolua_stall_CCharacter_SetDropOwnerID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetDropOwnerID00
  tolua_function(tolua_S,"GetDropOwnerID",tolua_stall_CCharacter_GetDropOwnerID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SelectFocus00
  tolua_function(tolua_S,"SelectFocus",tolua_stall_CCharacter_SelectFocus00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetFocusID00
  tolua_function(tolua_S,"GetFocusID",tolua_stall_CCharacter_GetFocusID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_Say00
  tolua_function(tolua_S,"Say",tolua_stall_CCharacter_Say00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SendMail00
  tolua_function(tolua_S,"SendMail",tolua_stall_CCharacter_SendMail00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SendMail01
  tolua_function(tolua_S,"SendMail",tolua_stall_CCharacter_SendMail01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetAIProcessor00
  tolua_function(tolua_S,"SetAIProcessor",tolua_stall_CCharacter_SetAIProcessor00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetAIProcessor00
  tolua_function(tolua_S,"GetAIProcessor",tolua_stall_CCharacter_GetAIProcessor00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetOriginalAiID00
  tolua_function(tolua_S,"GetOriginalAiID",tolua_stall_CCharacter_GetOriginalAiID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_SetGlobalCDDelayFrame00
  tolua_function(tolua_S,"SetGlobalCDDelayFrame",tolua_stall_CCharacter_SetGlobalCDDelayFrame00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetGlobalCDDelayFrame00
  tolua_function(tolua_S,"GetGlobalCDDelayFrame",tolua_stall_CCharacter_GetGlobalCDDelayFrame00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetCoolDown00
  tolua_function(tolua_S,"GetCoolDown",tolua_stall_CCharacter_GetCoolDown00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_GetHostID00
  tolua_function(tolua_S,"GetHostID",tolua_stall_CCharacter_GetHostID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CCharacter_Mine00
  tolua_function(tolua_S,"Mine",tolua_stall_CCharacter_Mine00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CFlagBits","CFlagBits","",NULL);
 tolua_beginmodule(tolua_S,"CFlagBits");
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_new00
  tolua_function(tolua_S,"new",tolua_stall_CFlagBits_new00);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_stall_CFlagBits_new00_local);
  tolua_function(tolua_S,".call",tolua_stall_CFlagBits_new00_local);
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_CheckFlag00
  tolua_function(tolua_S,"CheckFlag",tolua_stall_CFlagBits_CheckFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_SetFlag00
  tolua_function(tolua_S,"SetFlag",tolua_stall_CFlagBits_SetFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_ClearFlag00
  tolua_function(tolua_S,"ClearFlag",tolua_stall_CFlagBits_ClearFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_ResetFlag00
  tolua_function(tolua_S,"ResetFlag",tolua_stall_CFlagBits_ResetFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_FlagIncludeBits00
  tolua_function(tolua_S,"FlagIncludeBits",tolua_stall_CFlagBits_FlagIncludeBits00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_FlagNotIncludeBits00
  tolua_function(tolua_S,"FlagNotIncludeBits",tolua_stall_CFlagBits_FlagNotIncludeBits00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CFlagBits_GetFlag00
  tolua_function(tolua_S,"GetFlag",tolua_stall_CFlagBits_GetFlag00);
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
 tolua_cclass(tolua_S,"CStall","CStall","",NULL);
 tolua_beginmodule(tolua_S,"CStall");
#ifndef TOLUA_DISABLE_tolua_stall_CStall_GetStallState00
  tolua_function(tolua_S,"GetStallState",tolua_stall_CStall_GetStallState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CStall_GetStallName00
  tolua_function(tolua_S,"GetStallName",tolua_stall_CStall_GetStallName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CStall_GetStallLevelUpExpireTime00
  tolua_function(tolua_S,"GetStallLevelUpExpireTime",tolua_stall_CStall_GetStallLevelUpExpireTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CStall_GetFirstGoodSolt00
  tolua_function(tolua_S,"GetFirstGoodSolt",tolua_stall_CStall_GetFirstGoodSolt00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CStall_GetFirstGoodModifyFrame00
  tolua_function(tolua_S,"GetFirstGoodModifyFrame",tolua_stall_CStall_GetFirstGoodModifyFrame00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CStall_GetNextAddGoodSolt00
  tolua_function(tolua_S,"GetNextAddGoodSolt",tolua_stall_CStall_GetNextAddGoodSolt00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_stall_CStall_IsItemAlreadyInStall00
  tolua_function(tolua_S,"IsItemAlreadyInStall",tolua_stall_CStall_IsItemAlreadyInStall00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_stall (lua_State* tolua_S) {
 return tolua_stall_open(tolua_S);
};
#endif

