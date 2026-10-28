#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/t2d_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_gate_to_database_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["t2d_begin"] = static_cast<lua_Number>(InternalMessage::t2d_begin);
    internal_message_namespace["t2d_register"] = static_cast<lua_Number>(InternalMessage::t2d_register);
    internal_message_namespace["t2d_query_role_list"] = static_cast<lua_Number>(InternalMessage::t2d_query_role_list);
    internal_message_namespace["t2d_create_role"] = static_cast<lua_Number>(InternalMessage::t2d_create_role);
    internal_message_namespace["t2d_delete_role"] = static_cast<lua_Number>(InternalMessage::t2d_delete_role);
    internal_message_namespace["t2d_undelete_role"] = static_cast<lua_Number>(InternalMessage::t2d_undelete_role);
    internal_message_namespace["t2d_forever_delete_role"] = static_cast<lua_Number>(InternalMessage::t2d_forever_delete_role);
    internal_message_namespace["t2d_end"] = static_cast<lua_Number>(InternalMessage::t2d_end);
    auto internal_message_t2d_register_type = cqyh::lua::usertype<InternalMessage::T2D_REGISTER>(L, internal_message_namespace, "T2D_REGISTER", "InternalMessage::T2D_REGISTER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2d_register_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2D_REGISTER(); });
    internal_message_t2d_register_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2D_REGISTER>(new InternalMessage::T2D_REGISTER()); });
    internal_message_t2d_register_type["dwGTSessionID"] = sol::property([](const InternalMessage::T2D_REGISTER& self) { return self.dwGTSessionID; }, [](InternalMessage::T2D_REGISTER& self, decltype(InternalMessage::T2D_REGISTER::dwGTSessionID) value) { self.dwGTSessionID = value; });
    auto internal_message_t2d_query_role_list_type = cqyh::lua::usertype<InternalMessage::T2D_QUERY_ROLE_LIST>(L, internal_message_namespace, "T2D_QUERY_ROLE_LIST", "InternalMessage::T2D_QUERY_ROLE_LIST", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2d_query_role_list_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2D_QUERY_ROLE_LIST(); });
    internal_message_t2d_query_role_list_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2D_QUERY_ROLE_LIST>(new InternalMessage::T2D_QUERY_ROLE_LIST()); });
    internal_message_t2d_query_role_list_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2D_QUERY_ROLE_LIST& self) { return self.dwClientSessionID; }, [](InternalMessage::T2D_QUERY_ROLE_LIST& self, decltype(InternalMessage::T2D_QUERY_ROLE_LIST::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_t2d_query_role_list_type["byServerGroup"] = sol::property([](const InternalMessage::T2D_QUERY_ROLE_LIST& self) { return self.byServerGroup; }, [](InternalMessage::T2D_QUERY_ROLE_LIST& self, decltype(InternalMessage::T2D_QUERY_ROLE_LIST::byServerGroup) value) { self.byServerGroup = value; });
    internal_message_t2d_query_role_list_type["szUserName"] = cqyh::lua::string_property(&InternalMessage::T2D_QUERY_ROLE_LIST::szUserName);
    auto internal_message_t2d_create_role_type = cqyh::lua::usertype<InternalMessage::T2D_CREATE_ROLE>(L, internal_message_namespace, "T2D_CREATE_ROLE", "InternalMessage::T2D_CREATE_ROLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2d_create_role_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2D_CREATE_ROLE(); });
    internal_message_t2d_create_role_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2D_CREATE_ROLE>(new InternalMessage::T2D_CREATE_ROLE()); });
    internal_message_t2d_create_role_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2D_CREATE_ROLE& self) { return self.dwClientSessionID; }, [](InternalMessage::T2D_CREATE_ROLE& self, decltype(InternalMessage::T2D_CREATE_ROLE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_t2d_create_role_type["dwRoleID"] = sol::property([](const InternalMessage::T2D_CREATE_ROLE& self) { return self.dwRoleID; }, [](InternalMessage::T2D_CREATE_ROLE& self, decltype(InternalMessage::T2D_CREATE_ROLE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_t2d_create_role_type["szRoleName"] = cqyh::lua::string_property(&InternalMessage::T2D_CREATE_ROLE::szRoleName);
    internal_message_t2d_create_role_type["byClass"] = sol::property([](const InternalMessage::T2D_CREATE_ROLE& self) { return self.byClass; }, [](InternalMessage::T2D_CREATE_ROLE& self, decltype(InternalMessage::T2D_CREATE_ROLE::byClass) value) { self.byClass = value; });
    internal_message_t2d_create_role_type["bySex"] = sol::property([](const InternalMessage::T2D_CREATE_ROLE& self) { return self.bySex; }, [](InternalMessage::T2D_CREATE_ROLE& self, decltype(InternalMessage::T2D_CREATE_ROLE::bySex) value) { self.bySex = value; });
    internal_message_t2d_create_role_type["byHairType"] = sol::property([](const InternalMessage::T2D_CREATE_ROLE& self) { return self.byHairType; }, [](InternalMessage::T2D_CREATE_ROLE& self, decltype(InternalMessage::T2D_CREATE_ROLE::byHairType) value) { self.byHairType = value; });
    internal_message_t2d_create_role_type["byHairColor"] = sol::property([](const InternalMessage::T2D_CREATE_ROLE& self) { return self.byHairColor; }, [](InternalMessage::T2D_CREATE_ROLE& self, decltype(InternalMessage::T2D_CREATE_ROLE::byHairColor) value) { self.byHairColor = value; });
    internal_message_t2d_create_role_type["byFaceType"] = sol::property([](const InternalMessage::T2D_CREATE_ROLE& self) { return self.byFaceType; }, [](InternalMessage::T2D_CREATE_ROLE& self, decltype(InternalMessage::T2D_CREATE_ROLE::byFaceType) value) { self.byFaceType = value; });
    internal_message_t2d_create_role_type["bySkinColor"] = sol::property([](const InternalMessage::T2D_CREATE_ROLE& self) { return self.bySkinColor; }, [](InternalMessage::T2D_CREATE_ROLE& self, decltype(InternalMessage::T2D_CREATE_ROLE::bySkinColor) value) { self.bySkinColor = value; });
    auto internal_message_t2d_delete_role_type = cqyh::lua::usertype<InternalMessage::T2D_DELETE_ROLE>(L, internal_message_namespace, "T2D_DELETE_ROLE", "InternalMessage::T2D_DELETE_ROLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2d_delete_role_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2D_DELETE_ROLE(); });
    internal_message_t2d_delete_role_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2D_DELETE_ROLE>(new InternalMessage::T2D_DELETE_ROLE()); });
    internal_message_t2d_delete_role_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2D_DELETE_ROLE& self) { return self.dwClientSessionID; }, [](InternalMessage::T2D_DELETE_ROLE& self, decltype(InternalMessage::T2D_DELETE_ROLE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_t2d_delete_role_type["dwRoleID"] = sol::property([](const InternalMessage::T2D_DELETE_ROLE& self) { return self.dwRoleID; }, [](InternalMessage::T2D_DELETE_ROLE& self, decltype(InternalMessage::T2D_DELETE_ROLE::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_t2d_undelete_role_type = cqyh::lua::usertype<InternalMessage::T2D_UNDELETE_ROLE>(L, internal_message_namespace, "T2D_UNDELETE_ROLE", "InternalMessage::T2D_UNDELETE_ROLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2d_undelete_role_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2D_UNDELETE_ROLE(); });
    internal_message_t2d_undelete_role_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2D_UNDELETE_ROLE>(new InternalMessage::T2D_UNDELETE_ROLE()); });
    internal_message_t2d_undelete_role_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2D_UNDELETE_ROLE& self) { return self.dwClientSessionID; }, [](InternalMessage::T2D_UNDELETE_ROLE& self, decltype(InternalMessage::T2D_UNDELETE_ROLE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_t2d_undelete_role_type["dwRoleID"] = sol::property([](const InternalMessage::T2D_UNDELETE_ROLE& self) { return self.dwRoleID; }, [](InternalMessage::T2D_UNDELETE_ROLE& self, decltype(InternalMessage::T2D_UNDELETE_ROLE::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_t2d_forever_delete_role_type = cqyh::lua::usertype<InternalMessage::T2D_FOREVER_DELETE_ROLE>(L, internal_message_namespace, "T2D_FOREVER_DELETE_ROLE", "InternalMessage::T2D_FOREVER_DELETE_ROLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2d_forever_delete_role_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2D_FOREVER_DELETE_ROLE(); });
    internal_message_t2d_forever_delete_role_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2D_FOREVER_DELETE_ROLE>(new InternalMessage::T2D_FOREVER_DELETE_ROLE()); });
    internal_message_t2d_forever_delete_role_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2D_FOREVER_DELETE_ROLE& self) { return self.dwClientSessionID; }, [](InternalMessage::T2D_FOREVER_DELETE_ROLE& self, decltype(InternalMessage::T2D_FOREVER_DELETE_ROLE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_t2d_forever_delete_role_type["dwRoleID"] = sol::property([](const InternalMessage::T2D_FOREVER_DELETE_ROLE& self) { return self.dwRoleID; }, [](InternalMessage::T2D_FOREVER_DELETE_ROLE& self, decltype(InternalMessage::T2D_FOREVER_DELETE_ROLE::dwRoleID) value) { self.dwRoleID = value; });
}

}
