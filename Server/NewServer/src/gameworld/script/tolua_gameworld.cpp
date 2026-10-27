/*
** Lua binding: gameworld
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_gameworld_open (lua_State* tolua_S);

#include "game_world.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CSceneObject");
 tolua_usertype(tolua_S,"CCharacter");
 tolua_usertype(tolua_S,"CDoodad");
 tolua_usertype(tolua_S,"BTNod");
 tolua_usertype(tolua_S,"CRole");
 tolua_usertype(tolua_S,"CTeamInGS");
 tolua_usertype(tolua_S,"CNpc");
 tolua_usertype(tolua_S,"CGameWorld");
}

/* method: GetInstance of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetInstance00
static int tolua_gameworld_CGameWorld_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CGameWorld& tolua_ret = (CGameWorld&)  CGameWorld::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CGameWorld");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGameFrame of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetGameFrame00
static int tolua_gameworld_CGameWorld_GetGameFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGameFrame'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetGameFrame();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGameFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindRole of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindRole00
static int tolua_gameworld_CGameWorld_FindRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindRole'", NULL);
#endif
 {
  CRole* tolua_ret = (CRole*)  self->FindRole(dwRoleID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CRole");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCanCast of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetCanCast00
static int tolua_gameworld_CGameWorld_SetCanCast00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
   bool bCanCast = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCanCast'", NULL);
#endif
 {
  self->SetCanCast(bCanCast);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCanCast'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanCast of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_CanCast00
static int tolua_gameworld_CGameWorld_CanCast00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanCast'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CanCast();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanCast'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDrawDebugLine of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetDrawDebugLine00
static int tolua_gameworld_CGameWorld_SetDrawDebugLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
   bool bDraw = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDrawDebugLine'", NULL);
#endif
 {
  self->SetDrawDebugLine(bDraw);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDrawDebugLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCheckConsume of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetCheckConsume00
static int tolua_gameworld_CGameWorld_SetCheckConsume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
   bool bCheck = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCheckConsume'", NULL);
#endif
 {
  self->SetCheckConsume(bCheck);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCheckConsume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NewRole of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_NewRole00
static int tolua_gameworld_CGameWorld_NewRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NewRole'", NULL);
#endif
 {
  CRole* tolua_ret = (CRole*)  self->NewRole(dwRoleID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CRole");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NewRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelRole of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_DelRole00
static int tolua_gameworld_CGameWorld_DelRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  CRole* poRole = ((CRole*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelRole'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DelRole(poRole);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindRole of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindRole01
static int tolua_gameworld_CGameWorld_FindRole01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindRole'", NULL);
#endif
 {
  CRole* tolua_ret = (CRole*)  self->FindRole(dwRoleID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CRole");
 }
 }
 return 1;
tolua_lerror:
 return tolua_gameworld_CGameWorld_FindRole00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoleCount of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetRoleCount00
static int tolua_gameworld_CGameWorld_GetRoleCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoleCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetRoleCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRoleCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NewNpc of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_NewNpc00
static int tolua_gameworld_CGameWorld_NewNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwNpcID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NewNpc'", NULL);
#endif
 {
  CNpc* tolua_ret = (CNpc*)  self->NewNpc(dwNpcID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CNpc");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NewNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelNpc of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_DelNpc00
static int tolua_gameworld_CGameWorld_DelNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CNpc",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  CNpc* poNpc = ((CNpc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelNpc'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DelNpc(poNpc);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindNpc of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindNpc00
static int tolua_gameworld_CGameWorld_FindNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwNpcID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindNpc'", NULL);
#endif
 {
  CNpc* tolua_ret = (CNpc*)  self->FindNpc(dwNpcID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CNpc");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNpcID of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetNpcID00
static int tolua_gameworld_CGameWorld_GetNpcID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CNpc",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  CNpc* poNpc = ((CNpc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNpcID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetNpcID(poNpc);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNpcID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindTeam of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindTeam00
static int tolua_gameworld_CGameWorld_FindTeam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTeamID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindTeam'", NULL);
#endif
 {
  CTeamInGS* tolua_ret = (CTeamInGS*)  self->FindTeam(dwTeamID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTeamInGS");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindTeam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NewDoodad of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_NewDoodad00
static int tolua_gameworld_CGameWorld_NewDoodad00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NewDoodad'", NULL);
#endif
 {
  CDoodad* tolua_ret = (CDoodad*)  self->NewDoodad();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDoodad");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NewDoodad'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelDoodad of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_DelDoodad00
static int tolua_gameworld_CGameWorld_DelDoodad00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CDoodad",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  CDoodad* poDoodad = ((CDoodad*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelDoodad'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DelDoodad(poDoodad);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelDoodad'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindDoodad of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindDoodad00
static int tolua_gameworld_CGameWorld_FindDoodad00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwDoodadID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindDoodad'", NULL);
#endif
 {
  CDoodad* tolua_ret = (CDoodad*)  self->FindDoodad(dwDoodadID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDoodad");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindDoodad'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindCharacter of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindCharacter00
static int tolua_gameworld_CGameWorld_FindCharacter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwCharID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindCharacter'", NULL);
#endif
 {
  CCharacter* tolua_ret = (CCharacter*)  self->FindCharacter(dwCharID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCharacter");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindCharacter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindValidRole of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindValidRole00
static int tolua_gameworld_CGameWorld_FindValidRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindValidRole'", NULL);
#endif
 {
  CRole* tolua_ret = (CRole*)  self->FindValidRole(dwRoleID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CRole");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindValidRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindValidCharacter of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindValidCharacter00
static int tolua_gameworld_CGameWorld_FindValidCharacter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwCharID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindValidCharacter'", NULL);
#endif
 {
  CCharacter* tolua_ret = (CCharacter*)  self->FindValidCharacter(dwCharID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCharacter");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindValidCharacter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindValidObj of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindValidObj00
static int tolua_gameworld_CGameWorld_FindValidObj00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwObj = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindValidObj'", NULL);
#endif
 {
  CSceneObject* tolua_ret = (CSceneObject*)  self->FindValidObj(dwObj);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSceneObject");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindValidObj'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: JumpTo of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_JumpTo00
static int tolua_gameworld_CGameWorld_JumpTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  CRole* poRole = ((CRole*)  tolua_tousertype(tolua_S,2,0));
  signed int nSceneTempID = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nSceneID = (( signed int)  tolua_tonumber(tolua_S,4,0));
  signed int nX = (( signed int)  tolua_tonumber(tolua_S,5,0));
  signed int nY = (( signed int)  tolua_tonumber(tolua_S,6,0));
  signed int nZ = (( signed int)  tolua_tonumber(tolua_S,7,0));
  signed int nFaceDirection = (( signed int)  tolua_tonumber(tolua_S,8,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'JumpTo'", NULL);
#endif
 {
 int tolua_ret = (int)
self->JumpTo(poRole,nSceneTempID,nSceneID,nX,nY,nZ,nFaceDirection);
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

/* method: JumpToRole of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_JumpToRole00
static int tolua_gameworld_CGameWorld_JumpToRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CRole",0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  CRole* poRole = ((CRole*)  tolua_tousertype(tolua_S,2,0));
  const char* pcszRoleName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'JumpToRole'", NULL);
#endif
 {
 int tolua_ret = (int)
self->JumpToRole(poRole,pcszRoleName);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'JumpToRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TakeRole of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_TakeRole00
static int tolua_gameworld_CGameWorld_TakeRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CRole",0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  CRole* poRole = ((CRole*)  tolua_tousertype(tolua_S,2,0));
  const char* pcszRoleName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TakeRole'", NULL);
#endif
 {
 int tolua_ret = (int)
self->TakeRole(poRole,pcszRoleName);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TakeRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NewBTNod of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_NewBTNod00
static int tolua_gameworld_CGameWorld_NewBTNod00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NewBTNod'", NULL);
#endif
 {
  BTNod* tolua_ret = (BTNod*)  self->NewBTNod();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"BTNod");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NewBTNod'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelBTNod of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_DelBTNod00
static int tolua_gameworld_CGameWorld_DelBTNod00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"BTNod",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  BTNod* poNod = ((BTNod*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelBTNod'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DelBTNod(poNod);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelBTNod'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGameTime of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetGameTime00
static int tolua_gameworld_CGameWorld_SetGameTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwGameTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGameTime'", NULL);
#endif
 {
  self->SetGameTime(dwGameTime);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGameTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGameTime of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetGameTime00
static int tolua_gameworld_CGameWorld_GetGameTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGameTime'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetGameTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGameTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTimeZone of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetTimeZone00
static int tolua_gameworld_CGameWorld_GetTimeZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTimeZone'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetTimeZone();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTimeZone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFreezeTime of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetFreezeTime00
static int tolua_gameworld_CGameWorld_SetFreezeTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
   bool bFreezeTime = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFreezeTime'", NULL);
#endif
 {
  self->SetFreezeTime(bFreezeTime);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFreezeTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFreezeTime of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_IsFreezeTime00
static int tolua_gameworld_CGameWorld_IsFreezeTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFreezeTime'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsFreezeTime();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFreezeTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToggleGlobalDropMax of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_ToggleGlobalDropMax00
static int tolua_gameworld_CGameWorld_ToggleGlobalDropMax00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToggleGlobalDropMax'", NULL);
#endif
 {
  self->ToggleGlobalDropMax();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToggleGlobalDropMax'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGlobalDropRate of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetGlobalDropRate00
static int tolua_gameworld_CGameWorld_SetGlobalDropRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  signed int nDropRate = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGlobalDropRate'", NULL);
#endif
 {
  self->SetGlobalDropRate(nDropRate);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGlobalDropRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGlobalDropRate of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetGlobalDropRate00
static int tolua_gameworld_CGameWorld_GetGlobalDropRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGlobalDropRate'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetGlobalDropRate();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGlobalDropRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGlobalExpRate of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetGlobalExpRate00
static int tolua_gameworld_CGameWorld_SetGlobalExpRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  signed int nExpRate = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGlobalExpRate'", NULL);
#endif
 {
  self->SetGlobalExpRate(nExpRate);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGlobalExpRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGlobalExpRate of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetGlobalExpRate00
static int tolua_gameworld_CGameWorld_GetGlobalExpRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGlobalExpRate'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetGlobalExpRate();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGlobalExpRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAverageLevel of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetAverageLevel00
static int tolua_gameworld_CGameWorld_GetAverageLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  signed int nServerGroup = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAverageLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetAverageLevel(nServerGroup);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAverageLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetServerVariable of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetServerVariable00
static int tolua_gameworld_CGameWorld_GetServerVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  signed int nServerGroup = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nVarIndex = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetServerVariable'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetServerVariable(nServerGroup,nVarIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetServerVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetServerVariable of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetServerVariable00
static int tolua_gameworld_CGameWorld_SetServerVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  signed int nServerGroup = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nVarIndex = (( signed int)  tolua_tonumber(tolua_S,3,0));
   bool bAbsoluteValue = ((  bool)  tolua_toboolean(tolua_S,4,0));
  signed int nVarValue = (( signed int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetServerVariable'", NULL);
#endif
 {
  self->SetServerVariable(nServerGroup,nVarIndex,bAbsoluteValue,nVarValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetServerVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGsSessionID of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetGsSessionID00
static int tolua_gameworld_CGameWorld_GetGsSessionID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGsSessionID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetGsSessionID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGsSessionID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PrintMemoryStat of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_PrintMemoryStat00
static int tolua_gameworld_CGameWorld_PrintMemoryStat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PrintMemoryStat'", NULL);
#endif
 {
  self->PrintMemoryStat();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrintMemoryStat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PrintNpcPool of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_PrintNpcPool00
static int tolua_gameworld_CGameWorld_PrintNpcPool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PrintNpcPool'", NULL);
#endif
 {
  self->PrintNpcPool();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrintNpcPool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PrintRolePool of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_PrintRolePool00
static int tolua_gameworld_CGameWorld_PrintRolePool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PrintRolePool'", NULL);
#endif
 {
  self->PrintRolePool();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrintRolePool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PrintScenePool of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_PrintScenePool00
static int tolua_gameworld_CGameWorld_PrintScenePool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
   bool bDetail = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PrintScenePool'", NULL);
#endif
 {
  self->PrintScenePool(bDetail);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrintScenePool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAverageLevel of class  CGameWorld */
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetAverageLevel01
static int tolua_gameworld_CGameWorld_GetAverageLevel01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGameWorld",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CGameWorld* self = (CGameWorld*)  tolua_tousertype(tolua_S,1,0);
  signed int nServerGroup = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAverageLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetAverageLevel(nServerGroup);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_gameworld_CGameWorld_GetAverageLevel00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_gameworld_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CGameWorld","CGameWorld","",NULL);
 tolua_beginmodule(tolua_S,"CGameWorld");
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_gameworld_CGameWorld_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetGameFrame00
  tolua_function(tolua_S,"GetGameFrame",tolua_gameworld_CGameWorld_GetGameFrame00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindRole00
  tolua_function(tolua_S,"FindRole",tolua_gameworld_CGameWorld_FindRole00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetCanCast00
  tolua_function(tolua_S,"SetCanCast",tolua_gameworld_CGameWorld_SetCanCast00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_CanCast00
  tolua_function(tolua_S,"CanCast",tolua_gameworld_CGameWorld_CanCast00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetDrawDebugLine00
  tolua_function(tolua_S,"SetDrawDebugLine",tolua_gameworld_CGameWorld_SetDrawDebugLine00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetCheckConsume00
  tolua_function(tolua_S,"SetCheckConsume",tolua_gameworld_CGameWorld_SetCheckConsume00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_NewRole00
  tolua_function(tolua_S,"NewRole",tolua_gameworld_CGameWorld_NewRole00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_DelRole00
  tolua_function(tolua_S,"DelRole",tolua_gameworld_CGameWorld_DelRole00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindRole01
  tolua_function(tolua_S,"FindRole",tolua_gameworld_CGameWorld_FindRole01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetRoleCount00
  tolua_function(tolua_S,"GetRoleCount",tolua_gameworld_CGameWorld_GetRoleCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_NewNpc00
  tolua_function(tolua_S,"NewNpc",tolua_gameworld_CGameWorld_NewNpc00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_DelNpc00
  tolua_function(tolua_S,"DelNpc",tolua_gameworld_CGameWorld_DelNpc00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindNpc00
  tolua_function(tolua_S,"FindNpc",tolua_gameworld_CGameWorld_FindNpc00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetNpcID00
  tolua_function(tolua_S,"GetNpcID",tolua_gameworld_CGameWorld_GetNpcID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindTeam00
  tolua_function(tolua_S,"FindTeam",tolua_gameworld_CGameWorld_FindTeam00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_NewDoodad00
  tolua_function(tolua_S,"NewDoodad",tolua_gameworld_CGameWorld_NewDoodad00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_DelDoodad00
  tolua_function(tolua_S,"DelDoodad",tolua_gameworld_CGameWorld_DelDoodad00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindDoodad00
  tolua_function(tolua_S,"FindDoodad",tolua_gameworld_CGameWorld_FindDoodad00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindCharacter00
  tolua_function(tolua_S,"FindCharacter",tolua_gameworld_CGameWorld_FindCharacter00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindValidRole00
  tolua_function(tolua_S,"FindValidRole",tolua_gameworld_CGameWorld_FindValidRole00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindValidCharacter00
  tolua_function(tolua_S,"FindValidCharacter",tolua_gameworld_CGameWorld_FindValidCharacter00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_FindValidObj00
  tolua_function(tolua_S,"FindValidObj",tolua_gameworld_CGameWorld_FindValidObj00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_JumpTo00
  tolua_function(tolua_S,"JumpTo",tolua_gameworld_CGameWorld_JumpTo00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_JumpToRole00
  tolua_function(tolua_S,"JumpToRole",tolua_gameworld_CGameWorld_JumpToRole00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_TakeRole00
  tolua_function(tolua_S,"TakeRole",tolua_gameworld_CGameWorld_TakeRole00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_NewBTNod00
  tolua_function(tolua_S,"NewBTNod",tolua_gameworld_CGameWorld_NewBTNod00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_DelBTNod00
  tolua_function(tolua_S,"DelBTNod",tolua_gameworld_CGameWorld_DelBTNod00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetGameTime00
  tolua_function(tolua_S,"SetGameTime",tolua_gameworld_CGameWorld_SetGameTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetGameTime00
  tolua_function(tolua_S,"GetGameTime",tolua_gameworld_CGameWorld_GetGameTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetTimeZone00
  tolua_function(tolua_S,"GetTimeZone",tolua_gameworld_CGameWorld_GetTimeZone00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetFreezeTime00
  tolua_function(tolua_S,"SetFreezeTime",tolua_gameworld_CGameWorld_SetFreezeTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_IsFreezeTime00
  tolua_function(tolua_S,"IsFreezeTime",tolua_gameworld_CGameWorld_IsFreezeTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_ToggleGlobalDropMax00
  tolua_function(tolua_S,"ToggleGlobalDropMax",tolua_gameworld_CGameWorld_ToggleGlobalDropMax00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetGlobalDropRate00
  tolua_function(tolua_S,"SetGlobalDropRate",tolua_gameworld_CGameWorld_SetGlobalDropRate00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetGlobalDropRate00
  tolua_function(tolua_S,"GetGlobalDropRate",tolua_gameworld_CGameWorld_GetGlobalDropRate00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetGlobalExpRate00
  tolua_function(tolua_S,"SetGlobalExpRate",tolua_gameworld_CGameWorld_SetGlobalExpRate00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetGlobalExpRate00
  tolua_function(tolua_S,"GetGlobalExpRate",tolua_gameworld_CGameWorld_GetGlobalExpRate00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetAverageLevel00
  tolua_function(tolua_S,"GetAverageLevel",tolua_gameworld_CGameWorld_GetAverageLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetServerVariable00
  tolua_function(tolua_S,"GetServerVariable",tolua_gameworld_CGameWorld_GetServerVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_SetServerVariable00
  tolua_function(tolua_S,"SetServerVariable",tolua_gameworld_CGameWorld_SetServerVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetGsSessionID00
  tolua_function(tolua_S,"GetGsSessionID",tolua_gameworld_CGameWorld_GetGsSessionID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_PrintMemoryStat00
  tolua_function(tolua_S,"PrintMemoryStat",tolua_gameworld_CGameWorld_PrintMemoryStat00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_PrintNpcPool00
  tolua_function(tolua_S,"PrintNpcPool",tolua_gameworld_CGameWorld_PrintNpcPool00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_PrintRolePool00
  tolua_function(tolua_S,"PrintRolePool",tolua_gameworld_CGameWorld_PrintRolePool00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_PrintScenePool00
  tolua_function(tolua_S,"PrintScenePool",tolua_gameworld_CGameWorld_PrintScenePool00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gameworld_CGameWorld_GetAverageLevel01
  tolua_function(tolua_S,"GetAverageLevel",tolua_gameworld_CGameWorld_GetAverageLevel01);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_gameworld (lua_State* tolua_S) {
 return tolua_gameworld_open(tolua_S);
};
#endif

