/*
** Lua binding: scene_object
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_scene_object_open (lua_State* tolua_S);

#include "scene_object.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CSceneObject");
 tolua_usertype(tolua_S,"GRID_DATA");
 tolua_usertype(tolua_S,"GRID_INSTANCE_DATA");
 tolua_usertype(tolua_S,"ZONE_DATA");
 tolua_usertype(tolua_S,"CScene");
 tolua_usertype(tolua_S,"CRegion");
}

/* method: GetObjID of class  CSceneObject */
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetObjID00
static int tolua_scene_object_CSceneObject_GetObjID00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetObjType00
static int tolua_scene_object_CSceneObject_GetObjType00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetScene00
static int tolua_scene_object_CSceneObject_GetScene00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetRegion00
static int tolua_scene_object_CSceneObject_GetRegion00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetZone00
static int tolua_scene_object_CSceneObject_GetZone00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetGrid00
static int tolua_scene_object_CSceneObject_GetGrid00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetGridInstance00
static int tolua_scene_object_CSceneObject_GetGridInstance00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_SetX00
static int tolua_scene_object_CSceneObject_SetX00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_SetY00
static int tolua_scene_object_CSceneObject_SetY00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_SetZ00
static int tolua_scene_object_CSceneObject_SetZ00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetX00
static int tolua_scene_object_CSceneObject_GetX00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetY00
static int tolua_scene_object_CSceneObject_GetY00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetZ00
static int tolua_scene_object_CSceneObject_GetZ00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_SetFaceDirection00
static int tolua_scene_object_CSceneObject_SetFaceDirection00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetFaceDirection00
static int tolua_scene_object_CSceneObject_GetFaceDirection00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_SetBodyType00
static int tolua_scene_object_CSceneObject_SetBodyType00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetBodyType00
static int tolua_scene_object_CSceneObject_GetBodyType00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_CanTeleport00
static int tolua_scene_object_CSceneObject_CanTeleport00(lua_State* tolua_S)
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

/* Open function */
TOLUA_API int tolua_scene_object_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CSceneObject","CSceneObject","",NULL);
 tolua_beginmodule(tolua_S,"CSceneObject");
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetObjID00
  tolua_function(tolua_S,"GetObjID",tolua_scene_object_CSceneObject_GetObjID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetObjType00
  tolua_function(tolua_S,"GetObjType",tolua_scene_object_CSceneObject_GetObjType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetScene00
  tolua_function(tolua_S,"GetScene",tolua_scene_object_CSceneObject_GetScene00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetRegion00
  tolua_function(tolua_S,"GetRegion",tolua_scene_object_CSceneObject_GetRegion00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetZone00
  tolua_function(tolua_S,"GetZone",tolua_scene_object_CSceneObject_GetZone00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetGrid00
  tolua_function(tolua_S,"GetGrid",tolua_scene_object_CSceneObject_GetGrid00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetGridInstance00
  tolua_function(tolua_S,"GetGridInstance",tolua_scene_object_CSceneObject_GetGridInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_SetX00
  tolua_function(tolua_S,"SetX",tolua_scene_object_CSceneObject_SetX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_SetY00
  tolua_function(tolua_S,"SetY",tolua_scene_object_CSceneObject_SetY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_SetZ00
  tolua_function(tolua_S,"SetZ",tolua_scene_object_CSceneObject_SetZ00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetX00
  tolua_function(tolua_S,"GetX",tolua_scene_object_CSceneObject_GetX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetY00
  tolua_function(tolua_S,"GetY",tolua_scene_object_CSceneObject_GetY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetZ00
  tolua_function(tolua_S,"GetZ",tolua_scene_object_CSceneObject_GetZ00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_SetFaceDirection00
  tolua_function(tolua_S,"SetFaceDirection",tolua_scene_object_CSceneObject_SetFaceDirection00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetFaceDirection00
  tolua_function(tolua_S,"GetFaceDirection",tolua_scene_object_CSceneObject_GetFaceDirection00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_SetBodyType00
  tolua_function(tolua_S,"SetBodyType",tolua_scene_object_CSceneObject_SetBodyType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_GetBodyType00
  tolua_function(tolua_S,"GetBodyType",tolua_scene_object_CSceneObject_GetBodyType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_object_CSceneObject_CanTeleport00
  tolua_function(tolua_S,"CanTeleport",tolua_scene_object_CSceneObject_CanTeleport00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_scene_object (lua_State* tolua_S) {
 return tolua_scene_object_open(tolua_S);
};
#endif

