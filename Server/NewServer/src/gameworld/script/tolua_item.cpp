/*
** Lua binding: item
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_item_open (lua_State* tolua_S);

#include "item.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"ITEM_DATA");
 tolua_usertype(tolua_S,"Item");
 tolua_usertype(tolua_S,"ItemInfo");
}

/* get function: m_llGuid of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_llGuid
static int tolua_get_ItemInfo_unsigned_m_llGuid(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_llGuid'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_llGuid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_llGuid of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_llGuid
static int tolua_set_ItemInfo_unsigned_m_llGuid(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_llGuid'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_llGuid = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_nTemplateID of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_m_nTemplateID
static int tolua_get_ItemInfo_m_nTemplateID(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nTemplateID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_nTemplateID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_nTemplateID of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_m_nTemplateID
static int tolua_set_ItemInfo_m_nTemplateID(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nTemplateID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_nTemplateID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_byConSlot of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_byConSlot
static int tolua_get_ItemInfo_unsigned_m_byConSlot(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byConSlot'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_byConSlot);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_byConSlot of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_byConSlot
static int tolua_set_ItemInfo_unsigned_m_byConSlot(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byConSlot'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_byConSlot = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_byItemSlot of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_byItemSlot
static int tolua_get_ItemInfo_unsigned_m_byItemSlot(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byItemSlot'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_byItemSlot);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_byItemSlot of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_byItemSlot
static int tolua_set_ItemInfo_unsigned_m_byItemSlot(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byItemSlot'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_byItemSlot = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_nCurDur of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_m_nCurDur
static int tolua_get_ItemInfo_m_nCurDur(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nCurDur'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_nCurDur);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_nCurDur of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_m_nCurDur
static int tolua_set_ItemInfo_m_nCurDur(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nCurDur'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_nCurDur = (( signed short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_nMaxDur of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_m_nMaxDur
static int tolua_get_ItemInfo_m_nMaxDur(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nMaxDur'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_nMaxDur);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_nMaxDur of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_m_nMaxDur
static int tolua_set_ItemInfo_m_nMaxDur(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nMaxDur'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_nMaxDur = (( signed short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_byBindType of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_byBindType
static int tolua_get_ItemInfo_unsigned_m_byBindType(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byBindType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_byBindType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_byBindType of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_byBindType
static int tolua_set_ItemInfo_unsigned_m_byBindType(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byBindType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_byBindType = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_byIdentified of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_byIdentified
static int tolua_get_ItemInfo_unsigned_m_byIdentified(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byIdentified'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_byIdentified);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_byIdentified of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_byIdentified
static int tolua_set_ItemInfo_unsigned_m_byIdentified(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byIdentified'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_byIdentified = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_wRandomAttrID of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_item_ItemInfo_m_wRandomAttrID
static int tolua_get_item_ItemInfo_m_wRandomAttrID(lua_State* tolua_S)
{
 int tolua_index;
  ItemInfo* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ItemInfo*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_RANDOM_ATTR_COUNT)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_wRandomAttrID[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_wRandomAttrID of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_item_ItemInfo_m_wRandomAttrID
static int tolua_set_item_ItemInfo_m_wRandomAttrID(lua_State* tolua_S)
{
 int tolua_index;
  ItemInfo* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ItemInfo*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_RANDOM_ATTR_COUNT)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->m_wRandomAttrID[tolua_index] = (( unsigned short)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_dwRoleID of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_dwRoleID
static int tolua_get_ItemInfo_unsigned_m_dwRoleID(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwRoleID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_dwRoleID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_dwRoleID of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_dwRoleID
static int tolua_set_ItemInfo_unsigned_m_dwRoleID(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwRoleID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_dwCostMoney of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_dwCostMoney
static int tolua_get_ItemInfo_unsigned_m_dwCostMoney(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwCostMoney'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_dwCostMoney);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_dwCostMoney of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_dwCostMoney
static int tolua_set_ItemInfo_unsigned_m_dwCostMoney(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwCostMoney'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_dwCostMoney = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_byLuck of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_m_byLuck
static int tolua_get_ItemInfo_m_byLuck(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLuck'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_byLuck);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_byLuck of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_m_byLuck
static int tolua_set_ItemInfo_m_byLuck(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLuck'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_byLuck = (( signed char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_byLevelupTimes of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_byLevelupTimes
static int tolua_get_ItemInfo_unsigned_m_byLevelupTimes(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLevelupTimes'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_byLevelupTimes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_byLevelupTimes of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_byLevelupTimes
static int tolua_set_ItemInfo_unsigned_m_byLevelupTimes(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLevelupTimes'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_byLevelupTimes = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_byLevelupPhyPoint of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_byLevelupPhyPoint
static int tolua_get_ItemInfo_unsigned_m_byLevelupPhyPoint(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLevelupPhyPoint'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_byLevelupPhyPoint);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_byLevelupPhyPoint of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_byLevelupPhyPoint
static int tolua_set_ItemInfo_unsigned_m_byLevelupPhyPoint(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLevelupPhyPoint'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_byLevelupPhyPoint = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_byLevelupMagPoint of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_byLevelupMagPoint
static int tolua_get_ItemInfo_unsigned_m_byLevelupMagPoint(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLevelupMagPoint'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_byLevelupMagPoint);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_byLevelupMagPoint of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_byLevelupMagPoint
static int tolua_set_ItemInfo_unsigned_m_byLevelupMagPoint(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLevelupMagPoint'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_byLevelupMagPoint = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_byLevelupTaoPoint of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_byLevelupTaoPoint
static int tolua_get_ItemInfo_unsigned_m_byLevelupTaoPoint(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLevelupTaoPoint'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_byLevelupTaoPoint);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_byLevelupTaoPoint of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_byLevelupTaoPoint
static int tolua_set_ItemInfo_unsigned_m_byLevelupTaoPoint(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLevelupTaoPoint'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_byLevelupTaoPoint = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_byLevelupTypeHidden of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_byLevelupTypeHidden
static int tolua_get_ItemInfo_unsigned_m_byLevelupTypeHidden(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLevelupTypeHidden'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_byLevelupTypeHidden);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_byLevelupTypeHidden of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_byLevelupTypeHidden
static int tolua_set_ItemInfo_unsigned_m_byLevelupTypeHidden(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLevelupTypeHidden'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_byLevelupTypeHidden = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_byLevelupPointHidden of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_byLevelupPointHidden
static int tolua_get_ItemInfo_unsigned_m_byLevelupPointHidden(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLevelupPointHidden'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_byLevelupPointHidden);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_byLevelupPointHidden of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_byLevelupPointHidden
static int tolua_set_ItemInfo_unsigned_m_byLevelupPointHidden(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byLevelupPointHidden'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_byLevelupPointHidden = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_wRune of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_item_ItemInfo_m_wRune
static int tolua_get_item_ItemInfo_m_wRune(lua_State* tolua_S)
{
 int tolua_index;
  ItemInfo* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ItemInfo*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_RUNE_COUNT)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_wRune[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_wRune of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_item_ItemInfo_m_wRune
static int tolua_set_item_ItemInfo_m_wRune(lua_State* tolua_S)
{
 int tolua_index;
  ItemInfo* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ItemInfo*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_RUNE_COUNT)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->m_wRune[tolua_index] = (( unsigned short)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_dwSocketCombination of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_ItemInfo_unsigned_m_dwSocketCombination
static int tolua_get_ItemInfo_unsigned_m_dwSocketCombination(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwSocketCombination'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_dwSocketCombination);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_dwSocketCombination of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_ItemInfo_unsigned_m_dwSocketCombination
static int tolua_set_ItemInfo_unsigned_m_dwSocketCombination(lua_State* tolua_S)
{
  ItemInfo* self = (ItemInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwSocketCombination'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_dwSocketCombination = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_nSoulID of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_get_item_ItemInfo_m_nSoulID
static int tolua_get_item_ItemInfo_m_nSoulID(lua_State* tolua_S)
{
 int tolua_index;
  ItemInfo* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ItemInfo*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_SOCKET_COUNT)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_nSoulID[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_nSoulID of class  ItemInfo */
#ifndef TOLUA_DISABLE_tolua_set_item_ItemInfo_m_nSoulID
static int tolua_set_item_ItemInfo_m_nSoulID(lua_State* tolua_S)
{
 int tolua_index;
  ItemInfo* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ItemInfo*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_SOCKET_COUNT)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->m_nSoulID[tolua_index] = (( signed int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_pTemplate of class  Item */
#ifndef TOLUA_DISABLE_tolua_get_Item_m_pTemplate_ptr
static int tolua_get_Item_m_pTemplate_ptr(lua_State* tolua_S)
{
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pTemplate'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->m_pTemplate,"const ITEM_DATA");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_iteminfo of class  Item */
#ifndef TOLUA_DISABLE_tolua_get_Item_m_iteminfo
static int tolua_get_Item_m_iteminfo(lua_State* tolua_S)
{
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_iteminfo'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->m_iteminfo,"ItemInfo");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_iteminfo of class  Item */
#ifndef TOLUA_DISABLE_tolua_set_Item_m_iteminfo
static int tolua_set_Item_m_iteminfo(lua_State* tolua_S)
{
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_iteminfo'",NULL);
 if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ItemInfo",0,&tolua_err)))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_iteminfo = *((ItemInfo*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAttribute of class  Item */
#ifndef TOLUA_DISABLE_tolua_item_Item_SetAttribute00
static int tolua_item_Item_SetAttribute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  signed int index = (( signed int)  tolua_tonumber(tolua_S,2,0));
  unsigned short attrid = (( unsigned short)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAttribute'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetAttribute(index,attrid);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAttribute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSocketColor of class  Item */
#ifndef TOLUA_DISABLE_tolua_item_Item_SetSocketColor00
static int tolua_item_Item_SetSocketColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  signed int index = (( signed int)  tolua_tonumber(tolua_S,2,0));
  unsigned char color = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSocketColor'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetSocketColor(index,color);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSocketColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSoul of class  Item */
#ifndef TOLUA_DISABLE_tolua_item_Item_SetSoul00
static int tolua_item_Item_SetSoul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  signed int index = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int soulid = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSoul'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetSoul(index,soulid);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSoul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_item_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"ItemInfo","ItemInfo","",NULL);
 tolua_beginmodule(tolua_S,"ItemInfo");
  tolua_variable(tolua_S,"m_llGuid",tolua_get_ItemInfo_unsigned_m_llGuid,tolua_set_ItemInfo_unsigned_m_llGuid);
  tolua_variable(tolua_S,"m_nTemplateID",tolua_get_ItemInfo_m_nTemplateID,tolua_set_ItemInfo_m_nTemplateID);
  tolua_variable(tolua_S,"m_byConSlot",tolua_get_ItemInfo_unsigned_m_byConSlot,tolua_set_ItemInfo_unsigned_m_byConSlot);
  tolua_variable(tolua_S,"m_byItemSlot",tolua_get_ItemInfo_unsigned_m_byItemSlot,tolua_set_ItemInfo_unsigned_m_byItemSlot);
  tolua_variable(tolua_S,"m_nCurDur",tolua_get_ItemInfo_m_nCurDur,tolua_set_ItemInfo_m_nCurDur);
  tolua_variable(tolua_S,"m_nMaxDur",tolua_get_ItemInfo_m_nMaxDur,tolua_set_ItemInfo_m_nMaxDur);
  tolua_variable(tolua_S,"m_byBindType",tolua_get_ItemInfo_unsigned_m_byBindType,tolua_set_ItemInfo_unsigned_m_byBindType);
  tolua_variable(tolua_S,"m_byIdentified",tolua_get_ItemInfo_unsigned_m_byIdentified,tolua_set_ItemInfo_unsigned_m_byIdentified);
  tolua_array(tolua_S,"m_wRandomAttrID",tolua_get_item_ItemInfo_m_wRandomAttrID,tolua_set_item_ItemInfo_m_wRandomAttrID);
  tolua_variable(tolua_S,"m_dwRoleID",tolua_get_ItemInfo_unsigned_m_dwRoleID,tolua_set_ItemInfo_unsigned_m_dwRoleID);
  tolua_variable(tolua_S,"m_dwCostMoney",tolua_get_ItemInfo_unsigned_m_dwCostMoney,tolua_set_ItemInfo_unsigned_m_dwCostMoney);
  tolua_variable(tolua_S,"m_byLuck",tolua_get_ItemInfo_m_byLuck,tolua_set_ItemInfo_m_byLuck);
  tolua_variable(tolua_S,"m_byLevelupTimes",tolua_get_ItemInfo_unsigned_m_byLevelupTimes,tolua_set_ItemInfo_unsigned_m_byLevelupTimes);
  tolua_variable(tolua_S,"m_byLevelupPhyPoint",tolua_get_ItemInfo_unsigned_m_byLevelupPhyPoint,tolua_set_ItemInfo_unsigned_m_byLevelupPhyPoint);
  tolua_variable(tolua_S,"m_byLevelupMagPoint",tolua_get_ItemInfo_unsigned_m_byLevelupMagPoint,tolua_set_ItemInfo_unsigned_m_byLevelupMagPoint);
  tolua_variable(tolua_S,"m_byLevelupTaoPoint",tolua_get_ItemInfo_unsigned_m_byLevelupTaoPoint,tolua_set_ItemInfo_unsigned_m_byLevelupTaoPoint);
  tolua_variable(tolua_S,"m_byLevelupTypeHidden",tolua_get_ItemInfo_unsigned_m_byLevelupTypeHidden,tolua_set_ItemInfo_unsigned_m_byLevelupTypeHidden);
  tolua_variable(tolua_S,"m_byLevelupPointHidden",tolua_get_ItemInfo_unsigned_m_byLevelupPointHidden,tolua_set_ItemInfo_unsigned_m_byLevelupPointHidden);
  tolua_array(tolua_S,"m_wRune",tolua_get_item_ItemInfo_m_wRune,tolua_set_item_ItemInfo_m_wRune);
  tolua_variable(tolua_S,"m_dwSocketCombination",tolua_get_ItemInfo_unsigned_m_dwSocketCombination,tolua_set_ItemInfo_unsigned_m_dwSocketCombination);
  tolua_array(tolua_S,"m_nSoulID",tolua_get_item_ItemInfo_m_nSoulID,tolua_set_item_ItemInfo_m_nSoulID);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Item","Item","",NULL);
 tolua_beginmodule(tolua_S,"Item");
  tolua_variable(tolua_S,"m_pTemplate",tolua_get_Item_m_pTemplate_ptr,NULL);
  tolua_variable(tolua_S,"m_iteminfo",tolua_get_Item_m_iteminfo,tolua_set_Item_m_iteminfo);
#ifndef TOLUA_DISABLE_tolua_item_Item_SetAttribute00
  tolua_function(tolua_S,"SetAttribute",tolua_item_Item_SetAttribute00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_Item_SetSocketColor00
  tolua_function(tolua_S,"SetSocketColor",tolua_item_Item_SetSocketColor00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_Item_SetSoul00
  tolua_function(tolua_S,"SetSoul",tolua_item_Item_SetSoul00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_item (lua_State* tolua_S) {
 return tolua_item_open(tolua_S);
};
#endif

