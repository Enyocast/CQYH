#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/npc_relation_data.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"

namespace cqyh::fusion::bindings {

void register_npc_relation_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto npc_relation_data_type = cqyh::lua::usertype<NPC_RELATION_DATA>(L, globals, "NPC_RELATION_DATA", "NPC_RELATION_DATA");
    npc_relation_data_type["nForceID"] = sol::property([](const NPC_RELATION_DATA& self) { return self.nForceID; }, [](NPC_RELATION_DATA& self, decltype(NPC_RELATION_DATA::nForceID) value) { self.nForceID = value; });
    npc_relation_data_type["nRelation"] = cqyh::lua::array_property(&NPC_RELATION_DATA::nRelation);
    npc_relation_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, NPC_RELATION_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(NPC_RELATION_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_npc_relation_data_type = cqyh::lua::usertype<CDataManager<NPC_RELATION_DATA>>(L, globals, "CDataManager_NPC_RELATION_DATA_", "CDataManager<NPC_RELATION_DATA>");
    c_data_manager_npc_relation_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<NPC_RELATION_DATA>::GetInstance(); });
    c_data_manager_npc_relation_data_type.set_function("GetDataCount", [](CDataManager<NPC_RELATION_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_npc_relation_data_type.set_function("GetData", [](CDataManager<NPC_RELATION_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_npc_relation_data_type.set_function("GetID", [](CDataManager<NPC_RELATION_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_npc_relation_data_type.set_function("GetFirstData", [](CDataManager<NPC_RELATION_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_npc_relation_data_type.set_function("GetNextData", [](CDataManager<NPC_RELATION_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
