#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/fusion/inc/role_relation_data.h"
#include "../../../../../inc/baselib/data_manager.h"
#include "../../../../../inc/baselib/tabfile.h"
#include "../../../../../../Common/define/role_def.h"

namespace cqyh::gameworld::bindings {

void register_role_relation_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto role_relation_data_type = cqyh::lua::usertype<ROLE_RELATION_DATA>(L, globals, "ROLE_RELATION_DATA", "ROLE_RELATION_DATA");
    role_relation_data_type["nFactionID"] = sol::property([](const ROLE_RELATION_DATA& self) { return self.nFactionID; }, [](ROLE_RELATION_DATA& self, decltype(ROLE_RELATION_DATA::nFactionID) value) { self.nFactionID = value; });
    role_relation_data_type["nRelation"] = cqyh::lua::array_property(&ROLE_RELATION_DATA::nRelation);
    role_relation_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, ROLE_RELATION_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(ROLE_RELATION_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_role_relation_data_type = cqyh::lua::usertype<CDataManager<ROLE_RELATION_DATA>>(L, globals, "CDataManager_ROLE_RELATION_DATA_", "CDataManager<ROLE_RELATION_DATA>");
    c_data_manager_role_relation_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<ROLE_RELATION_DATA>::GetInstance(); });
    c_data_manager_role_relation_data_type.set_function("GetDataCount", [](CDataManager<ROLE_RELATION_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_role_relation_data_type.set_function("GetData", [](CDataManager<ROLE_RELATION_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_role_relation_data_type.set_function("GetID", [](CDataManager<ROLE_RELATION_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_role_relation_data_type.set_function("GetFirstData", [](CDataManager<ROLE_RELATION_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_role_relation_data_type.set_function("GetNextData", [](CDataManager<ROLE_RELATION_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
