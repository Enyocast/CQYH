/*
** Lua binding: spell_book
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:31.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_spell_book_open (lua_State* tolua_S);

#include "spell.h"
#include "spell_book.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"ISpellBook");
 tolua_usertype(tolua_S,"CSpellSet");
}

/* method: BeginSpellSet of class  ISpellBook */
#ifndef TOLUA_DISABLE_tolua_spell_book_ISpellBook_BeginSpellSet00
static int tolua_spell_book_ISpellBook_BeginSpellSet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ISpellBook",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ISpellBook* self = (ISpellBook*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BeginSpellSet'", NULL);
#endif
 {
  self->BeginSpellSet();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BeginSpellSet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NextSpellSet of class  ISpellBook */
#ifndef TOLUA_DISABLE_tolua_spell_book_ISpellBook_NextSpellSet00
static int tolua_spell_book_ISpellBook_NextSpellSet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ISpellBook",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ISpellBook* self = (ISpellBook*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NextSpellSet'", NULL);
#endif
 {
  CSpellSet* tolua_ret = (CSpellSet*)  self->NextSpellSet();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpellSet");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NextSpellSet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpellSet of class  ISpellBook */
#ifndef TOLUA_DISABLE_tolua_spell_book_ISpellBook_GetSpellSet00
static int tolua_spell_book_ISpellBook_GetSpellSet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ISpellBook",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ISpellBook* self = (ISpellBook*)  tolua_tousertype(tolua_S,1,0);
  signed int nSpellID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpellSet'", NULL);
#endif
 {
  CSpellSet* tolua_ret = (CSpellSet*)  self->GetSpellSet(nSpellID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpellSet");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpellSet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_spell_book_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"ISpellBook","ISpellBook","",NULL);
 tolua_beginmodule(tolua_S,"ISpellBook");
#ifndef TOLUA_DISABLE_tolua_spell_book_ISpellBook_BeginSpellSet00
  tolua_function(tolua_S,"BeginSpellSet",tolua_spell_book_ISpellBook_BeginSpellSet00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_book_ISpellBook_NextSpellSet00
  tolua_function(tolua_S,"NextSpellSet",tolua_spell_book_ISpellBook_NextSpellSet00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_book_ISpellBook_GetSpellSet00
  tolua_function(tolua_S,"GetSpellSet",tolua_spell_book_ISpellBook_GetSpellSet00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_spell_book (lua_State* tolua_S) {
 return tolua_spell_book_open(tolua_S);
};
#endif

