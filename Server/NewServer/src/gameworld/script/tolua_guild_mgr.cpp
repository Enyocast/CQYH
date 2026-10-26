/*
** Lua binding: guild_mgr
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:29.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_guild_mgr_open (lua_State* tolua_S);

#include "guild_mgr.h"
#include "gs_guild.h"
#include "asimov_guild.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"GUILD_WAR_DATA");
 tolua_usertype(tolua_S,"CGSGuild");
 tolua_usertype(tolua_S,"CGuildMgr");
}

/* method: GetInstance of class  CGuildMgr */
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_GetInstance00
static int tolua_guild_mgr_CGuildMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CGuildMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CGuildMgr& tolua_ret = (CGuildMgr&)  CGuildMgr::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CGuildMgr");
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

/* method: FindGuild of class  CGuildMgr */
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_FindGuild00
static int tolua_guild_mgr_CGuildMgr_FindGuild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGuildMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGuildMgr* self = (CGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindGuild'", NULL);
#endif
 {
  CGSGuild* tolua_ret = (CGSGuild*)  self->FindGuild(dwGuildID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGSGuild");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindGuild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddWarRelation of class  CGuildMgr */
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_AddWarRelation00
static int tolua_guild_mgr_CGuildMgr_AddWarRelation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGuildMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGuildMgr* self = (CGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwIntruderID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwDefenderID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddWarRelation'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddWarRelation(dwIntruderID,dwDefenderID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddWarRelation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindWarRelation of class  CGuildMgr */
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_FindWarRelation00
static int tolua_guild_mgr_CGuildMgr_FindWarRelation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGuildMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGuildMgr* self = (CGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwIntruderID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwDefenderID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindWarRelation'", NULL);
#endif
 {
  GUILD_WAR_DATA* tolua_ret = (GUILD_WAR_DATA*)  self->FindWarRelation(dwIntruderID,dwDefenderID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GUILD_WAR_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindWarRelation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindWarByAttackGuildID of class  CGuildMgr */
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_FindWarByAttackGuildID00
static int tolua_guild_mgr_CGuildMgr_FindWarByAttackGuildID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGuildMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGuildMgr* self = (CGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwIntruderID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindWarByAttackGuildID'", NULL);
#endif
 {
  GUILD_WAR_DATA* tolua_ret = (GUILD_WAR_DATA*)  self->FindWarByAttackGuildID(dwIntruderID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GUILD_WAR_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindWarByAttackGuildID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindWarByDefendGuildID of class  CGuildMgr */
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_FindWarByDefendGuildID00
static int tolua_guild_mgr_CGuildMgr_FindWarByDefendGuildID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGuildMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGuildMgr* self = (CGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwDefenderID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindWarByDefendGuildID'", NULL);
#endif
 {
  GUILD_WAR_DATA* tolua_ret = (GUILD_WAR_DATA*)  self->FindWarByDefendGuildID(dwDefenderID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GUILD_WAR_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindWarByDefendGuildID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelWarRelation of class  CGuildMgr */
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_DelWarRelation00
static int tolua_guild_mgr_CGuildMgr_DelWarRelation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGuildMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGuildMgr* self = (CGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwIntruderID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwDefenderID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelWarRelation'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DelWarRelation(dwIntruderID,dwDefenderID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelWarRelation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsHostile of class  CGuildMgr */
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_IsHostile00
static int tolua_guild_mgr_CGuildMgr_IsHostile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGuildMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGuildMgr* self = (CGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwTargetGuildID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsHostile'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsHostile(dwGuildID,dwTargetGuildID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsHostile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFriendly of class  CGuildMgr */
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_IsFriendly00
static int tolua_guild_mgr_CGuildMgr_IsFriendly00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGuildMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGuildMgr* self = (CGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwTargetGuildID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFriendly'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsFriendly(dwGuildID,dwTargetGuildID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFriendly'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SendMSToAddRes */
#ifndef TOLUA_DISABLE_tolua_guild_mgr_SendMSToAddRes00
static int tolua_guild_mgr_SendMSToAddRes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nCount = (( signed int)  tolua_tonumber(tolua_S,3,0));
 {
 int tolua_ret = (int)
SendMSToAddRes(dwRoleID,nType,nCount);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendMSToAddRes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_guild_mgr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CGuildMgr","CGuildMgr","",NULL);
 tolua_beginmodule(tolua_S,"CGuildMgr");
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_guild_mgr_CGuildMgr_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_FindGuild00
  tolua_function(tolua_S,"FindGuild",tolua_guild_mgr_CGuildMgr_FindGuild00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_AddWarRelation00
  tolua_function(tolua_S,"AddWarRelation",tolua_guild_mgr_CGuildMgr_AddWarRelation00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_FindWarRelation00
  tolua_function(tolua_S,"FindWarRelation",tolua_guild_mgr_CGuildMgr_FindWarRelation00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_FindWarByAttackGuildID00
  tolua_function(tolua_S,"FindWarByAttackGuildID",tolua_guild_mgr_CGuildMgr_FindWarByAttackGuildID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_FindWarByDefendGuildID00
  tolua_function(tolua_S,"FindWarByDefendGuildID",tolua_guild_mgr_CGuildMgr_FindWarByDefendGuildID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_DelWarRelation00
  tolua_function(tolua_S,"DelWarRelation",tolua_guild_mgr_CGuildMgr_DelWarRelation00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_IsHostile00
  tolua_function(tolua_S,"IsHostile",tolua_guild_mgr_CGuildMgr_IsHostile00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_guild_mgr_CGuildMgr_IsFriendly00
  tolua_function(tolua_S,"IsFriendly",tolua_guild_mgr_CGuildMgr_IsFriendly00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
#ifndef TOLUA_DISABLE_tolua_guild_mgr_SendMSToAddRes00
 tolua_function(tolua_S,"SendMSToAddRes",tolua_guild_mgr_SendMSToAddRes00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_guild_mgr (lua_State* tolua_S) {
 return tolua_guild_mgr_open(tolua_S);
};
#endif

