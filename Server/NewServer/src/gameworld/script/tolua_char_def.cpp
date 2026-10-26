/*
** Lua binding: char_def
** Generated automatically by tolua++-1.0.92 on 11/20/25 22:04:24.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_char_def_open (lua_State* tolua_S);

#include "../../../Common/define/char_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_char_def_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
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
  tolua_constant(tolua_S,"cstInvalid",cstInvalid);
  tolua_constant(tolua_S,"cstMale",cstMale);
  tolua_constant(tolua_S,"cstFemale",cstFemale);
  tolua_constant(tolua_S,"cstAsexual",cstAsexual);
  tolua_constant(tolua_S,"cstTotal",cstTotal);
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
  tolua_constant(tolua_S,"csfInvalid",csfInvalid);
  tolua_constant(tolua_S,"csfStand",csfStand);
  tolua_constant(tolua_S,"csfUp",csfUp);
  tolua_constant(tolua_S,"csfDown",csfDown);
  tolua_constant(tolua_S,"csfTotal",csfTotal);
  tolua_constant(tolua_S,"cstfBegin",cstfBegin);
  tolua_constant(tolua_S,"cstfFreeze",cstfFreeze);
  tolua_constant(tolua_S,"cstfKnockBack",cstfKnockBack);
  tolua_constant(tolua_S,"cstfSilent",cstfSilent);
  tolua_constant(tolua_S,"cstfTotal",cstfTotal);
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
  tolua_constant(tolua_S,"crtInvalid",crtInvalid);
  tolua_constant(tolua_S,"crtAtCurrentPos",crtAtCurrentPos);
  tolua_constant(tolua_S,"crtInstant",crtInstant);
  tolua_constant(tolua_S,"crtFree",crtFree);
  tolua_constant(tolua_S,"crtTotal",crtTotal);
  tolua_constant(tolua_S,"soatInvalid",soatInvalid);
  tolua_constant(tolua_S,"soatLogin",soatLogin);
  tolua_constant(tolua_S,"soatInRange",soatInRange);
  tolua_constant(tolua_S,"soatSpawn",soatSpawn);
  tolua_constant(tolua_S,"soatRevive",soatRevive);
  tolua_constant(tolua_S,"soatNoPerforSpawn",soatNoPerforSpawn);
  tolua_constant(tolua_S,"soatTotal",soatTotal);
  tolua_constant(tolua_S,"sodtInvalid",sodtInvalid);
  tolua_constant(tolua_S,"sodtLeaveScene",sodtLeaveScene);
  tolua_constant(tolua_S,"sodtOutOfRange",sodtOutOfRange);
  tolua_constant(tolua_S,"sodtTotal",sodtTotal);
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
  tolua_constant(tolua_S,"rrrNormal",rrrNormal);
  tolua_constant(tolua_S,"rrrAdvanced",rrrAdvanced);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_char_def (lua_State* tolua_S) {
 return tolua_char_def_open(tolua_S);
};
#endif

