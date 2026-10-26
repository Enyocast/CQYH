/*
** Lua binding: gs_team
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:29.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_gs_team_open (lua_State* tolua_S);

#include "../../../Common/define/team_def.h"
#include "../../inc/gameworld/team.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CTeamInGS");
 tolua_usertype(tolua_S,"TeamMember");
}

/* get function: szRoleName of class  TeamMember */
#ifndef TOLUA_DISABLE_tolua_get_TeamMember_szRoleName
static int tolua_get_TeamMember_szRoleName(lua_State* tolua_S)
{
  TeamMember* self = (TeamMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szRoleName'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szRoleName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szRoleName of class  TeamMember */
#ifndef TOLUA_DISABLE_tolua_set_TeamMember_szRoleName
static int tolua_set_TeamMember_szRoleName(lua_State* tolua_S)
{
  TeamMember* self = (TeamMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szRoleName'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szRoleName,(const char*)tolua_tostring(tolua_S,2,0),ROLE_NAME_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwRoleID of class  TeamMember */
#ifndef TOLUA_DISABLE_tolua_get_TeamMember_unsigned_dwRoleID
static int tolua_get_TeamMember_unsigned_dwRoleID(lua_State* tolua_S)
{
  TeamMember* self = (TeamMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwRoleID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwRoleID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwRoleID of class  TeamMember */
#ifndef TOLUA_DISABLE_tolua_set_TeamMember_unsigned_dwRoleID
static int tolua_set_TeamMember_unsigned_dwRoleID(lua_State* tolua_S)
{
  TeamMember* self = (TeamMember*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nLevel of class  TeamMember */
#ifndef TOLUA_DISABLE_tolua_get_TeamMember_nLevel
static int tolua_get_TeamMember_nLevel(lua_State* tolua_S)
{
  TeamMember* self = (TeamMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLevel'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nLevel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nLevel of class  TeamMember */
#ifndef TOLUA_DISABLE_tolua_set_TeamMember_nLevel
static int tolua_set_TeamMember_nLevel(lua_State* tolua_S)
{
  TeamMember* self = (TeamMember*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nSex of class  TeamMember */
#ifndef TOLUA_DISABLE_tolua_get_TeamMember_nSex
static int tolua_get_TeamMember_nSex(lua_State* tolua_S)
{
  TeamMember* self = (TeamMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSex'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSex of class  TeamMember */
#ifndef TOLUA_DISABLE_tolua_set_TeamMember_nSex
static int tolua_set_TeamMember_nSex(lua_State* tolua_S)
{
  TeamMember* self = (TeamMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSex'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSex = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nClass of class  TeamMember */
#ifndef TOLUA_DISABLE_tolua_get_TeamMember_nClass
static int tolua_get_TeamMember_nClass(lua_State* tolua_S)
{
  TeamMember* self = (TeamMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nClass'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nClass);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nClass of class  TeamMember */
#ifndef TOLUA_DISABLE_tolua_set_TeamMember_nClass
static int tolua_set_TeamMember_nClass(lua_State* tolua_S)
{
  TeamMember* self = (TeamMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nClass'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nClass = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLeaderID of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetLeaderID00
static int tolua_gs_team_CTeamInGS_GetLeaderID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetLeaderID of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetLeaderID00
static int tolua_gs_team_CTeamInGS_SetLeaderID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwLeaderID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLeaderID'", NULL);
#endif
 {
  self->SetLeaderID(dwLeaderID);
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

/* method: GetActivityType of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetActivityType00
static int tolua_gs_team_CTeamInGS_GetActivityType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetActivityType'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetActivityType();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetActivityType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetActivityType of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetActivityType00
static int tolua_gs_team_CTeamInGS_SetActivityType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwActivityType = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetActivityType'", NULL);
#endif
 {
  self->SetActivityType(dwActivityType);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetActivityType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetActivityID of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetActivityID00
static int tolua_gs_team_CTeamInGS_GetActivityID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetActivityID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetActivityID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetActivityID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetActivityID of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetActivityID00
static int tolua_gs_team_CTeamInGS_SetActivityID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwActivityID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetActivityID'", NULL);
#endif
 {
  self->SetActivityID(dwActivityID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetActivityID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAuctionItemColorLimit of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetAuctionItemColorLimit00
static int tolua_gs_team_CTeamInGS_GetAuctionItemColorLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAuctionItemColorLimit'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetAuctionItemColorLimit();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAuctionItemColorLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAuctionItemColorLimit of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetAuctionItemColorLimit00
static int tolua_gs_team_CTeamInGS_SetAuctionItemColorLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
  signed int nAuctionItemColorLimit = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAuctionItemColorLimit'", NULL);
#endif
 {
  self->SetAuctionItemColorLimit(nAuctionItemColorLimit);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAuctionItemColorLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTeamName of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetTeamName00
static int tolua_gs_team_CTeamInGS_GetTeamName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTeamName'", NULL);
#endif
 {
  char* tolua_ret = (char*)  self->GetTeamName();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTeamName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddNewMember of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_AddNewMember00
static int tolua_gs_team_CTeamInGS_AddNewMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwMemberID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  char* szRoleName = ((char*)  tolua_tostring(tolua_S,3,0));
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,4,0));
  signed int nSex = (( signed int)  tolua_tonumber(tolua_S,5,0));
  signed int nClass = (( signed int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddNewMember'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddNewMember(dwMemberID,szRoleName,nLevel,nSex,nClass);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddNewMember'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveMember of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_RemoveMember00
static int tolua_gs_team_CTeamInGS_RemoveMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwMemberID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveMember'", NULL);
#endif
 {
 int tolua_ret = (int)
self->RemoveMember(dwMemberID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveMember'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxMemberCount of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetMaxMemberCount00
static int tolua_gs_team_CTeamInGS_GetMaxMemberCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxMemberCount'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetMaxMemberCount();
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

/* method: SetMaxMemberCount of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetMaxMemberCount00
static int tolua_gs_team_CTeamInGS_SetMaxMemberCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwMaxMemberCount = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxMemberCount'", NULL);
#endif
 {
  self->SetMaxMemberCount(dwMaxMemberCount);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxMemberCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMemberCount of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetMemberCount00
static int tolua_gs_team_CTeamInGS_GetMemberCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMemberCount'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetMemberCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMemberCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMemberCount of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetMemberCount00
static int tolua_gs_team_CTeamInGS_SetMemberCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwMemberCount = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMemberCount'", NULL);
#endif
 {
  self->SetMemberCount(dwMemberCount);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMemberCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCreateTime of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetCreateTime00
static int tolua_gs_team_CTeamInGS_GetCreateTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCreateTime'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetCreateTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCreateTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCreateTime of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetCreateTime00
static int tolua_gs_team_CTeamInGS_SetCreateTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwCreateTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCreateTime'", NULL);
#endif
 {
  self->SetCreateTime(dwCreateTime);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCreateTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMemberTable of class  CTeamInGS */
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetMemberTable00
static int tolua_gs_team_CTeamInGS_GetMemberTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTeamInGS",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTeamInGS* self = (CTeamInGS*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMemberTable'", NULL);
#endif
 {
  TeamMember& tolua_ret = (TeamMember&)  self->GetMemberTable(nIndex);
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"TeamMember");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMemberTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_gs_team_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_TEAM_MEMBER_COUNT",MAX_TEAM_MEMBER_COUNT);
 tolua_constant(tolua_S,"MAX_ADJACENT_ROLE_NOTEAM_COUNT",MAX_ADJACENT_ROLE_NOTEAM_COUNT);
 tolua_constant(tolua_S,"MAX_ADJACENT_TEAM_COUNT",MAX_ADJACENT_TEAM_COUNT);
 tolua_constant(tolua_S,"TEAM_SYNC_MEMBERINFO_TO_MS",TEAM_SYNC_MEMBERINFO_TO_MS);
 tolua_constant(tolua_S,"TEAM_SYNC_MEMBERINFO_TO_CLIENT",TEAM_SYNC_MEMBERINFO_TO_CLIENT);
 tolua_constant(tolua_S,"TEAM_SYNC_MEMBERINFO_STOP",TEAM_SYNC_MEMBERINFO_STOP);
 tolua_constant(tolua_S,"MAX_TEAM_COUNT_PER_PAGE",MAX_TEAM_COUNT_PER_PAGE);
 tolua_constant(tolua_S,"MAX_TEAM_PAGE_COUNT",MAX_TEAM_PAGE_COUNT);
 tolua_constant(tolua_S,"MAX_TEAM_COUNT_PER_ACTIVITY",MAX_TEAM_COUNT_PER_ACTIVITY);
 tolua_constant(tolua_S,"MAX_TEAM_ACTIVITY",MAX_TEAM_ACTIVITY);
 tolua_constant(tolua_S,"MAX_TEAM_DUNGEON",MAX_TEAM_DUNGEON);
 tolua_constant(tolua_S,"TEAM_AUCTION_BID_FRAME_INTERVAL",TEAM_AUCTION_BID_FRAME_INTERVAL);
 tolua_constant(tolua_S,"TEAM_AUCTION_ITEM_INIT_INDEX",TEAM_AUCTION_ITEM_INIT_INDEX);
  tolua_constant(tolua_S,"etatInvite",etatInvite);
  tolua_constant(tolua_S,"etatEnter",etatEnter);
  tolua_constant(tolua_S,"etarAgree",etarAgree);
  tolua_constant(tolua_S,"etarDisAgree",etarDisAgree);
  tolua_constant(tolua_S,"etaInvalid",etaInvalid);
  tolua_constant(tolua_S,"etaFreeForAll",etaFreeForAll);
  tolua_constant(tolua_S,"etaTeamAuction",etaTeamAuction);
  tolua_constant(tolua_S,"etaLeaderPick",etaLeaderPick);
  tolua_constant(tolua_S,"etaTotal",etaTotal);
  tolua_constant(tolua_S,"etsOnline",etsOnline);
  tolua_constant(tolua_S,"etsOffline",etsOffline);
  tolua_constant(tolua_S,"etaatInvalid",etaatInvalid);
  tolua_constant(tolua_S,"etaatActivity",etaatActivity);
  tolua_constant(tolua_S,"etaatDungeon",etaatDungeon);
  tolua_constant(tolua_S,"etaatTotal",etaatTotal);
  tolua_constant(tolua_S,"etbsInvalid",etbsInvalid);
  tolua_constant(tolua_S,"etbsBidding",etbsBidding);
  tolua_constant(tolua_S,"etbsAbandon",etbsAbandon);
  tolua_constant(tolua_S,"etbsTotal",etbsTotal);
  tolua_constant(tolua_S,"TAA_ADDITEM",TAA_ADDITEM);
  tolua_constant(tolua_S,"TAA_START_AUCTION",TAA_START_AUCTION);
  tolua_constant(tolua_S,"TAA_BID",TAA_BID);
  tolua_constant(tolua_S,"TAA_ABANDON_SELF_REQUEST",TAA_ABANDON_SELF_REQUEST);
  tolua_constant(tolua_S,"TAA_ABANDON_LEAVE_SCENE",TAA_ABANDON_LEAVE_SCENE);
  tolua_constant(tolua_S,"TAA_REWARD_MONEY",TAA_REWARD_MONEY);
  tolua_constant(tolua_S,"TAA_WIN_ITEM",TAA_WIN_ITEM);
  tolua_constant(tolua_S,"TAA_LEADER_GOT_ITEM",TAA_LEADER_GOT_ITEM);
  tolua_constant(tolua_S,"TAA_RETURN_DEPOSIT",TAA_RETURN_DEPOSIT);
  tolua_constant(tolua_S,"TAA_FINISH_AUCTION",TAA_FINISH_AUCTION);
  tolua_constant(tolua_S,"TAA_TOTAL",TAA_TOTAL);
  tolua_constant(tolua_S,"TAMR_NO_CHANGE",TAMR_NO_CHANGE);
  tolua_constant(tolua_S,"TAMR_OFFER_PRICE",TAMR_OFFER_PRICE);
  tolua_constant(tolua_S,"TAMR_ABANDON",TAMR_ABANDON);
  tolua_constant(tolua_S,"TAMR_REWARD",TAMR_REWARD);
  tolua_constant(tolua_S,"TAMR_RETURN_DEPOSITE",TAMR_RETURN_DEPOSITE);
 tolua_cclass(tolua_S,"TeamMember","TeamMember","",NULL);
 tolua_beginmodule(tolua_S,"TeamMember");
  tolua_variable(tolua_S,"szRoleName",tolua_get_TeamMember_szRoleName,tolua_set_TeamMember_szRoleName);
  tolua_variable(tolua_S,"dwRoleID",tolua_get_TeamMember_unsigned_dwRoleID,tolua_set_TeamMember_unsigned_dwRoleID);
  tolua_variable(tolua_S,"nLevel",tolua_get_TeamMember_nLevel,tolua_set_TeamMember_nLevel);
  tolua_variable(tolua_S,"nSex",tolua_get_TeamMember_nSex,tolua_set_TeamMember_nSex);
  tolua_variable(tolua_S,"nClass",tolua_get_TeamMember_nClass,tolua_set_TeamMember_nClass);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CTeamInGS","CTeamInGS","",NULL);
 tolua_beginmodule(tolua_S,"CTeamInGS");
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetLeaderID00
  tolua_function(tolua_S,"GetLeaderID",tolua_gs_team_CTeamInGS_GetLeaderID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetLeaderID00
  tolua_function(tolua_S,"SetLeaderID",tolua_gs_team_CTeamInGS_SetLeaderID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetActivityType00
  tolua_function(tolua_S,"GetActivityType",tolua_gs_team_CTeamInGS_GetActivityType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetActivityType00
  tolua_function(tolua_S,"SetActivityType",tolua_gs_team_CTeamInGS_SetActivityType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetActivityID00
  tolua_function(tolua_S,"GetActivityID",tolua_gs_team_CTeamInGS_GetActivityID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetActivityID00
  tolua_function(tolua_S,"SetActivityID",tolua_gs_team_CTeamInGS_SetActivityID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetAuctionItemColorLimit00
  tolua_function(tolua_S,"GetAuctionItemColorLimit",tolua_gs_team_CTeamInGS_GetAuctionItemColorLimit00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetAuctionItemColorLimit00
  tolua_function(tolua_S,"SetAuctionItemColorLimit",tolua_gs_team_CTeamInGS_SetAuctionItemColorLimit00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetTeamName00
  tolua_function(tolua_S,"GetTeamName",tolua_gs_team_CTeamInGS_GetTeamName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_AddNewMember00
  tolua_function(tolua_S,"AddNewMember",tolua_gs_team_CTeamInGS_AddNewMember00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_RemoveMember00
  tolua_function(tolua_S,"RemoveMember",tolua_gs_team_CTeamInGS_RemoveMember00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetMaxMemberCount00
  tolua_function(tolua_S,"GetMaxMemberCount",tolua_gs_team_CTeamInGS_GetMaxMemberCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetMaxMemberCount00
  tolua_function(tolua_S,"SetMaxMemberCount",tolua_gs_team_CTeamInGS_SetMaxMemberCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetMemberCount00
  tolua_function(tolua_S,"GetMemberCount",tolua_gs_team_CTeamInGS_GetMemberCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetMemberCount00
  tolua_function(tolua_S,"SetMemberCount",tolua_gs_team_CTeamInGS_SetMemberCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetCreateTime00
  tolua_function(tolua_S,"GetCreateTime",tolua_gs_team_CTeamInGS_GetCreateTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_SetCreateTime00
  tolua_function(tolua_S,"SetCreateTime",tolua_gs_team_CTeamInGS_SetCreateTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_gs_team_CTeamInGS_GetMemberTable00
  tolua_function(tolua_S,"GetMemberTable",tolua_gs_team_CTeamInGS_GetMemberTable00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_gs_team (lua_State* tolua_S) {
 return tolua_gs_team_open(tolua_S);
};
#endif

