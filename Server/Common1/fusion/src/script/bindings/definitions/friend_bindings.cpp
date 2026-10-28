#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/friend_def.h"

namespace cqyh::fusion::bindings {

void register_friend_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_FRIEND_COUNT"] = static_cast<lua_Number>(MAX_FRIEND_COUNT);
    globals["MAX_FRIEND_GROUP_COUNT"] = static_cast<lua_Number>(MAX_FRIEND_GROUP_COUNT);
    globals["FRIEND_GROUP_ENEMY"] = static_cast<lua_Number>(FRIEND_GROUP_ENEMY);
    globals["FRIEND_GROUP_NAME_LEN"] = static_cast<lua_Number>(FRIEND_GROUP_NAME_LEN);
    globals["SIGNATURE_LEN"] = static_cast<lua_Number>(SIGNATURE_LEN);
    globals["MAX_PERSONAL_ENEMY_COUNT"] = static_cast<lua_Number>(MAX_PERSONAL_ENEMY_COUNT);
    globals["FS_ONLINE"] = static_cast<lua_Number>(FS_ONLINE);
    globals["FS_BUSY"] = static_cast<lua_Number>(FS_BUSY);
    globals["FS_AFK"] = static_cast<lua_Number>(FS_AFK);
    globals["FS_OFFLINE"] = static_cast<lua_Number>(FS_OFFLINE);
}

}
