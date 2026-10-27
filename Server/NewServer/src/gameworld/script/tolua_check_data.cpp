/*
** Lua binding: check_data
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_check_data_open (lua_State* tolua_S);

#include "../../inc/baselib/checkdata.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCheckData (lua_State* tolua_S)
{
 CCheckData* self = (CCheckData*) tolua_tousertype(tolua_S,1,0);
 Mtolua_delete(self);
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CTabFile");
 tolua_usertype(tolua_S,"CCheckData");
}

/* method: new of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_new00
static int tolua_check_data_CCheckData_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CCheckData* tolua_ret = (CCheckData*)  Mtolua_new((CCheckData)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCheckData");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_new00_local
static int tolua_check_data_CCheckData_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CCheckData* tolua_ret = (CCheckData*)  Mtolua_new((CCheckData)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCheckData");
 tolua_register_gc(tolua_S,lua_gettop(tolua_S));
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_delete00
static int tolua_check_data_CCheckData_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCheckData* self = (CCheckData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
 Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Check of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_Check00
static int tolua_check_data_CCheckData_Check00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCheckData* self = (CCheckData*)  tolua_tousertype(tolua_S,1,0);
  const char* pPath = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* pFoledrName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Check'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Check(pPath,pFoledrName);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Check'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDataByName of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetDataByName00
static int tolua_check_data_CCheckData_GetDataByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCheckData* self = (CCheckData*)  tolua_tousertype(tolua_S,1,0);
  const char* pName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDataByName'", NULL);
#endif
 {
  CTabFile* tolua_ret = (CTabFile*)  self->GetDataByName(pName);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTabFile");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDataByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTabRowCount of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetTabRowCount00
static int tolua_check_data_CCheckData_GetTabRowCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CTabFile",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCheckData* self = (CCheckData*)  tolua_tousertype(tolua_S,1,0);
  CTabFile* pTab = ((CTabFile*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTabRowCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetTabRowCount(pTab);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTabRowCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTabColCount of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetTabColCount00
static int tolua_check_data_CCheckData_GetTabColCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CTabFile",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCheckData* self = (CCheckData*)  tolua_tousertype(tolua_S,1,0);
  CTabFile* pTab = ((CTabFile*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTabColCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetTabColCount(pTab);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTabColCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumber of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetNumber00
static int tolua_check_data_CCheckData_GetNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CTabFile",0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCheckData* self = (CCheckData*)  tolua_tousertype(tolua_S,1,0);
  CTabFile* pTab = ((CTabFile*)  tolua_tousertype(tolua_S,2,0));
  char* pCol = ((char*)  tolua_tostring(tolua_S,3,0));
  signed int nRow = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumber'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetNumber(pTab,pCol,nRow);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetString of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetString00
static int tolua_check_data_CCheckData_GetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CTabFile",0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCheckData* self = (CCheckData*)  tolua_tousertype(tolua_S,1,0);
  CTabFile* pTab = ((CTabFile*)  tolua_tousertype(tolua_S,2,0));
  char* pCol = ((char*)  tolua_tostring(tolua_S,3,0));
  signed int nRow = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetString'", NULL);
#endif
 {
  char* tolua_ret = (char*)  self->GetString(pTab,pCol,nRow);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetColName of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetColName00
static int tolua_check_data_CCheckData_GetColName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CTabFile",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCheckData* self = (CCheckData*)  tolua_tousertype(tolua_S,1,0);
  CTabFile* pTab = ((CTabFile*)  tolua_tousertype(tolua_S,2,0));
  signed int nColID = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetColName'", NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->GetColName(pTab,nColID);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetColName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PrintInfo of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_PrintInfo00
static int tolua_check_data_CCheckData_PrintInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCheckData* self = (CCheckData*)  tolua_tousertype(tolua_S,1,0);
  char* pInfo = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PrintInfo'", NULL);
#endif
 {
  self->PrintInfo(pInfo);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrintInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PrintWrn of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_PrintWrn00
static int tolua_check_data_CCheckData_PrintWrn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CCheckData* self = (CCheckData*)  tolua_tousertype(tolua_S,1,0);
  char* pWrn = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PrintWrn'", NULL);
#endif
 {
  self->PrintWrn(pWrn);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrintWrn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstance of class  CCheckData */
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetInstance00
static int tolua_check_data_CCheckData_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CCheckData",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CCheckData& tolua_ret = (CCheckData&)  CCheckData::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CCheckData");
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

/* Open function */
TOLUA_API int tolua_check_data_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 #ifdef __cplusplus
 tolua_cclass(tolua_S,"CCheckData","CCheckData","",tolua_collect_CCheckData);
 #else
 tolua_cclass(tolua_S,"CCheckData","CCheckData","",NULL);
 #endif
 tolua_beginmodule(tolua_S,"CCheckData");
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_new00
  tolua_function(tolua_S,"new",tolua_check_data_CCheckData_new00);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_check_data_CCheckData_new00_local);
  tolua_function(tolua_S,".call",tolua_check_data_CCheckData_new00_local);
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_delete00
  tolua_function(tolua_S,"delete",tolua_check_data_CCheckData_delete00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_Check00
  tolua_function(tolua_S,"Check",tolua_check_data_CCheckData_Check00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetDataByName00
  tolua_function(tolua_S,"GetDataByName",tolua_check_data_CCheckData_GetDataByName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetTabRowCount00
  tolua_function(tolua_S,"GetTabRowCount",tolua_check_data_CCheckData_GetTabRowCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetTabColCount00
  tolua_function(tolua_S,"GetTabColCount",tolua_check_data_CCheckData_GetTabColCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetNumber00
  tolua_function(tolua_S,"GetNumber",tolua_check_data_CCheckData_GetNumber00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetString00
  tolua_function(tolua_S,"GetString",tolua_check_data_CCheckData_GetString00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetColName00
  tolua_function(tolua_S,"GetColName",tolua_check_data_CCheckData_GetColName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_PrintInfo00
  tolua_function(tolua_S,"PrintInfo",tolua_check_data_CCheckData_PrintInfo00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_PrintWrn00
  tolua_function(tolua_S,"PrintWrn",tolua_check_data_CCheckData_PrintWrn00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_check_data_CCheckData_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_check_data_CCheckData_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_check_data (lua_State* tolua_S) {
 return tolua_check_data_open(tolua_S);
};
#endif

