#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/g2m_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_game_to_manage_world_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_create_scene_ack_type = cqyh::lua::usertype<InternalMessage::G2M_CREATE_SCENE_ACK>(L, internal_message_namespace, "G2M_CREATE_SCENE_ACK", "InternalMessage::G2M_CREATE_SCENE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_create_scene_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_CREATE_SCENE_ACK(); });
    internal_message_g2m_create_scene_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_CREATE_SCENE_ACK>(new InternalMessage::G2M_CREATE_SCENE_ACK()); });
    internal_message_g2m_create_scene_ack_type["nErrCode"] = sol::property([](const InternalMessage::G2M_CREATE_SCENE_ACK& self) { return self.nErrCode; }, [](InternalMessage::G2M_CREATE_SCENE_ACK& self, decltype(InternalMessage::G2M_CREATE_SCENE_ACK::nErrCode) value) { self.nErrCode = value; });
    internal_message_g2m_create_scene_ack_type["byGroupID"] = sol::property([](const InternalMessage::G2M_CREATE_SCENE_ACK& self) { return self.byGroupID; }, [](InternalMessage::G2M_CREATE_SCENE_ACK& self, decltype(InternalMessage::G2M_CREATE_SCENE_ACK::byGroupID) value) { self.byGroupID = value; });
    internal_message_g2m_create_scene_ack_type["nSceneTempID"] = sol::property([](const InternalMessage::G2M_CREATE_SCENE_ACK& self) { return self.nSceneTempID; }, [](InternalMessage::G2M_CREATE_SCENE_ACK& self, decltype(InternalMessage::G2M_CREATE_SCENE_ACK::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_g2m_create_scene_ack_type["nSceneID"] = sol::property([](const InternalMessage::G2M_CREATE_SCENE_ACK& self) { return self.nSceneID; }, [](InternalMessage::G2M_CREATE_SCENE_ACK& self, decltype(InternalMessage::G2M_CREATE_SCENE_ACK::nSceneID) value) { self.nSceneID = value; });
    auto internal_message_g2m_close_scene_type = cqyh::lua::usertype<InternalMessage::G2M_CLOSE_SCENE>(L, internal_message_namespace, "G2M_CLOSE_SCENE", "InternalMessage::G2M_CLOSE_SCENE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_close_scene_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_CLOSE_SCENE(); });
    internal_message_g2m_close_scene_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_CLOSE_SCENE>(new InternalMessage::G2M_CLOSE_SCENE()); });
    internal_message_g2m_close_scene_type["byServerGroup"] = sol::property([](const InternalMessage::G2M_CLOSE_SCENE& self) { return self.byServerGroup; }, [](InternalMessage::G2M_CLOSE_SCENE& self, decltype(InternalMessage::G2M_CLOSE_SCENE::byServerGroup) value) { self.byServerGroup = value; });
    internal_message_g2m_close_scene_type["nSceneTempID"] = sol::property([](const InternalMessage::G2M_CLOSE_SCENE& self) { return self.nSceneTempID; }, [](InternalMessage::G2M_CLOSE_SCENE& self, decltype(InternalMessage::G2M_CLOSE_SCENE::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_g2m_close_scene_type["nSceneID"] = sol::property([](const InternalMessage::G2M_CLOSE_SCENE& self) { return self.nSceneID; }, [](InternalMessage::G2M_CLOSE_SCENE& self, decltype(InternalMessage::G2M_CLOSE_SCENE::nSceneID) value) { self.nSceneID = value; });
    auto internal_message_g2m_destroy_scene_ack_type = cqyh::lua::usertype<InternalMessage::G2M_DESTROY_SCENE_ACK>(L, internal_message_namespace, "G2M_DESTROY_SCENE_ACK", "InternalMessage::G2M_DESTROY_SCENE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_destroy_scene_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_DESTROY_SCENE_ACK(); });
    internal_message_g2m_destroy_scene_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_DESTROY_SCENE_ACK>(new InternalMessage::G2M_DESTROY_SCENE_ACK()); });
    internal_message_g2m_destroy_scene_ack_type["nErrCode"] = sol::property([](const InternalMessage::G2M_DESTROY_SCENE_ACK& self) { return self.nErrCode; }, [](InternalMessage::G2M_DESTROY_SCENE_ACK& self, decltype(InternalMessage::G2M_DESTROY_SCENE_ACK::nErrCode) value) { self.nErrCode = value; });
    internal_message_g2m_destroy_scene_ack_type["byGroupID"] = sol::property([](const InternalMessage::G2M_DESTROY_SCENE_ACK& self) { return self.byGroupID; }, [](InternalMessage::G2M_DESTROY_SCENE_ACK& self, decltype(InternalMessage::G2M_DESTROY_SCENE_ACK::byGroupID) value) { self.byGroupID = value; });
    internal_message_g2m_destroy_scene_ack_type["nSceneTempID"] = sol::property([](const InternalMessage::G2M_DESTROY_SCENE_ACK& self) { return self.nSceneTempID; }, [](InternalMessage::G2M_DESTROY_SCENE_ACK& self, decltype(InternalMessage::G2M_DESTROY_SCENE_ACK::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_g2m_destroy_scene_ack_type["nSceneID"] = sol::property([](const InternalMessage::G2M_DESTROY_SCENE_ACK& self) { return self.nSceneID; }, [](InternalMessage::G2M_DESTROY_SCENE_ACK& self, decltype(InternalMessage::G2M_DESTROY_SCENE_ACK::nSceneID) value) { self.nSceneID = value; });
    auto internal_message_g2m_reset_scene_type = cqyh::lua::usertype<InternalMessage::G2M_RESET_SCENE>(L, internal_message_namespace, "G2M_RESET_SCENE", "InternalMessage::G2M_RESET_SCENE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_reset_scene_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_RESET_SCENE(); });
    internal_message_g2m_reset_scene_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_RESET_SCENE>(new InternalMessage::G2M_RESET_SCENE()); });
    auto internal_message_g2m_query_scene_type = cqyh::lua::usertype<InternalMessage::G2M_QUERY_SCENE>(L, internal_message_namespace, "G2M_QUERY_SCENE", "InternalMessage::G2M_QUERY_SCENE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_query_scene_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_QUERY_SCENE(); });
    internal_message_g2m_query_scene_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_QUERY_SCENE>(new InternalMessage::G2M_QUERY_SCENE()); });
    internal_message_g2m_query_scene_type["dwClientSessionID"] = sol::property([](const InternalMessage::G2M_QUERY_SCENE& self) { return self.dwClientSessionID; }, [](InternalMessage::G2M_QUERY_SCENE& self, decltype(InternalMessage::G2M_QUERY_SCENE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_g2m_query_scene_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_QUERY_SCENE& self) { return self.dwRoleID; }, [](InternalMessage::G2M_QUERY_SCENE& self, decltype(InternalMessage::G2M_QUERY_SCENE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_query_scene_type["nSceneTempID"] = sol::property([](const InternalMessage::G2M_QUERY_SCENE& self) { return self.nSceneTempID; }, [](InternalMessage::G2M_QUERY_SCENE& self, decltype(InternalMessage::G2M_QUERY_SCENE::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_g2m_query_scene_type["nSceneID"] = sol::property([](const InternalMessage::G2M_QUERY_SCENE& self) { return self.nSceneID; }, [](InternalMessage::G2M_QUERY_SCENE& self, decltype(InternalMessage::G2M_QUERY_SCENE::nSceneID) value) { self.nSceneID = value; });
    internal_message_g2m_query_scene_type["nDestX"] = sol::property([](const InternalMessage::G2M_QUERY_SCENE& self) { return self.nDestX; }, [](InternalMessage::G2M_QUERY_SCENE& self, decltype(InternalMessage::G2M_QUERY_SCENE::nDestX) value) { self.nDestX = value; });
    internal_message_g2m_query_scene_type["nDestY"] = sol::property([](const InternalMessage::G2M_QUERY_SCENE& self) { return self.nDestY; }, [](InternalMessage::G2M_QUERY_SCENE& self, decltype(InternalMessage::G2M_QUERY_SCENE::nDestY) value) { self.nDestY = value; });
    internal_message_g2m_query_scene_type["nDestZ"] = sol::property([](const InternalMessage::G2M_QUERY_SCENE& self) { return self.nDestZ; }, [](InternalMessage::G2M_QUERY_SCENE& self, decltype(InternalMessage::G2M_QUERY_SCENE::nDestZ) value) { self.nDestZ = value; });
    internal_message_g2m_query_scene_type["nFaceDirection"] = sol::property([](const InternalMessage::G2M_QUERY_SCENE& self) { return self.nFaceDirection; }, [](InternalMessage::G2M_QUERY_SCENE& self, decltype(InternalMessage::G2M_QUERY_SCENE::nFaceDirection) value) { self.nFaceDirection = value; });
}

}
