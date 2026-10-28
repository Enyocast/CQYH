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

void register_internal_manage_to_game_pvp_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_join_battle_type = cqyh::lua::usertype<InternalMessage::M2G_JOIN_BATTLE>(L, internal_message_namespace, "M2G_JOIN_BATTLE", "InternalMessage::M2G_JOIN_BATTLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_join_battle_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_JOIN_BATTLE(); });
    internal_message_m2g_join_battle_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_JOIN_BATTLE>(new InternalMessage::M2G_JOIN_BATTLE()); });
    internal_message_m2g_join_battle_type["dwCliSessionID"] = sol::property([](const InternalMessage::M2G_JOIN_BATTLE& self) { return self.dwCliSessionID; }, [](InternalMessage::M2G_JOIN_BATTLE& self, decltype(InternalMessage::M2G_JOIN_BATTLE::dwCliSessionID) value) { self.dwCliSessionID = value; });
    internal_message_m2g_join_battle_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_JOIN_BATTLE& self) { return self.dwRoleID; }, [](InternalMessage::M2G_JOIN_BATTLE& self, decltype(InternalMessage::M2G_JOIN_BATTLE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_join_battle_type["dwSceneTempID"] = sol::property([](const InternalMessage::M2G_JOIN_BATTLE& self) { return self.dwSceneTempID; }, [](InternalMessage::M2G_JOIN_BATTLE& self, decltype(InternalMessage::M2G_JOIN_BATTLE::dwSceneTempID) value) { self.dwSceneTempID = value; });
    internal_message_m2g_join_battle_type["dwSceneID"] = sol::property([](const InternalMessage::M2G_JOIN_BATTLE& self) { return self.dwSceneID; }, [](InternalMessage::M2G_JOIN_BATTLE& self, decltype(InternalMessage::M2G_JOIN_BATTLE::dwSceneID) value) { self.dwSceneID = value; });
    internal_message_m2g_join_battle_type["bySide"] = sol::property([](const InternalMessage::M2G_JOIN_BATTLE& self) { return self.bySide; }, [](InternalMessage::M2G_JOIN_BATTLE& self, decltype(InternalMessage::M2G_JOIN_BATTLE::bySide) value) { self.bySide = value; });
    auto internal_message_m2g_arena_reward_type = cqyh::lua::usertype<InternalMessage::M2G_ARENA_REWARD>(L, internal_message_namespace, "M2G_ARENA_REWARD", "InternalMessage::M2G_ARENA_REWARD", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_arena_reward_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_ARENA_REWARD(); });
    internal_message_m2g_arena_reward_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_ARENA_REWARD>(new InternalMessage::M2G_ARENA_REWARD()); });
    internal_message_m2g_arena_reward_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_ARENA_REWARD& self) { return self.dwRoleID; }, [](InternalMessage::M2G_ARENA_REWARD& self, decltype(InternalMessage::M2G_ARENA_REWARD::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_arena_reward_type["dwItemID"] = sol::property([](const InternalMessage::M2G_ARENA_REWARD& self) { return self.dwItemID; }, [](InternalMessage::M2G_ARENA_REWARD& self, decltype(InternalMessage::M2G_ARENA_REWARD::dwItemID) value) { self.dwItemID = value; });
    internal_message_m2g_arena_reward_type["nMoney"] = sol::property([](const InternalMessage::M2G_ARENA_REWARD& self) { return self.nMoney; }, [](InternalMessage::M2G_ARENA_REWARD& self, decltype(InternalMessage::M2G_ARENA_REWARD::nMoney) value) { self.nMoney = value; });
}

}
