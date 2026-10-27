/*
** Lua binding: drop_generator
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_drop_generator_open (lua_State* tolua_S);

#include "drop_generator.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CDropGenerator");
 tolua_usertype(tolua_S,"CScene");
}

/* method: GetInstance of class  CDropGenerator */
#ifndef TOLUA_DISABLE_tolua_drop_generator_CDropGenerator_GetInstance00
static int tolua_drop_generator_CDropGenerator_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CDropGenerator",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CDropGenerator& tolua_ret = (CDropGenerator&)  CDropGenerator::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CDropGenerator");
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

/* method: GenerateDrop of class  CDropGenerator */
#ifndef TOLUA_DISABLE_tolua_drop_generator_CDropGenerator_GenerateDrop00
static int tolua_drop_generator_CDropGenerator_GenerateDrop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CDropGenerator",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,5,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,10,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CDropGenerator* self = (CDropGenerator*)  tolua_tousertype(tolua_S,1,0);
  signed int nServerGroup = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int itemid = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int itemcount = (( signed int)  tolua_tonumber(tolua_S,4,0));
  CScene* scene = ((CScene*)  tolua_tousertype(tolua_S,5,0));
  signed int llX = (( signed int)  tolua_tonumber(tolua_S,6,0));
  signed int llY = (( signed int)  tolua_tonumber(tolua_S,7,0));
  signed int llZ = (( signed int)  tolua_tonumber(tolua_S,8,0));
  unsigned int srcid = (( unsigned int)  tolua_tonumber(tolua_S,9,0));
   bool instantpick = ((  bool)  tolua_toboolean(tolua_S,10,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GenerateDrop'", NULL);
#endif
 {
 int tolua_ret = (int)
self->GenerateDrop(nServerGroup,itemid,itemcount,scene,llX,llY,llZ,srcid,instantpick);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GenerateDrop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_drop_generator_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CDropGenerator","CDropGenerator","",NULL);
 tolua_beginmodule(tolua_S,"CDropGenerator");
#ifndef TOLUA_DISABLE_tolua_drop_generator_CDropGenerator_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_drop_generator_CDropGenerator_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_drop_generator_CDropGenerator_GenerateDrop00
  tolua_function(tolua_S,"GenerateDrop",tolua_drop_generator_CDropGenerator_GenerateDrop00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_drop_generator (lua_State* tolua_S) {
 return tolua_drop_generator_open(tolua_S);
};
#endif

