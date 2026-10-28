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

void register_internal_manage_to_game_world_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_query_scene_ack_type = cqyh::lua::usertype<InternalMessage::M2G_QUERY_SCENE_ACK>(L, internal_message_namespace, "M2G_QUERY_SCENE_ACK", "InternalMessage::M2G_QUERY_SCENE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_query_scene_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_QUERY_SCENE_ACK(); });
    internal_message_m2g_query_scene_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_QUERY_SCENE_ACK>(new InternalMessage::M2G_QUERY_SCENE_ACK()); });
    internal_message_m2g_query_scene_ack_type["dwCliSessionID"] = sol::property([](const InternalMessage::M2G_QUERY_SCENE_ACK& self) { return self.dwCliSessionID; }, [](InternalMessage::M2G_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2G_QUERY_SCENE_ACK::dwCliSessionID) value) { self.dwCliSessionID = value; });
    internal_message_m2g_query_scene_ack_type["nErrCode"] = sol::property([](const InternalMessage::M2G_QUERY_SCENE_ACK& self) { return self.nErrCode; }, [](InternalMessage::M2G_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2G_QUERY_SCENE_ACK::nErrCode) value) { self.nErrCode = value; });
    internal_message_m2g_query_scene_ack_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_QUERY_SCENE_ACK& self) { return self.dwRoleID; }, [](InternalMessage::M2G_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2G_QUERY_SCENE_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_query_scene_ack_type["nSceneTempID"] = sol::property([](const InternalMessage::M2G_QUERY_SCENE_ACK& self) { return self.nSceneTempID; }, [](InternalMessage::M2G_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2G_QUERY_SCENE_ACK::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_m2g_query_scene_ack_type["nSceneID"] = sol::property([](const InternalMessage::M2G_QUERY_SCENE_ACK& self) { return self.nSceneID; }, [](InternalMessage::M2G_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2G_QUERY_SCENE_ACK::nSceneID) value) { self.nSceneID = value; });
    internal_message_m2g_query_scene_ack_type["nDestX"] = sol::property([](const InternalMessage::M2G_QUERY_SCENE_ACK& self) { return self.nDestX; }, [](InternalMessage::M2G_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2G_QUERY_SCENE_ACK::nDestX) value) { self.nDestX = value; });
    internal_message_m2g_query_scene_ack_type["nDestY"] = sol::property([](const InternalMessage::M2G_QUERY_SCENE_ACK& self) { return self.nDestY; }, [](InternalMessage::M2G_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2G_QUERY_SCENE_ACK::nDestY) value) { self.nDestY = value; });
    internal_message_m2g_query_scene_ack_type["nDestZ"] = sol::property([](const InternalMessage::M2G_QUERY_SCENE_ACK& self) { return self.nDestZ; }, [](InternalMessage::M2G_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2G_QUERY_SCENE_ACK::nDestZ) value) { self.nDestZ = value; });
    internal_message_m2g_query_scene_ack_type["nFaceDirection"] = sol::property([](const InternalMessage::M2G_QUERY_SCENE_ACK& self) { return self.nFaceDirection; }, [](InternalMessage::M2G_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2G_QUERY_SCENE_ACK::nFaceDirection) value) { self.nFaceDirection = value; });
    auto internal_message_m2g_create_scene_type = cqyh::lua::usertype<InternalMessage::M2G_CREATE_SCENE>(L, internal_message_namespace, "M2G_CREATE_SCENE", "InternalMessage::M2G_CREATE_SCENE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_create_scene_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_CREATE_SCENE(); });
    internal_message_m2g_create_scene_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_CREATE_SCENE>(new InternalMessage::M2G_CREATE_SCENE()); });
    internal_message_m2g_create_scene_type["byGroupID"] = sol::property([](const InternalMessage::M2G_CREATE_SCENE& self) { return self.byGroupID; }, [](InternalMessage::M2G_CREATE_SCENE& self, decltype(InternalMessage::M2G_CREATE_SCENE::byGroupID) value) { self.byGroupID = value; });
    internal_message_m2g_create_scene_type["nSceneTempID"] = sol::property([](const InternalMessage::M2G_CREATE_SCENE& self) { return self.nSceneTempID; }, [](InternalMessage::M2G_CREATE_SCENE& self, decltype(InternalMessage::M2G_CREATE_SCENE::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_m2g_create_scene_type["nSceneID"] = sol::property([](const InternalMessage::M2G_CREATE_SCENE& self) { return self.nSceneID; }, [](InternalMessage::M2G_CREATE_SCENE& self, decltype(InternalMessage::M2G_CREATE_SCENE::nSceneID) value) { self.nSceneID = value; });
    auto internal_message_m2g_destroy_scene_type = cqyh::lua::usertype<InternalMessage::M2G_DESTROY_SCENE>(L, internal_message_namespace, "M2G_DESTROY_SCENE", "InternalMessage::M2G_DESTROY_SCENE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_destroy_scene_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_DESTROY_SCENE(); });
    internal_message_m2g_destroy_scene_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_DESTROY_SCENE>(new InternalMessage::M2G_DESTROY_SCENE()); });
    internal_message_m2g_destroy_scene_type["byGroupID"] = sol::property([](const InternalMessage::M2G_DESTROY_SCENE& self) { return self.byGroupID; }, [](InternalMessage::M2G_DESTROY_SCENE& self, decltype(InternalMessage::M2G_DESTROY_SCENE::byGroupID) value) { self.byGroupID = value; });
    internal_message_m2g_destroy_scene_type["nSceneTempID"] = sol::property([](const InternalMessage::M2G_DESTROY_SCENE& self) { return self.nSceneTempID; }, [](InternalMessage::M2G_DESTROY_SCENE& self, decltype(InternalMessage::M2G_DESTROY_SCENE::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_m2g_destroy_scene_type["nSceneID"] = sol::property([](const InternalMessage::M2G_DESTROY_SCENE& self) { return self.nSceneID; }, [](InternalMessage::M2G_DESTROY_SCENE& self, decltype(InternalMessage::M2G_DESTROY_SCENE::nSceneID) value) { self.nSceneID = value; });
    auto internal_message_m2g_close_scene_type = cqyh::lua::usertype<InternalMessage::M2G_CLOSE_SCENE>(L, internal_message_namespace, "M2G_CLOSE_SCENE", "InternalMessage::M2G_CLOSE_SCENE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_close_scene_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_CLOSE_SCENE(); });
    internal_message_m2g_close_scene_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_CLOSE_SCENE>(new InternalMessage::M2G_CLOSE_SCENE()); });
    internal_message_m2g_close_scene_type["byServerGroup"] = sol::property([](const InternalMessage::M2G_CLOSE_SCENE& self) { return self.byServerGroup; }, [](InternalMessage::M2G_CLOSE_SCENE& self, decltype(InternalMessage::M2G_CLOSE_SCENE::byServerGroup) value) { self.byServerGroup = value; });
    internal_message_m2g_close_scene_type["nSceneTempID"] = sol::property([](const InternalMessage::M2G_CLOSE_SCENE& self) { return self.nSceneTempID; }, [](InternalMessage::M2G_CLOSE_SCENE& self, decltype(InternalMessage::M2G_CLOSE_SCENE::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_m2g_close_scene_type["nSceneID"] = sol::property([](const InternalMessage::M2G_CLOSE_SCENE& self) { return self.nSceneID; }, [](InternalMessage::M2G_CLOSE_SCENE& self, decltype(InternalMessage::M2G_CLOSE_SCENE::nSceneID) value) { self.nSceneID = value; });
    auto internal_message_m2g_change_scene_type = cqyh::lua::usertype<InternalMessage::M2G_CHANGE_SCENE>(L, internal_message_namespace, "M2G_CHANGE_SCENE", "InternalMessage::M2G_CHANGE_SCENE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_change_scene_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_CHANGE_SCENE(); });
    internal_message_m2g_change_scene_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_CHANGE_SCENE>(new InternalMessage::M2G_CHANGE_SCENE()); });
    internal_message_m2g_change_scene_type["dwCliSessionID"] = sol::property([](const InternalMessage::M2G_CHANGE_SCENE& self) { return self.dwCliSessionID; }, [](InternalMessage::M2G_CHANGE_SCENE& self, decltype(InternalMessage::M2G_CHANGE_SCENE::dwCliSessionID) value) { self.dwCliSessionID = value; });
    internal_message_m2g_change_scene_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_CHANGE_SCENE& self) { return self.dwRoleID; }, [](InternalMessage::M2G_CHANGE_SCENE& self, decltype(InternalMessage::M2G_CHANGE_SCENE::dwRoleID) value) { self.dwRoleID = value; });
}

}
