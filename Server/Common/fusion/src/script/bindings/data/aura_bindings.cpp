#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/aura_data.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"

namespace cqyh::fusion::bindings {

void register_aura_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto aura_entry_type = cqyh::lua::usertype<AURA_ENTRY>(L, globals, "AURA_ENTRY", "AURA_ENTRY");
    aura_entry_type["m_nID"] = sol::property([](const AURA_ENTRY& self) { return self.m_nID; }, [](AURA_ENTRY& self, decltype(AURA_ENTRY::m_nID) value) { self.m_nID = value; });
    aura_entry_type["m_nAttrTable"] = cqyh::lua::array_property(&AURA_ENTRY::m_nAttrTable);
    auto ex_evt_point_type = cqyh::lua::usertype<AURA_ENTRY::EX_EVT_POINT>(L, aura_entry_type, "EX_EVT_POINT", "AURA_ENTRY::EX_EVT_POINT");
    ex_evt_point_type["m_nExEvtTime"] = sol::property([](const AURA_ENTRY::EX_EVT_POINT& self) { return self.m_nExEvtTime; }, [](AURA_ENTRY::EX_EVT_POINT& self, decltype(AURA_ENTRY::EX_EVT_POINT::m_nExEvtTime) value) { self.m_nExEvtTime = value; });
    ex_evt_point_type["m_nExOnEvt"] = sol::property([](const AURA_ENTRY::EX_EVT_POINT& self) { return self.m_nExOnEvt; }, [](AURA_ENTRY::EX_EVT_POINT& self, decltype(AURA_ENTRY::EX_EVT_POINT::m_nExOnEvt) value) { self.m_nExOnEvt = value; });
    aura_entry_type["m_ExEvtPoint"] = cqyh::lua::array_property(&AURA_ENTRY::m_ExEvtPoint);
    aura_entry_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, AURA_ENTRY* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(AURA_ENTRY::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_aura_entry_type = cqyh::lua::usertype<CDataManager<AURA_ENTRY>>(L, globals, "CDataManager_AURA_ENTRY_", "CDataManager<AURA_ENTRY>");
    c_data_manager_aura_entry_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<AURA_ENTRY>::GetInstance(); });
    c_data_manager_aura_entry_type.set_function("GetDataCount", [](CDataManager<AURA_ENTRY>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_aura_entry_type.set_function("GetData", [](CDataManager<AURA_ENTRY>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_aura_entry_type.set_function("GetID", [](CDataManager<AURA_ENTRY>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_aura_entry_type.set_function("GetFirstData", [](CDataManager<AURA_ENTRY>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_aura_entry_type.set_function("GetNextData", [](CDataManager<AURA_ENTRY>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
