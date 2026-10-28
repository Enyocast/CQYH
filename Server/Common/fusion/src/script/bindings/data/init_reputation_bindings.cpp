#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/init_reputation_data.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"

namespace cqyh::fusion::bindings {

void register_init_reputation_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto init_reputation_data_type = cqyh::lua::usertype<INIT_REPUTATION_DATA>(L, globals, "INIT_REPUTATION_DATA", "INIT_REPUTATION_DATA");
    init_reputation_data_type["nForceID"] = sol::property([](const INIT_REPUTATION_DATA& self) { return self.nForceID; }, [](INIT_REPUTATION_DATA& self, decltype(INIT_REPUTATION_DATA::nForceID) value) { self.nForceID = value; });
    init_reputation_data_type["nInitValue"] = sol::property([](const INIT_REPUTATION_DATA& self) { return self.nInitValue; }, [](INIT_REPUTATION_DATA& self, decltype(INIT_REPUTATION_DATA::nInitValue) value) { self.nInitValue = value; });
    init_reputation_data_type["nMaxValue"] = sol::property([](const INIT_REPUTATION_DATA& self) { return self.nMaxValue; }, [](INIT_REPUTATION_DATA& self, decltype(INIT_REPUTATION_DATA::nMaxValue) value) { self.nMaxValue = value; });
    init_reputation_data_type["bActive"] = sol::property([](const INIT_REPUTATION_DATA& self) { return static_cast<bool>(self.bActive); }, [](INIT_REPUTATION_DATA& self, bool value) { self.bActive = value; });
    init_reputation_data_type["bCanAttackWithFreePkMode"] = sol::property([](const INIT_REPUTATION_DATA& self) { return static_cast<bool>(self.bCanAttackWithFreePkMode); }, [](INIT_REPUTATION_DATA& self, bool value) { self.bCanAttackWithFreePkMode = value; });
    init_reputation_data_type["bSabacMode"] = sol::property([](const INIT_REPUTATION_DATA& self) { return static_cast<bool>(self.bSabacMode); }, [](INIT_REPUTATION_DATA& self, bool value) { self.bSabacMode = value; });
    init_reputation_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, INIT_REPUTATION_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(INIT_REPUTATION_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_init_reputation_data_type = cqyh::lua::usertype<CDataManager<INIT_REPUTATION_DATA>>(L, globals, "CDataManager_INIT_REPUTATION_DATA_", "CDataManager<INIT_REPUTATION_DATA>");
    c_data_manager_init_reputation_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<INIT_REPUTATION_DATA>::GetInstance(); });
    c_data_manager_init_reputation_data_type.set_function("GetDataCount", [](CDataManager<INIT_REPUTATION_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_init_reputation_data_type.set_function("GetData", [](CDataManager<INIT_REPUTATION_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_init_reputation_data_type.set_function("GetID", [](CDataManager<INIT_REPUTATION_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_init_reputation_data_type.set_function("GetFirstData", [](CDataManager<INIT_REPUTATION_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_init_reputation_data_type.set_function("GetNextData", [](CDataManager<INIT_REPUTATION_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
