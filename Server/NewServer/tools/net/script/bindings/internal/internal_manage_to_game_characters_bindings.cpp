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

namespace cqyh::net_tools::bindings {

void register_internal_manage_to_game_characters_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_sync_role_social_data_type = cqyh::lua::usertype<InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA>(L, internal_message_namespace, "M2G_SYNC_ROLE_SOCIAL_DATA", "InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_sync_role_social_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA(); });
    internal_message_m2g_sync_role_social_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA>(new InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA()); });
    internal_message_m2g_sync_role_social_data_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA& self) { return self.dwRoleID; }, [](InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA& self, decltype(InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_sync_role_social_data_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA& self) { return self.dwGuildID; }, [](InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA& self, decltype(InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_sync_role_social_data_type["dwForbidChatTime"] = sol::property([](const InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA& self) { return self.dwForbidChatTime; }, [](InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA& self, decltype(InternalMessage::M2G_SYNC_ROLE_SOCIAL_DATA::dwForbidChatTime) value) { self.dwForbidChatTime = value; });
    auto internal_message_m2g_query_role_location_type = cqyh::lua::usertype<InternalMessage::M2G_QUERY_ROLE_LOCATION>(L, internal_message_namespace, "M2G_QUERY_ROLE_LOCATION", "InternalMessage::M2G_QUERY_ROLE_LOCATION", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_query_role_location_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_QUERY_ROLE_LOCATION(); });
    internal_message_m2g_query_role_location_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_QUERY_ROLE_LOCATION>(new InternalMessage::M2G_QUERY_ROLE_LOCATION()); });
    internal_message_m2g_query_role_location_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_QUERY_ROLE_LOCATION& self) { return self.dwRoleID; }, [](InternalMessage::M2G_QUERY_ROLE_LOCATION& self, decltype(InternalMessage::M2G_QUERY_ROLE_LOCATION::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_query_role_location_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2G_QUERY_ROLE_LOCATION& self) { return self.dwClientSessionID; }, [](InternalMessage::M2G_QUERY_ROLE_LOCATION& self, decltype(InternalMessage::M2G_QUERY_ROLE_LOCATION::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_m2g_query_role_location_type["dwTargetRoleID"] = sol::property([](const InternalMessage::M2G_QUERY_ROLE_LOCATION& self) { return self.dwTargetRoleID; }, [](InternalMessage::M2G_QUERY_ROLE_LOCATION& self, decltype(InternalMessage::M2G_QUERY_ROLE_LOCATION::dwTargetRoleID) value) { self.dwTargetRoleID = value; });
    internal_message_m2g_query_role_location_type["bFromItem"] = sol::property([](const InternalMessage::M2G_QUERY_ROLE_LOCATION& self) { return self.bFromItem; }, [](InternalMessage::M2G_QUERY_ROLE_LOCATION& self, decltype(InternalMessage::M2G_QUERY_ROLE_LOCATION::bFromItem) value) { self.bFromItem = value; });
    auto internal_message_m2g_query_role_location_ack_type = cqyh::lua::usertype<InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK>(L, internal_message_namespace, "M2G_QUERY_ROLE_LOCATION_ACK", "InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_query_role_location_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK(); });
    internal_message_m2g_query_role_location_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK>(new InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK()); });
    internal_message_m2g_query_role_location_ack_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self) { return self.dwRoleID; }, [](InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self, decltype(InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_query_role_location_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self, decltype(InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_m2g_query_role_location_ack_type["nSceneTempID"] = sol::property([](const InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self) { return self.nSceneTempID; }, [](InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self, decltype(InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_m2g_query_role_location_ack_type["nSceneID"] = sol::property([](const InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self) { return self.nSceneID; }, [](InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self, decltype(InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK::nSceneID) value) { self.nSceneID = value; });
    internal_message_m2g_query_role_location_ack_type["nX"] = sol::property([](const InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self) { return self.nX; }, [](InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self, decltype(InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK::nX) value) { self.nX = value; });
    internal_message_m2g_query_role_location_ack_type["nY"] = sol::property([](const InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self) { return self.nY; }, [](InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self, decltype(InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK::nY) value) { self.nY = value; });
    internal_message_m2g_query_role_location_ack_type["nZ"] = sol::property([](const InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self) { return self.nZ; }, [](InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self, decltype(InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK::nZ) value) { self.nZ = value; });
    internal_message_m2g_query_role_location_ack_type["bFromItem"] = sol::property([](const InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self) { return self.bFromItem; }, [](InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK& self, decltype(InternalMessage::M2G_QUERY_ROLE_LOCATION_ACK::bFromItem) value) { self.bFromItem = value; });
    auto internal_message_m2g_take_role_type = cqyh::lua::usertype<InternalMessage::M2G_TAKE_ROLE>(L, internal_message_namespace, "M2G_TAKE_ROLE", "InternalMessage::M2G_TAKE_ROLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_take_role_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_TAKE_ROLE(); });
    internal_message_m2g_take_role_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_TAKE_ROLE>(new InternalMessage::M2G_TAKE_ROLE()); });
    internal_message_m2g_take_role_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_TAKE_ROLE& self) { return self.dwRoleID; }, [](InternalMessage::M2G_TAKE_ROLE& self, decltype(InternalMessage::M2G_TAKE_ROLE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_take_role_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2G_TAKE_ROLE& self) { return self.dwClientSessionID; }, [](InternalMessage::M2G_TAKE_ROLE& self, decltype(InternalMessage::M2G_TAKE_ROLE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_m2g_take_role_type["nSceneTempID"] = sol::property([](const InternalMessage::M2G_TAKE_ROLE& self) { return self.nSceneTempID; }, [](InternalMessage::M2G_TAKE_ROLE& self, decltype(InternalMessage::M2G_TAKE_ROLE::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_m2g_take_role_type["nSceneID"] = sol::property([](const InternalMessage::M2G_TAKE_ROLE& self) { return self.nSceneID; }, [](InternalMessage::M2G_TAKE_ROLE& self, decltype(InternalMessage::M2G_TAKE_ROLE::nSceneID) value) { self.nSceneID = value; });
    internal_message_m2g_take_role_type["nX"] = sol::property([](const InternalMessage::M2G_TAKE_ROLE& self) { return self.nX; }, [](InternalMessage::M2G_TAKE_ROLE& self, decltype(InternalMessage::M2G_TAKE_ROLE::nX) value) { self.nX = value; });
    internal_message_m2g_take_role_type["nY"] = sol::property([](const InternalMessage::M2G_TAKE_ROLE& self) { return self.nY; }, [](InternalMessage::M2G_TAKE_ROLE& self, decltype(InternalMessage::M2G_TAKE_ROLE::nY) value) { self.nY = value; });
    internal_message_m2g_take_role_type["nZ"] = sol::property([](const InternalMessage::M2G_TAKE_ROLE& self) { return self.nZ; }, [](InternalMessage::M2G_TAKE_ROLE& self, decltype(InternalMessage::M2G_TAKE_ROLE::nZ) value) { self.nZ = value; });
    auto internal_message_m2g_arrest_role_type = cqyh::lua::usertype<InternalMessage::M2G_ARREST_ROLE>(L, internal_message_namespace, "M2G_ARREST_ROLE", "InternalMessage::M2G_ARREST_ROLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_arrest_role_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_ARREST_ROLE(); });
    internal_message_m2g_arrest_role_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_ARREST_ROLE>(new InternalMessage::M2G_ARREST_ROLE()); });
    internal_message_m2g_arrest_role_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_ARREST_ROLE& self) { return self.dwRoleID; }, [](InternalMessage::M2G_ARREST_ROLE& self, decltype(InternalMessage::M2G_ARREST_ROLE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_arrest_role_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2G_ARREST_ROLE& self) { return self.dwClientSessionID; }, [](InternalMessage::M2G_ARREST_ROLE& self, decltype(InternalMessage::M2G_ARREST_ROLE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_m2g_arrest_role_type["nDuration"] = sol::property([](const InternalMessage::M2G_ARREST_ROLE& self) { return self.nDuration; }, [](InternalMessage::M2G_ARREST_ROLE& self, decltype(InternalMessage::M2G_ARREST_ROLE::nDuration) value) { self.nDuration = value; });
    auto internal_message_m2g_update_average_level_type = cqyh::lua::usertype<InternalMessage::M2G_UPDATE_AVERAGE_LEVEL>(L, internal_message_namespace, "M2G_UPDATE_AVERAGE_LEVEL", "InternalMessage::M2G_UPDATE_AVERAGE_LEVEL", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_update_average_level_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_UPDATE_AVERAGE_LEVEL(); });
    internal_message_m2g_update_average_level_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_UPDATE_AVERAGE_LEVEL>(new InternalMessage::M2G_UPDATE_AVERAGE_LEVEL()); });
    internal_message_m2g_update_average_level_type["nAverageLevel"] = cqyh::lua::array_property(&InternalMessage::M2G_UPDATE_AVERAGE_LEVEL::nAverageLevel);
}

}
