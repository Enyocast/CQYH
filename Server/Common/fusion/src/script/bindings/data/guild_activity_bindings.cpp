#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/guild_activity.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"

namespace cqyh::fusion::bindings {

void register_guild_activity_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto guild_activity_data_type = cqyh::lua::usertype<GUILD_ACTIVITY_DATA>(L, globals, "GUILD_ACTIVITY_DATA", "GUILD_ACTIVITY_DATA");
    guild_activity_data_type["nType"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.nType; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::nType) value) { self.nType = value; });
    guild_activity_data_type["nLevel"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.nLevel; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::nLevel) value) { self.nLevel = value; });
    guild_activity_data_type["nGuildVariableIndex"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.nGuildVariableIndex; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::nGuildVariableIndex) value) { self.nGuildVariableIndex = value; });
    guild_activity_data_type["nLastTime"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.nLastTime; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::nLastTime) value) { self.nLastTime = value; });
    guild_activity_data_type["nRepeatNum"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.nRepeatNum; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::nRepeatNum) value) { self.nRepeatNum = value; });
    guild_activity_data_type["nBaseBuildingType"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.nBaseBuildingType; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::nBaseBuildingType) value) { self.nBaseBuildingType = value; });
    guild_activity_data_type["nBaseBuildingLevel"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.nBaseBuildingLevel; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::nBaseBuildingLevel) value) { self.nBaseBuildingLevel = value; });
    guild_activity_data_type["nConsumeMoney"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.nConsumeMoney; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::nConsumeMoney) value) { self.nConsumeMoney = value; });
    guild_activity_data_type["nConsumeHerb"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.nConsumeHerb; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::nConsumeHerb) value) { self.nConsumeHerb = value; });
    guild_activity_data_type["nConsumeWood"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.nConsumeWood; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::nConsumeWood) value) { self.nConsumeWood = value; });
    guild_activity_data_type["nConsumeCrystal"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.nConsumeCrystal; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::nConsumeCrystal) value) { self.nConsumeCrystal = value; });
    guild_activity_data_type["nConsumeSilver"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.nConsumeSilver; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::nConsumeSilver) value) { self.nConsumeSilver = value; });
    guild_activity_data_type["ncltLightingID"] = sol::property([](const GUILD_ACTIVITY_DATA& self) { return self.ncltLightingID; }, [](GUILD_ACTIVITY_DATA& self, decltype(GUILD_ACTIVITY_DATA::ncltLightingID) value) { self.ncltLightingID = value; });
    guild_activity_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, GUILD_ACTIVITY_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(GUILD_ACTIVITY_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_guild_activity_data_type = cqyh::lua::usertype<CDataManager<GUILD_ACTIVITY_DATA>>(L, globals, "CDataManager_GUILD_ACTIVITY_DATA_", "CDataManager<GUILD_ACTIVITY_DATA>");
    c_data_manager_guild_activity_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<GUILD_ACTIVITY_DATA>::GetInstance(); });
    c_data_manager_guild_activity_data_type.set_function("GetDataCount", [](CDataManager<GUILD_ACTIVITY_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_guild_activity_data_type.set_function("GetData", [](CDataManager<GUILD_ACTIVITY_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_guild_activity_data_type.set_function("GetID", [](CDataManager<GUILD_ACTIVITY_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_guild_activity_data_type.set_function("GetFirstData", [](CDataManager<GUILD_ACTIVITY_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_guild_activity_data_type.set_function("GetNextData", [](CDataManager<GUILD_ACTIVITY_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
