#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/fusion/inc/guild_building_data.h"
#include "../../../../../inc/baselib/data_manager.h"
#include "../../../../../inc/baselib/tabfile.h"

namespace cqyh::gameworld::bindings {

void register_guild_building_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto guild_building_data_type = cqyh::lua::usertype<GUILD_BUILDING_DATA>(L, globals, "GUILD_BUILDING_DATA", "GUILD_BUILDING_DATA");
    guild_building_data_type["dwID"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.dwID; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::dwID) value) { self.dwID = value; });
    guild_building_data_type["nLevel"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nLevel; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nLevel) value) { self.nLevel = value; });
    guild_building_data_type["nMaxLevel"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nMaxLevel; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nMaxLevel) value) { self.nMaxLevel = value; });
    guild_building_data_type["nMaxNum"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nMaxNum; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nMaxNum) value) { self.nMaxNum = value; });
    guild_building_data_type["nProsperity"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nProsperity; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nProsperity) value) { self.nProsperity = value; });
    guild_building_data_type["nMoneyConsumption"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nMoneyConsumption; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nMoneyConsumption) value) { self.nMoneyConsumption = value; });
    guild_building_data_type["nTotalMoneyConsumption"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nTotalMoneyConsumption; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nTotalMoneyConsumption) value) { self.nTotalMoneyConsumption = value; });
    guild_building_data_type["nHerbConsumption"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nHerbConsumption; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nHerbConsumption) value) { self.nHerbConsumption = value; });
    guild_building_data_type["nTotalHerbConsumption"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nTotalHerbConsumption; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nTotalHerbConsumption) value) { self.nTotalHerbConsumption = value; });
    guild_building_data_type["nWoodConsumption"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nWoodConsumption; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nWoodConsumption) value) { self.nWoodConsumption = value; });
    guild_building_data_type["nTotalWoodConsumption"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nTotalWoodConsumption; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nTotalWoodConsumption) value) { self.nTotalWoodConsumption = value; });
    guild_building_data_type["nCrystalConsumption"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nCrystalConsumption; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nCrystalConsumption) value) { self.nCrystalConsumption = value; });
    guild_building_data_type["nTotalCrystalConsumption"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nTotalCrystalConsumption; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nTotalCrystalConsumption) value) { self.nTotalCrystalConsumption = value; });
    guild_building_data_type["nSilverConsumption"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nSilverConsumption; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nSilverConsumption) value) { self.nSilverConsumption = value; });
    guild_building_data_type["nTotalSilverConsumption"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nTotalSilverConsumption; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nTotalSilverConsumption) value) { self.nTotalSilverConsumption = value; });
    guild_building_data_type["nUpgradeTime"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nUpgradeTime; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nUpgradeTime) value) { self.nUpgradeTime = value; });
    guild_building_data_type["nRoutineConsumption"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nRoutineConsumption; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nRoutineConsumption) value) { self.nRoutineConsumption = value; });
    guild_building_data_type["dwCdtnBaseNpcID"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.dwCdtnBaseNpcID; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::dwCdtnBaseNpcID) value) { self.dwCdtnBaseNpcID = value; });
    guild_building_data_type["dwConditionBuildingID"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.dwConditionBuildingID; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::dwConditionBuildingID) value) { self.dwConditionBuildingID = value; });
    guild_building_data_type["nConditionBuildingLvl"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nConditionBuildingLvl; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nConditionBuildingLvl) value) { self.nConditionBuildingLvl = value; });
    guild_building_data_type["dwUpgradingSpellID"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.dwUpgradingSpellID; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::dwUpgradingSpellID) value) { self.dwUpgradingSpellID = value; });
    guild_building_data_type["dwNpcTemplateID"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.dwNpcTemplateID; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::dwNpcTemplateID) value) { self.dwNpcTemplateID = value; });
    guild_building_data_type["dwDeadNpcTemplateID"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.dwDeadNpcTemplateID; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::dwDeadNpcTemplateID) value) { self.dwDeadNpcTemplateID = value; });
    guild_building_data_type["nReviveTime"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nReviveTime; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nReviveTime) value) { self.nReviveTime = value; });
    guild_building_data_type["nParam1"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nParam1; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nParam1) value) { self.nParam1 = value; });
    guild_building_data_type["nParam2"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nParam2; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nParam2) value) { self.nParam2 = value; });
    guild_building_data_type["nParam3"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nParam3; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nParam3) value) { self.nParam3 = value; });
    guild_building_data_type["nParam4"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nParam4; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nParam4) value) { self.nParam4 = value; });
    guild_building_data_type["nParam5"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.nParam5; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::nParam5) value) { self.nParam5 = value; });
    guild_building_data_type["dwIntruderMsgID"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.dwIntruderMsgID; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::dwIntruderMsgID) value) { self.dwIntruderMsgID = value; });
    guild_building_data_type["dwDefenderMsgID"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.dwDefenderMsgID; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::dwDefenderMsgID) value) { self.dwDefenderMsgID = value; });
    guild_building_data_type["dwFewMembersReward"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.dwFewMembersReward; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::dwFewMembersReward) value) { self.dwFewMembersReward = value; });
    guild_building_data_type["dwSomeMembersReward"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.dwSomeMembersReward; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::dwSomeMembersReward) value) { self.dwSomeMembersReward = value; });
    guild_building_data_type["dwManyMembersReward"] = sol::property([](const GUILD_BUILDING_DATA& self) { return self.dwManyMembersReward; }, [](GUILD_BUILDING_DATA& self, decltype(GUILD_BUILDING_DATA::dwManyMembersReward) value) { self.dwManyMembersReward = value; });
    guild_building_data_type.set_function("HasName", []() -> decltype(auto) { return static_cast<bool>(GUILD_BUILDING_DATA::HasName()); });
    guild_building_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, GUILD_BUILDING_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(GUILD_BUILDING_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_guild_building_data_type = cqyh::lua::usertype<CDataManager<GUILD_BUILDING_DATA>>(L, globals, "CDataManager_GUILD_BUILDING_DATA_", "CDataManager<GUILD_BUILDING_DATA>");
    c_data_manager_guild_building_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<GUILD_BUILDING_DATA>::GetInstance(); });
    c_data_manager_guild_building_data_type.set_function("GetDataCount", [](CDataManager<GUILD_BUILDING_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_guild_building_data_type.set_function("GetData", [](CDataManager<GUILD_BUILDING_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_guild_building_data_type.set_function("GetID", [](CDataManager<GUILD_BUILDING_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_guild_building_data_type.set_function("GetFirstData", [](CDataManager<GUILD_BUILDING_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_guild_building_data_type.set_function("GetNextData", [](CDataManager<GUILD_BUILDING_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
