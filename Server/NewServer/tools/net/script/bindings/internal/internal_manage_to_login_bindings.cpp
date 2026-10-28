#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/m2l_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_manage_to_login_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["m2l_begin"] = static_cast<lua_Number>(InternalMessage::m2l_begin);
    internal_message_namespace["m2l_register_ack"] = static_cast<lua_Number>(InternalMessage::m2l_register_ack);
    internal_message_namespace["m2l_end"] = static_cast<lua_Number>(InternalMessage::m2l_end);
    auto internal_message_m2l_register_ack_type = cqyh::lua::usertype<InternalMessage::M2L_REGISTER_ACK>(L, internal_message_namespace, "M2L_REGISTER_ACK", "InternalMessage::M2L_REGISTER_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2l_register_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2L_REGISTER_ACK(); });
    internal_message_m2l_register_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2L_REGISTER_ACK>(new InternalMessage::M2L_REGISTER_ACK()); });
}

}
