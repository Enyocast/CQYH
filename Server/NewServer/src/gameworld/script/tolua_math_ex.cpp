/*
** Lua binding: math_ex
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:30.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_math_ex_open (lua_State* tolua_S);

#include "math_ex.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_math_ex_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_DIRECTION_COUNT",MAX_DIRECTION_COUNT);
 tolua_constant(tolua_S,"SIN_COS_NUMBER",SIN_COS_NUMBER);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_math_ex (lua_State* tolua_S) {
 return tolua_math_ex_open(tolua_S);
};
#endif

