/*
** Lua binding: achievement_list
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_achievement_list_open (lua_State* tolua_S);

#include "achievement_list.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CAchievementsList");
}

/* method: CanComplete of class  CAchievementsList */
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_CanComplete00
static int tolua_achievement_list_CAchievementsList_CanComplete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAchievementsList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAchievementsList* self = (CAchievementsList*)  tolua_tousertype(tolua_S,1,0);
  signed int nAchievementID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanComplete'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->CanComplete(nAchievementID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanComplete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Complete of class  CAchievementsList */
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_Complete00
static int tolua_achievement_list_CAchievementsList_Complete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAchievementsList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAchievementsList* self = (CAchievementsList*)  tolua_tousertype(tolua_S,1,0);
  signed int nAchievementID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Complete'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->Complete(nAchievementID);
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

/* method: GetCompletedCount of class  CAchievementsList */
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_GetCompletedCount00
static int tolua_achievement_list_CAchievementsList_GetCompletedCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAchievementsList",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAchievementsList* self = (CAchievementsList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCompletedCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetCompletedCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCompletedCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanReward of class  CAchievementsList */
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_CanReward00
static int tolua_achievement_list_CAchievementsList_CanReward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAchievementsList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAchievementsList* self = (CAchievementsList*)  tolua_tousertype(tolua_S,1,0);
  signed int nAchievementID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanReward'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->CanReward(nAchievementID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanReward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reward of class  CAchievementsList */
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_Reward00
static int tolua_achievement_list_CAchievementsList_Reward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAchievementsList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAchievementsList* self = (CAchievementsList*)  tolua_tousertype(tolua_S,1,0);
  signed int nAchievementID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Reward'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->Reward(nAchievementID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Reward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVariable of class  CAchievementsList */
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_GetVariable00
static int tolua_achievement_list_CAchievementsList_GetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAchievementsList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAchievementsList* self = (CAchievementsList*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetVariable of class  CAchievementsList */
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_SetVariable00
static int tolua_achievement_list_CAchievementsList_SetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAchievementsList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAchievementsList* self = (CAchievementsList*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddVariable of class  CAchievementsList */
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_AddVariable00
static int tolua_achievement_list_CAchievementsList_AddVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAchievementsList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAchievementsList* self = (CAchievementsList*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nCount = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddVariable'", NULL);
#endif
 {
  self->AddVariable(nIndex,nCount);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ActivateHandbook of class  CAchievementsList */
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_ActivateHandbook00
static int tolua_achievement_list_CAchievementsList_ActivateHandbook00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAchievementsList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAchievementsList* self = (CAchievementsList*)  tolua_tousertype(tolua_S,1,0);
  signed int nHandbookType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ActivateHandbook'", NULL);
#endif
 {
  self->ActivateHandbook(nHandbookType,nIndex);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ActivateHandbook'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_achievement_list_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CAchievementsList","CAchievementsList","",NULL);
 tolua_beginmodule(tolua_S,"CAchievementsList");
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_CanComplete00
  tolua_function(tolua_S,"CanComplete",tolua_achievement_list_CAchievementsList_CanComplete00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_Complete00
  tolua_function(tolua_S,"Complete",tolua_achievement_list_CAchievementsList_Complete00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_GetCompletedCount00
  tolua_function(tolua_S,"GetCompletedCount",tolua_achievement_list_CAchievementsList_GetCompletedCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_CanReward00
  tolua_function(tolua_S,"CanReward",tolua_achievement_list_CAchievementsList_CanReward00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_Reward00
  tolua_function(tolua_S,"Reward",tolua_achievement_list_CAchievementsList_Reward00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_GetVariable00
  tolua_function(tolua_S,"GetVariable",tolua_achievement_list_CAchievementsList_GetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_SetVariable00
  tolua_function(tolua_S,"SetVariable",tolua_achievement_list_CAchievementsList_SetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_AddVariable00
  tolua_function(tolua_S,"AddVariable",tolua_achievement_list_CAchievementsList_AddVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_achievement_list_CAchievementsList_ActivateHandbook00
  tolua_function(tolua_S,"ActivateHandbook",tolua_achievement_list_CAchievementsList_ActivateHandbook00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_achievement_list (lua_State* tolua_S) {
 return tolua_achievement_list_open(tolua_S);
};
#endif

