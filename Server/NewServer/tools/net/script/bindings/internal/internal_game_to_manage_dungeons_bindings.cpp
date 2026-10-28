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

void register_internal_game_to_manage_dungeons_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_clear_team_dungeon_type = cqyh::lua::usertype<InternalMessage::G2M_CLEAR_TEAM_DUNGEON>(L, internal_message_namespace, "G2M_CLEAR_TEAM_DUNGEON", "InternalMessage::G2M_CLEAR_TEAM_DUNGEON", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_clear_team_dungeon_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_CLEAR_TEAM_DUNGEON(); });
    internal_message_g2m_clear_team_dungeon_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_CLEAR_TEAM_DUNGEON>(new InternalMessage::G2M_CLEAR_TEAM_DUNGEON()); });
    internal_message_g2m_clear_team_dungeon_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_CLEAR_TEAM_DUNGEON& self) { return self.dwRoleID; }, [](InternalMessage::G2M_CLEAR_TEAM_DUNGEON& self, decltype(InternalMessage::G2M_CLEAR_TEAM_DUNGEON::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_g2m_guild_pre_open_dungeon_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON>(L, internal_message_namespace, "G2M_GUILD_PRE_OPEN_DUNGEON", "InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_pre_open_dungeon_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON(); });
    internal_message_g2m_guild_pre_open_dungeon_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON>(new InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON()); });
    internal_message_g2m_guild_pre_open_dungeon_type["dwGuildID"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON& self) { return self.dwGuildID; }, [](InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON& self, decltype(InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_g2m_guild_pre_open_dungeon_type["dwTemplateID"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON& self) { return self.dwTemplateID; }, [](InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON& self, decltype(InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON::dwTemplateID) value) { self.dwTemplateID = value; });
    internal_message_g2m_guild_pre_open_dungeon_type["dwOwnerID"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON& self) { return self.dwOwnerID; }, [](InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON& self, decltype(InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON::dwOwnerID) value) { self.dwOwnerID = value; });
    internal_message_g2m_guild_pre_open_dungeon_type["dwLeaderID"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON& self) { return self.dwLeaderID; }, [](InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON& self, decltype(InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON::dwLeaderID) value) { self.dwLeaderID = value; });
    internal_message_g2m_guild_pre_open_dungeon_type["llMoney"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON& self) { return self.llMoney; }, [](InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON& self, decltype(InternalMessage::G2M_GUILD_PRE_OPEN_DUNGEON::llMoney) value) { self.llMoney = value; });
    auto internal_message_g2m_guild_open_dungeon_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_OPEN_DUNGEON>(L, internal_message_namespace, "G2M_GUILD_OPEN_DUNGEON", "InternalMessage::G2M_GUILD_OPEN_DUNGEON", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_open_dungeon_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_OPEN_DUNGEON(); });
    internal_message_g2m_guild_open_dungeon_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_OPEN_DUNGEON>(new InternalMessage::G2M_GUILD_OPEN_DUNGEON()); });
    internal_message_g2m_guild_open_dungeon_type["dwOwnerID"] = sol::property([](const InternalMessage::G2M_GUILD_OPEN_DUNGEON& self) { return self.dwOwnerID; }, [](InternalMessage::G2M_GUILD_OPEN_DUNGEON& self, decltype(InternalMessage::G2M_GUILD_OPEN_DUNGEON::dwOwnerID) value) { self.dwOwnerID = value; });
    internal_message_g2m_guild_open_dungeon_type["dwLeaderID"] = sol::property([](const InternalMessage::G2M_GUILD_OPEN_DUNGEON& self) { return self.dwLeaderID; }, [](InternalMessage::G2M_GUILD_OPEN_DUNGEON& self, decltype(InternalMessage::G2M_GUILD_OPEN_DUNGEON::dwLeaderID) value) { self.dwLeaderID = value; });
    internal_message_g2m_guild_open_dungeon_type["dwTemplateID"] = sol::property([](const InternalMessage::G2M_GUILD_OPEN_DUNGEON& self) { return self.dwTemplateID; }, [](InternalMessage::G2M_GUILD_OPEN_DUNGEON& self, decltype(InternalMessage::G2M_GUILD_OPEN_DUNGEON::dwTemplateID) value) { self.dwTemplateID = value; });
    auto internal_message_g2m_guild_enter_dungeon_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_ENTER_DUNGEON>(L, internal_message_namespace, "G2M_GUILD_ENTER_DUNGEON", "InternalMessage::G2M_GUILD_ENTER_DUNGEON", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_enter_dungeon_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_ENTER_DUNGEON(); });
    internal_message_g2m_guild_enter_dungeon_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_ENTER_DUNGEON>(new InternalMessage::G2M_GUILD_ENTER_DUNGEON()); });
    internal_message_g2m_guild_enter_dungeon_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_ENTER_DUNGEON& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_ENTER_DUNGEON& self, decltype(InternalMessage::G2M_GUILD_ENTER_DUNGEON::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_guild_enter_dungeon_type["dwTemplateID"] = sol::property([](const InternalMessage::G2M_GUILD_ENTER_DUNGEON& self) { return self.dwTemplateID; }, [](InternalMessage::G2M_GUILD_ENTER_DUNGEON& self, decltype(InternalMessage::G2M_GUILD_ENTER_DUNGEON::dwTemplateID) value) { self.dwTemplateID = value; });
    auto internal_message_g2m_guild_close_dungeon_commission_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION>(L, internal_message_namespace, "G2M_GUILD_CLOSE_DUNGEON_COMMISSION", "InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_close_dungeon_commission_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION(); });
    internal_message_g2m_guild_close_dungeon_commission_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION>(new InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION()); });
    internal_message_g2m_guild_close_dungeon_commission_type["dwTemplateID"] = sol::property([](const InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION& self) { return self.dwTemplateID; }, [](InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION& self, decltype(InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION::dwTemplateID) value) { self.dwTemplateID = value; });
    internal_message_g2m_guild_close_dungeon_commission_type["dwSceneID"] = sol::property([](const InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION& self) { return self.dwSceneID; }, [](InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION& self, decltype(InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION::dwSceneID) value) { self.dwSceneID = value; });
    internal_message_g2m_guild_close_dungeon_commission_type["nItemNum"] = sol::property([](const InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION& self) { return self.nItemNum; }, [](InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION& self, decltype(InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION::nItemNum) value) { self.nItemNum = value; });
    internal_message_g2m_guild_close_dungeon_commission_type["arrItemID"] = cqyh::lua::array_property(&InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION::arrItemID);
    internal_message_g2m_guild_close_dungeon_commission_type["arrItemCount"] = cqyh::lua::array_property(&InternalMessage::G2M_GUILD_CLOSE_DUNGEON_COMMISSION::arrItemCount);
}

}
