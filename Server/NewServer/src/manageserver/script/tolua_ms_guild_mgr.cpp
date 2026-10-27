/*
** Lua binding: ms_guild_mgr
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_ms_guild_mgr_open (lua_State* tolua_S);

#include "./guild/ms_guild_mgr.h"
#include "./guild/ms_guild.h"
#include "./guild/ms_guild_mgr.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"MS_GUILD_WAR_DATA");
 tolua_usertype(tolua_S,"CMsGuildMgr");
 tolua_usertype(tolua_S,"MS_ONLINE_ROLE_DATA");
 tolua_usertype(tolua_S,"CMsGuild");
}

/* method: GetInstance of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_GetInstance00
static int tolua_ms_guild_mgr_CMsGuildMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CMsGuildMgr& tolua_ret = (CMsGuildMgr&)  CMsGuildMgr::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CMsGuildMgr");
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

/* method: PreCreateGuild of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_PreCreateGuild00
static int tolua_ms_guild_mgr_CMsGuildMgr_PreCreateGuild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"MS_ONLINE_ROLE_DATA",0,&tolua_err)) ||
 !tolua_isstring(tolua_S,4,0,&tolua_err) ||
 !tolua_isstring(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwNewGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  MS_ONLINE_ROLE_DATA* onlineRoleData = ((MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,3,0));
  const char* pcszGuildName = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* pcszAnnounce = ((const char*)  tolua_tostring(tolua_S,5,0));
  signed int nIsNeedToConsume = (( signed int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PreCreateGuild'", NULL);
#endif
 {
 int tolua_ret = (int)
self->PreCreateGuild(dwNewGuildID,*onlineRoleData,pcszGuildName,pcszAnnounce,nIsNeedToConsume);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PreCreateGuild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindGuildByID of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_FindGuildByID00
static int tolua_ms_guild_mgr_CMsGuildMgr_FindGuildByID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindGuildByID'", NULL);
#endif
 {
  CMsGuild* tolua_ret = (CMsGuild*)  self->FindGuildByID(dwGuildID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMsGuild");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindGuildByID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindGuildByName of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_FindGuildByName00
static int tolua_ms_guild_mgr_CMsGuildMgr_FindGuildByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* pcszGuildName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindGuildByName'", NULL);
#endif
 {
  CMsGuild* tolua_ret = (CMsGuild*)  self->FindGuildByName(pcszGuildName);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMsGuild");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindGuildByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InsertGuildIntoLvlRank of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_InsertGuildIntoLvlRank00
static int tolua_ms_guild_mgr_CMsGuildMgr_InsertGuildIntoLvlRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  CMsGuild* pMsGuild = ((CMsGuild*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InsertGuildIntoLvlRank'", NULL);
#endif
 {
 int tolua_ret = (int)
self->InsertGuildIntoLvlRank(pMsGuild);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InsertGuildIntoLvlRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveGuildFromLvlRank of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_RemoveGuildFromLvlRank00
static int tolua_ms_guild_mgr_CMsGuildMgr_RemoveGuildFromLvlRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  CMsGuild* pMsGuild = ((CMsGuild*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveGuildFromLvlRank'", NULL);
#endif
 {
 int tolua_ret = (int)
self->RemoveGuildFromLvlRank(pMsGuild);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveGuildFromLvlRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DestroyGuild of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_DestroyGuild00
static int tolua_ms_guild_mgr_CMsGuildMgr_DestroyGuild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  CMsGuild* pMsGuild = ((CMsGuild*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DestroyGuild'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DestroyGuild(pMsGuild);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DestroyGuild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearWarData of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_ClearWarData00
static int tolua_ms_guild_mgr_CMsGuildMgr_ClearWarData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearWarData'", NULL);
#endif
 {
 int tolua_ret = (int)
self->ClearWarData();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearWarData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FirstWarData of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_FirstWarData00
static int tolua_ms_guild_mgr_CMsGuildMgr_FirstWarData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FirstWarData'", NULL);
#endif
 {
  MS_GUILD_WAR_DATA* tolua_ret = (MS_GUILD_WAR_DATA*)  self->FirstWarData();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"MS_GUILD_WAR_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FirstWarData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NextWarData of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_NextWarData00
static int tolua_ms_guild_mgr_CMsGuildMgr_NextWarData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NextWarData'", NULL);
#endif
 {
  MS_GUILD_WAR_DATA* tolua_ret = (MS_GUILD_WAR_DATA*)  self->NextWarData();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"MS_GUILD_WAR_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NextWarData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFirstGuildOnLvlRank of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_GetFirstGuildOnLvlRank00
static int tolua_ms_guild_mgr_CMsGuildMgr_GetFirstGuildOnLvlRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFirstGuildOnLvlRank'", NULL);
#endif
 {
  CMsGuild* tolua_ret = (CMsGuild*)  self->GetFirstGuildOnLvlRank();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMsGuild");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFirstGuildOnLvlRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNextGuildOnLvlRank of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_GetNextGuildOnLvlRank00
static int tolua_ms_guild_mgr_CMsGuildMgr_GetNextGuildOnLvlRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  CMsGuild* pMsGuild = ((CMsGuild*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNextGuildOnLvlRank'", NULL);
#endif
 {
  CMsGuild* tolua_ret = (CMsGuild*)  self->GetNextGuildOnLvlRank(pMsGuild);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMsGuild");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNextGuildOnLvlRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPrevGuildOnLvlRank of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_GetPrevGuildOnLvlRank00
static int tolua_ms_guild_mgr_CMsGuildMgr_GetPrevGuildOnLvlRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  CMsGuild* pMsGuild = ((CMsGuild*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPrevGuildOnLvlRank'", NULL);
#endif
 {
  CMsGuild* tolua_ret = (CMsGuild*)  self->GetPrevGuildOnLvlRank(pMsGuild);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMsGuild");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPrevGuildOnLvlRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelAlliance of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_DelAlliance00
static int tolua_ms_guild_mgr_CMsGuildMgr_DelAlliance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  signed int dwGuildID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int dwAllianceID = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelAlliance'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DelAlliance(dwGuildID,dwAllianceID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelAlliance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelEnemy of class  CMsGuildMgr */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_DelEnemy00
static int tolua_ms_guild_mgr_CMsGuildMgr_DelEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMgr* self = (CMsGuildMgr*)  tolua_tousertype(tolua_S,1,0);
  signed int dwGuildID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int dwEnemyID = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelEnemy'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DelEnemy(dwGuildID,dwEnemyID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelEnemy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GuildWarEnd */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_GuildWarEnd00
static int tolua_ms_guild_mgr_GuildWarEnd00(lua_State* tolua_S)
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
  unsigned int dwDefenderID = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
  signed int nWarDefenderResult = (( signed int)  tolua_tonumber(tolua_S,2,0));
 {
 int tolua_ret = (int)
GuildWarEnd(dwDefenderID,nWarDefenderResult);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GuildWarEnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GuildSyncWarRelation */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_GuildSyncWarRelation00
static int tolua_ms_guild_mgr_GuildSyncWarRelation00(lua_State* tolua_S)
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
  unsigned int dwIntruderID = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int dwDefenderID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 {
 int tolua_ret = (int)
GuildSyncWarRelation(dwIntruderID,dwDefenderID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GuildSyncWarRelation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GuildSyncResChange */
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_GuildSyncResChange00
static int tolua_ms_guild_mgr_GuildSyncResChange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int dwNpcID = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
   bool bAdd = ((  bool)  tolua_toboolean(tolua_S,3,0));
  signed int nResType = (( signed int)  tolua_tonumber(tolua_S,4,0));
  signed int nChangeCount = (( signed int)  tolua_tonumber(tolua_S,5,0));
  signed int nCtxType = (( signed int)  tolua_tonumber(tolua_S,6,0));
 {
 int tolua_ret = (int)
GuildSyncResChange(dwNpcID,dwGuildID,bAdd,nResType,nChangeCount,nCtxType);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GuildSyncResChange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ms_guild_mgr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CMsGuildMgr","CMsGuildMgr","",NULL);
 tolua_beginmodule(tolua_S,"CMsGuildMgr");
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_ms_guild_mgr_CMsGuildMgr_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_PreCreateGuild00
  tolua_function(tolua_S,"PreCreateGuild",tolua_ms_guild_mgr_CMsGuildMgr_PreCreateGuild00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_FindGuildByID00
  tolua_function(tolua_S,"FindGuildByID",tolua_ms_guild_mgr_CMsGuildMgr_FindGuildByID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_FindGuildByName00
  tolua_function(tolua_S,"FindGuildByName",tolua_ms_guild_mgr_CMsGuildMgr_FindGuildByName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_InsertGuildIntoLvlRank00
  tolua_function(tolua_S,"InsertGuildIntoLvlRank",tolua_ms_guild_mgr_CMsGuildMgr_InsertGuildIntoLvlRank00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_RemoveGuildFromLvlRank00
  tolua_function(tolua_S,"RemoveGuildFromLvlRank",tolua_ms_guild_mgr_CMsGuildMgr_RemoveGuildFromLvlRank00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_DestroyGuild00
  tolua_function(tolua_S,"DestroyGuild",tolua_ms_guild_mgr_CMsGuildMgr_DestroyGuild00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_ClearWarData00
  tolua_function(tolua_S,"ClearWarData",tolua_ms_guild_mgr_CMsGuildMgr_ClearWarData00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_FirstWarData00
  tolua_function(tolua_S,"FirstWarData",tolua_ms_guild_mgr_CMsGuildMgr_FirstWarData00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_NextWarData00
  tolua_function(tolua_S,"NextWarData",tolua_ms_guild_mgr_CMsGuildMgr_NextWarData00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_GetFirstGuildOnLvlRank00
  tolua_function(tolua_S,"GetFirstGuildOnLvlRank",tolua_ms_guild_mgr_CMsGuildMgr_GetFirstGuildOnLvlRank00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_GetNextGuildOnLvlRank00
  tolua_function(tolua_S,"GetNextGuildOnLvlRank",tolua_ms_guild_mgr_CMsGuildMgr_GetNextGuildOnLvlRank00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_GetPrevGuildOnLvlRank00
  tolua_function(tolua_S,"GetPrevGuildOnLvlRank",tolua_ms_guild_mgr_CMsGuildMgr_GetPrevGuildOnLvlRank00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_DelAlliance00
  tolua_function(tolua_S,"DelAlliance",tolua_ms_guild_mgr_CMsGuildMgr_DelAlliance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_CMsGuildMgr_DelEnemy00
  tolua_function(tolua_S,"DelEnemy",tolua_ms_guild_mgr_CMsGuildMgr_DelEnemy00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_GuildWarEnd00
 tolua_function(tolua_S,"GuildWarEnd",tolua_ms_guild_mgr_GuildWarEnd00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_GuildSyncWarRelation00
 tolua_function(tolua_S,"GuildSyncWarRelation",tolua_ms_guild_mgr_GuildSyncWarRelation00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_mgr_GuildSyncResChange00
 tolua_function(tolua_S,"GuildSyncResChange",tolua_ms_guild_mgr_GuildSyncResChange00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ms_guild_mgr (lua_State* tolua_S) {
 return tolua_ms_guild_mgr_open(tolua_S);
};
#endif

