/*
** Lua binding: spirit_def
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_spirit_def_open (lua_State* tolua_S);

#include "../../../Common/define/spirit_def.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_INT32 (lua_State* tolua_S)
{
 INT32* self = (INT32*) tolua_tousertype(tolua_S,1,0);
 Mtolua_delete(self);
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"INT32");
}

/* function: MAKE_AIR_LEVEL_KEY */
#ifndef TOLUA_DISABLE_tolua_spirit_def_MAKE_AIR_LEVEL_KEY00
static int tolua_spirit_def_MAKE_AIR_LEVEL_KEY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"INT32",0,&tolua_err)) ||
 (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"INT32",0,&tolua_err)) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  INT32 nLevel = *((INT32*)  tolua_tousertype(tolua_S,1,0));
  INT32 nClass = *((INT32*)  tolua_tousertype(tolua_S,2,0));
 {
  INT32 tolua_ret = (INT32)  MAKE_AIR_LEVEL_KEY(nLevel,nClass);
 {
#ifdef __cplusplus
 void* tolua_obj = Mtolua_new((INT32)(tolua_ret));
  tolua_pushusertype(tolua_S,tolua_obj,"INT32");
 tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(INT32));
  tolua_pushusertype(tolua_S,tolua_obj,"INT32");
 tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MAKE_AIR_LEVEL_KEY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MAKE_BLOOD_KEY */
#ifndef TOLUA_DISABLE_tolua_spirit_def_MAKE_BLOOD_KEY00
static int tolua_spirit_def_MAKE_BLOOD_KEY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"INT32",0,&tolua_err)) ||
 (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"INT32",0,&tolua_err)) ||
 (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"INT32",0,&tolua_err)) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  INT32 nPage = *((INT32*)  tolua_tousertype(tolua_S,1,0));
  INT32 nIndex = *((INT32*)  tolua_tousertype(tolua_S,2,0));
  INT32 nNumber = *((INT32*)  tolua_tousertype(tolua_S,3,0));
 {
  INT32 tolua_ret = (INT32)  MAKE_BLOOD_KEY(nPage,nIndex,nNumber);
 {
#ifdef __cplusplus
 void* tolua_obj = Mtolua_new((INT32)(tolua_ret));
  tolua_pushusertype(tolua_S,tolua_obj,"INT32");
 tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(INT32));
  tolua_pushusertype(tolua_S,tolua_obj,"INT32");
 tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MAKE_BLOOD_KEY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_spirit_def_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"SPIRIT_OPEN_LEVEL",SPIRIT_OPEN_LEVEL);
 tolua_constant(tolua_S,"MAX_EXT2PTS_MULTIPLE",MAX_EXT2PTS_MULTIPLE);
 tolua_constant(tolua_S,"MAX_EXP2PTS_THRESHOLD",MAX_EXP2PTS_THRESHOLD);
 tolua_constant(tolua_S,"MAX_SPIRIT_LEVEL",MAX_SPIRIT_LEVEL);
 tolua_constant(tolua_S,"MAX_SPIRIT_NODE_PER_LEVEL",MAX_SPIRIT_NODE_PER_LEVEL);
 tolua_constant(tolua_S,"MAX_AIRSEA_BAG_CONTAINER_SIZE",MAX_AIRSEA_BAG_CONTAINER_SIZE);
 tolua_constant(tolua_S,"MAX_AIRSEA_STALL_CONTAINER_SIZE",MAX_AIRSEA_STALL_CONTAINER_SIZE);
 tolua_constant(tolua_S,"MAX_AIRSEA_EQUIP_CONTAINER_SIZE",MAX_AIRSEA_EQUIP_CONTAINER_SIZE);
 tolua_constant(tolua_S,"MAX_AIR_PROCEDURE",MAX_AIR_PROCEDURE);
 tolua_constant(tolua_S,"MAX_DROP_AIR_COUNT",MAX_DROP_AIR_COUNT);
 tolua_constant(tolua_S,"MAX_AIR_LEVEL",MAX_AIR_LEVEL);
 tolua_constant(tolua_S,"MAX_AIR_NODE",MAX_AIR_NODE);
 tolua_constant(tolua_S,"MAX_ATTR_PER_NODE",MAX_ATTR_PER_NODE);
 tolua_constant(tolua_S,"MAX_SPIRIT_BUY_SLOT_COST",MAX_SPIRIT_BUY_SLOT_COST);
 tolua_constant(tolua_S,"INVALID_AIR_ID",INVALID_AIR_ID);
 tolua_constant(tolua_S,"INVALID_AIR_INDEX",INVALID_AIR_INDEX);
 tolua_constant(tolua_S,"MAX_EXP2PTS_LEVEL",MAX_EXP2PTS_LEVEL);
 tolua_constant(tolua_S,"MAX_BLOODSEA_PAGE",MAX_BLOODSEA_PAGE);
 tolua_constant(tolua_S,"MAX_BLOODSEA_SLOT_PER_PAGE",MAX_BLOODSEA_SLOT_PER_PAGE);
 tolua_constant(tolua_S,"MAX_BLOODSEA_SLOT_NUMBER",MAX_BLOODSEA_SLOT_NUMBER);
 tolua_constant(tolua_S,"MAX_BLOODSEA_ATTR_PER_SLOT",MAX_BLOODSEA_ATTR_PER_SLOT);
 tolua_constant(tolua_S,"BLOODSEA_SLOT_INIT_SLOT",BLOODSEA_SLOT_INIT_SLOT);
  tolua_constant(tolua_S,"sasbtInvalid",sasbtInvalid);
  tolua_constant(tolua_S,"sasbtBag",sasbtBag);
  tolua_constant(tolua_S,"sasbtStall",sasbtStall);
  tolua_constant(tolua_S,"sasbtEquip",sasbtEquip);
  tolua_constant(tolua_S,"sasbtTotal",sasbtTotal);
  tolua_constant(tolua_S,"spiritInvalid",spiritInvalid);
  tolua_constant(tolua_S,"spiritPower",spiritPower);
  tolua_constant(tolua_S,"spiritSwift",spiritSwift);
  tolua_constant(tolua_S,"spiritWise",spiritWise);
  tolua_constant(tolua_S,"spiritBody",spiritBody);
  tolua_constant(tolua_S,"spiritDivine",spiritDivine);
  tolua_constant(tolua_S,"spiritKing",spiritKing);
#ifndef TOLUA_DISABLE_tolua_spirit_def_MAKE_AIR_LEVEL_KEY00
 tolua_function(tolua_S,"MAKE_AIR_LEVEL_KEY",tolua_spirit_def_MAKE_AIR_LEVEL_KEY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spirit_def_MAKE_BLOOD_KEY00
 tolua_function(tolua_S,"MAKE_BLOOD_KEY",tolua_spirit_def_MAKE_BLOOD_KEY00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_spirit_def (lua_State* tolua_S) {
 return tolua_spirit_def_open(tolua_S);
};
#endif

