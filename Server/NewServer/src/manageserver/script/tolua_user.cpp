/*
** Lua binding: user
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_user_open (lua_State* tolua_S);

#include "client/user.h"
#include "client/usermgr.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"BASE_LIST_NODE");
 tolua_usertype(tolua_S,"UINT64");
 tolua_usertype(tolua_S,"CUserMgr");
 tolua_usertype(tolua_S,"MS_USER");
}

/* get function: szUserName of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_szUserName
static int tolua_get_MS_USER_szUserName(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szUserName'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szUserName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szUserName of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_szUserName
static int tolua_set_MS_USER_szUserName(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szUserName'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szUserName,(const char*)tolua_tostring(tolua_S,2,0),USER_NAME_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwCliSessionID of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_unsigned_dwCliSessionID
static int tolua_get_MS_USER_unsigned_dwCliSessionID(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwCliSessionID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwCliSessionID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwCliSessionID of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_unsigned_dwCliSessionID
static int tolua_set_MS_USER_unsigned_dwCliSessionID(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwCliSessionID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwCliSessionID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwClientIp of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_unsigned_dwClientIp
static int tolua_get_MS_USER_unsigned_dwClientIp(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwClientIp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwClientIp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwClientIp of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_unsigned_dwClientIp
static int tolua_set_MS_USER_unsigned_dwClientIp(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwClientIp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwClientIp = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bIpWhiteList of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_bIpWhiteList
static int tolua_get_MS_USER_bIpWhiteList(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bIpWhiteList'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bIpWhiteList);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bIpWhiteList of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_bIpWhiteList
static int tolua_set_MS_USER_bIpWhiteList(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bIpWhiteList'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bIpWhiteList = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bUserWhiteList of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_bUserWhiteList
static int tolua_get_MS_USER_bUserWhiteList(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bUserWhiteList'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bUserWhiteList);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bUserWhiteList of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_bUserWhiteList
static int tolua_set_MS_USER_bUserWhiteList(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bUserWhiteList'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bUserWhiteList = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szMac of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_user_MS_USER_szMac
static int tolua_get_user_MS_USER_szMac(lua_State* tolua_S)
{
 int tolua_index;
  MS_USER* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (MS_USER*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAC_ADDRESS_LEN)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->szMac[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szMac of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_user_MS_USER_szMac
static int tolua_set_user_MS_USER_szMac(lua_State* tolua_S)
{
 int tolua_index;
  MS_USER* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (MS_USER*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAC_ADDRESS_LEN)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->szMac[tolua_index] = ((  char)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: WaitListNode of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_WaitListNode
static int tolua_get_MS_USER_WaitListNode(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WaitListNode'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->WaitListNode,"BASE_LIST_NODE");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: WaitListNode of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_WaitListNode
static int tolua_set_MS_USER_WaitListNode(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WaitListNode'",NULL);
 if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"BASE_LIST_NODE",0,&tolua_err)))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->WaitListNode = *((BASE_LIST_NODE*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwLoginTime of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_unsigned_dwLoginTime
static int tolua_get_MS_USER_unsigned_dwLoginTime(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwLoginTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwLoginTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwLoginTime of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_unsigned_dwLoginTime
static int tolua_set_MS_USER_unsigned_dwLoginTime(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwLoginTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwLoginTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szOASessionID of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_szOASessionID
static int tolua_get_MS_USER_szOASessionID(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szOASessionID'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szOASessionID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szOASessionID of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_szOASessionID
static int tolua_set_MS_USER_szOASessionID(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szOASessionID'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szOASessionID,(const char*)tolua_tostring(tolua_S,2,0),OA_SESSION_ID_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szPGT of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_szPGT
static int tolua_get_MS_USER_szPGT(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szPGT'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szPGT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szPGT of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_szPGT
static int tolua_set_MS_USER_szPGT(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szPGT'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szPGT,(const char*)tolua_tostring(tolua_S,2,0),OA_PGT_FIELD_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bAdult of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_unsigned_bAdult
static int tolua_get_MS_USER_unsigned_bAdult(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAdult'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->bAdult);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bAdult of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_unsigned_bAdult
static int tolua_set_MS_USER_unsigned_bAdult(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAdult'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bAdult = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byFcmState of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_unsigned_byFcmState
static int tolua_get_MS_USER_unsigned_byFcmState(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byFcmState'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byFcmState);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byFcmState of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_unsigned_byFcmState
static int tolua_set_MS_USER_unsigned_byFcmState(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byFcmState'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byFcmState = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: eState of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_eState
static int tolua_get_MS_USER_eState(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'eState'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->eState);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: eState of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_eState
static int tolua_set_MS_USER_eState(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'eState'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->eState = ((EUserState) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: qwTimer of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_qwTimer
static int tolua_get_MS_USER_qwTimer(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'qwTimer'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->qwTimer,"UINT64");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: qwTimer of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_qwTimer
static int tolua_set_MS_USER_qwTimer(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'qwTimer'",NULL);
 if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"UINT64",0,&tolua_err)))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->qwTimer = *((UINT64*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwCurRoleID of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_unsigned_dwCurRoleID
static int tolua_get_MS_USER_unsigned_dwCurRoleID(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwCurRoleID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwCurRoleID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwCurRoleID of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_unsigned_dwCurRoleID
static int tolua_set_MS_USER_unsigned_dwCurRoleID(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwCurRoleID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwCurRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nShutdownType of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_nShutdownType
static int tolua_get_MS_USER_nShutdownType(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nShutdownType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nShutdownType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nShutdownType of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_nShutdownType
static int tolua_set_MS_USER_nShutdownType(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nShutdownType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nShutdownType = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bKicked of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_bKicked
static int tolua_get_MS_USER_bKicked(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bKicked'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bKicked);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bKicked of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_bKicked
static int tolua_set_MS_USER_bKicked(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bKicked'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bKicked = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bFreeMode of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_bFreeMode
static int tolua_get_MS_USER_bFreeMode(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bFreeMode'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bFreeMode);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bFreeMode of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_bFreeMode
static int tolua_set_MS_USER_bFreeMode(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bFreeMode'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bFreeMode = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwFreeModeLastCheckTime of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_unsigned_dwFreeModeLastCheckTime
static int tolua_get_MS_USER_unsigned_dwFreeModeLastCheckTime(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwFreeModeLastCheckTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwFreeModeLastCheckTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwFreeModeLastCheckTime of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_unsigned_dwFreeModeLastCheckTime
static int tolua_set_MS_USER_unsigned_dwFreeModeLastCheckTime(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwFreeModeLastCheckTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwFreeModeLastCheckTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nDianquan of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_nDianquan
static int tolua_get_MS_USER_nDianquan(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nDianquan'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nDianquan);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nDianquan of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_nDianquan
static int tolua_set_MS_USER_nDianquan(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nDianquan'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nDianquan = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nTimeLeft of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_nTimeLeft
static int tolua_get_MS_USER_nTimeLeft(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTimeLeft'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nTimeLeft);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nTimeLeft of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_nTimeLeft
static int tolua_set_MS_USER_nTimeLeft(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTimeLeft'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nTimeLeft = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwBeginTime of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_get_MS_USER_unsigned_dwBeginTime
static int tolua_get_MS_USER_unsigned_dwBeginTime(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwBeginTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwBeginTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwBeginTime of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_set_MS_USER_unsigned_dwBeginTime
static int tolua_set_MS_USER_unsigned_dwBeginTime(lua_State* tolua_S)
{
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwBeginTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwBeginTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFreeMode of class  MS_USER */
#ifndef TOLUA_DISABLE_tolua_user_MS_USER_SetFreeMode00
static int tolua_user_MS_USER_SetFreeMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MS_USER",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MS_USER* self = (MS_USER*)  tolua_tousertype(tolua_S,1,0);
   bool fm = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFreeMode'", NULL);
#endif
 {
  self->SetFreeMode(fm);
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

/* method: GetInstance of class  CUserMgr */
#ifndef TOLUA_DISABLE_tolua_user_CUserMgr_GetInstance00
static int tolua_user_CUserMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CUserMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CUserMgr& tolua_ret = (CUserMgr&)  CUserMgr::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CUserMgr");
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

/* method: Count of class  CUserMgr */
#ifndef TOLUA_DISABLE_tolua_user_CUserMgr_Count00
static int tolua_user_CUserMgr_Count00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CUserMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CUserMgr* self = (CUserMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Count'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->Count();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Count'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCountPerGroup of class  CUserMgr */
#ifndef TOLUA_DISABLE_tolua_user_CUserMgr_GetCountPerGroup00
static int tolua_user_CUserMgr_GetCountPerGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CUserMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CUserMgr* self = (CUserMgr*)  tolua_tousertype(tolua_S,1,0);
  signed int nServerGroup = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCountPerGroup'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetCountPerGroup(nServerGroup);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCountPerGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCountByIP of class  CUserMgr */
#ifndef TOLUA_DISABLE_tolua_user_CUserMgr_GetCountByIP00
static int tolua_user_CUserMgr_GetCountByIP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CUserMgr",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CUserMgr* self = (CUserMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* pcszIDAddress = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCountByIP'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetCountByIP(pcszIDAddress);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCountByIP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_user_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"USER_STATE_INVALID",USER_STATE_INVALID);
  tolua_constant(tolua_S,"USER_STATE_AUTHED",USER_STATE_AUTHED);
  tolua_constant(tolua_S,"USER_STATE_QUEUEFINISHED",USER_STATE_QUEUEFINISHED);
  tolua_constant(tolua_S,"USER_STATE_LOGIN_WAIT_CREATE_SCENE",USER_STATE_LOGIN_WAIT_CREATE_SCENE);
  tolua_constant(tolua_S,"USER_STATE_LOGIN_PRE_ENTER_GS",USER_STATE_LOGIN_PRE_ENTER_GS);
  tolua_constant(tolua_S,"USER_STATE_LOGIN_GSREADY",USER_STATE_LOGIN_GSREADY);
  tolua_constant(tolua_S,"USER_STATE_INGAME",USER_STATE_INGAME);
  tolua_constant(tolua_S,"USER_STATE_EXIT_GS_PREENTER",USER_STATE_EXIT_GS_PREENTER);
  tolua_constant(tolua_S,"USER_STATE_EXIT_GS",USER_STATE_EXIT_GS);
  tolua_constant(tolua_S,"USER_STATE_EXIT_2GS",USER_STATE_EXIT_2GS);
  tolua_constant(tolua_S,"USER_STATE_WAIT_EXIT_DB",USER_STATE_WAIT_EXIT_DB);
  tolua_constant(tolua_S,"USER_STATE_EXIT_DB",USER_STATE_EXIT_DB);
  tolua_constant(tolua_S,"USER_STATE_EXIT_GS_RETURN",USER_STATE_EXIT_GS_RETURN);
  tolua_constant(tolua_S,"USER_STATE_EXIT_DB_RETURN",USER_STATE_EXIT_DB_RETURN);
  tolua_constant(tolua_S,"USER_STATE_JUMP_EXIT_TGT",USER_STATE_JUMP_EXIT_TGT);
  tolua_constant(tolua_S,"USER_STATE_JUMP_WAIT_CREATE_SCENE",USER_STATE_JUMP_WAIT_CREATE_SCENE);
  tolua_constant(tolua_S,"USER_STATE_JUMP_PRE_ENTER_GS",USER_STATE_JUMP_PRE_ENTER_GS);
  tolua_constant(tolua_S,"USER_STATE_JUMP_EXIT_SRC",USER_STATE_JUMP_EXIT_SRC);
  tolua_constant(tolua_S,"USER_STATE_JUMP_ENTER_TARGET",USER_STATE_JUMP_ENTER_TARGET);
  tolua_constant(tolua_S,"USER_STATE_JUMP_GSREADY",USER_STATE_JUMP_GSREADY);
 tolua_cclass(tolua_S,"MS_USER","MS_USER","",NULL);
 tolua_beginmodule(tolua_S,"MS_USER");
  tolua_variable(tolua_S,"szUserName",tolua_get_MS_USER_szUserName,tolua_set_MS_USER_szUserName);
  tolua_variable(tolua_S,"dwCliSessionID",tolua_get_MS_USER_unsigned_dwCliSessionID,tolua_set_MS_USER_unsigned_dwCliSessionID);
  tolua_variable(tolua_S,"dwClientIp",tolua_get_MS_USER_unsigned_dwClientIp,tolua_set_MS_USER_unsigned_dwClientIp);
  tolua_variable(tolua_S,"bIpWhiteList",tolua_get_MS_USER_bIpWhiteList,tolua_set_MS_USER_bIpWhiteList);
  tolua_variable(tolua_S,"bUserWhiteList",tolua_get_MS_USER_bUserWhiteList,tolua_set_MS_USER_bUserWhiteList);
  tolua_array(tolua_S,"szMac",tolua_get_user_MS_USER_szMac,tolua_set_user_MS_USER_szMac);
  tolua_variable(tolua_S,"WaitListNode",tolua_get_MS_USER_WaitListNode,tolua_set_MS_USER_WaitListNode);
  tolua_variable(tolua_S,"dwLoginTime",tolua_get_MS_USER_unsigned_dwLoginTime,tolua_set_MS_USER_unsigned_dwLoginTime);
  tolua_variable(tolua_S,"szOASessionID",tolua_get_MS_USER_szOASessionID,tolua_set_MS_USER_szOASessionID);
  tolua_variable(tolua_S,"szPGT",tolua_get_MS_USER_szPGT,tolua_set_MS_USER_szPGT);
  tolua_variable(tolua_S,"bAdult",tolua_get_MS_USER_unsigned_bAdult,tolua_set_MS_USER_unsigned_bAdult);
  tolua_variable(tolua_S,"byFcmState",tolua_get_MS_USER_unsigned_byFcmState,tolua_set_MS_USER_unsigned_byFcmState);
  tolua_variable(tolua_S,"eState",tolua_get_MS_USER_eState,tolua_set_MS_USER_eState);
  tolua_variable(tolua_S,"qwTimer",tolua_get_MS_USER_qwTimer,tolua_set_MS_USER_qwTimer);
  tolua_variable(tolua_S,"dwCurRoleID",tolua_get_MS_USER_unsigned_dwCurRoleID,tolua_set_MS_USER_unsigned_dwCurRoleID);
  tolua_variable(tolua_S,"nShutdownType",tolua_get_MS_USER_nShutdownType,tolua_set_MS_USER_nShutdownType);
  tolua_variable(tolua_S,"bKicked",tolua_get_MS_USER_bKicked,tolua_set_MS_USER_bKicked);
  tolua_variable(tolua_S,"bFreeMode",tolua_get_MS_USER_bFreeMode,tolua_set_MS_USER_bFreeMode);
  tolua_variable(tolua_S,"dwFreeModeLastCheckTime",tolua_get_MS_USER_unsigned_dwFreeModeLastCheckTime,tolua_set_MS_USER_unsigned_dwFreeModeLastCheckTime);
  tolua_variable(tolua_S,"nDianquan",tolua_get_MS_USER_nDianquan,tolua_set_MS_USER_nDianquan);
  tolua_variable(tolua_S,"nTimeLeft",tolua_get_MS_USER_nTimeLeft,tolua_set_MS_USER_nTimeLeft);
  tolua_variable(tolua_S,"dwBeginTime",tolua_get_MS_USER_unsigned_dwBeginTime,tolua_set_MS_USER_unsigned_dwBeginTime);
#ifndef TOLUA_DISABLE_tolua_user_MS_USER_SetFreeMode00
  tolua_function(tolua_S,"SetFreeMode",tolua_user_MS_USER_SetFreeMode00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CUserMgr","CUserMgr","",NULL);
 tolua_beginmodule(tolua_S,"CUserMgr");
#ifndef TOLUA_DISABLE_tolua_user_CUserMgr_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_user_CUserMgr_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_user_CUserMgr_Count00
  tolua_function(tolua_S,"Count",tolua_user_CUserMgr_Count00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_user_CUserMgr_GetCountPerGroup00
  tolua_function(tolua_S,"GetCountPerGroup",tolua_user_CUserMgr_GetCountPerGroup00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_user_CUserMgr_GetCountByIP00
  tolua_function(tolua_S,"GetCountByIP",tolua_user_CUserMgr_GetCountByIP00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_user (lua_State* tolua_S) {
 return tolua_user_open(tolua_S);
};
#endif

