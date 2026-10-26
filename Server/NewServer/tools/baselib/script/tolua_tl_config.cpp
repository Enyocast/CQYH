/*
** Lua binding: tl_config
** Generated automatically by tolua++-1.0.92 on 05/07/18 16:30:10.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_tl_config_open (lua_State* tolua_S);

#include "../../inc/baselib/log.h"
#include "../../inc/baselib/tl_config.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_GM_GROUP_DATA (lua_State* tolua_S)
{
 GM_GROUP_DATA* self = (GM_GROUP_DATA*) tolua_tousertype(tolua_S,1,0);
 Mtolua_delete(self);
 return 0;
}

static int tolua_collect_GM_SVR (lua_State* tolua_S)
{
 GM_SVR* self = (GM_SVR*) tolua_tousertype(tolua_S,1,0);
 Mtolua_delete(self);
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"TL_CONFIG::GM_SVR_LIST");
 tolua_usertype(tolua_S,"TL_CONFIG");
 tolua_usertype(tolua_S,"GM_GROUP_DATA");
 tolua_usertype(tolua_S,"GM_SVR");
}

/* get function: szGroupName of class  GM_GROUP_DATA */
#ifndef TOLUA_DISABLE_tolua_get_GM_GROUP_DATA_szGroupName
static int tolua_get_GM_GROUP_DATA_szGroupName(lua_State* tolua_S)
{
  GM_GROUP_DATA* self = (GM_GROUP_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szGroupName'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szGroupName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szGroupName of class  GM_GROUP_DATA */
#ifndef TOLUA_DISABLE_tolua_set_GM_GROUP_DATA_szGroupName
static int tolua_set_GM_GROUP_DATA_szGroupName(lua_State* tolua_S)
{
  GM_GROUP_DATA* self = (GM_GROUP_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szGroupName'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szGroupName,(const char*)tolua_tostring(tolua_S,2,0),33-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSvrID of class  GM_SVR */
#ifndef TOLUA_DISABLE_tolua_get_GM_SVR_nSvrID
static int tolua_get_GM_SVR_nSvrID(lua_State* tolua_S)
{
  GM_SVR* self = (GM_SVR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSvrID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSvrID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSvrID of class  GM_SVR */
#ifndef TOLUA_DISABLE_tolua_set_GM_SVR_nSvrID
static int tolua_set_GM_SVR_nSvrID(lua_State* tolua_S)
{
  GM_SVR* self = (GM_SVR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSvrID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSvrID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szName of class  GM_SVR */
#ifndef TOLUA_DISABLE_tolua_get_GM_SVR_szName
static int tolua_get_GM_SVR_szName(lua_State* tolua_S)
{
  GM_SVR* self = (GM_SVR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szName of class  GM_SVR */
#ifndef TOLUA_DISABLE_tolua_set_GM_SVR_szName
static int tolua_set_GM_SVR_szName(lua_State* tolua_S)
{
  GM_SVR* self = (GM_SVR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szName,(const char*)tolua_tostring(tolua_S,2,0),128-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szAddr of class  GM_SVR */
#ifndef TOLUA_DISABLE_tolua_get_GM_SVR_szAddr
static int tolua_get_GM_SVR_szAddr(lua_State* tolua_S)
{
  GM_SVR* self = (GM_SVR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szAddr'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szAddr);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szAddr of class  GM_SVR */
#ifndef TOLUA_DISABLE_tolua_set_GM_SVR_szAddr
static int tolua_set_GM_SVR_szAddr(lua_State* tolua_S)
{
  GM_SVR* self = (GM_SVR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szAddr'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szAddr,(const char*)tolua_tostring(tolua_S,2,0),128-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwPort of class  GM_SVR */
#ifndef TOLUA_DISABLE_tolua_get_GM_SVR_unsigned_dwPort
static int tolua_get_GM_SVR_unsigned_dwPort(lua_State* tolua_S)
{
  GM_SVR* self = (GM_SVR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwPort'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwPort);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwPort of class  GM_SVR */
#ifndef TOLUA_DISABLE_tolua_set_GM_SVR_unsigned_dwPort
static int tolua_set_GM_SVR_unsigned_dwPort(lua_State* tolua_S)
{
  GM_SVR* self = (GM_SVR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwPort'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwPort = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: groupList of class  GM_SVR */
#ifndef TOLUA_DISABLE_tolua_get_tl_config_GM_SVR_groupList
static int tolua_get_tl_config_GM_SVR_groupList(lua_State* tolua_S)
{
 int tolua_index;
  GM_SVR* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GM_SVR*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=32)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->groupList[tolua_index],"GM_GROUP_DATA");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: groupList of class  GM_SVR */
#ifndef TOLUA_DISABLE_tolua_set_tl_config_GM_SVR_groupList
static int tolua_set_tl_config_GM_SVR_groupList(lua_State* tolua_S)
{
 int tolua_index;
  GM_SVR* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GM_SVR*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=32)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->groupList[tolua_index] = *((GM_GROUP_DATA*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSvrNum of class  GM_SVR_LIST */
#ifndef TOLUA_DISABLE_tolua_get_TL_CONFIG__GM_SVR_LIST_nSvrNum
static int tolua_get_TL_CONFIG__GM_SVR_LIST_nSvrNum(lua_State* tolua_S)
{
  TL_CONFIG::GM_SVR_LIST* self = (TL_CONFIG::GM_SVR_LIST*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSvrNum'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSvrNum);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSvrNum of class  GM_SVR_LIST */
#ifndef TOLUA_DISABLE_tolua_set_TL_CONFIG__GM_SVR_LIST_nSvrNum
static int tolua_set_TL_CONFIG__GM_SVR_LIST_nSvrNum(lua_State* tolua_S)
{
  TL_CONFIG::GM_SVR_LIST* self = (TL_CONFIG::GM_SVR_LIST*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSvrNum'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSvrNum = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: arrGMList of class  GM_SVR_LIST */
#ifndef TOLUA_DISABLE_tolua_get_tl_config_TL_CONFIG_GM_SVR_LIST_arrGMList
static int tolua_get_tl_config_TL_CONFIG_GM_SVR_LIST_arrGMList(lua_State* tolua_S)
{
 int tolua_index;
  TL_CONFIG::GM_SVR_LIST* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (TL_CONFIG::GM_SVR_LIST*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=GM_MAX_SERVER_COUNT)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->arrGMList[tolua_index],"GM_SVR");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: arrGMList of class  GM_SVR_LIST */
#ifndef TOLUA_DISABLE_tolua_set_tl_config_TL_CONFIG_GM_SVR_LIST_arrGMList
static int tolua_set_tl_config_TL_CONFIG_GM_SVR_LIST_arrGMList(lua_State* tolua_S)
{
 int tolua_index;
  TL_CONFIG::GM_SVR_LIST* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (TL_CONFIG::GM_SVR_LIST*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=GM_MAX_SERVER_COUNT)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->arrGMList[tolua_index] = *((GM_SVR*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ServerList of class  TL_CONFIG */
#ifndef TOLUA_DISABLE_tolua_get_TL_CONFIG_ServerList
static int tolua_get_TL_CONFIG_ServerList(lua_State* tolua_S)
{
  TL_CONFIG* self = (TL_CONFIG*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ServerList'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->ServerList,"TL_CONFIG::GM_SVR_LIST");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ServerList of class  TL_CONFIG */
#ifndef TOLUA_DISABLE_tolua_set_TL_CONFIG_ServerList
static int tolua_set_TL_CONFIG_ServerList(lua_State* tolua_S)
{
  TL_CONFIG* self = (TL_CONFIG*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ServerList'",NULL);
 if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"TL_CONFIG::GM_SVR_LIST",0,&tolua_err)))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ServerList = *((TL_CONFIG::GM_SVR_LIST*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetTLConfig */
#ifndef TOLUA_DISABLE_tolua_tl_config_GetTLConfig00
static int tolua_tl_config_GetTLConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  TL_CONFIG& tolua_ret = (TL_CONFIG&)  GetTLConfig();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"TL_CONFIG");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTLConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_tl_config_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"lotNone",lotNone);
  tolua_constant(tolua_S,"lotConsole",lotConsole);
  tolua_constant(tolua_S,"lotFile",lotFile);
  tolua_constant(tolua_S,"lotTrace",lotTrace);
  tolua_constant(tolua_S,"lotCustom",lotCustom);
  tolua_constant(tolua_S,"lotAll",lotAll);
  tolua_constant(tolua_S,"lltNone",lltNone);
  tolua_constant(tolua_S,"lltDebug",lltDebug);
  tolua_constant(tolua_S,"lltInfo",lltInfo);
  tolua_constant(tolua_S,"lltWarning",lltWarning);
  tolua_constant(tolua_S,"lltError",lltError);
  tolua_constant(tolua_S,"lltCritical",lltCritical);
  tolua_constant(tolua_S,"lltSDU",lltSDU);
  tolua_constant(tolua_S,"lltMove",lltMove);
  tolua_constant(tolua_S,"lltLua",lltLua);
  tolua_constant(tolua_S,"lltSpell",lltSpell);
  tolua_constant(tolua_S,"lltSys",lltSys);
  tolua_constant(tolua_S,"lltAll",lltAll);
 tolua_constant(tolua_S,"PING_SVR_INTERNAL",PING_SVR_INTERNAL);
 tolua_constant(tolua_S,"PING_SVR_TIMEOUT",PING_SVR_TIMEOUT);
 tolua_constant(tolua_S,"RECONNECT_TIME",RECONNECT_TIME);
 tolua_constant(tolua_S,"SMALL_PACKET_COUNT",SMALL_PACKET_COUNT);
 tolua_constant(tolua_S,"LARGE_PACKET_COUNT",LARGE_PACKET_COUNT);
 tolua_constant(tolua_S,"MAX_ACCEPTOR",MAX_ACCEPTOR);
 tolua_constant(tolua_S,"MAX_CONNECTOR",MAX_CONNECTOR);
 tolua_constant(tolua_S,"MAX_SESSION_COUNT",MAX_SESSION_COUNT);
 tolua_constant(tolua_S,"SEND_BUF_SIZE",SEND_BUF_SIZE);
 tolua_constant(tolua_S,"RECV_BUF_SIZE",RECV_BUF_SIZE);
 tolua_constant(tolua_S,"PACKET_BUFFER_SIZE",PACKET_BUFFER_SIZE);
 tolua_constant(tolua_S,"RELOGIN_INTERNAL",RELOGIN_INTERNAL);
 tolua_constant(tolua_S,"CMD_DATA_POOL_COUNT",CMD_DATA_POOL_COUNT);
 tolua_constant(tolua_S,"GM_MAX_SERVER_COUNT",GM_MAX_SERVER_COUNT);
 #ifdef __cplusplus
 tolua_cclass(tolua_S,"GM_GROUP_DATA","GM_GROUP_DATA","",tolua_collect_GM_GROUP_DATA);
 #else
 tolua_cclass(tolua_S,"GM_GROUP_DATA","GM_GROUP_DATA","",NULL);
 #endif
 tolua_beginmodule(tolua_S,"GM_GROUP_DATA");
  tolua_variable(tolua_S,"szGroupName",tolua_get_GM_GROUP_DATA_szGroupName,tolua_set_GM_GROUP_DATA_szGroupName);
 tolua_endmodule(tolua_S);
 #ifdef __cplusplus
 tolua_cclass(tolua_S,"GM_SVR","GM_SVR","",tolua_collect_GM_SVR);
 #else
 tolua_cclass(tolua_S,"GM_SVR","GM_SVR","",NULL);
 #endif
 tolua_beginmodule(tolua_S,"GM_SVR");
  tolua_variable(tolua_S,"nSvrID",tolua_get_GM_SVR_nSvrID,tolua_set_GM_SVR_nSvrID);
  tolua_variable(tolua_S,"szName",tolua_get_GM_SVR_szName,tolua_set_GM_SVR_szName);
  tolua_variable(tolua_S,"szAddr",tolua_get_GM_SVR_szAddr,tolua_set_GM_SVR_szAddr);
  tolua_variable(tolua_S,"dwPort",tolua_get_GM_SVR_unsigned_dwPort,tolua_set_GM_SVR_unsigned_dwPort);
  tolua_array(tolua_S,"groupList",tolua_get_tl_config_GM_SVR_groupList,tolua_set_tl_config_GM_SVR_groupList);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"TL_CONFIG","TL_CONFIG","",NULL);
 tolua_beginmodule(tolua_S,"TL_CONFIG");
  tolua_cclass(tolua_S,"GM_SVR_LIST","TL_CONFIG::GM_SVR_LIST","",NULL);
  tolua_beginmodule(tolua_S,"GM_SVR_LIST");
   tolua_variable(tolua_S,"nSvrNum",tolua_get_TL_CONFIG__GM_SVR_LIST_nSvrNum,tolua_set_TL_CONFIG__GM_SVR_LIST_nSvrNum);
   tolua_array(tolua_S,"arrGMList",tolua_get_tl_config_TL_CONFIG_GM_SVR_LIST_arrGMList,tolua_set_tl_config_TL_CONFIG_GM_SVR_LIST_arrGMList);
  tolua_endmodule(tolua_S);
  tolua_variable(tolua_S,"ServerList",tolua_get_TL_CONFIG_ServerList,tolua_set_TL_CONFIG_ServerList);
 tolua_endmodule(tolua_S);
#ifndef TOLUA_DISABLE_tolua_tl_config_GetTLConfig00
 tolua_function(tolua_S,"GetTLConfig",tolua_tl_config_GetTLConfig00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_tl_config (lua_State* tolua_S) {
 return tolua_tl_config_open(tolua_S);
};
#endif

