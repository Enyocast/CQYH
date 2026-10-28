#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/t2m_message.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gate_to_manage_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["t2m_begin"] = static_cast<lua_Number>(InternalMessage::t2m_begin);
    internal_message_namespace["t2m_register"] = static_cast<lua_Number>(InternalMessage::t2m_register);
    internal_message_namespace["t2m_ready"] = static_cast<lua_Number>(InternalMessage::t2m_ready);
    internal_message_namespace["t2m_close_ack"] = static_cast<lua_Number>(InternalMessage::t2m_close_ack);
    internal_message_namespace["t2m_client_shutdown"] = static_cast<lua_Number>(InternalMessage::t2m_client_shutdown);
    internal_message_namespace["t2m_enter_gate"] = static_cast<lua_Number>(InternalMessage::t2m_enter_gate);
    internal_message_namespace["t2m_query_scene"] = static_cast<lua_Number>(InternalMessage::t2m_query_scene);
    internal_message_namespace["t2m_return_select_role"] = static_cast<lua_Number>(InternalMessage::t2m_return_select_role);
    internal_message_namespace["t2m_change_gs_ack"] = static_cast<lua_Number>(InternalMessage::t2m_change_gs_ack);
    internal_message_namespace["t2m_check_new_name"] = static_cast<lua_Number>(InternalMessage::t2m_check_new_name);
    internal_message_namespace["t2m_client_msg"] = static_cast<lua_Number>(InternalMessage::t2m_client_msg);
    internal_message_namespace["t2m_end"] = static_cast<lua_Number>(InternalMessage::t2m_end);
    auto internal_message_t2m_register_type = cqyh::lua::usertype<InternalMessage::T2M_REGISTER>(L, internal_message_namespace, "T2M_REGISTER", "InternalMessage::T2M_REGISTER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2m_register_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2M_REGISTER(); });
    internal_message_t2m_register_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2M_REGISTER>(new InternalMessage::T2M_REGISTER()); });
    internal_message_t2m_register_type["dwInternalAddr"] = sol::property([](const InternalMessage::T2M_REGISTER& self) { return self.dwInternalAddr; }, [](InternalMessage::T2M_REGISTER& self, decltype(InternalMessage::T2M_REGISTER::dwInternalAddr) value) { self.dwInternalAddr = value; });
    internal_message_t2m_register_type["wInternalPort"] = sol::property([](const InternalMessage::T2M_REGISTER& self) { return self.wInternalPort; }, [](InternalMessage::T2M_REGISTER& self, decltype(InternalMessage::T2M_REGISTER::wInternalPort) value) { self.wInternalPort = value; });
    internal_message_t2m_register_type["byExternalCount"] = sol::property([](const InternalMessage::T2M_REGISTER& self) { return self.byExternalCount; }, [](InternalMessage::T2M_REGISTER& self, decltype(InternalMessage::T2M_REGISTER::byExternalCount) value) { self.byExternalCount = value; });
    internal_message_t2m_register_type["dwExternalAddr"] = cqyh::lua::array_property(&InternalMessage::T2M_REGISTER::dwExternalAddr);
    internal_message_t2m_register_type["wExternalPort"] = cqyh::lua::array_property(&InternalMessage::T2M_REGISTER::wExternalPort);
    auto internal_message_t2m_ready_type = cqyh::lua::usertype<InternalMessage::T2M_READY>(L, internal_message_namespace, "T2M_READY", "InternalMessage::T2M_READY", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2m_ready_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2M_READY(); });
    internal_message_t2m_ready_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2M_READY>(new InternalMessage::T2M_READY()); });
    auto internal_message_t2m_close_ack_type = cqyh::lua::usertype<InternalMessage::T2M_CLOSE_ACK>(L, internal_message_namespace, "T2M_CLOSE_ACK", "InternalMessage::T2M_CLOSE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2m_close_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2M_CLOSE_ACK(); });
    internal_message_t2m_close_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2M_CLOSE_ACK>(new InternalMessage::T2M_CLOSE_ACK()); });
    auto internal_message_t2m_enter_gate_type = cqyh::lua::usertype<InternalMessage::T2M_ENTER_GATE>(L, internal_message_namespace, "T2M_ENTER_GATE", "InternalMessage::T2M_ENTER_GATE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2m_enter_gate_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2M_ENTER_GATE(); });
    internal_message_t2m_enter_gate_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2M_ENTER_GATE>(new InternalMessage::T2M_ENTER_GATE()); });
    internal_message_t2m_enter_gate_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2M_ENTER_GATE& self) { return self.dwClientSessionID; }, [](InternalMessage::T2M_ENTER_GATE& self, decltype(InternalMessage::T2M_ENTER_GATE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_t2m_enter_gate_type["dwIpAddr"] = sol::property([](const InternalMessage::T2M_ENTER_GATE& self) { return self.dwIpAddr; }, [](InternalMessage::T2M_ENTER_GATE& self, decltype(InternalMessage::T2M_ENTER_GATE::dwIpAddr) value) { self.dwIpAddr = value; });
    internal_message_t2m_enter_gate_type["szMac"] = cqyh::lua::string_property(&InternalMessage::T2M_ENTER_GATE::szMac);
    internal_message_t2m_enter_gate_type["szOASessionID"] = cqyh::lua::string_property(&InternalMessage::T2M_ENTER_GATE::szOASessionID);
    internal_message_t2m_enter_gate_type["szUserName"] = cqyh::lua::string_property(&InternalMessage::T2M_ENTER_GATE::szUserName);
    internal_message_t2m_enter_gate_type["szPGT"] = cqyh::lua::string_property(&InternalMessage::T2M_ENTER_GATE::szPGT);
    internal_message_t2m_enter_gate_type["bAdult"] = sol::property([](const InternalMessage::T2M_ENTER_GATE& self) { return self.bAdult; }, [](InternalMessage::T2M_ENTER_GATE& self, decltype(InternalMessage::T2M_ENTER_GATE::bAdult) value) { self.bAdult = value; });
    internal_message_t2m_enter_gate_type["bIpWhiteList"] = sol::property([](const InternalMessage::T2M_ENTER_GATE& self) { return self.bIpWhiteList; }, [](InternalMessage::T2M_ENTER_GATE& self, decltype(InternalMessage::T2M_ENTER_GATE::bIpWhiteList) value) { self.bIpWhiteList = value; });
    internal_message_t2m_enter_gate_type["bUserWhiteList"] = sol::property([](const InternalMessage::T2M_ENTER_GATE& self) { return self.bUserWhiteList; }, [](InternalMessage::T2M_ENTER_GATE& self, decltype(InternalMessage::T2M_ENTER_GATE::bUserWhiteList) value) { self.bUserWhiteList = value; });
    auto internal_message_t2m_query_scene_type = cqyh::lua::usertype<InternalMessage::T2M_QUERY_SCENE>(L, internal_message_namespace, "T2M_QUERY_SCENE", "InternalMessage::T2M_QUERY_SCENE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2m_query_scene_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2M_QUERY_SCENE(); });
    internal_message_t2m_query_scene_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2M_QUERY_SCENE>(new InternalMessage::T2M_QUERY_SCENE()); });
    internal_message_t2m_query_scene_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.dwClientSessionID; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_t2m_query_scene_type["dwRoleID"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.dwRoleID; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_t2m_query_scene_type["dwSaveTime"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.dwSaveTime; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::dwSaveTime) value) { self.dwSaveTime = value; });
    internal_message_t2m_query_scene_type["nSceneTempID"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.nSceneTempID; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_t2m_query_scene_type["nSceneID"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.nSceneID; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::nSceneID) value) { self.nSceneID = value; });
    internal_message_t2m_query_scene_type["nX"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.nX; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::nX) value) { self.nX = value; });
    internal_message_t2m_query_scene_type["nY"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.nY; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::nY) value) { self.nY = value; });
    internal_message_t2m_query_scene_type["nZ"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.nZ; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::nZ) value) { self.nZ = value; });
    internal_message_t2m_query_scene_type["wFaceDirection"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.wFaceDirection; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::wFaceDirection) value) { self.wFaceDirection = value; });
    internal_message_t2m_query_scene_type["nReturnSceneTempID"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.nReturnSceneTempID; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::nReturnSceneTempID) value) { self.nReturnSceneTempID = value; });
    internal_message_t2m_query_scene_type["nReturnSceneID"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.nReturnSceneID; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::nReturnSceneID) value) { self.nReturnSceneID = value; });
    internal_message_t2m_query_scene_type["nReturnX"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.nReturnX; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::nReturnX) value) { self.nReturnX = value; });
    internal_message_t2m_query_scene_type["nReturnY"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.nReturnY; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::nReturnY) value) { self.nReturnY = value; });
    internal_message_t2m_query_scene_type["nReturnZ"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.nReturnZ; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::nReturnZ) value) { self.nReturnZ = value; });
    internal_message_t2m_query_scene_type["wReturnFaceDirection"] = sol::property([](const InternalMessage::T2M_QUERY_SCENE& self) { return self.wReturnFaceDirection; }, [](InternalMessage::T2M_QUERY_SCENE& self, decltype(InternalMessage::T2M_QUERY_SCENE::wReturnFaceDirection) value) { self.wReturnFaceDirection = value; });
    auto internal_message_t2m_client_shutdown_type = cqyh::lua::usertype<InternalMessage::T2M_CLIENT_SHUTDOWN>(L, internal_message_namespace, "T2M_CLIENT_SHUTDOWN", "InternalMessage::T2M_CLIENT_SHUTDOWN", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2m_client_shutdown_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2M_CLIENT_SHUTDOWN(); });
    internal_message_t2m_client_shutdown_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2M_CLIENT_SHUTDOWN>(new InternalMessage::T2M_CLIENT_SHUTDOWN()); });
    internal_message_t2m_client_shutdown_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2M_CLIENT_SHUTDOWN& self) { return self.dwClientSessionID; }, [](InternalMessage::T2M_CLIENT_SHUTDOWN& self, decltype(InternalMessage::T2M_CLIENT_SHUTDOWN::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_t2m_client_shutdown_type["byShutDownType"] = sol::property([](const InternalMessage::T2M_CLIENT_SHUTDOWN& self) { return self.byShutDownType; }, [](InternalMessage::T2M_CLIENT_SHUTDOWN& self, decltype(InternalMessage::T2M_CLIENT_SHUTDOWN::byShutDownType) value) { self.byShutDownType = value; });
    auto internal_message_t2m_return_select_role_type = cqyh::lua::usertype<InternalMessage::T2M_RETURN_SELECT_ROLE>(L, internal_message_namespace, "T2M_RETURN_SELECT_ROLE", "InternalMessage::T2M_RETURN_SELECT_ROLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2m_return_select_role_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2M_RETURN_SELECT_ROLE(); });
    internal_message_t2m_return_select_role_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2M_RETURN_SELECT_ROLE>(new InternalMessage::T2M_RETURN_SELECT_ROLE()); });
    internal_message_t2m_return_select_role_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2M_RETURN_SELECT_ROLE& self) { return self.dwClientSessionID; }, [](InternalMessage::T2M_RETURN_SELECT_ROLE& self, decltype(InternalMessage::T2M_RETURN_SELECT_ROLE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    auto internal_message_t2m_change_gs_ack_type = cqyh::lua::usertype<InternalMessage::T2M_CHANGE_GS_ACK>(L, internal_message_namespace, "T2M_CHANGE_GS_ACK", "InternalMessage::T2M_CHANGE_GS_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2m_change_gs_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2M_CHANGE_GS_ACK(); });
    internal_message_t2m_change_gs_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2M_CHANGE_GS_ACK>(new InternalMessage::T2M_CHANGE_GS_ACK()); });
    internal_message_t2m_change_gs_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2M_CHANGE_GS_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::T2M_CHANGE_GS_ACK& self, decltype(InternalMessage::T2M_CHANGE_GS_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    auto internal_message_t2m_check_new_name_type = cqyh::lua::usertype<InternalMessage::T2M_CHECK_NEW_NAME>(L, internal_message_namespace, "T2M_CHECK_NEW_NAME", "InternalMessage::T2M_CHECK_NEW_NAME", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2m_check_new_name_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2M_CHECK_NEW_NAME(); });
    internal_message_t2m_check_new_name_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2M_CHECK_NEW_NAME>(new InternalMessage::T2M_CHECK_NEW_NAME()); });
    internal_message_t2m_check_new_name_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2M_CHECK_NEW_NAME& self) { return self.dwClientSessionID; }, [](InternalMessage::T2M_CHECK_NEW_NAME& self, decltype(InternalMessage::T2M_CHECK_NEW_NAME::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_t2m_check_new_name_type["szName"] = cqyh::lua::string_property(&InternalMessage::T2M_CHECK_NEW_NAME::szName);
    internal_message_t2m_check_new_name_type["UserData"] = cqyh::lua::string_property(&InternalMessage::T2M_CHECK_NEW_NAME::UserData);
    auto internal_message_t2m_client_msg_type = cqyh::lua::usertype<InternalMessage::T2M_CLIENT_MSG>(L, internal_message_namespace, "T2M_CLIENT_MSG", "InternalMessage::T2M_CLIENT_MSG", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2m_client_msg_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2M_CLIENT_MSG(); });
    internal_message_t2m_client_msg_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2M_CLIENT_MSG>(new InternalMessage::T2M_CLIENT_MSG()); });
    internal_message_t2m_client_msg_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2M_CLIENT_MSG& self) { return self.dwClientSessionID; }, [](InternalMessage::T2M_CLIENT_MSG& self, decltype(InternalMessage::T2M_CLIENT_MSG::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_t2m_client_msg_type["szData"] = cqyh::lua::string_property(&InternalMessage::T2M_CLIENT_MSG::szData);
}

}
