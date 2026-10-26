/*
** Lua binding: friend
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:29.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_friend_open (lua_State* tolua_S);

#include "friend.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CRole");
 tolua_usertype(tolua_S,"CFriend");
}

/* method: AddFriend of class  CFriend */
#ifndef TOLUA_DISABLE_tolua_friend_CFriend_AddFriend00
static int tolua_friend_CFriend_AddFriend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CFriend",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CFriend* self = (CFriend*)  tolua_tousertype(tolua_S,1,0);
  unsigned char byGroupID = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwFriendID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddFriend'", NULL);
#endif
 {
  self->AddFriend(byGroupID,dwFriendID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddFriend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelFriend of class  CFriend */
#ifndef TOLUA_DISABLE_tolua_friend_CFriend_DelFriend00
static int tolua_friend_CFriend_DelFriend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CFriend",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CFriend* self = (CFriend*)  tolua_tousertype(tolua_S,1,0);
  unsigned char byGroupID = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwFriendID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelFriend'", NULL);
#endif
 {
  self->DelFriend(byGroupID,dwFriendID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelFriend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFriendCount of class  CFriend */
#ifndef TOLUA_DISABLE_tolua_friend_CFriend_GetFriendCount00
static int tolua_friend_CFriend_GetFriendCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CFriend",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CFriend* self = (CFriend*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFriendCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetFriendCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFriendCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPersonalEnemyCount of class  CFriend */
#ifndef TOLUA_DISABLE_tolua_friend_CFriend_GetPersonalEnemyCount00
static int tolua_friend_CFriend_GetPersonalEnemyCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CFriend",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CFriend* self = (CFriend*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPersonalEnemyCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetPersonalEnemyCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPersonalEnemyCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddBeKilledToList of class  CFriend */
#ifndef TOLUA_DISABLE_tolua_friend_CFriend_AddBeKilledToList00
static int tolua_friend_CFriend_AddBeKilledToList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CFriend",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CFriend* self = (CFriend*)  tolua_tousertype(tolua_S,1,0);
  CRole* poRole = ((CRole*)  tolua_tousertype(tolua_S,2,0));
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddBeKilledToList'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddBeKilledToList(poRole,dwRoleID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddBeKilledToList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_friend_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"CFriend","CFriend","",NULL);
 tolua_beginmodule(tolua_S,"CFriend");
#ifndef TOLUA_DISABLE_tolua_friend_CFriend_AddFriend00
  tolua_function(tolua_S,"AddFriend",tolua_friend_CFriend_AddFriend00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_friend_CFriend_DelFriend00
  tolua_function(tolua_S,"DelFriend",tolua_friend_CFriend_DelFriend00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_friend_CFriend_GetFriendCount00
  tolua_function(tolua_S,"GetFriendCount",tolua_friend_CFriend_GetFriendCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_friend_CFriend_GetPersonalEnemyCount00
  tolua_function(tolua_S,"GetPersonalEnemyCount",tolua_friend_CFriend_GetPersonalEnemyCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_friend_CFriend_AddBeKilledToList00
  tolua_function(tolua_S,"AddBeKilledToList",tolua_friend_CFriend_AddBeKilledToList00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_friend (lua_State* tolua_S) {
 return tolua_friend_open(tolua_S);
};
#endif

