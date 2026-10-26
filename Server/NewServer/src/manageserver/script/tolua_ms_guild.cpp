/*
** Lua binding: ms_guild
** Generated automatically by tolua++-1.0.92 on 05/30/18 13:59:45.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_ms_guild_open (lua_State* tolua_S);

#include "../../../Common/define/guild_def.h"
#include "./guild/ms_guild.h"
#include "./guild/ms_guild.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"GUILD_DB");
 tolua_usertype(tolua_S,"MS_ROLE_DATA");
 tolua_usertype(tolua_S,"CMsGuildMember");
 tolua_usertype(tolua_S,"UINT64");
 tolua_usertype(tolua_S,"BASE_TRIGGER_NODE");
 tolua_usertype(tolua_S,"GUILD_WAR_PERSONAL_ACHIEVEMENT");
 tolua_usertype(tolua_S,"DIPLOMAT_DATA");
 tolua_usertype(tolua_S,"BASE_LIST_NODE");
 tolua_usertype(tolua_S,"MS_GUILD_WAR_DATA");
 tolua_usertype(tolua_S,"CMsGuildStorage");
 tolua_usertype(tolua_S,"GUILD_DUNGEON");
 tolua_usertype(tolua_S,"CMsGuild");
}

/* get function: dwGuildID of class  DIPLOMAT_DATA */
#ifndef TOLUA_DISABLE_tolua_get_DIPLOMAT_DATA_unsigned_dwGuildID
static int tolua_get_DIPLOMAT_DATA_unsigned_dwGuildID(lua_State* tolua_S)
{
  DIPLOMAT_DATA* self = (DIPLOMAT_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwGuildID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwGuildID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwGuildID of class  DIPLOMAT_DATA */
#ifndef TOLUA_DISABLE_tolua_set_DIPLOMAT_DATA_unsigned_dwGuildID
static int tolua_set_DIPLOMAT_DATA_unsigned_dwGuildID(lua_State* tolua_S)
{
  DIPLOMAT_DATA* self = (DIPLOMAT_DATA*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: dwEndTime of class  DIPLOMAT_DATA */
#ifndef TOLUA_DISABLE_tolua_get_DIPLOMAT_DATA_unsigned_dwEndTime
static int tolua_get_DIPLOMAT_DATA_unsigned_dwEndTime(lua_State* tolua_S)
{
  DIPLOMAT_DATA* self = (DIPLOMAT_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwEndTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwEndTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwEndTime of class  DIPLOMAT_DATA */
#ifndef TOLUA_DISABLE_tolua_set_DIPLOMAT_DATA_unsigned_dwEndTime
static int tolua_set_DIPLOMAT_DATA_unsigned_dwEndTime(lua_State* tolua_S)
{
  DIPLOMAT_DATA* self = (DIPLOMAT_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwEndTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwEndTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwBeginDayTime of class  MS_GUILD_WAR_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_GUILD_WAR_DATA_unsigned_dwBeginDayTime
static int tolua_get_MS_GUILD_WAR_DATA_unsigned_dwBeginDayTime(lua_State* tolua_S)
{
  MS_GUILD_WAR_DATA* self = (MS_GUILD_WAR_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwBeginDayTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwBeginDayTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwBeginDayTime of class  MS_GUILD_WAR_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_GUILD_WAR_DATA_unsigned_dwBeginDayTime
static int tolua_set_MS_GUILD_WAR_DATA_unsigned_dwBeginDayTime(lua_State* tolua_S)
{
  MS_GUILD_WAR_DATA* self = (MS_GUILD_WAR_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwBeginDayTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwBeginDayTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwIntruderID of class  MS_GUILD_WAR_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_GUILD_WAR_DATA_unsigned_dwIntruderID
static int tolua_get_MS_GUILD_WAR_DATA_unsigned_dwIntruderID(lua_State* tolua_S)
{
  MS_GUILD_WAR_DATA* self = (MS_GUILD_WAR_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwIntruderID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwIntruderID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwIntruderID of class  MS_GUILD_WAR_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_GUILD_WAR_DATA_unsigned_dwIntruderID
static int tolua_set_MS_GUILD_WAR_DATA_unsigned_dwIntruderID(lua_State* tolua_S)
{
  MS_GUILD_WAR_DATA* self = (MS_GUILD_WAR_DATA*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: dwDefenderID of class  MS_GUILD_WAR_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_GUILD_WAR_DATA_unsigned_dwDefenderID
static int tolua_get_MS_GUILD_WAR_DATA_unsigned_dwDefenderID(lua_State* tolua_S)
{
  MS_GUILD_WAR_DATA* self = (MS_GUILD_WAR_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwDefenderID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwDefenderID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwDefenderID of class  MS_GUILD_WAR_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_GUILD_WAR_DATA_unsigned_dwDefenderID
static int tolua_set_MS_GUILD_WAR_DATA_unsigned_dwDefenderID(lua_State* tolua_S)
{
  MS_GUILD_WAR_DATA* self = (MS_GUILD_WAR_DATA*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nWarResult of class  MS_GUILD_WAR_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_GUILD_WAR_DATA_nWarResult
static int tolua_get_MS_GUILD_WAR_DATA_nWarResult(lua_State* tolua_S)
{
  MS_GUILD_WAR_DATA* self = (MS_GUILD_WAR_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nWarResult'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nWarResult);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nWarResult of class  MS_GUILD_WAR_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_GUILD_WAR_DATA_nWarResult
static int tolua_set_MS_GUILD_WAR_DATA_nWarResult(lua_State* tolua_S)
{
  MS_GUILD_WAR_DATA* self = (MS_GUILD_WAR_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nWarResult'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nWarResult = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwTemplateID of class  GUILD_DUNGEON */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_DUNGEON_unsigned_dwTemplateID
static int tolua_get_GUILD_DUNGEON_unsigned_dwTemplateID(lua_State* tolua_S)
{
  GUILD_DUNGEON* self = (GUILD_DUNGEON*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwTemplateID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwTemplateID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwTemplateID of class  GUILD_DUNGEON */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_DUNGEON_unsigned_dwTemplateID
static int tolua_set_GUILD_DUNGEON_unsigned_dwTemplateID(lua_State* tolua_S)
{
  GUILD_DUNGEON* self = (GUILD_DUNGEON*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwTemplateID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwTemplateID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwOwnerID of class  GUILD_DUNGEON */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_DUNGEON_unsigned_dwOwnerID
static int tolua_get_GUILD_DUNGEON_unsigned_dwOwnerID(lua_State* tolua_S)
{
  GUILD_DUNGEON* self = (GUILD_DUNGEON*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwOwnerID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwOwnerID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwOwnerID of class  GUILD_DUNGEON */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_DUNGEON_unsigned_dwOwnerID
static int tolua_set_GUILD_DUNGEON_unsigned_dwOwnerID(lua_State* tolua_S)
{
  GUILD_DUNGEON* self = (GUILD_DUNGEON*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwOwnerID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwOwnerID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwLeaderID of class  GUILD_DUNGEON */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_DUNGEON_unsigned_dwLeaderID
static int tolua_get_GUILD_DUNGEON_unsigned_dwLeaderID(lua_State* tolua_S)
{
  GUILD_DUNGEON* self = (GUILD_DUNGEON*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwLeaderID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwLeaderID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwLeaderID of class  GUILD_DUNGEON */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_DUNGEON_unsigned_dwLeaderID
static int tolua_set_GUILD_DUNGEON_unsigned_dwLeaderID(lua_State* tolua_S)
{
  GUILD_DUNGEON* self = (GUILD_DUNGEON*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwLeaderID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwLeaderID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nCreateTime of class  GUILD_DUNGEON */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_DUNGEON_nCreateTime
static int tolua_get_GUILD_DUNGEON_nCreateTime(lua_State* tolua_S)
{
  GUILD_DUNGEON* self = (GUILD_DUNGEON*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCreateTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nCreateTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nCreateTime of class  GUILD_DUNGEON */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_DUNGEON_nCreateTime
static int tolua_set_GUILD_DUNGEON_nCreateTime(lua_State* tolua_S)
{
  GUILD_DUNGEON* self = (GUILD_DUNGEON*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCreateTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nCreateTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwRoleID of class  GUILD_WAR_PERSONAL_ACHIEVEMENT */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_WAR_PERSONAL_ACHIEVEMENT_unsigned_dwRoleID
static int tolua_get_GUILD_WAR_PERSONAL_ACHIEVEMENT_unsigned_dwRoleID(lua_State* tolua_S)
{
  GUILD_WAR_PERSONAL_ACHIEVEMENT* self = (GUILD_WAR_PERSONAL_ACHIEVEMENT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwRoleID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwRoleID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwRoleID of class  GUILD_WAR_PERSONAL_ACHIEVEMENT */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_WAR_PERSONAL_ACHIEVEMENT_unsigned_dwRoleID
static int tolua_set_GUILD_WAR_PERSONAL_ACHIEVEMENT_unsigned_dwRoleID(lua_State* tolua_S)
{
  GUILD_WAR_PERSONAL_ACHIEVEMENT* self = (GUILD_WAR_PERSONAL_ACHIEVEMENT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nKillNum of class  GUILD_WAR_PERSONAL_ACHIEVEMENT */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_WAR_PERSONAL_ACHIEVEMENT_nKillNum
static int tolua_get_GUILD_WAR_PERSONAL_ACHIEVEMENT_nKillNum(lua_State* tolua_S)
{
  GUILD_WAR_PERSONAL_ACHIEVEMENT* self = (GUILD_WAR_PERSONAL_ACHIEVEMENT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nKillNum'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nKillNum);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nKillNum of class  GUILD_WAR_PERSONAL_ACHIEVEMENT */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_WAR_PERSONAL_ACHIEVEMENT_nKillNum
static int tolua_set_GUILD_WAR_PERSONAL_ACHIEVEMENT_nKillNum(lua_State* tolua_S)
{
  GUILD_WAR_PERSONAL_ACHIEVEMENT* self = (GUILD_WAR_PERSONAL_ACHIEVEMENT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nKillNum'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nKillNum = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nDeadCount of class  GUILD_WAR_PERSONAL_ACHIEVEMENT */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_WAR_PERSONAL_ACHIEVEMENT_nDeadCount
static int tolua_get_GUILD_WAR_PERSONAL_ACHIEVEMENT_nDeadCount(lua_State* tolua_S)
{
  GUILD_WAR_PERSONAL_ACHIEVEMENT* self = (GUILD_WAR_PERSONAL_ACHIEVEMENT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nDeadCount'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nDeadCount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nDeadCount of class  GUILD_WAR_PERSONAL_ACHIEVEMENT */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_WAR_PERSONAL_ACHIEVEMENT_nDeadCount
static int tolua_set_GUILD_WAR_PERSONAL_ACHIEVEMENT_nDeadCount(lua_State* tolua_S)
{
  GUILD_WAR_PERSONAL_ACHIEVEMENT* self = (GUILD_WAR_PERSONAL_ACHIEVEMENT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nDeadCount'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nDeadCount = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSalary of class  GUILD_WAR_PERSONAL_ACHIEVEMENT */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_WAR_PERSONAL_ACHIEVEMENT_nSalary
static int tolua_get_GUILD_WAR_PERSONAL_ACHIEVEMENT_nSalary(lua_State* tolua_S)
{
  GUILD_WAR_PERSONAL_ACHIEVEMENT* self = (GUILD_WAR_PERSONAL_ACHIEVEMENT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSalary'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSalary);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSalary of class  GUILD_WAR_PERSONAL_ACHIEVEMENT */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_WAR_PERSONAL_ACHIEVEMENT_nSalary
static int tolua_set_GUILD_WAR_PERSONAL_ACHIEVEMENT_nSalary(lua_State* tolua_S)
{
  GUILD_WAR_PERSONAL_ACHIEVEMENT* self = (GUILD_WAR_PERSONAL_ACHIEVEMENT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSalary'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSalary = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwGuildID of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_DB_unsigned_dwGuildID
static int tolua_get_GUILD_DB_unsigned_dwGuildID(lua_State* tolua_S)
{
  GUILD_DB* self = (GUILD_DB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwGuildID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwGuildID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwGuildID of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_DB_unsigned_dwGuildID
static int tolua_set_GUILD_DB_unsigned_dwGuildID(lua_State* tolua_S)
{
  GUILD_DB* self = (GUILD_DB*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: wVersion of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_DB_unsigned_wVersion
static int tolua_get_GUILD_DB_unsigned_wVersion(lua_State* tolua_S)
{
  GUILD_DB* self = (GUILD_DB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wVersion'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->wVersion);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wVersion of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_DB_unsigned_wVersion
static int tolua_set_GUILD_DB_unsigned_wVersion(lua_State* tolua_S)
{
  GUILD_DB* self = (GUILD_DB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wVersion'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->wVersion = (( unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szGuildName of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_get_ms_guild_GUILD_DB_szGuildName
static int tolua_get_ms_guild_GUILD_DB_szGuildName(lua_State* tolua_S)
{
 int tolua_index;
  GUILD_DB* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GUILD_DB*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=GUILD_NAME_LEN)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->szGuildName[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szGuildName of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_set_ms_guild_GUILD_DB_szGuildName
static int tolua_set_ms_guild_GUILD_DB_szGuildName(lua_State* tolua_S)
{
 int tolua_index;
  GUILD_DB* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GUILD_DB*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=GUILD_NAME_LEN)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->szGuildName[tolua_index] = ((  char)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bySvrGroup of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_DB_unsigned_bySvrGroup
static int tolua_get_GUILD_DB_unsigned_bySvrGroup(lua_State* tolua_S)
{
  GUILD_DB* self = (GUILD_DB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bySvrGroup'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->bySvrGroup);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bySvrGroup of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_DB_unsigned_bySvrGroup
static int tolua_set_GUILD_DB_unsigned_bySvrGroup(lua_State* tolua_S)
{
  GUILD_DB* self = (GUILD_DB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bySvrGroup'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bySvrGroup = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwLeaderID of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_DB_unsigned_dwLeaderID
static int tolua_get_GUILD_DB_unsigned_dwLeaderID(lua_State* tolua_S)
{
  GUILD_DB* self = (GUILD_DB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwLeaderID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwLeaderID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwLeaderID of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_DB_unsigned_dwLeaderID
static int tolua_set_GUILD_DB_unsigned_dwLeaderID(lua_State* tolua_S)
{
  GUILD_DB* self = (GUILD_DB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwLeaderID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwLeaderID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szCreaterName of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_get_ms_guild_GUILD_DB_szCreaterName
static int tolua_get_ms_guild_GUILD_DB_szCreaterName(lua_State* tolua_S)
{
 int tolua_index;
  GUILD_DB* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GUILD_DB*)  lua_touserdata(tolua_S,-1);
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
 tolua_pushnumber(tolua_S,(lua_Number)self->szCreaterName[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szCreaterName of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_set_ms_guild_GUILD_DB_szCreaterName
static int tolua_set_ms_guild_GUILD_DB_szCreaterName(lua_State* tolua_S)
{
 int tolua_index;
  GUILD_DB* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GUILD_DB*)  lua_touserdata(tolua_S,-1);
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
  self->szCreaterName[tolua_index] = ((  char)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwCreateTime of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_DB_unsigned_dwCreateTime
static int tolua_get_GUILD_DB_unsigned_dwCreateTime(lua_State* tolua_S)
{
  GUILD_DB* self = (GUILD_DB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwCreateTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwCreateTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwCreateTime of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_DB_unsigned_dwCreateTime
static int tolua_set_GUILD_DB_unsigned_dwCreateTime(lua_State* tolua_S)
{
  GUILD_DB* self = (GUILD_DB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwCreateTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwCreateTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szAnnounce of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_get_ms_guild_GUILD_DB_szAnnounce
static int tolua_get_ms_guild_GUILD_DB_szAnnounce(lua_State* tolua_S)
{
 int tolua_index;
  GUILD_DB* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GUILD_DB*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=GUILD_ANNOUNCE_LEN)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->szAnnounce[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szAnnounce of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_set_ms_guild_GUILD_DB_szAnnounce
static int tolua_set_ms_guild_GUILD_DB_szAnnounce(lua_State* tolua_S)
{
 int tolua_index;
  GUILD_DB* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GUILD_DB*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=GUILD_ANNOUNCE_LEN)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->szAnnounce[tolua_index] = ((  char)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szNotice of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_get_ms_guild_GUILD_DB_szNotice
static int tolua_get_ms_guild_GUILD_DB_szNotice(lua_State* tolua_S)
{
 int tolua_index;
  GUILD_DB* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GUILD_DB*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=GUILD_NOTICE_LEN)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->szNotice[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szNotice of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_set_ms_guild_GUILD_DB_szNotice
static int tolua_set_ms_guild_GUILD_DB_szNotice(lua_State* tolua_S)
{
 int tolua_index;
  GUILD_DB* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GUILD_DB*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=GUILD_NOTICE_LEN)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->szNotice[tolua_index] = ((  char)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: BlobBuffer of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_get_GUILD_DB_BlobBuffer
static int tolua_get_GUILD_DB_BlobBuffer(lua_State* tolua_S)
{
  GUILD_DB* self = (GUILD_DB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'BlobBuffer'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->BlobBuffer);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: BlobBuffer of class  GUILD_DB */
#ifndef TOLUA_DISABLE_tolua_set_GUILD_DB_BlobBuffer
static int tolua_set_GUILD_DB_BlobBuffer(lua_State* tolua_S)
{
  GUILD_DB* self = (GUILD_DB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'BlobBuffer'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->BlobBuffer,(const char*)tolua_tostring(tolua_S,2,0),0-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetID of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetID00
static int tolua_ms_guild_CMsGuild_GetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetSvrGroup of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetSvrGroup00
static int tolua_ms_guild_CMsGuild_GetSvrGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSvrGroup'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetSvrGroup();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSvrGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevel of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetLevel00
static int tolua_ms_guild_CMsGuild_GetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetName of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetName00
static int tolua_ms_guild_CMsGuild_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetCreaterName of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetCreaterName00
static int tolua_ms_guild_CMsGuild_GetCreaterName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCreaterName'", NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->GetCreaterName();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCreaterName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLeaderID of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetLeaderID00
static int tolua_ms_guild_CMsGuild_GetLeaderID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetCreateTime of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetCreateTime00
static int tolua_ms_guild_CMsGuild_GetCreateTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetAnnounce of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetAnnounce00
static int tolua_ms_guild_CMsGuild_GetAnnounce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnnounce'", NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->GetAnnounce();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnnounce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNotice of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SetNotice00
static int tolua_ms_guild_CMsGuild_SetNotice00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  const char* pcszNotice = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNotice'", NULL);
#endif
 {
  self->SetNotice(pcszNotice);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNotice'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNotice of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetNotice00
static int tolua_ms_guild_CMsGuild_GetNotice00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNotice'", NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->GetNotice();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNotice'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStorage of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetStorage00
static int tolua_ms_guild_CMsGuild_GetStorage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStorage'", NULL);
#endif
 {
  CMsGuildStorage& tolua_ret = (CMsGuildStorage&)  self->GetStorage();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CMsGuildStorage");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStorage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLvlRankNode of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetLvlRankNode00
static int tolua_ms_guild_CMsGuild_GetLvlRankNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLvlRankNode'", NULL);
#endif
 {
  BASE_LIST_NODE& tolua_ret = (BASE_LIST_NODE&)  self->GetLvlRankNode();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"BASE_LIST_NODE");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLvlRankNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMoney of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetMoney00
static int tolua_ms_guild_CMsGuild_GetMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddMoney of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddMoney00
static int tolua_ms_guild_CMsGuild_AddMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nMoney = (( signed int)  tolua_tonumber(tolua_S,2,0));
  GUILD_HISTORY_EVENT_TYPE eReason = ((GUILD_HISTORY_EVENT_TYPE) (int)  tolua_tonumber(tolua_S,3,0));
   bool bIsSave = ((  bool)  tolua_toboolean(tolua_S,4,TRUE));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddMoney'", NULL);
#endif
 {
  self->AddMoney(nMoney,eReason,bIsSave);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SubMoney of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SubMoney00
static int tolua_ms_guild_CMsGuild_SubMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nMoney = (( signed int)  tolua_tonumber(tolua_S,2,0));
  GUILD_HISTORY_EVENT_TYPE eReason = ((GUILD_HISTORY_EVENT_TYPE) (int)  tolua_tonumber(tolua_S,3,0));
   bool bIsSave = ((  bool)  tolua_toboolean(tolua_S,4,TRUE));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SubMoney'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SubMoney(nMoney,eReason,bIsSave);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SubMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWood of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetWood00
static int tolua_ms_guild_CMsGuild_GetWood00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddWood of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddWood00
static int tolua_ms_guild_CMsGuild_AddWood00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nWood = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddWood'", NULL);
#endif
 {
  self->AddWood(nWood);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddWood'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SubWood of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SubWood00
static int tolua_ms_guild_CMsGuild_SubWood00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nWood = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SubWood'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SubWood(nWood);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SubWood'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHerb of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetHerb00
static int tolua_ms_guild_CMsGuild_GetHerb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddHerb of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddHerb00
static int tolua_ms_guild_CMsGuild_AddHerb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nHerb = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddHerb'", NULL);
#endif
 {
  self->AddHerb(nHerb);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddHerb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SubHerb of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SubHerb00
static int tolua_ms_guild_CMsGuild_SubHerb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nHerb = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SubHerb'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SubHerb(nHerb);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SubHerb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCryStal of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetCryStal00
static int tolua_ms_guild_CMsGuild_GetCryStal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCryStal'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetCryStal();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCryStal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddCrystal of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddCrystal00
static int tolua_ms_guild_CMsGuild_AddCrystal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nCrystal = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddCrystal'", NULL);
#endif
 {
  self->AddCrystal(nCrystal);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddCrystal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SubCrystal of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SubCrystal00
static int tolua_ms_guild_CMsGuild_SubCrystal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nCrystal = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SubCrystal'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SubCrystal(nCrystal);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SubCrystal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSilver of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetSilver00
static int tolua_ms_guild_CMsGuild_GetSilver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddSilver of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddSilver00
static int tolua_ms_guild_CMsGuild_AddSilver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nSilver = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSilver'", NULL);
#endif
 {
  self->AddSilver(nSilver);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSilver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SubSilver of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SubSilver00
static int tolua_ms_guild_CMsGuild_SubSilver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nSilver = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SubSilver'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SubSilver(nSilver);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SubSilver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVariable of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetVariable00
static int tolua_ms_guild_CMsGuild_GetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetVariable of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SetVariable00
static int tolua_ms_guild_CMsGuild_SetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetStorageRightByPosition of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetStorageRightByPosition00
static int tolua_ms_guild_CMsGuild_GetStorageRightByPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nPosition = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStorageRightByPosition'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetStorageRightByPosition(nPosition);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStorageRightByPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanGuildChat of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_CanGuildChat00
static int tolua_ms_guild_CMsGuild_CanGuildChat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanGuildChat'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CanGuildChat(dwRoleID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanGuildChat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddGuildEvent of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddGuildEvent00
static int tolua_ms_guild_CMsGuild_AddGuildEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
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
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  unsigned int param1 = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int param2 = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
  unsigned int param3 = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
  unsigned int param4 = (( unsigned int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddGuildEvent'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddGuildEvent(nType,param1,param2,param3,param4);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddGuildEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMemberNum of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetMemberNum00
static int tolua_ms_guild_CMsGuild_GetMemberNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMemberNum'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMemberNum();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMemberNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsMember of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_IsMember00
static int tolua_ms_guild_CMsGuild_IsMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddMember of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddMember00
static int tolua_ms_guild_CMsGuild_AddMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"MS_ROLE_DATA",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  MS_ROLE_DATA* pRoleData = ((MS_ROLE_DATA*)  tolua_tousertype(tolua_S,2,0));
  signed int nPosition = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddMember'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddMember(pRoleData,nPosition);
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

/* method: DelMember of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_DelMember00
static int tolua_ms_guild_CMsGuild_DelMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelMember'", NULL);
#endif
 {
  self->DelMember(dwRoleID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelMember'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMember of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetMember00
static int tolua_ms_guild_CMsGuild_GetMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMember'", NULL);
#endif
 {
  CMsGuildMember* tolua_ret = (CMsGuildMember*)  self->GetMember(dwRoleID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMsGuildMember");
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

/* method: GetMemberNumInAPost of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetMemberNumInAPost00
static int tolua_ms_guild_CMsGuild_GetMemberNumInAPost00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned char byPosition = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMemberNumInAPost'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMemberNumInAPost(byPosition);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMemberNumInAPost'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BroadcastMail of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_BroadcastMail00
static int tolua_ms_guild_CMsGuild_BroadcastMail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  const char* pcszTitle = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* pcszContent = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BroadcastMail'", NULL);
#endif
 {
 int tolua_ret = (int)
self->BroadcastMail(pcszTitle,pcszContent);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BroadcastMail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BeginUpgradeWelfareBuffer of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_BeginUpgradeWelfareBuffer00
static int tolua_ms_guild_CMsGuild_BeginUpgradeWelfareBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BeginUpgradeWelfareBuffer'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->BeginUpgradeWelfareBuffer(dwRoleID,nType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BeginUpgradeWelfareBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CancelUpgradeWelfareBuffer of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_CancelUpgradeWelfareBuffer00
static int tolua_ms_guild_CMsGuild_CancelUpgradeWelfareBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CancelUpgradeWelfareBuffer'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->CancelUpgradeWelfareBuffer(nType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CancelUpgradeWelfareBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BeginUpgradeBuilding of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_BeginUpgradeBuilding00
static int tolua_ms_guild_CMsGuild_BeginUpgradeBuilding00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"UINT64",0,&tolua_err)) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  UINT64 qwNpcNameID = *((UINT64*)  tolua_tousertype(tolua_S,3,0));
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BeginUpgradeBuilding'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->BeginUpgradeBuilding(dwRoleID,qwNpcNameID,nType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BeginUpgradeBuilding'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CancelUpgradeBuilding of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_CancelUpgradeBuilding00
static int tolua_ms_guild_CMsGuild_CancelUpgradeBuilding00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"UINT64",0,&tolua_err)) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  UINT64 qwNpcNameID = *((UINT64*)  tolua_tousertype(tolua_S,2,0));
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CancelUpgradeBuilding'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->CancelUpgradeBuilding(qwNpcNameID,nType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CancelUpgradeBuilding'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEnemyNum of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetEnemyNum00
static int tolua_ms_guild_CMsGuild_GetEnemyNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEnemyNum'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetEnemyNum();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEnemyNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAllianceNum of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetAllianceNum00
static int tolua_ms_guild_CMsGuild_GetAllianceNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAllianceNum'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetAllianceNum();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAllianceNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAlliance of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_IsAlliance00
static int tolua_ms_guild_CMsGuild_IsAlliance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAlliance'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsAlliance(dwGuildID);
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

/* method: IsEnemy of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_IsEnemy00
static int tolua_ms_guild_CMsGuild_IsEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsEnemy'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsEnemy(dwGuildID);
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

/* method: AddAlliance of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddAlliance00
static int tolua_ms_guild_CMsGuild_AddAlliance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwEndTime = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddAlliance'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddAlliance(dwGuildID,dwEndTime);
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

/* method: DelAlliance of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_DelAlliance00
static int tolua_ms_guild_CMsGuild_DelAlliance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelAlliance'", NULL);
#endif
 {
  self->DelAlliance(dwGuildID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelAlliance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddEnemy of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddEnemy00
static int tolua_ms_guild_CMsGuild_AddEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwEndTime = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddEnemy'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddEnemy(dwGuildID,dwEndTime);
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

/* method: DelEnemy of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_DelEnemy00
static int tolua_ms_guild_CMsGuild_DelEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelEnemy'", NULL);
#endif
 {
  self->DelEnemy(dwGuildID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelEnemy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEnemyDataByIndex of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetEnemyDataByIndex00
static int tolua_ms_guild_CMsGuild_GetEnemyDataByIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEnemyDataByIndex'", NULL);
#endif
 {
  DIPLOMAT_DATA* tolua_ret = (DIPLOMAT_DATA*)  self->GetEnemyDataByIndex(nIndex);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"DIPLOMAT_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEnemyDataByIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAllianceDataByIndex of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetAllianceDataByIndex00
static int tolua_ms_guild_CMsGuild_GetAllianceDataByIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAllianceDataByIndex'", NULL);
#endif
 {
  DIPLOMAT_DATA* tolua_ret = (DIPLOMAT_DATA*)  self->GetAllianceDataByIndex(nIndex);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"DIPLOMAT_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAllianceDataByIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddDungeon of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddDungeon00
static int tolua_ms_guild_CMsGuild_AddDungeon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTemplateID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwOwnerID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int dwLeaderID = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddDungeon'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->AddDungeon(dwTemplateID,dwOwnerID,dwLeaderID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddDungeon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelDungeon of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_DelDungeon00
static int tolua_ms_guild_CMsGuild_DelDungeon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTemplateID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelDungeon'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DelDungeon(dwTemplateID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelDungeon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckSameDungeonType of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_CheckSameDungeonType00
static int tolua_ms_guild_CMsGuild_CheckSameDungeonType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTemplateID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckSameDungeonType'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CheckSameDungeonType(dwTemplateID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckSameDungeonType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindDunGeon of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_FindDunGeon00
static int tolua_ms_guild_CMsGuild_FindDunGeon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTemplateID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindDunGeon'", NULL);
#endif
 {
  GUILD_DUNGEON* tolua_ret = (GUILD_DUNGEON*)  self->FindDunGeon(dwTemplateID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"GUILD_DUNGEON");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindDunGeon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FilterDungeon of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_FilterDungeon00
static int tolua_ms_guild_CMsGuild_FilterDungeon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FilterDungeon'", NULL);
#endif
 {
 int tolua_ret = (int)
self->FilterDungeon();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FilterDungeon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSabacEnrollTime of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetSabacEnrollTime00
static int tolua_ms_guild_CMsGuild_GetSabacEnrollTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSabacEnrollTime'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetSabacEnrollTime(nIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSabacEnrollTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EnrollSabac of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_EnrollSabac00
static int tolua_ms_guild_CMsGuild_EnrollSabac00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwEnrollTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EnrollSabac'", NULL);
#endif
 {
  self->EnrollSabac(dwEnrollTime);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EnrollSabac'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OccupySabac of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_OccupySabac00
static int tolua_ms_guild_CMsGuild_OccupySabac00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
   bool bOccupied = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OccupySabac'", NULL);
#endif
 {
  self->OccupySabac(bOccupied);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OccupySabac'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsOccupiedSabac of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_IsOccupiedSabac00
static int tolua_ms_guild_CMsGuild_IsOccupiedSabac00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsOccupiedSabac'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsOccupiedSabac();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsOccupiedSabac'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsEnrolledSabac of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_IsEnrolledSabac00
static int tolua_ms_guild_CMsGuild_IsEnrolledSabac00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsEnrolledSabac'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsEnrolledSabac();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsEnrolledSabac'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckCharacter of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_CheckCharacter00
static int tolua_ms_guild_CMsGuild_CheckCharacter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nC = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckCharacter'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CheckCharacter(nC);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckCharacter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWarCharacter of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetWarCharacter00
static int tolua_ms_guild_CMsGuild_GetWarCharacter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWarCharacter'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetWarCharacter();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWarCharacter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWarCharacter of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SetWarCharacter00
static int tolua_ms_guild_CMsGuild_SetWarCharacter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int eC = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWarCharacter'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetWarCharacter(eC);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWarCharacter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearWarCharacter of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_ClearWarCharacter00
static int tolua_ms_guild_CMsGuild_ClearWarCharacter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nC = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearWarCharacter'", NULL);
#endif
 {
 int tolua_ret = (int)
self->ClearWarCharacter(nC);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearWarCharacter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearIntruder of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_ClearIntruder00
static int tolua_ms_guild_CMsGuild_ClearIntruder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearIntruder'", NULL);
#endif
 {
 int tolua_ret = (int)
self->ClearIntruder();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearIntruder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIntruderNum of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetIntruderNum00
static int tolua_ms_guild_CMsGuild_GetIntruderNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIntruderNum'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetIntruderNum();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIntruderNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FirstIntruder of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_FirstIntruder00
static int tolua_ms_guild_CMsGuild_FirstIntruder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FirstIntruder'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->FirstIntruder();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FirstIntruder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NextIntruder of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_NextIntruder00
static int tolua_ms_guild_CMsGuild_NextIntruder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NextIntruder'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->NextIntruder();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NextIntruder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaBroadcastMsgNotifyType of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_LuaBroadcastMsgNotifyType00
static int tolua_ms_guild_CMsGuild_LuaBroadcastMsgNotifyType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaBroadcastMsgNotifyType'", NULL);
#endif
 {
 int tolua_ret = (int)
self->LuaBroadcastMsgNotifyType(nType);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaBroadcastMsgNotifyType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaAddProtectionTime of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_LuaAddProtectionTime00
static int tolua_ms_guild_CMsGuild_LuaAddProtectionTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaAddProtectionTime'", NULL);
#endif
 {
 int tolua_ret = (int)
self->LuaAddProtectionTime(dwTime);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaAddProtectionTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaLeaveGuild of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_LuaLeaveGuild00
static int tolua_ms_guild_CMsGuild_LuaLeaveGuild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nLeaveType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaLeaveGuild'", NULL);
#endif
 {
 int tolua_ret = (int)
self->LuaLeaveGuild(nLeaveType,dwRoleID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaLeaveGuild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaBroadcastJoinWar of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_LuaBroadcastJoinWar00
static int tolua_ms_guild_CMsGuild_LuaBroadcastJoinWar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  signed int nWarCharacter = (( signed int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwTargetGuildID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaBroadcastJoinWar'", NULL);
#endif
 {
 int tolua_ret = (int)
self->LuaBroadcastJoinWar(nWarCharacter,dwTargetGuildID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaBroadcastJoinWar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaAddBuilding of class  CMsGuild */
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_LuaAddBuilding00
static int tolua_ms_guild_CMsGuild_LuaAddBuilding00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuild",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuild* self = (CMsGuild*)  tolua_tousertype(tolua_S,1,0);
  const char* pcszNameID = ((const char*)  tolua_tostring(tolua_S,2,0));
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,4,0));
  unsigned int dwReviveTime = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaAddBuilding'", NULL);
#endif
 {
 int tolua_ret = (int)
self->LuaAddBuilding(pcszNameID,nType,nLevel,dwReviveTime);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaAddBuilding'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetMaxOfferInPosition */
#ifndef TOLUA_DISABLE_tolua_ms_guild_GetMaxOfferInPosition00
static int tolua_ms_guild_GetMaxOfferInPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int nPosition = (( signed int)  tolua_tonumber(tolua_S,1,0));
 {
  signed int tolua_ret = ( signed int)  GetMaxOfferInPosition(nPosition);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxOfferInPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ms_guild_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"GUILD_CREATER_LEVEL",GUILD_CREATER_LEVEL);
 tolua_constant(tolua_S,"GUILD_CREATE_MONEY",GUILD_CREATE_MONEY);
 tolua_constant(tolua_S,"GUILD_CREATE_ITEM_ID",GUILD_CREATE_ITEM_ID);
 tolua_constant(tolua_S,"GUILD_CREATE_ITEM_NUM",GUILD_CREATE_ITEM_NUM);
 tolua_constant(tolua_S,"MAX_GUILD_NUM_SYSTEM_LIMIT",MAX_GUILD_NUM_SYSTEM_LIMIT);
 tolua_constant(tolua_S,"MAX_APPLY_GUILD_ROLE_NUM",MAX_APPLY_GUILD_ROLE_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_MEMBER_COUNT",GUILD_MAX_MEMBER_COUNT);
 tolua_constant(tolua_S,"MAX_VIEW_GUILD_LIST_COUNT",MAX_VIEW_GUILD_LIST_COUNT);
 tolua_constant(tolua_S,"ROLE_MAX_APPLICATION",ROLE_MAX_APPLICATION);
 tolua_constant(tolua_S,"GUILD_MAX_ALLIANCE_NUM",GUILD_MAX_ALLIANCE_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_ENEMY_NUM",GUILD_MAX_ENEMY_NUM);
 tolua_constant(tolua_S,"GUILD_DATA_NTF_HISTORY_NUM",GUILD_DATA_NTF_HISTORY_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_CHEST_NTF_NUM",GUILD_MAX_CHEST_NTF_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_HISTORY_EVENT_NUM",GUILD_MAX_HISTORY_EVENT_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_STORAGE_EVENT_NUM",GUILD_MAX_STORAGE_EVENT_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_CHEST_EVENT_NUM",GUILD_MAX_CHEST_EVENT_NUM);
 tolua_constant(tolua_S,"GUILD_STORAGE_MAX_ITEM_NUM_PER_TAG",GUILD_STORAGE_MAX_ITEM_NUM_PER_TAG);
 tolua_constant(tolua_S,"GUILD_STORAGE_MAX_TAG_NUM",GUILD_STORAGE_MAX_TAG_NUM);
 tolua_constant(tolua_S,"GUILD_STORAGE_LOW_LIMIT",GUILD_STORAGE_LOW_LIMIT);
 tolua_constant(tolua_S,"GUILD_MAX_APPLY_ALLIANCE_NUM",GUILD_MAX_APPLY_ALLIANCE_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_WELFARE_AURA_COUNT",GUILD_MAX_WELFARE_AURA_COUNT);
 tolua_constant(tolua_S,"GUILD_MAX_UPGRADE_AURA_COUNT",GUILD_MAX_UPGRADE_AURA_COUNT);
 tolua_constant(tolua_S,"GUILD_MAX_UPGRADE_BUILDING_COUNT",GUILD_MAX_UPGRADE_BUILDING_COUNT);
 tolua_constant(tolua_S,"GUILD_MAX_DUNGEON_COUNT",GUILD_MAX_DUNGEON_COUNT);
 tolua_constant(tolua_S,"ONE_DAY_SECOND",ONE_DAY_SECOND);
 tolua_constant(tolua_S,"GUILD_UPDATE_RANKLIST_STARTTIME",GUILD_UPDATE_RANKLIST_STARTTIME);
 tolua_constant(tolua_S,"GUILD_UPDATE_RANKLIST_ENDIME",GUILD_UPDATE_RANKLIST_ENDIME);
 tolua_constant(tolua_S,"GUILD_DUNGEON_AWARD_NUM",GUILD_DUNGEON_AWARD_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_ITEM_BUFFER_LENGTH",GUILD_MAX_ITEM_BUFFER_LENGTH);
 tolua_constant(tolua_S,"GUILD_MAX_BUILDING_LEVEL",GUILD_MAX_BUILDING_LEVEL);
 tolua_constant(tolua_S,"GUILD_MAX_BUILDING_NUM",GUILD_MAX_BUILDING_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_GATE_NUM",GUILD_MAX_GATE_NUM);
 tolua_constant(tolua_S,"MAX_SABAC_ENROLL_COUNT",MAX_SABAC_ENROLL_COUNT);
 tolua_constant(tolua_S,"GUILD_MAX_ACHIEVEMENT_NUM",GUILD_MAX_ACHIEVEMENT_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_ACHI_ARRAY_LENGTH",GUILD_MAX_ACHI_ARRAY_LENGTH);
 tolua_constant(tolua_S,"GUILD_WAR_RECORD_NUM_PER_PAGE",GUILD_WAR_RECORD_NUM_PER_PAGE);
 tolua_constant(tolua_S,"MAX_TIME_DEVIATION",MAX_TIME_DEVIATION);
 tolua_constant(tolua_S,"MAX_GUILD_CORE_MEMBER",MAX_GUILD_CORE_MEMBER);
  tolua_constant(tolua_S,"GUILD_NOTIFY_ROLE_APP",GUILD_NOTIFY_ROLE_APP);
  tolua_constant(tolua_S,"GUILD_NOTIFY_DIPLOMAT_APP",GUILD_NOTIFY_DIPLOMAT_APP);
  tolua_constant(tolua_S,"GUILD_NOTIFY_MATCH_WAR",GUILD_NOTIFY_MATCH_WAR);
  tolua_constant(tolua_S,"GUILD_VIEW_UP",GUILD_VIEW_UP);
  tolua_constant(tolua_S,"GUILD_VIEW_DOWN",GUILD_VIEW_DOWN);
  tolua_constant(tolua_S,"GUILD_POSITION_NONE",GUILD_POSITION_NONE);
  tolua_constant(tolua_S,"GUILD_POSITION_LEADER",GUILD_POSITION_LEADER);
  tolua_constant(tolua_S,"GUILD_POSITION_SUBLEADER",GUILD_POSITION_SUBLEADER);
  tolua_constant(tolua_S,"GUILD_POSITION_ELDER",GUILD_POSITION_ELDER);
  tolua_constant(tolua_S,"GUILD_POSITION_BISHOP",GUILD_POSITION_BISHOP);
  tolua_constant(tolua_S,"GUILD_POSITION_DEACON",GUILD_POSITION_DEACON);
  tolua_constant(tolua_S,"GUILD_POSITION_SUBDEACON",GUILD_POSITION_SUBDEACON);
  tolua_constant(tolua_S,"GUILD_POSITION_CIVILIAN",GUILD_POSITION_CIVILIAN);
  tolua_constant(tolua_S,"GUILD_POSITION_TOTAL",GUILD_POSITION_TOTAL);
 tolua_constant(tolua_S,"GUILD_POSITION_COUNT",GUILD_POSITION_COUNT);
  tolua_constant(tolua_S,"G_POS_RIGHT_NONE",G_POS_RIGHT_NONE);
  tolua_constant(tolua_S,"G_POS_RIGHT_INVITE",G_POS_RIGHT_INVITE);
  tolua_constant(tolua_S,"G_POS_RIGHT_RECRUIT",G_POS_RIGHT_RECRUIT);
  tolua_constant(tolua_S,"G_POS_RIGHT_FORBID_CHAT",G_POS_RIGHT_FORBID_CHAT);
  tolua_constant(tolua_S,"G_POS_RIGHT_NOTICE",G_POS_RIGHT_NOTICE);
  tolua_constant(tolua_S,"G_POS_RIGHT_SET_STORAGE_RIGHT",G_POS_RIGHT_SET_STORAGE_RIGHT);
  tolua_constant(tolua_S,"G_POS_RIGHT_OPEN_DUNGEON",G_POS_RIGHT_OPEN_DUNGEON);
  tolua_constant(tolua_S,"G_POS_RIGHT_UPGRADE_BUILDING",G_POS_RIGHT_UPGRADE_BUILDING);
  tolua_constant(tolua_S,"G_POS_RIGHT_UPGRADE_WELFARE",G_POS_RIGHT_UPGRADE_WELFARE);
  tolua_constant(tolua_S,"G_POS_RIGHT_CHANGE_POS",G_POS_RIGHT_CHANGE_POS);
  tolua_constant(tolua_S,"G_POS_RIGHT_BANISH",G_POS_RIGHT_BANISH);
  tolua_constant(tolua_S,"G_POS_RIGHT_DIPLOMAT",G_POS_RIGHT_DIPLOMAT);
  tolua_constant(tolua_S,"G_POS_RIGHT_ACTIVITY",G_POS_RIGHT_ACTIVITY);
  tolua_constant(tolua_S,"G_STORAGE_1_POP",G_STORAGE_1_POP);
  tolua_constant(tolua_S,"G_STORAGE_2_POP",G_STORAGE_2_POP);
  tolua_constant(tolua_S,"G_STORAGE_3_POP",G_STORAGE_3_POP);
  tolua_constant(tolua_S,"G_STORAGE_4_POP",G_STORAGE_4_POP);
  tolua_constant(tolua_S,"G_STORAGE_5_POP",G_STORAGE_5_POP);
  tolua_constant(tolua_S,"G_STORAGE_6_POP",G_STORAGE_6_POP);
  tolua_constant(tolua_S,"G_STORAGE_1_PUSH",G_STORAGE_1_PUSH);
  tolua_constant(tolua_S,"G_STORAGE_2_PUSH",G_STORAGE_2_PUSH);
  tolua_constant(tolua_S,"G_STORAGE_3_PUSH",G_STORAGE_3_PUSH);
  tolua_constant(tolua_S,"G_STORAGE_4_PUSH",G_STORAGE_4_PUSH);
  tolua_constant(tolua_S,"G_STORAGE_5_PUSH",G_STORAGE_5_PUSH);
  tolua_constant(tolua_S,"G_STORAGE_6_PUSH",G_STORAGE_6_PUSH);
  tolua_constant(tolua_S,"GUILD_FLAG_IS_CHAT_FORBIDDEN",GUILD_FLAG_IS_CHAT_FORBIDDEN);
  tolua_constant(tolua_S,"G_DIPLOMATIC_TIME_1",G_DIPLOMATIC_TIME_1);
  tolua_constant(tolua_S,"G_DIPLOMATIC_TIME_2",G_DIPLOMATIC_TIME_2);
  tolua_constant(tolua_S,"G_DIPLOMATIC_TIME_3",G_DIPLOMATIC_TIME_3);
  tolua_constant(tolua_S,"G_DIPLOMATIC_TIME_4",G_DIPLOMATIC_TIME_4);
  tolua_constant(tolua_S,"GUILD_REVERT_REFUSE",GUILD_REVERT_REFUSE);
  tolua_constant(tolua_S,"GUILD_REVERT_AGREE",GUILD_REVERT_AGREE);
  tolua_constant(tolua_S,"GUILD_CHAT_FORBID",GUILD_CHAT_FORBID);
  tolua_constant(tolua_S,"GUILD_CHAT_UNFORBID",GUILD_CHAT_UNFORBID);
  tolua_constant(tolua_S,"GUILD_RES_ADD_COUNT",GUILD_RES_ADD_COUNT);
  tolua_constant(tolua_S,"GUILD_RES_DEC_COUNT",GUILD_RES_DEC_COUNT);
  tolua_constant(tolua_S,"GUILD_RES_ADD_PERCENT",GUILD_RES_ADD_PERCENT);
  tolua_constant(tolua_S,"GUILD_RES_DEC_PERCENT",GUILD_RES_DEC_PERCENT);
  tolua_constant(tolua_S,"GUILD_ATTR_BEGIN",GUILD_ATTR_BEGIN);
  tolua_constant(tolua_S,"GUILD_ATTR_MONEY",GUILD_ATTR_MONEY);
  tolua_constant(tolua_S,"GUILD_ATTR_LEVEL",GUILD_ATTR_LEVEL);
  tolua_constant(tolua_S,"GUILD_ATTR_SALARY",GUILD_ATTR_SALARY);
  tolua_constant(tolua_S,"GUILD_ATTR_HERB",GUILD_ATTR_HERB);
  tolua_constant(tolua_S,"GUILD_ATTR_WOOD",GUILD_ATTR_WOOD);
  tolua_constant(tolua_S,"GUILD_ATTR_CRYSTAL",GUILD_ATTR_CRYSTAL);
  tolua_constant(tolua_S,"GUILD_ATTR_SILVER",GUILD_ATTR_SILVER);
  tolua_constant(tolua_S,"GUILD_ATTR_PROSPERITY",GUILD_ATTR_PROSPERITY);
  tolua_constant(tolua_S,"GUILD_ATTR_ATTACK_CD",GUILD_ATTR_ATTACK_CD);
  tolua_constant(tolua_S,"GUILD_ATTR_PROTECTION_TIME",GUILD_ATTR_PROTECTION_TIME);
  tolua_constant(tolua_S,"GUILD_AGREE_BY_APPLY",GUILD_AGREE_BY_APPLY);
  tolua_constant(tolua_S,"GUILD_AGREE_BY_INVITE",GUILD_AGREE_BY_INVITE);
  tolua_constant(tolua_S,"GUILD_LEAVE_ACTIVE",GUILD_LEAVE_ACTIVE);
  tolua_constant(tolua_S,"GUILD_LEAVE_PASSIVE",GUILD_LEAVE_PASSIVE);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_NEUTRALLY",GUILD_DIPLOMAT_NEUTRALLY);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_ALLIANCE",GUILD_DIPLOMAT_ALLIANCE);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_ENEMY",GUILD_DIPLOMAT_ENEMY);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_TIME_BEGIN",GUILD_DIPLOMAT_TIME_BEGIN);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_TIME_ONE",GUILD_DIPLOMAT_TIME_ONE);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_TIME_THREE",GUILD_DIPLOMAT_TIME_THREE);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_TIME_SEVEN",GUILD_DIPLOMAT_TIME_SEVEN);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_TIME_THIRTY",GUILD_DIPLOMAT_TIME_THIRTY);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_TIME_END",GUILD_DIPLOMAT_TIME_END);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BEGIN",GUILD_HE_TYPE_BEGIN);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_CREATE",GUILD_HE_TYPE_CREATE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_JOIN",GUILD_HE_TYPE_JOIN);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_LEAVE",GUILD_HE_TYPE_LEAVE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BANISH",GUILD_HE_TYPE_BANISH);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_POSITION_CHANGE",GUILD_HE_TYPE_POSITION_CHANGE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BUILDING_LVLUP",GUILD_HE_TYPE_BUILDING_LVLUP);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_SKILL_LVLUP",GUILD_HE_TYPE_SKILL_LVLUP);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_DEMISE",GUILD_HE_TYPE_DEMISE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_UNION",GUILD_HE_TYPE_UNION);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_ENEMY",GUILD_HE_TYPE_ENEMY);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_WAR",GUILD_HE_TYPE_WAR);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BUILDING_CREATE",GUILD_HE_TYPE_BUILDING_CREATE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BUILDING_DESTORY",GUILD_HE_TYPE_BUILDING_DESTORY);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BUILDING_DEL",GUILD_HE_TYPE_BUILDING_DEL);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BUILDING_REVIVE",GUILD_HE_TYPE_BUILDING_REVIVE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_ATTACK_SUCC",GUILD_HE_TYPE_ATTACK_SUCC);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_ATTACK_FAILED",GUILD_HE_TYPE_ATTACK_FAILED);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_DEFEND_SUCC",GUILD_HE_TYPE_DEFEND_SUCC);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_DEFEND_FAILED",GUILD_HE_TYPE_DEFEND_FAILED);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_OPEN_ACTIVITY",GUILD_HE_TYPE_OPEN_ACTIVITY);
  tolua_constant(tolua_S,"GUILD_HE_CANCEL_ALLIANCE",GUILD_HE_CANCEL_ALLIANCE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_END",GUILD_HE_TYPE_END);
  tolua_constant(tolua_S,"GUILD_CHEST_BEGIN",GUILD_CHEST_BEGIN);
  tolua_constant(tolua_S,"GUILD_CHEST_CREATE_BUILDING",GUILD_CHEST_CREATE_BUILDING);
  tolua_constant(tolua_S,"GUILD_CHEST_ACTIVITY",GUILD_CHEST_ACTIVITY);
  tolua_constant(tolua_S,"GUILD_CHEST_CONTRIBUTE",GUILD_CHEST_CONTRIBUTE);
  tolua_constant(tolua_S,"GUILD_CHEST_B_UPGRADE",GUILD_CHEST_B_UPGRADE);
  tolua_constant(tolua_S,"GUILD_CHEST_W_UPGRADE",GUILD_CHEST_W_UPGRADE);
  tolua_constant(tolua_S,"GUILD_CHEST_ALLIANCE",GUILD_CHEST_ALLIANCE);
  tolua_constant(tolua_S,"GUILD_CHEST_ARMY",GUILD_CHEST_ARMY);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_SACK_A_1",GUILD_CHEST_WAR_SACK_A_1);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_SACK_A_2",GUILD_CHEST_WAR_SACK_A_2);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_SACK_D_1",GUILD_CHEST_WAR_SACK_D_1);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_SACK_D_2",GUILD_CHEST_WAR_SACK_D_2);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_WIN",GUILD_CHEST_WAR_WIN);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_LOSE",GUILD_CHEST_WAR_LOSE);
  tolua_constant(tolua_S,"GUILD_CHEST_CANCEL_BUILDING_UPGRADE",GUILD_CHEST_CANCEL_BUILDING_UPGRADE);
  tolua_constant(tolua_S,"GUILD_CHEST_CANCEL_WELFARE_UPGRADE",GUILD_CHEST_CANCEL_WELFARE_UPGRADE);
  tolua_constant(tolua_S,"GUILD_CHEST_DEL_BUILDING",GUILD_CHEST_DEL_BUILDING);
  tolua_constant(tolua_S,"GUILD_CHEST_OPEN_DUNGEON",GUILD_CHEST_OPEN_DUNGEON);
  tolua_constant(tolua_S,"GUILD_CHEST_COMPLETE_DUNGEON",GUILD_CHEST_COMPLETE_DUNGEON);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_PLUNDER",GUILD_CHEST_WAR_PLUNDER);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_PLUNDER_EXTRA",GUILD_CHEST_WAR_PLUNDER_EXTRA);
  tolua_constant(tolua_S,"GUILD_CHEST_ROUTINE_CONSUME",GUILD_CHEST_ROUTINE_CONSUME);
  tolua_constant(tolua_S,"GUILD_CHEST_DECLARE_WAR",GUILD_CHEST_DECLARE_WAR);
  tolua_constant(tolua_S,"GUILD_CHEST_MATCH_WAR",GUILD_CHEST_MATCH_WAR);
  tolua_constant(tolua_S,"GUILD_CHEST_BUILDING_DAMAGE",GUILD_CHEST_BUILDING_DAMAGE);
  tolua_constant(tolua_S,"GUILD_CHEST_GM",GUILD_CHEST_GM);
  tolua_constant(tolua_S,"GUILD_CHEST_END",GUILD_CHEST_END);
  tolua_constant(tolua_S,"STORAGE_HE_TYPE_BEGIN",STORAGE_HE_TYPE_BEGIN);
  tolua_constant(tolua_S,"STORAGE_HE_TYPE_PUSH",STORAGE_HE_TYPE_PUSH);
  tolua_constant(tolua_S,"STORAGE_HE_TYPE_POP",STORAGE_HE_TYPE_POP);
  tolua_constant(tolua_S,"GUILD_STORAGE_TAG_1",GUILD_STORAGE_TAG_1);
  tolua_constant(tolua_S,"GUILD_STORAGE_TAG_2",GUILD_STORAGE_TAG_2);
  tolua_constant(tolua_S,"GUILD_STORAGE_TAG_3",GUILD_STORAGE_TAG_3);
  tolua_constant(tolua_S,"GUILD_STORAGE_TAG_4",GUILD_STORAGE_TAG_4);
  tolua_constant(tolua_S,"GUILD_STORAGE_TAG_5",GUILD_STORAGE_TAG_5);
  tolua_constant(tolua_S,"GUILD_STORAGE_TAG_6",GUILD_STORAGE_TAG_6);
  tolua_constant(tolua_S,"GUILD_REPLY_REFUSE",GUILD_REPLY_REFUSE);
  tolua_constant(tolua_S,"GUILD_REPLY_AGREE",GUILD_REPLY_AGREE);
  tolua_constant(tolua_S,"GUILD_B_NONE",GUILD_B_NONE);
  tolua_constant(tolua_S,"GUILD_B_MAIN",GUILD_B_MAIN);
  tolua_constant(tolua_S,"GUILD_B_BUSINESS",GUILD_B_BUSINESS);
  tolua_constant(tolua_S,"GUILD_B_DEITY",GUILD_B_DEITY);
  tolua_constant(tolua_S,"GUILD_B_HOUSE",GUILD_B_HOUSE);
  tolua_constant(tolua_S,"GUILD_B_STORAGE",GUILD_B_STORAGE);
  tolua_constant(tolua_S,"GUILD_B_STAFF",GUILD_B_STAFF);
  tolua_constant(tolua_S,"GUILD_B_WONDER",GUILD_B_WONDER);
  tolua_constant(tolua_S,"GUILD_B_HERB",GUILD_B_HERB);
  tolua_constant(tolua_S,"GUILD_B_WOOD",GUILD_B_WOOD);
  tolua_constant(tolua_S,"GUILD_B_CRYSTAL",GUILD_B_CRYSTAL);
  tolua_constant(tolua_S,"GUILD_B_SILVER",GUILD_B_SILVER);
  tolua_constant(tolua_S,"GUILD_B_HERB_STORAGE",GUILD_B_HERB_STORAGE);
  tolua_constant(tolua_S,"GUILD_B_WOOD_STORAGE",GUILD_B_WOOD_STORAGE);
  tolua_constant(tolua_S,"GUILD_B_CRYSTAL_STORAGE",GUILD_B_CRYSTAL_STORAGE);
  tolua_constant(tolua_S,"GUILD_B_SILVER_STORAGE",GUILD_B_SILVER_STORAGE);
  tolua_constant(tolua_S,"GUILD_B_FUNATIONAL_NUM",GUILD_B_FUNATIONAL_NUM);
  tolua_constant(tolua_S,"GUILD_B_GATE",GUILD_B_GATE);
  tolua_constant(tolua_S,"GUILD_B_WALL",GUILD_B_WALL);
  tolua_constant(tolua_S,"GUILD_B_ARMSHOP",GUILD_B_ARMSHOP);
  tolua_constant(tolua_S,"GUILD_B_ARROW",GUILD_B_ARROW);
  tolua_constant(tolua_S,"GUILD_B_TURRET",GUILD_B_TURRET);
  tolua_constant(tolua_S,"GUILD_B_GROUP_ATTACK",GUILD_B_GROUP_ATTACK);
  tolua_constant(tolua_S,"GUILD_B_MAGIC",GUILD_B_MAGIC);
  tolua_constant(tolua_S,"GUILD_B_CURE",GUILD_B_CURE);
  tolua_constant(tolua_S,"GUILD_B_BLOCK",GUILD_B_BLOCK);
  tolua_constant(tolua_S,"GUILD_B_NUM",GUILD_B_NUM);
  tolua_constant(tolua_S,"GUILD_B_PROTECTOR",GUILD_B_PROTECTOR);
  tolua_constant(tolua_S,"GUILD_CW_TIME_NONE",GUILD_CW_TIME_NONE);
  tolua_constant(tolua_S,"GUILD_CW_TIME_5M",GUILD_CW_TIME_5M);
  tolua_constant(tolua_S,"GUILD_CW_TIME_10M",GUILD_CW_TIME_10M);
  tolua_constant(tolua_S,"GUILD_CW_TIME_30M",GUILD_CW_TIME_30M);
  tolua_constant(tolua_S,"GUILD_CW_TIME_END",GUILD_CW_TIME_END);
  tolua_constant(tolua_S,"GUILD_STATE_NONE",GUILD_STATE_NONE);
  tolua_constant(tolua_S,"GUILD_STATE_STOP_WELFARE",GUILD_STATE_STOP_WELFARE);
  tolua_constant(tolua_S,"GUILD_ENTER_OWNER",GUILD_ENTER_OWNER);
  tolua_constant(tolua_S,"GUILD_ENTER_ALLIANCE",GUILD_ENTER_ALLIANCE);
 tolua_constant(tolua_S,"GUILD_MAX_INTRUDER_NUM",GUILD_MAX_INTRUDER_NUM);
  tolua_constant(tolua_S,"GUILD_WAR_NONE",GUILD_WAR_NONE);
  tolua_constant(tolua_S,"GUILD_WAR_INTRUDER",GUILD_WAR_INTRUDER);
  tolua_constant(tolua_S,"GUILD_WAR_DEFENDER",GUILD_WAR_DEFENDER);
  tolua_constant(tolua_S,"GUILD_WAR_STAGE_NONE",GUILD_WAR_STAGE_NONE);
  tolua_constant(tolua_S,"GUILD_WAR_STAGE_DECLARE",GUILD_WAR_STAGE_DECLARE);
  tolua_constant(tolua_S,"GUILD_WAR_STAGE_BEGIN",GUILD_WAR_STAGE_BEGIN);
  tolua_constant(tolua_S,"GUILD_WAR_STAGE_END",GUILD_WAR_STAGE_END);
  tolua_constant(tolua_S,"GUILD_WAR_DEFENDER_NONE",GUILD_WAR_DEFENDER_NONE);
  tolua_constant(tolua_S,"GUILD_WAR_DEFENDER_WIN",GUILD_WAR_DEFENDER_WIN);
  tolua_constant(tolua_S,"GUILD_WAR_DEFENDER_LOSE",GUILD_WAR_DEFENDER_LOSE);
  tolua_constant(tolua_S,"G_B_UPGRADE_BY_NPC",G_B_UPGRADE_BY_NPC);
  tolua_constant(tolua_S,"G_B_UPGRADE_BY_PANEL",G_B_UPGRADE_BY_PANEL);
  tolua_constant(tolua_S,"GUILD_BUILDING_ENABLE",GUILD_BUILDING_ENABLE);
  tolua_constant(tolua_S,"GUILD_BUILDING_DISABLE",GUILD_BUILDING_DISABLE);
  tolua_constant(tolua_S,"GUILD_CS_UPGRADING",GUILD_CS_UPGRADING);
  tolua_constant(tolua_S,"GUILD_CS_UPDATE",GUILD_CS_UPDATE);
  tolua_constant(tolua_S,"GUILD_CS_DEL",GUILD_CS_DEL);
  tolua_constant(tolua_S,"sabNotEnroll",sabNotEnroll);
  tolua_constant(tolua_S,"sabEnrolled",sabEnrolled);
  tolua_constant(tolua_S,"sabOccupied",sabOccupied);
  tolua_constant(tolua_S,"GUILD_ACHI_BEGIN",GUILD_ACHI_BEGIN);
  tolua_constant(tolua_S,"GUILD_ACHI_NONE",GUILD_ACHI_NONE);
  tolua_constant(tolua_S,"GUILD_ACHI_MEMBER",GUILD_ACHI_MEMBER);
  tolua_constant(tolua_S,"GUILD_ACHI_ENEMY",GUILD_ACHI_ENEMY);
  tolua_constant(tolua_S,"GUILD_ACHI_ALLIANCE",GUILD_ACHI_ALLIANCE);
  tolua_constant(tolua_S,"GUILD_ACHI_TAKE_POS_1",GUILD_ACHI_TAKE_POS_1);
  tolua_constant(tolua_S,"GUILD_ACHI_TAKE_POS_2",GUILD_ACHI_TAKE_POS_2);
  tolua_constant(tolua_S,"GUILD_ACHI_TYPE_NUM",GUILD_ACHI_TYPE_NUM);
  tolua_constant(tolua_S,"GA_AWARD_NONE",GA_AWARD_NONE);
  tolua_constant(tolua_S,"GA_AWARD_POINT",GA_AWARD_POINT);
  tolua_constant(tolua_S,"GA_AWARD_EXP",GA_AWARD_EXP);
  tolua_constant(tolua_S,"GA_AWARD_ITEM",GA_AWARD_ITEM);
  tolua_constant(tolua_S,"GA_AWARD_TITLE",GA_AWARD_TITLE);
  tolua_constant(tolua_S,"GA_AWARD_NUM",GA_AWARD_NUM);
  tolua_constant(tolua_S,"avGuildWarCanOpen",avGuildWarCanOpen);
 tolua_cclass(tolua_S,"DIPLOMAT_DATA","DIPLOMAT_DATA","",NULL);
 tolua_beginmodule(tolua_S,"DIPLOMAT_DATA");
  tolua_variable(tolua_S,"dwGuildID",tolua_get_DIPLOMAT_DATA_unsigned_dwGuildID,tolua_set_DIPLOMAT_DATA_unsigned_dwGuildID);
  tolua_variable(tolua_S,"dwEndTime",tolua_get_DIPLOMAT_DATA_unsigned_dwEndTime,tolua_set_DIPLOMAT_DATA_unsigned_dwEndTime);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MS_GUILD_WAR_DATA","MS_GUILD_WAR_DATA","BASE_TRIGGER_NODE",NULL);
 tolua_beginmodule(tolua_S,"MS_GUILD_WAR_DATA");
  tolua_variable(tolua_S,"dwBeginDayTime",tolua_get_MS_GUILD_WAR_DATA_unsigned_dwBeginDayTime,tolua_set_MS_GUILD_WAR_DATA_unsigned_dwBeginDayTime);
  tolua_variable(tolua_S,"dwIntruderID",tolua_get_MS_GUILD_WAR_DATA_unsigned_dwIntruderID,tolua_set_MS_GUILD_WAR_DATA_unsigned_dwIntruderID);
  tolua_variable(tolua_S,"dwDefenderID",tolua_get_MS_GUILD_WAR_DATA_unsigned_dwDefenderID,tolua_set_MS_GUILD_WAR_DATA_unsigned_dwDefenderID);
  tolua_variable(tolua_S,"nWarResult",tolua_get_MS_GUILD_WAR_DATA_nWarResult,tolua_set_MS_GUILD_WAR_DATA_nWarResult);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"GUILD_DUNGEON","GUILD_DUNGEON","",NULL);
 tolua_beginmodule(tolua_S,"GUILD_DUNGEON");
  tolua_variable(tolua_S,"dwTemplateID",tolua_get_GUILD_DUNGEON_unsigned_dwTemplateID,tolua_set_GUILD_DUNGEON_unsigned_dwTemplateID);
  tolua_variable(tolua_S,"dwOwnerID",tolua_get_GUILD_DUNGEON_unsigned_dwOwnerID,tolua_set_GUILD_DUNGEON_unsigned_dwOwnerID);
  tolua_variable(tolua_S,"dwLeaderID",tolua_get_GUILD_DUNGEON_unsigned_dwLeaderID,tolua_set_GUILD_DUNGEON_unsigned_dwLeaderID);
  tolua_variable(tolua_S,"nCreateTime",tolua_get_GUILD_DUNGEON_nCreateTime,tolua_set_GUILD_DUNGEON_nCreateTime);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"GUILD_WAR_PERSONAL_ACHIEVEMENT","GUILD_WAR_PERSONAL_ACHIEVEMENT","",NULL);
 tolua_beginmodule(tolua_S,"GUILD_WAR_PERSONAL_ACHIEVEMENT");
  tolua_variable(tolua_S,"dwRoleID",tolua_get_GUILD_WAR_PERSONAL_ACHIEVEMENT_unsigned_dwRoleID,tolua_set_GUILD_WAR_PERSONAL_ACHIEVEMENT_unsigned_dwRoleID);
  tolua_variable(tolua_S,"nKillNum",tolua_get_GUILD_WAR_PERSONAL_ACHIEVEMENT_nKillNum,tolua_set_GUILD_WAR_PERSONAL_ACHIEVEMENT_nKillNum);
  tolua_variable(tolua_S,"nDeadCount",tolua_get_GUILD_WAR_PERSONAL_ACHIEVEMENT_nDeadCount,tolua_set_GUILD_WAR_PERSONAL_ACHIEVEMENT_nDeadCount);
  tolua_variable(tolua_S,"nSalary",tolua_get_GUILD_WAR_PERSONAL_ACHIEVEMENT_nSalary,tolua_set_GUILD_WAR_PERSONAL_ACHIEVEMENT_nSalary);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"GUILD_DB","GUILD_DB","",NULL);
 tolua_beginmodule(tolua_S,"GUILD_DB");
  tolua_variable(tolua_S,"dwGuildID",tolua_get_GUILD_DB_unsigned_dwGuildID,tolua_set_GUILD_DB_unsigned_dwGuildID);
  tolua_variable(tolua_S,"wVersion",tolua_get_GUILD_DB_unsigned_wVersion,tolua_set_GUILD_DB_unsigned_wVersion);
  tolua_array(tolua_S,"szGuildName",tolua_get_ms_guild_GUILD_DB_szGuildName,tolua_set_ms_guild_GUILD_DB_szGuildName);
  tolua_variable(tolua_S,"bySvrGroup",tolua_get_GUILD_DB_unsigned_bySvrGroup,tolua_set_GUILD_DB_unsigned_bySvrGroup);
  tolua_variable(tolua_S,"dwLeaderID",tolua_get_GUILD_DB_unsigned_dwLeaderID,tolua_set_GUILD_DB_unsigned_dwLeaderID);
  tolua_array(tolua_S,"szCreaterName",tolua_get_ms_guild_GUILD_DB_szCreaterName,tolua_set_ms_guild_GUILD_DB_szCreaterName);
  tolua_variable(tolua_S,"dwCreateTime",tolua_get_GUILD_DB_unsigned_dwCreateTime,tolua_set_GUILD_DB_unsigned_dwCreateTime);
  tolua_array(tolua_S,"szAnnounce",tolua_get_ms_guild_GUILD_DB_szAnnounce,tolua_set_ms_guild_GUILD_DB_szAnnounce);
  tolua_array(tolua_S,"szNotice",tolua_get_ms_guild_GUILD_DB_szNotice,tolua_set_ms_guild_GUILD_DB_szNotice);
  tolua_variable(tolua_S,"BlobBuffer",tolua_get_GUILD_DB_BlobBuffer,tolua_set_GUILD_DB_BlobBuffer);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CMsGuild","CMsGuild","",NULL);
 tolua_beginmodule(tolua_S,"CMsGuild");
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetID00
  tolua_function(tolua_S,"GetID",tolua_ms_guild_CMsGuild_GetID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetSvrGroup00
  tolua_function(tolua_S,"GetSvrGroup",tolua_ms_guild_CMsGuild_GetSvrGroup00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetLevel00
  tolua_function(tolua_S,"GetLevel",tolua_ms_guild_CMsGuild_GetLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetName00
  tolua_function(tolua_S,"GetName",tolua_ms_guild_CMsGuild_GetName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetCreaterName00
  tolua_function(tolua_S,"GetCreaterName",tolua_ms_guild_CMsGuild_GetCreaterName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetLeaderID00
  tolua_function(tolua_S,"GetLeaderID",tolua_ms_guild_CMsGuild_GetLeaderID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetCreateTime00
  tolua_function(tolua_S,"GetCreateTime",tolua_ms_guild_CMsGuild_GetCreateTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetAnnounce00
  tolua_function(tolua_S,"GetAnnounce",tolua_ms_guild_CMsGuild_GetAnnounce00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SetNotice00
  tolua_function(tolua_S,"SetNotice",tolua_ms_guild_CMsGuild_SetNotice00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetNotice00
  tolua_function(tolua_S,"GetNotice",tolua_ms_guild_CMsGuild_GetNotice00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetStorage00
  tolua_function(tolua_S,"GetStorage",tolua_ms_guild_CMsGuild_GetStorage00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetLvlRankNode00
  tolua_function(tolua_S,"GetLvlRankNode",tolua_ms_guild_CMsGuild_GetLvlRankNode00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetMoney00
  tolua_function(tolua_S,"GetMoney",tolua_ms_guild_CMsGuild_GetMoney00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddMoney00
  tolua_function(tolua_S,"AddMoney",tolua_ms_guild_CMsGuild_AddMoney00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SubMoney00
  tolua_function(tolua_S,"SubMoney",tolua_ms_guild_CMsGuild_SubMoney00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetWood00
  tolua_function(tolua_S,"GetWood",tolua_ms_guild_CMsGuild_GetWood00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddWood00
  tolua_function(tolua_S,"AddWood",tolua_ms_guild_CMsGuild_AddWood00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SubWood00
  tolua_function(tolua_S,"SubWood",tolua_ms_guild_CMsGuild_SubWood00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetHerb00
  tolua_function(tolua_S,"GetHerb",tolua_ms_guild_CMsGuild_GetHerb00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddHerb00
  tolua_function(tolua_S,"AddHerb",tolua_ms_guild_CMsGuild_AddHerb00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SubHerb00
  tolua_function(tolua_S,"SubHerb",tolua_ms_guild_CMsGuild_SubHerb00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetCryStal00
  tolua_function(tolua_S,"GetCryStal",tolua_ms_guild_CMsGuild_GetCryStal00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddCrystal00
  tolua_function(tolua_S,"AddCrystal",tolua_ms_guild_CMsGuild_AddCrystal00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SubCrystal00
  tolua_function(tolua_S,"SubCrystal",tolua_ms_guild_CMsGuild_SubCrystal00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetSilver00
  tolua_function(tolua_S,"GetSilver",tolua_ms_guild_CMsGuild_GetSilver00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddSilver00
  tolua_function(tolua_S,"AddSilver",tolua_ms_guild_CMsGuild_AddSilver00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SubSilver00
  tolua_function(tolua_S,"SubSilver",tolua_ms_guild_CMsGuild_SubSilver00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetVariable00
  tolua_function(tolua_S,"GetVariable",tolua_ms_guild_CMsGuild_GetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SetVariable00
  tolua_function(tolua_S,"SetVariable",tolua_ms_guild_CMsGuild_SetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetStorageRightByPosition00
  tolua_function(tolua_S,"GetStorageRightByPosition",tolua_ms_guild_CMsGuild_GetStorageRightByPosition00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_CanGuildChat00
  tolua_function(tolua_S,"CanGuildChat",tolua_ms_guild_CMsGuild_CanGuildChat00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddGuildEvent00
  tolua_function(tolua_S,"AddGuildEvent",tolua_ms_guild_CMsGuild_AddGuildEvent00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetMemberNum00
  tolua_function(tolua_S,"GetMemberNum",tolua_ms_guild_CMsGuild_GetMemberNum00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_IsMember00
  tolua_function(tolua_S,"IsMember",tolua_ms_guild_CMsGuild_IsMember00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddMember00
  tolua_function(tolua_S,"AddMember",tolua_ms_guild_CMsGuild_AddMember00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_DelMember00
  tolua_function(tolua_S,"DelMember",tolua_ms_guild_CMsGuild_DelMember00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetMember00
  tolua_function(tolua_S,"GetMember",tolua_ms_guild_CMsGuild_GetMember00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetMemberNumInAPost00
  tolua_function(tolua_S,"GetMemberNumInAPost",tolua_ms_guild_CMsGuild_GetMemberNumInAPost00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_BroadcastMail00
  tolua_function(tolua_S,"BroadcastMail",tolua_ms_guild_CMsGuild_BroadcastMail00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_BeginUpgradeWelfareBuffer00
  tolua_function(tolua_S,"BeginUpgradeWelfareBuffer",tolua_ms_guild_CMsGuild_BeginUpgradeWelfareBuffer00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_CancelUpgradeWelfareBuffer00
  tolua_function(tolua_S,"CancelUpgradeWelfareBuffer",tolua_ms_guild_CMsGuild_CancelUpgradeWelfareBuffer00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_BeginUpgradeBuilding00
  tolua_function(tolua_S,"BeginUpgradeBuilding",tolua_ms_guild_CMsGuild_BeginUpgradeBuilding00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_CancelUpgradeBuilding00
  tolua_function(tolua_S,"CancelUpgradeBuilding",tolua_ms_guild_CMsGuild_CancelUpgradeBuilding00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetEnemyNum00
  tolua_function(tolua_S,"GetEnemyNum",tolua_ms_guild_CMsGuild_GetEnemyNum00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetAllianceNum00
  tolua_function(tolua_S,"GetAllianceNum",tolua_ms_guild_CMsGuild_GetAllianceNum00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_IsAlliance00
  tolua_function(tolua_S,"IsAlliance",tolua_ms_guild_CMsGuild_IsAlliance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_IsEnemy00
  tolua_function(tolua_S,"IsEnemy",tolua_ms_guild_CMsGuild_IsEnemy00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddAlliance00
  tolua_function(tolua_S,"AddAlliance",tolua_ms_guild_CMsGuild_AddAlliance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_DelAlliance00
  tolua_function(tolua_S,"DelAlliance",tolua_ms_guild_CMsGuild_DelAlliance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddEnemy00
  tolua_function(tolua_S,"AddEnemy",tolua_ms_guild_CMsGuild_AddEnemy00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_DelEnemy00
  tolua_function(tolua_S,"DelEnemy",tolua_ms_guild_CMsGuild_DelEnemy00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetEnemyDataByIndex00
  tolua_function(tolua_S,"GetEnemyDataByIndex",tolua_ms_guild_CMsGuild_GetEnemyDataByIndex00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetAllianceDataByIndex00
  tolua_function(tolua_S,"GetAllianceDataByIndex",tolua_ms_guild_CMsGuild_GetAllianceDataByIndex00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_AddDungeon00
  tolua_function(tolua_S,"AddDungeon",tolua_ms_guild_CMsGuild_AddDungeon00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_DelDungeon00
  tolua_function(tolua_S,"DelDungeon",tolua_ms_guild_CMsGuild_DelDungeon00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_CheckSameDungeonType00
  tolua_function(tolua_S,"CheckSameDungeonType",tolua_ms_guild_CMsGuild_CheckSameDungeonType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_FindDunGeon00
  tolua_function(tolua_S,"FindDunGeon",tolua_ms_guild_CMsGuild_FindDunGeon00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_FilterDungeon00
  tolua_function(tolua_S,"FilterDungeon",tolua_ms_guild_CMsGuild_FilterDungeon00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetSabacEnrollTime00
  tolua_function(tolua_S,"GetSabacEnrollTime",tolua_ms_guild_CMsGuild_GetSabacEnrollTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_EnrollSabac00
  tolua_function(tolua_S,"EnrollSabac",tolua_ms_guild_CMsGuild_EnrollSabac00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_OccupySabac00
  tolua_function(tolua_S,"OccupySabac",tolua_ms_guild_CMsGuild_OccupySabac00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_IsOccupiedSabac00
  tolua_function(tolua_S,"IsOccupiedSabac",tolua_ms_guild_CMsGuild_IsOccupiedSabac00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_IsEnrolledSabac00
  tolua_function(tolua_S,"IsEnrolledSabac",tolua_ms_guild_CMsGuild_IsEnrolledSabac00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_CheckCharacter00
  tolua_function(tolua_S,"CheckCharacter",tolua_ms_guild_CMsGuild_CheckCharacter00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetWarCharacter00
  tolua_function(tolua_S,"GetWarCharacter",tolua_ms_guild_CMsGuild_GetWarCharacter00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_SetWarCharacter00
  tolua_function(tolua_S,"SetWarCharacter",tolua_ms_guild_CMsGuild_SetWarCharacter00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_ClearWarCharacter00
  tolua_function(tolua_S,"ClearWarCharacter",tolua_ms_guild_CMsGuild_ClearWarCharacter00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_ClearIntruder00
  tolua_function(tolua_S,"ClearIntruder",tolua_ms_guild_CMsGuild_ClearIntruder00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_GetIntruderNum00
  tolua_function(tolua_S,"GetIntruderNum",tolua_ms_guild_CMsGuild_GetIntruderNum00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_FirstIntruder00
  tolua_function(tolua_S,"FirstIntruder",tolua_ms_guild_CMsGuild_FirstIntruder00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_NextIntruder00
  tolua_function(tolua_S,"NextIntruder",tolua_ms_guild_CMsGuild_NextIntruder00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_LuaBroadcastMsgNotifyType00
  tolua_function(tolua_S,"LuaBroadcastMsgNotifyType",tolua_ms_guild_CMsGuild_LuaBroadcastMsgNotifyType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_LuaAddProtectionTime00
  tolua_function(tolua_S,"LuaAddProtectionTime",tolua_ms_guild_CMsGuild_LuaAddProtectionTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_LuaLeaveGuild00
  tolua_function(tolua_S,"LuaLeaveGuild",tolua_ms_guild_CMsGuild_LuaLeaveGuild00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_LuaBroadcastJoinWar00
  tolua_function(tolua_S,"LuaBroadcastJoinWar",tolua_ms_guild_CMsGuild_LuaBroadcastJoinWar00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_CMsGuild_LuaAddBuilding00
  tolua_function(tolua_S,"LuaAddBuilding",tolua_ms_guild_CMsGuild_LuaAddBuilding00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
#ifndef TOLUA_DISABLE_tolua_ms_guild_GetMaxOfferInPosition00
 tolua_function(tolua_S,"GetMaxOfferInPosition",tolua_ms_guild_GetMaxOfferInPosition00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ms_guild (lua_State* tolua_S) {
 return tolua_ms_guild_open(tolua_S);
};
#endif

