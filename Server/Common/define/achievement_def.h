#ifndef _ACHIEVEMENT_DEF_H_
#define _ACHIEVEMENT_DEF_H_

#define MAX_CON_PER_ACHIEVEMENT 6
#define ACHIEVEMENT_MAX 512

#define ACHIEVEMENT_PK_VALUE 300
#define INVALID_ACHIEVEMENT_ID 0

#define MAX_REWARD_PER_ACHIEVEMENT 3

#define MAX_ACHIEVEMENT_STATISTIC_COUNT	(128)

#define MAX_ACHIEVEMENT_WEEKLY_UPDATE_TIME	(7*24*3600)
#define MAX_ACHIEVEMENT_MONTHLY_UPDATE_TIME	(4*MAX_ACHIEVEMENT_WEEKLY_UPDATE_TIME)

/*********************handbook*********************************/

#define MAX_HANKBOOK_COUNT_PER_TYPE		(256)
enum HANDBOOK_TYPE
{
	htInvalid,

	htNpcBegin,
	htNpc_Normal = htNpcBegin,
	htNpc_Elite,
	htNPc_Boss,

	htNpc_Function,
	htNpc_Story,
	htNpcEnd,

	htMap_Wild = htNpcEnd,
	htMap_Dungeon,
	htMap_Activity,

	htItem_Compose,
	htItem_Stone,
	htItem_Story,

	htEquip_Begin = htItem_Story,
	htEquip_Set,
	htEquip_Weapon,
	htEquip_Jewelry,
	htEquip_Armor,
	htEquip_End,

	htRune_Warrior = htEquip_End,
	htRune_Mage,
	htRune_Rogue,
	htRune_Archer,
	htRune_Taoist,

	htAir_Green,
	htAir_Blue,
	htAir_Purple,

	htTotal,
};

enum ACHIEVEMENT_REWARD_TYPE
{
	adtInvalid,
	
	adtTitle,
	adtItem,
	adtExp,

	adtTotal,

};

enum ACHIEVEMENT_RESET_TYPE
{
	acrtInvalid,

	acrtWeek,
	acrtMonth,

	acrtTotal,
};

enum ACHIENEMENT_DEF
{
	adInvalid,
	
	adLevel,			
	adExperience,
	adPkValue,

	adForceReputation,
	adVariousForceCount,

	adGetItem,
	adItemLuck,
	adItemRefine,

	adRefineLevel,

	adEquip,
	adEquipColor,
	adEquipBodyColor,
	
	adSet,
	adSetCount,
	
	adBankSlotCount,
	adBagSlotCount,
	adItemBagSlotCount,
	adEquipSlotCount,
	adMaterialBagSlotCount,

	adTotalMoneyType,

	adKillPlayerTotalCount,

	adEnterScene,

	adCompleteQuest,
	adCompleteQuestCount,

	adSpellLevelSpecified,
	adSpellLevel,
	adLearnSpell,
	adSpellCount,
	adActiveSpellCount,
	adRuneCount,
	adEquipPassiveSpellCount,
	adEquipPassiveSpellIDCount,

	adAchievement,
	adAchievementCount,

	adTitle,
	adTitleCount,

	adFriendCount,

	adLeaveStudentCount,

	adCreateTime,

	adVariable,
	adRoleVariable,

	adKilledByNpcIDCount,
	adKillNpcIDCount,
	adKillNpcGroupIDCount,
	adUseItemIDCount,

	adHero,

	adSpiritLevel,
	adSpiritAirColorCount,
	adSpiritAirColorLevel,
	adSpiritBuyAirEquipSlotCount,
	adSpiritBuyAirBagSlotCount,
	adSpiritBuyAirStallSlotCount,
	adSpiritBuyBloodSlotCount,
	adSpiritBloodPageCount,
	adSpiritBloodPageCompleteCount,
	adSpiritBloodPageLevel,

	adEquipDecompose,
	adEquipColorDecompose,
	adEquipCompose,
	adEquipColorCompose,

	adVip,
	adSubscribeVipTotalMonth,

	adJoinTeamCount,

	adAuctionBuyItemCount,
	adAuctionSellItemCount,

	adRanklist,
	
	adColorItemCompose,
	adColorItemDeCompose,

	adRuneWeaponCount,

	adExplore,

	adHandbook,

	adTotal,
};

enum ACHIEVEMENT_VARIABLE_DEF
{
	avdInvalid,

	avdForSceneBegin,
	avdSceneTempID = avdForSceneBegin,
	avdSceneID,

	avdReward_1,
	avdReward_2,
	avdReward_3,
	avdForSceneEnd = avdReward_3,

	avdStatisticBegin,
	avdDestoryItemCount = avdStatisticBegin,

	avdPickMoneyTotal,					
	avdQuestMoneyTotal,			
	avdSaleMoneyTotal,				
	avdRelieveMoneyTotal,
	avdReliveRMBTotal,
	avdRepairMoneyTotal,		
	avdRepairMoneyMax,			

	avdKillNpcTotalCount,
	avdSelfDieCount,					
	avdPVPKilledByPlayer,				
	avdPVPKilledByNpc,											
	avdKillWarriorCount,				
	avdKillMageCount,				
	avdKillRogueCount,				
	avdKillArcherCount,
	avdKillPkValuePlayerCount,
	avdKillWithNoGuilty,

	avdEnterDungeonSceneCount,

	avdCompleteStoryQuestCount,
	avdCompleteNormalQuestCount,	
	avdCompleteCircleQuestCount,	
	avdCompleteRewardQuestCount,
	avdCompleteEmegencyQuestCount,
	avdBrushRewardQuestCount,
	avdBuyRewardQuestCompleteCount,

	avdAbandonQuestCount,

	avdMaxHPHit,						
	avdMaxHPBeHit,									

	avdUseItemCount_Useable,
	avdUseItemCount_SpellBoke,

	avdOnlineTime,

	avdLeaveMaster,

	avdTotalRefineTime,
	avdRefineFailTime,

	avdFirstBloodCount,

	avdIdentifyItemCount,

	avdDropItemBeKilled,

	avdStatisticEnd,

	avdQuestFlytoZone,					// 新手引导 任务飞鞋用 前几次免费

	avdLastOfflineTime,					// 记录下线时间

	avdRewardQuestCompleteCount,		// 每日悬赏任务的完成次数，用于活动显示

	avdKillPlayerLevelDuarionBegin,
	avdKillPlayerLevelDuarion1 = avdKillPlayerLevelDuarionBegin,			// 杀死等级段1玩家，
	avdKillPlayerLevelDuarion2,												// 杀死等级段2玩家，
	avdKillPlayerLevelDuarion3,												// 杀死等级段3玩家，	

	avdEquipDecompose,
	avdEquipCompose,

	avdTeamAuctionCount,

	avdVip,
	avdSubscribeVipMonth,

	avdJoinTeamCount,

	avdComposeOrangeItem,
	avdComposePurpleItem,
	avdDecomposeOrangeItem,
	avdDecomposePurpleItem,
	avdComposeItemCount,
	avdDeComposeItemCount,

	avdAuctionSellCount,
	avdAuctionBid,

	avdMaxConsecutiveKillNpcCount,
	avdMaxMomentaryKillNpcCount,
	avdMaxConsecutiveKillPlayerCount,

	avdRealMoneyToItemCount,
	avdRealMoneyToMoney02Count,

	avdSpiritLevelUP,
	avdKillNpcNormal,
	avdKillNpcElit,
	avdKillNpcBoss,
	
	avdCompleteGuildQuest,
	avdCompleteAdventureQuest,

	avdItemRepairCount,

	avdRuneAddCount,

	avdCompleteQuestTotalCount,

	avdKillNpcRare,
	avdKillNpcCorpse,
	avdLevelOnlineTime,

	avdRankPow,
	avdRankLevel,
	avdRankMoney,
	avdRankPkValue,
	avdRankMasterExp,
	avdRankAchievementPts,

	avdExeciseTime,

	avdTotal,
};

#endif // _ACHIEVEMENT_DEF_H_