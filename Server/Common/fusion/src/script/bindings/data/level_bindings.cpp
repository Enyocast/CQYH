#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/level_data.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"

namespace cqyh::fusion::bindings {

void register_level_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto role_level_data_type = cqyh::lua::usertype<ROLE_LEVEL_DATA>(L, globals, "ROLE_LEVEL_DATA", "ROLE_LEVEL_DATA");
    role_level_data_type["m_nLevel"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nLevel; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nLevel) value) { self.m_nLevel = value; });
    role_level_data_type["m_nMaxExp"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nMaxExp; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nMaxExp) value) { self.m_nMaxExp = value; });
    role_level_data_type["m_nPow"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nPow; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nPow) value) { self.m_nPow = value; });
    role_level_data_type["m_nMoneyType01DailyUseLimit"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nMoneyType01DailyUseLimit; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nMoneyType01DailyUseLimit) value) { self.m_nMoneyType01DailyUseLimit = value; });
    role_level_data_type["m_nMoneyType02DailyEarnLimit"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nMoneyType02DailyEarnLimit; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nMoneyType02DailyEarnLimit) value) { self.m_nMoneyType02DailyEarnLimit = value; });
    role_level_data_type["m_nMoneyTypeBFTotalLimit"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nMoneyTypeBFTotalLimit; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nMoneyTypeBFTotalLimit) value) { self.m_nMoneyTypeBFTotalLimit = value; });
    role_level_data_type["m_nMoneyTypeBFWeeklyEarnLimit"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nMoneyTypeBFWeeklyEarnLimit; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nMoneyTypeBFWeeklyEarnLimit) value) { self.m_nMoneyTypeBFWeeklyEarnLimit = value; });
    role_level_data_type["m_nMoneyTypeArenaTotalLimit"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nMoneyTypeArenaTotalLimit; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nMoneyTypeArenaTotalLimit) value) { self.m_nMoneyTypeArenaTotalLimit = value; });
    role_level_data_type["m_nMoneyTypeArenaWeeklyEarnLimit"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nMoneyTypeArenaWeeklyEarnLimit; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nMoneyTypeArenaWeeklyEarnLimit) value) { self.m_nMoneyTypeArenaWeeklyEarnLimit = value; });
    role_level_data_type["m_nDailyExpLimit"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nDailyExpLimit; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nDailyExpLimit) value) { self.m_nDailyExpLimit = value; });
    role_level_data_type["m_nMaxExtraExp"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nMaxExtraExp; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nMaxExtraExp) value) { self.m_nMaxExtraExp = value; });
    role_level_data_type["m_nDailyExtraExp"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nDailyExtraExp; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nDailyExtraExp) value) { self.m_nDailyExtraExp = value; });
    role_level_data_type["m_nGoldPoolPer5Min"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nGoldPoolPer5Min; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nGoldPoolPer5Min) value) { self.m_nGoldPoolPer5Min = value; });
    role_level_data_type["m_nExerciseExpPerHour"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nExerciseExpPerHour; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nExerciseExpPerHour) value) { self.m_nExerciseExpPerHour = value; });
    role_level_data_type["m_nOnlineExtraExpPer5Min"] = sol::property([](const ROLE_LEVEL_DATA& self) { return self.m_nOnlineExtraExpPer5Min; }, [](ROLE_LEVEL_DATA& self, decltype(ROLE_LEVEL_DATA::m_nOnlineExtraExpPer5Min) value) { self.m_nOnlineExtraExpPer5Min = value; });
    role_level_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, ROLE_LEVEL_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(ROLE_LEVEL_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto hero_level_data_type = cqyh::lua::usertype<HERO_LEVEL_DATA>(L, globals, "HERO_LEVEL_DATA", "HERO_LEVEL_DATA");
    hero_level_data_type["m_nLevel"] = sol::property([](const HERO_LEVEL_DATA& self) { return self.m_nLevel; }, [](HERO_LEVEL_DATA& self, decltype(HERO_LEVEL_DATA::m_nLevel) value) { self.m_nLevel = value; });
    hero_level_data_type["m_nMaxExp"] = sol::property([](const HERO_LEVEL_DATA& self) { return self.m_nMaxExp; }, [](HERO_LEVEL_DATA& self, decltype(HERO_LEVEL_DATA::m_nMaxExp) value) { self.m_nMaxExp = value; });
    hero_level_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, HERO_LEVEL_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(HERO_LEVEL_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    globals.set_function("GetMaxExp", [](signed int nObjType, signed int nLevel) -> decltype(auto) { return GetMaxExp(nObjType,nLevel); });
    auto c_data_manager_role_level_data_type = cqyh::lua::usertype<CDataManager<ROLE_LEVEL_DATA>>(L, globals, "CDataManager_ROLE_LEVEL_DATA_", "CDataManager<ROLE_LEVEL_DATA>");
    c_data_manager_role_level_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<ROLE_LEVEL_DATA>::GetInstance(); });
    c_data_manager_role_level_data_type.set_function("GetDataCount", [](CDataManager<ROLE_LEVEL_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_role_level_data_type.set_function("GetData", [](CDataManager<ROLE_LEVEL_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_role_level_data_type.set_function("GetID", [](CDataManager<ROLE_LEVEL_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_role_level_data_type.set_function("GetFirstData", [](CDataManager<ROLE_LEVEL_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_role_level_data_type.set_function("GetNextData", [](CDataManager<ROLE_LEVEL_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
    auto c_data_manager_hero_level_data_type = cqyh::lua::usertype<CDataManager<HERO_LEVEL_DATA>>(L, globals, "CDataManager_HERO_LEVEL_DATA_", "CDataManager<HERO_LEVEL_DATA>");
    c_data_manager_hero_level_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<HERO_LEVEL_DATA>::GetInstance(); });
    c_data_manager_hero_level_data_type.set_function("GetDataCount", [](CDataManager<HERO_LEVEL_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_hero_level_data_type.set_function("GetData", [](CDataManager<HERO_LEVEL_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_hero_level_data_type.set_function("GetID", [](CDataManager<HERO_LEVEL_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_hero_level_data_type.set_function("GetFirstData", [](CDataManager<HERO_LEVEL_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_hero_level_data_type.set_function("GetNextData", [](CDataManager<HERO_LEVEL_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
