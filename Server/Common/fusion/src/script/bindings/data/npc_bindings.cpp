#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/npc_data.h"
#include "../../../../inc/shop_data.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"
#include "../../../../inc/adventure_data.h"

namespace cqyh::fusion::bindings {

void register_npc_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto npc_data_type = cqyh::lua::usertype<NPC_DATA>(L, globals, "NPC_DATA", "NPC_DATA");
    npc_data_type["nTemplateID"] = sol::property([](const NPC_DATA& self) { return self.nTemplateID; }, [](NPC_DATA& self, decltype(NPC_DATA::nTemplateID) value) { self.nTemplateID = value; });
    npc_data_type["nClientTemplateID"] = sol::property([](const NPC_DATA& self) { return self.nClientTemplateID; }, [](NPC_DATA& self, decltype(NPC_DATA::nClientTemplateID) value) { self.nClientTemplateID = value; });
    npc_data_type["szDisplayName"] = cqyh::lua::string_property(&NPC_DATA::szDisplayName);
    npc_data_type["szName"] = cqyh::lua::string_property(&NPC_DATA::szName);
    npc_data_type["nLevel"] = sol::property([](const NPC_DATA& self) { return self.nLevel; }, [](NPC_DATA& self, decltype(NPC_DATA::nLevel) value) { self.nLevel = value; });
    npc_data_type["nPatternID"] = sol::property([](const NPC_DATA& self) { return self.nPatternID; }, [](NPC_DATA& self, decltype(NPC_DATA::nPatternID) value) { self.nPatternID = value; });
    npc_data_type["nQuality"] = sol::property([](const NPC_DATA& self) { return self.nQuality; }, [](NPC_DATA& self, decltype(NPC_DATA::nQuality) value) { self.nQuality = value; });
    npc_data_type["nBroadcast"] = sol::property([](const NPC_DATA& self) { return self.nBroadcast; }, [](NPC_DATA& self, decltype(NPC_DATA::nBroadcast) value) { self.nBroadcast = value; });
    npc_data_type["nForceID"] = sol::property([](const NPC_DATA& self) { return self.nForceID; }, [](NPC_DATA& self, decltype(NPC_DATA::nForceID) value) { self.nForceID = value; });
    npc_data_type["bReduceReputation"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bReduceReputation); }, [](NPC_DATA& self, bool value) { self.bReduceReputation = value; });
    npc_data_type["nSpecies"] = sol::property([](const NPC_DATA& self) { return self.nSpecies; }, [](NPC_DATA& self, decltype(NPC_DATA::nSpecies) value) { self.nSpecies = value; });
    npc_data_type["nRivalForceID"] = sol::property([](const NPC_DATA& self) { return self.nRivalForceID; }, [](NPC_DATA& self, decltype(NPC_DATA::nRivalForceID) value) { self.nRivalForceID = value; });
    npc_data_type["nGroupID"] = sol::property([](const NPC_DATA& self) { return self.nGroupID; }, [](NPC_DATA& self, decltype(NPC_DATA::nGroupID) value) { self.nGroupID = value; });
    npc_data_type["nBodyType"] = sol::property([](const NPC_DATA& self) { return self.nBodyType; }, [](NPC_DATA& self, decltype(NPC_DATA::nBodyType) value) { self.nBodyType = value; });
    npc_data_type["nSpellEffectGroup"] = sol::property([](const NPC_DATA& self) { return self.nSpellEffectGroup; }, [](NPC_DATA& self, decltype(NPC_DATA::nSpellEffectGroup) value) { self.nSpellEffectGroup = value; });
    npc_data_type["nSpawnTime"] = sol::property([](const NPC_DATA& self) { return self.nSpawnTime; }, [](NPC_DATA& self, decltype(NPC_DATA::nSpawnTime) value) { self.nSpawnTime = value; });
    npc_data_type["nReviveTime"] = sol::property([](const NPC_DATA& self) { return self.nReviveTime; }, [](NPC_DATA& self, decltype(NPC_DATA::nReviveTime) value) { self.nReviveTime = value; });
    npc_data_type["nCorpseTime"] = sol::property([](const NPC_DATA& self) { return self.nCorpseTime; }, [](NPC_DATA& self, decltype(NPC_DATA::nCorpseTime) value) { self.nCorpseTime = value; });
    npc_data_type["nMinRespawnTime"] = sol::property([](const NPC_DATA& self) { return self.nMinRespawnTime; }, [](NPC_DATA& self, decltype(NPC_DATA::nMinRespawnTime) value) { self.nMinRespawnTime = value; });
    npc_data_type["nMaxRespawnTime"] = sol::property([](const NPC_DATA& self) { return self.nMaxRespawnTime; }, [](NPC_DATA& self, decltype(NPC_DATA::nMaxRespawnTime) value) { self.nMaxRespawnTime = value; });
    npc_data_type["nAIID"] = sol::property([](const NPC_DATA& self) { return self.nAIID; }, [](NPC_DATA& self, decltype(NPC_DATA::nAIID) value) { self.nAIID = value; });
    npc_data_type["bImmunePassiveMove"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bImmunePassiveMove); }, [](NPC_DATA& self, bool value) { self.bImmunePassiveMove = value; });
    npc_data_type["bInvincible"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInvincible); }, [](NPC_DATA& self, bool value) { self.bInvincible = value; });
    npc_data_type["bAlwaysRun"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bAlwaysRun); }, [](NPC_DATA& self, bool value) { self.bAlwaysRun = value; });
    npc_data_type["bCanbeThrown"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bCanbeThrown); }, [](NPC_DATA& self, bool value) { self.bCanbeThrown = value; });
    npc_data_type["bIgnoreInvisible"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bIgnoreInvisible); }, [](NPC_DATA& self, bool value) { self.bIgnoreInvisible = value; });
    npc_data_type["bCounterInvisible"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bCounterInvisible); }, [](NPC_DATA& self, bool value) { self.bCounterInvisible = value; });
    npc_data_type["nAttackRange"] = sol::property([](const NPC_DATA& self) { return self.nAttackRange; }, [](NPC_DATA& self, decltype(NPC_DATA::nAttackRange) value) { self.nAttackRange = value; });
    npc_data_type["bExclusive"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bExclusive); }, [](NPC_DATA& self, bool value) { self.bExclusive = value; });
    npc_data_type["bNeverBeHit"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bNeverBeHit); }, [](NPC_DATA& self, bool value) { self.bNeverBeHit = value; });
    npc_data_type["bProfit"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bProfit); }, [](NPC_DATA& self, bool value) { self.bProfit = value; });
    npc_data_type["nExpRate"] = sol::property([](const NPC_DATA& self) { return self.nExpRate; }, [](NPC_DATA& self, decltype(NPC_DATA::nExpRate) value) { self.nExpRate = value; });
    npc_data_type["nSoulRate"] = sol::property([](const NPC_DATA& self) { return self.nSoulRate; }, [](NPC_DATA& self, decltype(NPC_DATA::nSoulRate) value) { self.nSoulRate = value; });
    npc_data_type["bDailyExp"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bDailyExp); }, [](NPC_DATA& self, bool value) { self.bDailyExp = value; });
    npc_data_type["bAuraInvalid"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bAuraInvalid); }, [](NPC_DATA& self, bool value) { self.bAuraInvalid = value; });
    npc_data_type["nKillPlayerVarIndex"] = sol::property([](const NPC_DATA& self) { return self.nKillPlayerVarIndex; }, [](NPC_DATA& self, decltype(NPC_DATA::nKillPlayerVarIndex) value) { self.nKillPlayerVarIndex = value; });
    npc_data_type["nBeKilledVarIndex"] = sol::property([](const NPC_DATA& self) { return self.nBeKilledVarIndex; }, [](NPC_DATA& self, decltype(NPC_DATA::nBeKilledVarIndex) value) { self.nBeKilledVarIndex = value; });
    npc_data_type["nShopID"] = sol::property([](const NPC_DATA& self) { return self.nShopID; }, [](NPC_DATA& self, decltype(NPC_DATA::nShopID) value) { self.nShopID = value; });
    npc_data_type["nBlackMarketID"] = sol::property([](const NPC_DATA& self) { return self.nBlackMarketID; }, [](NPC_DATA& self, decltype(NPC_DATA::nBlackMarketID) value) { self.nBlackMarketID = value; });
    npc_data_type["bInteractBank"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractBank); }, [](NPC_DATA& self, bool value) { self.bInteractBank = value; });
    npc_data_type["bInteractGuildBank"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractGuildBank); }, [](NPC_DATA& self, bool value) { self.bInteractGuildBank = value; });
    npc_data_type["bInteractRewardQuest"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractRewardQuest); }, [](NPC_DATA& self, bool value) { self.bInteractRewardQuest = value; });
    npc_data_type["bInteractCreateGuild"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractCreateGuild); }, [](NPC_DATA& self, bool value) { self.bInteractCreateGuild = value; });
    npc_data_type["bInteractGuildSalary"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractGuildSalary); }, [](NPC_DATA& self, bool value) { self.bInteractGuildSalary = value; });
    npc_data_type["bInteractAuction"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractAuction); }, [](NPC_DATA& self, bool value) { self.bInteractAuction = value; });
    npc_data_type["bInteractRune"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractRune); }, [](NPC_DATA& self, bool value) { self.bInteractRune = value; });
    npc_data_type["bInteractSoul"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractSoul); }, [](NPC_DATA& self, bool value) { self.bInteractSoul = value; });
    npc_data_type["bInteractWeaponLevelUpPutIn"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractWeaponLevelUpPutIn); }, [](NPC_DATA& self, bool value) { self.bInteractWeaponLevelUpPutIn = value; });
    npc_data_type["bInteractWeaponLevelUpTakeOut"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractWeaponLevelUpTakeOut); }, [](NPC_DATA& self, bool value) { self.bInteractWeaponLevelUpTakeOut = value; });
    npc_data_type["bInteractSpecialRepair"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractSpecialRepair); }, [](NPC_DATA& self, bool value) { self.bInteractSpecialRepair = value; });
    npc_data_type["bInteractGamble"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractGamble); }, [](NPC_DATA& self, bool value) { self.bInteractGamble = value; });
    npc_data_type["bInteractExercise"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractExercise); }, [](NPC_DATA& self, bool value) { self.bInteractExercise = value; });
    npc_data_type["bInteractSpellBookGamble"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractSpellBookGamble); }, [](NPC_DATA& self, bool value) { self.bInteractSpellBookGamble = value; });
    npc_data_type["bInteractArenaReward"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bInteractArenaReward); }, [](NPC_DATA& self, bool value) { self.bInteractArenaReward = value; });
    npc_data_type["nCorpseDoodadID"] = sol::property([](const NPC_DATA& self) { return self.nCorpseDoodadID; }, [](NPC_DATA& self, decltype(NPC_DATA::nCorpseDoodadID) value) { self.nCorpseDoodadID = value; });
    npc_data_type["bDieIDMonitor"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bDieIDMonitor); }, [](NPC_DATA& self, bool value) { self.bDieIDMonitor = value; });
    npc_data_type["bStatMoney"] = sol::property([](const NPC_DATA& self) { return static_cast<bool>(self.bStatMoney); }, [](NPC_DATA& self, bool value) { self.bStatMoney = value; });
    npc_data_type["nBigDropInterval"] = sol::property([](const NPC_DATA& self) { return self.nBigDropInterval; }, [](NPC_DATA& self, decltype(NPC_DATA::nBigDropInterval) value) { self.nBigDropInterval = value; });
    npc_data_type["nRuneGroup"] = sol::property([](const NPC_DATA& self) { return self.nRuneGroup; }, [](NPC_DATA& self, decltype(NPC_DATA::nRuneGroup) value) { self.nRuneGroup = value; });
    npc_data_type["nHandbookType"] = sol::property([](const NPC_DATA& self) { return self.nHandbookType; }, [](NPC_DATA& self, decltype(NPC_DATA::nHandbookType) value) { self.nHandbookType = value; });
    npc_data_type["nHandbookIndex"] = sol::property([](const NPC_DATA& self) { return self.nHandbookIndex; }, [](NPC_DATA& self, decltype(NPC_DATA::nHandbookIndex) value) { self.nHandbookIndex = value; });
    npc_data_type["nKillNpcQuestID"] = sol::property([](const NPC_DATA& self) { return self.nKillNpcQuestID; }, [](NPC_DATA& self, decltype(NPC_DATA::nKillNpcQuestID) value) { self.nKillNpcQuestID = value; });
    npc_data_type["pAdventureData"] = sol::readonly(&NPC_DATA::pAdventureData);
    npc_data_type["szScriptName"] = cqyh::lua::string_property(&NPC_DATA::szScriptName);
    npc_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, NPC_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(NPC_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_npc_data_type = cqyh::lua::usertype<CDataManager<NPC_DATA>>(L, globals, "CDataManager_NPC_DATA_", "CDataManager<NPC_DATA>");
    c_data_manager_npc_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<NPC_DATA>::GetInstance(); });
    c_data_manager_npc_data_type.set_function("GetDataCount", [](CDataManager<NPC_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_npc_data_type.set_function("GetData", [](CDataManager<NPC_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_npc_data_type.set_function("GetID", [](CDataManager<NPC_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_npc_data_type.set_function("GetFirstData", [](CDataManager<NPC_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_npc_data_type.set_function("GetNextData", [](CDataManager<NPC_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
