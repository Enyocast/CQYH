#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "./ranklist/ranklist.h"
#include "./ranklist/ranklist.h"

int sol_ranklist_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CRankListMgr>(L, globals, "CRankListMgr", "CRankListMgr");
    type1.set_function("GetInstance", []() -> decltype(auto) { return CRankListMgr::GetInstance(); });
    type1.set_function("DelGuildRankNode", [](CRankListMgr* self, signed int nServerGroupID, unsigned int dwGuildID) -> decltype(auto) { return static_cast<bool>(self->DelGuildRankNode(nServerGroupID,dwGuildID)); });
    return 1;
}
