#include "stdafx.h"
#include "sol_bindings.h"
#include "../../inc/gameworld/asimov_role.h"

int sol_asimov_role_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type = cqyh::lua::usertype<CAsimovRole>(L, globals, "CAsimovRole", "CAsimovRole");
    type.set_function("RandShieldRole", [](CAsimovRole* self) -> decltype(auto) { return self->RandShieldRole(); });
    type.set_function("RandCompleteAchievement", [](CAsimovRole* self) -> decltype(auto) { return self->RandCompleteAchievement(); });
    type.set_function("LuaClearGuildApp", [](CAsimovRole* self) -> decltype(auto) { return static_cast<bool>(self->LuaClearGuildApp()); });
    type.set_function("LuaIsInGuildAppList", [](CAsimovRole* self, UINT32 dwGuildID) -> decltype(auto) { return static_cast<bool>(self->LuaIsInGuildAppList(dwGuildID)); });
    type.set_function("LuaGetGuildAppNum", [](CAsimovRole* self) -> decltype(auto) { return self->LuaGetGuildAppNum(); });
    type.set_function("LuaGetGuildAppByIndex", [](CAsimovRole* self, INT32 nIndex) -> decltype(auto) { return self->LuaGetGuildAppByIndex(nIndex); });
    type.set_function("LuaAddGuildApp", [](CAsimovRole* self, UINT32 dwGuildID) -> decltype(auto) { return static_cast<bool>(self->LuaAddGuildApp(dwGuildID)); });
    type.set_function("LuaDelGuildApp", [](CAsimovRole* self, UINT32 dwGuildID) -> decltype(auto) { return static_cast<bool>(self->LuaDelGuildApp(dwGuildID)); });
    type.set_function("GetViewListNum", [](CAsimovRole* self) -> decltype(auto) { return self->GetViewListNum(); });
    type.set_function("GetInviteGuildRoleID", [](CAsimovRole* self) -> decltype(auto) { return self->GetInviteGuildRoleID(); });
    type.set_function("GetViewListGuildIDByIndex", [](CAsimovRole* self, INT32 nIndex) -> decltype(auto) { return self->GetViewListGuildIDByIndex(nIndex); });
    return 1;
}
