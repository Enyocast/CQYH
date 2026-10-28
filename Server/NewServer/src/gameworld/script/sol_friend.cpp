#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "friend.h"
#include "../../../inc/gameworld/role.h"

int sol_friend_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CFriend>(L, globals, "CFriend", "CFriend");
    type1.set_function("AddFriend", [](CFriend* self, unsigned char byGroupID, unsigned int dwFriendID) -> decltype(auto) { self->AddFriend(byGroupID,dwFriendID); });
    type1.set_function("DelFriend", [](CFriend* self, unsigned char byGroupID, unsigned int dwFriendID) -> decltype(auto) { self->DelFriend(byGroupID,dwFriendID); });
    type1.set_function("GetFriendCount", [](CFriend* self) -> decltype(auto) { return self->GetFriendCount(); });
    type1.set_function("GetPersonalEnemyCount", [](CFriend* self) -> decltype(auto) { return self->GetPersonalEnemyCount(); });
    type1.set_function("AddBeKilledToList", [](CFriend* self, CRole* poRole, unsigned int dwRoleID) -> decltype(auto) { return static_cast<bool>(self->AddBeKilledToList(poRole,dwRoleID)); });
    return 1;
}
