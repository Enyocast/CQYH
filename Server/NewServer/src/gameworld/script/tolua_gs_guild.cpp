/*
** Lua binding: gs_guild
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:29.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_gs_guild_open (lua_State* tolua_S);

#include "../../inc/gameworld/gs_guild_data.h"
#include "../../inc/gameworld/role_guild_data.h"
#include "../../inc/gameworld/gs_guild.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"NAMEID");
 tolua_usertype(tolua_S,"CGSGuild");
 tolua_usertype(tolua_S,"CRoleGuildData");
 tolua_usertype(tolua_S,"GS_G_B_DATA");
 tolua_usertype(tolua_S,"GUILD_WAR_DATA");
 tolua_usertype(tolua_S,"GS_GUILD_MEMBER");
}

/* get function: dwIntruderID of class  GUILD_WAR_DATA */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_WAR_DATA_unsigned_dwIntruderID
static int tolua_get_GUILD_WAR_DATA_unsigned_dwIntruderID(lua_State* tolua_S)
{
  GUILD_WAR_DATA* self = (GUILD_WAR_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwIntruderID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwIntruderID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwIntruderID of class  GUILD_WAR_DATA */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_WAR_DATA_unsigned_dwIntruderID
static int tolua_set_GUILD_WAR_DATA_unsigned_dwIntruderID(lua_State* tolua_S)
{
  GUILD_WAR_DATA* self = (GUILD_WAR_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwIntruderID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwIntruderID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwDefenderID of class  GUILD_WAR_DATA */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_WAR_DATA_unsigned_dwDefenderID
static int tolua_get_GUILD_WAR_DATA_unsigned_dwDefenderID(lua_State* tolua_S)
{
  GUILD_WAR_DATA* self = (GUILD_WAR_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwDefenderID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwDefenderID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwDefenderID of class  GUILD_WAR_DATA */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_WAR_DATA_unsigned_dwDefenderID
static int tolua_set_GUILD_WAR_DATA_unsigned_dwDefenderID(lua_State* tolua_S)
{
  GUILD_WAR_DATA* self = (GUILD_WAR_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwDefenderID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwDefenderID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GS_G_B_DATA */
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_G_B_DATA_new00
static int tolua_gs_guild_GS_G_B_DATA_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"GS_G_B_DATA",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  GS_G_B_DATA* tolua_ret = (GS_G_B_DATA*)  Mtolua_new((GS_G_B_DATA)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_G_B_DATA");
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

/* method: new_local of class  GS_G_B_DATA */
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_G_B_DATA_new00_local
static int tolua_gs_guild_GS_G_B_DATA_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"GS_G_B_DATA",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  GS_G_B_DATA* tolua_ret = (GS_G_B_DATA*)  Mtolua_new((GS_G_B_DATA)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_G_B_DATA");
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

/* method: new of class  GS_G_B_DATA */
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_G_B_DATA_new01
static int tolua_gs_guild_GS_G_B_DATA_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"GS_G_B_DATA",0,&tolua_err) ||
 (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"NAMEID",0,&tolua_err)) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  NAMEID qwID = *((NAMEID*)  tolua_tousertype(tolua_S,2,0));
  signed int nT = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nL = (( signed int)  tolua_tonumber(tolua_S,4,0));
 {
  GS_G_B_DATA* tolua_ret = (GS_G_B_DATA*)  Mtolua_new((GS_G_B_DATA)(qwID,nT,nL));
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_G_B_DATA");
 }
 }
 return 1;
tolua_lerror:
 return tolua_gs_guild_GS_G_B_DATA_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GS_G_B_DATA */
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_G_B_DATA_new01_local
static int tolua_gs_guild_GS_G_B_DATA_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"GS_G_B_DATA",0,&tolua_err) ||
 (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"NAMEID",0,&tolua_err)) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  NAMEID qwID = *((NAMEID*)  tolua_tousertype(tolua_S,2,0));
  signed int nT = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nL = (( signed int)  tolua_tonumber(tolua_S,4,0));
 {
  GS_G_B_DATA* tolua_ret = (GS_G_B_DATA*)  Mtolua_new((GS_G_B_DATA)(qwID,nT,nL));
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_G_B_DATA");
 tolua_register_gc(tolua_S,lua_gettop(tolua_S));
 }
 }
 return 1;
tolua_lerror:
 return tolua_gs_guild_GS_G_B_DATA_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: qwNameID of class  GS_G_B_DATA */
#ifndef TOLUA_DISABLE_tolua_get_GS_G_B_DATA_qwNameID
static int tolua_get_GS_G_B_DATA_qwNameID(lua_State* tolua_S)
{
  GS_G_B_DATA* self = (GS_G_B_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'qwNameID'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->qwNameID,"NAMEID");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: qwNameID of class  GS_G_B_DATA */
#ifndef TOLUA_DISABLE_tolua_set_GS_G_B_DATA_qwNameID
static int tolua_set_GS_G_B_DATA_qwNameID(lua_State* tolua_S)
{
  GS_G_B_DATA* self = (GS_G_B_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'qwNameID'",NULL);
 if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"NAMEID",0,&tolua_err)))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->qwNameID = *((NAMEID*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nType of class  GS_G_B_DATA */
#ifndef TOLUA_DISABLE_tolua_get_GS_G_B_DATA_nType
static int tolua_get_GS_G_B_DATA_nType(lua_State* tolua_S)
{
  GS_G_B_DATA* self = (GS_G_B_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nType of class  GS_G_B_DATA */
#ifndef TOLUA_DISABLE_tolua_set_GS_G_B_DATA_nType
static int tolua_set_GS_G_B_DATA_nType(lua_State* tolua_S)
{
  GS_G_B_DATA* self = (GS_G_B_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nType = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nLevel of class  GS_G_B_DATA */
#ifndef TOLUA_DISABLE_tolua_get_GS_G_B_DATA_nLevel
static int tolua_get_GS_G_B_DATA_nLevel(lua_State* tolua_S)
{
  GS_G_B_DATA* self = (GS_G_B_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLevel'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nLevel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nLevel of class  GS_G_B_DATA */
#ifndef TOLUA_DISABLE_tolua_set_GS_G_B_DATA_nLevel
static int tolua_set_GS_G_B_DATA_nLevel(lua_State* tolua_S)
{
  GS_G_B_DATA* self = (GS_G_B_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLevel'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nLevel = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwReviveTime of class  GS_G_B_DATA */
#ifndef TOLUA_DISABLE_tolua_get_GS_G_B_DATA_unsigned_dwReviveTime
static int tolua_get_GS_G_B_DATA_unsigned_dwReviveTime(lua_State* tolua_S)
{
  GS_G_B_DATA* self = (GS_G_B_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwReviveTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwReviveTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwReviveTime of class  GS_G_B_DATA */
#ifndef TOLUA_DISABLE_tolua_set_GS_G_B_DATA_unsigned_dwReviveTime
static int tolua_set_GS_G_B_DATA_unsigned_dwReviveTime(lua_State* tolua_S)
{
  GS_G_B_DATA* self = (GS_G_B_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwReviveTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwReviveTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwRoleID of class  GS_GUILD_MEMBER */
#ifndef TOLUA_DISABLE_tolua_get_GS_GUILD_MEMBER_unsigned_dwRoleID
static int tolua_get_GS_GUILD_MEMBER_unsigned_dwRoleID(lua_State* tolua_S)
{
  GS_GUILD_MEMBER* self = (GS_GUILD_MEMBER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwRoleID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwRoleID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwRoleID of class  GS_GUILD_MEMBER */
#ifndef TOLUA_DISABLE_tolua_set_GS_GUILD_MEMBER_unsigned_dwRoleID
static int tolua_set_GS_GUILD_MEMBER_unsigned_dwRoleID(lua_State* tolua_S)
{
  GS_GUILD_MEMBER* self = (GS_GUILD_MEMBER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwRoleID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nPosition of class  GS_GUILD_MEMBER */
#ifndef TOLUA_DISABLE_tolua_get_GS_GUILD_MEMBER_nPosition
static int tolua_get_GS_GUILD_MEMBER_nPosition(lua_State* tolua_S)
{
  GS_GUILD_MEMBER* self = (GS_GUILD_MEMBER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nPosition'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nPosition);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nPosition of class  GS_GUILD_MEMBER */
#ifndef TOLUA_DISABLE_tolua_set_GS_GUILD_MEMBER_nPosition
static int tolua_set_GS_GUILD_MEMBER_nPosition(lua_State* tolua_S)
{
  GS_GUILD_MEMBER* self = (GS_GUILD_MEMBER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nPosition'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nPosition = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GS_GUILD_MEMBER */
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_GUILD_MEMBER_new00
static int tolua_gs_guild_GS_GUILD_MEMBER_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"GS_GUILD_MEMBER",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  GS_GUILD_MEMBER* tolua_ret = (GS_GUILD_MEMBER*)  Mtolua_new((GS_GUILD_MEMBER)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_GUILD_MEMBER");
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

/* method: new_local of class  GS_GUILD_MEMBER */
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_GUILD_MEMBER_new00_local
static int tolua_gs_guild_GS_GUILD_MEMBER_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"GS_GUILD_MEMBER",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  GS_GUILD_MEMBER* tolua_ret = (GS_GUILD_MEMBER*)  Mtolua_new((GS_GUILD_MEMBER)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_GUILD_MEMBER");
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

/* method: new of class  GS_GUILD_MEMBER */
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_GUILD_MEMBER_new01
static int tolua_gs_guild_GS_GUILD_MEMBER_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"GS_GUILD_MEMBER",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  unsigned int dwID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  signed int nP = (( signed int)  tolua_tonumber(tolua_S,3,0));
 {
  GS_GUILD_MEMBER* tolua_ret = (GS_GUILD_MEMBER*)  Mtolua_new((GS_GUILD_MEMBER)(dwID,nP));
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_GUILD_MEMBER");
 }
 }
 return 1;
tolua_lerror:
 return tolua_gs_guild_GS_GUILD_MEMBER_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GS_GUILD_MEMBER */
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_GUILD_MEMBER_new01_local
static int tolua_gs_guild_GS_GUILD_MEMBER_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"GS_GUILD_MEMBER",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  unsigned int dwID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  signed int nP = (( signed int)  tolua_tonumber(tolua_S,3,0));
 {
  GS_GUILD_MEMBER* tolua_ret = (GS_GUILD_MEMBER*)  Mtolua_new((GS_GUILD_MEMBER)(dwID,nP));
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_GUILD_MEMBER");
 tolua_register_gc(tolua_S,lua_gettop(tolua_S));
 }
 }
 return 1;
tolua_lerror:
 return tolua_gs_guild_GS_GUILD_MEMBER_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  GS_GUILD_MEMBER */
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_GUILD_MEMBER__eq00
static int tolua_gs_guild_GS_GUILD_MEMBER__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"GS_GUILD_MEMBER",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  GS_GUILD_MEMBER* self = (GS_GUILD_MEMBER*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
 {
 int tolua_ret = (int)
self->operator==(dwRoleID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CalculateFundLimit of class  CRoleGuildData */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CRoleGuildData_CalculateFundLimit00
static int tolua_gs_guild_CRoleGuildData_CalculateFundLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRoleGuildData",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRoleGuildData* self = (CRoleGuildData*)  tolua_tousertype(tolua_S,1,0);
  signed int nPosition = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nMoney = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CalculateFundLimit'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->CalculateFundLimit(nPosition,nMoney);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CalculateFundLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CalculateResLimit of class  CRoleGuildData */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CRoleGuildData_CalculateResLimit00
static int tolua_gs_guild_CRoleGuildData_CalculateResLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRoleGuildData",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRoleGuildData* self = (CRoleGuildData*)  tolua_tousertype(tolua_S,1,0);
  signed int nPosition = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nRes = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CalculateResLimit'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->CalculateResLimit(nPosition,nRes);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CalculateResLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetID of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetID00
static int tolua_gs_guild_CGSGuild_GetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetName of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetName00
static int tolua_gs_guild_CGSGuild_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetState of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetState00
static int tolua_gs_guild_CGSGuild_GetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetState'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetState();
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

/* method: SetState of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_SetState00
static int tolua_gs_guild_CGSGuild_SetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nState = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetState'", NULL);
#endif
 {
  self->SetState(nState);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLeaderID of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetLeaderID00
static int tolua_gs_guild_CGSGuild_GetLeaderID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLeaderID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetLeaderID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLeaderID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLeaderID of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_SetLeaderID00
static int tolua_gs_guild_CGSGuild_SetLeaderID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLeaderID'", NULL);
#endif
 {
  self->SetLeaderID(dwRoleID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLeaderID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMember of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetMember00
static int tolua_gs_guild_CGSGuild_GetMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMember'", NULL);
#endif
 {
  GS_GUILD_MEMBER* tolua_ret = (GS_GUILD_MEMBER*)  self->GetMember(dwRoleID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_GUILD_MEMBER");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMember'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxMemberCount of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetMaxMemberCount00
static int tolua_gs_guild_CGSGuild_GetMaxMemberCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxMemberCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMaxMemberCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxMemberCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddMember of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_AddMember00
static int tolua_gs_guild_CGSGuild_AddMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  signed int nPosition = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddMember'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddMember(dwRoleID,nPosition);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddMember'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelMember of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_DelMember00
static int tolua_gs_guild_CGSGuild_DelMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelMember'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DelMember(dwRoleID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelMember'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsMember of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_IsMember00
static int tolua_gs_guild_CGSGuild_IsMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsMember'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsMember(dwRoleID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsMember'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWelfareLevelByType of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetWelfareLevelByType00
static int tolua_gs_guild_CGSGuild_GetWelfareLevelByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWelfareLevelByType'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetWelfareLevelByType(nType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWelfareLevelByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWelfareLevelByType of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_SetWelfareLevelByType00
static int tolua_gs_guild_CGSGuild_SetWelfareLevelByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWelfareLevelByType'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetWelfareLevelByType(nType,nLevel);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWelfareLevelByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsActiveWelfareBuffer of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_IsActiveWelfareBuffer00
static int tolua_gs_guild_CGSGuild_IsActiveWelfareBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsActiveWelfareBuffer'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsActiveWelfareBuffer(nType);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsActiveWelfareBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBuildingMaxLevelByType of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetBuildingMaxLevelByType00
static int tolua_gs_guild_CGSGuild_GetBuildingMaxLevelByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBuildingMaxLevelByType'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetBuildingMaxLevelByType(nType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBuildingMaxLevelByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBuildingDataByNpcID of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetBuildingDataByNpcID00
static int tolua_gs_guild_CGSGuild_GetBuildingDataByNpcID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"NAMEID",0,&tolua_err)) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  NAMEID qwNpcNameID = *((NAMEID*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBuildingDataByNpcID'", NULL);
#endif
 {
  GS_G_B_DATA* tolua_ret = (GS_G_B_DATA*)  self->GetBuildingDataByNpcID(qwNpcNameID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_G_B_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBuildingDataByNpcID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFunBuildingDataByType of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetFunBuildingDataByType00
static int tolua_gs_guild_CGSGuild_GetFunBuildingDataByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFunBuildingDataByType'", NULL);
#endif
 {
  GS_G_B_DATA* tolua_ret = (GS_G_B_DATA*)  self->GetFunBuildingDataByType(nType);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_G_B_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFunBuildingDataByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FirstUnFunBuilding of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_FirstUnFunBuilding00
static int tolua_gs_guild_CGSGuild_FirstUnFunBuilding00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FirstUnFunBuilding'", NULL);
#endif
 {
  GS_G_B_DATA* tolua_ret = (GS_G_B_DATA*)  self->FirstUnFunBuilding();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_G_B_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FirstUnFunBuilding'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NextUnFunBuilding of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_NextUnFunBuilding00
static int tolua_gs_guild_CGSGuild_NextUnFunBuilding00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NextUnFunBuilding'", NULL);
#endif
 {
  GS_G_B_DATA* tolua_ret = (GS_G_B_DATA*)  self->NextUnFunBuilding();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_G_B_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NextUnFunBuilding'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FirstUpgradeBuilding of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_FirstUpgradeBuilding00
static int tolua_gs_guild_CGSGuild_FirstUpgradeBuilding00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FirstUpgradeBuilding'", NULL);
#endif
 {
  GS_G_B_DATA* tolua_ret = (GS_G_B_DATA*)  self->FirstUpgradeBuilding();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_G_B_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FirstUpgradeBuilding'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NextUpgradeBuilding of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_NextUpgradeBuilding00
static int tolua_gs_guild_CGSGuild_NextUpgradeBuilding00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NextUpgradeBuilding'", NULL);
#endif
 {
  GS_G_B_DATA* tolua_ret = (GS_G_B_DATA*)  self->NextUpgradeBuilding();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GS_G_B_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NextUpgradeBuilding'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBuildingEnable of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_IsBuildingEnable00
static int tolua_gs_guild_CGSGuild_IsBuildingEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"NAMEID",0,&tolua_err)) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  NAMEID qwNameID = *((NAMEID*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBuildingEnable'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsBuildingEnable(qwNameID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBuildingEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMoney of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetMoney00
static int tolua_gs_guild_CGSGuild_GetMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMoney'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMoney();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHerb of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetHerb00
static int tolua_gs_guild_CGSGuild_GetHerb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHerb'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetHerb();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHerb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWood of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetWood00
static int tolua_gs_guild_CGSGuild_GetWood00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWood'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetWood();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWood'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCrystal of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetCrystal00
static int tolua_gs_guild_CGSGuild_GetCrystal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCrystal'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetCrystal();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCrystal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSilver of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetSilver00
static int tolua_gs_guild_CGSGuild_GetSilver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSilver'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetSilver();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSilver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRes of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetRes00
static int tolua_gs_guild_CGSGuild_GetRes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nResType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRes'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetRes(nResType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxRes of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetMaxRes00
static int tolua_gs_guild_CGSGuild_GetMaxRes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nResType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxRes'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMaxRes(nResType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxRes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxStorage of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetMaxStorage00
static int tolua_gs_guild_CGSGuild_GetMaxStorage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxStorage'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMaxStorage(nType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxStorage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddAlliance of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_AddAlliance00
static int tolua_gs_guild_CGSGuild_AddAlliance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTargetID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddAlliance'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddAlliance(dwTargetID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddAlliance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelAlliance of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_DelAlliance00
static int tolua_gs_guild_CGSGuild_DelAlliance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTargetID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelAlliance'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DelAlliance(dwTargetID);
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

/* method: IsAlliance of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_IsAlliance00
static int tolua_gs_guild_CGSGuild_IsAlliance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTargetID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAlliance'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsAlliance(dwTargetID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAlliance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddEnemy of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_AddEnemy00
static int tolua_gs_guild_CGSGuild_AddEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTargetID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddEnemy'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddEnemy(dwTargetID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddEnemy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelEnemy of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_DelEnemy00
static int tolua_gs_guild_CGSGuild_DelEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTargetID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelEnemy'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DelEnemy(dwTargetID);
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

/* method: IsEnemy of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_IsEnemy00
static int tolua_gs_guild_CGSGuild_IsEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTargetID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsEnemy'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsEnemy(dwTargetID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsEnemy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVariable of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetVariable00
static int tolua_gs_guild_CGSGuild_GetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: IsActivityOpen of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_IsActivityOpen00
static int tolua_gs_guild_CGSGuild_IsActivityOpen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nActivityID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsActivityOpen'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsActivityOpen(nActivityID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsActivityOpen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetActivityMaxRepeatNum of class  CGSGuild */
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetActivityMaxRepeatNum00
static int tolua_gs_guild_CGSGuild_GetActivityMaxRepeatNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CGSGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CGSGuild* self = (CGSGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nActivityID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetActivityMaxRepeatNum'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetActivityMaxRepeatNum(nActivityID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetActivityMaxRepeatNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_gs_guild_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"GUILD_WAR_DATA","GUILD_WAR_DATA","",NULL);
 tolua_beginmodule(tolua_S,"GUILD_WAR_DATA");
  tolua_variable(tolua_S,"dwIntruderID",tolua_get_GUILD_WAR_DATA_unsigned_dwIntruderID,tolua_set_GUILD_WAR_DATA_unsigned_dwIntruderID);
  tolua_variable(tolua_S,"dwDefenderID",tolua_get_GUILD_WAR_DATA_unsigned_dwDefenderID,tolua_set_GUILD_WAR_DATA_unsigned_dwDefenderID);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"GS_G_B_DATA","GS_G_B_DATA","",NULL);
 tolua_beginmodule(tolua_S,"GS_G_B_DATA");
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_G_B_DATA_new00
  tolua_function(tolua_S,"new",tolua_gs_guild_GS_G_B_DATA_new00);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_gs_guild_GS_G_B_DATA_new00_local);
  tolua_function(tolua_S,".call",tolua_gs_guild_GS_G_B_DATA_new00_local);
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_G_B_DATA_new01
  tolua_function(tolua_S,"new",tolua_gs_guild_GS_G_B_DATA_new01);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_gs_guild_GS_G_B_DATA_new01_local);
  tolua_function(tolua_S,".call",tolua_gs_guild_GS_G_B_DATA_new01_local);
  tolua_variable(tolua_S,"qwNameID",tolua_get_GS_G_B_DATA_qwNameID,tolua_set_GS_G_B_DATA_qwNameID);
  tolua_variable(tolua_S,"nType",tolua_get_GS_G_B_DATA_nType,tolua_set_GS_G_B_DATA_nType);
  tolua_variable(tolua_S,"nLevel",tolua_get_GS_G_B_DATA_nLevel,tolua_set_GS_G_B_DATA_nLevel);
  tolua_variable(tolua_S,"dwReviveTime",tolua_get_GS_G_B_DATA_unsigned_dwReviveTime,tolua_set_GS_G_B_DATA_unsigned_dwReviveTime);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"GS_GUILD_MEMBER","GS_GUILD_MEMBER","",NULL);
 tolua_beginmodule(tolua_S,"GS_GUILD_MEMBER");
  tolua_variable(tolua_S,"dwRoleID",tolua_get_GS_GUILD_MEMBER_unsigned_dwRoleID,tolua_set_GS_GUILD_MEMBER_unsigned_dwRoleID);
  tolua_variable(tolua_S,"nPosition",tolua_get_GS_GUILD_MEMBER_nPosition,tolua_set_GS_GUILD_MEMBER_nPosition);
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_GUILD_MEMBER_new00
  tolua_function(tolua_S,"new",tolua_gs_guild_GS_GUILD_MEMBER_new00);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_gs_guild_GS_GUILD_MEMBER_new00_local);
  tolua_function(tolua_S,".call",tolua_gs_guild_GS_GUILD_MEMBER_new00_local);
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_GUILD_MEMBER_new01
  tolua_function(tolua_S,"new",tolua_gs_guild_GS_GUILD_MEMBER_new01);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_gs_guild_GS_GUILD_MEMBER_new01_local);
  tolua_function(tolua_S,".call",tolua_gs_guild_GS_GUILD_MEMBER_new01_local);
#ifndef TOLUA_DISABLE_tolua_gs_guild_GS_GUILD_MEMBER__eq00
  tolua_function(tolua_S,".eq",tolua_gs_guild_GS_GUILD_MEMBER__eq00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CRoleGuildData","CRoleGuildData","",NULL);
 tolua_beginmodule(tolua_S,"CRoleGuildData");
#ifndef TOLUA_DISABLE_tolua_gs_guild_CRoleGuildData_CalculateFundLimit00
  tolua_function(tolua_S,"CalculateFundLimit",tolua_gs_guild_CRoleGuildData_CalculateFundLimit00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CRoleGuildData_CalculateResLimit00
  tolua_function(tolua_S,"CalculateResLimit",tolua_gs_guild_CRoleGuildData_CalculateResLimit00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CGSGuild","CGSGuild","",NULL);
 tolua_beginmodule(tolua_S,"CGSGuild");
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetID00
  tolua_function(tolua_S,"GetID",tolua_gs_guild_CGSGuild_GetID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetName00
  tolua_function(tolua_S,"GetName",tolua_gs_guild_CGSGuild_GetName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetState00
  tolua_function(tolua_S,"GetState",tolua_gs_guild_CGSGuild_GetState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_SetState00
  tolua_function(tolua_S,"SetState",tolua_gs_guild_CGSGuild_SetState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetLeaderID00
  tolua_function(tolua_S,"GetLeaderID",tolua_gs_guild_CGSGuild_GetLeaderID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_SetLeaderID00
  tolua_function(tolua_S,"SetLeaderID",tolua_gs_guild_CGSGuild_SetLeaderID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetMember00
  tolua_function(tolua_S,"GetMember",tolua_gs_guild_CGSGuild_GetMember00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetMaxMemberCount00
  tolua_function(tolua_S,"GetMaxMemberCount",tolua_gs_guild_CGSGuild_GetMaxMemberCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_AddMember00
  tolua_function(tolua_S,"AddMember",tolua_gs_guild_CGSGuild_AddMember00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_DelMember00
  tolua_function(tolua_S,"DelMember",tolua_gs_guild_CGSGuild_DelMember00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_IsMember00
  tolua_function(tolua_S,"IsMember",tolua_gs_guild_CGSGuild_IsMember00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetWelfareLevelByType00
  tolua_function(tolua_S,"GetWelfareLevelByType",tolua_gs_guild_CGSGuild_GetWelfareLevelByType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_SetWelfareLevelByType00
  tolua_function(tolua_S,"SetWelfareLevelByType",tolua_gs_guild_CGSGuild_SetWelfareLevelByType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_IsActiveWelfareBuffer00
  tolua_function(tolua_S,"IsActiveWelfareBuffer",tolua_gs_guild_CGSGuild_IsActiveWelfareBuffer00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetBuildingMaxLevelByType00
  tolua_function(tolua_S,"GetBuildingMaxLevelByType",tolua_gs_guild_CGSGuild_GetBuildingMaxLevelByType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetBuildingDataByNpcID00
  tolua_function(tolua_S,"GetBuildingDataByNpcID",tolua_gs_guild_CGSGuild_GetBuildingDataByNpcID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetFunBuildingDataByType00
  tolua_function(tolua_S,"GetFunBuildingDataByType",tolua_gs_guild_CGSGuild_GetFunBuildingDataByType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_FirstUnFunBuilding00
  tolua_function(tolua_S,"FirstUnFunBuilding",tolua_gs_guild_CGSGuild_FirstUnFunBuilding00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_NextUnFunBuilding00
  tolua_function(tolua_S,"NextUnFunBuilding",tolua_gs_guild_CGSGuild_NextUnFunBuilding00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_FirstUpgradeBuilding00
  tolua_function(tolua_S,"FirstUpgradeBuilding",tolua_gs_guild_CGSGuild_FirstUpgradeBuilding00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_NextUpgradeBuilding00
  tolua_function(tolua_S,"NextUpgradeBuilding",tolua_gs_guild_CGSGuild_NextUpgradeBuilding00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_IsBuildingEnable00
  tolua_function(tolua_S,"IsBuildingEnable",tolua_gs_guild_CGSGuild_IsBuildingEnable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetMoney00
  tolua_function(tolua_S,"GetMoney",tolua_gs_guild_CGSGuild_GetMoney00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetHerb00
  tolua_function(tolua_S,"GetHerb",tolua_gs_guild_CGSGuild_GetHerb00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetWood00
  tolua_function(tolua_S,"GetWood",tolua_gs_guild_CGSGuild_GetWood00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetCrystal00
  tolua_function(tolua_S,"GetCrystal",tolua_gs_guild_CGSGuild_GetCrystal00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetSilver00
  tolua_function(tolua_S,"GetSilver",tolua_gs_guild_CGSGuild_GetSilver00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetRes00
  tolua_function(tolua_S,"GetRes",tolua_gs_guild_CGSGuild_GetRes00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetMaxRes00
  tolua_function(tolua_S,"GetMaxRes",tolua_gs_guild_CGSGuild_GetMaxRes00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetMaxStorage00
  tolua_function(tolua_S,"GetMaxStorage",tolua_gs_guild_CGSGuild_GetMaxStorage00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_AddAlliance00
  tolua_function(tolua_S,"AddAlliance",tolua_gs_guild_CGSGuild_AddAlliance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_DelAlliance00
  tolua_function(tolua_S,"DelAlliance",tolua_gs_guild_CGSGuild_DelAlliance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_IsAlliance00
  tolua_function(tolua_S,"IsAlliance",tolua_gs_guild_CGSGuild_IsAlliance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_AddEnemy00
  tolua_function(tolua_S,"AddEnemy",tolua_gs_guild_CGSGuild_AddEnemy00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_DelEnemy00
  tolua_function(tolua_S,"DelEnemy",tolua_gs_guild_CGSGuild_DelEnemy00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_IsEnemy00
  tolua_function(tolua_S,"IsEnemy",tolua_gs_guild_CGSGuild_IsEnemy00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetVariable00
  tolua_function(tolua_S,"GetVariable",tolua_gs_guild_CGSGuild_GetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_IsActivityOpen00
  tolua_function(tolua_S,"IsActivityOpen",tolua_gs_guild_CGSGuild_IsActivityOpen00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_guild_CGSGuild_GetActivityMaxRepeatNum00
  tolua_function(tolua_S,"GetActivityMaxRepeatNum",tolua_gs_guild_CGSGuild_GetActivityMaxRepeatNum00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_gs_guild (lua_State* tolua_S) {
 return tolua_gs_guild_open(tolua_S);
};
#endif

