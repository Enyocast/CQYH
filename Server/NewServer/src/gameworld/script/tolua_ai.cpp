/*
** Lua binding: ai
** Generated automatically by tolua++-1.0.92 on 09/29/25 00:22:31.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_ai_open (lua_State* tolua_S);

#include "../../inc/baselib/btnod.h"
#include "../../inc/gameworld/bt_action.h"
#include "../../inc/gameworld/ai_signal.h"
#include "../../../Common/define/ai_def.h"
#include "ai_processor.h"
#include "../../../common/fusion/inc/ai_data.h"
#include "ai_data.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCharacter");
 tolua_usertype(tolua_S,"BASE_LIST_NODE");
 tolua_usertype(tolua_S,"CTabFile");
 tolua_usertype(tolua_S,"NEW_AI_DATA");
 tolua_usertype(tolua_S,"CAIProcessor");
 tolua_usertype(tolua_S,"stSignal");
}

/* get function: nType of class  stSignal */
#ifndef TOLUA_DISABLE_tolua_get_stSignal_nType
static int tolua_get_stSignal_nType(lua_State* tolua_S)
{
  stSignal* self = (stSignal*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nType of class  stSignal */
#ifndef TOLUA_DISABLE_tolua_set_stSignal_nType
static int tolua_set_stSignal_nType(lua_State* tolua_S)
{
  stSignal* self = (stSignal*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nType = (( signed char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nParam of class  stSignal */
#ifndef TOLUA_DISABLE_tolua_get_stSignal_nParam
static int tolua_get_stSignal_nParam(lua_State* tolua_S)
{
  stSignal* self = (stSignal*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nParam'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nParam);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nParam of class  stSignal */
#ifndef TOLUA_DISABLE_tolua_set_stSignal_nParam
static int tolua_set_stSignal_nParam(lua_State* tolua_S)
{
  stSignal* self = (stSignal*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nParam'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nParam = (( signed char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nRemainTimes of class  stSignal */
#ifndef TOLUA_DISABLE_tolua_get_stSignal_nRemainTimes
static int tolua_get_stSignal_nRemainTimes(lua_State* tolua_S)
{
  stSignal* self = (stSignal*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRemainTimes'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nRemainTimes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nRemainTimes of class  stSignal */
#ifndef TOLUA_DISABLE_tolua_set_stSignal_nRemainTimes
static int tolua_set_stSignal_nRemainTimes(lua_State* tolua_S)
{
  stSignal* self = (stSignal*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRemainTimes'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nRemainTimes = (( signed short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nExpiredFrame of class  stSignal */
#ifndef TOLUA_DISABLE_tolua_get_stSignal_nExpiredFrame
static int tolua_get_stSignal_nExpiredFrame(lua_State* tolua_S)
{
  stSignal* self = (stSignal*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nExpiredFrame'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nExpiredFrame);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nExpiredFrame of class  stSignal */
#ifndef TOLUA_DISABLE_tolua_set_stSignal_nExpiredFrame
static int tolua_set_stSignal_nExpiredFrame(lua_State* tolua_S)
{
  stSignal* self = (stSignal*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nExpiredFrame'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nExpiredFrame = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwIssuerID of class  stSignal */
#ifndef TOLUA_DISABLE_tolua_get_stSignal_unsigned_dwIssuerID
static int tolua_get_stSignal_unsigned_dwIssuerID(lua_State* tolua_S)
{
  stSignal* self = (stSignal*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwIssuerID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwIssuerID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwIssuerID of class  stSignal */
#ifndef TOLUA_DISABLE_tolua_set_stSignal_unsigned_dwIssuerID
static int tolua_set_stSignal_unsigned_dwIssuerID(lua_State* tolua_S)
{
  stSignal* self = (stSignal*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwIssuerID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwIssuerID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ListNode of class  stSignal */
#ifndef TOLUA_DISABLE_tolua_get_stSignal_ListNode
static int tolua_get_stSignal_ListNode(lua_State* tolua_S)
{
  stSignal* self = (stSignal*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ListNode'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->ListNode,"BASE_LIST_NODE");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ListNode of class  stSignal */
#ifndef TOLUA_DISABLE_tolua_set_stSignal_ListNode
static int tolua_set_stSignal_ListNode(lua_State* tolua_S)
{
  stSignal* self = (stSignal*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ListNode'",NULL);
 if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"BASE_LIST_NODE",0,&tolua_err)))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ListNode = *((BASE_LIST_NODE*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nAIID of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nAIID
static int tolua_get_NEW_AI_DATA_nAIID(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nAIID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nAIID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nAIID of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nAIID
static int tolua_set_NEW_AI_DATA_nAIID(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nAIID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nAIID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szScriptName of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_szScriptName
static int tolua_get_NEW_AI_DATA_szScriptName(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szScriptName'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szScriptName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szScriptName of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_szScriptName
static int tolua_set_NEW_AI_DATA_szScriptName(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szScriptName'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szScriptName,(const char*)tolua_tostring(tolua_S,2,0),SCRIPT_NAME_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nWalkSpeed of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nWalkSpeed
static int tolua_get_NEW_AI_DATA_nWalkSpeed(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nWalkSpeed'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nWalkSpeed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nWalkSpeed of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nWalkSpeed
static int tolua_set_NEW_AI_DATA_nWalkSpeed(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nWalkSpeed'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nWalkSpeed = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nRunSpeed of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nRunSpeed
static int tolua_get_NEW_AI_DATA_nRunSpeed(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRunSpeed'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nRunSpeed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nRunSpeed of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nRunSpeed
static int tolua_set_NEW_AI_DATA_nRunSpeed(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRunSpeed'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nRunSpeed = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nRotateSpeed of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nRotateSpeed
static int tolua_get_NEW_AI_DATA_nRotateSpeed(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRotateSpeed'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nRotateSpeed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nRotateSpeed of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nRotateSpeed
static int tolua_set_NEW_AI_DATA_nRotateSpeed(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRotateSpeed'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nRotateSpeed = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bPatrol of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_bPatrol
static int tolua_get_NEW_AI_DATA_bPatrol(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bPatrol'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bPatrol);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bPatrol of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_bPatrol
static int tolua_set_NEW_AI_DATA_bPatrol(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bPatrol'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bPatrol = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bFollow of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_bFollow
static int tolua_get_NEW_AI_DATA_bFollow(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bFollow'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bFollow);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bFollow of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_bFollow
static int tolua_set_NEW_AI_DATA_bFollow(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bFollow'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bFollow = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bCanRun of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_bCanRun
static int tolua_get_NEW_AI_DATA_bCanRun(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bCanRun'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bCanRun);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bCanRun of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_bCanRun
static int tolua_set_NEW_AI_DATA_bCanRun(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bCanRun'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bCanRun = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bAlwaysRun of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_bAlwaysRun
static int tolua_get_NEW_AI_DATA_bAlwaysRun(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAlwaysRun'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bAlwaysRun);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bAlwaysRun of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_bAlwaysRun
static int tolua_set_NEW_AI_DATA_bAlwaysRun(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAlwaysRun'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bAlwaysRun = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nScanEnemyRange of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nScanEnemyRange
static int tolua_get_NEW_AI_DATA_nScanEnemyRange(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nScanEnemyRange'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nScanEnemyRange);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nScanEnemyRange of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nScanEnemyRange
static int tolua_set_NEW_AI_DATA_nScanEnemyRange(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nScanEnemyRange'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nScanEnemyRange = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nScanFriendRange of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nScanFriendRange
static int tolua_get_NEW_AI_DATA_nScanFriendRange(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nScanFriendRange'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nScanFriendRange);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nScanFriendRange of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nScanFriendRange
static int tolua_set_NEW_AI_DATA_nScanFriendRange(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nScanFriendRange'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nScanFriendRange = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nChaseRange of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nChaseRange
static int tolua_get_NEW_AI_DATA_nChaseRange(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nChaseRange'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nChaseRange);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nChaseRange of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nChaseRange
static int tolua_set_NEW_AI_DATA_nChaseRange(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nChaseRange'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nChaseRange = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nPreferDistance of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nPreferDistance
static int tolua_get_NEW_AI_DATA_nPreferDistance(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nPreferDistance'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nPreferDistance);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nPreferDistance of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nPreferDistance
static int tolua_set_NEW_AI_DATA_nPreferDistance(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nPreferDistance'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nPreferDistance = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nWithdrawThreshold of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nWithdrawThreshold
static int tolua_get_NEW_AI_DATA_nWithdrawThreshold(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nWithdrawThreshold'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nWithdrawThreshold);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nWithdrawThreshold of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nWithdrawThreshold
static int tolua_set_NEW_AI_DATA_nWithdrawThreshold(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nWithdrawThreshold'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nWithdrawThreshold = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nChaseThreshold of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nChaseThreshold
static int tolua_get_NEW_AI_DATA_nChaseThreshold(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nChaseThreshold'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nChaseThreshold);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nChaseThreshold of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nChaseThreshold
static int tolua_set_NEW_AI_DATA_nChaseThreshold(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nChaseThreshold'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nChaseThreshold = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nChaseDelayTime of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nChaseDelayTime
static int tolua_get_NEW_AI_DATA_nChaseDelayTime(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nChaseDelayTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nChaseDelayTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nChaseDelayTime of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nChaseDelayTime
static int tolua_set_NEW_AI_DATA_nChaseDelayTime(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nChaseDelayTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nChaseDelayTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nInitAuraID of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_ai_NEW_AI_DATA_nInitAuraID
static int tolua_get_ai_NEW_AI_DATA_nInitAuraID(lua_State* tolua_S)
{
 int tolua_index;
  NEW_AI_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (NEW_AI_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_AI_INIT_AURA_COUNT)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nInitAuraID[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nInitAuraID of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_ai_NEW_AI_DATA_nInitAuraID
static int tolua_set_ai_NEW_AI_DATA_nInitAuraID(lua_State* tolua_S)
{
 int tolua_index;
  NEW_AI_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (NEW_AI_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_AI_INIT_AURA_COUNT)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->nInitAuraID[tolua_index] = (( signed int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nLiveTime of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nLiveTime
static int tolua_get_NEW_AI_DATA_nLiveTime(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLiveTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nLiveTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nLiveTime of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nLiveTime
static int tolua_set_NEW_AI_DATA_nLiveTime(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLiveTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nLiveTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bDisappearOnTimeout of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_bDisappearOnTimeout
static int tolua_get_NEW_AI_DATA_bDisappearOnTimeout(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bDisappearOnTimeout'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bDisappearOnTimeout);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bDisappearOnTimeout of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_bDisappearOnTimeout
static int tolua_set_NEW_AI_DATA_bDisappearOnTimeout(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bDisappearOnTimeout'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bDisappearOnTimeout = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nWanderRange of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nWanderRange
static int tolua_get_NEW_AI_DATA_nWanderRange(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nWanderRange'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nWanderRange);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nWanderRange of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nWanderRange
static int tolua_set_NEW_AI_DATA_nWanderRange(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nWanderRange'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nWanderRange = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nWanderInterval of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nWanderInterval
static int tolua_get_NEW_AI_DATA_nWanderInterval(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nWanderInterval'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nWanderInterval);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nWanderInterval of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nWanderInterval
static int tolua_set_NEW_AI_DATA_nWanderInterval(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nWanderInterval'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nWanderInterval = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSpellID of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_ai_NEW_AI_DATA_nSpellID
static int tolua_get_ai_NEW_AI_DATA_nSpellID(lua_State* tolua_S)
{
 int tolua_index;
  NEW_AI_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (NEW_AI_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=nastTotal)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSpellID[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSpellID of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_ai_NEW_AI_DATA_nSpellID
static int tolua_set_ai_NEW_AI_DATA_nSpellID(lua_State* tolua_S)
{
 int tolua_index;
  NEW_AI_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (NEW_AI_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=nastTotal)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->nSpellID[tolua_index] = (( signed int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSpellChance of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_ai_NEW_AI_DATA_nSpellChance
static int tolua_get_ai_NEW_AI_DATA_nSpellChance(lua_State* tolua_S)
{
 int tolua_index;
  NEW_AI_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (NEW_AI_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=nastTotal)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSpellChance[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSpellChance of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_ai_NEW_AI_DATA_nSpellChance
static int tolua_set_ai_NEW_AI_DATA_nSpellChance(lua_State* tolua_S)
{
 int tolua_index;
  NEW_AI_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (NEW_AI_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=nastTotal)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->nSpellChance[tolua_index] = (( signed int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSpellCDTime of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_ai_NEW_AI_DATA_nSpellCDTime
static int tolua_get_ai_NEW_AI_DATA_nSpellCDTime(lua_State* tolua_S)
{
 int tolua_index;
  NEW_AI_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (NEW_AI_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=nastTotal)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSpellCDTime[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSpellCDTime of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_ai_NEW_AI_DATA_nSpellCDTime
static int tolua_set_ai_NEW_AI_DATA_nSpellCDTime(lua_State* tolua_S)
{
 int tolua_index;
  NEW_AI_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (NEW_AI_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=nastTotal)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->nSpellCDTime[tolua_index] = (( signed int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSelfHpPercent of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_ai_NEW_AI_DATA_nSelfHpPercent
static int tolua_get_ai_NEW_AI_DATA_nSelfHpPercent(lua_State* tolua_S)
{
 int tolua_index;
  NEW_AI_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (NEW_AI_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=nastTotal)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSelfHpPercent[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSelfHpPercent of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_ai_NEW_AI_DATA_nSelfHpPercent
static int tolua_set_ai_NEW_AI_DATA_nSelfHpPercent(lua_State* tolua_S)
{
 int tolua_index;
  NEW_AI_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (NEW_AI_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=nastTotal)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->nSelfHpPercent[tolua_index] = (( signed int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGlobalCDTime of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nGlobalCDTime
static int tolua_get_NEW_AI_DATA_nGlobalCDTime(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGlobalCDTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nGlobalCDTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGlobalCDTime of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nGlobalCDTime
static int tolua_set_NEW_AI_DATA_nGlobalCDTime(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGlobalCDTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGlobalCDTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nFriendlyNpcTemplateID of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nFriendlyNpcTemplateID
static int tolua_get_NEW_AI_DATA_nFriendlyNpcTemplateID(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFriendlyNpcTemplateID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nFriendlyNpcTemplateID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nFriendlyNpcTemplateID of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nFriendlyNpcTemplateID
static int tolua_set_NEW_AI_DATA_nFriendlyNpcTemplateID(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFriendlyNpcTemplateID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nFriendlyNpcTemplateID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bFriendlyCorpse of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_bFriendlyCorpse
static int tolua_get_NEW_AI_DATA_bFriendlyCorpse(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bFriendlyCorpse'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bFriendlyCorpse);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bFriendlyCorpse of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_bFriendlyCorpse
static int tolua_set_NEW_AI_DATA_bFriendlyCorpse(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bFriendlyCorpse'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bFriendlyCorpse = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nCorpseTemplateID of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nCorpseTemplateID
static int tolua_get_NEW_AI_DATA_nCorpseTemplateID(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCorpseTemplateID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nCorpseTemplateID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nCorpseTemplateID of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nCorpseTemplateID
static int tolua_set_NEW_AI_DATA_nCorpseTemplateID(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCorpseTemplateID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nCorpseTemplateID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nIssuerSpellSignalType of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nIssuerSpellSignalType
static int tolua_get_NEW_AI_DATA_nIssuerSpellSignalType(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nIssuerSpellSignalType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nIssuerSpellSignalType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nIssuerSpellSignalType of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nIssuerSpellSignalType
static int tolua_set_NEW_AI_DATA_nIssuerSpellSignalType(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nIssuerSpellSignalType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nIssuerSpellSignalType = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nIssuerSpellSignalRange of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nIssuerSpellSignalRange
static int tolua_get_NEW_AI_DATA_nIssuerSpellSignalRange(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nIssuerSpellSignalRange'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nIssuerSpellSignalRange);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nIssuerSpellSignalRange of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nIssuerSpellSignalRange
static int tolua_set_NEW_AI_DATA_nIssuerSpellSignalRange(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nIssuerSpellSignalRange'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nIssuerSpellSignalRange = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nTargetSpellSignalType of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nTargetSpellSignalType
static int tolua_get_NEW_AI_DATA_nTargetSpellSignalType(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTargetSpellSignalType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nTargetSpellSignalType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nTargetSpellSignalType of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nTargetSpellSignalType
static int tolua_set_NEW_AI_DATA_nTargetSpellSignalType(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTargetSpellSignalType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nTargetSpellSignalType = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nTargetSpellSignalRange of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nTargetSpellSignalRange
static int tolua_get_NEW_AI_DATA_nTargetSpellSignalRange(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTargetSpellSignalRange'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nTargetSpellSignalRange);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nTargetSpellSignalRange of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nTargetSpellSignalRange
static int tolua_set_NEW_AI_DATA_nTargetSpellSignalRange(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTargetSpellSignalRange'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nTargetSpellSignalRange = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nFleeHpPercent of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nFleeHpPercent
static int tolua_get_NEW_AI_DATA_nFleeHpPercent(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFleeHpPercent'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nFleeHpPercent);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nFleeHpPercent of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nFleeHpPercent
static int tolua_set_NEW_AI_DATA_nFleeHpPercent(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFleeHpPercent'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nFleeHpPercent = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nFleeChance of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nFleeChance
static int tolua_get_NEW_AI_DATA_nFleeChance(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFleeChance'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nFleeChance);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nFleeChance of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nFleeChance
static int tolua_set_NEW_AI_DATA_nFleeChance(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFleeChance'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nFleeChance = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nFleeDuration of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nFleeDuration
static int tolua_get_NEW_AI_DATA_nFleeDuration(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFleeDuration'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nFleeDuration);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nFleeDuration of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nFleeDuration
static int tolua_set_NEW_AI_DATA_nFleeDuration(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFleeDuration'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nFleeDuration = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nStepAroundChance of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nStepAroundChance
static int tolua_get_NEW_AI_DATA_nStepAroundChance(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nStepAroundChance'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nStepAroundChance);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nStepAroundChance of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nStepAroundChance
static int tolua_set_NEW_AI_DATA_nStepAroundChance(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nStepAroundChance'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nStepAroundChance = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nStepAroundCDTime of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nStepAroundCDTime
static int tolua_get_NEW_AI_DATA_nStepAroundCDTime(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nStepAroundCDTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nStepAroundCDTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nStepAroundCDTime of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nStepAroundCDTime
static int tolua_set_NEW_AI_DATA_nStepAroundCDTime(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nStepAroundCDTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nStepAroundCDTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nChangeTargetChance of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nChangeTargetChance
static int tolua_get_NEW_AI_DATA_nChangeTargetChance(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nChangeTargetChance'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nChangeTargetChance);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nChangeTargetChance of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nChangeTargetChance
static int tolua_set_NEW_AI_DATA_nChangeTargetChance(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nChangeTargetChance'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nChangeTargetChance = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nChangeTargetCDTime of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nChangeTargetCDTime
static int tolua_get_NEW_AI_DATA_nChangeTargetCDTime(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nChangeTargetCDTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nChangeTargetCDTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nChangeTargetCDTime of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nChangeTargetCDTime
static int tolua_set_NEW_AI_DATA_nChangeTargetCDTime(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nChangeTargetCDTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nChangeTargetCDTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSpreadThreatCount of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NEW_AI_DATA_nSpreadThreatCount
static int tolua_get_NEW_AI_DATA_nSpreadThreatCount(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSpreadThreatCount'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSpreadThreatCount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSpreadThreatCount of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NEW_AI_DATA_nSpreadThreatCount
static int tolua_set_NEW_AI_DATA_nSpreadThreatCount(lua_State* tolua_S)
{
  NEW_AI_DATA* self = (NEW_AI_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSpreadThreatCount'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSpreadThreatCount = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nParam of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_get_ai_NEW_AI_DATA_nParam
static int tolua_get_ai_NEW_AI_DATA_nParam(lua_State* tolua_S)
{
 int tolua_index;
  NEW_AI_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (NEW_AI_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_AI_DATA_PARAM_COUNT)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nParam[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nParam of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_set_ai_NEW_AI_DATA_nParam
static int tolua_set_ai_NEW_AI_DATA_nParam(lua_State* tolua_S)
{
 int tolua_index;
  NEW_AI_DATA* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (NEW_AI_DATA*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_AI_DATA_PARAM_COUNT)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->nParam[tolua_index] = (( signed int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReadLine of class  NEW_AI_DATA */
#ifndef TOLUA_DISABLE_tolua_ai_NEW_AI_DATA_ReadLine00
static int tolua_ai_NEW_AI_DATA_ReadLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"NEW_AI_DATA",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,4,"NEW_AI_DATA",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,5,"CTabFile",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int rnID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  const char* rpcszName = ((const char*)  tolua_tostring(tolua_S,3,0));
  NEW_AI_DATA* pData = ((NEW_AI_DATA*)  tolua_tousertype(tolua_S,4,0));
  CTabFile* pTabConfig = ((CTabFile*)  tolua_tousertype(tolua_S,5,0));
  signed int nRow = (( signed int)  tolua_tonumber(tolua_S,6,0));
 {
 int tolua_ret = (int)
NEW_AI_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 tolua_pushnumber(tolua_S,(lua_Number)rnID);
 tolua_pushstring(tolua_S,(const char*)rpcszName);
 }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReadLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOwner of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetOwner00
static int tolua_ai_CAIProcessor_GetOwner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOwner'", NULL);
#endif
 {
  CCharacter* tolua_ret = (CCharacter*)  self->GetOwner();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCharacter");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOwner'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAIID of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetAIID00
static int tolua_ai_CAIProcessor_GetAIID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAIID'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetAIID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAIID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Stop of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Stop00
static int tolua_ai_CAIProcessor_Stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Stop'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Stop();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MoveTo of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_MoveTo00
static int tolua_ai_CAIProcessor_MoveTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
  signed int llDestX = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int llDestY = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MoveTo'", NULL);
#endif
 {
 int tolua_ret = (int)
self->MoveTo(llDestX,llDestY);
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

/* method: SyncMoveTo of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SyncMoveTo00
static int tolua_ai_CAIProcessor_SyncMoveTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
  signed int llDestX = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int llDestY = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SyncMoveTo'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SyncMoveTo(llDestX,llDestY);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SyncMoveTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Wander of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Wander00
static int tolua_ai_CAIProcessor_Wander00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
  signed int nWanderRange = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nWanderInterval = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Wander'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Wander(nWanderRange,nWanderInterval);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Wander'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Patrol of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Patrol00
static int tolua_ai_CAIProcessor_Patrol00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Patrol'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Patrol();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Patrol'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Chase of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Chase00
static int tolua_ai_CAIProcessor_Chase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
  signed int nPreferDistance = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nChaseThreshold = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nDelayTime = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Chase'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Chase(nPreferDistance,nChaseThreshold,nDelayTime);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Chase'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Withdraw of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Withdraw00
static int tolua_ai_CAIProcessor_Withdraw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
  signed int nPreferDistance = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nWithdrawThreshold = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Withdraw'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Withdraw(nPreferDistance,nWithdrawThreshold);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Withdraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StepAround of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_StepAround00
static int tolua_ai_CAIProcessor_StepAround00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
  CCharacter* poTarget = ((CCharacter*)  tolua_tousertype(tolua_S,2,0));
  signed int nPreferDistance = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nChaseThreshold = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StepAround'", NULL);
#endif
 {
 int tolua_ret = (int)
self->StepAround(poTarget,nPreferDistance,nChaseThreshold);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StepAround'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Follow of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Follow00
static int tolua_ai_CAIProcessor_Follow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Follow'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Follow();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Follow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Flee of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Flee00
static int tolua_ai_CAIProcessor_Flee00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
  signed int nFleeTime = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Flee'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Flee(nFleeTime);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Flee'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NeedChase of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_NeedChase00
static int tolua_ai_CAIProcessor_NeedChase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
  CCharacter* poTarget = ((CCharacter*)  tolua_tousertype(tolua_S,2,0));
  signed int nChaseThreshold = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NeedChase'", NULL);
#endif
 {
 int tolua_ret = (int)
self->NeedChase(poTarget,nChaseThreshold);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NeedChase'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NeedWithdraw of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_NeedWithdraw00
static int tolua_ai_CAIProcessor_NeedWithdraw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CCharacter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
  CCharacter* poTarget = ((CCharacter*)  tolua_tousertype(tolua_S,2,0));
  signed int nWithdrawThreshold = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NeedWithdraw'", NULL);
#endif
 {
 int tolua_ret = (int)
self->NeedWithdraw(poTarget,nWithdrawThreshold);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NeedWithdraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GoHome of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GoHome00
static int tolua_ai_CAIProcessor_GoHome00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GoHome'", NULL);
#endif
 {
 int tolua_ret = (int)
self->GoHome();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GoHome'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CallInitBT of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_CallInitBT00
static int tolua_ai_CAIProcessor_CallInitBT00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CallInitBT'", NULL);
#endif
 {
  self->CallInitBT();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CallInitBT'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PrintAllBT of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_PrintAllBT00
static int tolua_ai_CAIProcessor_PrintAllBT00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PrintAllBT'", NULL);
#endif
 {
  self->PrintAllBT();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrintAllBT'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInteractRoleID of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetInteractRoleID00
static int tolua_ai_CAIProcessor_GetInteractRoleID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInteractRoleID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetInteractRoleID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInteractRoleID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVariable of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SetVariable00
static int tolua_ai_CAIProcessor_SetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetVariable of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetVariable00
static int tolua_ai_CAIProcessor_GetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetBossState of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetBossState00
static int tolua_ai_CAIProcessor_GetBossState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBossState'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetBossState();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBossState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBossState of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SetBossState00
static int tolua_ai_CAIProcessor_SetBossState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
  signed int nState = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBossState'", NULL);
#endif
 {
  self->SetBossState(nState);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBossState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTargetID of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SetTargetID00
static int tolua_ai_CAIProcessor_SetTargetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTargetID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTargetID'", NULL);
#endif
 {
  self->SetTargetID(dwTargetID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTargetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTargetID of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetTargetID00
static int tolua_ai_CAIProcessor_GetTargetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTargetID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetTargetID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTargetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNearestEnemyID of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetNearestEnemyID00
static int tolua_ai_CAIProcessor_GetNearestEnemyID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNearestEnemyID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetNearestEnemyID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNearestEnemyID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFarthestEnemyID of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetFarthestEnemyID00
static int tolua_ai_CAIProcessor_GetFarthestEnemyID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFarthestEnemyID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetFarthestEnemyID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFarthestEnemyID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCastingEnemyID of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetCastingEnemyID00
static int tolua_ai_CAIProcessor_GetCastingEnemyID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCastingEnemyID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetCastingEnemyID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCastingEnemyID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIgnoreInvisible of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SetIgnoreInvisible00
static int tolua_ai_CAIProcessor_SetIgnoreInvisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
   bool bValue = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIgnoreInvisible'", NULL);
#endif
 {
  self->SetIgnoreInvisible(bValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIgnoreInvisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IgnoreInvisible of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_IgnoreInvisible00
static int tolua_ai_CAIProcessor_IgnoreInvisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IgnoreInvisible'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IgnoreInvisible();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IgnoreInvisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCounterInvisible of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SetCounterInvisible00
static int tolua_ai_CAIProcessor_SetCounterInvisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
   bool bValue = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCounterInvisible'", NULL);
#endif
 {
  self->SetCounterInvisible(bValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCounterInvisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CounterInvisible of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_CounterInvisible00
static int tolua_ai_CAIProcessor_CounterInvisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CounterInvisible'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CounterInvisible();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CounterInvisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFollowParam of class  CAIProcessor */
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SetFollowParam00
static int tolua_ai_CAIProcessor_SetFollowParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAIProcessor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAIProcessor* self = (CAIProcessor*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwFollowHostID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  signed int nFollowOffsetX = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nFollowOffsetY = (( signed int)  tolua_tonumber(tolua_S,4,0));
   bool bUseHostSpeed = ((  bool)  tolua_toboolean(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFollowParam'", NULL);
#endif
 {
  self->SetFollowParam(dwFollowHostID,nFollowOffsetX,nFollowOffsetY,bUseHostSpeed);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFollowParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ai_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"brvError",brvError);
  tolua_constant(tolua_S,"brvFail",brvFail);
  tolua_constant(tolua_S,"brvSuccess",brvSuccess);
  tolua_constant(tolua_S,"brvRunning",brvRunning);
  tolua_constant(tolua_S,"brvTotal",brvTotal);
  tolua_constant(tolua_S,"btInvalid",btInvalid);
  tolua_constant(tolua_S,"btSelector",btSelector);
  tolua_constant(tolua_S,"btSequencer",btSequencer);
  tolua_constant(tolua_S,"btParallel",btParallel);
  tolua_constant(tolua_S,"btNot",btNot);
  tolua_constant(tolua_S,"btDebug",btDebug);
  tolua_constant(tolua_S,"btRandom",btRandom);
  tolua_constant(tolua_S,"btRepeat",btRepeat);
  tolua_constant(tolua_S,"btUserDefine",btUserDefine);
  tolua_constant(tolua_S,"btTotal",btTotal);
  tolua_constant(tolua_S,"boLT",boLT);
  tolua_constant(tolua_S,"boLTE",boLTE);
  tolua_constant(tolua_S,"boGT",boGT);
  tolua_constant(tolua_S,"boGTE",boGTE);
  tolua_constant(tolua_S,"boEQ",boEQ);
  tolua_constant(tolua_S,"boNEQ",boNEQ);
  tolua_constant(tolua_S,"tarInvalid",tarInvalid);
  tolua_constant(tolua_S,"tarSelf",tarSelf);
  tolua_constant(tolua_S,"tarAITarget",tarAITarget);
  tolua_constant(tolua_S,"tarHost",tarHost);
  tolua_constant(tolua_S,"tarNearestEnemy",tarNearestEnemy);
  tolua_constant(tolua_S,"tarFarthestEnemy",tarFarthestEnemy);
  tolua_constant(tolua_S,"tarCastingEnemy",tarCastingEnemy);
  tolua_constant(tolua_S,"tarCorpse",tarCorpse);
  tolua_constant(tolua_S,"tarAuraChar",tarAuraChar);
  tolua_constant(tolua_S,"tarNearestFriend",tarNearestFriend);
  tolua_constant(tolua_S,"tarSignalIssuer",tarSignalIssuer);
  tolua_constant(tolua_S,"tarSignalIssuerTarget",tarSignalIssuerTarget);
  tolua_constant(tolua_S,"tarNearestEnemyRole",tarNearestEnemyRole);
  tolua_constant(tolua_S,"tarRole",tarRole);
  tolua_constant(tolua_S,"tarRoleKiller",tarRoleKiller);
  tolua_constant(tolua_S,"tarRolePet1",tarRolePet1);
  tolua_constant(tolua_S,"tarRolePet2",tarRolePet2);
  tolua_constant(tolua_S,"tarRolePet3",tarRolePet3);
  tolua_constant(tolua_S,"tarRolePet4",tarRolePet4);
  tolua_constant(tolua_S,"tarRolePet5",tarRolePet5);
  tolua_constant(tolua_S,"tarRolePet6",tarRolePet6);
  tolua_constant(tolua_S,"tarDirection",tarDirection);
  tolua_constant(tolua_S,"tarPosition",tarPosition);
  tolua_constant(tolua_S,"tarRelativePosition",tarRelativePosition);
  tolua_constant(tolua_S,"tarHome",tarHome);
  tolua_constant(tolua_S,"tarTotal",tarTotal);
  tolua_constant(tolua_S,"batInvalid",batInvalid);
  tolua_constant(tolua_S,"batSelector",batSelector);
  tolua_constant(tolua_S,"batSequencer",batSequencer);
  tolua_constant(tolua_S,"batParallel",batParallel);
  tolua_constant(tolua_S,"batNot",batNot);
  tolua_constant(tolua_S,"batDebug",batDebug);
  tolua_constant(tolua_S,"batRandom",batRandom);
  tolua_constant(tolua_S,"batRepeat",batRepeat);
  tolua_constant(tolua_S,"batBegin",batBegin);
  tolua_constant(tolua_S,"batReturnSuccess",batReturnSuccess);
  tolua_constant(tolua_S,"batReturnFail",batReturnFail);
  tolua_constant(tolua_S,"batPrint",batPrint);
  tolua_constant(tolua_S,"batCheckDice",batCheckDice);
  tolua_constant(tolua_S,"batCheckSceneVariable",batCheckSceneVariable);
  tolua_constant(tolua_S,"batCheckServerVariable",batCheckServerVariable);
  tolua_constant(tolua_S,"batCheckDateTime",batCheckDateTime);
  tolua_constant(tolua_S,"batCheckWeather",batCheckWeather);
  tolua_constant(tolua_S,"batCompareSceneVariable",batCompareSceneVariable);
  tolua_constant(tolua_S,"batCheckDoorState",batCheckDoorState);
  tolua_constant(tolua_S,"batWait",batWait);
  tolua_constant(tolua_S,"batOpenDoor",batOpenDoor);
  tolua_constant(tolua_S,"batCloseDoor",batCloseDoor);
  tolua_constant(tolua_S,"batToggleDoor",batToggleDoor);
  tolua_constant(tolua_S,"batSay",batSay);
  tolua_constant(tolua_S,"batSetSceneVariable",batSetSceneVariable);
  tolua_constant(tolua_S,"batSetServerVariable",batSetServerVariable);
  tolua_constant(tolua_S,"batSpawnNpc",batSpawnNpc);
  tolua_constant(tolua_S,"batSpawnNpcAtPoint",batSpawnNpcAtPoint);
  tolua_constant(tolua_S,"batSpawnSingleNpc",batSpawnSingleNpc);
  tolua_constant(tolua_S,"batSpawnMediumGroup",batSpawnMediumGroup);
  tolua_constant(tolua_S,"batSpawnLargeGroup",batSpawnLargeGroup);
  tolua_constant(tolua_S,"batSpawnDoodad",batSpawnDoodad);
  tolua_constant(tolua_S,"batSpawnDoodadAtPoint",batSpawnDoodadAtPoint);
  tolua_constant(tolua_S,"batSpawnDoodadGroup",batSpawnDoodadGroup);
  tolua_constant(tolua_S,"batCheckSceneRuning",batCheckSceneRuning);
  tolua_constant(tolua_S,"batFinishScene",batFinishScene);
  tolua_constant(tolua_S,"batCalculateDungeonScore",batCalculateDungeonScore);
  tolua_constant(tolua_S,"batSetReputationToFaction",batSetReputationToFaction);
  tolua_constant(tolua_S,"batAddMoneyToFaction",batAddMoneyToFaction);
  tolua_constant(tolua_S,"batSubMoneyToFaction",batSubMoneyToFaction);
  tolua_constant(tolua_S,"batAddAuraToFaction",batAddAuraToFaction);
  tolua_constant(tolua_S,"batRemoveAuraToFaction",batRemoveAuraToFaction);
  tolua_constant(tolua_S,"batAddItemToFaction",batAddItemToFaction);
  tolua_constant(tolua_S,"batSetCombatStatToFaction",batSetCombatStatToFaction);
  tolua_constant(tolua_S,"batGuildEndWar",batGuildEndWar);
  tolua_constant(tolua_S,"batCloseGuildDungeon",batCloseGuildDungeon);
  tolua_constant(tolua_S,"batGuildWarTime",batGuildWarTime);
  tolua_constant(tolua_S,"batRoleCheckRoleVariable",batRoleCheckRoleVariable);
  tolua_constant(tolua_S,"batRoleCheckGuildVariable",batRoleCheckGuildVariable);
  tolua_constant(tolua_S,"batRoleCheckHasQuest",batRoleCheckHasQuest);
  tolua_constant(tolua_S,"batRoleCheckQuestVariable",batRoleCheckQuestVariable);
  tolua_constant(tolua_S,"batRoleCheckFaction",batRoleCheckFaction);
  tolua_constant(tolua_S,"batCheckInTeam",batCheckInTeam);
  tolua_constant(tolua_S,"batRoleCheckInteractOption",batRoleCheckInteractOption);
  tolua_constant(tolua_S,"batRoleCheckVIP",batRoleCheckVIP);
  tolua_constant(tolua_S,"batRoleCheckLevel",batRoleCheckLevel);
  tolua_constant(tolua_S,"batRoleIsSabacGuildMember",batRoleIsSabacGuildMember);
  tolua_constant(tolua_S,"batRoleIsSabacGuildLeader",batRoleIsSabacGuildLeader);
  tolua_constant(tolua_S,"batRoleSetRoleVariable",batRoleSetRoleVariable);
  tolua_constant(tolua_S,"batRoleSetGuildVariable",batRoleSetGuildVariable);
  tolua_constant(tolua_S,"batRoleSetQuestVariable",batRoleSetQuestVariable);
  tolua_constant(tolua_S,"batRoleSetCombatStat",batRoleSetCombatStat);
  tolua_constant(tolua_S,"batRoleTeleportToPoint",batRoleTeleportToPoint);
  tolua_constant(tolua_S,"batRoleTeleport",batRoleTeleport);
  tolua_constant(tolua_S,"batRoleReturnStaticScene",batRoleReturnStaticScene);
  tolua_constant(tolua_S,"batRoleSetReputation",batRoleSetReputation);
  tolua_constant(tolua_S,"batRoleCheckMoney",batRoleCheckMoney);
  tolua_constant(tolua_S,"batRoleAddMoney",batRoleAddMoney);
  tolua_constant(tolua_S,"batRoleSubMoney",batRoleSubMoney);
  tolua_constant(tolua_S,"batRoleCheckItemCount",batRoleCheckItemCount);
  tolua_constant(tolua_S,"batRoleAddItem",batRoleAddItem);
  tolua_constant(tolua_S,"batRoleDelItem",batRoleDelItem);
  tolua_constant(tolua_S,"batRoleOpenDialog",batRoleOpenDialog);
  tolua_constant(tolua_S,"batRoleLeaveTeam",batRoleLeaveTeam);
  tolua_constant(tolua_S,"batRoleSetFaction",batRoleSetFaction);
  tolua_constant(tolua_S,"batRoleCheckSelfScene",batRoleCheckSelfScene);
  tolua_constant(tolua_S,"batRoleCheckAllianceScene",batRoleCheckAllianceScene);
  tolua_constant(tolua_S,"batRoleJumpToTargetGuildScene",batRoleJumpToTargetGuildScene);
  tolua_constant(tolua_S,"batRoleCheckDailyVariable",batRoleCheckDailyVariable);
  tolua_constant(tolua_S,"batRoleUpdateDailyVariable",batRoleUpdateDailyVariable);
  tolua_constant(tolua_S,"batRoleEnterCutScene",batRoleEnterCutScene);
  tolua_constant(tolua_S,"batRoleEnrollSabac",batRoleEnrollSabac);
  tolua_constant(tolua_S,"batRoleViewSabacEnrollList",batRoleViewSabacEnrollList);
  tolua_constant(tolua_S,"batRoleErectStatue",batRoleErectStatue);
  tolua_constant(tolua_S,"batRoleAddDailyExtraExp",batRoleAddDailyExtraExp);
  tolua_constant(tolua_S,"batRoleCheckCDTimer",batRoleCheckCDTimer);
  tolua_constant(tolua_S,"batRoleSetCDTimer",batRoleSetCDTimer);
  tolua_constant(tolua_S,"batRoleJumpToRevivePos",batRoleJumpToRevivePos);
  tolua_constant(tolua_S,"batRoleErrorCodeNotify",batRoleErrorCodeNotify);
  tolua_constant(tolua_S,"batRoleCheckGuild",batRoleCheckGuild);
  tolua_constant(tolua_S,"batRoleCheckPosition",batRoleCheckPosition);
  tolua_constant(tolua_S,"batRoleCheckGuildActivity",batRoleCheckGuildActivity);
  tolua_constant(tolua_S,"batRoleTemporaryCharge",batRoleTemporaryCharge);
  tolua_constant(tolua_S,"batCheckCharMoveState",batCheckCharMoveState);
  tolua_constant(tolua_S,"batCheckDirection",batCheckDirection);
  tolua_constant(tolua_S,"batCheckCharHp",batCheckCharHp);
  tolua_constant(tolua_S,"batAddAura",batAddAura);
  tolua_constant(tolua_S,"batReduceAura",batReduceAura);
  tolua_constant(tolua_S,"batRemoveAura",batRemoveAura);
  tolua_constant(tolua_S,"batCopyAura",batCopyAura);
  tolua_constant(tolua_S,"batCheckAura",batCheckAura);
  tolua_constant(tolua_S,"batRotateTo",batRotateTo);
  tolua_constant(tolua_S,"batSyncRotateTo",batSyncRotateTo);
  tolua_constant(tolua_S,"batMoveTo",batMoveTo);
  tolua_constant(tolua_S,"batSyncMoveTo",batSyncMoveTo);
  tolua_constant(tolua_S,"batTeleportTo",batTeleportTo);
  tolua_constant(tolua_S,"batSuicide",batSuicide);
  tolua_constant(tolua_S,"batSetCharHp",batSetCharHp);
  tolua_constant(tolua_S,"batSendMail",batSendMail);
  tolua_constant(tolua_S,"batSummonNpc",batSummonNpc);
  tolua_constant(tolua_S,"batSummonDoodad",batSummonDoodad);
  tolua_constant(tolua_S,"batSendAwardInfo",batSendAwardInfo);
  tolua_constant(tolua_S,"batDistributeExp",batDistributeExp);
  tolua_constant(tolua_S,"batClearThreatList",batClearThreatList);
  tolua_constant(tolua_S,"batAddExp",batAddExp);
  tolua_constant(tolua_S,"batRecvMsg",batRecvMsg);
  tolua_constant(tolua_S,"batCheckCCFlag",batCheckCCFlag);
  tolua_constant(tolua_S,"batCheckFlag",batCheckFlag);
  tolua_constant(tolua_S,"batCheckInCombat",batCheckInCombat);
  tolua_constant(tolua_S,"batCheckHostInCombat",batCheckHostInCombat);
  tolua_constant(tolua_S,"batCheckCharOutOfHomeRange",batCheckCharOutOfHomeRange);
  tolua_constant(tolua_S,"batCheckCharHpMeet",batCheckCharHpMeet);
  tolua_constant(tolua_S,"batCheckCharCasting",batCheckCharCasting);
  tolua_constant(tolua_S,"batCheckBossState",batCheckBossState);
  tolua_constant(tolua_S,"batCheckDistance",batCheckDistance);
  tolua_constant(tolua_S,"batCheckCDTimer",batCheckCDTimer);
  tolua_constant(tolua_S,"batCheckAIVariable",batCheckAIVariable);
  tolua_constant(tolua_S,"batCheckHeroWeaponEquipped",batCheckHeroWeaponEquipped);
  tolua_constant(tolua_S,"batCheckTarget",batCheckTarget);
  tolua_constant(tolua_S,"batCheckTargetType",batCheckTargetType);
  tolua_constant(tolua_S,"batWander",batWander);
  tolua_constant(tolua_S,"batGoHome",batGoHome);
  tolua_constant(tolua_S,"batSetHome",batSetHome);
  tolua_constant(tolua_S,"batFlee",batFlee);
  tolua_constant(tolua_S,"batChase",batChase);
  tolua_constant(tolua_S,"batWithdraw",batWithdraw);
  tolua_constant(tolua_S,"batSetFollowParam",batSetFollowParam);
  tolua_constant(tolua_S,"batFollow",batFollow);
  tolua_constant(tolua_S,"batInvincible",batInvincible);
  tolua_constant(tolua_S,"batEnterIdle",batEnterIdle);
  tolua_constant(tolua_S,"batEnterFight",batEnterFight);
  tolua_constant(tolua_S,"batCastSpell",batCastSpell);
  tolua_constant(tolua_S,"batSetTarget",batSetTarget);
  tolua_constant(tolua_S,"batSetRoleAsTarget",batSetRoleAsTarget);
  tolua_constant(tolua_S,"batSetTargetAsRole",batSetTargetAsRole);
  tolua_constant(tolua_S,"batSetLastCaster",batSetLastCaster);
  tolua_constant(tolua_S,"batSetScanEnemyParam",batSetScanEnemyParam);
  tolua_constant(tolua_S,"batSetScanFriendParam",batSetScanFriendParam);
  tolua_constant(tolua_S,"batSetScanCorpseParam",batSetScanCorpseParam);
  tolua_constant(tolua_S,"batSetScanAuraCharParam",batSetScanAuraCharParam);
  tolua_constant(tolua_S,"batScanEnemy",batScanEnemy);
  tolua_constant(tolua_S,"batScanNearby",batScanNearby);
  tolua_constant(tolua_S,"batScanRedName",batScanRedName);
  tolua_constant(tolua_S,"batScanSabacWinner",batScanSabacWinner);
  tolua_constant(tolua_S,"batScanSabacEnemy",batScanSabacEnemy);
  tolua_constant(tolua_S,"batGetTargetFromThreatList",batGetTargetFromThreatList);
  tolua_constant(tolua_S,"batPetGetTargetFromThreatList",batPetGetTargetFromThreatList);
  tolua_constant(tolua_S,"batScanHostThreatList",batScanHostThreatList);
  tolua_constant(tolua_S,"batAddTargetThreat",batAddTargetThreat);
  tolua_constant(tolua_S,"batSetBossState",batSetBossState);
  tolua_constant(tolua_S,"batSetFlag",batSetFlag);
  tolua_constant(tolua_S,"batClearFlag",batClearFlag);
  tolua_constant(tolua_S,"batPlayAction",batPlayAction);
  tolua_constant(tolua_S,"batSetCDTimer",batSetCDTimer);
  tolua_constant(tolua_S,"batSetAIVariable",batSetAIVariable);
  tolua_constant(tolua_S,"batStepAroundTarget",batStepAroundTarget);
  tolua_constant(tolua_S,"batCheckNeedChase",batCheckNeedChase);
  tolua_constant(tolua_S,"batCheckNeedWithdraw",batCheckNeedWithdraw);
  tolua_constant(tolua_S,"batCheckCanMove",batCheckCanMove);
  tolua_constant(tolua_S,"batCheckCanCastSpell",batCheckCanCastSpell);
  tolua_constant(tolua_S,"batCastSpellToTarget",batCastSpellToTarget);
  tolua_constant(tolua_S,"batCastSlotSpellToTarget",batCastSlotSpellToTarget);
  tolua_constant(tolua_S,"batCastSpellToPos",batCastSpellToPos);
  tolua_constant(tolua_S,"batCastSpellToTargetPos",batCastSpellToTargetPos);
  tolua_constant(tolua_S,"batCastSpellToDir",batCastSpellToDir);
  tolua_constant(tolua_S,"batCastSpellToTargetDir",batCastSpellToTargetDir);
  tolua_constant(tolua_S,"batSyncCastSpellToTarget",batSyncCastSpellToTarget);
  tolua_constant(tolua_S,"batSyncCastSpellToPos",batSyncCastSpellToPos);
  tolua_constant(tolua_S,"batSyncCastSpellToTargetPos",batSyncCastSpellToTargetPos);
  tolua_constant(tolua_S,"batSyncCastSpellToDir",batSyncCastSpellToDir);
  tolua_constant(tolua_S,"batSyncCastSpellToTargetDir",batSyncCastSpellToTargetDir);
  tolua_constant(tolua_S,"batSyncCastSlotSpellToTarget",batSyncCastSlotSpellToTarget);
  tolua_constant(tolua_S,"batWaitCastSpell",batWaitCastSpell);
  tolua_constant(tolua_S,"batSyncBreakCast",batSyncBreakCast);
  tolua_constant(tolua_S,"batIssueSignal",batIssueSignal);
  tolua_constant(tolua_S,"batPickSignal",batPickSignal);
  tolua_constant(tolua_S,"batGetTargetFromSignal",batGetTargetFromSignal);
  tolua_constant(tolua_S,"batSetPatrolParam",batSetPatrolParam);
  tolua_constant(tolua_S,"batPatrol",batPatrol);
  tolua_constant(tolua_S,"batAddThreatListFromSignal",batAddThreatListFromSignal);
  tolua_constant(tolua_S,"batCheckIntValue",batCheckIntValue);
  tolua_constant(tolua_S,"batGBuildingDead",batGBuildingDead);
  tolua_constant(tolua_S,"batCheckHost",batCheckHost);
  tolua_constant(tolua_S,"batMagePetCastSpellToTarget",batMagePetCastSpellToTarget);
  tolua_constant(tolua_S,"batPetScanEnemy",batPetScanEnemy);
  tolua_constant(tolua_S,"batJumpToHost",batJumpToHost);
  tolua_constant(tolua_S,"batPetFollow",batPetFollow);
  tolua_constant(tolua_S,"batPetCheckHostDirection",batPetCheckHostDirection);
  tolua_constant(tolua_S,"batCheckThreatList",batCheckThreatList);
  tolua_constant(tolua_S,"batPetChangeChaseTarget",batPetChangeChaseTarget);
  tolua_constant(tolua_S,"batPetChangeFightTarget",batPetChangeFightTarget);
  tolua_constant(tolua_S,"batPetGetCaster",batPetGetCaster);
  tolua_constant(tolua_S,"batCheckThreatFadeTime",batCheckThreatFadeTime);
  tolua_constant(tolua_S,"batCheckThreatenFadeTime",batCheckThreatenFadeTime);
  tolua_constant(tolua_S,"batPetWander",batPetWander);
  tolua_constant(tolua_S,"batPetCheckValidTarget",batPetCheckValidTarget);
  tolua_constant(tolua_S,"batPetCheckNeedChase",batPetCheckNeedChase);
  tolua_constant(tolua_S,"batPetChase",batPetChase);
  tolua_constant(tolua_S,"batPetCheckRoleState",batPetCheckRoleState);
  tolua_constant(tolua_S,"batPetStopMove",batPetStopMove);
  tolua_constant(tolua_S,"batPetDelSbFromThreatenList",batPetDelSbFromThreatenList);
  tolua_constant(tolua_S,"batPetDelSbFromThreatList",batPetDelSbFromThreatList);
  tolua_constant(tolua_S,"batPetCheckHostTarget",batPetCheckHostTarget);
  tolua_constant(tolua_S,"batPetClearHostTarget",batPetClearHostTarget);
  tolua_constant(tolua_S,"batSetAvoidGroundEffect",batSetAvoidGroundEffect);
  tolua_constant(tolua_S,"batChangeGuildResource",batChangeGuildResource);
  tolua_constant(tolua_S,"batSetAlwaysRun",batSetAlwaysRun);
  tolua_constant(tolua_S,"batTeleportSceneRoleToReturnPos",batTeleportSceneRoleToReturnPos);
  tolua_constant(tolua_S,"batTpOtherGuildRoleToReturnPos",batTpOtherGuildRoleToReturnPos);
  tolua_constant(tolua_S,"batSceneRoleSetFaction",batSceneRoleSetFaction);
  tolua_constant(tolua_S,"batSceneEndArena",batSceneEndArena);
  tolua_constant(tolua_S,"batEnd",batEnd);
 tolua_cclass(tolua_S,"stSignal","stSignal","",NULL);
 tolua_beginmodule(tolua_S,"stSignal");
  tolua_variable(tolua_S,"nType",tolua_get_stSignal_nType,tolua_set_stSignal_nType);
  tolua_variable(tolua_S,"nParam",tolua_get_stSignal_nParam,tolua_set_stSignal_nParam);
  tolua_variable(tolua_S,"nRemainTimes",tolua_get_stSignal_nRemainTimes,tolua_set_stSignal_nRemainTimes);
  tolua_variable(tolua_S,"nExpiredFrame",tolua_get_stSignal_nExpiredFrame,tolua_set_stSignal_nExpiredFrame);
  tolua_variable(tolua_S,"dwIssuerID",tolua_get_stSignal_unsigned_dwIssuerID,tolua_set_stSignal_unsigned_dwIssuerID);
  tolua_variable(tolua_S,"ListNode",tolua_get_stSignal_ListNode,tolua_set_stSignal_ListNode);
 tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"sigInvalid",sigInvalid);
  tolua_constant(tolua_S,"sigSpreadHate",sigSpreadHate);
  tolua_constant(tolua_S,"sigAssistOnce",sigAssistOnce);
  tolua_constant(tolua_S,"sigAssist",sigAssist);
  tolua_constant(tolua_S,"sigHelpSpellHeal",sigHelpSpellHeal);
  tolua_constant(tolua_S,"sigHelpSpellHarm",sigHelpSpellHarm);
  tolua_constant(tolua_S,"sigUserDefine",sigUserDefine);
  tolua_constant(tolua_S,"sigEnd",sigEnd);
  tolua_constant(tolua_S,"apsInvalid",apsInvalid);
  tolua_constant(tolua_S,"apsLine",apsLine);
  tolua_constant(tolua_S,"apsLineBack",apsLineBack);
  tolua_constant(tolua_S,"apsCircle",apsCircle);
  tolua_constant(tolua_S,"apsTotal",apsTotal);
 tolua_constant(tolua_S,"MAX_AI_ID",MAX_AI_ID);
 tolua_constant(tolua_S,"MAX_AI_INIT_AURA_COUNT",MAX_AI_INIT_AURA_COUNT);
 tolua_constant(tolua_S,"MAX_AI_DATA_PARAM_COUNT",MAX_AI_DATA_PARAM_COUNT);
  tolua_constant(tolua_S,"nastInvalid",nastInvalid);
  tolua_constant(tolua_S,"nastNormalSpell1",nastNormalSpell1);
  tolua_constant(tolua_S,"nastNormalSpell2",nastNormalSpell2);
  tolua_constant(tolua_S,"nastHelpFriendSpell1",nastHelpFriendSpell1);
  tolua_constant(tolua_S,"nastHelpFriendSpell2",nastHelpFriendSpell2);
  tolua_constant(tolua_S,"nastCorpseSpell",nastCorpseSpell);
  tolua_constant(tolua_S,"nastSignalIssuerSpell",nastSignalIssuerSpell);
  tolua_constant(tolua_S,"nastSignalTargetSpell",nastSignalTargetSpell);
  tolua_constant(tolua_S,"nastNormalSpell3",nastNormalSpell3);
  tolua_constant(tolua_S,"nastNormalSpell4",nastNormalSpell4);
  tolua_constant(tolua_S,"nastEnterFightSpell",nastEnterFightSpell);
  tolua_constant(tolua_S,"nastChaseSpell",nastChaseSpell);
  tolua_constant(tolua_S,"nastInitSpell1",nastInitSpell1);
  tolua_constant(tolua_S,"nastInitSpell2",nastInitSpell2);
  tolua_constant(tolua_S,"nastInitSpell3",nastInitSpell3);
  tolua_constant(tolua_S,"nastDeadSpell",nastDeadSpell);
  tolua_constant(tolua_S,"nastIdleSpell",nastIdleSpell);
  tolua_constant(tolua_S,"nastTotal",nastTotal);
  tolua_constant(tolua_S,"nastGlobalCDTimer",nastGlobalCDTimer);
  tolua_constant(tolua_S,"nastLiveTimer",nastLiveTimer);
  tolua_constant(tolua_S,"nastFleeTimer",nastFleeTimer);
  tolua_constant(tolua_S,"nastThreatSingalTimer",nastThreatSingalTimer);
  tolua_constant(tolua_S,"nastChanceTargetTimer",nastChanceTargetTimer);
  tolua_constant(tolua_S,"nastScanNearbyTimer",nastScanNearbyTimer);
  tolua_constant(tolua_S,"nastStepAroundTimer",nastStepAroundTimer);
  tolua_constant(tolua_S,"nastWithdrawTimer",nastWithdrawTimer);
  tolua_constant(tolua_S,"nastCustom",nastCustom);
 tolua_cclass(tolua_S,"NEW_AI_DATA","NEW_AI_DATA","",NULL);
 tolua_beginmodule(tolua_S,"NEW_AI_DATA");
  tolua_variable(tolua_S,"nAIID",tolua_get_NEW_AI_DATA_nAIID,tolua_set_NEW_AI_DATA_nAIID);
  tolua_variable(tolua_S,"szScriptName",tolua_get_NEW_AI_DATA_szScriptName,tolua_set_NEW_AI_DATA_szScriptName);
  tolua_variable(tolua_S,"nWalkSpeed",tolua_get_NEW_AI_DATA_nWalkSpeed,tolua_set_NEW_AI_DATA_nWalkSpeed);
  tolua_variable(tolua_S,"nRunSpeed",tolua_get_NEW_AI_DATA_nRunSpeed,tolua_set_NEW_AI_DATA_nRunSpeed);
  tolua_variable(tolua_S,"nRotateSpeed",tolua_get_NEW_AI_DATA_nRotateSpeed,tolua_set_NEW_AI_DATA_nRotateSpeed);
  tolua_variable(tolua_S,"bPatrol",tolua_get_NEW_AI_DATA_bPatrol,tolua_set_NEW_AI_DATA_bPatrol);
  tolua_variable(tolua_S,"bFollow",tolua_get_NEW_AI_DATA_bFollow,tolua_set_NEW_AI_DATA_bFollow);
  tolua_variable(tolua_S,"bCanRun",tolua_get_NEW_AI_DATA_bCanRun,tolua_set_NEW_AI_DATA_bCanRun);
  tolua_variable(tolua_S,"bAlwaysRun",tolua_get_NEW_AI_DATA_bAlwaysRun,tolua_set_NEW_AI_DATA_bAlwaysRun);
  tolua_variable(tolua_S,"nScanEnemyRange",tolua_get_NEW_AI_DATA_nScanEnemyRange,tolua_set_NEW_AI_DATA_nScanEnemyRange);
  tolua_variable(tolua_S,"nScanFriendRange",tolua_get_NEW_AI_DATA_nScanFriendRange,tolua_set_NEW_AI_DATA_nScanFriendRange);
  tolua_variable(tolua_S,"nChaseRange",tolua_get_NEW_AI_DATA_nChaseRange,tolua_set_NEW_AI_DATA_nChaseRange);
  tolua_variable(tolua_S,"nPreferDistance",tolua_get_NEW_AI_DATA_nPreferDistance,tolua_set_NEW_AI_DATA_nPreferDistance);
  tolua_variable(tolua_S,"nWithdrawThreshold",tolua_get_NEW_AI_DATA_nWithdrawThreshold,tolua_set_NEW_AI_DATA_nWithdrawThreshold);
  tolua_variable(tolua_S,"nChaseThreshold",tolua_get_NEW_AI_DATA_nChaseThreshold,tolua_set_NEW_AI_DATA_nChaseThreshold);
  tolua_variable(tolua_S,"nChaseDelayTime",tolua_get_NEW_AI_DATA_nChaseDelayTime,tolua_set_NEW_AI_DATA_nChaseDelayTime);
  tolua_array(tolua_S,"nInitAuraID",tolua_get_ai_NEW_AI_DATA_nInitAuraID,tolua_set_ai_NEW_AI_DATA_nInitAuraID);
  tolua_variable(tolua_S,"nLiveTime",tolua_get_NEW_AI_DATA_nLiveTime,tolua_set_NEW_AI_DATA_nLiveTime);
  tolua_variable(tolua_S,"bDisappearOnTimeout",tolua_get_NEW_AI_DATA_bDisappearOnTimeout,tolua_set_NEW_AI_DATA_bDisappearOnTimeout);
  tolua_variable(tolua_S,"nWanderRange",tolua_get_NEW_AI_DATA_nWanderRange,tolua_set_NEW_AI_DATA_nWanderRange);
  tolua_variable(tolua_S,"nWanderInterval",tolua_get_NEW_AI_DATA_nWanderInterval,tolua_set_NEW_AI_DATA_nWanderInterval);
  tolua_array(tolua_S,"nSpellID",tolua_get_ai_NEW_AI_DATA_nSpellID,tolua_set_ai_NEW_AI_DATA_nSpellID);
  tolua_array(tolua_S,"nSpellChance",tolua_get_ai_NEW_AI_DATA_nSpellChance,tolua_set_ai_NEW_AI_DATA_nSpellChance);
  tolua_array(tolua_S,"nSpellCDTime",tolua_get_ai_NEW_AI_DATA_nSpellCDTime,tolua_set_ai_NEW_AI_DATA_nSpellCDTime);
  tolua_array(tolua_S,"nSelfHpPercent",tolua_get_ai_NEW_AI_DATA_nSelfHpPercent,tolua_set_ai_NEW_AI_DATA_nSelfHpPercent);
  tolua_variable(tolua_S,"nGlobalCDTime",tolua_get_NEW_AI_DATA_nGlobalCDTime,tolua_set_NEW_AI_DATA_nGlobalCDTime);
  tolua_variable(tolua_S,"nFriendlyNpcTemplateID",tolua_get_NEW_AI_DATA_nFriendlyNpcTemplateID,tolua_set_NEW_AI_DATA_nFriendlyNpcTemplateID);
  tolua_variable(tolua_S,"bFriendlyCorpse",tolua_get_NEW_AI_DATA_bFriendlyCorpse,tolua_set_NEW_AI_DATA_bFriendlyCorpse);
  tolua_variable(tolua_S,"nCorpseTemplateID",tolua_get_NEW_AI_DATA_nCorpseTemplateID,tolua_set_NEW_AI_DATA_nCorpseTemplateID);
  tolua_variable(tolua_S,"nIssuerSpellSignalType",tolua_get_NEW_AI_DATA_nIssuerSpellSignalType,tolua_set_NEW_AI_DATA_nIssuerSpellSignalType);
  tolua_variable(tolua_S,"nIssuerSpellSignalRange",tolua_get_NEW_AI_DATA_nIssuerSpellSignalRange,tolua_set_NEW_AI_DATA_nIssuerSpellSignalRange);
  tolua_variable(tolua_S,"nTargetSpellSignalType",tolua_get_NEW_AI_DATA_nTargetSpellSignalType,tolua_set_NEW_AI_DATA_nTargetSpellSignalType);
  tolua_variable(tolua_S,"nTargetSpellSignalRange",tolua_get_NEW_AI_DATA_nTargetSpellSignalRange,tolua_set_NEW_AI_DATA_nTargetSpellSignalRange);
  tolua_variable(tolua_S,"nFleeHpPercent",tolua_get_NEW_AI_DATA_nFleeHpPercent,tolua_set_NEW_AI_DATA_nFleeHpPercent);
  tolua_variable(tolua_S,"nFleeChance",tolua_get_NEW_AI_DATA_nFleeChance,tolua_set_NEW_AI_DATA_nFleeChance);
  tolua_variable(tolua_S,"nFleeDuration",tolua_get_NEW_AI_DATA_nFleeDuration,tolua_set_NEW_AI_DATA_nFleeDuration);
  tolua_variable(tolua_S,"nStepAroundChance",tolua_get_NEW_AI_DATA_nStepAroundChance,tolua_set_NEW_AI_DATA_nStepAroundChance);
  tolua_variable(tolua_S,"nStepAroundCDTime",tolua_get_NEW_AI_DATA_nStepAroundCDTime,tolua_set_NEW_AI_DATA_nStepAroundCDTime);
  tolua_variable(tolua_S,"nChangeTargetChance",tolua_get_NEW_AI_DATA_nChangeTargetChance,tolua_set_NEW_AI_DATA_nChangeTargetChance);
  tolua_variable(tolua_S,"nChangeTargetCDTime",tolua_get_NEW_AI_DATA_nChangeTargetCDTime,tolua_set_NEW_AI_DATA_nChangeTargetCDTime);
  tolua_variable(tolua_S,"nSpreadThreatCount",tolua_get_NEW_AI_DATA_nSpreadThreatCount,tolua_set_NEW_AI_DATA_nSpreadThreatCount);
  tolua_array(tolua_S,"nParam",tolua_get_ai_NEW_AI_DATA_nParam,tolua_set_ai_NEW_AI_DATA_nParam);
#ifndef TOLUA_DISABLE_tolua_ai_NEW_AI_DATA_ReadLine00
  tolua_function(tolua_S,"ReadLine",tolua_ai_NEW_AI_DATA_ReadLine00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CAIProcessor","CAIProcessor","",NULL);
 tolua_beginmodule(tolua_S,"CAIProcessor");
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetOwner00
  tolua_function(tolua_S,"GetOwner",tolua_ai_CAIProcessor_GetOwner00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetAIID00
  tolua_function(tolua_S,"GetAIID",tolua_ai_CAIProcessor_GetAIID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Stop00
  tolua_function(tolua_S,"Stop",tolua_ai_CAIProcessor_Stop00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_MoveTo00
  tolua_function(tolua_S,"MoveTo",tolua_ai_CAIProcessor_MoveTo00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SyncMoveTo00
  tolua_function(tolua_S,"SyncMoveTo",tolua_ai_CAIProcessor_SyncMoveTo00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Wander00
  tolua_function(tolua_S,"Wander",tolua_ai_CAIProcessor_Wander00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Patrol00
  tolua_function(tolua_S,"Patrol",tolua_ai_CAIProcessor_Patrol00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Chase00
  tolua_function(tolua_S,"Chase",tolua_ai_CAIProcessor_Chase00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Withdraw00
  tolua_function(tolua_S,"Withdraw",tolua_ai_CAIProcessor_Withdraw00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_StepAround00
  tolua_function(tolua_S,"StepAround",tolua_ai_CAIProcessor_StepAround00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Follow00
  tolua_function(tolua_S,"Follow",tolua_ai_CAIProcessor_Follow00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_Flee00
  tolua_function(tolua_S,"Flee",tolua_ai_CAIProcessor_Flee00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_NeedChase00
  tolua_function(tolua_S,"NeedChase",tolua_ai_CAIProcessor_NeedChase00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_NeedWithdraw00
  tolua_function(tolua_S,"NeedWithdraw",tolua_ai_CAIProcessor_NeedWithdraw00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GoHome00
  tolua_function(tolua_S,"GoHome",tolua_ai_CAIProcessor_GoHome00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_CallInitBT00
  tolua_function(tolua_S,"CallInitBT",tolua_ai_CAIProcessor_CallInitBT00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_PrintAllBT00
  tolua_function(tolua_S,"PrintAllBT",tolua_ai_CAIProcessor_PrintAllBT00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetInteractRoleID00
  tolua_function(tolua_S,"GetInteractRoleID",tolua_ai_CAIProcessor_GetInteractRoleID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SetVariable00
  tolua_function(tolua_S,"SetVariable",tolua_ai_CAIProcessor_SetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetVariable00
  tolua_function(tolua_S,"GetVariable",tolua_ai_CAIProcessor_GetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetBossState00
  tolua_function(tolua_S,"GetBossState",tolua_ai_CAIProcessor_GetBossState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SetBossState00
  tolua_function(tolua_S,"SetBossState",tolua_ai_CAIProcessor_SetBossState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SetTargetID00
  tolua_function(tolua_S,"SetTargetID",tolua_ai_CAIProcessor_SetTargetID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetTargetID00
  tolua_function(tolua_S,"GetTargetID",tolua_ai_CAIProcessor_GetTargetID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetNearestEnemyID00
  tolua_function(tolua_S,"GetNearestEnemyID",tolua_ai_CAIProcessor_GetNearestEnemyID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetFarthestEnemyID00
  tolua_function(tolua_S,"GetFarthestEnemyID",tolua_ai_CAIProcessor_GetFarthestEnemyID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_GetCastingEnemyID00
  tolua_function(tolua_S,"GetCastingEnemyID",tolua_ai_CAIProcessor_GetCastingEnemyID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SetIgnoreInvisible00
  tolua_function(tolua_S,"SetIgnoreInvisible",tolua_ai_CAIProcessor_SetIgnoreInvisible00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_IgnoreInvisible00
  tolua_function(tolua_S,"IgnoreInvisible",tolua_ai_CAIProcessor_IgnoreInvisible00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SetCounterInvisible00
  tolua_function(tolua_S,"SetCounterInvisible",tolua_ai_CAIProcessor_SetCounterInvisible00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_CounterInvisible00
  tolua_function(tolua_S,"CounterInvisible",tolua_ai_CAIProcessor_CounterInvisible00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ai_CAIProcessor_SetFollowParam00
  tolua_function(tolua_S,"SetFollowParam",tolua_ai_CAIProcessor_SetFollowParam00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ai (lua_State* tolua_S) {
 return tolua_ai_open(tolua_S);
};
#endif

