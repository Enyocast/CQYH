#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/doodad_data.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"
#include "../../../../inc/adventure_data.h"

namespace cqyh::fusion::bindings {

void register_doodad_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto doodad_data_type = cqyh::lua::usertype<DOODAD_DATA>(L, globals, "DOODAD_DATA", "DOODAD_DATA");
    doodad_data_type["nTemplateID"] = sol::property([](const DOODAD_DATA& self) { return self.nTemplateID; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nTemplateID) value) { self.nTemplateID = value; });
    doodad_data_type["szName"] = cqyh::lua::string_property(&DOODAD_DATA::szName);
    doodad_data_type["nLevel"] = sol::property([](const DOODAD_DATA& self) { return self.nLevel; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nLevel) value) { self.nLevel = value; });
    doodad_data_type["nType"] = sol::property([](const DOODAD_DATA& self) { return self.nType; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nType) value) { self.nType = value; });
    doodad_data_type["nSubType"] = sol::property([](const DOODAD_DATA& self) { return self.nSubType; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nSubType) value) { self.nSubType = value; });
    doodad_data_type["nBodyType"] = sol::property([](const DOODAD_DATA& self) { return self.nBodyType; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nBodyType) value) { self.nBodyType = value; });
    doodad_data_type["nOperateDuration"] = sol::property([](const DOODAD_DATA& self) { return self.nOperateDuration; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nOperateDuration) value) { self.nOperateDuration = value; });
    doodad_data_type["nMinOpenCount"] = sol::property([](const DOODAD_DATA& self) { return self.nMinOpenCount; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nMinOpenCount) value) { self.nMinOpenCount = value; });
    doodad_data_type["nMaxOpenCount"] = sol::property([](const DOODAD_DATA& self) { return self.nMaxOpenCount; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nMaxOpenCount) value) { self.nMaxOpenCount = value; });
    doodad_data_type["nRequireItemID"] = sol::property([](const DOODAD_DATA& self) { return self.nRequireItemID; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nRequireItemID) value) { self.nRequireItemID = value; });
    doodad_data_type["bCostItem"] = sol::property([](const DOODAD_DATA& self) { return static_cast<bool>(self.bCostItem); }, [](DOODAD_DATA& self, bool value) { self.bCostItem = value; });
    doodad_data_type["nRequireVarID"] = sol::property([](const DOODAD_DATA& self) { return self.nRequireVarID; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nRequireVarID) value) { self.nRequireVarID = value; });
    doodad_data_type["nRequireVarValue"] = sol::property([](const DOODAD_DATA& self) { return self.nRequireVarValue; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nRequireVarValue) value) { self.nRequireVarValue = value; });
    doodad_data_type["nSpawnNpcID"] = sol::property([](const DOODAD_DATA& self) { return self.nSpawnNpcID; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nSpawnNpcID) value) { self.nSpawnNpcID = value; });
    doodad_data_type["nSpawnNpcChance"] = sol::property([](const DOODAD_DATA& self) { return self.nSpawnNpcChance; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nSpawnNpcChance) value) { self.nSpawnNpcChance = value; });
    doodad_data_type["nAuraID"] = sol::property([](const DOODAD_DATA& self) { return self.nAuraID; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nAuraID) value) { self.nAuraID = value; });
    doodad_data_type["nLifeFrm"] = sol::property([](const DOODAD_DATA& self) { return self.nLifeFrm; }, [](DOODAD_DATA& self, decltype(DOODAD_DATA::nLifeFrm) value) { self.nLifeFrm = value; });
    doodad_data_type["szScriptName"] = cqyh::lua::string_property(&DOODAD_DATA::szScriptName);
    doodad_data_type["pAdventureData"] = sol::readonly(&DOODAD_DATA::pAdventureData);
    doodad_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, DOODAD_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(DOODAD_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_doodad_data_type = cqyh::lua::usertype<CDataManager<DOODAD_DATA>>(L, globals, "CDataManager_DOODAD_DATA_", "CDataManager<DOODAD_DATA>");
    c_data_manager_doodad_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<DOODAD_DATA>::GetInstance(); });
    c_data_manager_doodad_data_type.set_function("GetDataCount", [](CDataManager<DOODAD_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_doodad_data_type.set_function("GetData", [](CDataManager<DOODAD_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_doodad_data_type.set_function("GetID", [](CDataManager<DOODAD_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_doodad_data_type.set_function("GetFirstData", [](CDataManager<DOODAD_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_doodad_data_type.set_function("GetNextData", [](CDataManager<DOODAD_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
