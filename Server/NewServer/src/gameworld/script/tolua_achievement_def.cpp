/*
** Lua binding: achievement_def
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:28.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_achievement_def_open (lua_State* tolua_S);

#include "../../../Common/define/achievement_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_achievement_def_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_CON_PER_ACHIEVEMENT",MAX_CON_PER_ACHIEVEMENT);
 tolua_constant(tolua_S,"ACHIEVEMENT_MAX",ACHIEVEMENT_MAX);
 tolua_constant(tolua_S,"ACHIEVEMENT_PK_VALUE",ACHIEVEMENT_PK_VALUE);
 tolua_constant(tolua_S,"INVALID_ACHIEVEMENT_ID",INVALID_ACHIEVEMENT_ID);
 tolua_constant(tolua_S,"MAX_REWARD_PER_ACHIEVEMENT",MAX_REWARD_PER_ACHIEVEMENT);
 tolua_constant(tolua_S,"MAX_ACHIEVEMENT_STATISTIC_COUNT",MAX_ACHIEVEMENT_STATISTIC_COUNT);
 tolua_constant(tolua_S,"MAX_ACHIEVEMENT_WEEKLY_UPDATE_TIME",MAX_ACHIEVEMENT_WEEKLY_UPDATE_TIME);
 tolua_constant(tolua_S,"MAX_ACHIEVEMENT_MONTHLY_UPDATE_TIME",MAX_ACHIEVEMENT_MONTHLY_UPDATE_TIME);
 tolua_constant(tolua_S,"MAX_HANKBOOK_COUNT_PER_TYPE",MAX_HANKBOOK_COUNT_PER_TYPE);
  tolua_constant(tolua_S,"htInvalid",htInvalid);
  tolua_constant(tolua_S,"htNpcBegin",htNpcBegin);
  tolua_constant(tolua_S,"htNpc_Normal",htNpc_Normal);
  tolua_constant(tolua_S,"htNpc_Elite",htNpc_Elite);
  tolua_constant(tolua_S,"htNPc_Boss",htNPc_Boss);
  tolua_constant(tolua_S,"htNpc_Function",htNpc_Function);
  tolua_constant(tolua_S,"htNpc_Story",htNpc_Story);
  tolua_constant(tolua_S,"htNpcEnd",htNpcEnd);
  tolua_constant(tolua_S,"htMap_Wild",htMap_Wild);
  tolua_constant(tolua_S,"htMap_Dungeon",htMap_Dungeon);
  tolua_constant(tolua_S,"htMap_Activity",htMap_Activity);
  tolua_constant(tolua_S,"htItem_Compose",htItem_Compose);
  tolua_constant(tolua_S,"htItem_Stone",htItem_Stone);
  tolua_constant(tolua_S,"htItem_Story",htItem_Story);
  tolua_constant(tolua_S,"htEquip_Begin",htEquip_Begin);
  tolua_constant(tolua_S,"htEquip_Set",htEquip_Set);
  tolua_constant(tolua_S,"htEquip_Weapon",htEquip_Weapon);
  tolua_constant(tolua_S,"htEquip_Jewelry",htEquip_Jewelry);
  tolua_constant(tolua_S,"htEquip_Armor",htEquip_Armor);
  tolua_constant(tolua_S,"htEquip_End",htEquip_End);
  tolua_constant(tolua_S,"htRune_Warrior",htRune_Warrior);
  tolua_constant(tolua_S,"htRune_Mage",htRune_Mage);
  tolua_constant(tolua_S,"htRune_Rogue",htRune_Rogue);
  tolua_constant(tolua_S,"htRune_Archer",htRune_Archer);
  tolua_constant(tolua_S,"htRune_Taoist",htRune_Taoist);
  tolua_constant(tolua_S,"htAir_Green",htAir_Green);
  tolua_constant(tolua_S,"htAir_Blue",htAir_Blue);
  tolua_constant(tolua_S,"htAir_Purple",htAir_Purple);
  tolua_constant(tolua_S,"htTotal",htTotal);
  tolua_constant(tolua_S,"adtInvalid",adtInvalid);
  tolua_constant(tolua_S,"adtTitle",adtTitle);
  tolua_constant(tolua_S,"adtItem",adtItem);
  tolua_constant(tolua_S,"adtExp",adtExp);
  tolua_constant(tolua_S,"adtTotal",adtTotal);
  tolua_constant(tolua_S,"acrtInvalid",acrtInvalid);
  tolua_constant(tolua_S,"acrtWeek",acrtWeek);
  tolua_constant(tolua_S,"acrtMonth",acrtMonth);
  tolua_constant(tolua_S,"acrtTotal",acrtTotal);
  tolua_constant(tolua_S,"adInvalid",adInvalid);
  tolua_constant(tolua_S,"adLevel",adLevel);
  tolua_constant(tolua_S,"adExperience",adExperience);
  tolua_constant(tolua_S,"adPkValue",adPkValue);
  tolua_constant(tolua_S,"adForceReputation",adForceReputation);
  tolua_constant(tolua_S,"adVariousForceCount",adVariousForceCount);
  tolua_constant(tolua_S,"adGetItem",adGetItem);
  tolua_constant(tolua_S,"adItemLuck",adItemLuck);
  tolua_constant(tolua_S,"adItemRefine",adItemRefine);
  tolua_constant(tolua_S,"adRefineLevel",adRefineLevel);
  tolua_constant(tolua_S,"adEquip",adEquip);
  tolua_constant(tolua_S,"adEquipColor",adEquipColor);
  tolua_constant(tolua_S,"adEquipBodyColor",adEquipBodyColor);
  tolua_constant(tolua_S,"adSet",adSet);
  tolua_constant(tolua_S,"adSetCount",adSetCount);
  tolua_constant(tolua_S,"adBankSlotCount",adBankSlotCount);
  tolua_constant(tolua_S,"adBagSlotCount",adBagSlotCount);
  tolua_constant(tolua_S,"adItemBagSlotCount",adItemBagSlotCount);
  tolua_constant(tolua_S,"adEquipSlotCount",adEquipSlotCount);
  tolua_constant(tolua_S,"adMaterialBagSlotCount",adMaterialBagSlotCount);
  tolua_constant(tolua_S,"adTotalMoneyType",adTotalMoneyType);
  tolua_constant(tolua_S,"adKillPlayerTotalCount",adKillPlayerTotalCount);
  tolua_constant(tolua_S,"adEnterScene",adEnterScene);
  tolua_constant(tolua_S,"adCompleteQuest",adCompleteQuest);
  tolua_constant(tolua_S,"adCompleteQuestCount",adCompleteQuestCount);
  tolua_constant(tolua_S,"adSpellLevelSpecified",adSpellLevelSpecified);
  tolua_constant(tolua_S,"adSpellLevel",adSpellLevel);
  tolua_constant(tolua_S,"adLearnSpell",adLearnSpell);
  tolua_constant(tolua_S,"adSpellCount",adSpellCount);
  tolua_constant(tolua_S,"adActiveSpellCount",adActiveSpellCount);
  tolua_constant(tolua_S,"adRuneCount",adRuneCount);
  tolua_constant(tolua_S,"adEquipPassiveSpellCount",adEquipPassiveSpellCount);
  tolua_constant(tolua_S,"adEquipPassiveSpellIDCount",adEquipPassiveSpellIDCount);
  tolua_constant(tolua_S,"adAchievement",adAchievement);
  tolua_constant(tolua_S,"adAchievementCount",adAchievementCount);
  tolua_constant(tolua_S,"adTitle",adTitle);
  tolua_constant(tolua_S,"adTitleCount",adTitleCount);
  tolua_constant(tolua_S,"adFriendCount",adFriendCount);
  tolua_constant(tolua_S,"adLeaveStudentCount",adLeaveStudentCount);
  tolua_constant(tolua_S,"adCreateTime",adCreateTime);
  tolua_constant(tolua_S,"adVariable",adVariable);
  tolua_constant(tolua_S,"adRoleVariable",adRoleVariable);
  tolua_constant(tolua_S,"adKilledByNpcIDCount",adKilledByNpcIDCount);
  tolua_constant(tolua_S,"adKillNpcIDCount",adKillNpcIDCount);
  tolua_constant(tolua_S,"adKillNpcGroupIDCount",adKillNpcGroupIDCount);
  tolua_constant(tolua_S,"adUseItemIDCount",adUseItemIDCount);
  tolua_constant(tolua_S,"adHero",adHero);
  tolua_constant(tolua_S,"adSpiritLevel",adSpiritLevel);
  tolua_constant(tolua_S,"adSpiritAirColorCount",adSpiritAirColorCount);
  tolua_constant(tolua_S,"adSpiritAirColorLevel",adSpiritAirColorLevel);
  tolua_constant(tolua_S,"adSpiritBuyAirEquipSlotCount",adSpiritBuyAirEquipSlotCount);
  tolua_constant(tolua_S,"adSpiritBuyAirBagSlotCount",adSpiritBuyAirBagSlotCount);
  tolua_constant(tolua_S,"adSpiritBuyAirStallSlotCount",adSpiritBuyAirStallSlotCount);
  tolua_constant(tolua_S,"adSpiritBuyBloodSlotCount",adSpiritBuyBloodSlotCount);
  tolua_constant(tolua_S,"adSpiritBloodPageCount",adSpiritBloodPageCount);
  tolua_constant(tolua_S,"adSpiritBloodPageCompleteCount",adSpiritBloodPageCompleteCount);
  tolua_constant(tolua_S,"adSpiritBloodPageLevel",adSpiritBloodPageLevel);
  tolua_constant(tolua_S,"adEquipDecompose",adEquipDecompose);
  tolua_constant(tolua_S,"adEquipColorDecompose",adEquipColorDecompose);
  tolua_constant(tolua_S,"adEquipCompose",adEquipCompose);
  tolua_constant(tolua_S,"adEquipColorCompose",adEquipColorCompose);
  tolua_constant(tolua_S,"adVip",adVip);
  tolua_constant(tolua_S,"adSubscribeVipTotalMonth",adSubscribeVipTotalMonth);
  tolua_constant(tolua_S,"adJoinTeamCount",adJoinTeamCount);
  tolua_constant(tolua_S,"adAuctionBuyItemCount",adAuctionBuyItemCount);
  tolua_constant(tolua_S,"adAuctionSellItemCount",adAuctionSellItemCount);
  tolua_constant(tolua_S,"adRanklist",adRanklist);
  tolua_constant(tolua_S,"adColorItemCompose",adColorItemCompose);
  tolua_constant(tolua_S,"adColorItemDeCompose",adColorItemDeCompose);
  tolua_constant(tolua_S,"adRuneWeaponCount",adRuneWeaponCount);
  tolua_constant(tolua_S,"adExplore",adExplore);
  tolua_constant(tolua_S,"adHandbook",adHandbook);
  tolua_constant(tolua_S,"adTotal",adTotal);
  tolua_constant(tolua_S,"avdInvalid",avdInvalid);
  tolua_constant(tolua_S,"avdForSceneBegin",avdForSceneBegin);
  tolua_constant(tolua_S,"avdSceneTempID",avdSceneTempID);
  tolua_constant(tolua_S,"avdSceneID",avdSceneID);
  tolua_constant(tolua_S,"avdReward_1",avdReward_1);
  tolua_constant(tolua_S,"avdReward_2",avdReward_2);
  tolua_constant(tolua_S,"avdReward_3",avdReward_3);
  tolua_constant(tolua_S,"avdForSceneEnd",avdForSceneEnd);
  tolua_constant(tolua_S,"avdStatisticBegin",avdStatisticBegin);
  tolua_constant(tolua_S,"avdDestoryItemCount",avdDestoryItemCount);
  tolua_constant(tolua_S,"avdPickMoneyTotal",avdPickMoneyTotal);
  tolua_constant(tolua_S,"avdQuestMoneyTotal",avdQuestMoneyTotal);
  tolua_constant(tolua_S,"avdSaleMoneyTotal",avdSaleMoneyTotal);
  tolua_constant(tolua_S,"avdRelieveMoneyTotal",avdRelieveMoneyTotal);
  tolua_constant(tolua_S,"avdReliveRMBTotal",avdReliveRMBTotal);
  tolua_constant(tolua_S,"avdRepairMoneyTotal",avdRepairMoneyTotal);
  tolua_constant(tolua_S,"avdRepairMoneyMax",avdRepairMoneyMax);
  tolua_constant(tolua_S,"avdKillNpcTotalCount",avdKillNpcTotalCount);
  tolua_constant(tolua_S,"avdSelfDieCount",avdSelfDieCount);
  tolua_constant(tolua_S,"avdPVPKilledByPlayer",avdPVPKilledByPlayer);
  tolua_constant(tolua_S,"avdPVPKilledByNpc",avdPVPKilledByNpc);
  tolua_constant(tolua_S,"avdKillWarriorCount",avdKillWarriorCount);
  tolua_constant(tolua_S,"avdKillMageCount",avdKillMageCount);
  tolua_constant(tolua_S,"avdKillRogueCount",avdKillRogueCount);
  tolua_constant(tolua_S,"avdKillArcherCount",avdKillArcherCount);
  tolua_constant(tolua_S,"avdKillPkValuePlayerCount",avdKillPkValuePlayerCount);
  tolua_constant(tolua_S,"avdKillWithNoGuilty",avdKillWithNoGuilty);
  tolua_constant(tolua_S,"avdEnterDungeonSceneCount",avdEnterDungeonSceneCount);
  tolua_constant(tolua_S,"avdCompleteStoryQuestCount",avdCompleteStoryQuestCount);
  tolua_constant(tolua_S,"avdCompleteNormalQuestCount",avdCompleteNormalQuestCount);
  tolua_constant(tolua_S,"avdCompleteCircleQuestCount",avdCompleteCircleQuestCount);
  tolua_constant(tolua_S,"avdCompleteRewardQuestCount",avdCompleteRewardQuestCount);
  tolua_constant(tolua_S,"avdCompleteEmegencyQuestCount",avdCompleteEmegencyQuestCount);
  tolua_constant(tolua_S,"avdBrushRewardQuestCount",avdBrushRewardQuestCount);
  tolua_constant(tolua_S,"avdBuyRewardQuestCompleteCount",avdBuyRewardQuestCompleteCount);
  tolua_constant(tolua_S,"avdAbandonQuestCount",avdAbandonQuestCount);
  tolua_constant(tolua_S,"avdMaxHPHit",avdMaxHPHit);
  tolua_constant(tolua_S,"avdMaxHPBeHit",avdMaxHPBeHit);
  tolua_constant(tolua_S,"avdUseItemCount_Useable",avdUseItemCount_Useable);
  tolua_constant(tolua_S,"avdUseItemCount_SpellBoke",avdUseItemCount_SpellBoke);
  tolua_constant(tolua_S,"avdOnlineTime",avdOnlineTime);
  tolua_constant(tolua_S,"avdLeaveMaster",avdLeaveMaster);
  tolua_constant(tolua_S,"avdTotalRefineTime",avdTotalRefineTime);
  tolua_constant(tolua_S,"avdRefineFailTime",avdRefineFailTime);
  tolua_constant(tolua_S,"avdFirstBloodCount",avdFirstBloodCount);
  tolua_constant(tolua_S,"avdIdentifyItemCount",avdIdentifyItemCount);
  tolua_constant(tolua_S,"avdDropItemBeKilled",avdDropItemBeKilled);
  tolua_constant(tolua_S,"avdStatisticEnd",avdStatisticEnd);
  tolua_constant(tolua_S,"avdQuestFlytoZone",avdQuestFlytoZone);
  tolua_constant(tolua_S,"avdLastOfflineTime",avdLastOfflineTime);
  tolua_constant(tolua_S,"avdRewardQuestCompleteCount",avdRewardQuestCompleteCount);
  tolua_constant(tolua_S,"avdKillPlayerLevelDuarionBegin",avdKillPlayerLevelDuarionBegin);
  tolua_constant(tolua_S,"avdKillPlayerLevelDuarion1",avdKillPlayerLevelDuarion1);
  tolua_constant(tolua_S,"avdKillPlayerLevelDuarion2",avdKillPlayerLevelDuarion2);
  tolua_constant(tolua_S,"avdKillPlayerLevelDuarion3",avdKillPlayerLevelDuarion3);
  tolua_constant(tolua_S,"avdEquipDecompose",avdEquipDecompose);
  tolua_constant(tolua_S,"avdEquipCompose",avdEquipCompose);
  tolua_constant(tolua_S,"avdTeamAuctionCount",avdTeamAuctionCount);
  tolua_constant(tolua_S,"avdVip",avdVip);
  tolua_constant(tolua_S,"avdSubscribeVipMonth",avdSubscribeVipMonth);
  tolua_constant(tolua_S,"avdJoinTeamCount",avdJoinTeamCount);
  tolua_constant(tolua_S,"avdComposeOrangeItem",avdComposeOrangeItem);
  tolua_constant(tolua_S,"avdComposePurpleItem",avdComposePurpleItem);
  tolua_constant(tolua_S,"avdDecomposeOrangeItem",avdDecomposeOrangeItem);
  tolua_constant(tolua_S,"avdDecomposePurpleItem",avdDecomposePurpleItem);
  tolua_constant(tolua_S,"avdComposeItemCount",avdComposeItemCount);
  tolua_constant(tolua_S,"avdDeComposeItemCount",avdDeComposeItemCount);
  tolua_constant(tolua_S,"avdAuctionSellCount",avdAuctionSellCount);
  tolua_constant(tolua_S,"avdAuctionBid",avdAuctionBid);
  tolua_constant(tolua_S,"avdMaxConsecutiveKillNpcCount",avdMaxConsecutiveKillNpcCount);
  tolua_constant(tolua_S,"avdMaxMomentaryKillNpcCount",avdMaxMomentaryKillNpcCount);
  tolua_constant(tolua_S,"avdMaxConsecutiveKillPlayerCount",avdMaxConsecutiveKillPlayerCount);
  tolua_constant(tolua_S,"avdRealMoneyToItemCount",avdRealMoneyToItemCount);
  tolua_constant(tolua_S,"avdRealMoneyToMoney02Count",avdRealMoneyToMoney02Count);
  tolua_constant(tolua_S,"avdSpiritLevelUP",avdSpiritLevelUP);
  tolua_constant(tolua_S,"avdKillNpcNormal",avdKillNpcNormal);
  tolua_constant(tolua_S,"avdKillNpcElit",avdKillNpcElit);
  tolua_constant(tolua_S,"avdKillNpcBoss",avdKillNpcBoss);
  tolua_constant(tolua_S,"avdCompleteGuildQuest",avdCompleteGuildQuest);
  tolua_constant(tolua_S,"avdCompleteAdventureQuest",avdCompleteAdventureQuest);
  tolua_constant(tolua_S,"avdItemRepairCount",avdItemRepairCount);
  tolua_constant(tolua_S,"avdRuneAddCount",avdRuneAddCount);
  tolua_constant(tolua_S,"avdCompleteQuestTotalCount",avdCompleteQuestTotalCount);
  tolua_constant(tolua_S,"avdKillNpcRare",avdKillNpcRare);
  tolua_constant(tolua_S,"avdKillNpcCorpse",avdKillNpcCorpse);
  tolua_constant(tolua_S,"avdLevelOnlineTime",avdLevelOnlineTime);
  tolua_constant(tolua_S,"avdRankPow",avdRankPow);
  tolua_constant(tolua_S,"avdRankLevel",avdRankLevel);
  tolua_constant(tolua_S,"avdRankMoney",avdRankMoney);
  tolua_constant(tolua_S,"avdRankPkValue",avdRankPkValue);
  tolua_constant(tolua_S,"avdRankMasterExp",avdRankMasterExp);
  tolua_constant(tolua_S,"avdRankAchievementPts",avdRankAchievementPts);
  tolua_constant(tolua_S,"avdExeciseTime",avdExeciseTime);
  tolua_constant(tolua_S,"avdTotal",avdTotal);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_achievement_def (lua_State* tolua_S) {
 return tolua_achievement_def_open(tolua_S);
};
#endif

