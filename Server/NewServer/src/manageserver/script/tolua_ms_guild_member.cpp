/*
** Lua binding: ms_guild_member
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_ms_guild_member_open (lua_State* tolua_S);

#include "../../../Common/define/guild_def.h"
#include "./guild/ms_guild_member.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CMsGuildMember");
}

/* method: GetRoleID of class  CMsGuildMember */
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_GetRoleID00
static int tolua_ms_guild_member_CMsGuildMember_GetRoleID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMember",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMember* self = (CMsGuildMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoleID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetRoleID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRoleID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPosition of class  CMsGuildMember */
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_GetPosition00
static int tolua_ms_guild_member_CMsGuildMember_GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMember",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMember* self = (CMsGuildMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPosition'", NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->GetPosition();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPosition of class  CMsGuildMember */
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_SetPosition00
static int tolua_ms_guild_member_CMsGuildMember_SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMember",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMember* self = (CMsGuildMember*)  tolua_tousertype(tolua_S,1,0);
  unsigned char byPosition = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPosition'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetPosition(byPosition);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFlag of class  CMsGuildMember */
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_GetFlag00
static int tolua_ms_guild_member_CMsGuildMember_GetFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMember",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMember* self = (CMsGuildMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFlag'", NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->GetFlag();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFlag of class  CMsGuildMember */
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_SetFlag00
static int tolua_ms_guild_member_CMsGuildMember_SetFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMember",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMember* self = (CMsGuildMember*)  tolua_tousertype(tolua_S,1,0);
  unsigned char byFlag = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFlag'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetFlag(byFlag);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSalary of class  CMsGuildMember */
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_GetSalary00
static int tolua_ms_guild_member_CMsGuildMember_GetSalary00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMember",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMember* self = (CMsGuildMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSalary'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetSalary();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSalary'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSalary of class  CMsGuildMember */
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_AddSalary00
static int tolua_ms_guild_member_CMsGuildMember_AddSalary00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMember",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMember* self = (CMsGuildMember*)  tolua_tousertype(tolua_S,1,0);
  signed int nSalary = (( signed int)  tolua_tonumber(tolua_S,2,0));
   bool isSave = ((  bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSalary'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddSalary(nSalary,isSave);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSalary'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SubSalary of class  CMsGuildMember */
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_SubSalary00
static int tolua_ms_guild_member_CMsGuildMember_SubSalary00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMember",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMember* self = (CMsGuildMember*)  tolua_tousertype(tolua_S,1,0);
  signed int nSalary = (( signed int)  tolua_tonumber(tolua_S,2,0));
   bool isSave = ((  bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SubSalary'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SubSalary(nSalary,isSave);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SubSalary'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDrawSalaryTime of class  CMsGuildMember */
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_GetDrawSalaryTime00
static int tolua_ms_guild_member_CMsGuildMember_GetDrawSalaryTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMember",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMember* self = (CMsGuildMember*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDrawSalaryTime'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetDrawSalaryTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDrawSalaryTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDrawSalaryTime of class  CMsGuildMember */
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_SetDrawSalaryTime00
static int tolua_ms_guild_member_CMsGuildMember_SetDrawSalaryTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMsGuildMember",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMsGuildMember* self = (CMsGuildMember*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDrawSalaryTime'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetDrawSalaryTime(dwTime);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDrawSalaryTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ms_guild_member_open (lua_State* tolua_S)
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
 tolua_cclass(tolua_S,"CMsGuildMember","CMsGuildMember","",NULL);
 tolua_beginmodule(tolua_S,"CMsGuildMember");
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_GetRoleID00
  tolua_function(tolua_S,"GetRoleID",tolua_ms_guild_member_CMsGuildMember_GetRoleID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_GetPosition00
  tolua_function(tolua_S,"GetPosition",tolua_ms_guild_member_CMsGuildMember_GetPosition00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_SetPosition00
  tolua_function(tolua_S,"SetPosition",tolua_ms_guild_member_CMsGuildMember_SetPosition00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_GetFlag00
  tolua_function(tolua_S,"GetFlag",tolua_ms_guild_member_CMsGuildMember_GetFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_SetFlag00
  tolua_function(tolua_S,"SetFlag",tolua_ms_guild_member_CMsGuildMember_SetFlag00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_GetSalary00
  tolua_function(tolua_S,"GetSalary",tolua_ms_guild_member_CMsGuildMember_GetSalary00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_AddSalary00
  tolua_function(tolua_S,"AddSalary",tolua_ms_guild_member_CMsGuildMember_AddSalary00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_SubSalary00
  tolua_function(tolua_S,"SubSalary",tolua_ms_guild_member_CMsGuildMember_SubSalary00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_GetDrawSalaryTime00
  tolua_function(tolua_S,"GetDrawSalaryTime",tolua_ms_guild_member_CMsGuildMember_GetDrawSalaryTime00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_guild_member_CMsGuildMember_SetDrawSalaryTime00
  tolua_function(tolua_S,"SetDrawSalaryTime",tolua_ms_guild_member_CMsGuildMember_SetDrawSalaryTime00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ms_guild_member (lua_State* tolua_S) {
 return tolua_ms_guild_member_open(tolua_S);
};
#endif

