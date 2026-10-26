/*
** Lua binding: role_data_mgr
** Generated automatically by tolua++-1.0.92 on 05/30/18 13:59:46.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_role_data_mgr_open (lua_State* tolua_S);

#include "./role_data.h"
#include "role_data_mgr.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CRoleDataMgr");
 tolua_usertype(tolua_S,"MS_ROLE_DATA");
}

/* method: GetInstance of class  CRoleDataMgr */
#ifndef TOLUA_DISABLE_tolua_role_data_mgr_CRoleDataMgr_GetInstance00
static int tolua_role_data_mgr_CRoleDataMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CRoleDataMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CRoleDataMgr& tolua_ret = (CRoleDataMgr&)  CRoleDataMgr::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CRoleDataMgr");
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

/* method: FindRole of class  CRoleDataMgr */
#ifndef TOLUA_DISABLE_tolua_role_data_mgr_CRoleDataMgr_FindRole00
static int tolua_role_data_mgr_CRoleDataMgr_FindRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRoleDataMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRoleDataMgr* self = (CRoleDataMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindRole'", NULL);
#endif
 {
  MS_ROLE_DATA* tolua_ret = (MS_ROLE_DATA*)  self->FindRole(dwRoleID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"MS_ROLE_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindRoleByName of class  CRoleDataMgr */
#ifndef TOLUA_DISABLE_tolua_role_data_mgr_CRoleDataMgr_FindRoleByName00
static int tolua_role_data_mgr_CRoleDataMgr_FindRoleByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRoleDataMgr",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRoleDataMgr* self = (CRoleDataMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* pcszRoleName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindRoleByName'", NULL);
#endif
 {
  MS_ROLE_DATA* tolua_ret = (MS_ROLE_DATA*)  self->FindRoleByName(pcszRoleName);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"MS_ROLE_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindRoleByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_role_data_mgr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CRoleDataMgr","CRoleDataMgr","",NULL);
 tolua_beginmodule(tolua_S,"CRoleDataMgr");
#ifndef TOLUA_DISABLE_tolua_role_data_mgr_CRoleDataMgr_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_role_data_mgr_CRoleDataMgr_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_role_data_mgr_CRoleDataMgr_FindRole00
  tolua_function(tolua_S,"FindRole",tolua_role_data_mgr_CRoleDataMgr_FindRole00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_role_data_mgr_CRoleDataMgr_FindRoleByName00
  tolua_function(tolua_S,"FindRoleByName",tolua_role_data_mgr_CRoleDataMgr_FindRoleByName00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_role_data_mgr (lua_State* tolua_S) {
 return tolua_role_data_mgr_open(tolua_S);
};
#endif

