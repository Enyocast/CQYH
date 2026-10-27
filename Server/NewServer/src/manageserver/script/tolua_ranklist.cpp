/*
** Lua binding: ranklist
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_ranklist_open (lua_State* tolua_S);

#include "./ranklist/ranklist.h"
#include "./ranklist/ranklist.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CRankListMgr");
}

/* method: GetInstance of class  CRankListMgr */
#ifndef TOLUA_DISABLE_tolua_ranklist_CRankListMgr_GetInstance00
static int tolua_ranklist_CRankListMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CRankListMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CRankListMgr& tolua_ret = (CRankListMgr&)  CRankListMgr::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CRankListMgr");
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

/* method: DelGuildRankNode of class  CRankListMgr */
#ifndef TOLUA_DISABLE_tolua_ranklist_CRankListMgr_DelGuildRankNode00
static int tolua_ranklist_CRankListMgr_DelGuildRankNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CRankListMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CRankListMgr* self = (CRankListMgr*)  tolua_tousertype(tolua_S,1,0);
  signed int nServerGroupID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwGuildID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelGuildRankNode'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DelGuildRankNode(nServerGroupID,dwGuildID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelGuildRankNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ranklist_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CRankListMgr","CRankListMgr","",NULL);
 tolua_beginmodule(tolua_S,"CRankListMgr");
#ifndef TOLUA_DISABLE_tolua_ranklist_CRankListMgr_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_ranklist_CRankListMgr_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ranklist_CRankListMgr_DelGuildRankNode00
  tolua_function(tolua_S,"DelGuildRankNode",tolua_ranklist_CRankListMgr_DelGuildRankNode00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ranklist (lua_State* tolua_S) {
 return tolua_ranklist_open(tolua_S);
};
#endif

