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

void register_internal_manage_to_game_dungeons_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_room_enter_dungeon_type = cqyh::lua::usertype<InternalMessage::M2G_ROOM_ENTER_DUNGEON>(L, internal_message_namespace, "M2G_ROOM_ENTER_DUNGEON", "InternalMessage::M2G_ROOM_ENTER_DUNGEON", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_room_enter_dungeon_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_ROOM_ENTER_DUNGEON(); });
    internal_message_m2g_room_enter_dungeon_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_ROOM_ENTER_DUNGEON>(new InternalMessage::M2G_ROOM_ENTER_DUNGEON()); });
    internal_message_m2g_room_enter_dungeon_type["dwCliSessionID"] = sol::property([](const InternalMessage::M2G_ROOM_ENTER_DUNGEON& self) { return self.dwCliSessionID; }, [](InternalMessage::M2G_ROOM_ENTER_DUNGEON& self, decltype(InternalMessage::M2G_ROOM_ENTER_DUNGEON::dwCliSessionID) value) { self.dwCliSessionID = value; });
    internal_message_m2g_room_enter_dungeon_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_ROOM_ENTER_DUNGEON& self) { return self.dwRoleID; }, [](InternalMessage::M2G_ROOM_ENTER_DUNGEON& self, decltype(InternalMessage::M2G_ROOM_ENTER_DUNGEON::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_room_enter_dungeon_type["nSceneTempID"] = sol::property([](const InternalMessage::M2G_ROOM_ENTER_DUNGEON& self) { return self.nSceneTempID; }, [](InternalMessage::M2G_ROOM_ENTER_DUNGEON& self, decltype(InternalMessage::M2G_ROOM_ENTER_DUNGEON::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_m2g_room_enter_dungeon_type["nSceneID"] = sol::property([](const InternalMessage::M2G_ROOM_ENTER_DUNGEON& self) { return self.nSceneID; }, [](InternalMessage::M2G_ROOM_ENTER_DUNGEON& self, decltype(InternalMessage::M2G_ROOM_ENTER_DUNGEON::nSceneID) value) { self.nSceneID = value; });
    auto internal_message_m2g_guild_pre_open_dungeon_ack_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK>(L, internal_message_namespace, "M2G_GUILD_PRE_OPEN_DUNGEON_ACK", "InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_pre_open_dungeon_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK(); });
    internal_message_m2g_guild_pre_open_dungeon_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK>(new InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK()); });
    internal_message_m2g_guild_pre_open_dungeon_ack_type["dwTemplateID"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK& self) { return self.dwTemplateID; }, [](InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK::dwTemplateID) value) { self.dwTemplateID = value; });
    internal_message_m2g_guild_pre_open_dungeon_ack_type["dwOwnerID"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK& self) { return self.dwOwnerID; }, [](InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK::dwOwnerID) value) { self.dwOwnerID = value; });
    internal_message_m2g_guild_pre_open_dungeon_ack_type["dwLeaderID"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK& self) { return self.dwLeaderID; }, [](InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK::dwLeaderID) value) { self.dwLeaderID = value; });
    internal_message_m2g_guild_pre_open_dungeon_ack_type["nConsumeMoney"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK& self) { return self.nConsumeMoney; }, [](InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_OPEN_DUNGEON_ACK::nConsumeMoney) value) { self.nConsumeMoney = value; });
    auto internal_message_m2g_guild_enter_dungeon_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_ENTER_DUNGEON>(L, internal_message_namespace, "M2G_GUILD_ENTER_DUNGEON", "InternalMessage::M2G_GUILD_ENTER_DUNGEON", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_enter_dungeon_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_ENTER_DUNGEON(); });
    internal_message_m2g_guild_enter_dungeon_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_ENTER_DUNGEON>(new InternalMessage::M2G_GUILD_ENTER_DUNGEON()); });
    internal_message_m2g_guild_enter_dungeon_type["dwTemplateID"] = sol::property([](const InternalMessage::M2G_GUILD_ENTER_DUNGEON& self) { return self.dwTemplateID; }, [](InternalMessage::M2G_GUILD_ENTER_DUNGEON& self, decltype(InternalMessage::M2G_GUILD_ENTER_DUNGEON::dwTemplateID) value) { self.dwTemplateID = value; });
    internal_message_m2g_guild_enter_dungeon_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_GUILD_ENTER_DUNGEON& self) { return self.dwRoleID; }, [](InternalMessage::M2G_GUILD_ENTER_DUNGEON& self, decltype(InternalMessage::M2G_GUILD_ENTER_DUNGEON::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_guild_enter_dungeon_type["dwDungeonLeaderID"] = sol::property([](const InternalMessage::M2G_GUILD_ENTER_DUNGEON& self) { return self.dwDungeonLeaderID; }, [](InternalMessage::M2G_GUILD_ENTER_DUNGEON& self, decltype(InternalMessage::M2G_GUILD_ENTER_DUNGEON::dwDungeonLeaderID) value) { self.dwDungeonLeaderID = value; });
}

}
