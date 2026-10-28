#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/ai_data.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"

namespace cqyh::fusion::bindings {

void register_ai_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_AI_ID"] = static_cast<lua_Number>(MAX_AI_ID);
    globals["MAX_AI_INIT_AURA_COUNT"] = static_cast<lua_Number>(MAX_AI_INIT_AURA_COUNT);
    globals["MAX_AI_DATA_PARAM_COUNT"] = static_cast<lua_Number>(MAX_AI_DATA_PARAM_COUNT);
    globals["nastInvalid"] = static_cast<lua_Number>(nastInvalid);
    globals["nastNormalSpell1"] = static_cast<lua_Number>(nastNormalSpell1);
    globals["nastNormalSpell2"] = static_cast<lua_Number>(nastNormalSpell2);
    globals["nastHelpFriendSpell1"] = static_cast<lua_Number>(nastHelpFriendSpell1);
    globals["nastHelpFriendSpell2"] = static_cast<lua_Number>(nastHelpFriendSpell2);
    globals["nastCorpseSpell"] = static_cast<lua_Number>(nastCorpseSpell);
    globals["nastSignalIssuerSpell"] = static_cast<lua_Number>(nastSignalIssuerSpell);
    globals["nastSignalTargetSpell"] = static_cast<lua_Number>(nastSignalTargetSpell);
    globals["nastNormalSpell3"] = static_cast<lua_Number>(nastNormalSpell3);
    globals["nastNormalSpell4"] = static_cast<lua_Number>(nastNormalSpell4);
    globals["nastEnterFightSpell"] = static_cast<lua_Number>(nastEnterFightSpell);
    globals["nastChaseSpell"] = static_cast<lua_Number>(nastChaseSpell);
    globals["nastInitSpell1"] = static_cast<lua_Number>(nastInitSpell1);
    globals["nastInitSpell2"] = static_cast<lua_Number>(nastInitSpell2);
    globals["nastInitSpell3"] = static_cast<lua_Number>(nastInitSpell3);
    globals["nastDeadSpell"] = static_cast<lua_Number>(nastDeadSpell);
    globals["nastIdleSpell"] = static_cast<lua_Number>(nastIdleSpell);
    globals["nastTotal"] = static_cast<lua_Number>(nastTotal);
    globals["nastGlobalCDTimer"] = static_cast<lua_Number>(nastGlobalCDTimer);
    globals["nastLiveTimer"] = static_cast<lua_Number>(nastLiveTimer);
    globals["nastFleeTimer"] = static_cast<lua_Number>(nastFleeTimer);
    globals["nastThreatSingalTimer"] = static_cast<lua_Number>(nastThreatSingalTimer);
    globals["nastChanceTargetTimer"] = static_cast<lua_Number>(nastChanceTargetTimer);
    globals["nastScanNearbyTimer"] = static_cast<lua_Number>(nastScanNearbyTimer);
    globals["nastStepAroundTimer"] = static_cast<lua_Number>(nastStepAroundTimer);
    globals["nastWithdrawTimer"] = static_cast<lua_Number>(nastWithdrawTimer);
    globals["nastCustom"] = static_cast<lua_Number>(nastCustom);
    auto new_ai_data_type = cqyh::lua::usertype<NEW_AI_DATA>(L, globals, "NEW_AI_DATA", "NEW_AI_DATA");
    new_ai_data_type["nAIID"] = sol::property([](const NEW_AI_DATA& self) { return self.nAIID; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nAIID) value) { self.nAIID = value; });
    new_ai_data_type["szScriptName"] = cqyh::lua::string_property(&NEW_AI_DATA::szScriptName);
    new_ai_data_type["nWalkSpeed"] = sol::property([](const NEW_AI_DATA& self) { return self.nWalkSpeed; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nWalkSpeed) value) { self.nWalkSpeed = value; });
    new_ai_data_type["nRunSpeed"] = sol::property([](const NEW_AI_DATA& self) { return self.nRunSpeed; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nRunSpeed) value) { self.nRunSpeed = value; });
    new_ai_data_type["nRotateSpeed"] = sol::property([](const NEW_AI_DATA& self) { return self.nRotateSpeed; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nRotateSpeed) value) { self.nRotateSpeed = value; });
    new_ai_data_type["bPatrol"] = sol::property([](const NEW_AI_DATA& self) { return static_cast<bool>(self.bPatrol); }, [](NEW_AI_DATA& self, bool value) { self.bPatrol = value; });
    new_ai_data_type["bFollow"] = sol::property([](const NEW_AI_DATA& self) { return static_cast<bool>(self.bFollow); }, [](NEW_AI_DATA& self, bool value) { self.bFollow = value; });
    new_ai_data_type["bCanRun"] = sol::property([](const NEW_AI_DATA& self) { return static_cast<bool>(self.bCanRun); }, [](NEW_AI_DATA& self, bool value) { self.bCanRun = value; });
    new_ai_data_type["bAlwaysRun"] = sol::property([](const NEW_AI_DATA& self) { return static_cast<bool>(self.bAlwaysRun); }, [](NEW_AI_DATA& self, bool value) { self.bAlwaysRun = value; });
    new_ai_data_type["nScanEnemyRange"] = sol::property([](const NEW_AI_DATA& self) { return self.nScanEnemyRange; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nScanEnemyRange) value) { self.nScanEnemyRange = value; });
    new_ai_data_type["nScanFriendRange"] = sol::property([](const NEW_AI_DATA& self) { return self.nScanFriendRange; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nScanFriendRange) value) { self.nScanFriendRange = value; });
    new_ai_data_type["nChaseRange"] = sol::property([](const NEW_AI_DATA& self) { return self.nChaseRange; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nChaseRange) value) { self.nChaseRange = value; });
    new_ai_data_type["nPreferDistance"] = sol::property([](const NEW_AI_DATA& self) { return self.nPreferDistance; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nPreferDistance) value) { self.nPreferDistance = value; });
    new_ai_data_type["nWithdrawThreshold"] = sol::property([](const NEW_AI_DATA& self) { return self.nWithdrawThreshold; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nWithdrawThreshold) value) { self.nWithdrawThreshold = value; });
    new_ai_data_type["nChaseThreshold"] = sol::property([](const NEW_AI_DATA& self) { return self.nChaseThreshold; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nChaseThreshold) value) { self.nChaseThreshold = value; });
    new_ai_data_type["nChaseDelayTime"] = sol::property([](const NEW_AI_DATA& self) { return self.nChaseDelayTime; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nChaseDelayTime) value) { self.nChaseDelayTime = value; });
    new_ai_data_type["nInitAuraID"] = cqyh::lua::array_property(&NEW_AI_DATA::nInitAuraID);
    new_ai_data_type["nLiveTime"] = sol::property([](const NEW_AI_DATA& self) { return self.nLiveTime; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nLiveTime) value) { self.nLiveTime = value; });
    new_ai_data_type["bDisappearOnTimeout"] = sol::property([](const NEW_AI_DATA& self) { return static_cast<bool>(self.bDisappearOnTimeout); }, [](NEW_AI_DATA& self, bool value) { self.bDisappearOnTimeout = value; });
    new_ai_data_type["nWanderRange"] = sol::property([](const NEW_AI_DATA& self) { return self.nWanderRange; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nWanderRange) value) { self.nWanderRange = value; });
    new_ai_data_type["nWanderInterval"] = sol::property([](const NEW_AI_DATA& self) { return self.nWanderInterval; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nWanderInterval) value) { self.nWanderInterval = value; });
    new_ai_data_type["nSpellID"] = cqyh::lua::array_property(&NEW_AI_DATA::nSpellID);
    new_ai_data_type["nSpellChance"] = cqyh::lua::array_property(&NEW_AI_DATA::nSpellChance);
    new_ai_data_type["nSpellCDTime"] = cqyh::lua::array_property(&NEW_AI_DATA::nSpellCDTime);
    new_ai_data_type["nSelfHpPercent"] = cqyh::lua::array_property(&NEW_AI_DATA::nSelfHpPercent);
    new_ai_data_type["nGlobalCDTime"] = sol::property([](const NEW_AI_DATA& self) { return self.nGlobalCDTime; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nGlobalCDTime) value) { self.nGlobalCDTime = value; });
    new_ai_data_type["nFriendlyNpcTemplateID"] = sol::property([](const NEW_AI_DATA& self) { return self.nFriendlyNpcTemplateID; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nFriendlyNpcTemplateID) value) { self.nFriendlyNpcTemplateID = value; });
    new_ai_data_type["bFriendlyCorpse"] = sol::property([](const NEW_AI_DATA& self) { return static_cast<bool>(self.bFriendlyCorpse); }, [](NEW_AI_DATA& self, bool value) { self.bFriendlyCorpse = value; });
    new_ai_data_type["nCorpseTemplateID"] = sol::property([](const NEW_AI_DATA& self) { return self.nCorpseTemplateID; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nCorpseTemplateID) value) { self.nCorpseTemplateID = value; });
    new_ai_data_type["nIssuerSpellSignalType"] = sol::property([](const NEW_AI_DATA& self) { return self.nIssuerSpellSignalType; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nIssuerSpellSignalType) value) { self.nIssuerSpellSignalType = value; });
    new_ai_data_type["nIssuerSpellSignalRange"] = sol::property([](const NEW_AI_DATA& self) { return self.nIssuerSpellSignalRange; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nIssuerSpellSignalRange) value) { self.nIssuerSpellSignalRange = value; });
    new_ai_data_type["nTargetSpellSignalType"] = sol::property([](const NEW_AI_DATA& self) { return self.nTargetSpellSignalType; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nTargetSpellSignalType) value) { self.nTargetSpellSignalType = value; });
    new_ai_data_type["nTargetSpellSignalRange"] = sol::property([](const NEW_AI_DATA& self) { return self.nTargetSpellSignalRange; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nTargetSpellSignalRange) value) { self.nTargetSpellSignalRange = value; });
    new_ai_data_type["nFleeHpPercent"] = sol::property([](const NEW_AI_DATA& self) { return self.nFleeHpPercent; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nFleeHpPercent) value) { self.nFleeHpPercent = value; });
    new_ai_data_type["nFleeChance"] = sol::property([](const NEW_AI_DATA& self) { return self.nFleeChance; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nFleeChance) value) { self.nFleeChance = value; });
    new_ai_data_type["nFleeDuration"] = sol::property([](const NEW_AI_DATA& self) { return self.nFleeDuration; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nFleeDuration) value) { self.nFleeDuration = value; });
    new_ai_data_type["nStepAroundChance"] = sol::property([](const NEW_AI_DATA& self) { return self.nStepAroundChance; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nStepAroundChance) value) { self.nStepAroundChance = value; });
    new_ai_data_type["nStepAroundCDTime"] = sol::property([](const NEW_AI_DATA& self) { return self.nStepAroundCDTime; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nStepAroundCDTime) value) { self.nStepAroundCDTime = value; });
    new_ai_data_type["nChangeTargetChance"] = sol::property([](const NEW_AI_DATA& self) { return self.nChangeTargetChance; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nChangeTargetChance) value) { self.nChangeTargetChance = value; });
    new_ai_data_type["nChangeTargetCDTime"] = sol::property([](const NEW_AI_DATA& self) { return self.nChangeTargetCDTime; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nChangeTargetCDTime) value) { self.nChangeTargetCDTime = value; });
    new_ai_data_type["nSpreadThreatCount"] = sol::property([](const NEW_AI_DATA& self) { return self.nSpreadThreatCount; }, [](NEW_AI_DATA& self, decltype(NEW_AI_DATA::nSpreadThreatCount) value) { self.nSpreadThreatCount = value; });
    new_ai_data_type["nParam"] = cqyh::lua::array_property(&NEW_AI_DATA::nParam);
    new_ai_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, NEW_AI_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(NEW_AI_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_new_ai_data_type = cqyh::lua::usertype<CDataManager<NEW_AI_DATA>>(L, globals, "CDataManager_NEW_AI_DATA_", "CDataManager<NEW_AI_DATA>");
    c_data_manager_new_ai_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<NEW_AI_DATA>::GetInstance(); });
    c_data_manager_new_ai_data_type.set_function("GetDataCount", [](CDataManager<NEW_AI_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_new_ai_data_type.set_function("GetData", [](CDataManager<NEW_AI_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_new_ai_data_type.set_function("GetID", [](CDataManager<NEW_AI_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_new_ai_data_type.set_function("GetFirstData", [](CDataManager<NEW_AI_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_new_ai_data_type.set_function("GetNextData", [](CDataManager<NEW_AI_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
