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

void register_internal_manage_to_game_connection_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_register_ack_type = cqyh::lua::usertype<InternalMessage::M2G_REGISTER_ACK>(L, internal_message_namespace, "M2G_REGISTER_ACK", "InternalMessage::M2G_REGISTER_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_register_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_REGISTER_ACK(); });
    internal_message_m2g_register_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_REGISTER_ACK>(new InternalMessage::M2G_REGISTER_ACK()); });
    internal_message_m2g_register_ack_type["dwGSSessionID"] = sol::property([](const InternalMessage::M2G_REGISTER_ACK& self) { return self.dwGSSessionID; }, [](InternalMessage::M2G_REGISTER_ACK& self, decltype(InternalMessage::M2G_REGISTER_ACK::dwGSSessionID) value) { self.dwGSSessionID = value; });
}

}
