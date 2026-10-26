#include "stdafx.h"
#include "npc_data.h"
#include "npc_def.h"

#include "scene_def.h"
#include "shop_data.h"
#include "script_mgr.h"

BOOL NPC_DATA::ReadLine(INT32& rnID, const char*& rpcszName, NPC_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("TemplateID", nTemplateID);
	READ_INT("ClientTemplateID", nClientTemplateID);

	READ_STR("DisplayName", szName);
	strxcpy(pData->szDisplayName, pData->szName, MAX_NPC_NAME_LEN);
	strtok(pData->szDisplayName, "0123456789");
	READ_INT("Level", nLevel);
	READ_INT("Pattern", nPatternID);
	READ_INT("Quality", nQuality);
    READ_INT("Broadcast", nBroadcast);
	READ_INT("GroupID", nGroupID);
	READ_INT("DieIDMonitor", bDieIDMonitor);
    READ_INT("StatMoney", bStatMoney);
    READ_INT("BigDropInterval", nBigDropInterval);
    READ_INT("RuneGroup", nRuneGroup);
	READ_INT("SpellEffectGroups", nSpellEffectGroup);

	READ_INT("ForceID", nForceID);
	READ_INT("ReduceReputation", bReduceReputation);
	READ_INT("RivalForceID", nRivalForceID);
	READ_INT("SpeciesType", nSpecies);
	pData->pAdventureData = NULL;
	READ_INT_EXPR("BodyType", nBodyType);
	if (pData->nBodyType <= bodyInvalid || pData->nBodyType >= bodyTotal)
		pData->nBodyType = body1x1;

	pData->nBeKilledVarIndex = -1;
	pData->nKillPlayerVarIndex = -1;
	pData->nKillNpcQuestID = -1;

	READ_TIME("ServerSpawnTime", nSpawnTime);
	READ_TIME("ReviveTime", nReviveTime);
	READ_TIME("CorpseTime", nCorpseTime);
	READ_TIME("RespawnTimeMin", nMinRespawnTime);
	READ_TIME("RespawnTimeMax", nMaxRespawnTime);

	READ_INT("AIData", nAIID);
	READ_INT("ImmunePassiveMove", bImmunePassiveMove);
	READ_INT("Invincible", bInvincible);
	READ_INT("CanbeThrown", bCanbeThrown);
	READ_INT("IgnoreInvisible", bIgnoreInvisible);
	READ_INT("CounterInvisible", bCounterInvisible);
	READ_INT("AttackRange", nAttackRange);
	READ_INT("Exclusive", bExclusive);
	READ_INT("Profit", bProfit);
	READ_INT("ExpRate", nExpRate);
	READ_INT("NeverBeHit", bNeverBeHit);
	READ_INT("SoulRate", nSoulRate);
	READ_INT("DailyExp", bDailyExp);
	READ_INT("ShopID", nShopID);
    READ_INT("BlackMarketID", nBlackMarketID);
	READ_INT("CorpseDoodadID", nCorpseDoodadID);
	READ_INT("EnableDiag_PlayerBank.Enable", bInteractBank);
	READ_INT("EnableDiag_GuildBank.Enable", bInteractGuildBank);
	READ_INT("EnableDiag_RewardQuest.Enable", bInteractRewardQuest);
	READ_INT("EnableDiag_CreateGuild.Enable", bInteractCreateGuild);
	READ_INT("EnableDiag_GuildSalary.Enable", bInteractGuildSalary);
	READ_INT("EnableDiag_Auction.Enable", bInteractAuction);
	READ_INT("EnableDiag_WeaponRune.Enable", bInteractRune);
	READ_INT("EnableDiag_GemEmbed.Enable", bInteractSoul);
    READ_INT("EnableDiag_LevelUpCurWeapon.Enable", bInteractWeaponLevelUpPutIn);
    READ_INT("EnableDiag_GetBackCurLvUpWeapon.Enable", bInteractWeaponLevelUpTakeOut);
	READ_INT("EnableDiag_SpecialRepair.Enable", bInteractSpecialRepair);
    READ_INT("EnableDiag_Gamble.Enable", bInteractGamble);
    READ_INT("EnableDiag_Exercise.Enable", bInteractExercise);
    READ_INT("EnableDiag_GambleBook.Enable", bInteractSpellBookGamble);
    READ_INT("EnableDiag_ArenaReward.Enable", bInteractArenaReward);
	READ_INT("AuraInvalid", bAuraInvalid);
	READ_STR("NPCScriptName", szScriptName);

	rpcszName = pData->szName;
	READ_END(nTemplateID);
}
