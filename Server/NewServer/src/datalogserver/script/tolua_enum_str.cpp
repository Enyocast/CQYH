/*
** Lua binding: enum_str
** Generated automatically by tolua++-1.0.92 on 11/08/18 22:52:12.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_enum_str_open (lua_State* tolua_S);

#include "../../../common/define/item_def.h"
#include "../../../common/define/char_def.h"
#include "../../../common/define/id_def.h"
#include "../../../common/define/quest_def.h"
#include "../../../common/define/guild_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"DROP_CHANCE_DATA");
}

/* function: IsAppearance */
#ifndef TOLUA_DISABLE_tolua_enum_str_IsAppearance00
static int tolua_enum_str_IsAppearance00(lua_State* tolua_S)
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

/* method: new of class  DROP_CHANCE_DATA */
#ifndef TOLUA_DISABLE_tolua_enum_str_DROP_CHANCE_DATA_new00
static int tolua_enum_str_DROP_CHANCE_DATA_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"DROP_CHANCE_DATA",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  DROP_CHANCE_DATA* tolua_ret = (DROP_CHANCE_DATA*)  Mtolua_new((DROP_CHANCE_DATA)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"DROP_CHANCE_DATA");
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

/* method: new_local of class  DROP_CHANCE_DATA */
#ifndef TOLUA_DISABLE_tolua_enum_str_DROP_CHANCE_DATA_new00_local
static int tolua_enum_str_DROP_CHANCE_DATA_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"DROP_CHANCE_DATA",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  DROP_CHANCE_DATA* tolua_ret = (DROP_CHANCE_DATA*)  Mtolua_new((DROP_CHANCE_DATA)());
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"DROP_CHANCE_DATA");
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

/* function: MakeObjectID */
#ifndef TOLUA_DISABLE_tolua_enum_str_MakeObjectID00
static int tolua_enum_str_MakeObjectID00(lua_State* tolua_S)
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
  unsigned int dwType = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int dwIndex = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 {
  unsigned int tolua_ret = ( unsigned int)  MakeObjectID(dwType,dwIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeObjectID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetTypeFromID */
#ifndef TOLUA_DISABLE_tolua_enum_str_GetTypeFromID00
static int tolua_enum_str_GetTypeFromID00(lua_State* tolua_S)
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
  unsigned int dwObjID = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  signed int tolua_ret = ( signed int)  GetTypeFromID(dwObjID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTypeFromID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetIndexFromID */
#ifndef TOLUA_DISABLE_tolua_enum_str_GetIndexFromID00
static int tolua_enum_str_GetIndexFromID00(lua_State* tolua_S)
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
  unsigned int dwObjID = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  signed int tolua_ret = ( signed int)  GetIndexFromID(dwObjID);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIndexFromID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_enum_str_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_ITEM_COUNT",MAX_ITEM_COUNT);
 tolua_constant(tolua_S,"MAX_DROP_COUNT",MAX_DROP_COUNT);
 tolua_constant(tolua_S,"MAX_REFINE_LEVEL",MAX_REFINE_LEVEL);
 tolua_module(tolua_S,"EItemLog",0);
 tolua_beginmodule(tolua_S,"EItemLog");
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
  tolua_constant(tolua_S,"ITEMLOG_TOTAL",ITEMLOG_TOTAL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"EMoneyLog",0);
 tolua_beginmodule(tolua_S,"EMoneyLog");
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
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"EItemActionType",0);
 tolua_beginmodule(tolua_S,"EItemActionType");
  tolua_constant(tolua_S,"ITEMACTION_ADD",ITEMACTION_ADD);
  tolua_constant(tolua_S,"ITEMACTION_DEL",ITEMACTION_DEL);
  tolua_constant(tolua_S,"ITEMACTION_INC",ITEMACTION_INC);
  tolua_constant(tolua_S,"ITEMACTION_DEC",ITEMACTION_DEC);
  tolua_constant(tolua_S,"ITEMACTION_DROP",ITEMACTION_DROP);
  tolua_constant(tolua_S,"ITEMACTION_TOTAL",ITEMACTION_TOTAL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"ETradeActionType",0);
 tolua_beginmodule(tolua_S,"ETradeActionType");
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
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"ITEM_TYPE",0);
 tolua_beginmodule(tolua_S,"ITEM_TYPE");
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
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"ITEM_SUBTYPE",0);
 tolua_beginmodule(tolua_S,"ITEM_SUBTYPE");
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
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"WEAPON_TYPE",0);
 tolua_beginmodule(tolua_S,"WEAPON_TYPE");
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
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"ARMOR_TYPE",0);
 tolua_beginmodule(tolua_S,"ARMOR_TYPE");
  tolua_constant(tolua_S,"ARMORTYPE_INVALID",ARMORTYPE_INVALID);
  tolua_constant(tolua_S,"ARMORTYPE_NO_ARMOR",ARMORTYPE_NO_ARMOR);
  tolua_constant(tolua_S,"ARMORTYPE_CLOTH",ARMORTYPE_CLOTH);
  tolua_constant(tolua_S,"ARMORTYPE_LEATHER",ARMORTYPE_LEATHER);
  tolua_constant(tolua_S,"ARMORTYPE_CHAIN",ARMORTYPE_CHAIN);
  tolua_constant(tolua_S,"ARMORTYPE_PLATE",ARMORTYPE_PLATE);
  tolua_constant(tolua_S,"ARMORTYPE_BACK",ARMORTYPE_BACK);
  tolua_constant(tolua_S,"ARMORTYPE_JEWELRY",ARMORTYPE_JEWELRY);
  tolua_constant(tolua_S,"ARMORTYPE_AVATAR",ARMORTYPE_AVATAR);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"ITEM_COLOR",0);
 tolua_beginmodule(tolua_S,"ITEM_COLOR");
  tolua_constant(tolua_S,"ITEMCOLOR_INVALID",ITEMCOLOR_INVALID);
  tolua_constant(tolua_S,"ITEMCOLOR_WHITE",ITEMCOLOR_WHITE);
  tolua_constant(tolua_S,"ITEMCOLOR_GREEN",ITEMCOLOR_GREEN);
  tolua_constant(tolua_S,"ITEMCOLOR_BLUE",ITEMCOLOR_BLUE);
  tolua_constant(tolua_S,"ITEMCOLOR_PURPLE",ITEMCOLOR_PURPLE);
  tolua_constant(tolua_S,"ITEMCOLOR_ORANGE",ITEMCOLOR_ORANGE);
  tolua_constant(tolua_S,"ITEMCOLOR_RESERVED1",ITEMCOLOR_RESERVED1);
  tolua_constant(tolua_S,"ITEMCOLOR_RESERVED2",ITEMCOLOR_RESERVED2);
  tolua_constant(tolua_S,"ITEMCOLOR_TOTAL",ITEMCOLOR_TOTAL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"ITEM_COMBAT_TYPE",0);
 tolua_beginmodule(tolua_S,"ITEM_COMBAT_TYPE");
  tolua_constant(tolua_S,"ITEMCOMBAT_BOTH",ITEMCOMBAT_BOTH);
  tolua_constant(tolua_S,"ITEMCOMBAT_IN",ITEMCOMBAT_IN);
  tolua_constant(tolua_S,"ITEMCOMBAT_OUT",ITEMCOMBAT_OUT);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"DUR_TYPE",0);
 tolua_beginmodule(tolua_S,"DUR_TYPE");
  tolua_constant(tolua_S,"DURTYPE_NONE",DURTYPE_NONE);
  tolua_constant(tolua_S,"DURTYPE_EQUIP",DURTYPE_EQUIP);
  tolua_constant(tolua_S,"DURTYPE_STACK",DURTYPE_STACK);
  tolua_constant(tolua_S,"DURTYPE_USE",DURTYPE_USE);
  tolua_constant(tolua_S,"DURTYPE_DEPOSIT",DURTYPE_DEPOSIT);
  tolua_constant(tolua_S,"DURTYPE_RECOVER",DURTYPE_RECOVER);
  tolua_constant(tolua_S,"DURTYPE_PURITY",DURTYPE_PURITY);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"EQUIP_DUR_MULTIPLIER",EQUIP_DUR_MULTIPLIER);
 tolua_module(tolua_S,"BIND_TYPE",0);
 tolua_beginmodule(tolua_S,"BIND_TYPE");
  tolua_constant(tolua_S,"BINDTYPE_NONE",BINDTYPE_NONE);
  tolua_constant(tolua_S,"BINDTYPE_BOU",BINDTYPE_BOU);
  tolua_constant(tolua_S,"BINDTYPE_BOE",BINDTYPE_BOE);
  tolua_constant(tolua_S,"BINDTYPE_BOP",BINDTYPE_BOP);
  tolua_constant(tolua_S,"BINDTYPE_BOT",BINDTYPE_BOT);
  tolua_constant(tolua_S,"BINDTYPE_BINDED",BINDTYPE_BINDED);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"PK_DROP_TYPE",0);
 tolua_beginmodule(tolua_S,"PK_DROP_TYPE");
  tolua_constant(tolua_S,"PKDROP_BY_CHANCE",PKDROP_BY_CHANCE);
  tolua_constant(tolua_S,"PKDROP_NOT_DROP",PKDROP_NOT_DROP);
  tolua_constant(tolua_S,"PKDROP_MUST_DROP",PKDROP_MUST_DROP);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"IDENTIFY_TYPE",0);
 tolua_beginmodule(tolua_S,"IDENTIFY_TYPE");
  tolua_constant(tolua_S,"IDENTIFY_TYPE_NO",IDENTIFY_TYPE_NO);
  tolua_constant(tolua_S,"IDENTIFY_TYPE_YES",IDENTIFY_TYPE_YES);
  tolua_constant(tolua_S,"IDENTIFY_TYPE_LEVEL_UP",IDENTIFY_TYPE_LEVEL_UP);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"CONTAINER_SLOT",0);
 tolua_beginmodule(tolua_S,"CONTAINER_SLOT");
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
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"NORMAL_EQUIP_SLOT",0);
 tolua_beginmodule(tolua_S,"NORMAL_EQUIP_SLOT");
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
 tolua_endmodule(tolua_S);
#ifndef TOLUA_DISABLE_tolua_enum_str_IsAppearance00
 tolua_function(tolua_S,"IsAppearance",tolua_enum_str_IsAppearance00);
#endif //#ifndef TOLUA_DISABLE
 tolua_module(tolua_S,"DEPOSIT_ITEM_SLOT",0);
 tolua_beginmodule(tolua_S,"DEPOSIT_ITEM_SLOT");
  tolua_constant(tolua_S,"DEPOSIT_SOUL_SLOT",DEPOSIT_SOUL_SLOT);
  tolua_constant(tolua_S,"DEPOSIT_EXP_SLOT",DEPOSIT_EXP_SLOT);
  tolua_constant(tolua_S,"DEPOSIT_ITEM_SLOT_TOTAL",DEPOSIT_ITEM_SLOT_TOTAL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"SOCKET_TYPE",0);
 tolua_beginmodule(tolua_S,"SOCKET_TYPE");
  tolua_constant(tolua_S,"SOCKET_NONE",SOCKET_NONE);
  tolua_constant(tolua_S,"SOCKET_RED",SOCKET_RED);
  tolua_constant(tolua_S,"SOCKET_YELLOW",SOCKET_YELLOW);
  tolua_constant(tolua_S,"SOCKET_BLUE",SOCKET_BLUE);
  tolua_constant(tolua_S,"SOCKET_GREEN",SOCKET_GREEN);
  tolua_constant(tolua_S,"SOCKET_PURPLE",SOCKET_PURPLE);
  tolua_constant(tolua_S,"SOCKET_COLORFUL",SOCKET_COLORFUL);
  tolua_constant(tolua_S,"SOCKET_TYPE_COUNT",SOCKET_TYPE_COUNT);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"EStallState",0);
 tolua_beginmodule(tolua_S,"EStallState");
  tolua_constant(tolua_S,"essNotOpen",essNotOpen);
  tolua_constant(tolua_S,"essPreparing",essPreparing);
  tolua_constant(tolua_S,"essOpen",essOpen);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"MAX_TRADE_SLOT",MAX_TRADE_SLOT);
 tolua_module(tolua_S,"ETradeState",0);
 tolua_beginmodule(tolua_S,"ETradeState");
  tolua_constant(tolua_S,"etsFree",etsFree);
  tolua_constant(tolua_S,"etsAsking",etsAsking);
  tolua_constant(tolua_S,"etsBeingAsked",etsBeingAsked);
  tolua_constant(tolua_S,"etsTrading",etsTrading);
  tolua_constant(tolua_S,"etsLocked",etsLocked);
  tolua_constant(tolua_S,"etsConfirmed",etsConfirmed);
  tolua_constant(tolua_S,"etsSuccess",etsSuccess);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"MAX_SOLD_ITEMS",MAX_SOLD_ITEMS);
 tolua_module(tolua_S,"EBlackMarketLimitType",0);
 tolua_beginmodule(tolua_S,"EBlackMarketLimitType");
  tolua_constant(tolua_S,"ebmltNone",ebmltNone);
  tolua_constant(tolua_S,"ebmltRole",ebmltRole);
  tolua_constant(tolua_S,"ebmltServer",ebmltServer);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"MAX_RUNE_COUNT",MAX_RUNE_COUNT);
 tolua_constant(tolua_S,"MAX_SOCKET_COUNT",MAX_SOCKET_COUNT);
 tolua_cclass(tolua_S,"DROP_CHANCE_DATA","DROP_CHANCE_DATA","",NULL);
 tolua_beginmodule(tolua_S,"DROP_CHANCE_DATA");
#ifndef TOLUA_DISABLE_tolua_enum_str_DROP_CHANCE_DATA_new00
  tolua_function(tolua_S,"new",tolua_enum_str_DROP_CHANCE_DATA_new00);
#endif //#ifndef TOLUA_DISABLE
  tolua_function(tolua_S,"new_local",tolua_enum_str_DROP_CHANCE_DATA_new00_local);
  tolua_function(tolua_S,".call",tolua_enum_str_DROP_CHANCE_DATA_new00_local);
  tolua_variable(tolua_S,"nDropGroupID",tolua_get_DROP_CHANCE_DATA_nDropGroupID,tolua_set_DROP_CHANCE_DATA_nDropGroupID);
  tolua_variable(tolua_S,"nDropChance",tolua_get_DROP_CHANCE_DATA_nDropChance,tolua_set_DROP_CHANCE_DATA_nDropChance);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"EGambleType",0);
 tolua_beginmodule(tolua_S,"EGambleType");
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
  tolua_constant(tolua_S,"egtReserved01",egtGambleItem);
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
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"CHAR_MOVE_STATE",0);
 tolua_beginmodule(tolua_S,"CHAR_MOVE_STATE");
  tolua_constant(tolua_S,"CMS_INVALID",CMS_INVALID);
  tolua_constant(tolua_S,"CMS_ACTIVE_MOVE",CMS_ACTIVE_MOVE);
  tolua_constant(tolua_S,"CMS_STAND",CMS_STAND);
  tolua_constant(tolua_S,"CMS_SIT",CMS_SIT);
  tolua_constant(tolua_S,"CMS_WALK",CMS_WALK);
  tolua_constant(tolua_S,"CMS_RUN",CMS_RUN);
  tolua_constant(tolua_S,"CMS_MOVE",CMS_MOVE);
  tolua_constant(tolua_S,"CMS_MINE",CMS_MINE);
  tolua_constant(tolua_S,"CMS_PASSIVE_MOVE",CMS_PASSIVE_MOVE);
  tolua_constant(tolua_S,"CMS_DASH",CMS_DASH);
  tolua_constant(tolua_S,"CMS_KNOCK_BACK",CMS_KNOCK_BACK);
  tolua_constant(tolua_S,"CMS_THROWN",CMS_THROWN);
  tolua_constant(tolua_S,"CMS_FREEZE",CMS_FREEZE);
  tolua_constant(tolua_S,"CMS_FEAR",CMS_FEAR);
  tolua_constant(tolua_S,"CMS_DIE",CMS_DIE);
  tolua_constant(tolua_S,"CMS_CLIENT_SHOW_TIME",CMS_CLIENT_SHOW_TIME);
  tolua_constant(tolua_S,"CMS_STALL",CMS_STALL);
  tolua_constant(tolua_S,"CMS_TOTAL",CMS_TOTAL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"CHAR_SPELL_STATE",0);
 tolua_beginmodule(tolua_S,"CHAR_SPELL_STATE");
  tolua_constant(tolua_S,"cspsInvalid",cspsInvalid);
  tolua_constant(tolua_S,"cspsIdle",cspsIdle);
  tolua_constant(tolua_S,"cspsCastingBegin",cspsCastingBegin);
  tolua_constant(tolua_S,"cspsChanneling",cspsChanneling);
  tolua_constant(tolua_S,"cspsPreparing",cspsPreparing);
  tolua_constant(tolua_S,"cspsPreAccumulating",cspsPreAccumulating);
  tolua_constant(tolua_S,"cspsAccumulating",cspsAccumulating);
  tolua_constant(tolua_S,"cspsBreaking",cspsBreaking);
  tolua_constant(tolua_S,"cspsOpening",cspsOpening);
  tolua_constant(tolua_S,"cspsCastingEnd",cspsCastingEnd);
  tolua_constant(tolua_S,"cspsHard",cspsHard);
  tolua_constant(tolua_S,"cspsTotal",cspsTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"CHAR_SEX_TYPE",0);
 tolua_beginmodule(tolua_S,"CHAR_SEX_TYPE");
  tolua_constant(tolua_S,"cstInvalid",cstInvalid);
  tolua_constant(tolua_S,"cstMale",cstMale);
  tolua_constant(tolua_S,"cstFemale",cstFemale);
  tolua_constant(tolua_S,"cstAsexual",cstAsexual);
  tolua_constant(tolua_S,"cstTotal",cstTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"CHAR_CLASS_TYPE",0);
 tolua_beginmodule(tolua_S,"CHAR_CLASS_TYPE");
  tolua_constant(tolua_S,"clsInvalid",clsInvalid);
  tolua_constant(tolua_S,"clsPlayerBegin",clsPlayerBegin);
  tolua_constant(tolua_S,"clsWarrior",clsWarrior);
  tolua_constant(tolua_S,"clsMage",clsMage);
  tolua_constant(tolua_S,"clsRogue",clsRogue);
  tolua_constant(tolua_S,"clsArcher",clsArcher);
  tolua_constant(tolua_S,"clsTaoist",clsTaoist);
  tolua_constant(tolua_S,"clsPlayerEnd",clsPlayerEnd);
  tolua_constant(tolua_S,"clsPlayerTotal",clsPlayerTotal);
  tolua_constant(tolua_S,"clsNpc",clsNpc);
  tolua_constant(tolua_S,"clsTotal",clsTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"CHAR_SPECIES_TYPE",0);
 tolua_beginmodule(tolua_S,"CHAR_SPECIES_TYPE");
  tolua_constant(tolua_S,"spcInvalid",spcInvalid);
  tolua_constant(tolua_S,"spcNone",spcNone);
  tolua_constant(tolua_S,"spcPlayer",spcPlayer);
  tolua_constant(tolua_S,"spcHuman",spcHuman);
  tolua_constant(tolua_S,"spcHumanlike",spcHumanlike);
  tolua_constant(tolua_S,"spcBeast",spcBeast);
  tolua_constant(tolua_S,"spcInsect",spcInsect);
  tolua_constant(tolua_S,"spcPlant",spcPlant);
  tolua_constant(tolua_S,"spcUndead",spcUndead);
  tolua_constant(tolua_S,"spcMachine",spcMachine);
  tolua_constant(tolua_S,"spcDragon",spcDragon);
  tolua_constant(tolua_S,"spcDemon",spcDemon);
  tolua_constant(tolua_S,"spcElements",spcElements);
  tolua_constant(tolua_S,"spcBuilding",spcBuilding);
  tolua_constant(tolua_S,"spcTotal",spcTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"CHAR_CC_FLAG",0);
 tolua_beginmodule(tolua_S,"CHAR_CC_FLAG");
  tolua_constant(tolua_S,"cclInvalid",cclInvalid);
  tolua_constant(tolua_S,"cclBegin",cclBegin);
  tolua_constant(tolua_S,"cclStun",cclStun);
  tolua_constant(tolua_S,"cclFear",cclFear);
  tolua_constant(tolua_S,"cclFury",cclFury);
  tolua_constant(tolua_S,"cclDazzle",cclDazzle);
  tolua_constant(tolua_S,"cclSlowed",cclSlowed);
  tolua_constant(tolua_S,"cclKnockBack",cclKnockBack);
  tolua_constant(tolua_S,"cclFreeze",cclFreeze);
  tolua_constant(tolua_S,"cclSeduced",cclSeduced);
  tolua_constant(tolua_S,"cclInvincible",cclInvincible);
  tolua_constant(tolua_S,"cclLeech",cclLeech);
  tolua_constant(tolua_S,"cclTransportationRing",cclTransportationRing);
  tolua_constant(tolua_S,"cclProbeNecklace",cclProbeNecklace);
  tolua_constant(tolua_S,"cclMemoSuit",cclMemoSuit);
  tolua_constant(tolua_S,"cclInvisible",cclInvisible);
  tolua_constant(tolua_S,"cclTotal",cclTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"CHAR_FLAG",0);
 tolua_beginmodule(tolua_S,"CHAR_FLAG");
  tolua_constant(tolua_S,"cfInvalid",cfInvalid);
  tolua_constant(tolua_S,"cfNotInCombat",cfNotInCombat);
  tolua_constant(tolua_S,"cfInCombat",cfInCombat);
  tolua_constant(tolua_S,"cfCounter",cfCounter);
  tolua_constant(tolua_S,"cfOnMount",cfOnMount);
  tolua_constant(tolua_S,"cfCannotBeThrown",cfCannotBeThrown);
  tolua_constant(tolua_S,"cfTempUndead",cfTempUndead);
  tolua_constant(tolua_S,"cfImmunePhyAtk",cfImmunePhyAtk);
  tolua_constant(tolua_S,"cfImmuleMagAtk",cfImmuleMagAtk);
  tolua_constant(tolua_S,"cfCanNotBeSelectedAsTarget",cfCanNotBeSelectedAsTarget);
  tolua_constant(tolua_S,"cfBTDenyDie",cfBTDenyDie);
  tolua_constant(tolua_S,"cfBTHasFlee",cfBTHasFlee);
  tolua_constant(tolua_S,"cfAuraInvalid",cfAuraInvalid);
  tolua_constant(tolua_S,"cfCombatPoseOn",cfCombatPoseOn);
  tolua_constant(tolua_S,"cfImmunePassiveMove",cfImmunePassiveMove);
  tolua_constant(tolua_S,"cfFury",cfFury);
  tolua_constant(tolua_S,"cfDamageStatistics",cfDamageStatistics);
  tolua_constant(tolua_S,"cfNeverBeHit",cfNeverBeHit);
  tolua_constant(tolua_S,"cfTotal",cfTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"CHAR_STANCE_FLAG",0);
 tolua_beginmodule(tolua_S,"CHAR_STANCE_FLAG");
  tolua_constant(tolua_S,"csfInvalid",csfInvalid);
  tolua_constant(tolua_S,"csfStand",csfStand);
  tolua_constant(tolua_S,"csfUp",csfUp);
  tolua_constant(tolua_S,"csfDown",csfDown);
  tolua_constant(tolua_S,"csfTotal",csfTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"CHAR_STIFF_BITS",0);
 tolua_beginmodule(tolua_S,"CHAR_STIFF_BITS");
  tolua_constant(tolua_S,"cstfBegin",cstfBegin);
  tolua_constant(tolua_S,"cstfFreeze",cstfFreeze);
  tolua_constant(tolua_S,"cstfKnockBack",cstfKnockBack);
  tolua_constant(tolua_S,"cstfSilent",cstfSilent);
  tolua_constant(tolua_S,"cstfTotal",cstfTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"CHAR_DIE_REASON",0);
 tolua_beginmodule(tolua_S,"CHAR_DIE_REASON");
  tolua_constant(tolua_S,"cdrInvalid",cdrInvalid);
  tolua_constant(tolua_S,"cdrDefault",cdrDefault);
  tolua_constant(tolua_S,"cdrSpell",cdrSpell);
  tolua_constant(tolua_S,"cdrAura",cdrAura);
  tolua_constant(tolua_S,"cdrRecovery",cdrRecovery);
  tolua_constant(tolua_S,"cdrTimeToDie",cdrTimeToDie);
  tolua_constant(tolua_S,"cdrAIBehavior",cdrAIBehavior);
  tolua_constant(tolua_S,"cdrSilent",cdrSilent);
  tolua_constant(tolua_S,"cdrLeech",cdrLeech);
  tolua_constant(tolua_S,"cdrSuicide",cdrSuicide);
  tolua_constant(tolua_S,"cdrCount",cdrCount);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"CHAR_REVIVE_TYPE",0);
 tolua_beginmodule(tolua_S,"CHAR_REVIVE_TYPE");
  tolua_constant(tolua_S,"crtInvalid",crtInvalid);
  tolua_constant(tolua_S,"crtAtCurrentPos",crtAtCurrentPos);
  tolua_constant(tolua_S,"crtInstant",crtInstant);
  tolua_constant(tolua_S,"crtFree",crtFree);
  tolua_constant(tolua_S,"crtTotal",crtTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"SCENE_OBJECT_APPEAR_TYPE",0);
 tolua_beginmodule(tolua_S,"SCENE_OBJECT_APPEAR_TYPE");
  tolua_constant(tolua_S,"soatInvalid",soatInvalid);
  tolua_constant(tolua_S,"soatLogin",soatLogin);
  tolua_constant(tolua_S,"soatInRange",soatInRange);
  tolua_constant(tolua_S,"soatSpawn",soatSpawn);
  tolua_constant(tolua_S,"soatRevive",soatRevive);
  tolua_constant(tolua_S,"soatNoPerforSpawn",soatNoPerforSpawn);
  tolua_constant(tolua_S,"soatTotal",soatTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"SCENE_OBJECT_DISAPPEAR_TYPE",0);
 tolua_beginmodule(tolua_S,"SCENE_OBJECT_DISAPPEAR_TYPE");
  tolua_constant(tolua_S,"sodtInvalid",sodtInvalid);
  tolua_constant(tolua_S,"sodtLeaveScene",sodtLeaveScene);
  tolua_constant(tolua_S,"sodtOutOfRange",sodtOutOfRange);
  tolua_constant(tolua_S,"sodtTotal",sodtTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"ENUM_COMBAT_STAT_ENTRY",0);
 tolua_beginmodule(tolua_S,"ENUM_COMBAT_STAT_ENTRY");
  tolua_constant(tolua_S,"escsInvalid",escsInvalid);
  tolua_constant(tolua_S,"escsDeathCount",escsDeathCount);
  tolua_constant(tolua_S,"escsRoleKillCount",escsRoleKillCount);
  tolua_constant(tolua_S,"escsNpcKillCount",escsNpcKillCount);
  tolua_constant(tolua_S,"escsEliteNpcKillCount",escsEliteNpcKillCount);
  tolua_constant(tolua_S,"escsBossKillCount",escsBossKillCount);
  tolua_constant(tolua_S,"escsDoodadKillCount",escsDoodadKillCount);
  tolua_constant(tolua_S,"escsTotalHeal",escsTotalHeal);
  tolua_constant(tolua_S,"escsTotalDamage",escsTotalDamage);
  tolua_constant(tolua_S,"escsPhyAtkCritCount",escsPhyAtkCritCount);
  tolua_constant(tolua_S,"escsMagAtkCritCount",escsMagAtkCritCount);
  tolua_constant(tolua_S,"escsScore1",escsScore1);
  tolua_constant(tolua_S,"escsScore2",escsScore2);
  tolua_constant(tolua_S,"escsTotalScore",escsTotalScore);
  tolua_constant(tolua_S,"escsTotal",escsTotal);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"INVALID_OBJECT_ID",INVALID_OBJECT_ID);
 tolua_constant(tolua_S,"OBJECT_TYPE_MASK",OBJECT_TYPE_MASK);
 tolua_constant(tolua_S,"OBJECT_ID_MASK",OBJECT_ID_MASK);
 tolua_constant(tolua_S,"MAX_OBJECT_ID",MAX_OBJECT_ID);
 tolua_module(tolua_S,"OBJECT_TYPE",0);
 tolua_beginmodule(tolua_S,"OBJECT_TYPE");
  tolua_constant(tolua_S,"otInvalid",otInvalid);
  tolua_constant(tolua_S,"otRole",otRole);
  tolua_constant(tolua_S,"otNpc",otNpc);
  tolua_constant(tolua_S,"otHero",otHero);
  tolua_constant(tolua_S,"otDoodad",otDoodad);
  tolua_constant(tolua_S,"otMissile",otMissile);
  tolua_constant(tolua_S,"otDrop",otDrop);
  tolua_constant(tolua_S,"otGuild",otGuild);
  tolua_constant(tolua_S,"otTeam",otTeam);
  tolua_constant(tolua_S,"otBattleTeam",otBattleTeam);
  tolua_constant(tolua_S,"otChannel",otChannel);
  tolua_constant(tolua_S,"otTrumpet",otTrumpet);
  tolua_constant(tolua_S,"otTotal",otTotal);
 tolua_endmodule(tolua_S);
#ifndef TOLUA_DISABLE_tolua_enum_str_MakeObjectID00
 tolua_function(tolua_S,"MakeObjectID",tolua_enum_str_MakeObjectID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_enum_str_GetTypeFromID00
 tolua_function(tolua_S,"GetTypeFromID",tolua_enum_str_GetTypeFromID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_enum_str_GetIndexFromID00
 tolua_function(tolua_S,"GetIndexFromID",tolua_enum_str_GetIndexFromID00);
#endif //#ifndef TOLUA_DISABLE
 tolua_constant(tolua_S,"MAX_NORMAL_QUEST_COUNT",MAX_NORMAL_QUEST_COUNT);
 tolua_constant(tolua_S,"MAX_NORMAL_QUEST_BYTE_SIZE",MAX_NORMAL_QUEST_BYTE_SIZE);
 tolua_constant(tolua_S,"REPEAT_QUEST_START_ID",REPEAT_QUEST_START_ID);
 tolua_constant(tolua_S,"MAX_REPEAT_QUEST_COUNT",MAX_REPEAT_QUEST_COUNT);
 tolua_constant(tolua_S,"MAX_REPEAT_QUEST_CYCLE",MAX_REPEAT_QUEST_CYCLE);
 tolua_constant(tolua_S,"MAX_ACCEPTED_NORMAL_QUEST_COUNT",MAX_ACCEPTED_NORMAL_QUEST_COUNT);
 tolua_constant(tolua_S,"MAX_ACCEPTED_EMERGENCY_QUEST_COUNT",MAX_ACCEPTED_EMERGENCY_QUEST_COUNT);
 tolua_constant(tolua_S,"MAX_CONDITION_PER_QUEST",MAX_CONDITION_PER_QUEST);
 tolua_constant(tolua_S,"MAX_REWARD_PER_QUEST",MAX_REWARD_PER_QUEST);
 tolua_constant(tolua_S,"MAX_SELECTABLE_REWARD_COUNT",MAX_SELECTABLE_REWARD_COUNT);
 tolua_constant(tolua_S,"MAX_DIALOG_CONTENT_LEN",MAX_DIALOG_CONTENT_LEN);
 tolua_constant(tolua_S,"INVALID_QUEST_ID",INVALID_QUEST_ID);
 tolua_constant(tolua_S,"MAX_FLY_SPOT_PER_QUEST",MAX_FLY_SPOT_PER_QUEST);
 tolua_constant(tolua_S,"CIRCLE_QUEST_START_ID",CIRCLE_QUEST_START_ID);
 tolua_constant(tolua_S,"EMERGENCY_QUEST_START_ID",EMERGENCY_QUEST_START_ID);
 tolua_constant(tolua_S,"MAX_EMERGENCY_QUEST_COUNT",MAX_EMERGENCY_QUEST_COUNT);
 tolua_constant(tolua_S,"MAX_EMERGENCY_QUEST_COMPLETE_PER_DAY",MAX_EMERGENCY_QUEST_COMPLETE_PER_DAY);
 tolua_constant(tolua_S,"MAX_EMERGENCY_QUEST_PER_ROLE",MAX_EMERGENCY_QUEST_PER_ROLE);
 tolua_constant(tolua_S,"MAX_CHECK_VAR_COUNT",MAX_CHECK_VAR_COUNT);
 tolua_constant(tolua_S,"MAX_KILL_NPC_QUEST_COUNT",MAX_KILL_NPC_QUEST_COUNT);
 tolua_constant(tolua_S,"MAX_KILL_COUNT_PER_NPC",MAX_KILL_COUNT_PER_NPC);
 tolua_module(tolua_S,"QUEST_ACCEPT_TYPE",0);
 tolua_beginmodule(tolua_S,"QUEST_ACCEPT_TYPE");
  tolua_constant(tolua_S,"qatInvalid",qatInvalid);
  tolua_constant(tolua_S,"qatNpc",qatNpc);
  tolua_constant(tolua_S,"qatShare",qatShare);
  tolua_constant(tolua_S,"qatPublish",qatPublish);
  tolua_constant(tolua_S,"qatEmegency",qatEmegency);
  tolua_constant(tolua_S,"qatItem",qatItem);
  tolua_constant(tolua_S,"qatTotal",qatTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"QUEST_TIME_TYPE",0);
 tolua_beginmodule(tolua_S,"QUEST_TIME_TYPE");
  tolua_constant(tolua_S,"qttInvalid",qttInvalid);
  tolua_constant(tolua_S,"qttNoReset",qttNoReset);
  tolua_constant(tolua_S,"qttDay",qttDay);
  tolua_constant(tolua_S,"qttWeek",qttWeek);
  tolua_constant(tolua_S,"qttTotal",qttTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"QUEST_RELATION_TYPE",0);
 tolua_beginmodule(tolua_S,"QUEST_RELATION_TYPE");
  tolua_constant(tolua_S,"qrtInvalid",qrtInvalid);
  tolua_constant(tolua_S,"qrtMaster",qrtMaster);
  tolua_constant(tolua_S,"qrtDisciple",qrtDisciple);
  tolua_constant(tolua_S,"qrtHusband",qrtHusband);
  tolua_constant(tolua_S,"qrtWife",qrtWife);
  tolua_constant(tolua_S,"qrtGuildLeader",qrtGuildLeader);
  tolua_constant(tolua_S,"qrtGuildMember",qrtGuildMember);
  tolua_constant(tolua_S,"qrtTeamMaster",qrtTeamMaster);
  tolua_constant(tolua_S,"qrtTeamHusband",qrtTeamHusband);
  tolua_constant(tolua_S,"qrtTeamGuild",qrtTeamGuild);
  tolua_constant(tolua_S,"qrtTotal",qrtTotal);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"QUEST_TYPE",0);
 tolua_beginmodule(tolua_S,"QUEST_TYPE");
  tolua_constant(tolua_S,"qtInvalid",qtInvalid);
  tolua_constant(tolua_S,"qtTrunk",qtTrunk);
  tolua_constant(tolua_S,"qtBranch",qtBranch);
  tolua_constant(tolua_S,"qtDaily",qtDaily);
  tolua_constant(tolua_S,"qtReward",qtReward);
  tolua_constant(tolua_S,"qtCircle",qtCircle);
  tolua_constant(tolua_S,"qtActivity",qtActivity);
  tolua_constant(tolua_S,"qtGuild",qtGuild);
  tolua_constant(tolua_S,"qtMaster",qtMaster);
  tolua_constant(tolua_S,"qtWedding",qtWedding);
  tolua_constant(tolua_S,"qtAdventure",qtAdventure);
  tolua_constant(tolua_S,"qtGuide",qtGuide);
  tolua_constant(tolua_S,"qtEmegency",qtEmegency);
  tolua_constant(tolua_S,"qtTotal",qtTotal);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"GUILD_CREATER_LEVEL",GUILD_CREATER_LEVEL);
 tolua_constant(tolua_S,"GUILD_CREATE_MONEY",GUILD_CREATE_MONEY);
 tolua_constant(tolua_S,"GUILD_CREATE_ITEM_ID",GUILD_CREATE_ITEM_ID);
 tolua_constant(tolua_S,"GUILD_CREATE_ITEM_NUM",GUILD_CREATE_ITEM_NUM);
 tolua_constant(tolua_S,"MAX_GUILD_NUM_SYSTEM_LIMIT",MAX_GUILD_NUM_SYSTEM_LIMIT);
 tolua_constant(tolua_S,"MAX_APPLY_GUILD_ROLE_NUM",MAX_APPLY_GUILD_ROLE_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_MEMBER_COUNT",GUILD_MAX_MEMBER_COUNT);
 tolua_constant(tolua_S,"MAX_VIEW_GUILD_LIST_COUNT",MAX_VIEW_GUILD_LIST_COUNT);
 tolua_constant(tolua_S,"ROLE_MAX_APPLICATION",ROLE_MAX_APPLICATION);
 tolua_constant(tolua_S,"GUILD_MAX_ALLIANCE_NUM",GUILD_MAX_ALLIANCE_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_ENEMY_NUM",GUILD_MAX_ENEMY_NUM);
 tolua_constant(tolua_S,"GUILD_DATA_NTF_HISTORY_NUM",GUILD_DATA_NTF_HISTORY_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_CHEST_NTF_NUM",GUILD_MAX_CHEST_NTF_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_HISTORY_EVENT_NUM",GUILD_MAX_HISTORY_EVENT_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_STORAGE_EVENT_NUM",GUILD_MAX_STORAGE_EVENT_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_CHEST_EVENT_NUM",GUILD_MAX_CHEST_EVENT_NUM);
 tolua_constant(tolua_S,"GUILD_STORAGE_MAX_ITEM_NUM_PER_TAG",GUILD_STORAGE_MAX_ITEM_NUM_PER_TAG);
 tolua_constant(tolua_S,"GUILD_STORAGE_MAX_TAG_NUM",GUILD_STORAGE_MAX_TAG_NUM);
 tolua_constant(tolua_S,"GUILD_STORAGE_LOW_LIMIT",GUILD_STORAGE_LOW_LIMIT);
 tolua_constant(tolua_S,"GUILD_MAX_APPLY_ALLIANCE_NUM",GUILD_MAX_APPLY_ALLIANCE_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_WELFARE_AURA_COUNT",GUILD_MAX_WELFARE_AURA_COUNT);
 tolua_constant(tolua_S,"GUILD_MAX_UPGRADE_AURA_COUNT",GUILD_MAX_UPGRADE_AURA_COUNT);
 tolua_constant(tolua_S,"GUILD_MAX_UPGRADE_BUILDING_COUNT",GUILD_MAX_UPGRADE_BUILDING_COUNT);
 tolua_constant(tolua_S,"GUILD_MAX_DUNGEON_COUNT",GUILD_MAX_DUNGEON_COUNT);
 tolua_constant(tolua_S,"ONE_DAY_SECOND",ONE_DAY_SECOND);
 tolua_constant(tolua_S,"GUILD_UPDATE_RANKLIST_STARTTIME",GUILD_UPDATE_RANKLIST_STARTTIME);
 tolua_constant(tolua_S,"GUILD_UPDATE_RANKLIST_ENDIME",GUILD_UPDATE_RANKLIST_ENDIME);
 tolua_constant(tolua_S,"GUILD_DUNGEON_AWARD_NUM",GUILD_DUNGEON_AWARD_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_ITEM_BUFFER_LENGTH",GUILD_MAX_ITEM_BUFFER_LENGTH);
 tolua_constant(tolua_S,"GUILD_MAX_BUILDING_LEVEL",GUILD_MAX_BUILDING_LEVEL);
 tolua_constant(tolua_S,"GUILD_MAX_BUILDING_NUM",GUILD_MAX_BUILDING_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_GATE_NUM",GUILD_MAX_GATE_NUM);
 tolua_constant(tolua_S,"MAX_SABAC_ENROLL_COUNT",MAX_SABAC_ENROLL_COUNT);
 tolua_constant(tolua_S,"GUILD_MAX_ACHIEVEMENT_NUM",GUILD_MAX_ACHIEVEMENT_NUM);
 tolua_constant(tolua_S,"GUILD_MAX_ACHI_ARRAY_LENGTH",GUILD_MAX_ACHI_ARRAY_LENGTH);
 tolua_constant(tolua_S,"GUILD_WAR_RECORD_NUM_PER_PAGE",GUILD_WAR_RECORD_NUM_PER_PAGE);
 tolua_constant(tolua_S,"MAX_TIME_DEVIATION",MAX_TIME_DEVIATION);
 tolua_constant(tolua_S,"MAX_GUILD_CORE_MEMBER",MAX_GUILD_CORE_MEMBER);
 tolua_module(tolua_S,"GUILD_NOTIFY_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_NOTIFY_TYPE");
  tolua_constant(tolua_S,"GUILD_NOTIFY_ROLE_APP",GUILD_NOTIFY_ROLE_APP);
  tolua_constant(tolua_S,"GUILD_NOTIFY_DIPLOMAT_APP",GUILD_NOTIFY_DIPLOMAT_APP);
  tolua_constant(tolua_S,"GUILD_NOTIFY_MATCH_WAR",GUILD_NOTIFY_MATCH_WAR);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_VIEW_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_VIEW_TYPE");
  tolua_constant(tolua_S,"GUILD_VIEW_UP",GUILD_VIEW_UP);
  tolua_constant(tolua_S,"GUILD_VIEW_DOWN",GUILD_VIEW_DOWN);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_POSITION_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_POSITION_TYPE");
  tolua_constant(tolua_S,"GUILD_POSITION_NONE",GUILD_POSITION_NONE);
  tolua_constant(tolua_S,"GUILD_POSITION_LEADER",GUILD_POSITION_LEADER);
  tolua_constant(tolua_S,"GUILD_POSITION_SUBLEADER",GUILD_POSITION_SUBLEADER);
  tolua_constant(tolua_S,"GUILD_POSITION_ELDER",GUILD_POSITION_ELDER);
  tolua_constant(tolua_S,"GUILD_POSITION_BISHOP",GUILD_POSITION_BISHOP);
  tolua_constant(tolua_S,"GUILD_POSITION_DEACON",GUILD_POSITION_DEACON);
  tolua_constant(tolua_S,"GUILD_POSITION_SUBDEACON",GUILD_POSITION_SUBDEACON);
  tolua_constant(tolua_S,"GUILD_POSITION_CIVILIAN",GUILD_POSITION_CIVILIAN);
  tolua_constant(tolua_S,"GUILD_POSITION_TOTAL",GUILD_POSITION_TOTAL);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"GUILD_POSITION_COUNT",GUILD_POSITION_COUNT);
 tolua_module(tolua_S,"GUILD_POSITION_RIGHT_FIELD",0);
 tolua_beginmodule(tolua_S,"GUILD_POSITION_RIGHT_FIELD");
  tolua_constant(tolua_S,"G_POS_RIGHT_NONE",G_POS_RIGHT_NONE);
  tolua_constant(tolua_S,"G_POS_RIGHT_INVITE",G_POS_RIGHT_INVITE);
  tolua_constant(tolua_S,"G_POS_RIGHT_RECRUIT",G_POS_RIGHT_RECRUIT);
  tolua_constant(tolua_S,"G_POS_RIGHT_FORBID_CHAT",G_POS_RIGHT_FORBID_CHAT);
  tolua_constant(tolua_S,"G_POS_RIGHT_NOTICE",G_POS_RIGHT_NOTICE);
  tolua_constant(tolua_S,"G_POS_RIGHT_SET_STORAGE_RIGHT",G_POS_RIGHT_SET_STORAGE_RIGHT);
  tolua_constant(tolua_S,"G_POS_RIGHT_OPEN_DUNGEON",G_POS_RIGHT_OPEN_DUNGEON);
  tolua_constant(tolua_S,"G_POS_RIGHT_UPGRADE_BUILDING",G_POS_RIGHT_UPGRADE_BUILDING);
  tolua_constant(tolua_S,"G_POS_RIGHT_UPGRADE_WELFARE",G_POS_RIGHT_UPGRADE_WELFARE);
  tolua_constant(tolua_S,"G_POS_RIGHT_CHANGE_POS",G_POS_RIGHT_CHANGE_POS);
  tolua_constant(tolua_S,"G_POS_RIGHT_BANISH",G_POS_RIGHT_BANISH);
  tolua_constant(tolua_S,"G_POS_RIGHT_DIPLOMAT",G_POS_RIGHT_DIPLOMAT);
  tolua_constant(tolua_S,"G_POS_RIGHT_ACTIVITY",G_POS_RIGHT_ACTIVITY);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_STORAGE_RIGHT_FLAG",0);
 tolua_beginmodule(tolua_S,"GUILD_STORAGE_RIGHT_FLAG");
  tolua_constant(tolua_S,"G_STORAGE_1_POP",G_STORAGE_1_POP);
  tolua_constant(tolua_S,"G_STORAGE_2_POP",G_STORAGE_2_POP);
  tolua_constant(tolua_S,"G_STORAGE_3_POP",G_STORAGE_3_POP);
  tolua_constant(tolua_S,"G_STORAGE_4_POP",G_STORAGE_4_POP);
  tolua_constant(tolua_S,"G_STORAGE_5_POP",G_STORAGE_5_POP);
  tolua_constant(tolua_S,"G_STORAGE_6_POP",G_STORAGE_6_POP);
  tolua_constant(tolua_S,"G_STORAGE_1_PUSH",G_STORAGE_1_PUSH);
  tolua_constant(tolua_S,"G_STORAGE_2_PUSH",G_STORAGE_2_PUSH);
  tolua_constant(tolua_S,"G_STORAGE_3_PUSH",G_STORAGE_3_PUSH);
  tolua_constant(tolua_S,"G_STORAGE_4_PUSH",G_STORAGE_4_PUSH);
  tolua_constant(tolua_S,"G_STORAGE_5_PUSH",G_STORAGE_5_PUSH);
  tolua_constant(tolua_S,"G_STORAGE_6_PUSH",G_STORAGE_6_PUSH);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_FLAG_FIELD",0);
 tolua_beginmodule(tolua_S,"GUILD_FLAG_FIELD");
  tolua_constant(tolua_S,"GUILD_FLAG_IS_CHAT_FORBIDDEN",GUILD_FLAG_IS_CHAT_FORBIDDEN);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_DIPLOMATIC_TIME_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_DIPLOMATIC_TIME_TYPE");
  tolua_constant(tolua_S,"G_DIPLOMATIC_TIME_1",G_DIPLOMATIC_TIME_1);
  tolua_constant(tolua_S,"G_DIPLOMATIC_TIME_2",G_DIPLOMATIC_TIME_2);
  tolua_constant(tolua_S,"G_DIPLOMATIC_TIME_3",G_DIPLOMATIC_TIME_3);
  tolua_constant(tolua_S,"G_DIPLOMATIC_TIME_4",G_DIPLOMATIC_TIME_4);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_REVERT_APPLY_ENUM",0);
 tolua_beginmodule(tolua_S,"GUILD_REVERT_APPLY_ENUM");
  tolua_constant(tolua_S,"GUILD_REVERT_REFUSE",GUILD_REVERT_REFUSE);
  tolua_constant(tolua_S,"GUILD_REVERT_AGREE",GUILD_REVERT_AGREE);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_FORBID_CHAT_ENUM",0);
 tolua_beginmodule(tolua_S,"GUILD_FORBID_CHAT_ENUM");
  tolua_constant(tolua_S,"GUILD_CHAT_FORBID",GUILD_CHAT_FORBID);
  tolua_constant(tolua_S,"GUILD_CHAT_UNFORBID",GUILD_CHAT_UNFORBID);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_RESOURCE_CHANGE_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_RESOURCE_CHANGE_TYPE");
  tolua_constant(tolua_S,"GUILD_RES_ADD_COUNT",GUILD_RES_ADD_COUNT);
  tolua_constant(tolua_S,"GUILD_RES_DEC_COUNT",GUILD_RES_DEC_COUNT);
  tolua_constant(tolua_S,"GUILD_RES_ADD_PERCENT",GUILD_RES_ADD_PERCENT);
  tolua_constant(tolua_S,"GUILD_RES_DEC_PERCENT",GUILD_RES_DEC_PERCENT);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_ATTR_ENUM",0);
 tolua_beginmodule(tolua_S,"GUILD_ATTR_ENUM");
  tolua_constant(tolua_S,"GUILD_ATTR_BEGIN",GUILD_ATTR_BEGIN);
  tolua_constant(tolua_S,"GUILD_ATTR_MONEY",GUILD_ATTR_MONEY);
  tolua_constant(tolua_S,"GUILD_ATTR_LEVEL",GUILD_ATTR_LEVEL);
  tolua_constant(tolua_S,"GUILD_ATTR_SALARY",GUILD_ATTR_SALARY);
  tolua_constant(tolua_S,"GUILD_ATTR_HERB",GUILD_ATTR_HERB);
  tolua_constant(tolua_S,"GUILD_ATTR_WOOD",GUILD_ATTR_WOOD);
  tolua_constant(tolua_S,"GUILD_ATTR_CRYSTAL",GUILD_ATTR_CRYSTAL);
  tolua_constant(tolua_S,"GUILD_ATTR_SILVER",GUILD_ATTR_SILVER);
  tolua_constant(tolua_S,"GUILD_ATTR_PROSPERITY",GUILD_ATTR_PROSPERITY);
  tolua_constant(tolua_S,"GUILD_ATTR_ATTACK_CD",GUILD_ATTR_ATTACK_CD);
  tolua_constant(tolua_S,"GUILD_ATTR_PROTECTION_TIME",GUILD_ATTR_PROTECTION_TIME);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_JOIN_AGREE_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_JOIN_AGREE_TYPE");
  tolua_constant(tolua_S,"GUILD_AGREE_BY_APPLY",GUILD_AGREE_BY_APPLY);
  tolua_constant(tolua_S,"GUILD_AGREE_BY_INVITE",GUILD_AGREE_BY_INVITE);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_LEAVE_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_LEAVE_TYPE");
  tolua_constant(tolua_S,"GUILD_LEAVE_ACTIVE",GUILD_LEAVE_ACTIVE);
  tolua_constant(tolua_S,"GUILD_LEAVE_PASSIVE",GUILD_LEAVE_PASSIVE);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_DIPLOMAT_OP_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_DIPLOMAT_OP_TYPE");
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_NEUTRALLY",GUILD_DIPLOMAT_NEUTRALLY);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_ALLIANCE",GUILD_DIPLOMAT_ALLIANCE);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_ENEMY",GUILD_DIPLOMAT_ENEMY);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_DIPLOMAT_TIME_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_DIPLOMAT_TIME_TYPE");
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_TIME_BEGIN",GUILD_DIPLOMAT_TIME_BEGIN);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_TIME_ONE",GUILD_DIPLOMAT_TIME_ONE);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_TIME_THREE",GUILD_DIPLOMAT_TIME_THREE);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_TIME_SEVEN",GUILD_DIPLOMAT_TIME_SEVEN);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_TIME_THIRTY",GUILD_DIPLOMAT_TIME_THIRTY);
  tolua_constant(tolua_S,"GUILD_DIPLOMAT_TIME_END",GUILD_DIPLOMAT_TIME_END);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_HISTORY_EVENT_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_HISTORY_EVENT_TYPE");
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BEGIN",GUILD_HE_TYPE_BEGIN);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_CREATE",GUILD_HE_TYPE_CREATE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_JOIN",GUILD_HE_TYPE_JOIN);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_LEAVE",GUILD_HE_TYPE_LEAVE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BANISH",GUILD_HE_TYPE_BANISH);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_POSITION_CHANGE",GUILD_HE_TYPE_POSITION_CHANGE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BUILDING_LVLUP",GUILD_HE_TYPE_BUILDING_LVLUP);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_SKILL_LVLUP",GUILD_HE_TYPE_SKILL_LVLUP);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_DEMISE",GUILD_HE_TYPE_DEMISE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_UNION",GUILD_HE_TYPE_UNION);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_ENEMY",GUILD_HE_TYPE_ENEMY);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_WAR",GUILD_HE_TYPE_WAR);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BUILDING_CREATE",GUILD_HE_TYPE_BUILDING_CREATE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BUILDING_DESTORY",GUILD_HE_TYPE_BUILDING_DESTORY);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BUILDING_DEL",GUILD_HE_TYPE_BUILDING_DEL);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_BUILDING_REVIVE",GUILD_HE_TYPE_BUILDING_REVIVE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_ATTACK_SUCC",GUILD_HE_TYPE_ATTACK_SUCC);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_ATTACK_FAILED",GUILD_HE_TYPE_ATTACK_FAILED);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_DEFEND_SUCC",GUILD_HE_TYPE_DEFEND_SUCC);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_DEFEND_FAILED",GUILD_HE_TYPE_DEFEND_FAILED);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_OPEN_ACTIVITY",GUILD_HE_TYPE_OPEN_ACTIVITY);
  tolua_constant(tolua_S,"GUILD_HE_CANCEL_ALLIANCE",GUILD_HE_CANCEL_ALLIANCE);
  tolua_constant(tolua_S,"GUILD_HE_TYPE_END",GUILD_HE_TYPE_END);
  tolua_constant(tolua_S,"GUILD_CHEST_BEGIN",GUILD_CHEST_BEGIN);
  tolua_constant(tolua_S,"GUILD_CHEST_CREATE_BUILDING",GUILD_CHEST_CREATE_BUILDING);
  tolua_constant(tolua_S,"GUILD_CHEST_ACTIVITY",GUILD_CHEST_ACTIVITY);
  tolua_constant(tolua_S,"GUILD_CHEST_CONTRIBUTE",GUILD_CHEST_CONTRIBUTE);
  tolua_constant(tolua_S,"GUILD_CHEST_B_UPGRADE",GUILD_CHEST_B_UPGRADE);
  tolua_constant(tolua_S,"GUILD_CHEST_W_UPGRADE",GUILD_CHEST_W_UPGRADE);
  tolua_constant(tolua_S,"GUILD_CHEST_ALLIANCE",GUILD_CHEST_ALLIANCE);
  tolua_constant(tolua_S,"GUILD_CHEST_ARMY",GUILD_CHEST_ARMY);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_SACK_A_1",GUILD_CHEST_WAR_SACK_A_1);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_SACK_A_2",GUILD_CHEST_WAR_SACK_A_2);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_SACK_D_1",GUILD_CHEST_WAR_SACK_D_1);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_SACK_D_2",GUILD_CHEST_WAR_SACK_D_2);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_WIN",GUILD_CHEST_WAR_WIN);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_LOSE",GUILD_CHEST_WAR_LOSE);
  tolua_constant(tolua_S,"GUILD_CHEST_CANCEL_BUILDING_UPGRADE",GUILD_CHEST_CANCEL_BUILDING_UPGRADE);
  tolua_constant(tolua_S,"GUILD_CHEST_CANCEL_WELFARE_UPGRADE",GUILD_CHEST_CANCEL_WELFARE_UPGRADE);
  tolua_constant(tolua_S,"GUILD_CHEST_DEL_BUILDING",GUILD_CHEST_DEL_BUILDING);
  tolua_constant(tolua_S,"GUILD_CHEST_OPEN_DUNGEON",GUILD_CHEST_OPEN_DUNGEON);
  tolua_constant(tolua_S,"GUILD_CHEST_COMPLETE_DUNGEON",GUILD_CHEST_COMPLETE_DUNGEON);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_PLUNDER",GUILD_CHEST_WAR_PLUNDER);
  tolua_constant(tolua_S,"GUILD_CHEST_WAR_PLUNDER_EXTRA",GUILD_CHEST_WAR_PLUNDER_EXTRA);
  tolua_constant(tolua_S,"GUILD_CHEST_ROUTINE_CONSUME",GUILD_CHEST_ROUTINE_CONSUME);
  tolua_constant(tolua_S,"GUILD_CHEST_DECLARE_WAR",GUILD_CHEST_DECLARE_WAR);
  tolua_constant(tolua_S,"GUILD_CHEST_MATCH_WAR",GUILD_CHEST_MATCH_WAR);
  tolua_constant(tolua_S,"GUILD_CHEST_BUILDING_DAMAGE",GUILD_CHEST_BUILDING_DAMAGE);
  tolua_constant(tolua_S,"GUILD_CHEST_GM",GUILD_CHEST_GM);
  tolua_constant(tolua_S,"GUILD_CHEST_END",GUILD_CHEST_END);
  tolua_constant(tolua_S,"STORAGE_HE_TYPE_BEGIN",STORAGE_HE_TYPE_BEGIN);
  tolua_constant(tolua_S,"STORAGE_HE_TYPE_PUSH",STORAGE_HE_TYPE_PUSH);
  tolua_constant(tolua_S,"STORAGE_HE_TYPE_POP",STORAGE_HE_TYPE_POP);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_STORAGE_TAG",0);
 tolua_beginmodule(tolua_S,"GUILD_STORAGE_TAG");
  tolua_constant(tolua_S,"GUILD_STORAGE_TAG_1",GUILD_STORAGE_TAG_1);
  tolua_constant(tolua_S,"GUILD_STORAGE_TAG_2",GUILD_STORAGE_TAG_2);
  tolua_constant(tolua_S,"GUILD_STORAGE_TAG_3",GUILD_STORAGE_TAG_3);
  tolua_constant(tolua_S,"GUILD_STORAGE_TAG_4",GUILD_STORAGE_TAG_4);
  tolua_constant(tolua_S,"GUILD_STORAGE_TAG_5",GUILD_STORAGE_TAG_5);
  tolua_constant(tolua_S,"GUILD_STORAGE_TAG_6",GUILD_STORAGE_TAG_6);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_REPLY",0);
 tolua_beginmodule(tolua_S,"GUILD_REPLY");
  tolua_constant(tolua_S,"GUILD_REPLY_REFUSE",GUILD_REPLY_REFUSE);
  tolua_constant(tolua_S,"GUILD_REPLY_AGREE",GUILD_REPLY_AGREE);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_BUILDING_ENUM",0);
 tolua_beginmodule(tolua_S,"GUILD_BUILDING_ENUM");
  tolua_constant(tolua_S,"GUILD_B_NONE",GUILD_B_NONE);
  tolua_constant(tolua_S,"GUILD_B_MAIN",GUILD_B_MAIN);
  tolua_constant(tolua_S,"GUILD_B_BUSINESS",GUILD_B_BUSINESS);
  tolua_constant(tolua_S,"GUILD_B_DEITY",GUILD_B_DEITY);
  tolua_constant(tolua_S,"GUILD_B_HOUSE",GUILD_B_HOUSE);
  tolua_constant(tolua_S,"GUILD_B_STORAGE",GUILD_B_STORAGE);
  tolua_constant(tolua_S,"GUILD_B_STAFF",GUILD_B_STAFF);
  tolua_constant(tolua_S,"GUILD_B_WONDER",GUILD_B_WONDER);
  tolua_constant(tolua_S,"GUILD_B_HERB",GUILD_B_HERB);
  tolua_constant(tolua_S,"GUILD_B_WOOD",GUILD_B_WOOD);
  tolua_constant(tolua_S,"GUILD_B_CRYSTAL",GUILD_B_CRYSTAL);
  tolua_constant(tolua_S,"GUILD_B_SILVER",GUILD_B_SILVER);
  tolua_constant(tolua_S,"GUILD_B_HERB_STORAGE",GUILD_B_HERB_STORAGE);
  tolua_constant(tolua_S,"GUILD_B_WOOD_STORAGE",GUILD_B_WOOD_STORAGE);
  tolua_constant(tolua_S,"GUILD_B_CRYSTAL_STORAGE",GUILD_B_CRYSTAL_STORAGE);
  tolua_constant(tolua_S,"GUILD_B_SILVER_STORAGE",GUILD_B_SILVER_STORAGE);
  tolua_constant(tolua_S,"GUILD_B_FUNATIONAL_NUM",GUILD_B_FUNATIONAL_NUM);
  tolua_constant(tolua_S,"GUILD_B_GATE",GUILD_B_GATE);
  tolua_constant(tolua_S,"GUILD_B_WALL",GUILD_B_WALL);
  tolua_constant(tolua_S,"GUILD_B_ARMSHOP",GUILD_B_ARMSHOP);
  tolua_constant(tolua_S,"GUILD_B_ARROW",GUILD_B_ARROW);
  tolua_constant(tolua_S,"GUILD_B_TURRET",GUILD_B_TURRET);
  tolua_constant(tolua_S,"GUILD_B_GROUP_ATTACK",GUILD_B_GROUP_ATTACK);
  tolua_constant(tolua_S,"GUILD_B_MAGIC",GUILD_B_MAGIC);
  tolua_constant(tolua_S,"GUILD_B_CURE",GUILD_B_CURE);
  tolua_constant(tolua_S,"GUILD_B_BLOCK",GUILD_B_BLOCK);
  tolua_constant(tolua_S,"GUILD_B_NUM",GUILD_B_NUM);
  tolua_constant(tolua_S,"GUILD_B_PROTECTOR",GUILD_B_PROTECTOR);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_CHANGE_WEATHER_TIME_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_CHANGE_WEATHER_TIME_TYPE");
  tolua_constant(tolua_S,"GUILD_CW_TIME_NONE",GUILD_CW_TIME_NONE);
  tolua_constant(tolua_S,"GUILD_CW_TIME_5M",GUILD_CW_TIME_5M);
  tolua_constant(tolua_S,"GUILD_CW_TIME_10M",GUILD_CW_TIME_10M);
  tolua_constant(tolua_S,"GUILD_CW_TIME_30M",GUILD_CW_TIME_30M);
  tolua_constant(tolua_S,"GUILD_CW_TIME_END",GUILD_CW_TIME_END);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_STATE",0);
 tolua_beginmodule(tolua_S,"GUILD_STATE");
  tolua_constant(tolua_S,"GUILD_STATE_NONE",GUILD_STATE_NONE);
  tolua_constant(tolua_S,"GUILD_STATE_STOP_WELFARE",GUILD_STATE_STOP_WELFARE);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_ENTER_MAP_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_ENTER_MAP_TYPE");
  tolua_constant(tolua_S,"GUILD_ENTER_OWNER",GUILD_ENTER_OWNER);
  tolua_constant(tolua_S,"GUILD_ENTER_ALLIANCE",GUILD_ENTER_ALLIANCE);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"GUILD_MAX_INTRUDER_NUM",GUILD_MAX_INTRUDER_NUM);
 tolua_module(tolua_S,"GUILD_WAR_CHARACTER",0);
 tolua_beginmodule(tolua_S,"GUILD_WAR_CHARACTER");
  tolua_constant(tolua_S,"GUILD_WAR_NONE",GUILD_WAR_NONE);
  tolua_constant(tolua_S,"GUILD_WAR_INTRUDER",GUILD_WAR_INTRUDER);
  tolua_constant(tolua_S,"GUILD_WAR_DEFENDER",GUILD_WAR_DEFENDER);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_WAR_STAGE",0);
 tolua_beginmodule(tolua_S,"GUILD_WAR_STAGE");
  tolua_constant(tolua_S,"GUILD_WAR_STAGE_NONE",GUILD_WAR_STAGE_NONE);
  tolua_constant(tolua_S,"GUILD_WAR_STAGE_DECLARE",GUILD_WAR_STAGE_DECLARE);
  tolua_constant(tolua_S,"GUILD_WAR_STAGE_BEGIN",GUILD_WAR_STAGE_BEGIN);
  tolua_constant(tolua_S,"GUILD_WAR_STAGE_END",GUILD_WAR_STAGE_END);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_WAR_DEFENDER_RESULT",0);
 tolua_beginmodule(tolua_S,"GUILD_WAR_DEFENDER_RESULT");
  tolua_constant(tolua_S,"GUILD_WAR_DEFENDER_NONE",GUILD_WAR_DEFENDER_NONE);
  tolua_constant(tolua_S,"GUILD_WAR_DEFENDER_WIN",GUILD_WAR_DEFENDER_WIN);
  tolua_constant(tolua_S,"GUILD_WAR_DEFENDER_LOSE",GUILD_WAR_DEFENDER_LOSE);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"UPGRADE_BUILDING_TYPE",0);
 tolua_beginmodule(tolua_S,"UPGRADE_BUILDING_TYPE");
  tolua_constant(tolua_S,"G_B_UPGRADE_BY_NPC",G_B_UPGRADE_BY_NPC);
  tolua_constant(tolua_S,"G_B_UPGRADE_BY_PANEL",G_B_UPGRADE_BY_PANEL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_BUILDING_STATE",0);
 tolua_beginmodule(tolua_S,"GUILD_BUILDING_STATE");
  tolua_constant(tolua_S,"GUILD_BUILDING_ENABLE",GUILD_BUILDING_ENABLE);
  tolua_constant(tolua_S,"GUILD_BUILDING_DISABLE",GUILD_BUILDING_DISABLE);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_CAST_SPELL_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_CAST_SPELL_TYPE");
  tolua_constant(tolua_S,"GUILD_CS_UPGRADING",GUILD_CS_UPGRADING);
  tolua_constant(tolua_S,"GUILD_CS_UPDATE",GUILD_CS_UPDATE);
  tolua_constant(tolua_S,"GUILD_CS_DEL",GUILD_CS_DEL);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"SABAC_STATE",0);
 tolua_beginmodule(tolua_S,"SABAC_STATE");
  tolua_constant(tolua_S,"sabNotEnroll",sabNotEnroll);
  tolua_constant(tolua_S,"sabEnrolled",sabEnrolled);
  tolua_constant(tolua_S,"sabOccupied",sabOccupied);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_ACHIEVEMENT_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_ACHIEVEMENT_TYPE");
  tolua_constant(tolua_S,"GUILD_ACHI_BEGIN",GUILD_ACHI_BEGIN);
  tolua_constant(tolua_S,"GUILD_ACHI_NONE",GUILD_ACHI_NONE);
  tolua_constant(tolua_S,"GUILD_ACHI_MEMBER",GUILD_ACHI_MEMBER);
  tolua_constant(tolua_S,"GUILD_ACHI_ENEMY",GUILD_ACHI_ENEMY);
  tolua_constant(tolua_S,"GUILD_ACHI_ALLIANCE",GUILD_ACHI_ALLIANCE);
  tolua_constant(tolua_S,"GUILD_ACHI_TAKE_POS_1",GUILD_ACHI_TAKE_POS_1);
  tolua_constant(tolua_S,"GUILD_ACHI_TAKE_POS_2",GUILD_ACHI_TAKE_POS_2);
  tolua_constant(tolua_S,"GUILD_ACHI_TYPE_NUM",GUILD_ACHI_TYPE_NUM);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_ACHIEVEMENT_AWARD_TYPE",0);
 tolua_beginmodule(tolua_S,"GUILD_ACHIEVEMENT_AWARD_TYPE");
  tolua_constant(tolua_S,"GA_AWARD_NONE",GA_AWARD_NONE);
  tolua_constant(tolua_S,"GA_AWARD_POINT",GA_AWARD_POINT);
  tolua_constant(tolua_S,"GA_AWARD_EXP",GA_AWARD_EXP);
  tolua_constant(tolua_S,"GA_AWARD_ITEM",GA_AWARD_ITEM);
  tolua_constant(tolua_S,"GA_AWARD_TITLE",GA_AWARD_TITLE);
  tolua_constant(tolua_S,"GA_AWARD_NUM",GA_AWARD_NUM);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"GUILD_VARIABLE",0);
 tolua_beginmodule(tolua_S,"GUILD_VARIABLE");
  tolua_constant(tolua_S,"avGuildWarCanOpen",avGuildWarCanOpen);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_enum_str (lua_State* tolua_S) {
 return tolua_enum_str_open(tolua_S);
};
#endif

