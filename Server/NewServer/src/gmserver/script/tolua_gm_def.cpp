/*
** Lua binding: gm_def
** Generated automatically by tolua++-1.0.92 on 02/11/26 14:43:14.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_gm_def_open (lua_State* tolua_S);

#include "../../inc/baselib/log.h"
#include "../../inc/gm/gm_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"GM_ROLE_SLOT");
 tolua_usertype(tolua_S,"GM_ROLE_MAIL_SLOT");
 tolua_usertype(tolua_S,"GM_ROLE_ITEM_SLOT");
 tolua_usertype(tolua_S,"GM_ROLE_SPELL_SLOT");
 tolua_usertype(tolua_S,"GM_ROLE_TITLE_SLOT");
}

/* get function: wLength of class  GM_ROLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_SLOT_unsigned_wLength
static int tolua_get_GM_ROLE_SLOT_unsigned_wLength(lua_State* tolua_S)
{
  GM_ROLE_SLOT* self = (GM_ROLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wLength'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->wLength);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wLength of class  GM_ROLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_SLOT_unsigned_wLength
static int tolua_set_GM_ROLE_SLOT_unsigned_wLength(lua_State* tolua_S)
{
  GM_ROLE_SLOT* self = (GM_ROLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wLength'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->wLength = (( unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wRoleType of class  GM_ROLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_SLOT_unsigned_wRoleType
static int tolua_get_GM_ROLE_SLOT_unsigned_wRoleType(lua_State* tolua_S)
{
  GM_ROLE_SLOT* self = (GM_ROLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wRoleType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->wRoleType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wRoleType of class  GM_ROLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_SLOT_unsigned_wRoleType
static int tolua_set_GM_ROLE_SLOT_unsigned_wRoleType(lua_State* tolua_S)
{
  GM_ROLE_SLOT* self = (GM_ROLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wRoleType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->wRoleType = (( unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wBaseDataType of class  GM_ROLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_SLOT_unsigned_wBaseDataType
static int tolua_get_GM_ROLE_SLOT_unsigned_wBaseDataType(lua_State* tolua_S)
{
  GM_ROLE_SLOT* self = (GM_ROLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wBaseDataType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->wBaseDataType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wBaseDataType of class  GM_ROLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_SLOT_unsigned_wBaseDataType
static int tolua_set_GM_ROLE_SLOT_unsigned_wBaseDataType(lua_State* tolua_S)
{
  GM_ROLE_SLOT* self = (GM_ROLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wBaseDataType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->wBaseDataType = (( unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szData of class  GM_ROLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_SLOT_szData
static int tolua_get_GM_ROLE_SLOT_szData(lua_State* tolua_S)
{
  GM_ROLE_SLOT* self = (GM_ROLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szData'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szData);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szData of class  GM_ROLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_SLOT_szData
static int tolua_set_GM_ROLE_SLOT_szData(lua_State* tolua_S)
{
  GM_ROLE_SLOT* self = (GM_ROLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szData'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szData,(const char*)tolua_tostring(tolua_S,2,0),0-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSpellID of class  GM_ROLE_SPELL_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_SPELL_SLOT_nSpellID
static int tolua_get_GM_ROLE_SPELL_SLOT_nSpellID(lua_State* tolua_S)
{
  GM_ROLE_SPELL_SLOT* self = (GM_ROLE_SPELL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSpellID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSpellID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSpellID of class  GM_ROLE_SPELL_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_SPELL_SLOT_nSpellID
static int tolua_set_GM_ROLE_SPELL_SLOT_nSpellID(lua_State* tolua_S)
{
  GM_ROLE_SPELL_SLOT* self = (GM_ROLE_SPELL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSpellID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSpellID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nRuneID of class  GM_ROLE_SPELL_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_SPELL_SLOT_nRuneID
static int tolua_get_GM_ROLE_SPELL_SLOT_nRuneID(lua_State* tolua_S)
{
  GM_ROLE_SPELL_SLOT* self = (GM_ROLE_SPELL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRuneID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nRuneID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nRuneID of class  GM_ROLE_SPELL_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_SPELL_SLOT_nRuneID
static int tolua_set_GM_ROLE_SPELL_SLOT_nRuneID(lua_State* tolua_S)
{
  GM_ROLE_SPELL_SLOT* self = (GM_ROLE_SPELL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRuneID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nRuneID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nEquipedIndex of class  GM_ROLE_SPELL_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_SPELL_SLOT_nEquipedIndex
static int tolua_get_GM_ROLE_SPELL_SLOT_nEquipedIndex(lua_State* tolua_S)
{
  GM_ROLE_SPELL_SLOT* self = (GM_ROLE_SPELL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nEquipedIndex'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nEquipedIndex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nEquipedIndex of class  GM_ROLE_SPELL_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_SPELL_SLOT_nEquipedIndex
static int tolua_set_GM_ROLE_SPELL_SLOT_nEquipedIndex(lua_State* tolua_S)
{
  GM_ROLE_SPELL_SLOT* self = (GM_ROLE_SPELL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nEquipedIndex'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nEquipedIndex = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szName of class  GM_ROLE_SPELL_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_SPELL_SLOT_szName
static int tolua_get_GM_ROLE_SPELL_SLOT_szName(lua_State* tolua_S)
{
  GM_ROLE_SPELL_SLOT* self = (GM_ROLE_SPELL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szName of class  GM_ROLE_SPELL_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_SPELL_SLOT_szName
static int tolua_set_GM_ROLE_SPELL_SLOT_szName(lua_State* tolua_S)
{
  GM_ROLE_SPELL_SLOT* self = (GM_ROLE_SPELL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szName,(const char*)tolua_tostring(tolua_S,2,0),MAX_SPELL_NAME_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nTemplateID of class  GM_ROLE_TITLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_TITLE_SLOT_nTemplateID
static int tolua_get_GM_ROLE_TITLE_SLOT_nTemplateID(lua_State* tolua_S)
{
  GM_ROLE_TITLE_SLOT* self = (GM_ROLE_TITLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTemplateID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nTemplateID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nTemplateID of class  GM_ROLE_TITLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_TITLE_SLOT_nTemplateID
static int tolua_set_GM_ROLE_TITLE_SLOT_nTemplateID(lua_State* tolua_S)
{
  GM_ROLE_TITLE_SLOT* self = (GM_ROLE_TITLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTemplateID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nTemplateID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwExpireTime of class  GM_ROLE_TITLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_TITLE_SLOT_unsigned_dwExpireTime
static int tolua_get_GM_ROLE_TITLE_SLOT_unsigned_dwExpireTime(lua_State* tolua_S)
{
  GM_ROLE_TITLE_SLOT* self = (GM_ROLE_TITLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwExpireTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwExpireTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwExpireTime of class  GM_ROLE_TITLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_TITLE_SLOT_unsigned_dwExpireTime
static int tolua_set_GM_ROLE_TITLE_SLOT_unsigned_dwExpireTime(lua_State* tolua_S)
{
  GM_ROLE_TITLE_SLOT* self = (GM_ROLE_TITLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwExpireTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwExpireTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szName of class  GM_ROLE_TITLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_TITLE_SLOT_szName
static int tolua_get_GM_ROLE_TITLE_SLOT_szName(lua_State* tolua_S)
{
  GM_ROLE_TITLE_SLOT* self = (GM_ROLE_TITLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szName of class  GM_ROLE_TITLE_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_TITLE_SLOT_szName
static int tolua_set_GM_ROLE_TITLE_SLOT_szName(lua_State* tolua_S)
{
  GM_ROLE_TITLE_SLOT* self = (GM_ROLE_TITLE_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szName,(const char*)tolua_tostring(tolua_S,2,0),MAX_TITLE_NAME_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwItemID of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_dwItemID
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_dwItemID(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwItemID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwItemID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwItemID of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_dwItemID
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_dwItemID(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwItemID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwItemID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: qwGuid of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_qwGuid
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_qwGuid(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'qwGuid'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->qwGuid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: qwGuid of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_qwGuid
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_qwGuid(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'qwGuid'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->qwGuid = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wConSlot of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_wConSlot
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_wConSlot(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wConSlot'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->wConSlot);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wConSlot of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_wConSlot
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_wConSlot(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wConSlot'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->wConSlot = (( unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wItemSlot of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_wItemSlot
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_wItemSlot(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wItemSlot'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->wItemSlot);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wItemSlot of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_wItemSlot
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_wItemSlot(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wItemSlot'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->wItemSlot = (( unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nType of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_nType
static int tolua_get_GM_ROLE_ITEM_SLOT_nType(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nType of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_nType
static int tolua_set_GM_ROLE_ITEM_SLOT_nType(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nType = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSubType of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_nSubType
static int tolua_get_GM_ROLE_ITEM_SLOT_nSubType(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSubType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSubType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSubType of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_nSubType
static int tolua_set_GM_ROLE_ITEM_SLOT_nSubType(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSubType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSubType = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nNum of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_nNum
static int tolua_get_GM_ROLE_ITEM_SLOT_nNum(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nNum'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nNum);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nNum of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_nNum
static int tolua_set_GM_ROLE_ITEM_SLOT_nNum(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nNum'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nNum = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byBindType of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byBindType
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byBindType(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byBindType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byBindType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byBindType of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byBindType
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byBindType(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byBindType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byBindType = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byIdentified of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byIdentified
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byIdentified(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byIdentified'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byIdentified);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byIdentified of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byIdentified
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byIdentified(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byIdentified'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byIdentified = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wRandomAttrID of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_gm_def_GM_ROLE_ITEM_SLOT_wRandomAttrID
static int tolua_get_gm_def_GM_ROLE_ITEM_SLOT_wRandomAttrID(lua_State* tolua_S)
{
 int tolua_index;
  GM_ROLE_ITEM_SLOT* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GM_ROLE_ITEM_SLOT*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=4)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->wRandomAttrID[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wRandomAttrID of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_gm_def_GM_ROLE_ITEM_SLOT_wRandomAttrID
static int tolua_set_gm_def_GM_ROLE_ITEM_SLOT_wRandomAttrID(lua_State* tolua_S)
{
 int tolua_index;
  GM_ROLE_ITEM_SLOT* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GM_ROLE_ITEM_SLOT*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=4)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->wRandomAttrID[tolua_index] = (( unsigned short)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwRoleID of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_dwRoleID
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_dwRoleID(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwRoleID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwRoleID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwRoleID of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_dwRoleID
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_dwRoleID(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwRoleID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwCostMoney of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_dwCostMoney
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_dwCostMoney(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwCostMoney'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwCostMoney);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwCostMoney of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_dwCostMoney
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_dwCostMoney(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwCostMoney'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwCostMoney = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byLuck of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_byLuck
static int tolua_get_GM_ROLE_ITEM_SLOT_byLuck(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLuck'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byLuck);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byLuck of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_byLuck
static int tolua_set_GM_ROLE_ITEM_SLOT_byLuck(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLuck'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byLuck = (( signed char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byLevelupTimes of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTimes
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTimes(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevelupTimes'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byLevelupTimes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byLevelupTimes of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTimes
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTimes(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevelupTimes'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byLevelupTimes = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byLevelupPhyPoint of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupPhyPoint
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupPhyPoint(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevelupPhyPoint'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byLevelupPhyPoint);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byLevelupPhyPoint of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupPhyPoint
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupPhyPoint(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevelupPhyPoint'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byLevelupPhyPoint = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byLevelupMagPoint of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupMagPoint
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupMagPoint(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevelupMagPoint'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byLevelupMagPoint);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byLevelupMagPoint of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupMagPoint
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupMagPoint(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevelupMagPoint'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byLevelupMagPoint = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byLevelupTaoPoint of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTaoPoint
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTaoPoint(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevelupTaoPoint'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byLevelupTaoPoint);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byLevelupTaoPoint of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTaoPoint
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTaoPoint(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevelupTaoPoint'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byLevelupTaoPoint = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byLevelupTypeHidden of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTypeHidden
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTypeHidden(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevelupTypeHidden'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byLevelupTypeHidden);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byLevelupTypeHidden of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTypeHidden
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTypeHidden(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevelupTypeHidden'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byLevelupTypeHidden = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byLevelupPointHidden of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupPointHidden
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupPointHidden(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevelupPointHidden'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byLevelupPointHidden);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byLevelupPointHidden of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupPointHidden
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupPointHidden(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byLevelupPointHidden'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byLevelupPointHidden = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wRune of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_gm_def_GM_ROLE_ITEM_SLOT_wRune
static int tolua_get_gm_def_GM_ROLE_ITEM_SLOT_wRune(lua_State* tolua_S)
{
 int tolua_index;
  GM_ROLE_ITEM_SLOT* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GM_ROLE_ITEM_SLOT*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=6)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->wRune[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wRune of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_gm_def_GM_ROLE_ITEM_SLOT_wRune
static int tolua_set_gm_def_GM_ROLE_ITEM_SLOT_wRune(lua_State* tolua_S)
{
 int tolua_index;
  GM_ROLE_ITEM_SLOT* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GM_ROLE_ITEM_SLOT*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=6)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->wRune[tolua_index] = (( unsigned short)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwSocketCombination of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_unsigned_dwSocketCombination
static int tolua_get_GM_ROLE_ITEM_SLOT_unsigned_dwSocketCombination(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwSocketCombination'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwSocketCombination);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwSocketCombination of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_unsigned_dwSocketCombination
static int tolua_set_GM_ROLE_ITEM_SLOT_unsigned_dwSocketCombination(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwSocketCombination'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwSocketCombination = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSoulID of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_gm_def_GM_ROLE_ITEM_SLOT_nSoulID
static int tolua_get_gm_def_GM_ROLE_ITEM_SLOT_nSoulID(lua_State* tolua_S)
{
 int tolua_index;
  GM_ROLE_ITEM_SLOT* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GM_ROLE_ITEM_SLOT*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=3)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSoulID[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSoulID of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_gm_def_GM_ROLE_ITEM_SLOT_nSoulID
static int tolua_set_gm_def_GM_ROLE_ITEM_SLOT_nSoulID(lua_State* tolua_S)
{
 int tolua_index;
  GM_ROLE_ITEM_SLOT* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (GM_ROLE_ITEM_SLOT*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=3)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->nSoulID[tolua_index] = (( signed int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szData of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_ITEM_SLOT_szData
static int tolua_get_GM_ROLE_ITEM_SLOT_szData(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szData'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szData);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szData of class  GM_ROLE_ITEM_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_ITEM_SLOT_szData
static int tolua_set_GM_ROLE_ITEM_SLOT_szData(lua_State* tolua_S)
{
  GM_ROLE_ITEM_SLOT* self = (GM_ROLE_ITEM_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szData'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szData,(const char*)tolua_tostring(tolua_S,2,0),0-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwMailID of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_MAIL_SLOT_unsigned_dwMailID
static int tolua_get_GM_ROLE_MAIL_SLOT_unsigned_dwMailID(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwMailID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwMailID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwMailID of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_MAIL_SLOT_unsigned_dwMailID
static int tolua_set_GM_ROLE_MAIL_SLOT_unsigned_dwMailID(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwMailID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwMailID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nMailType of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_MAIL_SLOT_nMailType
static int tolua_get_GM_ROLE_MAIL_SLOT_nMailType(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMailType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMailType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMailType of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_MAIL_SLOT_nMailType
static int tolua_set_GM_ROLE_MAIL_SLOT_nMailType(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMailType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nMailType = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nAttachType of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_MAIL_SLOT_nAttachType
static int tolua_get_GM_ROLE_MAIL_SLOT_nAttachType(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nAttachType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nAttachType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nAttachType of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_MAIL_SLOT_nAttachType
static int tolua_set_GM_ROLE_MAIL_SLOT_nAttachType(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nAttachType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nAttachType = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nState of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_MAIL_SLOT_nState
static int tolua_get_GM_ROLE_MAIL_SLOT_nState(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nState'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nState);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nState of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_MAIL_SLOT_nState
static int tolua_set_GM_ROLE_MAIL_SLOT_nState(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nState'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nState = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nAttachLocked of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_MAIL_SLOT_nAttachLocked
static int tolua_get_GM_ROLE_MAIL_SLOT_nAttachLocked(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nAttachLocked'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nAttachLocked);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nAttachLocked of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_MAIL_SLOT_nAttachLocked
static int tolua_set_GM_ROLE_MAIL_SLOT_nAttachLocked(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nAttachLocked'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nAttachLocked = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nItemID of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_MAIL_SLOT_nItemID
static int tolua_get_GM_ROLE_MAIL_SLOT_nItemID(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nItemID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nItemID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nItemID of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_MAIL_SLOT_nItemID
static int tolua_set_GM_ROLE_MAIL_SLOT_nItemID(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nItemID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nItemID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nItemCount of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_MAIL_SLOT_nItemCount
static int tolua_get_GM_ROLE_MAIL_SLOT_nItemCount(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nItemCount'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nItemCount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nItemCount of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_MAIL_SLOT_nItemCount
static int tolua_set_GM_ROLE_MAIL_SLOT_nItemCount(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nItemCount'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nItemCount = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szData of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_get_GM_ROLE_MAIL_SLOT_szData
static int tolua_get_GM_ROLE_MAIL_SLOT_szData(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szData'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szData);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szData of class  GM_ROLE_MAIL_SLOT */
#ifndef TOLUA_DISABLE_tolua_set_GM_ROLE_MAIL_SLOT_szData
static int tolua_set_GM_ROLE_MAIL_SLOT_szData(lua_State* tolua_S)
{
  GM_ROLE_MAIL_SLOT* self = (GM_ROLE_MAIL_SLOT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szData'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szData,(const char*)tolua_tostring(tolua_S,2,0),0-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_gm_def_open (lua_State* tolua_S)
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
 tolua_constant(tolua_S,"FOREVER_TIME",FOREVER_TIME);
 tolua_constant(tolua_S,"MAX_GM_ROLE_KEY_NUM",MAX_GM_ROLE_KEY_NUM);
 tolua_constant(tolua_S,"GM_SVR_TIMEOUT",GM_SVR_TIMEOUT);
 tolua_constant(tolua_S,"GM_SVR_LONG_TIMEOUT",GM_SVR_LONG_TIMEOUT);
 tolua_constant(tolua_S,"TL_CMD_TIMEOUT_TIME",TL_CMD_TIMEOUT_TIME);
 tolua_constant(tolua_S,"TL_CMD_LONG_TIMEOUT",TL_CMD_LONG_TIMEOUT);
 tolua_constant(tolua_S,"GM_TYPE_CLIENT_CS",GM_TYPE_CLIENT_CS);
 tolua_constant(tolua_S,"MSG_LOG_ITEM_COUNT",MSG_LOG_ITEM_COUNT);
 tolua_constant(tolua_S,"MAX_GM_GAMELOG_LENGTH",MAX_GM_GAMELOG_LENGTH);
 tolua_constant(tolua_S,"MAX_GM_ROLE_DATA_STR_LENGTH",MAX_GM_ROLE_DATA_STR_LENGTH);
 tolua_constant(tolua_S,"MAX_GM_LOG_LENGTH",MAX_GM_LOG_LENGTH);
 tolua_constant(tolua_S,"GM_DATA_LOG_LENGTH",GM_DATA_LOG_LENGTH);
  tolua_constant(tolua_S,"GM_QUERY_BY_ROLE_NAME",GM_QUERY_BY_ROLE_NAME);
  tolua_constant(tolua_S,"GM_QUERY_BY_USER_NAME",GM_QUERY_BY_USER_NAME);
  tolua_constant(tolua_S,"GM_LOG_QUERY_NONE",GM_LOG_QUERY_NONE);
  tolua_constant(tolua_S,"GM_LOG_QUERY_ROLE_LOGIN",GM_LOG_QUERY_ROLE_LOGIN);
  tolua_constant(tolua_S,"GM_LOG_QUERY_ROLE_LOGOUT",GM_LOG_QUERY_ROLE_LOGOUT);
  tolua_constant(tolua_S,"GM_LOG_QUERY_ITEM",GM_LOG_QUERY_ITEM);
  tolua_constant(tolua_S,"GM_LOG_QUERY_MONEY",GM_LOG_QUERY_MONEY);
  tolua_constant(tolua_S,"GM_LOG_QUERY_QUEST",GM_LOG_QUERY_QUEST);
  tolua_constant(tolua_S,"GM_LOG_QUERY_GM",GM_LOG_QUERY_GM);
  tolua_constant(tolua_S,"GM_QUERY_NUM",GM_QUERY_NUM);
  tolua_constant(tolua_S,"GM_ROLE_NONE",GM_ROLE_NONE);
  tolua_constant(tolua_S,"GM_ROLE_BASE_DATA",GM_ROLE_BASE_DATA);
  tolua_constant(tolua_S,"GM_ROLE_TITLE",GM_ROLE_TITLE);
  tolua_constant(tolua_S,"GM_ROLE_SPELL",GM_ROLE_SPELL);
  tolua_constant(tolua_S,"GM_ROLE_ITEM",GM_ROLE_ITEM);
  tolua_constant(tolua_S,"GM_ROLE_QUEST",GM_ROLE_QUEST);
  tolua_constant(tolua_S,"GM_ROLE_MAIL",GM_ROLE_MAIL);
  tolua_constant(tolua_S,"GM_ROLE_TAKE_ITEM",GM_ROLE_TAKE_ITEM);
  tolua_constant(tolua_S,"GM_RBD_NONE",GM_RBD_NONE);
  tolua_constant(tolua_S,"GM_RBD_ID",GM_RBD_ID);
  tolua_constant(tolua_S,"GM_RBD_NAME",GM_RBD_NAME);
  tolua_constant(tolua_S,"GM_RBD_GROUPID",GM_RBD_GROUPID);
  tolua_constant(tolua_S,"GM_RBD_DELETETIME",GM_RBD_DELETETIME);
  tolua_constant(tolua_S,"GM_RBD_CLASS",GM_RBD_CLASS);
  tolua_constant(tolua_S,"GM_RBD_SEX",GM_RBD_SEX);
  tolua_constant(tolua_S,"GM_RBD_LEVEL",GM_RBD_LEVEL);
  tolua_constant(tolua_S,"GM_RBD_EXP",GM_RBD_EXP);
  tolua_constant(tolua_S,"GM_RBD_PKVALUE",GM_RBD_PKVALUE);
  tolua_constant(tolua_S,"GM_RBD_GMLEVEL",GM_RBD_GMLEVEL);
  tolua_constant(tolua_S,"GM_RBD_MAP_ID",GM_RBD_MAP_ID);
  tolua_constant(tolua_S,"GM_RBD_MAP_SERIAL_ID",GM_RBD_MAP_SERIAL_ID);
  tolua_constant(tolua_S,"GM_RBD_X",GM_RBD_X);
  tolua_constant(tolua_S,"GM_RBD_Y",GM_RBD_Y);
  tolua_constant(tolua_S,"GM_RBD_Z",GM_RBD_Z);
  tolua_constant(tolua_S,"GM_RBD_LAST_LOGIN_TIME",GM_RBD_LAST_LOGIN_TIME);
  tolua_constant(tolua_S,"GM_RBD_LAST_LOGOUT_TIME",GM_RBD_LAST_LOGOUT_TIME);
  tolua_constant(tolua_S,"GM_RBD_FORBIDDEND_CHAT_TIME",GM_RBD_FORBIDDEND_CHAT_TIME);
  tolua_constant(tolua_S,"GM_RBD_FREEZE_ROLE_TIME",GM_RBD_FREEZE_ROLE_TIME);
  tolua_constant(tolua_S,"GM_RBD_FREEZE_CHEAT_ROLE",GM_RBD_FREEZE_CHEAT_ROLE);
  tolua_constant(tolua_S,"GM_RBD_GUILD_ID",GM_RBD_GUILD_ID);
  tolua_constant(tolua_S,"GM_RBD_MONEY_1",GM_RBD_MONEY_1);
  tolua_constant(tolua_S,"GM_RBD_MONEY_2",GM_RBD_MONEY_2);
  tolua_constant(tolua_S,"GM_RBD_MONEY_3",GM_RBD_MONEY_3);
  tolua_constant(tolua_S,"GM_RBD_MONEY_4",GM_RBD_MONEY_4);
  tolua_constant(tolua_S,"GM_RBD_MONEY_5",GM_RBD_MONEY_5);
  tolua_constant(tolua_S,"GM_RBD_MONEY_6",GM_RBD_MONEY_6);
  tolua_constant(tolua_S,"GM_RBD_MONEY_7",GM_RBD_MONEY_7);
  tolua_constant(tolua_S,"GM_RBD_MONEY_8",GM_RBD_MONEY_8);
  tolua_constant(tolua_S,"GM_RBD_MONEY_9",GM_RBD_MONEY_9);
  tolua_constant(tolua_S,"GM_RBD_MONEY_10",GM_RBD_MONEY_10);
  tolua_constant(tolua_S,"GM_RBD_MONEY_11",GM_RBD_MONEY_11);
  tolua_constant(tolua_S,"GM_RBD_MONEY_12",GM_RBD_MONEY_12);
  tolua_constant(tolua_S,"GM_RBD_MONEY_13",GM_RBD_MONEY_13);
  tolua_constant(tolua_S,"GM_RBD_MONEY_14",GM_RBD_MONEY_14);
 tolua_cclass(tolua_S,"GM_ROLE_SLOT","GM_ROLE_SLOT","",NULL);
 tolua_beginmodule(tolua_S,"GM_ROLE_SLOT");
  tolua_variable(tolua_S,"wLength",tolua_get_GM_ROLE_SLOT_unsigned_wLength,tolua_set_GM_ROLE_SLOT_unsigned_wLength);
  tolua_variable(tolua_S,"wRoleType",tolua_get_GM_ROLE_SLOT_unsigned_wRoleType,tolua_set_GM_ROLE_SLOT_unsigned_wRoleType);
  tolua_variable(tolua_S,"wBaseDataType",tolua_get_GM_ROLE_SLOT_unsigned_wBaseDataType,tolua_set_GM_ROLE_SLOT_unsigned_wBaseDataType);
  tolua_variable(tolua_S,"szData",tolua_get_GM_ROLE_SLOT_szData,tolua_set_GM_ROLE_SLOT_szData);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"GM_ROLE_SPELL_SLOT","GM_ROLE_SPELL_SLOT","",NULL);
 tolua_beginmodule(tolua_S,"GM_ROLE_SPELL_SLOT");
  tolua_variable(tolua_S,"nSpellID",tolua_get_GM_ROLE_SPELL_SLOT_nSpellID,tolua_set_GM_ROLE_SPELL_SLOT_nSpellID);
  tolua_variable(tolua_S,"nRuneID",tolua_get_GM_ROLE_SPELL_SLOT_nRuneID,tolua_set_GM_ROLE_SPELL_SLOT_nRuneID);
  tolua_variable(tolua_S,"nEquipedIndex",tolua_get_GM_ROLE_SPELL_SLOT_nEquipedIndex,tolua_set_GM_ROLE_SPELL_SLOT_nEquipedIndex);
  tolua_variable(tolua_S,"szName",tolua_get_GM_ROLE_SPELL_SLOT_szName,tolua_set_GM_ROLE_SPELL_SLOT_szName);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"GM_ROLE_TITLE_SLOT","GM_ROLE_TITLE_SLOT","",NULL);
 tolua_beginmodule(tolua_S,"GM_ROLE_TITLE_SLOT");
  tolua_variable(tolua_S,"nTemplateID",tolua_get_GM_ROLE_TITLE_SLOT_nTemplateID,tolua_set_GM_ROLE_TITLE_SLOT_nTemplateID);
  tolua_variable(tolua_S,"dwExpireTime",tolua_get_GM_ROLE_TITLE_SLOT_unsigned_dwExpireTime,tolua_set_GM_ROLE_TITLE_SLOT_unsigned_dwExpireTime);
  tolua_variable(tolua_S,"szName",tolua_get_GM_ROLE_TITLE_SLOT_szName,tolua_set_GM_ROLE_TITLE_SLOT_szName);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"GM_ROLE_ITEM_SLOT","GM_ROLE_ITEM_SLOT","",NULL);
 tolua_beginmodule(tolua_S,"GM_ROLE_ITEM_SLOT");
  tolua_variable(tolua_S,"dwItemID",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_dwItemID,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_dwItemID);
  tolua_variable(tolua_S,"qwGuid",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_qwGuid,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_qwGuid);
  tolua_variable(tolua_S,"wConSlot",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_wConSlot,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_wConSlot);
  tolua_variable(tolua_S,"wItemSlot",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_wItemSlot,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_wItemSlot);
  tolua_variable(tolua_S,"nType",tolua_get_GM_ROLE_ITEM_SLOT_nType,tolua_set_GM_ROLE_ITEM_SLOT_nType);
  tolua_variable(tolua_S,"nSubType",tolua_get_GM_ROLE_ITEM_SLOT_nSubType,tolua_set_GM_ROLE_ITEM_SLOT_nSubType);
  tolua_variable(tolua_S,"nNum",tolua_get_GM_ROLE_ITEM_SLOT_nNum,tolua_set_GM_ROLE_ITEM_SLOT_nNum);
  tolua_variable(tolua_S,"byBindType",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byBindType,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byBindType);
  tolua_variable(tolua_S,"byIdentified",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byIdentified,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byIdentified);
  tolua_array(tolua_S,"wRandomAttrID",tolua_get_gm_def_GM_ROLE_ITEM_SLOT_wRandomAttrID,tolua_set_gm_def_GM_ROLE_ITEM_SLOT_wRandomAttrID);
  tolua_variable(tolua_S,"dwRoleID",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_dwRoleID,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_dwRoleID);
  tolua_variable(tolua_S,"dwCostMoney",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_dwCostMoney,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_dwCostMoney);
  tolua_variable(tolua_S,"byLuck",tolua_get_GM_ROLE_ITEM_SLOT_byLuck,tolua_set_GM_ROLE_ITEM_SLOT_byLuck);
  tolua_variable(tolua_S,"byLevelupTimes",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTimes,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTimes);
  tolua_variable(tolua_S,"byLevelupPhyPoint",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupPhyPoint,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupPhyPoint);
  tolua_variable(tolua_S,"byLevelupMagPoint",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupMagPoint,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupMagPoint);
  tolua_variable(tolua_S,"byLevelupTaoPoint",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTaoPoint,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTaoPoint);
  tolua_variable(tolua_S,"byLevelupTypeHidden",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTypeHidden,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupTypeHidden);
  tolua_variable(tolua_S,"byLevelupPointHidden",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_byLevelupPointHidden,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_byLevelupPointHidden);
  tolua_array(tolua_S,"wRune",tolua_get_gm_def_GM_ROLE_ITEM_SLOT_wRune,tolua_set_gm_def_GM_ROLE_ITEM_SLOT_wRune);
  tolua_variable(tolua_S,"dwSocketCombination",tolua_get_GM_ROLE_ITEM_SLOT_unsigned_dwSocketCombination,tolua_set_GM_ROLE_ITEM_SLOT_unsigned_dwSocketCombination);
  tolua_array(tolua_S,"nSoulID",tolua_get_gm_def_GM_ROLE_ITEM_SLOT_nSoulID,tolua_set_gm_def_GM_ROLE_ITEM_SLOT_nSoulID);
  tolua_variable(tolua_S,"szData",tolua_get_GM_ROLE_ITEM_SLOT_szData,tolua_set_GM_ROLE_ITEM_SLOT_szData);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"GM_ROLE_MAIL_SLOT","GM_ROLE_MAIL_SLOT","",NULL);
 tolua_beginmodule(tolua_S,"GM_ROLE_MAIL_SLOT");
  tolua_variable(tolua_S,"dwMailID",tolua_get_GM_ROLE_MAIL_SLOT_unsigned_dwMailID,tolua_set_GM_ROLE_MAIL_SLOT_unsigned_dwMailID);
  tolua_variable(tolua_S,"nMailType",tolua_get_GM_ROLE_MAIL_SLOT_nMailType,tolua_set_GM_ROLE_MAIL_SLOT_nMailType);
  tolua_variable(tolua_S,"nAttachType",tolua_get_GM_ROLE_MAIL_SLOT_nAttachType,tolua_set_GM_ROLE_MAIL_SLOT_nAttachType);
  tolua_variable(tolua_S,"nState",tolua_get_GM_ROLE_MAIL_SLOT_nState,tolua_set_GM_ROLE_MAIL_SLOT_nState);
  tolua_variable(tolua_S,"nAttachLocked",tolua_get_GM_ROLE_MAIL_SLOT_nAttachLocked,tolua_set_GM_ROLE_MAIL_SLOT_nAttachLocked);
  tolua_variable(tolua_S,"nItemID",tolua_get_GM_ROLE_MAIL_SLOT_nItemID,tolua_set_GM_ROLE_MAIL_SLOT_nItemID);
  tolua_variable(tolua_S,"nItemCount",tolua_get_GM_ROLE_MAIL_SLOT_nItemCount,tolua_set_GM_ROLE_MAIL_SLOT_nItemCount);
  tolua_variable(tolua_S,"szData",tolua_get_GM_ROLE_MAIL_SLOT_szData,tolua_set_GM_ROLE_MAIL_SLOT_szData);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_gm_def (lua_State* tolua_S) {
 return tolua_gm_def_open(tolua_S);
};
#endif

