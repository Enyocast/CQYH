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

void register_internal_manage_to_game_guild_war_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_guild_sync_war_relation_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_SYNC_WAR_RELATION>(L, internal_message_namespace, "M2G_GUILD_SYNC_WAR_RELATION", "InternalMessage::M2G_GUILD_SYNC_WAR_RELATION", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_sync_war_relation_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_SYNC_WAR_RELATION(); });
    internal_message_m2g_guild_sync_war_relation_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_SYNC_WAR_RELATION>(new InternalMessage::M2G_GUILD_SYNC_WAR_RELATION()); });
    internal_message_m2g_guild_sync_war_relation_type["dwIntruderID"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_WAR_RELATION& self) { return self.dwIntruderID; }, [](InternalMessage::M2G_GUILD_SYNC_WAR_RELATION& self, decltype(InternalMessage::M2G_GUILD_SYNC_WAR_RELATION::dwIntruderID) value) { self.dwIntruderID = value; });
    internal_message_m2g_guild_sync_war_relation_type["dwDefenderID"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_WAR_RELATION& self) { return self.dwDefenderID; }, [](InternalMessage::M2G_GUILD_SYNC_WAR_RELATION& self, decltype(InternalMessage::M2G_GUILD_SYNC_WAR_RELATION::dwDefenderID) value) { self.dwDefenderID = value; });
    auto internal_message_m2g_guild_sync_war_char_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_SYNC_WAR_CHAR>(L, internal_message_namespace, "M2G_GUILD_SYNC_WAR_CHAR", "InternalMessage::M2G_GUILD_SYNC_WAR_CHAR", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_sync_war_char_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_SYNC_WAR_CHAR(); });
    internal_message_m2g_guild_sync_war_char_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_SYNC_WAR_CHAR>(new InternalMessage::M2G_GUILD_SYNC_WAR_CHAR()); });
    internal_message_m2g_guild_sync_war_char_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_WAR_CHAR& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_SYNC_WAR_CHAR& self, decltype(InternalMessage::M2G_GUILD_SYNC_WAR_CHAR::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_sync_war_char_type["byCharacter"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_WAR_CHAR& self) { return self.byCharacter; }, [](InternalMessage::M2G_GUILD_SYNC_WAR_CHAR& self, decltype(InternalMessage::M2G_GUILD_SYNC_WAR_CHAR::byCharacter) value) { self.byCharacter = value; });
    auto internal_message_m2g_guild_war_end_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_WAR_END>(L, internal_message_namespace, "M2G_GUILD_WAR_END", "InternalMessage::M2G_GUILD_WAR_END", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_war_end_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_WAR_END(); });
    internal_message_m2g_guild_war_end_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_WAR_END>(new InternalMessage::M2G_GUILD_WAR_END()); });
    internal_message_m2g_guild_war_end_type["dwDefenderID"] = sol::property([](const InternalMessage::M2G_GUILD_WAR_END& self) { return self.dwDefenderID; }, [](InternalMessage::M2G_GUILD_WAR_END& self, decltype(InternalMessage::M2G_GUILD_WAR_END::dwDefenderID) value) { self.dwDefenderID = value; });
    auto internal_message_m2g_guild_achievement_reward_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_ACHIEVEMENT_REWARD>(L, internal_message_namespace, "M2G_GUILD_ACHIEVEMENT_REWARD", "InternalMessage::M2G_GUILD_ACHIEVEMENT_REWARD", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_achievement_reward_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_ACHIEVEMENT_REWARD(); });
    internal_message_m2g_guild_achievement_reward_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_ACHIEVEMENT_REWARD>(new InternalMessage::M2G_GUILD_ACHIEVEMENT_REWARD()); });
    internal_message_m2g_guild_achievement_reward_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_GUILD_ACHIEVEMENT_REWARD& self) { return self.dwRoleID; }, [](InternalMessage::M2G_GUILD_ACHIEVEMENT_REWARD& self, decltype(InternalMessage::M2G_GUILD_ACHIEVEMENT_REWARD::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_guild_achievement_reward_type["nID"] = sol::property([](const InternalMessage::M2G_GUILD_ACHIEVEMENT_REWARD& self) { return self.nID; }, [](InternalMessage::M2G_GUILD_ACHIEVEMENT_REWARD& self, decltype(InternalMessage::M2G_GUILD_ACHIEVEMENT_REWARD::nID) value) { self.nID = value; });
}

}
