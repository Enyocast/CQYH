#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "./role_data.h"
#include "role_data_mgr.h"

int sol_role_data_mgr_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CRoleDataMgr>(L, globals, "CRoleDataMgr", "CRoleDataMgr");
    type1.set_function("GetInstance", []() -> decltype(auto) { return CRoleDataMgr::GetInstance(); });
    type1.set_function("FindRole", [](CRoleDataMgr* self, unsigned int dwRoleID) -> decltype(auto) { return self->FindRole(dwRoleID); });
    type1.set_function("FindRoleByName", [](CRoleDataMgr* self, const char* pcszRoleName) -> decltype(auto) { return self->FindRoleByName(pcszRoleName); });
    return 1;
}
