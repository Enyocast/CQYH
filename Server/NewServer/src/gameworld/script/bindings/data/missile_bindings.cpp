#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/fusion/inc/missile_data.h"
#include "../../../../../inc/baselib/data_manager.h"
#include "../../../../../inc/baselib/tabfile.h"

namespace cqyh::gameworld::bindings {

void register_missile_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto missile_data_type = cqyh::lua::usertype<MISSILE_DATA>(L, globals, "MISSILE_DATA", "MISSILE_DATA");
    missile_data_type["m_nTemplateID"] = sol::property([](const MISSILE_DATA& self) { return self.m_nTemplateID; }, [](MISSILE_DATA& self, decltype(MISSILE_DATA::m_nTemplateID) value) { self.m_nTemplateID = value; });
    missile_data_type["m_nAttr"] = cqyh::lua::array_property(&MISSILE_DATA::m_nAttr);
    missile_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, MISSILE_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(MISSILE_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_missile_data_type = cqyh::lua::usertype<CDataManager<MISSILE_DATA>>(L, globals, "CDataManager_MISSILE_DATA_", "CDataManager<MISSILE_DATA>");
    c_data_manager_missile_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<MISSILE_DATA>::GetInstance(); });
    c_data_manager_missile_data_type.set_function("GetDataCount", [](CDataManager<MISSILE_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_missile_data_type.set_function("GetData", [](CDataManager<MISSILE_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_missile_data_type.set_function("GetID", [](CDataManager<MISSILE_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_missile_data_type.set_function("GetFirstData", [](CDataManager<MISSILE_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_missile_data_type.set_function("GetNextData", [](CDataManager<MISSILE_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
