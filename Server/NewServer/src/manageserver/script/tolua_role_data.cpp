/*
** Lua binding: role_data
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_role_data_open (lua_State* tolua_S);

#include "role_data.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CBaseList");
 tolua_usertype(tolua_S,"MS_ROLE_DATA");
}

/* get function: dwRoleID of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_unsigned_dwRoleID
static int tolua_get_MS_ROLE_DATA_unsigned_dwRoleID(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwRoleID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwRoleID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwRoleID of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_unsigned_dwRoleID
static int tolua_set_MS_ROLE_DATA_unsigned_dwRoleID(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: szRoleName of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_role_data_MS_ROLE_DATA_szRoleName
static int tolua_get_role_data_MS_ROLE_DATA_szRoleName(lua_State* tolua_S)
{
 int tolua_index;
  MS_ROLE_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (MS_ROLE_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=ROLE_NAME_LEN)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->szRoleName[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szRoleName of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_role_data_MS_ROLE_DATA_szRoleName
static int tolua_set_role_data_MS_ROLE_DATA_szRoleName(lua_State* tolua_S)
{
 int tolua_index;
  MS_ROLE_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (MS_ROLE_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=ROLE_NAME_LEN)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->szRoleName[tolua_index] = ((  char)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byGroup of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_unsigned_byGroup
static int tolua_get_MS_ROLE_DATA_unsigned_byGroup(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byGroup'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byGroup);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byGroup of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_unsigned_byGroup
static int tolua_set_MS_ROLE_DATA_unsigned_byGroup(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byGroup'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byGroup = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byLevel of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_unsigned_byLevel
static int tolua_get_MS_ROLE_DATA_unsigned_byLevel(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevel'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byLevel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byLevel of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_unsigned_byLevel
static int tolua_set_MS_ROLE_DATA_unsigned_byLevel(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevel'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byLevel = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bySex of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_unsigned_bySex
static int tolua_get_MS_ROLE_DATA_unsigned_bySex(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bySex'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->bySex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bySex of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_unsigned_bySex
static int tolua_set_MS_ROLE_DATA_unsigned_bySex(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bySex'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bySex = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byClass of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_unsigned_byClass
static int tolua_get_MS_ROLE_DATA_unsigned_byClass(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byClass'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byClass);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byClass of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_unsigned_byClass
static int tolua_set_MS_ROLE_DATA_unsigned_byClass(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byClass'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byClass = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nLastLoginTime of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_nLastLoginTime
static int tolua_get_MS_ROLE_DATA_nLastLoginTime(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLastLoginTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nLastLoginTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nLastLoginTime of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_nLastLoginTime
static int tolua_set_MS_ROLE_DATA_nLastLoginTime(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLastLoginTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nLastLoginTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSceneTempID of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_nSceneTempID
static int tolua_get_MS_ROLE_DATA_nSceneTempID(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneTempID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSceneTempID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSceneTempID of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_nSceneTempID
static int tolua_set_MS_ROLE_DATA_nSceneTempID(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneTempID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSceneTempID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSceneID of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_nSceneID
static int tolua_get_MS_ROLE_DATA_nSceneID(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSceneID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSceneID of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_nSceneID
static int tolua_set_MS_ROLE_DATA_nSceneID(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSceneID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwTeamID of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_unsigned_dwTeamID
static int tolua_get_MS_ROLE_DATA_unsigned_dwTeamID(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwTeamID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwTeamID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwTeamID of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_unsigned_dwTeamID
static int tolua_set_MS_ROLE_DATA_unsigned_dwTeamID(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwTeamID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwTeamID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwMailCounts of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_unsigned_dwMailCounts
static int tolua_get_MS_ROLE_DATA_unsigned_dwMailCounts(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwMailCounts'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwMailCounts);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwMailCounts of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_unsigned_dwMailCounts
static int tolua_set_MS_ROLE_DATA_unsigned_dwMailCounts(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwMailCounts'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwMailCounts = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lstMails of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_lstMails
static int tolua_get_MS_ROLE_DATA_lstMails(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lstMails'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->lstMails,"CBaseList");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lstMails of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_lstMails
static int tolua_set_MS_ROLE_DATA_lstMails(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lstMails'",NULL);
 if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CBaseList",0,&tolua_err)))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lstMails = *((CBaseList*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwGuildID of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_unsigned_dwGuildID
static int tolua_get_MS_ROLE_DATA_unsigned_dwGuildID(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwGuildID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwGuildID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwGuildID of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_unsigned_dwGuildID
static int tolua_set_MS_ROLE_DATA_unsigned_dwGuildID(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwGuildID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwJoinGuildCD of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ROLE_DATA_unsigned_dwJoinGuildCD
static int tolua_get_MS_ROLE_DATA_unsigned_dwJoinGuildCD(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwJoinGuildCD'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwJoinGuildCD);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwJoinGuildCD of class  MS_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ROLE_DATA_unsigned_dwJoinGuildCD
static int tolua_set_MS_ROLE_DATA_unsigned_dwJoinGuildCD(lua_State* tolua_S)
{
  MS_ROLE_DATA* self = (MS_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwJoinGuildCD'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwJoinGuildCD = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_role_data_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"MS_ROLE_DATA","MS_ROLE_DATA","",NULL);
 tolua_beginmodule(tolua_S,"MS_ROLE_DATA");
  tolua_variable(tolua_S,"dwRoleID",tolua_get_MS_ROLE_DATA_unsigned_dwRoleID,tolua_set_MS_ROLE_DATA_unsigned_dwRoleID);
  tolua_array(tolua_S,"szRoleName",tolua_get_role_data_MS_ROLE_DATA_szRoleName,tolua_set_role_data_MS_ROLE_DATA_szRoleName);
  tolua_variable(tolua_S,"byGroup",tolua_get_MS_ROLE_DATA_unsigned_byGroup,tolua_set_MS_ROLE_DATA_unsigned_byGroup);
  tolua_variable(tolua_S,"byLevel",tolua_get_MS_ROLE_DATA_unsigned_byLevel,tolua_set_MS_ROLE_DATA_unsigned_byLevel);
  tolua_variable(tolua_S,"bySex",tolua_get_MS_ROLE_DATA_unsigned_bySex,tolua_set_MS_ROLE_DATA_unsigned_bySex);
  tolua_variable(tolua_S,"byClass",tolua_get_MS_ROLE_DATA_unsigned_byClass,tolua_set_MS_ROLE_DATA_unsigned_byClass);
  tolua_variable(tolua_S,"nLastLoginTime",tolua_get_MS_ROLE_DATA_nLastLoginTime,tolua_set_MS_ROLE_DATA_nLastLoginTime);
  tolua_variable(tolua_S,"nSceneTempID",tolua_get_MS_ROLE_DATA_nSceneTempID,tolua_set_MS_ROLE_DATA_nSceneTempID);
  tolua_variable(tolua_S,"nSceneID",tolua_get_MS_ROLE_DATA_nSceneID,tolua_set_MS_ROLE_DATA_nSceneID);
  tolua_variable(tolua_S,"dwTeamID",tolua_get_MS_ROLE_DATA_unsigned_dwTeamID,tolua_set_MS_ROLE_DATA_unsigned_dwTeamID);
  tolua_variable(tolua_S,"dwMailCounts",tolua_get_MS_ROLE_DATA_unsigned_dwMailCounts,tolua_set_MS_ROLE_DATA_unsigned_dwMailCounts);
  tolua_variable(tolua_S,"lstMails",tolua_get_MS_ROLE_DATA_lstMails,tolua_set_MS_ROLE_DATA_lstMails);
  tolua_variable(tolua_S,"dwGuildID",tolua_get_MS_ROLE_DATA_unsigned_dwGuildID,tolua_set_MS_ROLE_DATA_unsigned_dwGuildID);
  tolua_variable(tolua_S,"dwJoinGuildCD",tolua_get_MS_ROLE_DATA_unsigned_dwJoinGuildCD,tolua_set_MS_ROLE_DATA_unsigned_dwJoinGuildCD);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_role_data (lua_State* tolua_S) {
 return tolua_role_data_open(tolua_S);
};
#endif

