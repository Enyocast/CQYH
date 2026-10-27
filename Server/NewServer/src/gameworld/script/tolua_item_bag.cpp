/*
** Lua binding: item_bag
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_item_bag_open (lua_State* tolua_S);

#include "../../../Common/define/item_def.h"
#include "item_bag.h"
#include "item_mgr.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CItemBag");
 tolua_usertype(tolua_S,"Item");
 tolua_usertype(tolua_S,"CItemMgr");
 tolua_usertype(tolua_S,"ITEM_DATA");
 tolua_usertype(tolua_S,"DROP_CHANCE_DATA");
}

/* function: IsAppearance */
#ifndef TOLUA_DISABLE_tolua_item_bag_IsAppearance00
static int tolua_item_bag_IsAppearance00(lua_State* tolua_S)
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
  unsigned short conslot = (( unsigned short)  tolua_tonumber(tolua_S,1,0));
  unsigned short itemslot = (( unsigned short)  tolua_tonumber(tolua_S,2,0));
 {
 int tolua_ret = (int)
IsAppearance(conslot,itemslot);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAppearance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nDropGroupID of class  DROP_CHANCE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_DROP_CHANCE_DATA_nDropGroupID
static int tolua_get_DROP_CHANCE_DATA_nDropGroupID(lua_State* tolua_S)
{
  DROP_CHANCE_DATA* self = (DROP_CHANCE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nDropGroupID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nDropGroupID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nDropGroupID of class  DROP_CHANCE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_DROP_CHANCE_DATA_nDropGroupID
static int tolua_set_DROP_CHANCE_DATA_nDropGroupID(lua_State* tolua_S)
{
  DROP_CHANCE_DATA* self = (DROP_CHANCE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nDropGroupID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nDropGroupID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nDropChance of class  DROP_CHANCE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_DROP_CHANCE_DATA_nDropChance
static int tolua_get_DROP_CHANCE_DATA_nDropChance(lua_State* tolua_S)
{
  DROP_CHANCE_DATA* self = (DROP_CHANCE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nDropChance'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nDropChance);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nDropChance of class  DROP_CHANCE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_DROP_CHANCE_DATA_nDropChance
static int tolua_set_DROP_CHANCE_DATA_nDropChance(lua_State* tolua_S)
{
  DROP_CHANCE_DATA* self = (DROP_CHANCE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nDropChance'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nDropChance = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddItem of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_AddItem00
static int tolua_item_bag_CItemBag_AddItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int itemid = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int itemcount = (( signed int)  tolua_tonumber(tolua_S,3,0));
  EItemLog reason = ((EItemLog) (int)  tolua_tonumber(tolua_S,4,0));
  unsigned int userdefine = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
   bool forcebinded = ((  bool)  tolua_toboolean(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddItem'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->AddItem(itemid,itemcount,reason,userdefine,forcebinded);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddItem of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_AddItem01
static int tolua_item_bag_CItemBag_AddItem01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Item",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  Item* item = ((Item*)  tolua_tousertype(tolua_S,2,0));
  EItemLog reason = ((EItemLog) (int)  tolua_tonumber(tolua_S,3,0));
  unsigned int userdefine = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddItem'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->AddItem(item,reason,userdefine);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_item_bag_CItemBag_AddItem00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: UseItem of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_UseItem00
static int tolua_item_bag_CItemBag_UseItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char conslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char itemslot = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UseItem'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->UseItem(conslot,itemslot);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UseItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MoveItem of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_MoveItem00
static int tolua_item_bag_CItemBag_MoveItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char srcconslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char srcitemslot = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
  unsigned char dstconslot = (( unsigned char)  tolua_tonumber(tolua_S,4,0));
  unsigned char dstitemslot = (( unsigned char)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MoveItem'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->MoveItem(srcconslot,srcitemslot,dstconslot,dstitemslot);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MoveItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SplitItem of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SplitItem00
static int tolua_item_bag_CItemBag_SplitItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char srcconslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char srcitemslot = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
  unsigned char dstconslot = (( unsigned char)  tolua_tonumber(tolua_S,4,0));
  unsigned char dstitemslot = (( unsigned char)  tolua_tonumber(tolua_S,5,0));
  signed short itemcount = (( signed short)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SplitItem'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->SplitItem(srcconslot,srcitemslot,dstconslot,dstitemslot,itemcount);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SplitItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DeleteItemPos of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_DeleteItemPos00
static int tolua_item_bag_CItemBag_DeleteItemPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char conslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char itemslot = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
  signed short itemcount = (( signed short)  tolua_tonumber(tolua_S,4,0));
  EItemLog reason = ((EItemLog) (int)  tolua_tonumber(tolua_S,5,0));
  unsigned int qwUserDefinedID = (( unsigned int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DeleteItemPos'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->DeleteItemPos(conslot,itemslot,itemcount,reason,qwUserDefinedID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DeleteItemPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItemCount of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetItemCount00
static int tolua_item_bag_CItemBag_GetItemCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int itemid = (( signed int)  tolua_tonumber(tolua_S,2,0));
   bool includebank = ((  bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItemCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetItemCount(itemid,includebank);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItemCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DeleteItemId of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_DeleteItemId00
static int tolua_item_bag_CItemBag_DeleteItemId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int itemid = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed short itemcount = (( signed short)  tolua_tonumber(tolua_S,3,0));
  EItemLog reason = ((EItemLog) (int)  tolua_tonumber(tolua_S,4,0));
   bool includebank = ((  bool)  tolua_toboolean(tolua_S,5,0));
  unsigned int qwUserDefinedID = (( unsigned int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DeleteItemId'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->DeleteItemId(itemid,itemcount,reason,includebank,qwUserDefinedID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DeleteItemId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFreeSlots of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetFreeSlots00
static int tolua_item_bag_CItemBag_GetFreeSlots00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char conslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFreeSlots'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetFreeSlots(conslot);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFreeSlots'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IdentifyItem of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_IdentifyItem00
static int tolua_item_bag_CItemBag_IdentifyItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char conslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char itemslot = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IdentifyItem'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->IdentifyItem(conslot,itemslot);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IdentifyItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Refine of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_Refine00
static int tolua_item_bag_CItemBag_Refine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char refineslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char addequip = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
  unsigned char conslot = (( unsigned char)  tolua_tonumber(tolua_S,4,0));
  unsigned char itemslot = (( unsigned char)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Refine'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->Refine(refineslot,addequip,conslot,itemslot);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Refine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRefineLevel of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SetRefineLevel00
static int tolua_item_bag_CItemBag_SetRefineLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char refineslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned short level = (( unsigned short)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRefineLevel'", NULL);
#endif
 {
  self->SetRefineLevel(refineslot,level);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRefineLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RandomizeItem of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_RandomizeItem00
static int tolua_item_bag_CItemBag_RandomizeItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char conslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char itemslot = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RandomizeItem'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->RandomizeItem(conslot,itemslot);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RandomizeItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSoul of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_AddSoul00
static int tolua_item_bag_CItemBag_AddSoul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char equipconslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char equipitemslot = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
  unsigned char socketindex = (( unsigned char)  tolua_tonumber(tolua_S,4,0));
  unsigned char soulconslot = (( unsigned char)  tolua_tonumber(tolua_S,5,0));
  unsigned char soulitemslot = (( unsigned char)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSoul'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->AddSoul(equipconslot,equipitemslot,socketindex,soulconslot,soulitemslot);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSoul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItem of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetItem00
static int tolua_item_bag_CItemBag_GetItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char conslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char itemslot = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItem'", NULL);
#endif
 {
  Item* tolua_ret = (Item*)  self->GetItem(conslot,itemslot);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"Item");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoseWeaponDur of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_LoseWeaponDur00
static int tolua_item_bag_CItemBag_LoseWeaponDur00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoseWeaponDur'", NULL);
#endif
 {
  self->LoseWeaponDur();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoseWeaponDur'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoseArmorDur of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_LoseArmorDur00
static int tolua_item_bag_CItemBag_LoseArmorDur00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int damage = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoseArmorDur'", NULL);
#endif
 {
  self->LoseArmorDur(damage);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoseArmorDur'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BuySlots of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_BuySlots00
static int tolua_item_bag_CItemBag_BuySlots00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char conslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char slotcount = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BuySlots'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->BuySlots(conslot,slotcount);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BuySlots'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EquipItemOnBirth of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_EquipItemOnBirth00
static int tolua_item_bag_CItemBag_EquipItemOnBirth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int itemid = (( signed int)  tolua_tonumber(tolua_S,2,0));
  unsigned char itemslot = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EquipItemOnBirth'", NULL);
#endif
 {
 int tolua_ret = (int)
self->EquipItemOnBirth(itemid,itemslot);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EquipItemOnBirth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EquipHeroItemOnBirth of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_EquipHeroItemOnBirth00
static int tolua_item_bag_CItemBag_EquipHeroItemOnBirth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int itemid = (( signed int)  tolua_tonumber(tolua_S,2,0));
  unsigned char itemslot = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EquipHeroItemOnBirth'", NULL);
#endif
 {
 int tolua_ret = (int)
self->EquipHeroItemOnBirth(itemid,itemslot);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EquipHeroItemOnBirth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMoney of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetMoney00
static int tolua_item_bag_CItemBag_GetMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CItemBag* self = (const CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int moneytype = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMoney'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMoney(moneytype);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddMoney of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_AddMoney00
static int tolua_item_bag_CItemBag_AddMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int moneytype = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nCount = (( signed int)  tolua_tonumber(tolua_S,3,0));
  EMoneyLog reason = ((EMoneyLog) (int)  tolua_tonumber(tolua_S,4,0));
  unsigned int dwSourceID = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddMoney'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->AddMoney(moneytype,nCount,reason,dwSourceID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SubMoney of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SubMoney00
static int tolua_item_bag_CItemBag_SubMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int moneytype = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nCount = (( signed int)  tolua_tonumber(tolua_S,3,0));
  EMoneyLog reason = ((EMoneyLog) (int)  tolua_tonumber(tolua_S,4,0));
  unsigned int dwTargetID = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SubMoney'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->SubMoney(moneytype,nCount,reason,dwTargetID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SubMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMoney of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SetMoney00
static int tolua_item_bag_CItemBag_SetMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int moneytype = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nCount = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMoney'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->SetMoney(moneytype,nCount);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGoldPool of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetGoldPool00
static int tolua_item_bag_CItemBag_GetGoldPool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CItemBag",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CItemBag* self = (const CItemBag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGoldPool'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetGoldPool();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGoldPool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChanceByGoldPool of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetChanceByGoldPool00
static int tolua_item_bag_CItemBag_GetChanceByGoldPool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CItemBag",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CItemBag* self = (const CItemBag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChanceByGoldPool'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetChanceByGoldPool();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChanceByGoldPool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUseMoneytype01Only of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SetUseMoneytype01Only00
static int tolua_item_bag_CItemBag_SetUseMoneytype01Only00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char use = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUseMoneytype01Only'", NULL);
#endif
 {
  self->SetUseMoneytype01Only(use);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUseMoneytype01Only'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUseMoneytype01Only of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetUseMoneytype01Only00
static int tolua_item_bag_CItemBag_GetUseMoneytype01Only00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const CItemBag",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const CItemBag* self = (const CItemBag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUseMoneytype01Only'", NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->GetUseMoneytype01Only();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUseMoneytype01Only'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWeaponType of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetWeaponType00
static int tolua_item_bag_CItemBag_GetWeaponType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWeaponType'", NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->GetWeaponType();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWeaponType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeroWeaponType of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetHeroWeaponType00
static int tolua_item_bag_CItemBag_GetHeroWeaponType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeroWeaponType'", NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->GetHeroWeaponType();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeroWeaponType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Begin of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_Begin00
static int tolua_item_bag_CItemBag_Begin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char conslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Begin'", NULL);
#endif
 {
  self->Begin(conslot);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Begin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Next of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_Next00
static int tolua_item_bag_CItemBag_Next00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  unsigned char conslot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Next'", NULL);
#endif
 {
  const Item* tolua_ret = (const Item*)  self->Next(conslot);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"const Item");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Next'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWeaponLuck of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SetWeaponLuck00
static int tolua_item_bag_CItemBag_SetWeaponLuck00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed char v = (( signed char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWeaponLuck'", NULL);
#endif
 {
  self->SetWeaponLuck(v);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWeaponLuck'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IncreaseWeaponLuck of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_IncreaseWeaponLuck00
static int tolua_item_bag_CItemBag_IncreaseWeaponLuck00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed char v = (( signed char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IncreaseWeaponLuck'", NULL);
#endif
 {
  self->IncreaseWeaponLuck(v);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IncreaseWeaponLuck'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DecreaseWeaponLuck of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_DecreaseWeaponLuck00
static int tolua_item_bag_CItemBag_DecreaseWeaponLuck00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DecreaseWeaponLuck'", NULL);
#endif
 {
  self->DecreaseWeaponLuck();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DecreaseWeaponLuck'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RuneTest of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_RuneTest00
static int tolua_item_bag_CItemBag_RuneTest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int nRuneID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RuneTest'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->RuneTest(nRuneID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RuneTest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EquipAddSocket of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_EquipAddSocket00
static int tolua_item_bag_CItemBag_EquipAddSocket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EquipAddSocket'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->EquipAddSocket(nIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EquipAddSocket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSocketColor of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SetSocketColor00
static int tolua_item_bag_CItemBag_SetSocketColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nColor = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSocketColor'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->SetSocketColor(nIndex,nColor);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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

/* method: AddDestinyWeapon of class  CItemBag */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_AddDestinyWeapon00
static int tolua_item_bag_CItemBag_AddDestinyWeapon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemBag",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemBag* self = (CItemBag*)  tolua_tousertype(tolua_S,1,0);
  signed int nItemID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nLevel = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddDestinyWeapon'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->AddDestinyWeapon(nItemID,nLevel);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddDestinyWeapon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstance of class  CItemMgr */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemMgr_GetInstance00
static int tolua_item_bag_CItemMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CItemMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CItemMgr& tolua_ret = (CItemMgr&)  CItemMgr::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CItemMgr");
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

/* method: GenerateItem of class  CItemMgr */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemMgr_GenerateItem00
static int tolua_item_bag_CItemMgr_GenerateItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemMgr* self = (CItemMgr*)  tolua_tousertype(tolua_S,1,0);
  signed int nTemplateID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nItemCount = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GenerateItem'", NULL);
#endif
 {
  Item* tolua_ret = (Item*)  self->GenerateItem(nTemplateID,nItemCount);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"Item");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GenerateItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GenerateItem of class  CItemMgr */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemMgr_GenerateItem01
static int tolua_item_bag_CItemMgr_GenerateItem01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemMgr",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const ITEM_DATA",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CItemMgr* self = (CItemMgr*)  tolua_tousertype(tolua_S,1,0);
  const ITEM_DATA* itemdata = ((const ITEM_DATA*)  tolua_tousertype(tolua_S,2,0));
  signed int nItemCount = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GenerateItem'", NULL);
#endif
 {
  Item* tolua_ret = (Item*)  self->GenerateItem(itemdata,nItemCount);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"Item");
 }
 }
 return 1;
tolua_lerror:
 return tolua_item_bag_CItemMgr_GenerateItem00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: DestroyItem of class  CItemMgr */
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemMgr_DestroyItem00
static int tolua_item_bag_CItemMgr_DestroyItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CItemMgr",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Item",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CItemMgr* self = (CItemMgr*)  tolua_tousertype(tolua_S,1,0);
  Item* item = ((Item*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DestroyItem'", NULL);
#endif
 {
 int tolua_ret = (int)
self->DestroyItem(item);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DestroyItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_item_bag_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_ITEM_COUNT",MAX_ITEM_COUNT);
 tolua_constant(tolua_S,"MAX_DROP_COUNT",MAX_DROP_COUNT);
 tolua_constant(tolua_S,"MAX_REFINE_LEVEL",MAX_REFINE_LEVEL);
  tolua_constant(tolua_S,"ITEMLOG_INVALID",ITEMLOG_INVALID);
  tolua_constant(tolua_S,"ITEMLOG_SHOP",ITEMLOG_SHOP);
  tolua_constant(tolua_S,"ITEMLOG_LOOT",ITEMLOG_LOOT);
  tolua_constant(tolua_S,"ITEMLOG_GM_COMMAND",ITEMLOG_GM_COMMAND);
  tolua_constant(tolua_S,"ITEMLOG_QUEST_PREPAY",ITEMLOG_QUEST_PREPAY);
  tolua_constant(tolua_S,"ITEMLOG_QUEST_REWARD",ITEMLOG_QUEST_REWARD);
  tolua_constant(tolua_S,"ITEMLOG_DUNGEON_REWARD",ITEMLOG_DUNGEON_REWARD);
  tolua_constant(tolua_S,"ITEMLOG_PLAYER_STALL",ITEMLOG_PLAYER_STALL);
  tolua_constant(tolua_S,"ITEMLOG_PLAYER_TRADE",ITEMLOG_PLAYER_TRADE);
  tolua_constant(tolua_S,"ITEMLOG_BUY_BACK",ITEMLOG_BUY_BACK);
  tolua_constant(tolua_S,"ITEMLOG_CREATE_ROLE",ITEMLOG_CREATE_ROLE);
  tolua_constant(tolua_S,"ITEMLOG_CREATE_HERO",ITEMLOG_CREATE_HERO);
  tolua_constant(tolua_S,"ITEMLOG_SCRIPT",ITEMLOG_SCRIPT);
  tolua_constant(tolua_S,"ITEMLOG_GET_MAIL_ATTACH",ITEMLOG_GET_MAIL_ATTACH);
  tolua_constant(tolua_S,"ITEMLOG_GUILD_STORAGE",ITEMLOG_GUILD_STORAGE);
  tolua_constant(tolua_S,"ITEMLOG_GUILD_DESTORY",ITEMLOG_GUILD_DESTORY);
  tolua_constant(tolua_S,"ITEMLOG_ACHIEVEMENT_REWARD",ITEMLOG_ACHIEVEMENT_REWARD);
  tolua_constant(tolua_S,"ITEMLOG_UPGRADE_SOUL",ITEMLOG_UPGRADE_SOUL);
  tolua_constant(tolua_S,"ITEMLOG_REMOVE_SOUL",ITEMLOG_REMOVE_SOUL);
  tolua_constant(tolua_S,"ITEMLOG_NPC_DROP",ITEMLOG_NPC_DROP);
  tolua_constant(tolua_S,"ITEMLOG_USER_REQUEST",ITEMLOG_USER_REQUEST);
  tolua_constant(tolua_S,"ITEMLOG_SELL",ITEMLOG_SELL);
  tolua_constant(tolua_S,"ITEMLOG_CAST_SPELL",ITEMLOG_CAST_SPELL);
  tolua_constant(tolua_S,"ITEMLOG_REFINE_ITEM",ITEMLOG_REFINE_ITEM);
  tolua_constant(tolua_S,"ITEMLOG_COMPLETE_QUEST",ITEMLOG_COMPLETE_QUEST);
  tolua_constant(tolua_S,"ITEMLOG_CREATE_GUILD",ITEMLOG_CREATE_GUILD);
  tolua_constant(tolua_S,"ITEMLOG_USE_ITEM",ITEMLOG_USE_ITEM);
  tolua_constant(tolua_S,"ITEMLOG_INSERT_SOUL",ITEMLOG_INSERT_SOUL);
  tolua_constant(tolua_S,"ITEMLOG_AUCTION_SELL",ITEMLOG_AUCTION_SELL);
  tolua_constant(tolua_S,"ITEMLOG_RUNE",ITEMLOG_RUNE);
  tolua_constant(tolua_S,"ITEMLOG_DECOMPOSE",ITEMLOG_DECOMPOSE);
  tolua_constant(tolua_S,"ITEMLOG_COMPOSE",ITEMLOG_COMPOSE);
  tolua_constant(tolua_S,"ITEMLOG_ACTIVITY_REWARD",ITEMLOG_ACTIVITY_REWARD);
  tolua_constant(tolua_S,"ITEMLOG_REVIVE",ITEMLOG_REVIVE);
  tolua_constant(tolua_S,"ITEMLOG_GM",ITEMLOG_GM);
  tolua_constant(tolua_S,"ITEMLOG_OPEN_DOODAD",ITEMLOG_OPEN_DOODAD);
  tolua_constant(tolua_S,"ITEMLOG_REAL_MONEY_SHOP",ITEMLOG_REAL_MONEY_SHOP);
  tolua_constant(tolua_S,"ITEMLOG_TEAM_AUCTION",ITEMLOG_TEAM_AUCTION);
  tolua_constant(tolua_S,"ITEMLOG_TEAM_AUCTION_FAILED",ITEMLOG_TEAM_AUCTION_FAILED);
  tolua_constant(tolua_S,"ITEMLOG_QUEST_RECYCLE",ITEMLOG_QUEST_RECYCLE);
  tolua_constant(tolua_S,"ITEMLOG_EXCHANGE",ITEMLOG_EXCHANGE);
  tolua_constant(tolua_S,"ITEMLOG_ARENA_COMMON_REWARD",ITEMLOG_ARENA_COMMON_REWARD);
  tolua_constant(tolua_S,"ITEMLOG_SABAC_AWARD",ITEMLOG_SABAC_AWARD);
  tolua_constant(tolua_S,"ITEMLOG_REPUTATION_AWARD",ITEMLOG_REPUTATION_AWARD);
  tolua_constant(tolua_S,"ITEMLOG_SPLIT",ITEMLOG_SPLIT);
  tolua_constant(tolua_S,"ITEMLOG_MOVE",ITEMLOG_MOVE);
  tolua_constant(tolua_S,"ITEMLOG_ORGANIZE_BAG",ITEMLOG_ORGANIZE_BAG);
  tolua_constant(tolua_S,"ITEMLOG_EQUIP_LEVELUP",ITEMLOG_EQUIP_LEVELUP);
  tolua_constant(tolua_S,"ITEMLOG_EQUIP_LEVELUP_FAILED",ITEMLOG_EQUIP_LEVELUP_FAILED);
  tolua_constant(tolua_S,"ITEMLOG_EQUIP_LEVELUP_SUCCEEDED",ITEMLOG_EQUIP_LEVELUP_SUCCEEDED);
  tolua_constant(tolua_S,"ITEMLOG_RECOVER_USED_UP",ITEMLOG_RECOVER_USED_UP);
  tolua_constant(tolua_S,"ITEMLOG_MINE",ITEMLOG_MINE);
  tolua_constant(tolua_S,"ITEMLOG_ENROLL_SABAC",ITEMLOG_ENROLL_SABAC);
  tolua_constant(tolua_S,"ITEMLOG_DEATH",ITEMLOG_DEATH);
  tolua_constant(tolua_S,"ITEMLOG_SPELL",ITEMLOG_SPELL);
  tolua_constant(tolua_S,"ITEMLOG_ATTACK",ITEMLOG_ATTACK);
  tolua_constant(tolua_S,"ITEMLOG_ATTACKED",ITEMLOG_ATTACKED);
  tolua_constant(tolua_S,"ITEMLOG_TRUMPET",ITEMLOG_TRUMPET);
  tolua_constant(tolua_S,"ITEMLOG_CHECKIN_AWARD",ITEMLOG_CHECKIN_AWARD);
  tolua_constant(tolua_S,"ITEMLOG_AWARD",ITEMLOG_AWARD);
  tolua_constant(tolua_S,"ITEMLOG_BLACK_MARKET",ITEMLOG_BLACK_MARKET);
  tolua_constant(tolua_S,"ITEMLOG_MATERIAL",ITEMLOG_MATERIAL);
  tolua_constant(tolua_S,"ITEMLOG_GAMBLE",ITEMLOG_GAMBLE);
  tolua_constant(tolua_S,"ITEMLOG_PACKAGE",ITEMLOG_PACKAGE);
  tolua_constant(tolua_S,"ITEMLOG_IDENTIFY",ITEMLOG_IDENTIFY);
  tolua_constant(tolua_S,"ITEMLOG_RANDOMIZE",ITEMLOG_RANDOMIZE);
  tolua_constant(tolua_S,"ITEMLOG_LUCK_OIL",ITEMLOG_LUCK_OIL);
  tolua_constant(tolua_S,"ITEMLOG_SIGN",ITEMLOG_SIGN);
  tolua_constant(tolua_S,"ITEMLOG_STORAGE_ROLLBACK",ITEMLOG_STORAGE_ROLLBACK);
  tolua_constant(tolua_S,"ITEMLOG_SPELL_BOOK_GAMBLE",ITEMLOG_SPELL_BOOK_GAMBLE);
  tolua_constant(tolua_S,"ITEMLOG_GM_FIX_ROLE",ITEMLOG_GM_FIX_ROLE);
  tolua_constant(tolua_S,"ITEMLOG_RUNE_ADVANCE_CONFIRM",ITEMLOG_RUNE_ADVANCE_CONFIRM);
  tolua_constant(tolua_S,"ITEMLOG_POTION_GAMBLE",ITEMLOG_POTION_GAMBLE);
  tolua_constant(tolua_S,"ITEMLOG_SELL_RESOURCE_ITEM",ITEMLOG_SELL_RESOURCE_ITEM);
  tolua_constant(tolua_S,"ITEMLOG_EQUIP_ADD_SOCKET",ITEMLOG_EQUIP_ADD_SOCKET);
  tolua_constant(tolua_S,"ITEMLOG_EQUIP_SET_COLOR",ITEMLOG_EQUIP_SET_COLOR);
  tolua_constant(tolua_S,"ITEMLOG_CHANGE_EUIQP_SOCKET_COLOR",ITEMLOG_CHANGE_EUIQP_SOCKET_COLOR);
  tolua_constant(tolua_S,"ITEMLOG_ADD_DESTINY_WEAPON",ITEMLOG_ADD_DESTINY_WEAPON);
  tolua_constant(tolua_S,"ITEMLOG_TOTAL",ITEMLOG_TOTAL);
  tolua_constant(tolua_S,"MONEYLOG_INVALID",MONEYLOG_INVALID);
  tolua_constant(tolua_S,"MONEYLOG_BUY_ITEM",MONEYLOG_BUY_ITEM);
  tolua_constant(tolua_S,"MONEYLOG_REPAIR",MONEYLOG_REPAIR);
  tolua_constant(tolua_S,"MONEYLOG_PLAYER_STALL",MONEYLOG_PLAYER_STALL);
  tolua_constant(tolua_S,"MONEYLOG_PLAYER_STALL_TAX",MONEYLOG_PLAYER_STALL_TAX);
  tolua_constant(tolua_S,"MONEYLOG_PLAYER_TRADE",MONEYLOG_PLAYER_TRADE);
  tolua_constant(tolua_S,"MONEYLOG_PLAYER_TRADE_TAX",MONEYLOG_PLAYER_TRADE_TAX);
  tolua_constant(tolua_S,"MONEYLOG_BUY_BACK",MONEYLOG_BUY_BACK);
  tolua_constant(tolua_S,"MONEYLOG_REFINE_ITEM",MONEYLOG_REFINE_ITEM);
  tolua_constant(tolua_S,"MONEYLOG_BUY_SLOTS",MONEYLOG_BUY_SLOTS);
  tolua_constant(tolua_S,"MONEYLOG_REMOVE_SOUL",MONEYLOG_REMOVE_SOUL);
  tolua_constant(tolua_S,"MONEYLOG_CREATE_GUILD",MONEYLOG_CREATE_GUILD);
  tolua_constant(tolua_S,"MONEYLOG_GUILD_CONTRIBUTE",MONEYLOG_GUILD_CONTRIBUTE);
  tolua_constant(tolua_S,"MONEYLOG_GUILD_POP_ITEM",MONEYLOG_GUILD_POP_ITEM);
  tolua_constant(tolua_S,"MOMEYLOG_GUILD_ENTER_DUNGEON",MOMEYLOG_GUILD_ENTER_DUNGEON);
  tolua_constant(tolua_S,"MONEYLOG_TELEPORT_PLATFORM",MONEYLOG_TELEPORT_PLATFORM);
  tolua_constant(tolua_S,"MONEYLOG_DUNGEON_SELECT_REWARD",MONEYLOG_DUNGEON_SELECT_REWARD);
  tolua_constant(tolua_S,"MONEYLOG_CAST_SPELL",MONEYLOG_CAST_SPELL);
  tolua_constant(tolua_S,"MONEYLOG_MAIL_COST",MONEYLOG_MAIL_COST);
  tolua_constant(tolua_S,"MONEYLOG_LOOT",MONEYLOG_LOOT);
  tolua_constant(tolua_S,"MONEYLOG_SELL_ITEM",MONEYLOG_SELL_ITEM);
  tolua_constant(tolua_S,"MONEYLOG_QUEST_PREPAY",MONEYLOG_QUEST_PREPAY);
  tolua_constant(tolua_S,"MONEYLOG_QUEST_REWARD",MONEYLOG_QUEST_REWARD);
  tolua_constant(tolua_S,"MONEYLOG_QUEST_COST",MONEYLOG_QUEST_COST);
  tolua_constant(tolua_S,"MONEYLOG_GUILD_SALARY",MONEYLOG_GUILD_SALARY);
  tolua_constant(tolua_S,"MONEYLOG_DUNGEON_REWARD",MONEYLOG_DUNGEON_REWARD);
  tolua_constant(tolua_S,"MONEYLOG_GM_COMMAND",MONEYLOG_GM_COMMAND);
  tolua_constant(tolua_S,"MONEYLOG_SCRIPT",MONEYLOG_SCRIPT);
  tolua_constant(tolua_S,"MONEYLOG_IDENTIFY_ITEM",MONEYLOG_IDENTIFY_ITEM);
  tolua_constant(tolua_S,"MONEYLOG_RANDOMIZE_ITEM",MONEYLOG_RANDOMIZE_ITEM);
  tolua_constant(tolua_S,"MONEYLOG_QUEST_FLY_COST",MONEYLOG_QUEST_FLY_COST);
  tolua_constant(tolua_S,"MONEYLOG_SIGN_ITEM_COST",MONEYLOG_SIGN_ITEM_COST);
  tolua_constant(tolua_S,"MONEYLOG_AUCTION_SELL_COST",MONEYLOG_AUCTION_SELL_COST);
  tolua_constant(tolua_S,"MONEYLOG_AUCTION_DEPOSIT_COST",MONEYLOG_AUCTION_DEPOSIT_COST);
  tolua_constant(tolua_S,"MONEYLOG_AUCTION_LEFT_MONEY",MONEYLOG_AUCTION_LEFT_MONEY);
  tolua_constant(tolua_S,"MONEYLOG_CHANGE_WEATHER",MONEYLOG_CHANGE_WEATHER);
  tolua_constant(tolua_S,"MONEYLOG_BUY_VIP",MONEYLOG_BUY_VIP);
  tolua_constant(tolua_S,"MONEYLOG_DAILY_QUEST_BUY_COMPLETE_TIME",MONEYLOG_DAILY_QUEST_BUY_COMPLETE_TIME);
  tolua_constant(tolua_S,"MONEYLOG_DAILY_QUEST_BUY_ONESHOT",MONEYLOG_DAILY_QUEST_BUY_ONESHOT);
  tolua_constant(tolua_S,"MONEYLOG_OPEN_GUILD_DUNGEON",MONEYLOG_OPEN_GUILD_DUNGEON);
  tolua_constant(tolua_S,"MONEYLOG_GUILD_DECLARE_WAR",MONEYLOG_GUILD_DECLARE_WAR);
  tolua_constant(tolua_S,"MONEYLOG_DECOMPOSE",MONEYLOG_DECOMPOSE);
  tolua_constant(tolua_S,"MONEYLOG_COMPOSE",MONEYLOG_COMPOSE);
  tolua_constant(tolua_S,"MONEYLOG_SPIRIT_EXP2PTS",MONEYLOG_SPIRIT_EXP2PTS);
  tolua_constant(tolua_S,"MONEYLOG_SPIRIT_ADDAIR",MONEYLOG_SPIRIT_ADDAIR);
  tolua_constant(tolua_S,"MONEYLOG_SPIRIT_BUYSLOT",MONEYLOG_SPIRIT_BUYSLOT);
  tolua_constant(tolua_S,"MONEYLOG_SPIRIT_BUYEXCHANGEAIR",MONEYLOG_SPIRIT_BUYEXCHANGEAIR);
  tolua_constant(tolua_S,"MONEYLOG_SPIRIT_BLOOD",MONEYLOG_SPIRIT_BLOOD);
  tolua_constant(tolua_S,"MONEYLOG_REVIVE",MONEYLOG_REVIVE);
  tolua_constant(tolua_S,"MONEYLOG_CREATE_ARENA_TEAM",MONEYLOG_CREATE_ARENA_TEAM);
  tolua_constant(tolua_S,"MONEYLOG_GUILD_BUY_AURA",MONEYLOG_GUILD_BUY_AURA);
  tolua_constant(tolua_S,"MONEYLOG_GET_MAIL_ATTACH",MONEYLOG_GET_MAIL_ATTACH);
  tolua_constant(tolua_S,"MONEYLOG_GM",MONEYLOG_GM);
  tolua_constant(tolua_S,"MONEYLOG_REAL_MONEY_SHOP",MONEYLOG_REAL_MONEY_SHOP);
  tolua_constant(tolua_S,"MONEYLOG_TEAM_AUCTION_BONUS",MONEYLOG_TEAM_AUCTION_BONUS);
  tolua_constant(tolua_S,"MONEYLOG_TEAM_AUCTION_RETURN",MONEYLOG_TEAM_AUCTION_RETURN);
  tolua_constant(tolua_S,"MONEYLOG_TEAM_AUCTION_DEPOSITE",MONEYLOG_TEAM_AUCTION_DEPOSITE);
  tolua_constant(tolua_S,"MONEYLOG_EXCHANGE",MONEYLOG_EXCHANGE);
  tolua_constant(tolua_S,"MONEYLOG_EXCHANGE_FEE",MONEYLOG_EXCHANGE_FEE);
  tolua_constant(tolua_S,"MONEYLOG_MASTER_CZ",MONEYLOG_MASTER_CZ);
  tolua_constant(tolua_S,"MONEYLOG_ACHIEVEMENT_REWARD",MONEYLOG_ACHIEVEMENT_REWARD);
  tolua_constant(tolua_S,"MONEYLOG_RUNE",MONEYLOG_RUNE);
  tolua_constant(tolua_S,"MONEYLOG_ARENA_JOIN_SEASON",MONEYLOG_ARENA_JOIN_SEASON);
  tolua_constant(tolua_S,"MONEYLOG_ARENA_RANK_REWARD",MONEYLOG_ARENA_RANK_REWARD);
  tolua_constant(tolua_S,"MONEYLOG_ENROLL_SABAC",MONEYLOG_ENROLL_SABAC);
  tolua_constant(tolua_S,"MONEYLOG_EQUIP_LEVELUP",MONEYLOG_EQUIP_LEVELUP);
  tolua_constant(tolua_S,"MONEYLOG_REPUTATION_AWARD",MONEYLOG_REPUTATION_AWARD);
  tolua_constant(tolua_S,"MONEYLOG_UPGRADE_STALL",MONEYLOG_UPGRADE_STALL);
  tolua_constant(tolua_S,"MONEYLOG_MINE",MONEYLOG_MINE);
  tolua_constant(tolua_S,"MONEYLOG_AWARD",MONEYLOG_AWARD);
  tolua_constant(tolua_S,"MONEYLOG_ERECT_STATUS",MONEYLOG_ERECT_STATUS);
  tolua_constant(tolua_S,"MONEYLOG_FCM_LOSS",MONEYLOG_FCM_LOSS);
  tolua_constant(tolua_S,"MONEYLOG_DAILY_LIMIT_LOSS",MONEYLOG_DAILY_LIMIT_LOSS);
  tolua_constant(tolua_S,"MONEYLOG_WEEKLY_LIMIT_LOSS",MONEYLOG_WEEKLY_LIMIT_LOSS);
  tolua_constant(tolua_S,"MONEYLOG_TOTAL_LIMIT_LOSS",MONEYLOG_TOTAL_LIMIT_LOSS);
  tolua_constant(tolua_S,"MONEYLOG_CHAT_COST",MONEYLOG_CHAT_COST);
  tolua_constant(tolua_S,"MONEYLOG_ESCORT",MONEYLOG_ESCORT);
  tolua_constant(tolua_S,"MONEYLOG_BLACK_MARKET",MONEYLOG_BLACK_MARKET);
  tolua_constant(tolua_S,"MONEYLOG_MATERIAL",MONEYLOG_MATERIAL);
  tolua_constant(tolua_S,"MONEYLOG_BIRTH",MONEYLOG_BIRTH);
  tolua_constant(tolua_S,"MONEYLOG_EXP_MORAL",MONEYLOG_EXP_MORAL);
  tolua_constant(tolua_S,"MONEYLOG_TEACHER_REWARD",MONEYLOG_TEACHER_REWARD);
  tolua_constant(tolua_S,"MONEYLOG_STUDENT_REWARD",MONEYLOG_STUDENT_REWARD);
  tolua_constant(tolua_S,"MONEYLOG_PACKAGE",MONEYLOG_PACKAGE);
  tolua_constant(tolua_S,"MONEYLOG_EQUIP_LEVELUP_IMMEDIATELY",MONEYLOG_EQUIP_LEVELUP_IMMEDIATELY);
  tolua_constant(tolua_S,"MONEYLOG_ARENA_REFUND",MONEYLOG_ARENA_REFUND);
  tolua_constant(tolua_S,"MONEYLOG_ARENA_REWARD",MONEYLOG_ARENA_REWARD);
  tolua_constant(tolua_S,"MONEYLOG_SELL_RESOURCE_ITEM",MONEYLOG_SELL_RESOURCE_ITEM);
  tolua_constant(tolua_S,"MONEYLOG_CUSTOM_ROLE_BUY_TIME",MONEYLOG_CUSTOM_ROLE_BUY_TIME);
  tolua_constant(tolua_S,"MONEYLOG_EQUIP_LEVELUP_TAKE_OUT_IMMEDIATELY",MONEYLOG_EQUIP_LEVELUP_TAKE_OUT_IMMEDIATELY);
  tolua_constant(tolua_S,"MONEYLOG_GM_CMD_SUB_MONEY_YB",MONEYLOG_GM_CMD_SUB_MONEY_YB);
  tolua_constant(tolua_S,"MONEYLOG_GM_CMD_ADD_ITEM_YBD",MONEYLOG_GM_CMD_ADD_ITEM_YBD);
  tolua_constant(tolua_S,"MONEYLOG_BT_BEGIN",MONEYLOG_BT_BEGIN);
  tolua_constant(tolua_S,"MONEYLOG_BT_01",MONEYLOG_BT_01);
  tolua_constant(tolua_S,"MONEYLOG_BT_02",MONEYLOG_BT_02);
  tolua_constant(tolua_S,"MONEYLOG_BT_03",MONEYLOG_BT_03);
  tolua_constant(tolua_S,"MONEYLOG_BT_04",MONEYLOG_BT_04);
  tolua_constant(tolua_S,"MONEYLOG_BT_05",MONEYLOG_BT_05);
  tolua_constant(tolua_S,"MONEYLOG_BT_06",MONEYLOG_BT_06);
  tolua_constant(tolua_S,"MONEYLOG_BT_07",MONEYLOG_BT_07);
  tolua_constant(tolua_S,"MONEYLOG_BT_08",MONEYLOG_BT_08);
  tolua_constant(tolua_S,"MONEYLOG_BT_09",MONEYLOG_BT_09);
  tolua_constant(tolua_S,"MONEYLOG_BT_10",MONEYLOG_BT_10);
  tolua_constant(tolua_S,"MONEYLOG_BT_11",MONEYLOG_BT_11);
  tolua_constant(tolua_S,"MONEYLOG_BT_12",MONEYLOG_BT_12);
  tolua_constant(tolua_S,"MONEYLOG_BT_13",MONEYLOG_BT_13);
  tolua_constant(tolua_S,"MONEYLOG_BT_14",MONEYLOG_BT_14);
  tolua_constant(tolua_S,"MONEYLOG_BT_15",MONEYLOG_BT_15);
  tolua_constant(tolua_S,"MONEYLOG_BT_16",MONEYLOG_BT_16);
  tolua_constant(tolua_S,"MONEYLOG_BT_17",MONEYLOG_BT_17);
  tolua_constant(tolua_S,"MONEYLOG_BT_18",MONEYLOG_BT_18);
  tolua_constant(tolua_S,"MONEYLOG_BT_19",MONEYLOG_BT_19);
  tolua_constant(tolua_S,"MONEYLOG_BT_20",MONEYLOG_BT_20);
  tolua_constant(tolua_S,"MONEYLOG_BT_21",MONEYLOG_BT_21);
  tolua_constant(tolua_S,"MONEYLOG_BT_22",MONEYLOG_BT_22);
  tolua_constant(tolua_S,"MONEYLOG_BT_23",MONEYLOG_BT_23);
  tolua_constant(tolua_S,"MONEYLOG_BT_24",MONEYLOG_BT_24);
  tolua_constant(tolua_S,"MONEYLOG_BT_25",MONEYLOG_BT_25);
  tolua_constant(tolua_S,"MONEYLOG_BT_26",MONEYLOG_BT_26);
  tolua_constant(tolua_S,"MONEYLOG_BT_27",MONEYLOG_BT_27);
  tolua_constant(tolua_S,"MONEYLOG_BT_28",MONEYLOG_BT_28);
  tolua_constant(tolua_S,"MONEYLOG_BT_29",MONEYLOG_BT_29);
  tolua_constant(tolua_S,"MONEYLOG_BT_30",MONEYLOG_BT_30);
  tolua_constant(tolua_S,"MONEYLOG_BT_31",MONEYLOG_BT_31);
  tolua_constant(tolua_S,"MONEYLOG_BT_32",MONEYLOG_BT_32);
  tolua_constant(tolua_S,"MONEYLOG_BT_33",MONEYLOG_BT_33);
  tolua_constant(tolua_S,"MONEYLOG_BT_34",MONEYLOG_BT_34);
  tolua_constant(tolua_S,"MONEYLOG_BT_35",MONEYLOG_BT_35);
  tolua_constant(tolua_S,"MONEYLOG_BT_36",MONEYLOG_BT_36);
  tolua_constant(tolua_S,"MONEYLOG_BT_37",MONEYLOG_BT_37);
  tolua_constant(tolua_S,"MONEYLOG_BT_38",MONEYLOG_BT_38);
  tolua_constant(tolua_S,"MONEYLOG_BT_39",MONEYLOG_BT_39);
  tolua_constant(tolua_S,"MONEYLOG_BT_40",MONEYLOG_BT_40);
  tolua_constant(tolua_S,"MONEYLOG_TOTAL",MONEYLOG_TOTAL);
  tolua_constant(tolua_S,"ITEMACTION_ADD",ITEMACTION_ADD);
  tolua_constant(tolua_S,"ITEMACTION_DEL",ITEMACTION_DEL);
  tolua_constant(tolua_S,"ITEMACTION_INC",ITEMACTION_INC);
  tolua_constant(tolua_S,"ITEMACTION_DEC",ITEMACTION_DEC);
  tolua_constant(tolua_S,"ITEMACTION_DROP",ITEMACTION_DROP);
  tolua_constant(tolua_S,"ITEMACTION_TOTAL",ITEMACTION_TOTAL);
  tolua_constant(tolua_S,"TRADEACTION_ASK",TRADEACTION_ASK);
  tolua_constant(tolua_S,"TRADEACTION_ACCEPT",TRADEACTION_ACCEPT);
  tolua_constant(tolua_S,"TRADEACTION_PUT_ITEM",TRADEACTION_PUT_ITEM);
  tolua_constant(tolua_S,"TRADEACTION_PUT_MONEY",TRADEACTION_PUT_MONEY);
  tolua_constant(tolua_S,"TRADEACTION_LOCK",TRADEACTION_LOCK);
  tolua_constant(tolua_S,"TRADEACTION_CONFIRM",TRADEACTION_CONFIRM);
  tolua_constant(tolua_S,"TRADEACTION_UNLOCK",TRADEACTION_UNLOCK);
  tolua_constant(tolua_S,"TRADEACTION_CANCEL",TRADEACTION_CANCEL);
  tolua_constant(tolua_S,"TRADEACTION_COMMIT_FAIL_ROLE_MONEY",TRADEACTION_COMMIT_FAIL_ROLE_MONEY);
  tolua_constant(tolua_S,"TRADEACTION_COMMIT_FAIL_TARGET_MONEY",TRADEACTION_COMMIT_FAIL_TARGET_MONEY);
  tolua_constant(tolua_S,"TRADEACTION_COMMIT_FAIL_ROLE_BAG",TRADEACTION_COMMIT_FAIL_ROLE_BAG);
  tolua_constant(tolua_S,"TRADEACTION_COMMIT_FAIL_TARGET_BAG",TRADEACTION_COMMIT_FAIL_TARGET_BAG);
  tolua_constant(tolua_S,"TRADEACTION_COMMIT_SUCCESS",TRADEACTION_COMMIT_SUCCESS);
  tolua_constant(tolua_S,"TRADEACTION_COMMIT_FAIL_ROLE_OVERWEIGHT",TRADEACTION_COMMIT_FAIL_ROLE_OVERWEIGHT);
  tolua_constant(tolua_S,"TRADEACTION_COMMIT_FAIL_TARGET_OVERWEIGHT",TRADEACTION_COMMIT_FAIL_TARGET_OVERWEIGHT);
  tolua_constant(tolua_S,"TRADEACTION_TOTAL",TRADEACTION_TOTAL);
  tolua_constant(tolua_S,"ITEMTYPE_INVALID",ITEMTYPE_INVALID);
  tolua_constant(tolua_S,"ITEMTYPE_USABLE",ITEMTYPE_USABLE);
  tolua_constant(tolua_S,"ITEMTYPE_EQUIP",ITEMTYPE_EQUIP);
  tolua_constant(tolua_S,"ITEMTYPE_MATERIAL",ITEMTYPE_MATERIAL);
  tolua_constant(tolua_S,"ITEMTYPE_FORMULA",ITEMTYPE_FORMULA);
  tolua_constant(tolua_S,"ITEMTYPE_SPELLBOOK",ITEMTYPE_SPELLBOOK);
  tolua_constant(tolua_S,"ITEMTYPE_RUNE",ITEMTYPE_RUNE);
  tolua_constant(tolua_S,"ITEMTYPE_DAN",ITEMTYPE_DAN);
  tolua_constant(tolua_S,"ITEMTYPE_SOUL",ITEMTYPE_SOUL);
  tolua_constant(tolua_S,"ITEMTYPE_MISC",ITEMTYPE_MISC);
  tolua_constant(tolua_S,"ITEMTYPE_QUEST",ITEMTYPE_QUEST);
  tolua_constant(tolua_S,"ITEMTYPE_DEPOSIT",ITEMTYPE_DEPOSIT);
  tolua_constant(tolua_S,"ITEMTYPE_RECOVER",ITEMTYPE_RECOVER);
  tolua_constant(tolua_S,"ITEMTYPE_RMB",ITEMTYPE_RMB);
  tolua_constant(tolua_S,"ITEMTYPE_TOTAL",ITEMTYPE_TOTAL);
  tolua_constant(tolua_S,"ITEMSUBTYPE_INVALID",ITEMSUBTYPE_INVALID);
  tolua_constant(tolua_S,"ITEMSUBTYPE_USABLE_FOOD",ITEMSUBTYPE_USABLE_FOOD);
  tolua_constant(tolua_S,"ITEMSUBTYPE_USABLE_DRINK",ITEMSUBTYPE_USABLE_DRINK);
  tolua_constant(tolua_S,"ITEMSUBTYPE_USABLE_POTION",ITEMSUBTYPE_USABLE_POTION);
  tolua_constant(tolua_S,"ITEMSUBTYPE_USABLE_FLASK",ITEMSUBTYPE_USABLE_FLASK);
  tolua_constant(tolua_S,"ITEMSUBTYPE_USABLE_SCROLL",ITEMSUBTYPE_USABLE_SCROLL);
  tolua_constant(tolua_S,"ITEMSUBTYPE_USABLE_MISC",ITEMSUBTYPE_USABLE_MISC);
  tolua_constant(tolua_S,"ITEMSUBTYPE_USABLE_GREY_POWDER",ITEMSUBTYPE_USABLE_GREY_POWDER);
  tolua_constant(tolua_S,"ITEMSUBTYPE_USABLE_YELLOW_POWDER",ITEMSUBTYPE_USABLE_YELLOW_POWDER);
  tolua_constant(tolua_S,"ITEMSUBTYPE_USABLE_RUNE",ITEMSUBTYPE_USABLE_RUNE);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_WEAPON",ITEMSUBTYPE_EQUIP_WEAPON);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_HAT",ITEMSUBTYPE_EQUIP_HAT);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_SHOULDER_ARMOR",ITEMSUBTYPE_EQUIP_SHOULDER_ARMOR);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_CHEST_ARMOR",ITEMSUBTYPE_EQUIP_CHEST_ARMOR);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_WRIST_ARMOR",ITEMSUBTYPE_EQUIP_WRIST_ARMOR);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_BELT",ITEMSUBTYPE_EQUIP_BELT);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_SHOES",ITEMSUBTYPE_EQUIP_SHOES);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_CLOAK",ITEMSUBTYPE_EQUIP_CLOAK);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_NECKLACE",ITEMSUBTYPE_EQUIP_NECKLACE);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_RING",ITEMSUBTYPE_EQUIP_RING);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_BRACELET",ITEMSUBTYPE_EQUIP_BRACELET);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_HONOR",ITEMSUBTYPE_EQUIP_HONOR);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_JADE",ITEMSUBTYPE_EQUIP_JADE);
  tolua_constant(tolua_S,"ITEMSUBTYPE_EQUIP_OFFHAND",ITEMSUBTYPE_EQUIP_OFFHAND);
  tolua_constant(tolua_S,"ITEMSUBTYPE_MATERIAL_REFINE",ITEMSUBTYPE_MATERIAL_REFINE);
  tolua_constant(tolua_S,"ITEMSUBTYPE_MATERIAL_COMPOSE",ITEMSUBTYPE_MATERIAL_COMPOSE);
  tolua_constant(tolua_S,"ITEMSUBTYPE_MATERIAL_WEAPON_LEVELUP",ITEMSUBTYPE_MATERIAL_WEAPON_LEVELUP);
  tolua_constant(tolua_S,"ITEMSUBTYPE_MATERIAL_MISC",ITEMSUBTYPE_MATERIAL_MISC);
  tolua_constant(tolua_S,"ITEMSUBTYPE_FORMULA_DEFAULT",ITEMSUBTYPE_FORMULA_DEFAULT);
  tolua_constant(tolua_S,"ITEMSUBTYPE_SPELLBOOK_PLAYER",ITEMSUBTYPE_SPELLBOOK_PLAYER);
  tolua_constant(tolua_S,"ITEMSUBTYPE_SPELLBOOK_PET",ITEMSUBTYPE_SPELLBOOK_PET);
  tolua_constant(tolua_S,"ITEMSUBTYPE_RUNE_DEFAULT",ITEMSUBTYPE_RUNE_DEFAULT);
  tolua_constant(tolua_S,"ITEMSUBTYPE_DAN_DEFAULT",ITEMSUBTYPE_DAN_DEFAULT);
  tolua_constant(tolua_S,"ITEMSUBTYPE_SOUL_DEFAULT",ITEMSUBTYPE_SOUL_DEFAULT);
  tolua_constant(tolua_S,"ITEMSUBTYPE_MISC_DEFAULT",ITEMSUBTYPE_MISC_DEFAULT);
  tolua_constant(tolua_S,"ITEMSUBTYPE_MISC_PET",ITEMSUBTYPE_MISC_PET);
  tolua_constant(tolua_S,"ITEMSUBTYPE_MISC_MOUNT",ITEMSUBTYPE_MISC_MOUNT);
  tolua_constant(tolua_S,"ITEMSUBTYPE_QUEST_DEFAULT",ITEMSUBTYPE_QUEST_DEFAULT);
  tolua_constant(tolua_S,"ITEMSUBTYPE_DEPOSIT_SOUL",ITEMSUBTYPE_DEPOSIT_SOUL);
  tolua_constant(tolua_S,"ITEMSUBTYPE_DEPOSIT_EXP",ITEMSUBTYPE_DEPOSIT_EXP);
  tolua_constant(tolua_S,"ITEMSUBTYPE_RECOVER_HP",ITEMSUBTYPE_RECOVER_HP);
  tolua_constant(tolua_S,"ITEMSUBTYPE_RECOVER_MP",ITEMSUBTYPE_RECOVER_MP);
  tolua_constant(tolua_S,"ITEMSUBTYPE_RECOVER_HPMP",ITEMSUBTYPE_RECOVER_HPMP);
  tolua_constant(tolua_S,"ITEMSUBTYPE_RMB_DEFAULT",ITEMSUBTYPE_RMB_DEFAULT);
  tolua_constant(tolua_S,"WEAPONTYPE_INVALID",WEAPONTYPE_INVALID);
  tolua_constant(tolua_S,"WEAPONTYPE_HAND",WEAPONTYPE_HAND);
  tolua_constant(tolua_S,"WEAPONTYPE_01",WEAPONTYPE_01);
  tolua_constant(tolua_S,"WEAPONTYPE_02",WEAPONTYPE_02);
  tolua_constant(tolua_S,"WEAPONTYPE_03",WEAPONTYPE_03);
  tolua_constant(tolua_S,"WEAPONTYPE_04",WEAPONTYPE_04);
  tolua_constant(tolua_S,"WEAPONTYPE_05",WEAPONTYPE_05);
  tolua_constant(tolua_S,"WEAPONTYPE_06",WEAPONTYPE_06);
  tolua_constant(tolua_S,"WEAPONTYPE_07",WEAPONTYPE_07);
  tolua_constant(tolua_S,"WEAPONTYPE_08",WEAPONTYPE_08);
  tolua_constant(tolua_S,"WEAPONTYPE_09",WEAPONTYPE_09);
  tolua_constant(tolua_S,"WEAPONTYPE_10",WEAPONTYPE_10);
  tolua_constant(tolua_S,"WEAPONTYPE_11",WEAPONTYPE_11);
  tolua_constant(tolua_S,"WEAPONTYPE_12",WEAPONTYPE_12);
  tolua_constant(tolua_S,"WEAPONTYPE_13",WEAPONTYPE_13);
  tolua_constant(tolua_S,"WEAPONTYPE_14",WEAPONTYPE_14);
  tolua_constant(tolua_S,"WEAPONTYPE_15",WEAPONTYPE_15);
  tolua_constant(tolua_S,"WEAPONTYPE_16",WEAPONTYPE_16);
  tolua_constant(tolua_S,"WEAPONTYPE_17",WEAPONTYPE_17);
  tolua_constant(tolua_S,"WEAPONTYPE_TOTAL",WEAPONTYPE_TOTAL);
  tolua_constant(tolua_S,"ARMORTYPE_INVALID",ARMORTYPE_INVALID);
  tolua_constant(tolua_S,"ARMORTYPE_NO_ARMOR",ARMORTYPE_NO_ARMOR);
  tolua_constant(tolua_S,"ARMORTYPE_CLOTH",ARMORTYPE_CLOTH);
  tolua_constant(tolua_S,"ARMORTYPE_LEATHER",ARMORTYPE_LEATHER);
  tolua_constant(tolua_S,"ARMORTYPE_CHAIN",ARMORTYPE_CHAIN);
  tolua_constant(tolua_S,"ARMORTYPE_PLATE",ARMORTYPE_PLATE);
  tolua_constant(tolua_S,"ARMORTYPE_BACK",ARMORTYPE_BACK);
  tolua_constant(tolua_S,"ARMORTYPE_JEWELRY",ARMORTYPE_JEWELRY);
  tolua_constant(tolua_S,"ARMORTYPE_AVATAR",ARMORTYPE_AVATAR);
  tolua_constant(tolua_S,"ITEMCOLOR_INVALID",ITEMCOLOR_INVALID);
  tolua_constant(tolua_S,"ITEMCOLOR_WHITE",ITEMCOLOR_WHITE);
  tolua_constant(tolua_S,"ITEMCOLOR_GREEN",ITEMCOLOR_GREEN);
  tolua_constant(tolua_S,"ITEMCOLOR_BLUE",ITEMCOLOR_BLUE);
  tolua_constant(tolua_S,"ITEMCOLOR_PURPLE",ITEMCOLOR_PURPLE);
  tolua_constant(tolua_S,"ITEMCOLOR_ORANGE",ITEMCOLOR_ORANGE);
  tolua_constant(tolua_S,"ITEMCOLOR_RESERVED1",ITEMCOLOR_RESERVED1);
  tolua_constant(tolua_S,"ITEMCOLOR_RESERVED2",ITEMCOLOR_RESERVED2);
  tolua_constant(tolua_S,"ITEMCOLOR_TOTAL",ITEMCOLOR_TOTAL);
  tolua_constant(tolua_S,"ITEMCOMBAT_BOTH",ITEMCOMBAT_BOTH);
  tolua_constant(tolua_S,"ITEMCOMBAT_IN",ITEMCOMBAT_IN);
  tolua_constant(tolua_S,"ITEMCOMBAT_OUT",ITEMCOMBAT_OUT);
  tolua_constant(tolua_S,"DURTYPE_NONE",DURTYPE_NONE);
  tolua_constant(tolua_S,"DURTYPE_EQUIP",DURTYPE_EQUIP);
  tolua_constant(tolua_S,"DURTYPE_STACK",DURTYPE_STACK);
  tolua_constant(tolua_S,"DURTYPE_USE",DURTYPE_USE);
  tolua_constant(tolua_S,"DURTYPE_DEPOSIT",DURTYPE_DEPOSIT);
  tolua_constant(tolua_S,"DURTYPE_RECOVER",DURTYPE_RECOVER);
  tolua_constant(tolua_S,"DURTYPE_PURITY",DURTYPE_PURITY);
 tolua_constant(tolua_S,"EQUIP_DUR_MULTIPLIER",EQUIP_DUR_MULTIPLIER);
  tolua_constant(tolua_S,"BINDTYPE_NONE",BINDTYPE_NONE);
  tolua_constant(tolua_S,"BINDTYPE_BOU",BINDTYPE_BOU);
  tolua_constant(tolua_S,"BINDTYPE_BOE",BINDTYPE_BOE);
  tolua_constant(tolua_S,"BINDTYPE_BOP",BINDTYPE_BOP);
  tolua_constant(tolua_S,"BINDTYPE_BOT",BINDTYPE_BOT);
  tolua_constant(tolua_S,"BINDTYPE_BINDED",BINDTYPE_BINDED);
  tolua_constant(tolua_S,"PKDROP_BY_CHANCE",PKDROP_BY_CHANCE);
  tolua_constant(tolua_S,"PKDROP_NOT_DROP",PKDROP_NOT_DROP);
  tolua_constant(tolua_S,"PKDROP_MUST_DROP",PKDROP_MUST_DROP);
  tolua_constant(tolua_S,"IDENTIFY_TYPE_NO",IDENTIFY_TYPE_NO);
  tolua_constant(tolua_S,"IDENTIFY_TYPE_YES",IDENTIFY_TYPE_YES);
  tolua_constant(tolua_S,"IDENTIFY_TYPE_LEVEL_UP",IDENTIFY_TYPE_LEVEL_UP);
  tolua_constant(tolua_S,"CONSLOT_EQUIPPED",CONSLOT_EQUIPPED);
  tolua_constant(tolua_S,"CONSLOT_DEFAULT",CONSLOT_DEFAULT);
  tolua_constant(tolua_S,"CONSLOT_BANK",CONSLOT_BANK);
  tolua_constant(tolua_S,"CONSLOT_HERO_EQUIPPED",CONSLOT_HERO_EQUIPPED);
  tolua_constant(tolua_S,"CONSLOT_HERO_EQUIPMENT",CONSLOT_HERO_EQUIPMENT);
  tolua_constant(tolua_S,"CONSLOT_DEPOSIT",CONSLOT_DEPOSIT);
  tolua_constant(tolua_S,"CONSLOT_RECOVER",CONSLOT_RECOVER);
  tolua_constant(tolua_S,"CONSLOT_RESOURCE",CONSLOT_RESOURCE);
  tolua_constant(tolua_S,"CONSLOT_COUNT",CONSLOT_COUNT);
  tolua_constant(tolua_S,"CONSLOT_P2P_MY",CONSLOT_P2P_MY);
  tolua_constant(tolua_S,"CONSLOT_P2P_TG",CONSLOT_P2P_TG);
  tolua_constant(tolua_S,"CONSLOT_STALL_SETTING",CONSLOT_STALL_SETTING);
  tolua_constant(tolua_S,"CONSLOT_STALL_BUY",CONSLOT_STALL_BUY);
  tolua_constant(tolua_S,"CONSLOT_PROFILE",CONSLOT_PROFILE);
  tolua_constant(tolua_S,"CONSLOT_GUILD_BANK",CONSLOT_GUILD_BANK);
  tolua_constant(tolua_S,"CONSLOT_WEAPON_LEVEL_UP",CONSLOT_WEAPON_LEVEL_UP);
  tolua_constant(tolua_S,"NES_MAIN_HAND",NES_MAIN_HAND);
  tolua_constant(tolua_S,"NES_BODY",NES_BODY);
  tolua_constant(tolua_S,"NES_BACK",NES_BACK);
  tolua_constant(tolua_S,"NES_HEAD",NES_HEAD);
  tolua_constant(tolua_S,"NES_SHOULDER",NES_SHOULDER);
  tolua_constant(tolua_S,"NES_ARM",NES_ARM);
  tolua_constant(tolua_S,"NES_WAIST",NES_WAIST);
  tolua_constant(tolua_S,"NES_FOOT",NES_FOOT);
  tolua_constant(tolua_S,"NES_NECK",NES_NECK);
  tolua_constant(tolua_S,"NES_FINGER_L",NES_FINGER_L);
  tolua_constant(tolua_S,"NES_FINGER_R",NES_FINGER_R);
  tolua_constant(tolua_S,"NES_WRIST_L",NES_WRIST_L);
  tolua_constant(tolua_S,"NES_WRIST_R",NES_WRIST_R);
  tolua_constant(tolua_S,"NES_TOTAL",NES_TOTAL);
  tolua_constant(tolua_S,"NES_VISIBLE_TOTAL",NES_VISIBLE_TOTAL);
#ifndef TOLUA_DISABLE_tolua_item_bag_IsAppearance00
 tolua_function(tolua_S,"IsAppearance",tolua_item_bag_IsAppearance00);
#endif //#ifndef TOLUA_DISABLE
  tolua_constant(tolua_S,"DEPOSIT_SOUL_SLOT",DEPOSIT_SOUL_SLOT);
  tolua_constant(tolua_S,"DEPOSIT_EXP_SLOT",DEPOSIT_EXP_SLOT);
  tolua_constant(tolua_S,"DEPOSIT_ITEM_SLOT_TOTAL",DEPOSIT_ITEM_SLOT_TOTAL);
  tolua_constant(tolua_S,"SOCKET_NONE",SOCKET_NONE);
  tolua_constant(tolua_S,"SOCKET_RED",SOCKET_RED);
  tolua_constant(tolua_S,"SOCKET_YELLOW",SOCKET_YELLOW);
  tolua_constant(tolua_S,"SOCKET_BLUE",SOCKET_BLUE);
  tolua_constant(tolua_S,"SOCKET_GREEN",SOCKET_GREEN);
  tolua_constant(tolua_S,"SOCKET_PURPLE",SOCKET_PURPLE);
  tolua_constant(tolua_S,"SOCKET_COLORFUL",SOCKET_COLORFUL);
  tolua_constant(tolua_S,"SOCKET_TYPE_COUNT",SOCKET_TYPE_COUNT);
  tolua_constant(tolua_S,"asetEquipIsNull",asetEquipIsNull);
  tolua_constant(tolua_S,"asetEquipCantSocket",asetEquipCantSocket);
  tolua_constant(tolua_S,"asetEquipCantNotBeAddSocket",asetEquipCantNotBeAddSocket);
  tolua_constant(tolua_S,"asetEquipAddSocketSlotUnknown",asetEquipAddSocketSlotUnknown);
  tolua_constant(tolua_S,"asetEquipNeedItemCount",asetEquipNeedItemCount);
  tolua_constant(tolua_S,"asetEquipItemNotEnough",asetEquipItemNotEnough);
  tolua_constant(tolua_S,"asetEquipAddSocketSuccess",asetEquipAddSocketSuccess);
  tolua_constant(tolua_S,"ssctEquipIsNull",ssctEquipIsNull);
  tolua_constant(tolua_S,"ssctEquipNoSocket1",ssctEquipNoSocket1);
  tolua_constant(tolua_S,"ssctEquipNoSocket2",ssctEquipNoSocket2);
  tolua_constant(tolua_S,"ssctEquipCantSetColor",ssctEquipCantSetColor);
  tolua_constant(tolua_S,"ssctEquipSetColorError",ssctEquipSetColorError);
  tolua_constant(tolua_S,"ssctEquipSetSlotError",ssctEquipSetSlotError);
  tolua_constant(tolua_S,"ssctEquipNeedItemCount",ssctEquipNeedItemCount);
  tolua_constant(tolua_S,"ssctEquipItemNotEnough",ssctEquipItemNotEnough);
  tolua_constant(tolua_S,"ssctEquipSetSocketSuccess",ssctEquipSetSocketSuccess);
  tolua_constant(tolua_S,"essNotOpen",essNotOpen);
  tolua_constant(tolua_S,"essPreparing",essPreparing);
  tolua_constant(tolua_S,"essOpen",essOpen);
 tolua_constant(tolua_S,"MAX_TRADE_SLOT",MAX_TRADE_SLOT);
  tolua_constant(tolua_S,"etsFree",etsFree);
  tolua_constant(tolua_S,"etsAsking",etsAsking);
  tolua_constant(tolua_S,"etsBeingAsked",etsBeingAsked);
  tolua_constant(tolua_S,"etsTrading",etsTrading);
  tolua_constant(tolua_S,"etsLocked",etsLocked);
  tolua_constant(tolua_S,"etsConfirmed",etsConfirmed);
  tolua_constant(tolua_S,"etsSuccess",etsSuccess);
 tolua_constant(tolua_S,"MAX_SOLD_ITEMS",MAX_SOLD_ITEMS);
  tolua_constant(tolua_S,"ebmltNone",ebmltNone);
  tolua_constant(tolua_S,"ebmltRole",ebmltRole);
  tolua_constant(tolua_S,"ebmltServer",ebmltServer);
 tolua_constant(tolua_S,"MAX_RUNE_COUNT",MAX_RUNE_COUNT);
 tolua_constant(tolua_S,"MAX_SOCKET_COUNT",MAX_SOCKET_COUNT);
 tolua_cclass(tolua_S,"DROP_CHANCE_DATA","DROP_CHANCE_DATA","",NULL);
 tolua_beginmodule(tolua_S,"DROP_CHANCE_DATA");
  tolua_variable(tolua_S,"nDropGroupID",tolua_get_DROP_CHANCE_DATA_nDropGroupID,tolua_set_DROP_CHANCE_DATA_nDropGroupID);
  tolua_variable(tolua_S,"nDropChance",tolua_get_DROP_CHANCE_DATA_nDropChance,tolua_set_DROP_CHANCE_DATA_nDropChance);
 tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"egtInvalid",egtInvalid);
  tolua_constant(tolua_S,"egtEquipWeapon",egtEquipWeapon);
  tolua_constant(tolua_S,"egtEquipHat",egtEquipHat);
  tolua_constant(tolua_S,"egtEquipShoulderArmor",egtEquipShoulderArmor);
  tolua_constant(tolua_S,"egtEquipChestArmor",egtEquipChestArmor);
  tolua_constant(tolua_S,"egtEquipWristArmor",egtEquipWristArmor);
  tolua_constant(tolua_S,"egtEquipBelt",egtEquipBelt);
  tolua_constant(tolua_S,"egtEquipShoes",egtEquipShoes);
  tolua_constant(tolua_S,"egtEquipCloak",egtEquipCloak);
  tolua_constant(tolua_S,"egtEquipNecklace",egtEquipNecklace);
  tolua_constant(tolua_S,"egtEquipRing",egtEquipRing);
  tolua_constant(tolua_S,"egtEquipBracelet",egtEquipBracelet);
  tolua_constant(tolua_S,"egtSpellBook",egtSpellBook);
  tolua_constant(tolua_S,"egtRuneWarrior",egtRuneWarrior);
  tolua_constant(tolua_S,"egtRuneMage",egtRuneMage);
  tolua_constant(tolua_S,"egtRuneRogue",egtRuneRogue);
  tolua_constant(tolua_S,"egtRuneArcher",egtRuneArcher);
  tolua_constant(tolua_S,"egtRuneTaoist",egtRuneTaoist);
  tolua_constant(tolua_S,"egtGambleItem",egtGambleItem);
  tolua_constant(tolua_S,"egtPotion",egtPotion);
  tolua_constant(tolua_S,"egtReserved03",egtReserved03);
  tolua_constant(tolua_S,"egtReserved04",egtReserved04);
  tolua_constant(tolua_S,"egtReserved05",egtReserved05);
  tolua_constant(tolua_S,"egtReserved06",egtReserved06);
  tolua_constant(tolua_S,"egtReserved07",egtReserved07);
  tolua_constant(tolua_S,"egtReserved08",egtReserved08);
  tolua_constant(tolua_S,"egtReserved09",egtReserved09);
  tolua_constant(tolua_S,"egtReserved10",egtReserved10);
  tolua_constant(tolua_S,"egtReserved11",egtReserved11);
  tolua_constant(tolua_S,"egtReserved12",egtReserved12);
  tolua_constant(tolua_S,"egtReserved13",egtReserved13);
  tolua_constant(tolua_S,"egtReserved14",egtReserved14);
  tolua_constant(tolua_S,"egtReserved15",egtReserved15);
  tolua_constant(tolua_S,"egtTotal",egtTotal);
 tolua_cclass(tolua_S,"CItemBag","CItemBag","",NULL);
 tolua_beginmodule(tolua_S,"CItemBag");
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_AddItem00
  tolua_function(tolua_S,"AddItem",tolua_item_bag_CItemBag_AddItem00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_AddItem01
  tolua_function(tolua_S,"AddItem",tolua_item_bag_CItemBag_AddItem01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_UseItem00
  tolua_function(tolua_S,"UseItem",tolua_item_bag_CItemBag_UseItem00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_MoveItem00
  tolua_function(tolua_S,"MoveItem",tolua_item_bag_CItemBag_MoveItem00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SplitItem00
  tolua_function(tolua_S,"SplitItem",tolua_item_bag_CItemBag_SplitItem00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_DeleteItemPos00
  tolua_function(tolua_S,"DeleteItemPos",tolua_item_bag_CItemBag_DeleteItemPos00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetItemCount00
  tolua_function(tolua_S,"GetItemCount",tolua_item_bag_CItemBag_GetItemCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_DeleteItemId00
  tolua_function(tolua_S,"DeleteItemId",tolua_item_bag_CItemBag_DeleteItemId00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetFreeSlots00
  tolua_function(tolua_S,"GetFreeSlots",tolua_item_bag_CItemBag_GetFreeSlots00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_IdentifyItem00
  tolua_function(tolua_S,"IdentifyItem",tolua_item_bag_CItemBag_IdentifyItem00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_Refine00
  tolua_function(tolua_S,"Refine",tolua_item_bag_CItemBag_Refine00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SetRefineLevel00
  tolua_function(tolua_S,"SetRefineLevel",tolua_item_bag_CItemBag_SetRefineLevel00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_RandomizeItem00
  tolua_function(tolua_S,"RandomizeItem",tolua_item_bag_CItemBag_RandomizeItem00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_AddSoul00
  tolua_function(tolua_S,"AddSoul",tolua_item_bag_CItemBag_AddSoul00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetItem00
  tolua_function(tolua_S,"GetItem",tolua_item_bag_CItemBag_GetItem00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_LoseWeaponDur00
  tolua_function(tolua_S,"LoseWeaponDur",tolua_item_bag_CItemBag_LoseWeaponDur00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_LoseArmorDur00
  tolua_function(tolua_S,"LoseArmorDur",tolua_item_bag_CItemBag_LoseArmorDur00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_BuySlots00
  tolua_function(tolua_S,"BuySlots",tolua_item_bag_CItemBag_BuySlots00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_EquipItemOnBirth00
  tolua_function(tolua_S,"EquipItemOnBirth",tolua_item_bag_CItemBag_EquipItemOnBirth00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_EquipHeroItemOnBirth00
  tolua_function(tolua_S,"EquipHeroItemOnBirth",tolua_item_bag_CItemBag_EquipHeroItemOnBirth00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetMoney00
  tolua_function(tolua_S,"GetMoney",tolua_item_bag_CItemBag_GetMoney00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_AddMoney00
  tolua_function(tolua_S,"AddMoney",tolua_item_bag_CItemBag_AddMoney00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SubMoney00
  tolua_function(tolua_S,"SubMoney",tolua_item_bag_CItemBag_SubMoney00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SetMoney00
  tolua_function(tolua_S,"SetMoney",tolua_item_bag_CItemBag_SetMoney00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetGoldPool00
  tolua_function(tolua_S,"GetGoldPool",tolua_item_bag_CItemBag_GetGoldPool00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetChanceByGoldPool00
  tolua_function(tolua_S,"GetChanceByGoldPool",tolua_item_bag_CItemBag_GetChanceByGoldPool00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SetUseMoneytype01Only00
  tolua_function(tolua_S,"SetUseMoneytype01Only",tolua_item_bag_CItemBag_SetUseMoneytype01Only00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetUseMoneytype01Only00
  tolua_function(tolua_S,"GetUseMoneytype01Only",tolua_item_bag_CItemBag_GetUseMoneytype01Only00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetWeaponType00
  tolua_function(tolua_S,"GetWeaponType",tolua_item_bag_CItemBag_GetWeaponType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_GetHeroWeaponType00
  tolua_function(tolua_S,"GetHeroWeaponType",tolua_item_bag_CItemBag_GetHeroWeaponType00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_Begin00
  tolua_function(tolua_S,"Begin",tolua_item_bag_CItemBag_Begin00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_Next00
  tolua_function(tolua_S,"Next",tolua_item_bag_CItemBag_Next00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SetWeaponLuck00
  tolua_function(tolua_S,"SetWeaponLuck",tolua_item_bag_CItemBag_SetWeaponLuck00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_IncreaseWeaponLuck00
  tolua_function(tolua_S,"IncreaseWeaponLuck",tolua_item_bag_CItemBag_IncreaseWeaponLuck00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_DecreaseWeaponLuck00
  tolua_function(tolua_S,"DecreaseWeaponLuck",tolua_item_bag_CItemBag_DecreaseWeaponLuck00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_RuneTest00
  tolua_function(tolua_S,"RuneTest",tolua_item_bag_CItemBag_RuneTest00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_EquipAddSocket00
  tolua_function(tolua_S,"EquipAddSocket",tolua_item_bag_CItemBag_EquipAddSocket00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_SetSocketColor00
  tolua_function(tolua_S,"SetSocketColor",tolua_item_bag_CItemBag_SetSocketColor00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemBag_AddDestinyWeapon00
  tolua_function(tolua_S,"AddDestinyWeapon",tolua_item_bag_CItemBag_AddDestinyWeapon00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CItemMgr","CItemMgr","",NULL);
 tolua_beginmodule(tolua_S,"CItemMgr");
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemMgr_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_item_bag_CItemMgr_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemMgr_GenerateItem00
  tolua_function(tolua_S,"GenerateItem",tolua_item_bag_CItemMgr_GenerateItem00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemMgr_GenerateItem01
  tolua_function(tolua_S,"GenerateItem",tolua_item_bag_CItemMgr_GenerateItem01);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_item_bag_CItemMgr_DestroyItem00
  tolua_function(tolua_S,"DestroyItem",tolua_item_bag_CItemMgr_DestroyItem00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_item_bag (lua_State* tolua_S) {
 return tolua_item_bag_open(tolua_S);
};
#endif

