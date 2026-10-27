/*
** Lua binding: rank_list_def
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_rank_list_def_open (lua_State* tolua_S);

#include "../../../Common/define/ranklist_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_rank_list_def_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_RANK_LIST_NODE_COUNT",MAX_RANK_LIST_NODE_COUNT);
 tolua_constant(tolua_S,"MAX_RANK_NODE_NUM_PER_PAGE",MAX_RANK_NODE_NUM_PER_PAGE);
  tolua_constant(tolua_S,"rlInvalid",rlInvalid);
  tolua_constant(tolua_S,"rlBegin",rlBegin);
  tolua_constant(tolua_S,"rlRoleBegin",rlRoleBegin);
  tolua_constant(tolua_S,"rlLevel",rlLevel);
  tolua_constant(tolua_S,"rlLevelWarrior",rlLevelWarrior);
  tolua_constant(tolua_S,"rlLevelMage",rlLevelMage);
  tolua_constant(tolua_S,"rlLevelTaoist",rlLevelTaoist);
  tolua_constant(tolua_S,"rlLevelRogue",rlLevelRogue);
  tolua_constant(tolua_S,"rlLevelArcher",rlLevelArcher);
  tolua_constant(tolua_S,"rlPower",rlPower);
  tolua_constant(tolua_S,"rlPowerWarrior",rlPowerWarrior);
  tolua_constant(tolua_S,"rlPowerMage",rlPowerMage);
  tolua_constant(tolua_S,"rlPowerTaoist",rlPowerTaoist);
  tolua_constant(tolua_S,"rlPowerRogue",rlPowerRogue);
  tolua_constant(tolua_S,"rlPowerArcher",rlPowerArcher);
  tolua_constant(tolua_S,"rlMoney",rlMoney);
  tolua_constant(tolua_S,"rlAchievement",rlAchievement);
  tolua_constant(tolua_S,"rlMaster",rlMaster);
  tolua_constant(tolua_S,"rlPkValue",rlPkValue);
  tolua_constant(tolua_S,"rlTotalKillCount",rlTotalKillCount);
  tolua_constant(tolua_S,"rlActivity01",rlActivity01);
  tolua_constant(tolua_S,"rlActivity02",rlActivity02);
  tolua_constant(tolua_S,"rlActivity03",rlActivity03);
  tolua_constant(tolua_S,"rlActivity04",rlActivity04);
  tolua_constant(tolua_S,"rlActivity05",rlActivity05);
  tolua_constant(tolua_S,"rlActivity06",rlActivity06);
  tolua_constant(tolua_S,"rlActivity07",rlActivity07);
  tolua_constant(tolua_S,"rlActivity08",rlActivity08);
  tolua_constant(tolua_S,"rlReserved01",rlReserved01);
  tolua_constant(tolua_S,"rlReserved02",rlReserved02);
  tolua_constant(tolua_S,"rlReserved03",rlReserved03);
  tolua_constant(tolua_S,"rlReserved04",rlReserved04);
  tolua_constant(tolua_S,"rlReserved05",rlReserved05);
  tolua_constant(tolua_S,"rlReserved06",rlReserved06);
  tolua_constant(tolua_S,"rlReserved07",rlReserved07);
  tolua_constant(tolua_S,"rlReserved08",rlReserved08);
  tolua_constant(tolua_S,"rlArena1v1",rlArena1v1);
  tolua_constant(tolua_S,"rlArena1v1Warrior",rlArena1v1Warrior);
  tolua_constant(tolua_S,"rlArena1v1Mage",rlArena1v1Mage);
  tolua_constant(tolua_S,"rlArena1v1Taoist",rlArena1v1Taoist);
  tolua_constant(tolua_S,"rlArena1v1Reserved01",rlArena1v1Reserved01);
  tolua_constant(tolua_S,"rlArena1v1Reserved02",rlArena1v1Reserved02);
  tolua_constant(tolua_S,"rlArena5v5",rlArena5v5);
  tolua_constant(tolua_S,"rlArena5v5Reserved01",rlArena5v5Reserved01);
  tolua_constant(tolua_S,"rlArena5v5Reserved02",rlArena5v5Reserved02);
  tolua_constant(tolua_S,"rlArena5v5Reserved03",rlArena5v5Reserved03);
  tolua_constant(tolua_S,"rlArena5v5Reserved04",rlArena5v5Reserved04);
  tolua_constant(tolua_S,"rlArena5v5Reserved05",rlArena5v5Reserved05);
  tolua_constant(tolua_S,"rlRoleEnd",rlRoleEnd);
  tolua_constant(tolua_S,"rlGuildBegin",rlGuildBegin);
  tolua_constant(tolua_S,"rlGuild_Level",rlGuild_Level);
  tolua_constant(tolua_S,"rlGuild_Money",rlGuild_Money);
  tolua_constant(tolua_S,"rlGuild_Resource_Herb",rlGuild_Resource_Herb);
  tolua_constant(tolua_S,"rlGuild_Resource_Wood",rlGuild_Resource_Wood);
  tolua_constant(tolua_S,"rlGuild_Resource_Crystal",rlGuild_Resource_Crystal);
  tolua_constant(tolua_S,"rlGuild_Resource_Silver",rlGuild_Resource_Silver);
  tolua_constant(tolua_S,"rlGuild_Pow",rlGuild_Pow);
  tolua_constant(tolua_S,"rlGuild_War",rlGuild_War);
  tolua_constant(tolua_S,"rlGuildEnd",rlGuildEnd);
  tolua_constant(tolua_S,"rlTotal",rlTotal);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_rank_list_def (lua_State* tolua_S) {
 return tolua_rank_list_def_open(tolua_S);
};
#endif

