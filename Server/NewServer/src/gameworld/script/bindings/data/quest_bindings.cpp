#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/fusion/inc/quest_data.h"
#include "../../../../../inc/baselib/data_manager.h"
#include "../../../../../inc/baselib/tabfile.h"
#include "../../../../../../Common/fusion/inc/quest_reward_data.h"
#include "../../../../../../Common/define/quest_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::gameworld::bindings {

void register_quest_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto quest_data_type = cqyh::lua::usertype<QUEST_DATA>(L, globals, "QUEST_DATA", "QUEST_DATA");
    quest_data_type["nQuestID"] = sol::property([](const QUEST_DATA& self) { return self.nQuestID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nQuestID) value) { self.nQuestID = value; });
    quest_data_type["eResetType"] = sol::property([](const QUEST_DATA& self) { return self.eResetType; }, [](QUEST_DATA& self, decltype(QUEST_DATA::eResetType) value) { self.eResetType = value; });
    quest_data_type["nQuestType"] = sol::property([](const QUEST_DATA& self) { return self.nQuestType; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nQuestType) value) { self.nQuestType = value; });
    quest_data_type["nCircleID"] = sol::property([](const QUEST_DATA& self) { return self.nCircleID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nCircleID) value) { self.nCircleID = value; });
    quest_data_type["nQuality"] = sol::property([](const QUEST_DATA& self) { return self.nQuality; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nQuality) value) { self.nQuality = value; });
    quest_data_type["dwResetTime"] = sol::property([](const QUEST_DATA& self) { return self.dwResetTime; }, [](QUEST_DATA& self, decltype(QUEST_DATA::dwResetTime) value) { self.dwResetTime = value; });
    quest_data_type["bCanAbandon"] = sol::property([](const QUEST_DATA& self) { return static_cast<bool>(self.bCanAbandon); }, [](QUEST_DATA& self, bool value) { self.bCanAbandon = value; });
    quest_data_type["bCanShare"] = sol::property([](const QUEST_DATA& self) { return static_cast<bool>(self.bCanShare); }, [](QUEST_DATA& self, bool value) { self.bCanShare = value; });
    quest_data_type["bCanPublish"] = sol::property([](const QUEST_DATA& self) { return static_cast<bool>(self.bCanPublish); }, [](QUEST_DATA& self, bool value) { self.bCanPublish = value; });
    quest_data_type["nEmergencyCoolDown"] = sol::property([](const QUEST_DATA& self) { return self.nEmergencyCoolDown; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nEmergencyCoolDown) value) { self.nEmergencyCoolDown = value; });
    quest_data_type["nDurationLimit"] = sol::property([](const QUEST_DATA& self) { return self.nDurationLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nDurationLimit) value) { self.nDurationLimit = value; });
    quest_data_type["szName"] = cqyh::lua::string_property(&QUEST_DATA::szName);
    quest_data_type["nSceneID"] = cqyh::lua::array_property(&QUEST_DATA::nSceneID);
    quest_data_type["nX"] = cqyh::lua::array_property(&QUEST_DATA::nX);
    quest_data_type["nY"] = cqyh::lua::array_property(&QUEST_DATA::nY);
    quest_data_type["nZ"] = cqyh::lua::array_property(&QUEST_DATA::nZ);
    quest_data_type["nMaxCompletedCount"] = sol::property([](const QUEST_DATA& self) { return self.nMaxCompletedCount; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nMaxCompletedCount) value) { self.nMaxCompletedCount = value; });
    quest_data_type["nClassLimit"] = sol::property([](const QUEST_DATA& self) { return self.nClassLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nClassLimit) value) { self.nClassLimit = value; });
    quest_data_type["nSexLimit"] = sol::property([](const QUEST_DATA& self) { return self.nSexLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nSexLimit) value) { self.nSexLimit = value; });
    quest_data_type["nRelationLimit"] = sol::property([](const QUEST_DATA& self) { return self.nRelationLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nRelationLimit) value) { self.nRelationLimit = value; });
    quest_data_type["nPreQuestID1"] = sol::property([](const QUEST_DATA& self) { return self.nPreQuestID1; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nPreQuestID1) value) { self.nPreQuestID1 = value; });
    quest_data_type["nPreQuestID2"] = sol::property([](const QUEST_DATA& self) { return self.nPreQuestID2; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nPreQuestID2) value) { self.nPreQuestID2 = value; });
    quest_data_type["nStartNpcID"] = sol::property([](const QUEST_DATA& self) { return self.nStartNpcID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nStartNpcID) value) { self.nStartNpcID = value; });
    quest_data_type["nStartItemID"] = sol::property([](const QUEST_DATA& self) { return self.nStartItemID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nStartItemID) value) { self.nStartItemID = value; });
    quest_data_type["bStartZone"] = sol::property([](const QUEST_DATA& self) { return static_cast<bool>(self.bStartZone); }, [](QUEST_DATA& self, bool value) { self.bStartZone = value; });
    quest_data_type["nMinLevelLimit"] = sol::property([](const QUEST_DATA& self) { return self.nMinLevelLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nMinLevelLimit) value) { self.nMinLevelLimit = value; });
    quest_data_type["nMaxLevelLimit"] = sol::property([](const QUEST_DATA& self) { return self.nMaxLevelLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nMaxLevelLimit) value) { self.nMaxLevelLimit = value; });
    quest_data_type["nBuffIDLimit"] = sol::property([](const QUEST_DATA& self) { return self.nBuffIDLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nBuffIDLimit) value) { self.nBuffIDLimit = value; });
    quest_data_type["nBuffLevelLimit"] = sol::property([](const QUEST_DATA& self) { return self.nBuffLevelLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nBuffLevelLimit) value) { self.nBuffLevelLimit = value; });
    quest_data_type["nMoneyTypeLimit"] = sol::property([](const QUEST_DATA& self) { return self.nMoneyTypeLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nMoneyTypeLimit) value) { self.nMoneyTypeLimit = value; });
    quest_data_type["nMoneyAmountLimit"] = sol::property([](const QUEST_DATA& self) { return self.nMoneyAmountLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nMoneyAmountLimit) value) { self.nMoneyAmountLimit = value; });
    quest_data_type["nReputationForceID"] = sol::property([](const QUEST_DATA& self) { return self.nReputationForceID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nReputationForceID) value) { self.nReputationForceID = value; });
    quest_data_type["nReputationMinLimit"] = sol::property([](const QUEST_DATA& self) { return self.nReputationMinLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nReputationMinLimit) value) { self.nReputationMinLimit = value; });
    quest_data_type["nReputationMaxLimit"] = sol::property([](const QUEST_DATA& self) { return self.nReputationMaxLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nReputationMaxLimit) value) { self.nReputationMaxLimit = value; });
    quest_data_type["nYearLimit"] = sol::property([](const QUEST_DATA& self) { return self.nYearLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nYearLimit) value) { self.nYearLimit = value; });
    quest_data_type["nMonthLimit"] = sol::property([](const QUEST_DATA& self) { return self.nMonthLimit; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nMonthLimit) value) { self.nMonthLimit = value; });
    quest_data_type["nStartWeekday"] = sol::property([](const QUEST_DATA& self) { return self.nStartWeekday; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nStartWeekday) value) { self.nStartWeekday = value; });
    quest_data_type["nWeekdayDuration"] = sol::property([](const QUEST_DATA& self) { return self.nWeekdayDuration; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nWeekdayDuration) value) { self.nWeekdayDuration = value; });
    quest_data_type["nStartMonthday"] = sol::property([](const QUEST_DATA& self) { return self.nStartMonthday; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nStartMonthday) value) { self.nStartMonthday = value; });
    quest_data_type["nMonthdayDuration"] = sol::property([](const QUEST_DATA& self) { return self.nMonthdayDuration; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nMonthdayDuration) value) { self.nMonthdayDuration = value; });
    quest_data_type["dwAcceptStartTime"] = sol::property([](const QUEST_DATA& self) { return self.dwAcceptStartTime; }, [](QUEST_DATA& self, decltype(QUEST_DATA::dwAcceptStartTime) value) { self.dwAcceptStartTime = value; });
    quest_data_type["dwAcceptEndTime"] = sol::property([](const QUEST_DATA& self) { return self.dwAcceptEndTime; }, [](QUEST_DATA& self, decltype(QUEST_DATA::dwAcceptEndTime) value) { self.dwAcceptEndTime = value; });
    quest_data_type["nAcceptStartHour"] = sol::property([](const QUEST_DATA& self) { return self.nAcceptStartHour; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nAcceptStartHour) value) { self.nAcceptStartHour = value; });
    quest_data_type["nAcceptStartMin"] = sol::property([](const QUEST_DATA& self) { return self.nAcceptStartMin; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nAcceptStartMin) value) { self.nAcceptStartMin = value; });
    quest_data_type["nAcceptEndHour"] = sol::property([](const QUEST_DATA& self) { return self.nAcceptEndHour; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nAcceptEndHour) value) { self.nAcceptEndHour = value; });
    quest_data_type["nAcceptEndMin"] = sol::property([](const QUEST_DATA& self) { return self.nAcceptEndMin; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nAcceptEndMin) value) { self.nAcceptEndMin = value; });
    quest_data_type["nAcceptStartDayTime"] = sol::property([](const QUEST_DATA& self) { return self.nAcceptStartDayTime; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nAcceptStartDayTime) value) { self.nAcceptStartDayTime = value; });
    quest_data_type["nAcceptEndDayTime"] = sol::property([](const QUEST_DATA& self) { return self.nAcceptEndDayTime; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nAcceptEndDayTime) value) { self.nAcceptEndDayTime = value; });
    quest_data_type["vecItemLimitID"] = cqyh::lua::array_property(&QUEST_DATA::vecItemLimitID);
    quest_data_type["vecItemLimitCnt"] = cqyh::lua::array_property(&QUEST_DATA::vecItemLimitCnt);
    quest_data_type["nLimitVarID1"] = sol::property([](const QUEST_DATA& self) { return self.nLimitVarID1; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nLimitVarID1) value) { self.nLimitVarID1 = value; });
    quest_data_type["nLimitVarValue1"] = sol::property([](const QUEST_DATA& self) { return self.nLimitVarValue1; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nLimitVarValue1) value) { self.nLimitVarValue1 = value; });
    quest_data_type["nLimitVarID2"] = sol::property([](const QUEST_DATA& self) { return self.nLimitVarID2; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nLimitVarID2) value) { self.nLimitVarID2 = value; });
    quest_data_type["nLimitVarValue2"] = sol::property([](const QUEST_DATA& self) { return self.nLimitVarValue2; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nLimitVarValue2) value) { self.nLimitVarValue2 = value; });
    quest_data_type["szBeforeAcceptScriptName"] = cqyh::lua::array_property(&QUEST_DATA::szBeforeAcceptScriptName);
    quest_data_type["nOfferMoneyType"] = sol::property([](const QUEST_DATA& self) { return self.nOfferMoneyType; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nOfferMoneyType) value) { self.nOfferMoneyType = value; });
    quest_data_type["nOfferMoneyAmount"] = sol::property([](const QUEST_DATA& self) { return self.nOfferMoneyAmount; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nOfferMoneyAmount) value) { self.nOfferMoneyAmount = value; });
    quest_data_type["nOfferBuffID"] = sol::property([](const QUEST_DATA& self) { return self.nOfferBuffID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nOfferBuffID) value) { self.nOfferBuffID = value; });
    quest_data_type["nOfferBuffLevel"] = sol::property([](const QUEST_DATA& self) { return self.nOfferBuffLevel; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nOfferBuffLevel) value) { self.nOfferBuffLevel = value; });
    quest_data_type["nOfferItemID"] = sol::property([](const QUEST_DATA& self) { return self.nOfferItemID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nOfferItemID) value) { self.nOfferItemID = value; });
    quest_data_type["nOfferItemCnt"] = sol::property([](const QUEST_DATA& self) { return self.nOfferItemCnt; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nOfferItemCnt) value) { self.nOfferItemCnt = value; });
    quest_data_type["szAfterAcceptScriptName"] = cqyh::lua::array_property(&QUEST_DATA::szAfterAcceptScriptName);
    quest_data_type["nFinishNpc"] = sol::property([](const QUEST_DATA& self) { return self.nFinishNpc; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nFinishNpc) value) { self.nFinishNpc = value; });
    quest_data_type["nFinishItemID"] = sol::property([](const QUEST_DATA& self) { return self.nFinishItemID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nFinishItemID) value) { self.nFinishItemID = value; });
    quest_data_type["nCheckBuffID"] = sol::property([](const QUEST_DATA& self) { return self.nCheckBuffID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nCheckBuffID) value) { self.nCheckBuffID = value; });
    quest_data_type["nCheckBuffLevel"] = sol::property([](const QUEST_DATA& self) { return self.nCheckBuffLevel; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nCheckBuffLevel) value) { self.nCheckBuffLevel = value; });
    quest_data_type["nCheckLevel"] = sol::property([](const QUEST_DATA& self) { return self.nCheckLevel; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nCheckLevel) value) { self.nCheckLevel = value; });
    quest_data_type["nCheckKillPlayerLevlStart"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillPlayerLevlStart);
    quest_data_type["nCheckKillPlayerLevlEnd"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillPlayerLevlEnd);
    quest_data_type["nCheckKillPlayerCount"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillPlayerCount);
    quest_data_type["nCheckKillBufPlayerBufID"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillBufPlayerBufID);
    quest_data_type["nCheckKillBufPlayerCount"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillBufPlayerCount);
    quest_data_type["nCheckKillNpcID"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillNpcID);
    quest_data_type["nCheckKillNpcGroupID"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillNpcGroupID);
    quest_data_type["nCheckKillNpcCnt"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillNpcCnt);
    quest_data_type["nCheckKillItemNpcID"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillItemNpcID);
    quest_data_type["nCheckKillItemNpcRate"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillItemNpcRate);
    quest_data_type["nCheckKillItemCnt"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillItemCnt);
    quest_data_type["nCheckKillDoodadID"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillDoodadID);
    quest_data_type["nCheckKillDoodadCnt"] = cqyh::lua::array_property(&QUEST_DATA::nCheckKillDoodadCnt);
    quest_data_type["nCheckItemID"] = cqyh::lua::array_property(&QUEST_DATA::nCheckItemID);
    quest_data_type["nCheckItemCount"] = cqyh::lua::array_property(&QUEST_DATA::nCheckItemCount);
    quest_data_type["nCheckReputationForceID"] = sol::property([](const QUEST_DATA& self) { return self.nCheckReputationForceID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nCheckReputationForceID) value) { self.nCheckReputationForceID = value; });
    quest_data_type["nCheckReputationForceValue"] = sol::property([](const QUEST_DATA& self) { return self.nCheckReputationForceValue; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nCheckReputationForceValue) value) { self.nCheckReputationForceValue = value; });
    quest_data_type["nCheckVarID"] = cqyh::lua::array_property(&QUEST_DATA::nCheckVarID);
    quest_data_type["nCheckVarValue"] = cqyh::lua::array_property(&QUEST_DATA::nCheckVarValue);
    quest_data_type["szBeforeCompleteScriptName"] = cqyh::lua::array_property(&QUEST_DATA::szBeforeCompleteScriptName);
    quest_data_type["nTalkNpcID"] = sol::property([](const QUEST_DATA& self) { return self.nTalkNpcID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nTalkNpcID) value) { self.nTalkNpcID = value; });
    quest_data_type["nTalkVarID"] = sol::property([](const QUEST_DATA& self) { return self.nTalkVarID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nTalkVarID) value) { self.nTalkVarID = value; });
    quest_data_type["nExploreVarID"] = sol::property([](const QUEST_DATA& self) { return self.nExploreVarID; }, [](QUEST_DATA& self, decltype(QUEST_DATA::nExploreVarID) value) { self.nExploreVarID = value; });
    quest_data_type["szAfterCompleteScriptName"] = cqyh::lua::array_property(&QUEST_DATA::szAfterCompleteScriptName);
    quest_data_type["stRewardData"] = &QUEST_DATA::stRewardData;
    quest_data_type["szAbandonScriptName"] = cqyh::lua::array_property(&QUEST_DATA::szAbandonScriptName);
    quest_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, QUEST_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(QUEST_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    quest_data_type.set_function("CheckValidQuestID", [](sol::table, signed int nQuestType, signed int nQuestID) -> decltype(auto) { return static_cast<bool>(QUEST_DATA::CheckValidQuestID(nQuestType,nQuestID)); });
    auto reward_quest_money_cost_data_type = cqyh::lua::usertype<REWARD_QUEST_MONEY_COST_DATA>(L, globals, "REWARD_QUEST_MONEY_COST_DATA", "REWARD_QUEST_MONEY_COST_DATA");
    reward_quest_money_cost_data_type["nTime"] = sol::property([](const REWARD_QUEST_MONEY_COST_DATA& self) { return self.nTime; }, [](REWARD_QUEST_MONEY_COST_DATA& self, decltype(REWARD_QUEST_MONEY_COST_DATA::nTime) value) { self.nTime = value; });
    reward_quest_money_cost_data_type["nMoneyCost"] = sol::property([](const REWARD_QUEST_MONEY_COST_DATA& self) { return self.nMoneyCost; }, [](REWARD_QUEST_MONEY_COST_DATA& self, decltype(REWARD_QUEST_MONEY_COST_DATA::nMoneyCost) value) { self.nMoneyCost = value; });
    reward_quest_money_cost_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, REWARD_QUEST_MONEY_COST_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(REWARD_QUEST_MONEY_COST_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto quest_recycle_data_type = cqyh::lua::usertype<QUEST_RECYCLE_DATA>(L, globals, "QUEST_RECYCLE_DATA", "QUEST_RECYCLE_DATA");
    quest_recycle_data_type["nItemLevel"] = sol::property([](const QUEST_RECYCLE_DATA& self) { return self.nItemLevel; }, [](QUEST_RECYCLE_DATA& self, decltype(QUEST_RECYCLE_DATA::nItemLevel) value) { self.nItemLevel = value; });
    quest_recycle_data_type["nItemColor"] = sol::property([](const QUEST_RECYCLE_DATA& self) { return self.nItemColor; }, [](QUEST_RECYCLE_DATA& self, decltype(QUEST_RECYCLE_DATA::nItemColor) value) { self.nItemColor = value; });
    quest_recycle_data_type["nItemSubType"] = sol::property([](const QUEST_RECYCLE_DATA& self) { return self.nItemSubType; }, [](QUEST_RECYCLE_DATA& self, decltype(QUEST_RECYCLE_DATA::nItemSubType) value) { self.nItemSubType = value; });
    quest_recycle_data_type["nVarIndex"] = sol::property([](const QUEST_RECYCLE_DATA& self) { return self.nVarIndex; }, [](QUEST_RECYCLE_DATA& self, decltype(QUEST_RECYCLE_DATA::nVarIndex) value) { self.nVarIndex = value; });
    quest_recycle_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, QUEST_RECYCLE_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(QUEST_RECYCLE_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_quest_data_type = cqyh::lua::usertype<CDataManager<QUEST_DATA>>(L, globals, "CDataManager_QUEST_DATA_", "CDataManager<QUEST_DATA>");
    c_data_manager_quest_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<QUEST_DATA>::GetInstance(); });
    c_data_manager_quest_data_type.set_function("GetDataCount", [](CDataManager<QUEST_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_quest_data_type.set_function("GetData", [](CDataManager<QUEST_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_quest_data_type.set_function("GetID", [](CDataManager<QUEST_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_quest_data_type.set_function("GetFirstData", [](CDataManager<QUEST_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_quest_data_type.set_function("GetNextData", [](CDataManager<QUEST_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
