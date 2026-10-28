#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/attr_conversion_data.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"
#include "../../../../../../NewServer/inc/baselib/lua_script.h"

namespace cqyh::fusion::bindings {

void register_attr_conversion_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto attr_level_type = cqyh::lua::usertype<ATTR_LEVEL>(L, globals, "ATTR_LEVEL", "ATTR_LEVEL");
    attr_level_type["m_nLevel"] = sol::property([](const ATTR_LEVEL& self) { return self.m_nLevel; }, [](ATTR_LEVEL& self, decltype(ATTR_LEVEL::m_nLevel) value) { self.m_nLevel = value; });
    attr_level_type["m_nClass"] = sol::property([](const ATTR_LEVEL& self) { return self.m_nClass; }, [](ATTR_LEVEL& self, decltype(ATTR_LEVEL::m_nClass) value) { self.m_nClass = value; });
    attr_level_type["m_nMainAttr"] = cqyh::lua::array_property(&ATTR_LEVEL::m_nMainAttr);
    attr_level_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, ATTR_LEVEL* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(ATTR_LEVEL::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_attr_level_type = cqyh::lua::usertype<CDataManager<ATTR_LEVEL>>(L, globals, "CDataManager_ATTR_LEVEL_", "CDataManager<ATTR_LEVEL>");
    c_data_manager_attr_level_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<ATTR_LEVEL>::GetInstance(); });
    c_data_manager_attr_level_type.set_function("GetDataCount", [](CDataManager<ATTR_LEVEL>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_attr_level_type.set_function("GetData", [](CDataManager<ATTR_LEVEL>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_attr_level_type.set_function("GetID", [](CDataManager<ATTR_LEVEL>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_attr_level_type.set_function("GetFirstData", [](CDataManager<ATTR_LEVEL>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_attr_level_type.set_function("GetNextData", [](CDataManager<ATTR_LEVEL>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
