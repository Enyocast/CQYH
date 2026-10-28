#include "stdafx.h"
#include "sol_bindings.h"
#include "user_mgr.h"
#include "user.h"
#include "role.h"

int sol_asimov_user_mgr_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type = cqyh::lua::usertype<CUserMgr>(L, globals, "CUserMgr", "CUserMgr");
    type.set_function("GetInstance", []() -> decltype(auto) { return CUserMgr::GetInstance(); });
    type.set_function("FindUser", [](CUserMgr* self, INT32 nUserID) -> decltype(auto) { return self->FindUser(nUserID); });
    type.set_function("RandAnotherUser", [](CUserMgr* self, CUser* poSelfUser) -> decltype(auto) { return self->RandAnotherUser(poSelfUser); });
    type.set_function("GetDefaultGroupID", [](CUserMgr* self) -> decltype(auto) { return self->GetDefaultGroupID(); });
    return 1;
}
