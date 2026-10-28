#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/achievement_data.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"

namespace cqyh::fusion::bindings {

void register_achievement_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto achievement_data_type = cqyh::lua::usertype<ACHIEVEMENT_DATA>(L, globals, "ACHIEVEMENT_DATA", "ACHIEVEMENT_DATA");
    achievement_data_type["nAchievementID"] = sol::property([](const ACHIEVEMENT_DATA& self) { return self.nAchievementID; }, [](ACHIEVEMENT_DATA& self, decltype(ACHIEVEMENT_DATA::nAchievementID) value) { self.nAchievementID = value; });
    achievement_data_type["szName"] = cqyh::lua::string_property(&ACHIEVEMENT_DATA::szName);
    achievement_data_type["vecAchievementType"] = cqyh::lua::array_property(&ACHIEVEMENT_DATA::vecAchievementType);
    achievement_data_type["vecAchievementValue1"] = cqyh::lua::array_property(&ACHIEVEMENT_DATA::vecAchievementValue1);
    achievement_data_type["vecAchievementValue2"] = cqyh::lua::array_property(&ACHIEVEMENT_DATA::vecAchievementValue2);
    achievement_data_type["vecAchievementValue3"] = cqyh::lua::array_property(&ACHIEVEMENT_DATA::vecAchievementValue3);
    achievement_data_type["nAwardSlotCount"] = sol::property([](const ACHIEVEMENT_DATA& self) { return self.nAwardSlotCount; }, [](ACHIEVEMENT_DATA& self, decltype(ACHIEVEMENT_DATA::nAwardSlotCount) value) { self.nAwardSlotCount = value; });
    achievement_data_type["nPreAchievementID1"] = sol::property([](const ACHIEVEMENT_DATA& self) { return self.nPreAchievementID1; }, [](ACHIEVEMENT_DATA& self, decltype(ACHIEVEMENT_DATA::nPreAchievementID1) value) { self.nPreAchievementID1 = value; });
    achievement_data_type["nPreAchievementID2"] = sol::property([](const ACHIEVEMENT_DATA& self) { return self.nPreAchievementID2; }, [](ACHIEVEMENT_DATA& self, decltype(ACHIEVEMENT_DATA::nPreAchievementID2) value) { self.nPreAchievementID2 = value; });
    achievement_data_type["nRewardType"] = cqyh::lua::array_property(&ACHIEVEMENT_DATA::nRewardType);
    achievement_data_type["nRewardID"] = cqyh::lua::array_property(&ACHIEVEMENT_DATA::nRewardID);
    achievement_data_type["nAchievementPts"] = sol::property([](const ACHIEVEMENT_DATA& self) { return self.nAchievementPts; }, [](ACHIEVEMENT_DATA& self, decltype(ACHIEVEMENT_DATA::nAchievementPts) value) { self.nAchievementPts = value; });
    achievement_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, ACHIEVEMENT_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(ACHIEVEMENT_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto handbook_data_type = cqyh::lua::usertype<HANDBOOK_DATA>(L, globals, "HANDBOOK_DATA", "HANDBOOK_DATA");
    handbook_data_type["nHandbookID"] = sol::property([](const HANDBOOK_DATA& self) { return self.nHandbookID; }, [](HANDBOOK_DATA& self, decltype(HANDBOOK_DATA::nHandbookID) value) { self.nHandbookID = value; });
    handbook_data_type["nHandbookType"] = sol::property([](const HANDBOOK_DATA& self) { return self.nHandbookType; }, [](HANDBOOK_DATA& self, decltype(HANDBOOK_DATA::nHandbookType) value) { self.nHandbookType = value; });
    handbook_data_type["nIndex"] = sol::property([](const HANDBOOK_DATA& self) { return self.nIndex; }, [](HANDBOOK_DATA& self, decltype(HANDBOOK_DATA::nIndex) value) { self.nIndex = value; });
    handbook_data_type["nID"] = cqyh::lua::array_property(&HANDBOOK_DATA::nID);
    handbook_data_type["szValue"] = cqyh::lua::string_property(&HANDBOOK_DATA::szValue);
    handbook_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, HANDBOOK_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(HANDBOOK_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_achievement_data_type = cqyh::lua::usertype<CDataManager<ACHIEVEMENT_DATA>>(L, globals, "CDataManager_ACHIEVEMENT_DATA_", "CDataManager<ACHIEVEMENT_DATA>");
    c_data_manager_achievement_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<ACHIEVEMENT_DATA>::GetInstance(); });
    c_data_manager_achievement_data_type.set_function("GetDataCount", [](CDataManager<ACHIEVEMENT_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_achievement_data_type.set_function("GetData", [](CDataManager<ACHIEVEMENT_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_achievement_data_type.set_function("GetID", [](CDataManager<ACHIEVEMENT_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_achievement_data_type.set_function("GetFirstData", [](CDataManager<ACHIEVEMENT_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_achievement_data_type.set_function("GetNextData", [](CDataManager<ACHIEVEMENT_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
