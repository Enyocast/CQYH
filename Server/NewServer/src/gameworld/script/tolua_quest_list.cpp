/*
** Lua binding: quest_list
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_quest_list_open (lua_State* tolua_S);

#include "quest_list.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"ACCEPTED_QUEST");
 tolua_usertype(tolua_S,"CQuestList");
}

/* get function: nQuestID of class  ACCEPTED_QUEST */
#ifndef TOLUA_DISABLE_tolua_get_ACCEPTED_QUEST_nQuestID
static int tolua_get_ACCEPTED_QUEST_nQuestID(lua_State* tolua_S)
{
  ACCEPTED_QUEST* self = (ACCEPTED_QUEST*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nQuestID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nQuestID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nQuestID of class  ACCEPTED_QUEST */
#ifndef TOLUA_DISABLE_tolua_set_ACCEPTED_QUEST_nQuestID
static int tolua_set_ACCEPTED_QUEST_nQuestID(lua_State* tolua_S)
{
  ACCEPTED_QUEST* self = (ACCEPTED_QUEST*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nQuestID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nQuestID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwAcceptTime of class  ACCEPTED_QUEST */
#ifndef TOLUA_DISABLE_tolua_get_ACCEPTED_QUEST_unsigned_dwAcceptTime
static int tolua_get_ACCEPTED_QUEST_unsigned_dwAcceptTime(lua_State* tolua_S)
{
  ACCEPTED_QUEST* self = (ACCEPTED_QUEST*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwAcceptTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwAcceptTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwAcceptTime of class  ACCEPTED_QUEST */
#ifndef TOLUA_DISABLE_tolua_set_ACCEPTED_QUEST_unsigned_dwAcceptTime
static int tolua_set_ACCEPTED_QUEST_unsigned_dwAcceptTime(lua_State* tolua_S)
{
  ACCEPTED_QUEST* self = (ACCEPTED_QUEST*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwAcceptTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwAcceptTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nKillNpcCount of class  ACCEPTED_QUEST */
#ifndef TOLUA_DISABLE_tolua_get_quest_list_ACCEPTED_QUEST_nKillNpcCount
static int tolua_get_quest_list_ACCEPTED_QUEST_nKillNpcCount(lua_State* tolua_S)
{
 int tolua_index;
  ACCEPTED_QUEST* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ACCEPTED_QUEST*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_CONDITION_PER_QUEST)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nKillNpcCount[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nKillNpcCount of class  ACCEPTED_QUEST */
#ifndef TOLUA_DISABLE_tolua_set_quest_list_ACCEPTED_QUEST_nKillNpcCount
static int tolua_set_quest_list_ACCEPTED_QUEST_nKillNpcCount(lua_State* tolua_S)
{
 int tolua_index;
  ACCEPTED_QUEST* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ACCEPTED_QUEST*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_CONDITION_PER_QUEST)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->nKillNpcCount[tolua_index] = (( signed int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nVariable of class  ACCEPTED_QUEST */
#ifndef TOLUA_DISABLE_tolua_get_quest_list_ACCEPTED_QUEST_nVariable
static int tolua_get_quest_list_ACCEPTED_QUEST_nVariable(lua_State* tolua_S)
{
 int tolua_index;
  ACCEPTED_QUEST* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ACCEPTED_QUEST*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_VARIABLE_PER_QUEST)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nVariable[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nVariable of class  ACCEPTED_QUEST */
#ifndef TOLUA_DISABLE_tolua_set_quest_list_ACCEPTED_QUEST_nVariable
static int tolua_set_quest_list_ACCEPTED_QUEST_nVariable(lua_State* tolua_S)
{
 int tolua_index;
  ACCEPTED_QUEST* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ACCEPTED_QUEST*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_VARIABLE_PER_QUEST)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->nVariable[tolua_index] = (( signed int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAcceptedQuest of class  CQuestList */
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_GetAcceptedQuest00
static int tolua_quest_list_CQuestList_GetAcceptedQuest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CQuestList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CQuestList* self = (CQuestList*)  tolua_tousertype(tolua_S,1,0);
  signed int nQuestID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAcceptedQuest'", NULL);
#endif
 {
  const ACCEPTED_QUEST* tolua_ret = (const ACCEPTED_QUEST*)  self->GetAcceptedQuest(nQuestID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"const ACCEPTED_QUEST");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAcceptedQuest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVariable of class  CQuestList */
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_SetVariable00
static int tolua_quest_list_CQuestList_SetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CQuestList",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const ACCEPTED_QUEST",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CQuestList* self = (CQuestList*)  tolua_tousertype(tolua_S,1,0);
  const ACCEPTED_QUEST* pAcceptedQuest = ((const ACCEPTED_QUEST*)  tolua_tousertype(tolua_S,2,0));
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nValue = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVariable'", NULL);
#endif
 {
  self->SetVariable(pAcceptedQuest,nIndex,nValue);
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

/* method: GetVariable of class  CQuestList */
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_GetVariable00
static int tolua_quest_list_CQuestList_GetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CQuestList",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const ACCEPTED_QUEST",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CQuestList* self = (CQuestList*)  tolua_tousertype(tolua_S,1,0);
  const ACCEPTED_QUEST* pAcceptedQuest = ((const ACCEPTED_QUEST*)  tolua_tousertype(tolua_S,2,0));
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVariable'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetVariable(pAcceptedQuest,nIndex);
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

/* method: CanAbandon of class  CQuestList */
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_CanAbandon00
static int tolua_quest_list_CQuestList_CanAbandon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CQuestList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CQuestList* self = (CQuestList*)  tolua_tousertype(tolua_S,1,0);
  signed int nQuestID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanAbandon'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->CanAbandon(nQuestID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanAbandon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Abandon of class  CQuestList */
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_Abandon00
static int tolua_quest_list_CQuestList_Abandon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CQuestList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CQuestList* self = (CQuestList*)  tolua_tousertype(tolua_S,1,0);
  signed int nQuestID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Abandon'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->Abandon(nQuestID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Abandon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanAccept of class  CQuestList */
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_CanAccept00
static int tolua_quest_list_CQuestList_CanAccept00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CQuestList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CQuestList* self = (CQuestList*)  tolua_tousertype(tolua_S,1,0);
  signed int nQuestID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nAcceptType = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nSrcID = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanAccept'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->CanAccept(nQuestID,nAcceptType,nSrcID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanAccept'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Accept of class  CQuestList */
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_Accept00
static int tolua_quest_list_CQuestList_Accept00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CQuestList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CQuestList* self = (CQuestList*)  tolua_tousertype(tolua_S,1,0);
  signed int nQuestID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Accept'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->Accept(nQuestID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Accept'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Complete of class  CQuestList */
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_Complete00
static int tolua_quest_list_CQuestList_Complete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CQuestList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CQuestList* self = (CQuestList*)  tolua_tousertype(tolua_S,1,0);
  signed int nQuestID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nSelectedAwardIndex = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Complete'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->Complete(nQuestID,nSelectedAwardIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Complete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetQuestFailed of class  CQuestList */
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_SetQuestFailed00
static int tolua_quest_list_CQuestList_SetQuestFailed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CQuestList",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const ACCEPTED_QUEST",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CQuestList* self = (CQuestList*)  tolua_tousertype(tolua_S,1,0);
  const ACCEPTED_QUEST* pAcceptedQuest = ((const ACCEPTED_QUEST*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetQuestFailed'", NULL);
#endif
 {
  self->SetQuestFailed(pAcceptedQuest);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetQuestFailed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_quest_list_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"ACCEPTED_QUEST","ACCEPTED_QUEST","",NULL);
 tolua_beginmodule(tolua_S,"ACCEPTED_QUEST");
  tolua_variable(tolua_S,"nQuestID",tolua_get_ACCEPTED_QUEST_nQuestID,tolua_set_ACCEPTED_QUEST_nQuestID);
  tolua_variable(tolua_S,"dwAcceptTime",tolua_get_ACCEPTED_QUEST_unsigned_dwAcceptTime,tolua_set_ACCEPTED_QUEST_unsigned_dwAcceptTime);
  tolua_array(tolua_S,"nKillNpcCount",tolua_get_quest_list_ACCEPTED_QUEST_nKillNpcCount,tolua_set_quest_list_ACCEPTED_QUEST_nKillNpcCount);
  tolua_array(tolua_S,"nVariable",tolua_get_quest_list_ACCEPTED_QUEST_nVariable,tolua_set_quest_list_ACCEPTED_QUEST_nVariable);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CQuestList","CQuestList","",NULL);
 tolua_beginmodule(tolua_S,"CQuestList");
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_GetAcceptedQuest00
  tolua_function(tolua_S,"GetAcceptedQuest",tolua_quest_list_CQuestList_GetAcceptedQuest00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_SetVariable00
  tolua_function(tolua_S,"SetVariable",tolua_quest_list_CQuestList_SetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_GetVariable00
  tolua_function(tolua_S,"GetVariable",tolua_quest_list_CQuestList_GetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_CanAbandon00
  tolua_function(tolua_S,"CanAbandon",tolua_quest_list_CQuestList_CanAbandon00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_Abandon00
  tolua_function(tolua_S,"Abandon",tolua_quest_list_CQuestList_Abandon00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_CanAccept00
  tolua_function(tolua_S,"CanAccept",tolua_quest_list_CQuestList_CanAccept00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_Accept00
  tolua_function(tolua_S,"Accept",tolua_quest_list_CQuestList_Accept00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_Complete00
  tolua_function(tolua_S,"Complete",tolua_quest_list_CQuestList_Complete00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_quest_list_CQuestList_SetQuestFailed00
  tolua_function(tolua_S,"SetQuestFailed",tolua_quest_list_CQuestList_SetQuestFailed00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_quest_list (lua_State* tolua_S) {
 return tolua_quest_list_open(tolua_S);
};
#endif

