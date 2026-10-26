/*
** Lua binding: master_mgr
** Generated automatically by tolua++-1.0.92 on 05/30/18 13:59:44.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_master_mgr_open (lua_State* tolua_S);

#include "../../../Common/define/master_def.h"
#include "./master/master_mgr.h"
#include "role_data.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CMasterMgr");
 tolua_usertype(tolua_S,"MS_ROLE_DATA");
 tolua_usertype(tolua_S,"MS_ONLINE_ROLE_DATA");
}

/* method: GetInstance of class  CMasterMgr */
#ifndef TOLUA_DISABLE_tolua_master_mgr_CMasterMgr_GetInstance00
static int tolua_master_mgr_CMasterMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CMasterMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CMasterMgr& tolua_ret = (CMasterMgr&)  CMasterMgr::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CMasterMgr");
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

/* method: BeMaster of class  CMasterMgr */
#ifndef TOLUA_DISABLE_tolua_master_mgr_CMasterMgr_BeMaster00
static int tolua_master_mgr_CMasterMgr_BeMaster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMasterMgr",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"MS_ROLE_DATA",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMasterMgr* self = (CMasterMgr*)  tolua_tousertype(tolua_S,1,0);
  MS_ROLE_DATA* pRole = ((MS_ROLE_DATA*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BeMaster'", NULL);
#endif
 {
 int tolua_ret = (int)
self->BeMaster(pRole);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BeMaster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateMasterRelation of class  CMasterMgr */
#ifndef TOLUA_DISABLE_tolua_master_mgr_CMasterMgr_CreateMasterRelation00
static int tolua_master_mgr_CMasterMgr_CreateMasterRelation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMasterMgr",0,&tolua_err) ||
 (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"MS_ONLINE_ROLE_DATA",0,&tolua_err)) ||
 (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"MS_ONLINE_ROLE_DATA",0,&tolua_err)) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMasterMgr* self = (CMasterMgr*)  tolua_tousertype(tolua_S,1,0);
  MS_ONLINE_ROLE_DATA* teacher = ((MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,2,0));
  MS_ONLINE_ROLE_DATA* student = ((MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateMasterRelation'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->CreateMasterRelation(*teacher,*student);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateMasterRelation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelMasterRelation of class  CMasterMgr */
#ifndef TOLUA_DISABLE_tolua_master_mgr_CMasterMgr_DelMasterRelation00
static int tolua_master_mgr_CMasterMgr_DelMasterRelation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMasterMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"MS_ROLE_DATA",0,&tolua_err)) ||
 !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMasterMgr* self = (CMasterMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTeacherID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  MS_ROLE_DATA* student = ((MS_ROLE_DATA*)  tolua_tousertype(tolua_S,3,0));
   bool bIsGrad = ((  bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelMasterRelation'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->DelMasterRelation(dwTeacherID,*student,bIsGrad);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelMasterRelation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_master_mgr_open (lua_State* tolua_S)
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
 tolua_cclass(tolua_S,"CMasterMgr","CMasterMgr","",NULL);
 tolua_beginmodule(tolua_S,"CMasterMgr");
#ifndef TOLUA_DISABLE_tolua_master_mgr_CMasterMgr_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_master_mgr_CMasterMgr_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_master_mgr_CMasterMgr_BeMaster00
  tolua_function(tolua_S,"BeMaster",tolua_master_mgr_CMasterMgr_BeMaster00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_master_mgr_CMasterMgr_CreateMasterRelation00
  tolua_function(tolua_S,"CreateMasterRelation",tolua_master_mgr_CMasterMgr_CreateMasterRelation00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_master_mgr_CMasterMgr_DelMasterRelation00
  tolua_function(tolua_S,"DelMasterRelation",tolua_master_mgr_CMasterMgr_DelMasterRelation00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_master_mgr (lua_State* tolua_S) {
 return tolua_master_mgr_open(tolua_S);
};
#endif

