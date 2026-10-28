#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmsvr_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_gm_server_connection_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2gm_register_type = cqyh::lua::usertype<InternalMessage::M2GM_REGISTER>(L, internal_message_namespace, "M2GM_REGISTER", "InternalMessage::M2GM_REGISTER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2gm_register_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2GM_REGISTER(); });
    internal_message_m2gm_register_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2GM_REGISTER>(new InternalMessage::M2GM_REGISTER()); });
    internal_message_m2gm_register_type["szName"] = cqyh::lua::string_property(&InternalMessage::M2GM_REGISTER::szName);
    auto internal_message_gm2_m_register_ack_type = cqyh::lua::usertype<InternalMessage::GM2M_REGISTER_ACK>(L, internal_message_namespace, "GM2M_REGISTER_ACK", "InternalMessage::GM2M_REGISTER_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_m_register_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2M_REGISTER_ACK(); });
    internal_message_gm2_m_register_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2M_REGISTER_ACK>(new InternalMessage::GM2M_REGISTER_ACK()); });
}

}
