#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/g2m_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_game_to_manage_guild_war_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_guild_end_war_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_END_WAR>(L, internal_message_namespace, "G2M_GUILD_END_WAR", "InternalMessage::G2M_GUILD_END_WAR", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_end_war_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_END_WAR(); });
    internal_message_g2m_guild_end_war_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_END_WAR>(new InternalMessage::G2M_GUILD_END_WAR()); });
    internal_message_g2m_guild_end_war_type["dwDefenderID"] = sol::property([](const InternalMessage::G2M_GUILD_END_WAR& self) { return self.dwDefenderID; }, [](InternalMessage::G2M_GUILD_END_WAR& self, decltype(InternalMessage::G2M_GUILD_END_WAR::dwDefenderID) value) { self.dwDefenderID = value; });
    internal_message_g2m_guild_end_war_type["nWarDefenderResult"] = sol::property([](const InternalMessage::G2M_GUILD_END_WAR& self) { return self.nWarDefenderResult; }, [](InternalMessage::G2M_GUILD_END_WAR& self, decltype(InternalMessage::G2M_GUILD_END_WAR::nWarDefenderResult) value) { self.nWarDefenderResult = value; });
    auto internal_message_g2m_guild_achievement_reward_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_ACHIEVEMENT_REWARD>(L, internal_message_namespace, "G2M_GUILD_ACHIEVEMENT_REWARD", "InternalMessage::G2M_GUILD_ACHIEVEMENT_REWARD", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_achievement_reward_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_ACHIEVEMENT_REWARD(); });
    internal_message_g2m_guild_achievement_reward_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_ACHIEVEMENT_REWARD>(new InternalMessage::G2M_GUILD_ACHIEVEMENT_REWARD()); });
    internal_message_g2m_guild_achievement_reward_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_ACHIEVEMENT_REWARD& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_ACHIEVEMENT_REWARD& self, decltype(InternalMessage::G2M_GUILD_ACHIEVEMENT_REWARD::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_guild_achievement_reward_type["nID"] = sol::property([](const InternalMessage::G2M_GUILD_ACHIEVEMENT_REWARD& self) { return self.nID; }, [](InternalMessage::G2M_GUILD_ACHIEVEMENT_REWARD& self, decltype(InternalMessage::G2M_GUILD_ACHIEVEMENT_REWARD::nID) value) { self.nID = value; });
}

}
