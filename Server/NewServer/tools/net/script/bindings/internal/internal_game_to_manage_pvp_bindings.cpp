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

void register_internal_game_to_manage_pvp_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_arena_sync_data_type = cqyh::lua::usertype<InternalMessage::G2M_ARENA_SYNC_DATA>(L, internal_message_namespace, "G2M_ARENA_SYNC_DATA", "InternalMessage::G2M_ARENA_SYNC_DATA", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_arena_sync_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_ARENA_SYNC_DATA(); });
    internal_message_g2m_arena_sync_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_ARENA_SYNC_DATA>(new InternalMessage::G2M_ARENA_SYNC_DATA()); });
    internal_message_g2m_arena_sync_data_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_ARENA_SYNC_DATA& self) { return self.dwRoleID; }, [](InternalMessage::G2M_ARENA_SYNC_DATA& self, decltype(InternalMessage::G2M_ARENA_SYNC_DATA::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_arena_sync_data_type["byPointSeasonTimes"] = sol::property([](const InternalMessage::G2M_ARENA_SYNC_DATA& self) { return self.byPointSeasonTimes; }, [](InternalMessage::G2M_ARENA_SYNC_DATA& self, decltype(InternalMessage::G2M_ARENA_SYNC_DATA::byPointSeasonTimes) value) { self.byPointSeasonTimes = value; });
    internal_message_g2m_arena_sync_data_type["nPointSeasonEndTime"] = sol::property([](const InternalMessage::G2M_ARENA_SYNC_DATA& self) { return self.nPointSeasonEndTime; }, [](InternalMessage::G2M_ARENA_SYNC_DATA& self, decltype(InternalMessage::G2M_ARENA_SYNC_DATA::nPointSeasonEndTime) value) { self.nPointSeasonEndTime = value; });
    auto internal_message_g2m_arena_join_season_type = cqyh::lua::usertype<InternalMessage::G2M_ARENA_JOIN_SEASON>(L, internal_message_namespace, "G2M_ARENA_JOIN_SEASON", "InternalMessage::G2M_ARENA_JOIN_SEASON", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_arena_join_season_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_ARENA_JOIN_SEASON(); });
    internal_message_g2m_arena_join_season_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_ARENA_JOIN_SEASON>(new InternalMessage::G2M_ARENA_JOIN_SEASON()); });
    internal_message_g2m_arena_join_season_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_ARENA_JOIN_SEASON& self) { return self.dwRoleID; }, [](InternalMessage::G2M_ARENA_JOIN_SEASON& self, decltype(InternalMessage::G2M_ARENA_JOIN_SEASON::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_g2m_arena_match_type = cqyh::lua::usertype<InternalMessage::G2M_ARENA_MATCH>(L, internal_message_namespace, "G2M_ARENA_MATCH", "InternalMessage::G2M_ARENA_MATCH", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_arena_match_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_ARENA_MATCH(); });
    internal_message_g2m_arena_match_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_ARENA_MATCH>(new InternalMessage::G2M_ARENA_MATCH()); });
    internal_message_g2m_arena_match_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_ARENA_MATCH& self) { return self.dwRoleID; }, [](InternalMessage::G2M_ARENA_MATCH& self, decltype(InternalMessage::G2M_ARENA_MATCH::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_g2m_arena_win_type = cqyh::lua::usertype<InternalMessage::G2M_ARENA_WIN>(L, internal_message_namespace, "G2M_ARENA_WIN", "InternalMessage::G2M_ARENA_WIN", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_arena_win_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_ARENA_WIN(); });
    internal_message_g2m_arena_win_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_ARENA_WIN>(new InternalMessage::G2M_ARENA_WIN()); });
    internal_message_g2m_arena_win_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_ARENA_WIN& self) { return self.dwRoleID; }, [](InternalMessage::G2M_ARENA_WIN& self, decltype(InternalMessage::G2M_ARENA_WIN::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_g2m_arena_defeated_type = cqyh::lua::usertype<InternalMessage::G2M_ARENA_DEFEATED>(L, internal_message_namespace, "G2M_ARENA_DEFEATED", "InternalMessage::G2M_ARENA_DEFEATED", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_arena_defeated_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_ARENA_DEFEATED(); });
    internal_message_g2m_arena_defeated_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_ARENA_DEFEATED>(new InternalMessage::G2M_ARENA_DEFEATED()); });
    internal_message_g2m_arena_defeated_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_ARENA_DEFEATED& self) { return self.dwRoleID; }, [](InternalMessage::G2M_ARENA_DEFEATED& self, decltype(InternalMessage::G2M_ARENA_DEFEATED::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_arena_defeated_type["byPointSeasonTimes"] = sol::property([](const InternalMessage::G2M_ARENA_DEFEATED& self) { return self.byPointSeasonTimes; }, [](InternalMessage::G2M_ARENA_DEFEATED& self, decltype(InternalMessage::G2M_ARENA_DEFEATED::byPointSeasonTimes) value) { self.byPointSeasonTimes = value; });
    internal_message_g2m_arena_defeated_type["nPointSeasonEndTime"] = sol::property([](const InternalMessage::G2M_ARENA_DEFEATED& self) { return self.nPointSeasonEndTime; }, [](InternalMessage::G2M_ARENA_DEFEATED& self, decltype(InternalMessage::G2M_ARENA_DEFEATED::nPointSeasonEndTime) value) { self.nPointSeasonEndTime = value; });
    auto internal_message_g2m_arena_reward_type = cqyh::lua::usertype<InternalMessage::G2M_ARENA_REWARD>(L, internal_message_namespace, "G2M_ARENA_REWARD", "InternalMessage::G2M_ARENA_REWARD", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_arena_reward_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_ARENA_REWARD(); });
    internal_message_g2m_arena_reward_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_ARENA_REWARD>(new InternalMessage::G2M_ARENA_REWARD()); });
    internal_message_g2m_arena_reward_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_ARENA_REWARD& self) { return self.dwRoleID; }, [](InternalMessage::G2M_ARENA_REWARD& self, decltype(InternalMessage::G2M_ARENA_REWARD::dwRoleID) value) { self.dwRoleID = value; });
}

}
