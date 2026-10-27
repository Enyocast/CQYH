/*
** Lua binding: master
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_master_open (lua_State* tolua_S);

#include "../../../Common/define/master_def.h"
#include "master.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CMaster");
 tolua_usertype(tolua_S,"CRole");
}

/* method: IsTeacher of class  CMaster */
#ifndef TOLUA_DISABLE_tolua_master_CMaster_IsTeacher00
static int tolua_master_CMaster_IsTeacher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMaster",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMaster* self = (CMaster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsTeacher'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsTeacher();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsTeacher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsStudent of class  CMaster */
#ifndef TOLUA_DISABLE_tolua_master_CMaster_IsStudent00
static int tolua_master_CMaster_IsStudent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMaster",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMaster* self = (CMaster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsStudent'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsStudent();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsStudent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStudentCount of class  CMaster */
#ifndef TOLUA_DISABLE_tolua_master_CMaster_GetStudentCount00
static int tolua_master_CMaster_GetStudentCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMaster",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMaster* self = (CMaster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStudentCount'", NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->GetStudentCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStudentCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsStudentFull of class  CMaster */
#ifndef TOLUA_DISABLE_tolua_master_CMaster_IsStudentFull00
static int tolua_master_CMaster_IsStudentFull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMaster",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMaster* self = (CMaster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsStudentFull'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsStudentFull();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsStudentFull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetState of class  CMaster */
#ifndef TOLUA_DISABLE_tolua_master_CMaster_GetState00
static int tolua_master_CMaster_GetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMaster",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMaster* self = (CMaster*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetCD of class  CMaster */
#ifndef TOLUA_DISABLE_tolua_master_CMaster_GetCD00
static int tolua_master_CMaster_GetCD00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMaster",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMaster* self = (CMaster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCD'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetCD();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCD'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStudentByIndex of class  CMaster */
#ifndef TOLUA_DISABLE_tolua_master_CMaster_GetStudentByIndex00
static int tolua_master_CMaster_GetStudentByIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMaster",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMaster* self = (CMaster*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStudentByIndex'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetStudentByIndex(nIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStudentByIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTeacherID of class  CMaster */
#ifndef TOLUA_DISABLE_tolua_master_CMaster_GetTeacherID00
static int tolua_master_CMaster_GetTeacherID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMaster",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMaster* self = (CMaster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTeacherID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetTeacherID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTeacherID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaSyncMasterExpToMS of class  CMaster */
#ifndef TOLUA_DISABLE_tolua_master_CMaster_LuaSyncMasterExpToMS00
static int tolua_master_CMaster_LuaSyncMasterExpToMS00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMaster",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMaster* self = (CMaster*)  tolua_tousertype(tolua_S,1,0);
  CRole* poRole = ((CRole*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaSyncMasterExpToMS'", NULL);
#endif
 {
 int tolua_ret = (int)
self->LuaSyncMasterExpToMS(poRole);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaSyncMasterExpToMS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_master_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_STUDENT_NUM",MAX_STUDENT_NUM);
 tolua_constant(tolua_S,"GRADUATE_LEVEL",GRADUATE_LEVEL);
 tolua_constant(tolua_S,"STUD_LEVEL_LOWER_LIMIT",STUD_LEVEL_LOWER_LIMIT);
 tolua_constant(tolua_S,"REGET_MASTER_CD",REGET_MASTER_CD);
 tolua_constant(tolua_S,"APPLY_VALID_TIME",APPLY_VALID_TIME);
 tolua_constant(tolua_S,"SEND_MASTER_INFO_NUM",SEND_MASTER_INFO_NUM);
 tolua_constant(tolua_S,"SEND_SOLO_INFO_NUM",SEND_SOLO_INFO_NUM);
 tolua_constant(tolua_S,"MAX_CZ_TEXT_LENGTH",MAX_CZ_TEXT_LENGTH);
 tolua_constant(tolua_S,"MAX_MASTER_SEND_APP_NUM",MAX_MASTER_SEND_APP_NUM);
 tolua_constant(tolua_S,"MAX_MASTER_RECV_APP_NUM",MAX_MASTER_RECV_APP_NUM);
  tolua_constant(tolua_S,"MASTER_NONE",MASTER_NONE);
  tolua_constant(tolua_S,"MASTER_STUDENT",MASTER_STUDENT);
  tolua_constant(tolua_S,"MASTER_TEACHER",MASTER_TEACHER);
  tolua_constant(tolua_S,"MASTER_BECOME_TEACHER",MASTER_BECOME_TEACHER);
  tolua_constant(tolua_S,"MASTER_CONG_BEGIN",MASTER_CONG_BEGIN);
  tolua_constant(tolua_S,"MASTER_CONG_BY_FREE",MASTER_CONG_BY_FREE);
  tolua_constant(tolua_S,"MASTER_CONG_BY_MONEY",MASTER_CONG_BY_MONEY);
  tolua_constant(tolua_S,"MASTER_CONG_BY_GOLD",MASTER_CONG_BY_GOLD);
  tolua_constant(tolua_S,"MASTER_CONG_END",MASTER_CONG_END);
  tolua_constant(tolua_S,"MTAT_FROM_COMMON",MTAT_FROM_COMMON);
  tolua_constant(tolua_S,"MTAT_FROM_TWITTER",MTAT_FROM_TWITTER);
  tolua_constant(tolua_S,"MST_APPLY_RECRUIT_SUCC",MST_APPLY_RECRUIT_SUCC);
  tolua_constant(tolua_S,"MST_CANCEL_RECRUIT_SUCC",MST_CANCEL_RECRUIT_SUCC);
  tolua_constant(tolua_S,"MST_SYNC_GS_CD",MST_SYNC_GS_CD);
  tolua_constant(tolua_S,"MST_SYNC_GS_TWITTER_CD",MST_SYNC_GS_TWITTER_CD);
  tolua_constant(tolua_S,"MST_SYNC_PUNISH_EXP",MST_SYNC_PUNISH_EXP);
  tolua_constant(tolua_S,"MST_SYNC_MASTER_EXP_DEC",MST_SYNC_MASTER_EXP_DEC);
 tolua_cclass(tolua_S,"CMaster","CMaster","",NULL);
 tolua_beginmodule(tolua_S,"CMaster");
#ifndef TOLUA_DISABLE_tolua_master_CMaster_IsTeacher00
  tolua_function(tolua_S,"IsTeacher",tolua_master_CMaster_IsTeacher00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_master_CMaster_IsStudent00
  tolua_function(tolua_S,"IsStudent",tolua_master_CMaster_IsStudent00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_master_CMaster_GetStudentCount00
  tolua_function(tolua_S,"GetStudentCount",tolua_master_CMaster_GetStudentCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_master_CMaster_IsStudentFull00
  tolua_function(tolua_S,"IsStudentFull",tolua_master_CMaster_IsStudentFull00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_master_CMaster_GetState00
  tolua_function(tolua_S,"GetState",tolua_master_CMaster_GetState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_master_CMaster_GetCD00
  tolua_function(tolua_S,"GetCD",tolua_master_CMaster_GetCD00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_master_CMaster_GetStudentByIndex00
  tolua_function(tolua_S,"GetStudentByIndex",tolua_master_CMaster_GetStudentByIndex00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_master_CMaster_GetTeacherID00
  tolua_function(tolua_S,"GetTeacherID",tolua_master_CMaster_GetTeacherID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_master_CMaster_LuaSyncMasterExpToMS00
  tolua_function(tolua_S,"LuaSyncMasterExpToMS",tolua_master_CMaster_LuaSyncMasterExpToMS00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_master (lua_State* tolua_S) {
 return tolua_master_open(tolua_S);
};
#endif

