#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/fusion/inc/title_data.h"
#include "../../../../../inc/baselib/data_manager.h"
#include "../../../../../inc/baselib/tabfile.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::gameworld::bindings {

void register_title_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto title_template_type = cqyh::lua::usertype<TITLE_TEMPLATE>(L, globals, "TITLE_TEMPLATE", "TITLE_TEMPLATE");
    title_template_type["m_nTemplateID"] = sol::property([](const TITLE_TEMPLATE& self) { return self.m_nTemplateID; }, [](TITLE_TEMPLATE& self, decltype(TITLE_TEMPLATE::m_nTemplateID) value) { self.m_nTemplateID = value; });
    title_template_type["m_szName"] = cqyh::lua::string_property(&TITLE_TEMPLATE::m_szName);
    title_template_type["m_nValidTime"] = sol::property([](const TITLE_TEMPLATE& self) { return self.m_nValidTime; }, [](TITLE_TEMPLATE& self, decltype(TITLE_TEMPLATE::m_nValidTime) value) { self.m_nValidTime = value; });
    title_template_type["nPow"] = sol::property([](const TITLE_TEMPLATE& self) { return self.nPow; }, [](TITLE_TEMPLATE& self, decltype(TITLE_TEMPLATE::nPow) value) { self.nPow = value; });
    title_template_type["m_nAttrID"] = cqyh::lua::array_property(&TITLE_TEMPLATE::m_nAttrID);
    title_template_type["m_nNodeCount"] = sol::property([](const TITLE_TEMPLATE& self) { return self.m_nNodeCount; }, [](TITLE_TEMPLATE& self, decltype(TITLE_TEMPLATE::m_nNodeCount) value) { self.m_nNodeCount = value; });
    title_template_type["m_nNodeIDs"] = cqyh::lua::array_property(&TITLE_TEMPLATE::m_nNodeIDs);
    auto title_template_title_condition_type = cqyh::lua::usertype<TITLE_TEMPLATE::TitleCondition>(L, title_template_type, "TitleCondition", "TITLE_TEMPLATE::TitleCondition");
    title_template_title_condition_type["shConType"] = sol::property([](const TITLE_TEMPLATE::TitleCondition& self) { return self.shConType; }, [](TITLE_TEMPLATE::TitleCondition& self, decltype(TITLE_TEMPLATE::TitleCondition::shConType) value) { self.shConType = value; });
    title_template_title_condition_type["shConValue"] = sol::property([](const TITLE_TEMPLATE::TitleCondition& self) { return self.shConValue; }, [](TITLE_TEMPLATE::TitleCondition& self, decltype(TITLE_TEMPLATE::TitleCondition::shConValue) value) { self.shConValue = value; });
    title_template_type["m_Condition"] = cqyh::lua::array_property(&TITLE_TEMPLATE::m_Condition);
    title_template_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, TITLE_TEMPLATE* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(TITLE_TEMPLATE::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_title_template_type = cqyh::lua::usertype<CDataManager<TITLE_TEMPLATE>>(L, globals, "CDataManager_TITLE_TEMPLATE_", "CDataManager<TITLE_TEMPLATE>");
    c_data_manager_title_template_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<TITLE_TEMPLATE>::GetInstance(); });
    c_data_manager_title_template_type.set_function("GetDataCount", [](CDataManager<TITLE_TEMPLATE>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_title_template_type.set_function("GetData", [](CDataManager<TITLE_TEMPLATE>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_title_template_type.set_function("GetID", [](CDataManager<TITLE_TEMPLATE>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_title_template_type.set_function("GetFirstData", [](CDataManager<TITLE_TEMPLATE>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_title_template_type.set_function("GetNextData", [](CDataManager<TITLE_TEMPLATE>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
