#include "stdafx.h"
#include "sol_bindings.h"
#include "../../inc/gameworld/general_mgr.h"

int sol_general_mgr_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto role = cqyh::lua::usertype<RAND_ROLE_DATA>(L, globals, "RAND_ROLE_DATA", "RAND_ROLE_DATA");
    role["dwRoleID"] = &RAND_ROLE_DATA::dwRoleID;
    role["szRoleName"] = cqyh::lua::string_property(&RAND_ROLE_DATA::szRoleName);
    auto type = cqyh::lua::usertype<CGeneralMgr>(L, globals, "CGeneralMgr", "CGeneralMgr");
    type.set_function("GetInstance", []() -> decltype(auto) { return CGeneralMgr::GetInstance(); });
    type.set_function("IsValidRandRoleExist", [](CGeneralMgr* self) -> decltype(auto) { return static_cast<bool>(self->IsValidRandRoleExist()); });
    type.set_function("GetRandRole", [](CGeneralMgr* self, UINT32 dwRoleID) -> decltype(auto) { return self->GetRandRole(dwRoleID); });
    type.set_function("AddRandRole", [](CGeneralMgr* self, UINT32 dwRoleID, const char * pcszName) -> decltype(auto) { self->AddRandRole(dwRoleID, pcszName); });
    type.set_function("GetRandomGuild", [](CGeneralMgr* self) -> decltype(auto) { return self->GetRandomGuild(); });
    return 1;
}
