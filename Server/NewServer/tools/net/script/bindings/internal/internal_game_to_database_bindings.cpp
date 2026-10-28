#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/g2d_message.h"

namespace cqyh::net_tools::bindings {

void register_internal_game_to_database_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["g2d_begin"] = static_cast<lua_Number>(InternalMessage::g2d_begin);
    internal_message_namespace["g2d_register"] = static_cast<lua_Number>(InternalMessage::g2d_register);
    internal_message_namespace["g2d_load_lock_role_data"] = static_cast<lua_Number>(InternalMessage::g2d_load_lock_role_data);
    internal_message_namespace["g2d_save_role_data"] = static_cast<lua_Number>(InternalMessage::g2d_save_role_data);
    internal_message_namespace["g2d_unlock_role_data"] = static_cast<lua_Number>(InternalMessage::g2d_unlock_role_data);
    internal_message_namespace["g2d_end"] = static_cast<lua_Number>(InternalMessage::g2d_end);
    auto internal_message_g2d_register_type = cqyh::lua::usertype<InternalMessage::G2D_REGISTER>(L, internal_message_namespace, "G2D_REGISTER", "InternalMessage::G2D_REGISTER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2d_register_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2D_REGISTER(); });
    internal_message_g2d_register_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2D_REGISTER>(new InternalMessage::G2D_REGISTER()); });
    internal_message_g2d_register_type["dwGSSessionID"] = sol::property([](const InternalMessage::G2D_REGISTER& self) { return self.dwGSSessionID; }, [](InternalMessage::G2D_REGISTER& self, decltype(InternalMessage::G2D_REGISTER::dwGSSessionID) value) { self.dwGSSessionID = value; });
    auto internal_message_g2d_load_lock_role_data_type = cqyh::lua::usertype<InternalMessage::G2D_LOAD_LOCK_ROLE_DATA>(L, internal_message_namespace, "G2D_LOAD_LOCK_ROLE_DATA", "InternalMessage::G2D_LOAD_LOCK_ROLE_DATA", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2d_load_lock_role_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2D_LOAD_LOCK_ROLE_DATA(); });
    internal_message_g2d_load_lock_role_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2D_LOAD_LOCK_ROLE_DATA>(new InternalMessage::G2D_LOAD_LOCK_ROLE_DATA()); });
    internal_message_g2d_load_lock_role_data_type["dwClientSessionID"] = sol::property([](const InternalMessage::G2D_LOAD_LOCK_ROLE_DATA& self) { return self.dwClientSessionID; }, [](InternalMessage::G2D_LOAD_LOCK_ROLE_DATA& self, decltype(InternalMessage::G2D_LOAD_LOCK_ROLE_DATA::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_g2d_load_lock_role_data_type["dwRoleID"] = sol::property([](const InternalMessage::G2D_LOAD_LOCK_ROLE_DATA& self) { return self.dwRoleID; }, [](InternalMessage::G2D_LOAD_LOCK_ROLE_DATA& self, decltype(InternalMessage::G2D_LOAD_LOCK_ROLE_DATA::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_g2d_save_role_data_type = cqyh::lua::usertype<InternalMessage::G2D_SAVE_ROLE_DATA>(L, internal_message_namespace, "G2D_SAVE_ROLE_DATA", "InternalMessage::G2D_SAVE_ROLE_DATA", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2d_save_role_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2D_SAVE_ROLE_DATA(); });
    internal_message_g2d_save_role_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2D_SAVE_ROLE_DATA>(new InternalMessage::G2D_SAVE_ROLE_DATA()); });
    internal_message_g2d_save_role_data_type["dwClientSessionID"] = sol::property([](const InternalMessage::G2D_SAVE_ROLE_DATA& self) { return self.dwClientSessionID; }, [](InternalMessage::G2D_SAVE_ROLE_DATA& self, decltype(InternalMessage::G2D_SAVE_ROLE_DATA::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_g2d_save_role_data_type["dwRoleID"] = sol::property([](const InternalMessage::G2D_SAVE_ROLE_DATA& self) { return self.dwRoleID; }, [](InternalMessage::G2D_SAVE_ROLE_DATA& self, decltype(InternalMessage::G2D_SAVE_ROLE_DATA::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2d_save_role_data_type["dwDataSize"] = sol::property([](const InternalMessage::G2D_SAVE_ROLE_DATA& self) { return self.dwDataSize; }, [](InternalMessage::G2D_SAVE_ROLE_DATA& self, decltype(InternalMessage::G2D_SAVE_ROLE_DATA::dwDataSize) value) { self.dwDataSize = value; });
    internal_message_g2d_save_role_data_type["RoleData"] = cqyh::lua::string_property(&InternalMessage::G2D_SAVE_ROLE_DATA::RoleData);
    auto internal_message_g2d_unlock_role_data_type = cqyh::lua::usertype<InternalMessage::G2D_UNLOCK_ROLE_DATA>(L, internal_message_namespace, "G2D_UNLOCK_ROLE_DATA", "InternalMessage::G2D_UNLOCK_ROLE_DATA", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2d_unlock_role_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2D_UNLOCK_ROLE_DATA(); });
    internal_message_g2d_unlock_role_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2D_UNLOCK_ROLE_DATA>(new InternalMessage::G2D_UNLOCK_ROLE_DATA()); });
    internal_message_g2d_unlock_role_data_type["dwClientSessionID"] = sol::property([](const InternalMessage::G2D_UNLOCK_ROLE_DATA& self) { return self.dwClientSessionID; }, [](InternalMessage::G2D_UNLOCK_ROLE_DATA& self, decltype(InternalMessage::G2D_UNLOCK_ROLE_DATA::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_g2d_unlock_role_data_type["dwRoleID"] = sol::property([](const InternalMessage::G2D_UNLOCK_ROLE_DATA& self) { return self.dwRoleID; }, [](InternalMessage::G2D_UNLOCK_ROLE_DATA& self, decltype(InternalMessage::G2D_UNLOCK_ROLE_DATA::dwRoleID) value) { self.dwRoleID = value; });
}

}
