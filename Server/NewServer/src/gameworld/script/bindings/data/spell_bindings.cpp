#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/fusion/inc/item_data.h"
#include "../../../../../../Common/fusion/inc/spell_data.h"
#include "../../../../../inc/baselib/data_manager.h"
#include "../../../../../inc/baselib/tabfile.h"
#include "../../../../../../Common/define/spell_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::gameworld::bindings {

void register_spell_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto c_data_manager_spell_entry_type = cqyh::lua::usertype<CDataManager<SPELL_ENTRY>>(L, globals, "CDataManager_SPELL_ENTRY_", "CDataManager<SPELL_ENTRY>");
    c_data_manager_spell_entry_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<SPELL_ENTRY>::GetInstance(); });
    c_data_manager_spell_entry_type.set_function("GetDataCount", [](CDataManager<SPELL_ENTRY>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_spell_entry_type.set_function("GetData", [](CDataManager<SPELL_ENTRY>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_spell_entry_type.set_function("GetID", [](CDataManager<SPELL_ENTRY>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_spell_entry_type.set_function("GetFirstData", [](CDataManager<SPELL_ENTRY>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_spell_entry_type.set_function("GetNextData", [](CDataManager<SPELL_ENTRY>* self) -> decltype(auto) { return self->GetNextData(); });
    auto c_data_manager_spell_var_type = cqyh::lua::usertype<CDataManager<SPELL_VAR>>(L, globals, "CDataManager_SPELL_VAR_", "CDataManager<SPELL_VAR>");
    c_data_manager_spell_var_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<SPELL_VAR>::GetInstance(); });
    c_data_manager_spell_var_type.set_function("GetDataCount", [](CDataManager<SPELL_VAR>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_spell_var_type.set_function("GetData", [](CDataManager<SPELL_VAR>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_spell_var_type.set_function("GetID", [](CDataManager<SPELL_VAR>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_spell_var_type.set_function("GetFirstData", [](CDataManager<SPELL_VAR>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_spell_var_type.set_function("GetNextData", [](CDataManager<SPELL_VAR>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
