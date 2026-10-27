/*
** Lua binding: spell
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_spell_open (lua_State* tolua_S);

#include "spell.h"
#include "spell_set.h"
#include "aura.h"
#include "spell_slot.h"
#include "spell_config.h"
#include "spell_book.h"
#include "spell_instance.h"
#include "aura_instance.h"
#include "target_scanner.h"
#include "../../../Common/define/spell_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CAuraInstance");
 tolua_usertype(tolua_S,"CSpellSet");
 tolua_usertype(tolua_S,"CAuraList");
 tolua_usertype(tolua_S,"CSpellInstance");
 tolua_usertype(tolua_S,"CSpellSlot");
 tolua_usertype(tolua_S,"CAura");
 tolua_usertype(tolua_S,"CSpellConfig");
 tolua_usertype(tolua_S,"CSpell");
 tolua_usertype(tolua_S,"ISpellBook");
 tolua_usertype(tolua_S,"CTargetScanner");
 tolua_usertype(tolua_S,"CSpellTemplate");
 tolua_usertype(tolua_S,"CAuraTemplate");
 tolua_usertype(tolua_S,"SPELL_ENTRY");
 tolua_usertype(tolua_S,"AURA_ENTRY");
}

/* function: MakeSpellKey */
#ifndef TOLUA_DISABLE_tolua_spell_MakeSpellKey00
static int tolua_spell_MakeSpellKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int nID = (( signed int)  tolua_tonumber(tolua_S,1,0));
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nRuneID = (( signed int)  tolua_tonumber(tolua_S,3,0));
 {
  signed int tolua_ret = ( signed int)  MakeSpellKey(nID,nLevel,nRuneID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeSpellKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MakeSpellProgressKey */
#ifndef TOLUA_DISABLE_tolua_spell_MakeSpellProgressKey00
static int tolua_spell_MakeSpellProgressKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int nID = (( signed int)  tolua_tonumber(tolua_S,1,0));
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,2,0));
 {
  signed int tolua_ret = ( signed int)  MakeSpellProgressKey(nID,nLevel);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeSpellProgressKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MakeAuraKey */
#ifndef TOLUA_DISABLE_tolua_spell_MakeAuraKey00
static int tolua_spell_MakeAuraKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int nID = (( signed int)  tolua_tonumber(tolua_S,1,0));
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,2,0));
 {
  signed int tolua_ret = ( signed int)  MakeAuraKey(nID,nLevel);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeAuraKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MakeAuraInstanceKey */
#ifndef TOLUA_DISABLE_tolua_spell_MakeAuraInstanceKey00
static int tolua_spell_MakeAuraInstanceKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int nType = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int dwGenerator = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 {
  unsigned int tolua_ret = ( unsigned int)  MakeAuraInstanceKey(nType,dwGenerator);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeAuraInstanceKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetAuraTypeFromInstanceID */
#ifndef TOLUA_DISABLE_tolua_spell_GetAuraTypeFromInstanceID00
static int tolua_spell_GetAuraTypeFromInstanceID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int dwAuraInstanceID = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  signed int tolua_ret = ( signed int)  GetAuraTypeFromInstanceID(dwAuraInstanceID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAuraTypeFromInstanceID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MakeCoolDownID */
#ifndef TOLUA_DISABLE_tolua_spell_MakeCoolDownID00
static int tolua_spell_MakeCoolDownID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,1,0));
  signed int nID = (( signed int)  tolua_tonumber(tolua_S,2,0));
 {
  signed int tolua_ret = ( signed int)  MakeCoolDownID(nType,nID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeCoolDownID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ParseCoolDownID */
#ifndef TOLUA_DISABLE_tolua_spell_ParseCoolDownID00
static int tolua_spell_ParseCoolDownID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int ID = (( signed int)  tolua_tonumber(tolua_S,1,0));
  signed int nType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nID = (( signed int)  tolua_tonumber(tolua_S,3,0));
 {
  ParseCoolDownID(ID,nType,nID);
 tolua_pushnumber(tolua_S,(lua_Number)nType);
 tolua_pushnumber(tolua_S,(lua_Number)nID);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ParseCoolDownID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetID of class  CSpell */
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_GetID00
static int tolua_spell_CSpell_GetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpell",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpell* self = (CSpell*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetID'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevel of class  CSpell */
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_GetLevel00
static int tolua_spell_CSpell_GetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpell",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpell* self = (CSpell*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetLevel();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRuneSlot of class  CSpell */
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_GetRuneSlot00
static int tolua_spell_CSpell_GetRuneSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpell",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpell* self = (CSpell*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRuneSlot'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetRuneSlot();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRuneSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAttr of class  CSpell */
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_GetAttr00
static int tolua_spell_CSpell_GetAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpell",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpell* self = (CSpell*)  tolua_tousertype(tolua_S,1,0);
  signed int eAttrType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAttr'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetAttr(eAttrType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanBindSlot of class  CSpell */
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_CanBindSlot00
static int tolua_spell_CSpell_CanBindSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpell",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpell* self = (CSpell*)  tolua_tousertype(tolua_S,1,0);
  signed int nSlotID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanBindSlot'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CanBindSlot(nSlotID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanBindSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanShowOnUI of class  CSpell */
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_CanShowOnUI00
static int tolua_spell_CSpell_CanShowOnUI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpell",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpell* self = (CSpell*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanShowOnUI'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CanShowOnUI();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanShowOnUI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanLearnByClass of class  CSpell */
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_CanLearnByClass00
static int tolua_spell_CSpell_CanLearnByClass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpell",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpell* self = (CSpell*)  tolua_tousertype(tolua_S,1,0);
  signed int nClass = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanLearnByClass'", NULL);
#endif
 {
 int tolua_ret = (int)
self->CanLearnByClass(nClass);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanLearnByClass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAttr of class  CSpellTemplate */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellTemplate_SetAttr00
static int tolua_spell_CSpellTemplate_SetAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellTemplate",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellTemplate* self = (CSpellTemplate*)  tolua_tousertype(tolua_S,1,0);
  signed int eAttrType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nVal = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAttr'", NULL);
#endif
 {
  self->SetAttr(eAttrType,nVal);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetID of class  CSpellSet */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSet_GetID00
static int tolua_spell_CSpellSet_GetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellSet",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellSet* self = (CSpellSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetID'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevel of class  CSpellSet */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSet_GetLevel00
static int tolua_spell_CSpellSet_GetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellSet",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellSet* self = (CSpellSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetLevel();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpell of class  CSpellSet */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSet_GetSpell00
static int tolua_spell_CSpellSet_GetSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellSet",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellSet* self = (CSpellSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpell'", NULL);
#endif
 {
  CSpell* tolua_ret = (CSpell*)  self->GetSpell();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpell");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetID of class  CSpellSet */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSet_GetID01
static int tolua_spell_CSpellSet_GetID01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellSet",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSpellSet* self = (CSpellSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetID'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_spell_CSpellSet_GetID00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevel of class  CSpellSet */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSet_GetLevel01
static int tolua_spell_CSpellSet_GetLevel01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellSet",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CSpellSet* self = (CSpellSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetLevel();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_spell_CSpellSet_GetLevel00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRuneSlot of class  CSpellSet */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSet_GetRuneSlot00
static int tolua_spell_CSpellSet_GetRuneSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellSet",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellSet* self = (CSpellSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRuneSlot'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetRuneSlot();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRuneSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFromObjID of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetFromObjID00
static int tolua_spell_CSpellInstance_GetFromObjID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFromObjID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetFromObjID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFromObjID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScanner of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetScanner00
static int tolua_spell_CSpellInstance_GetScanner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScanner'", NULL);
#endif
 {
  CTargetScanner& tolua_ret = (CTargetScanner&)  self->GetScanner();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CTargetScanner");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScanner'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInitX of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetInitX00
static int tolua_spell_CSpellInstance_GetInitX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInitX'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetInitX();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInitX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInitY of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetInitY00
static int tolua_spell_CSpellInstance_GetInitY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInitY'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetInitY();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInitY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInitZ of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetInitZ00
static int tolua_spell_CSpellInstance_GetInitZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInitZ'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetInitZ();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInitZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAtkSpeedFactor of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetAtkSpeedFactor00
static int tolua_spell_CSpellInstance_GetAtkSpeedFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAtkSpeedFactor'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetAtkSpeedFactor();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAtkSpeedFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWeaponSpeedFactor of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetWeaponSpeedFactor00
static int tolua_spell_CSpellInstance_GetWeaponSpeedFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWeaponSpeedFactor'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetWeaponSpeedFactor();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWeaponSpeedFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWeaponStiffFactor of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetWeaponStiffFactor00
static int tolua_spell_CSpellInstance_GetWeaponStiffFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWeaponStiffFactor'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetWeaponStiffFactor();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWeaponStiffFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCastSerial of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetCastSerial00
static int tolua_spell_CSpellInstance_GetCastSerial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCastSerial'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetCastSerial();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCastSerial'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEffectSerial of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetEffectSerial00
static int tolua_spell_CSpellInstance_GetEffectSerial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEffectSerial'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetEffectSerial();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEffectSerial'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPrepareTimeMinFrm of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetPrepareTimeMinFrm00
static int tolua_spell_CSpellInstance_GetPrepareTimeMinFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPrepareTimeMinFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetPrepareTimeMinFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPrepareTimeMinFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPrepareTimeMaxFrm of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetPrepareTimeMaxFrm00
static int tolua_spell_CSpellInstance_GetPrepareTimeMaxFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPrepareTimeMaxFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetPrepareTimeMaxFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPrepareTimeMaxFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIntervalFrm of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetIntervalFrm00
static int tolua_spell_CSpellInstance_GetIntervalFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIntervalFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetIntervalFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIntervalFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHardTimeFrm of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetHardTimeFrm00
static int tolua_spell_CSpellInstance_GetHardTimeFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHardTimeFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetHardTimeFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHardTimeFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResetTimeFrm of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetResetTimeFrm00
static int tolua_spell_CSpellInstance_GetResetTimeFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResetTimeFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetResetTimeFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResetTimeFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCacheTimeFrm of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetCacheTimeFrm00
static int tolua_spell_CSpellInstance_GetCacheTimeFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCacheTimeFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetCacheTimeFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCacheTimeFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAccumulateTimeMaxFrm of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetAccumulateTimeMaxFrm00
static int tolua_spell_CSpellInstance_GetAccumulateTimeMaxFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAccumulateTimeMaxFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetAccumulateTimeMaxFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAccumulateTimeMaxFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStiffFrm of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetStiffFrm00
static int tolua_spell_CSpellInstance_GetStiffFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStiffFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetStiffFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStiffFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetExCastFrm of class  CSpellInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetExCastFrm00
static int tolua_spell_CSpellInstance_GetExCastFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellInstance",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellInstance* self = (CSpellInstance*)  tolua_tousertype(tolua_S,1,0);
  signed int idx = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetExCastFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetExCastFrm(idx);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetExCastFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Lock of class  CSpellSlot */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSlot_Lock00
static int tolua_spell_CSpellSlot_Lock00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellSlot",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellSlot* self = (CSpellSlot*)  tolua_tousertype(tolua_S,1,0);
   bool bLock = ((  bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Lock'", NULL);
#endif
 {
  self->Lock(bLock);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Lock'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsLocked of class  CSpellSlot */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSlot_IsLocked00
static int tolua_spell_CSpellSlot_IsLocked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellSlot",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellSlot* self = (CSpellSlot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsLocked'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsLocked();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsLocked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMainSpellID of class  CSpellSlot */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSlot_GetMainSpellID00
static int tolua_spell_CSpellSlot_GetMainSpellID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellSlot",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellSlot* self = (CSpellSlot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMainSpellID'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMainSpellID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMainSpellID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetID of class  CAura */
#ifndef TOLUA_DISABLE_tolua_spell_CAura_GetID00
static int tolua_spell_CAura_GetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAura",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAura* self = (CAura*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetID'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAttr of class  CAura */
#ifndef TOLUA_DISABLE_tolua_spell_CAura_GetAttr00
static int tolua_spell_CAura_GetAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAura",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAura* self = (CAura*)  tolua_tousertype(tolua_S,1,0);
  signed int eAttrType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAttr'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetAttr(eAttrType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDurationFrm of class  CAura */
#ifndef TOLUA_DISABLE_tolua_spell_CAura_GetDurationFrm00
static int tolua_spell_CAura_GetDurationFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAura",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAura* self = (CAura*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDurationFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetDurationFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDurationFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIntervalFrm of class  CAura */
#ifndef TOLUA_DISABLE_tolua_spell_CAura_GetIntervalFrm00
static int tolua_spell_CAura_GetIntervalFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAura",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAura* self = (CAura*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIntervalFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetIntervalFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIntervalFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDelayFrm of class  CAura */
#ifndef TOLUA_DISABLE_tolua_spell_CAura_GetDelayFrm00
static int tolua_spell_CAura_GetDelayFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAura",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAura* self = (CAura*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDelayFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetDelayFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDelayFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEffectMinFrm of class  CAura */
#ifndef TOLUA_DISABLE_tolua_spell_CAura_GetEffectMinFrm00
static int tolua_spell_CAura_GetEffectMinFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAura",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAura* self = (CAura*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEffectMinFrm'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetEffectMinFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEffectMinFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitAttr of class  CAuraTemplate */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraTemplate_InitAttr00
static int tolua_spell_CAuraTemplate_InitAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraTemplate",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraTemplate* self = (CAuraTemplate*)  tolua_tousertype(tolua_S,1,0);
  signed int eAttrType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nVal = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitAttr'", NULL);
#endif
 {
  self->InitAttr(eAttrType,nVal);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitWithData of class  CAuraTemplate */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraTemplate_InitWithData00
static int tolua_spell_CAuraTemplate_InitWithData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraTemplate",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"AURA_ENTRY",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraTemplate* self = (CAuraTemplate*)  tolua_tousertype(tolua_S,1,0);
  AURA_ENTRY* pData = ((AURA_ENTRY*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitWithData'", NULL);
#endif
 {
  self->InitWithData(pData);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitWithData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstanceID of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetInstanceID00
static int tolua_spell_CAuraInstance_GetInstanceID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraInstance* self = (CAuraInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInstanceID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetInstanceID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstanceID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStackCount of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetStackCount00
static int tolua_spell_CAuraInstance_GetStackCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraInstance* self = (CAuraInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStackCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetStackCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStackCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCasterID of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetCasterID00
static int tolua_spell_CAuraInstance_GetCasterID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraInstance* self = (CAuraInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCasterID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetCasterID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCasterID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFromObjID of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetFromObjID00
static int tolua_spell_CAuraInstance_GetFromObjID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraInstance* self = (CAuraInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFromObjID'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetFromObjID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFromObjID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStrengthLevel of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetStrengthLevel00
static int tolua_spell_CAuraInstance_GetStrengthLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraInstance* self = (CAuraInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStrengthLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetStrengthLevel();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStrengthLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTotalEffectValue of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetTotalEffectValue00
static int tolua_spell_CAuraInstance_GetTotalEffectValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraInstance* self = (CAuraInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTotalEffectValue'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetTotalEffectValue();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTotalEffectValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEffectPct of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetEffectPct00
static int tolua_spell_CAuraInstance_GetEffectPct00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraInstance* self = (CAuraInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEffectPct'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetEffectPct();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEffectPct'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEffectValue of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetEffectValue00
static int tolua_spell_CAuraInstance_GetEffectValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraInstance* self = (CAuraInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEffectValue'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetEffectValue();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEffectValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpellID of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetSpellID00
static int tolua_spell_CAuraInstance_GetSpellID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraInstance* self = (CAuraInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpellID'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetSpellID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpellID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpellLevel of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetSpellLevel00
static int tolua_spell_CAuraInstance_GetSpellLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraInstance* self = (CAuraInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpellLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetSpellLevel();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpellLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRemainFrm of class  CAuraInstance */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetRemainFrm00
static int tolua_spell_CAuraInstance_GetRemainFrm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraInstance* self = (CAuraInstance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRemainFrm'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetRemainFrm();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRemainFrm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BeginAura of class  CAuraList */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraList_BeginAura00
static int tolua_spell_CAuraList_BeginAura00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraList* self = (CAuraList*)  tolua_tousertype(tolua_S,1,0);
  signed int nEffectType = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BeginAura'", NULL);
#endif
 {
  CAuraInstance* tolua_ret = (CAuraInstance*)  self->BeginAura(nEffectType);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAuraInstance");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BeginAura'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NextAura of class  CAuraList */
#ifndef TOLUA_DISABLE_tolua_spell_CAuraList_NextAura00
static int tolua_spell_CAuraList_NextAura00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CAuraList",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"CAuraInstance",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CAuraList* self = (CAuraList*)  tolua_tousertype(tolua_S,1,0);
  signed int nEffectType = (( signed int)  tolua_tonumber(tolua_S,2,0));
  CAuraInstance* poPrevAura = ((CAuraInstance*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NextAura'", NULL);
#endif
 {
  CAuraInstance* tolua_ret = (CAuraInstance*)  self->NextAura(nEffectType,poPrevAura);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAuraInstance");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NextAura'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstance of class  CSpellConfig */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_GetInstance00
static int tolua_spell_CSpellConfig_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CSpellConfig",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CSpellConfig& tolua_ret = (CSpellConfig&)  CSpellConfig::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CSpellConfig");
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

/* method: FindAuraTemplate of class  CSpellConfig */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_FindAuraTemplate00
static int tolua_spell_CSpellConfig_FindAuraTemplate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellConfig",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellConfig* self = (CSpellConfig*)  tolua_tousertype(tolua_S,1,0);
  signed int nAuraID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindAuraTemplate'", NULL);
#endif
 {
  CAuraTemplate* tolua_ret = (CAuraTemplate*)  self->FindAuraTemplate(nAuraID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAuraTemplate");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindAuraTemplate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NewAuraTemplate of class  CSpellConfig */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_NewAuraTemplate00
static int tolua_spell_CSpellConfig_NewAuraTemplate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellConfig",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellConfig* self = (CSpellConfig*)  tolua_tousertype(tolua_S,1,0);
  signed int nAuraID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NewAuraTemplate'", NULL);
#endif
 {
  CAuraTemplate* tolua_ret = (CAuraTemplate*)  self->NewAuraTemplate(nAuraID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAuraTemplate");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NewAuraTemplate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHighestLevel of class  CSpellConfig */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_GetHighestLevel00
static int tolua_spell_CSpellConfig_GetHighestLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellConfig",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellConfig* self = (CSpellConfig*)  tolua_tousertype(tolua_S,1,0);
  signed int nSpellID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHighestLevel'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetHighestLevel(nSpellID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHighestLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindSpellTemplate of class  CSpellConfig */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_FindSpellTemplate00
static int tolua_spell_CSpellConfig_FindSpellTemplate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellConfig",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellConfig* self = (CSpellConfig*)  tolua_tousertype(tolua_S,1,0);
  signed int nSpellID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nSpellLevel = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nRuneID = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindSpellTemplate'", NULL);
#endif
 {
  CSpellTemplate* tolua_ret = (CSpellTemplate*)  self->FindSpellTemplate(nSpellID,nSpellLevel,nRuneID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpellTemplate");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindSpellTemplate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSpellTemplate of class  CSpellConfig */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_SetSpellTemplate00
static int tolua_spell_CSpellConfig_SetSpellTemplate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellConfig",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,5,"const SPELL_ENTRY",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellConfig* self = (CSpellConfig*)  tolua_tousertype(tolua_S,1,0);
  signed int nSpellID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nSpellLevel = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nRuneID = (( signed int)  tolua_tonumber(tolua_S,4,0));
  const SPELL_ENTRY* pData = ((const SPELL_ENTRY*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSpellTemplate'", NULL);
#endif
 {
  CSpellTemplate* tolua_ret = (CSpellTemplate*)  self->SetSpellTemplate(nSpellID,nSpellLevel,nRuneID,pData);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpellTemplate");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSpellTemplate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSpellMaxProgress of class  CSpellConfig */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_SetSpellMaxProgress00
static int tolua_spell_CSpellConfig_SetSpellMaxProgress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellConfig",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellConfig* self = (CSpellConfig*)  tolua_tousertype(tolua_S,1,0);
  signed int nSpellID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nSpellLevel = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nMaxProgress = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSpellMaxProgress'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetSpellMaxProgress(nSpellID,nSpellLevel,nMaxProgress);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSpellMaxProgress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxProgress of class  CSpellConfig */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_GetMaxProgress00
static int tolua_spell_CSpellConfig_GetMaxProgress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellConfig",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellConfig* self = (CSpellConfig*)  tolua_tousertype(tolua_S,1,0);
  signed int nSpellID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nSpellLevel = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nMaxProgress = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxProgress'", NULL);
#endif
 {
 int tolua_ret = (int)
self->GetMaxProgress(nSpellID,nSpellLevel,nMaxProgress);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 tolua_pushnumber(tolua_S,(lua_Number)nMaxProgress);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxProgress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BeginSpell of class  CSpellConfig */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_BeginSpell00
static int tolua_spell_CSpellConfig_BeginSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellConfig",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellConfig* self = (CSpellConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BeginSpell'", NULL);
#endif
 {
  self->BeginSpell();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BeginSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NextSpell of class  CSpellConfig */
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_NextSpell00
static int tolua_spell_CSpellConfig_NextSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSpellConfig",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSpellConfig* self = (CSpellConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NextSpell'", NULL);
#endif
 {
  CSpellTemplate* tolua_ret = (CSpellTemplate*)  self->NextSpell();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpellTemplate");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NextSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMainSpell of class  ISpellBook */
#ifndef TOLUA_DISABLE_tolua_spell_ISpellBook_GetMainSpell00
static int tolua_spell_ISpellBook_GetMainSpell00(lua_State* tolua_S)
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
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMainSpell'", NULL);
#endif
 {
  CSpell* tolua_ret = (CSpell*)  self->GetMainSpell(nSpellID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpell");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMainSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpellSet of class  ISpellBook */
#ifndef TOLUA_DISABLE_tolua_spell_ISpellBook_GetSpellSet00
static int tolua_spell_ISpellBook_GetSpellSet00(lua_State* tolua_S)
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

/* method: BeginSpellSet of class  ISpellBook */
#ifndef TOLUA_DISABLE_tolua_spell_ISpellBook_BeginSpellSet00
static int tolua_spell_ISpellBook_BeginSpellSet00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_spell_ISpellBook_NextSpellSet00
static int tolua_spell_ISpellBook_NextSpellSet00(lua_State* tolua_S)
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

/* method: RemoveSpell of class  ISpellBook */
#ifndef TOLUA_DISABLE_tolua_spell_ISpellBook_RemoveSpell00
static int tolua_spell_ISpellBook_RemoveSpell00(lua_State* tolua_S)
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
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveSpell'", NULL);
#endif
 {
  self->RemoveSpell(nSpellID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLockedTarget of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetLockedTarget00
static int tolua_spell_CTargetScanner_GetLockedTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLockedTarget'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetLockedTarget();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLockedTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTargetX of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetTargetX00
static int tolua_spell_CTargetScanner_GetTargetX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTargetX'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetTargetX();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTargetX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTargetY of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetTargetY00
static int tolua_spell_CTargetScanner_GetTargetY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTargetY'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetTargetY();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTargetY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTargetZ of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetTargetZ00
static int tolua_spell_CTargetScanner_GetTargetZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTargetZ'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetTargetZ();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTargetZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRangeType of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetRangeType00
static int tolua_spell_CTargetScanner_GetRangeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRangeType'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetRangeType();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRangeType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParam1 of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetParam100
static int tolua_spell_CTargetScanner_GetParam100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParam1'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetParam1();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetParam1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParam2 of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetParam200
static int tolua_spell_CTargetScanner_GetParam200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParam2'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetParam2();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetParam2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParam3 of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetParam300
static int tolua_spell_CTargetScanner_GetParam300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParam3'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetParam3();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetParam3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTargetCount of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetTargetCount00
static int tolua_spell_CTargetScanner_GetTargetCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTargetCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetTargetCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTargetCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDirection of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetDirection00
static int tolua_spell_CTargetScanner_GetDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDirection'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetDirection();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BeginTarget of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_BeginTarget00
static int tolua_spell_CTargetScanner_BeginTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BeginTarget'", NULL);
#endif
 {
  self->BeginTarget();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BeginTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NextTarget of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_NextTarget00
static int tolua_spell_CTargetScanner_NextTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NextTarget'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->NextTarget();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NextTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoopNextTarget of class  CTargetScanner */
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_LoopNextTarget00
static int tolua_spell_CTargetScanner_LoopNextTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CTargetScanner",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CTargetScanner* self = (CTargetScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoopNextTarget'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->LoopNextTarget();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoopNextTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_spell_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_SPELL_LEVEL",MAX_SPELL_LEVEL);
 tolua_constant(tolua_S,"MAX_RUNE_SLOT",MAX_RUNE_SLOT);
 tolua_constant(tolua_S,"MAX_EX_PARAM_COUNT",MAX_EX_PARAM_COUNT);
 tolua_constant(tolua_S,"MAX_SPELL_NAME",MAX_SPELL_NAME);
 tolua_constant(tolua_S,"MAX_CD_GROUP",MAX_CD_GROUP);
 tolua_constant(tolua_S,"MAX_EX_CAST",MAX_EX_CAST);
 tolua_constant(tolua_S,"MAX_SPELL_TARGET_COUNT",MAX_SPELL_TARGET_COUNT);
 tolua_constant(tolua_S,"MAX_SPELL_EFFECT_DISTANCE",MAX_SPELL_EFFECT_DISTANCE);
 tolua_constant(tolua_S,"MAX_SUBSPELL_DEPTH",MAX_SUBSPELL_DEPTH);
  tolua_constant(tolua_S,"qssSlotInvalid",qssSlotInvalid);
  tolua_constant(tolua_S,"qssSlotBegin",qssSlotBegin);
  tolua_constant(tolua_S,"qssNormalAtk",qssNormalAtk);
  tolua_constant(tolua_S,"qssQteBegin",qssQteBegin);
  tolua_constant(tolua_S,"qssBossQTE",qssBossQTE);
  tolua_constant(tolua_S,"qssQteEnd",qssQteEnd);
  tolua_constant(tolua_S,"qssPassiveBegin",qssPassiveBegin);
  tolua_constant(tolua_S,"qssPassive1",qssPassive1);
  tolua_constant(tolua_S,"qssPassive2",qssPassive2);
  tolua_constant(tolua_S,"qssPassive3",qssPassive3);
  tolua_constant(tolua_S,"qssPassiveEnd",qssPassiveEnd);
  tolua_constant(tolua_S,"qssActiveBegin",qssActiveBegin);
  tolua_constant(tolua_S,"qssKey0",qssKey0);
  tolua_constant(tolua_S,"qssKey1",qssKey1);
  tolua_constant(tolua_S,"qssKey2",qssKey2);
  tolua_constant(tolua_S,"qssKey3",qssKey3);
  tolua_constant(tolua_S,"qssKey4",qssKey4);
  tolua_constant(tolua_S,"qssKey5",qssKey5);
  tolua_constant(tolua_S,"qssKey6",qssKey6);
  tolua_constant(tolua_S,"qssKey7",qssKey7);
  tolua_constant(tolua_S,"qssKey8",qssKey8);
  tolua_constant(tolua_S,"qssKey9",qssKey9);
  tolua_constant(tolua_S,"qssKey10",qssKey10);
  tolua_constant(tolua_S,"qssKey11",qssKey11);
  tolua_constant(tolua_S,"qssActiveEnd",qssActiveEnd);
  tolua_constant(tolua_S,"qssSlotCount",qssSlotCount);
  tolua_constant(tolua_S,"sfbInvalid",sfbInvalid);
  tolua_constant(tolua_S,"sfbRoundTableBegin",sfbRoundTableBegin);
  tolua_constant(tolua_S,"sfbCrit",sfbCrit);
  tolua_constant(tolua_S,"sfbBlock",sfbBlock);
  tolua_constant(tolua_S,"sfbDodge",sfbDodge);
  tolua_constant(tolua_S,"sfbParry",sfbParry);
  tolua_constant(tolua_S,"sfbMiss",sfbMiss);
  tolua_constant(tolua_S,"sfbNormal",sfbNormal);
  tolua_constant(tolua_S,"sfbRoundTableEnd",sfbRoundTableEnd);
  tolua_constant(tolua_S,"sfbImmune",sfbImmune);
  tolua_constant(tolua_S,"sfbDead",sfbDead);
  tolua_constant(tolua_S,"sfbEmptyEffect",sfbEmptyEffect);
  tolua_constant(tolua_S,"sfbTotal",sfbTotal);
  tolua_constant(tolua_S,"spctInvalid",spctInvalid);
  tolua_constant(tolua_S,"spctPassive",spctPassive);
  tolua_constant(tolua_S,"spctActive",spctActive);
  tolua_constant(tolua_S,"spctSubSpell",spctSubSpell);
  tolua_constant(tolua_S,"spctDirectly",spctDirectly);
  tolua_constant(tolua_S,"spctSwitch",spctSwitch);
  tolua_constant(tolua_S,"spctTotal",spctTotal);
  tolua_constant(tolua_S,"spjtInvalid",spjtInvalid);
  tolua_constant(tolua_S,"spjtDirectly",spjtDirectly);
  tolua_constant(tolua_S,"spjtPhy",spjtPhy);
  tolua_constant(tolua_S,"spjtMag",spjtMag);
  tolua_constant(tolua_S,"spjtTotal",spjtTotal);
  tolua_constant(tolua_S,"spatInvalid",spatInvalid);
  tolua_constant(tolua_S,"spatNone",spatNone);
  tolua_constant(tolua_S,"spatPhy",spatPhy);
  tolua_constant(tolua_S,"spatMag",spatMag);
  tolua_constant(tolua_S,"spatTao",spatTao);
  tolua_constant(tolua_S,"spatTotal",spatTotal);
  tolua_constant(tolua_S,"spdtInvalid",spdtInvalid);
  tolua_constant(tolua_S,"spdtNone",spdtNone);
  tolua_constant(tolua_S,"spdtDamageTypeBegin",spdtDamageTypeBegin);
  tolua_constant(tolua_S,"spdtPhy",spdtPhy);
  tolua_constant(tolua_S,"spdtEarth",spdtEarth);
  tolua_constant(tolua_S,"spdtFire",spdtFire);
  tolua_constant(tolua_S,"spdtWater",spdtWater);
  tolua_constant(tolua_S,"spdtWind",spdtWind);
  tolua_constant(tolua_S,"spdtThunder",spdtThunder);
  tolua_constant(tolua_S,"spdtLight",spdtLight);
  tolua_constant(tolua_S,"spdtShadow",spdtShadow);
  tolua_constant(tolua_S,"spdtNature",spdtNature);
  tolua_constant(tolua_S,"spdtDamageTypeEnd",spdtDamageTypeEnd);
  tolua_constant(tolua_S,"spdtTotal",spdtTotal);
  tolua_constant(tolua_S,"sprtInvalid",sprtInvalid);
  tolua_constant(tolua_S,"sprtSingle",sprtSingle);
  tolua_constant(tolua_S,"sprtCircle",sprtCircle);
  tolua_constant(tolua_S,"sprtSector",sprtSector);
  tolua_constant(tolua_S,"sprtArc",sprtArc);
  tolua_constant(tolua_S,"sprtRectangle",sprtRectangle);
  tolua_constant(tolua_S,"sprtRearHalfCircle",sprtRearHalfCircle);
  tolua_constant(tolua_S,"sprtGridBegin",sprtGridBegin);
  tolua_constant(tolua_S,"sprtGridLine",sprtGridLine);
  tolua_constant(tolua_S,"sprtGridRect",sprtGridRect);
  tolua_constant(tolua_S,"sprtGridCross",sprtGridCross);
  tolua_constant(tolua_S,"sprtGridX",sprtGridX);
  tolua_constant(tolua_S,"sprtGridU",sprtGridU);
  tolua_constant(tolua_S,"sprtGridSingle",sprtGridSingle);
  tolua_constant(tolua_S,"sprtGridLineTransverse",sprtGridLineTransverse);
  tolua_constant(tolua_S,"sprtGridMultiLine",sprtGridMultiLine);
  tolua_constant(tolua_S,"sprtGridEnd",sprtGridEnd);
  tolua_constant(tolua_S,"sprtTotal",sprtTotal);
  tolua_constant(tolua_S,"spltInvalid",spltInvalid);
  tolua_constant(tolua_S,"spltSelf",spltSelf);
  tolua_constant(tolua_S,"spltObject",spltObject);
  tolua_constant(tolua_S,"spltDirection",spltDirection);
  tolua_constant(tolua_S,"spltPos",spltPos);
  tolua_constant(tolua_S,"spltSelfPos",spltSelfPos);
  tolua_constant(tolua_S,"spltSmartPos",spltSmartPos);
  tolua_constant(tolua_S,"spltTotal",spltTotal);
  tolua_constant(tolua_S,"spcotInvalid",spcotInvalid);
  tolua_constant(tolua_S,"spcotFury",spcotFury);
  tolua_constant(tolua_S,"spcotEnergy",spcotEnergy);
  tolua_constant(tolua_S,"spcotMana",spcotMana);
  tolua_constant(tolua_S,"spcotWhite",spcotWhite);
  tolua_constant(tolua_S,"spcotTotal",spcotTotal);
  tolua_constant(tolua_S,"sptstInvalid",sptstInvalid);
  tolua_constant(tolua_S,"sptstMale",sptstMale);
  tolua_constant(tolua_S,"sptstFemale",sptstFemale);
  tolua_constant(tolua_S,"sptstNone",sptstNone);
  tolua_constant(tolua_S,"sptptInvalid",sptptInvalid);
  tolua_constant(tolua_S,"sptptFront",sptptFront);
  tolua_constant(tolua_S,"sptptBack",sptptBack);
  tolua_constant(tolua_S,"sptrInvalid",sptrInvalid);
  tolua_constant(tolua_S,"sptrSelf",sptrSelf);
  tolua_constant(tolua_S,"sptrFriendly",sptrFriendly);
  tolua_constant(tolua_S,"sptrEnemy",sptrEnemy);
  tolua_constant(tolua_S,"sptrTotal",sptrTotal);
  tolua_constant(tolua_S,"sptotInvalid",sptotInvalid);
  tolua_constant(tolua_S,"sptotNone",sptotNone);
  tolua_constant(tolua_S,"sptotPlayer",sptotPlayer);
  tolua_constant(tolua_S,"sptotHuman",sptotHuman);
  tolua_constant(tolua_S,"sptotHumanlike",sptotHumanlike);
  tolua_constant(tolua_S,"sptotBeast",sptotBeast);
  tolua_constant(tolua_S,"sptotInsect",sptotInsect);
  tolua_constant(tolua_S,"sptotPlant",sptotPlant);
  tolua_constant(tolua_S,"sptotUndead",sptotUndead);
  tolua_constant(tolua_S,"sptotMachine",sptotMachine);
  tolua_constant(tolua_S,"sptotDragon",sptotDragon);
  tolua_constant(tolua_S,"sptotDemon",sptotDemon);
  tolua_constant(tolua_S,"sptotElements",sptotElements);
  tolua_constant(tolua_S,"sptotBuilding",sptotBuilding);
  tolua_constant(tolua_S,"sptotTotal",sptotTotal);
  tolua_constant(tolua_S,"spcdtInvalid",spcdtInvalid);
  tolua_constant(tolua_S,"spcdtOnPrepare",spcdtOnPrepare);
  tolua_constant(tolua_S,"spcdtOnCast",spcdtOnCast);
  tolua_constant(tolua_S,"spcdtTotal",spcdtTotal);
  tolua_constant(tolua_S,"sfpptInvalid",sfpptInvalid);
  tolua_constant(tolua_S,"sfpptChanneled",sfpptChanneled);
  tolua_constant(tolua_S,"sfpptPrepared",sfpptPrepared);
  tolua_constant(tolua_S,"sfpptPreparedEx",sfpptPreparedEx);
  tolua_constant(tolua_S,"sfpptInstantCast",sfpptInstantCast);
  tolua_constant(tolua_S,"sfpptAccumulated",sfpptAccumulated);
  tolua_constant(tolua_S,"sfpptTotal",sfpptTotal);
  tolua_constant(tolua_S,"spptInvalid",spptInvalid);
  tolua_constant(tolua_S,"spptChanneled",spptChanneled);
  tolua_constant(tolua_S,"spptPrepared",spptPrepared);
  tolua_constant(tolua_S,"spptAccumulated",spptAccumulated);
  tolua_constant(tolua_S,"spptTotal",spptTotal);
  tolua_constant(tolua_S,"spcltInvalid",spcltInvalid);
  tolua_constant(tolua_S,"spcltNone",spcltNone);
  tolua_constant(tolua_S,"spcltDependOnValue",spcltDependOnValue);
  tolua_constant(tolua_S,"spcltInstant",spcltInstant);
  tolua_constant(tolua_S,"spcltTotal",spcltTotal);
  tolua_constant(tolua_S,"spctagInvalid",spctagInvalid);
  tolua_constant(tolua_S,"spctagNoMove",spctagNoMove);
  tolua_constant(tolua_S,"spctagNoCast",spctagNoCast);
  tolua_constant(tolua_S,"spctagTotal",spctagTotal);
  tolua_constant(tolua_S,"sphtagInvalid",sphtagInvalid);
  tolua_constant(tolua_S,"sphtagCommon",sphtagCommon);
  tolua_constant(tolua_S,"sphtagDefence",sphtagDefence);
  tolua_constant(tolua_S,"sphtagSuperArmor",sphtagSuperArmor);
  tolua_constant(tolua_S,"sphtagInvincible",sphtagInvincible);
  tolua_constant(tolua_S,"sphtagTotal",sphtagTotal);
  tolua_constant(tolua_S,"spslInvalid",spslInvalid);
  tolua_constant(tolua_S,"spslBreakCast",spslBreakCast);
  tolua_constant(tolua_S,"spslBreakMovement",spslBreakMovement);
  tolua_constant(tolua_S,"spslKnockBack",spslKnockBack);
  tolua_constant(tolua_S,"spslTotal",spslTotal);
  tolua_constant(tolua_S,"spqteInvalid",spqteInvalid);
  tolua_constant(tolua_S,"spqteNone",spqteNone);
  tolua_constant(tolua_S,"spqteCounter",spqteCounter);
  tolua_constant(tolua_S,"spqteChase",spqteChase);
  tolua_constant(tolua_S,"spqteTerminate",spqteTerminate);
  tolua_constant(tolua_S,"spqteTotal",spqteTotal);
  tolua_constant(tolua_S,"betInvalid",betInvalid);
  tolua_constant(tolua_S,"betBegin",betBegin);
  tolua_constant(tolua_S,"betDamage",betDamage);
  tolua_constant(tolua_S,"betHeal",betHeal);
  tolua_constant(tolua_S,"betNone",betNone);
  tolua_constant(tolua_S,"betTotal",betTotal);
#ifndef TOLUA_DISABLE_tolua_spell_MakeSpellKey00
 tolua_function(tolua_S,"MakeSpellKey",tolua_spell_MakeSpellKey00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_MakeSpellProgressKey00
 tolua_function(tolua_S,"MakeSpellProgressKey",tolua_spell_MakeSpellProgressKey00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_MakeAuraKey00
 tolua_function(tolua_S,"MakeAuraKey",tolua_spell_MakeAuraKey00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_MakeAuraInstanceKey00
 tolua_function(tolua_S,"MakeAuraInstanceKey",tolua_spell_MakeAuraInstanceKey00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_GetAuraTypeFromInstanceID00
 tolua_function(tolua_S,"GetAuraTypeFromInstanceID",tolua_spell_GetAuraTypeFromInstanceID00);
#endif //#ifndef TOLUA_DISABLE
  tolua_constant(tolua_S,"COOLDOWN_INVALID",COOLDOWN_INVALID);
  tolua_constant(tolua_S,"COOLDOWN_GROUP",COOLDOWN_GROUP);
  tolua_constant(tolua_S,"COOLDOWN_SPELL",COOLDOWN_SPELL);
  tolua_constant(tolua_S,"COOLDOWN_ITEM",COOLDOWN_ITEM);
  tolua_constant(tolua_S,"COOLDOWN_QUEST",COOLDOWN_QUEST);
  tolua_constant(tolua_S,"COOLDOWN_AI",COOLDOWN_AI);
  tolua_constant(tolua_S,"COOLDOWN_SPELL_EVENT_TRIGGER",COOLDOWN_SPELL_EVENT_TRIGGER);
  tolua_constant(tolua_S,"COOLDOWN_MISC",COOLDOWN_MISC);
  tolua_constant(tolua_S,"COOLDOWN_SCRIPT_SPELL",COOLDOWN_SCRIPT_SPELL);
  tolua_constant(tolua_S,"COOLDOWN_SPECIAL_ITEM",COOLDOWN_SPECIAL_ITEM);
  tolua_constant(tolua_S,"COOLDOWN_GUILD",COOLDOWN_GUILD);
  tolua_constant(tolua_S,"COOLDOWN_TOTAL",COOLDOWN_TOTAL);
  tolua_constant(tolua_S,"COOLDOWN_MISC_INVALID",COOLDOWN_MISC_INVALID);
  tolua_constant(tolua_S,"COOLDOWN_MISC_HERO_REVIVE",COOLDOWN_MISC_HERO_REVIVE);
  tolua_constant(tolua_S,"COOLDOWN_MISC_ARREST",COOLDOWN_MISC_ARREST);
  tolua_constant(tolua_S,"COOLDOWN_MISC_TOTAL",COOLDOWN_MISC_TOTAL);
  tolua_constant(tolua_S,"COOLDOWN_SAVE_TYPE_INVALID",COOLDOWN_SAVE_TYPE_INVALID);
  tolua_constant(tolua_S,"COOLDOWN_SAVE_TYPE_OFFLINE_TIME_VALID",COOLDOWN_SAVE_TYPE_OFFLINE_TIME_VALID);
  tolua_constant(tolua_S,"COOLDOWN_SAVE_TYPE_OFFLINE_TIME_INVALID",COOLDOWN_SAVE_TYPE_OFFLINE_TIME_INVALID);
#ifndef TOLUA_DISABLE_tolua_spell_MakeCoolDownID00
 tolua_function(tolua_S,"MakeCoolDownID",tolua_spell_MakeCoolDownID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_ParseCoolDownID00
 tolua_function(tolua_S,"ParseCoolDownID",tolua_spell_ParseCoolDownID00);
#endif //#ifndef TOLUA_DISABLE
  tolua_constant(tolua_S,"ptInvalid",ptInvalid);
  tolua_constant(tolua_S,"ptNone",ptNone);
  tolua_constant(tolua_S,"ptNormal",ptNormal);
  tolua_constant(tolua_S,"ptFast",ptFast);
  tolua_constant(tolua_S,"ptTotal",ptTotal);
  tolua_constant(tolua_S,"nptInvalid",nptInvalid);
  tolua_constant(tolua_S,"nptType1",nptType1);
  tolua_constant(tolua_S,"nptType2",nptType2);
  tolua_constant(tolua_S,"nptType3",nptType3);
  tolua_constant(tolua_S,"nptCount",nptCount);
  tolua_constant(tolua_S,"rftInvalid",rftInvalid);
  tolua_constant(tolua_S,"rftFragA",rftFragA);
  tolua_constant(tolua_S,"rftFragB",rftFragB);
  tolua_constant(tolua_S,"rftFragC",rftFragC);
  tolua_constant(tolua_S,"rftFragD",rftFragD);
  tolua_constant(tolua_S,"rftFragE",rftFragE);
  tolua_constant(tolua_S,"rftCount",rftCount);
  tolua_constant(tolua_S,"rdtInvalid",rdtInvalid);
  tolua_constant(tolua_S,"rdtNever",rdtNever);
  tolua_constant(tolua_S,"rdtByUseTimes",rdtByUseTimes);
  tolua_constant(tolua_S,"rdtByDuration",rdtByDuration);
  tolua_constant(tolua_S,"rdtCount",rdtCount);
 tolua_cclass(tolua_S,"CSpell","CSpell","",NULL);
 tolua_beginmodule(tolua_S,"CSpell");
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_GetID00
  tolua_function(tolua_S,"GetID",tolua_spell_CSpell_GetID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_GetLevel00
  tolua_function(tolua_S,"GetLevel",tolua_spell_CSpell_GetLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_GetRuneSlot00
  tolua_function(tolua_S,"GetRuneSlot",tolua_spell_CSpell_GetRuneSlot00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_GetAttr00
  tolua_function(tolua_S,"GetAttr",tolua_spell_CSpell_GetAttr00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_CanBindSlot00
  tolua_function(tolua_S,"CanBindSlot",tolua_spell_CSpell_CanBindSlot00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_CanShowOnUI00
  tolua_function(tolua_S,"CanShowOnUI",tolua_spell_CSpell_CanShowOnUI00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpell_CanLearnByClass00
  tolua_function(tolua_S,"CanLearnByClass",tolua_spell_CSpell_CanLearnByClass00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CSpellTemplate","CSpellTemplate","CSpell",NULL);
 tolua_beginmodule(tolua_S,"CSpellTemplate");
#ifndef TOLUA_DISABLE_tolua_spell_CSpellTemplate_SetAttr00
  tolua_function(tolua_S,"SetAttr",tolua_spell_CSpellTemplate_SetAttr00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CSpellSet","CSpellSet","",NULL);
 tolua_beginmodule(tolua_S,"CSpellSet");
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSet_GetID00
  tolua_function(tolua_S,"GetID",tolua_spell_CSpellSet_GetID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSet_GetLevel00
  tolua_function(tolua_S,"GetLevel",tolua_spell_CSpellSet_GetLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSet_GetSpell00
  tolua_function(tolua_S,"GetSpell",tolua_spell_CSpellSet_GetSpell00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSet_GetID01
  tolua_function(tolua_S,"GetID",tolua_spell_CSpellSet_GetID01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSet_GetLevel01
  tolua_function(tolua_S,"GetLevel",tolua_spell_CSpellSet_GetLevel01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSet_GetRuneSlot00
  tolua_function(tolua_S,"GetRuneSlot",tolua_spell_CSpellSet_GetRuneSlot00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CSpellInstance","CSpellInstance","CSpell",NULL);
 tolua_beginmodule(tolua_S,"CSpellInstance");
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetFromObjID00
  tolua_function(tolua_S,"GetFromObjID",tolua_spell_CSpellInstance_GetFromObjID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetScanner00
  tolua_function(tolua_S,"GetScanner",tolua_spell_CSpellInstance_GetScanner00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetInitX00
  tolua_function(tolua_S,"GetInitX",tolua_spell_CSpellInstance_GetInitX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetInitY00
  tolua_function(tolua_S,"GetInitY",tolua_spell_CSpellInstance_GetInitY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetInitZ00
  tolua_function(tolua_S,"GetInitZ",tolua_spell_CSpellInstance_GetInitZ00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetAtkSpeedFactor00
  tolua_function(tolua_S,"GetAtkSpeedFactor",tolua_spell_CSpellInstance_GetAtkSpeedFactor00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetWeaponSpeedFactor00
  tolua_function(tolua_S,"GetWeaponSpeedFactor",tolua_spell_CSpellInstance_GetWeaponSpeedFactor00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetWeaponStiffFactor00
  tolua_function(tolua_S,"GetWeaponStiffFactor",tolua_spell_CSpellInstance_GetWeaponStiffFactor00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetCastSerial00
  tolua_function(tolua_S,"GetCastSerial",tolua_spell_CSpellInstance_GetCastSerial00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetEffectSerial00
  tolua_function(tolua_S,"GetEffectSerial",tolua_spell_CSpellInstance_GetEffectSerial00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetPrepareTimeMinFrm00
  tolua_function(tolua_S,"GetPrepareTimeMinFrm",tolua_spell_CSpellInstance_GetPrepareTimeMinFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetPrepareTimeMaxFrm00
  tolua_function(tolua_S,"GetPrepareTimeMaxFrm",tolua_spell_CSpellInstance_GetPrepareTimeMaxFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetIntervalFrm00
  tolua_function(tolua_S,"GetIntervalFrm",tolua_spell_CSpellInstance_GetIntervalFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetHardTimeFrm00
  tolua_function(tolua_S,"GetHardTimeFrm",tolua_spell_CSpellInstance_GetHardTimeFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetResetTimeFrm00
  tolua_function(tolua_S,"GetResetTimeFrm",tolua_spell_CSpellInstance_GetResetTimeFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetCacheTimeFrm00
  tolua_function(tolua_S,"GetCacheTimeFrm",tolua_spell_CSpellInstance_GetCacheTimeFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetAccumulateTimeMaxFrm00
  tolua_function(tolua_S,"GetAccumulateTimeMaxFrm",tolua_spell_CSpellInstance_GetAccumulateTimeMaxFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetStiffFrm00
  tolua_function(tolua_S,"GetStiffFrm",tolua_spell_CSpellInstance_GetStiffFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellInstance_GetExCastFrm00
  tolua_function(tolua_S,"GetExCastFrm",tolua_spell_CSpellInstance_GetExCastFrm00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CSpellSlot","CSpellSlot","",NULL);
 tolua_beginmodule(tolua_S,"CSpellSlot");
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSlot_Lock00
  tolua_function(tolua_S,"Lock",tolua_spell_CSpellSlot_Lock00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSlot_IsLocked00
  tolua_function(tolua_S,"IsLocked",tolua_spell_CSpellSlot_IsLocked00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellSlot_GetMainSpellID00
  tolua_function(tolua_S,"GetMainSpellID",tolua_spell_CSpellSlot_GetMainSpellID00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CAura","CAura","",NULL);
 tolua_beginmodule(tolua_S,"CAura");
#ifndef TOLUA_DISABLE_tolua_spell_CAura_GetID00
  tolua_function(tolua_S,"GetID",tolua_spell_CAura_GetID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAura_GetAttr00
  tolua_function(tolua_S,"GetAttr",tolua_spell_CAura_GetAttr00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAura_GetDurationFrm00
  tolua_function(tolua_S,"GetDurationFrm",tolua_spell_CAura_GetDurationFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAura_GetIntervalFrm00
  tolua_function(tolua_S,"GetIntervalFrm",tolua_spell_CAura_GetIntervalFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAura_GetDelayFrm00
  tolua_function(tolua_S,"GetDelayFrm",tolua_spell_CAura_GetDelayFrm00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAura_GetEffectMinFrm00
  tolua_function(tolua_S,"GetEffectMinFrm",tolua_spell_CAura_GetEffectMinFrm00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CAuraTemplate","CAuraTemplate","CAura",NULL);
 tolua_beginmodule(tolua_S,"CAuraTemplate");
#ifndef TOLUA_DISABLE_tolua_spell_CAuraTemplate_InitAttr00
  tolua_function(tolua_S,"InitAttr",tolua_spell_CAuraTemplate_InitAttr00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAuraTemplate_InitWithData00
  tolua_function(tolua_S,"InitWithData",tolua_spell_CAuraTemplate_InitWithData00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CAuraInstance","CAuraInstance","CAura",NULL);
 tolua_beginmodule(tolua_S,"CAuraInstance");
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetInstanceID00
  tolua_function(tolua_S,"GetInstanceID",tolua_spell_CAuraInstance_GetInstanceID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetStackCount00
  tolua_function(tolua_S,"GetStackCount",tolua_spell_CAuraInstance_GetStackCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetCasterID00
  tolua_function(tolua_S,"GetCasterID",tolua_spell_CAuraInstance_GetCasterID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetFromObjID00
  tolua_function(tolua_S,"GetFromObjID",tolua_spell_CAuraInstance_GetFromObjID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetStrengthLevel00
  tolua_function(tolua_S,"GetStrengthLevel",tolua_spell_CAuraInstance_GetStrengthLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetTotalEffectValue00
  tolua_function(tolua_S,"GetTotalEffectValue",tolua_spell_CAuraInstance_GetTotalEffectValue00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetEffectPct00
  tolua_function(tolua_S,"GetEffectPct",tolua_spell_CAuraInstance_GetEffectPct00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetEffectValue00
  tolua_function(tolua_S,"GetEffectValue",tolua_spell_CAuraInstance_GetEffectValue00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetSpellID00
  tolua_function(tolua_S,"GetSpellID",tolua_spell_CAuraInstance_GetSpellID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetSpellLevel00
  tolua_function(tolua_S,"GetSpellLevel",tolua_spell_CAuraInstance_GetSpellLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAuraInstance_GetRemainFrm00
  tolua_function(tolua_S,"GetRemainFrm",tolua_spell_CAuraInstance_GetRemainFrm00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CAuraList","CAuraList","",NULL);
 tolua_beginmodule(tolua_S,"CAuraList");
#ifndef TOLUA_DISABLE_tolua_spell_CAuraList_BeginAura00
  tolua_function(tolua_S,"BeginAura",tolua_spell_CAuraList_BeginAura00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CAuraList_NextAura00
  tolua_function(tolua_S,"NextAura",tolua_spell_CAuraList_NextAura00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CSpellConfig","CSpellConfig","",NULL);
 tolua_beginmodule(tolua_S,"CSpellConfig");
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_spell_CSpellConfig_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_FindAuraTemplate00
  tolua_function(tolua_S,"FindAuraTemplate",tolua_spell_CSpellConfig_FindAuraTemplate00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_NewAuraTemplate00
  tolua_function(tolua_S,"NewAuraTemplate",tolua_spell_CSpellConfig_NewAuraTemplate00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_GetHighestLevel00
  tolua_function(tolua_S,"GetHighestLevel",tolua_spell_CSpellConfig_GetHighestLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_FindSpellTemplate00
  tolua_function(tolua_S,"FindSpellTemplate",tolua_spell_CSpellConfig_FindSpellTemplate00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_SetSpellTemplate00
  tolua_function(tolua_S,"SetSpellTemplate",tolua_spell_CSpellConfig_SetSpellTemplate00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_SetSpellMaxProgress00
  tolua_function(tolua_S,"SetSpellMaxProgress",tolua_spell_CSpellConfig_SetSpellMaxProgress00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_GetMaxProgress00
  tolua_function(tolua_S,"GetMaxProgress",tolua_spell_CSpellConfig_GetMaxProgress00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_BeginSpell00
  tolua_function(tolua_S,"BeginSpell",tolua_spell_CSpellConfig_BeginSpell00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CSpellConfig_NextSpell00
  tolua_function(tolua_S,"NextSpell",tolua_spell_CSpellConfig_NextSpell00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"ISpellBook","ISpellBook","",NULL);
 tolua_beginmodule(tolua_S,"ISpellBook");
#ifndef TOLUA_DISABLE_tolua_spell_ISpellBook_GetMainSpell00
  tolua_function(tolua_S,"GetMainSpell",tolua_spell_ISpellBook_GetMainSpell00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_ISpellBook_GetSpellSet00
  tolua_function(tolua_S,"GetSpellSet",tolua_spell_ISpellBook_GetSpellSet00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_ISpellBook_BeginSpellSet00
  tolua_function(tolua_S,"BeginSpellSet",tolua_spell_ISpellBook_BeginSpellSet00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_ISpellBook_NextSpellSet00
  tolua_function(tolua_S,"NextSpellSet",tolua_spell_ISpellBook_NextSpellSet00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_ISpellBook_RemoveSpell00
  tolua_function(tolua_S,"RemoveSpell",tolua_spell_ISpellBook_RemoveSpell00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CTargetScanner","CTargetScanner","",NULL);
 tolua_beginmodule(tolua_S,"CTargetScanner");
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetLockedTarget00
  tolua_function(tolua_S,"GetLockedTarget",tolua_spell_CTargetScanner_GetLockedTarget00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetTargetX00
  tolua_function(tolua_S,"GetTargetX",tolua_spell_CTargetScanner_GetTargetX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetTargetY00
  tolua_function(tolua_S,"GetTargetY",tolua_spell_CTargetScanner_GetTargetY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetTargetZ00
  tolua_function(tolua_S,"GetTargetZ",tolua_spell_CTargetScanner_GetTargetZ00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetRangeType00
  tolua_function(tolua_S,"GetRangeType",tolua_spell_CTargetScanner_GetRangeType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetParam100
  tolua_function(tolua_S,"GetParam1",tolua_spell_CTargetScanner_GetParam100);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetParam200
  tolua_function(tolua_S,"GetParam2",tolua_spell_CTargetScanner_GetParam200);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetParam300
  tolua_function(tolua_S,"GetParam3",tolua_spell_CTargetScanner_GetParam300);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetTargetCount00
  tolua_function(tolua_S,"GetTargetCount",tolua_spell_CTargetScanner_GetTargetCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_GetDirection00
  tolua_function(tolua_S,"GetDirection",tolua_spell_CTargetScanner_GetDirection00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_BeginTarget00
  tolua_function(tolua_S,"BeginTarget",tolua_spell_CTargetScanner_BeginTarget00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_NextTarget00
  tolua_function(tolua_S,"NextTarget",tolua_spell_CTargetScanner_NextTarget00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_spell_CTargetScanner_LoopNextTarget00
  tolua_function(tolua_S,"LoopNextTarget",tolua_spell_CTargetScanner_LoopNextTarget00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_spell (lua_State* tolua_S) {
 return tolua_spell_open(tolua_S);
};
#endif

