/*
** Lua binding: ms_chat
** Generated automatically by tolua++-1.0.92 on 05/30/18 13:59:44.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_ms_chat_open (lua_State* tolua_S);

#include "../../../Common/define/chat_def.h"
#include "./chat/ms_chat.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CMSChatMgr");
}

/* method: GetInstance of class  CMSChatMgr */
#ifndef TOLUA_DISABLE_tolua_ms_chat_CMSChatMgr_GetInstance00
static int tolua_ms_chat_CMSChatMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CMSChatMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CMSChatMgr& tolua_ret = (CMSChatMgr&)  CMSChatMgr::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CMSChatMgr");
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

/* method: Say of class  CMSChatMgr */
#ifndef TOLUA_DISABLE_tolua_ms_chat_CMSChatMgr_Say00
static int tolua_ms_chat_CMSChatMgr_Say00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CMSChatMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isstring(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CMSChatMgr* self = (CMSChatMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwSourceRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwTargetRoleID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  signed int nShowLocation = (( signed int)  tolua_tonumber(tolua_S,4,0));
  const char* pText = ((const char*)  tolua_tostring(tolua_S,5,0));
  signed int nGroupID = (( signed int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Say'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->Say(dwSourceRoleID,dwTargetRoleID,nShowLocation,pText,nGroupID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Say'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ms_chat_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_CHAT_MESSAGE_LEN",MAX_CHAT_MESSAGE_LEN);
 tolua_constant(tolua_S,"CHAT_SYSTEM_ID",CHAT_SYSTEM_ID);
  tolua_constant(tolua_S,"cctInvalid",cctInvalid);
  tolua_constant(tolua_S,"cctScreen",cctScreen);
  tolua_constant(tolua_S,"cctScene",cctScene);
  tolua_constant(tolua_S,"cctGroup",cctGroup);
  tolua_constant(tolua_S,"cctServer",cctServer);
  tolua_constant(tolua_S,"cctTotal",cctTotal);
  tolua_constant(tolua_S,"cltInvalid",cltInvalid);
  tolua_constant(tolua_S,"cltNormal",cltNormal);
  tolua_constant(tolua_S,"cltLighting",cltLighting);
  tolua_constant(tolua_S,"cltTvShow",cltTvShow);
  tolua_constant(tolua_S,"cltUrl",cltUrl);
  tolua_constant(tolua_S,"cltDialog",cltDialog);
  tolua_constant(tolua_S,"cltTrumpet",cltTrumpet);
  tolua_constant(tolua_S,"cltGMTrumpet",cltGMTrumpet);
  tolua_constant(tolua_S,"cltTotal",cltTotal);
 tolua_cclass(tolua_S,"CMSChatMgr","CMSChatMgr","",NULL);
 tolua_beginmodule(tolua_S,"CMSChatMgr");
#ifndef TOLUA_DISABLE_tolua_ms_chat_CMSChatMgr_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_ms_chat_CMSChatMgr_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_ms_chat_CMSChatMgr_Say00
  tolua_function(tolua_S,"Say",tolua_ms_chat_CMSChatMgr_Say00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ms_chat (lua_State* tolua_S) {
 return tolua_ms_chat_open(tolua_S);
};
#endif

