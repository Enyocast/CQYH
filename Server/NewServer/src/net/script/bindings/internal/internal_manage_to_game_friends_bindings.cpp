#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/m2g_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"
#include "../../../../../../Common/define/variable_def.h"

namespace cqyh::net::bindings {

void register_internal_manage_to_game_friends_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_friend_add_type = cqyh::lua::usertype<InternalMessage::M2G_FRIEND_ADD>(L, internal_message_namespace, "M2G_FRIEND_ADD", "InternalMessage::M2G_FRIEND_ADD", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_friend_add_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_FRIEND_ADD(); });
    internal_message_m2g_friend_add_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_FRIEND_ADD>(new InternalMessage::M2G_FRIEND_ADD()); });
    internal_message_m2g_friend_add_type["dwCliSessionID"] = sol::property([](const InternalMessage::M2G_FRIEND_ADD& self) { return self.dwCliSessionID; }, [](InternalMessage::M2G_FRIEND_ADD& self, decltype(InternalMessage::M2G_FRIEND_ADD::dwCliSessionID) value) { self.dwCliSessionID = value; });
    internal_message_m2g_friend_add_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_FRIEND_ADD& self) { return self.dwRoleID; }, [](InternalMessage::M2G_FRIEND_ADD& self, decltype(InternalMessage::M2G_FRIEND_ADD::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_friend_add_type["dwFriendID"] = sol::property([](const InternalMessage::M2G_FRIEND_ADD& self) { return self.dwFriendID; }, [](InternalMessage::M2G_FRIEND_ADD& self, decltype(InternalMessage::M2G_FRIEND_ADD::dwFriendID) value) { self.dwFriendID = value; });
    internal_message_m2g_friend_add_type["byGroupID"] = sol::property([](const InternalMessage::M2G_FRIEND_ADD& self) { return self.byGroupID; }, [](InternalMessage::M2G_FRIEND_ADD& self, decltype(InternalMessage::M2G_FRIEND_ADD::byGroupID) value) { self.byGroupID = value; });
    auto internal_message_m2g_friend_del_type = cqyh::lua::usertype<InternalMessage::M2G_FRIEND_DEL>(L, internal_message_namespace, "M2G_FRIEND_DEL", "InternalMessage::M2G_FRIEND_DEL", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_friend_del_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_FRIEND_DEL(); });
    internal_message_m2g_friend_del_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_FRIEND_DEL>(new InternalMessage::M2G_FRIEND_DEL()); });
    internal_message_m2g_friend_del_type["dwCliSessionID"] = sol::property([](const InternalMessage::M2G_FRIEND_DEL& self) { return self.dwCliSessionID; }, [](InternalMessage::M2G_FRIEND_DEL& self, decltype(InternalMessage::M2G_FRIEND_DEL::dwCliSessionID) value) { self.dwCliSessionID = value; });
    internal_message_m2g_friend_del_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_FRIEND_DEL& self) { return self.dwRoleID; }, [](InternalMessage::M2G_FRIEND_DEL& self, decltype(InternalMessage::M2G_FRIEND_DEL::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_friend_del_type["dwFriendID"] = sol::property([](const InternalMessage::M2G_FRIEND_DEL& self) { return self.dwFriendID; }, [](InternalMessage::M2G_FRIEND_DEL& self, decltype(InternalMessage::M2G_FRIEND_DEL::dwFriendID) value) { self.dwFriendID = value; });
    internal_message_m2g_friend_del_type["byGroupID"] = sol::property([](const InternalMessage::M2G_FRIEND_DEL& self) { return self.byGroupID; }, [](InternalMessage::M2G_FRIEND_DEL& self, decltype(InternalMessage::M2G_FRIEND_DEL::byGroupID) value) { self.byGroupID = value; });
    auto internal_message_m2g_shield_type = cqyh::lua::usertype<InternalMessage::M2G_SHIELD>(L, internal_message_namespace, "M2G_SHIELD", "InternalMessage::M2G_SHIELD", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_shield_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_SHIELD(); });
    internal_message_m2g_shield_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_SHIELD>(new InternalMessage::M2G_SHIELD()); });
    internal_message_m2g_shield_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_SHIELD& self) { return self.dwRoleID; }, [](InternalMessage::M2G_SHIELD& self, decltype(InternalMessage::M2G_SHIELD::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_shield_type["dwTargetRoleID"] = sol::property([](const InternalMessage::M2G_SHIELD& self) { return self.dwTargetRoleID; }, [](InternalMessage::M2G_SHIELD& self, decltype(InternalMessage::M2G_SHIELD::dwTargetRoleID) value) { self.dwTargetRoleID = value; });
    internal_message_m2g_shield_type["szTargetRoleName"] = cqyh::lua::string_property(&InternalMessage::M2G_SHIELD::szTargetRoleName);
}

}
