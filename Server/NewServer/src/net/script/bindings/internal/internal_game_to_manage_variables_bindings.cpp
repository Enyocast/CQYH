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

void register_internal_game_to_manage_variables_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_set_server_variable_type = cqyh::lua::usertype<InternalMessage::G2M_SET_SERVER_VARIABLE>(L, internal_message_namespace, "G2M_SET_SERVER_VARIABLE", "InternalMessage::G2M_SET_SERVER_VARIABLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_set_server_variable_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_SET_SERVER_VARIABLE(); });
    internal_message_g2m_set_server_variable_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_SET_SERVER_VARIABLE>(new InternalMessage::G2M_SET_SERVER_VARIABLE()); });
    internal_message_g2m_set_server_variable_type["byServerGroup"] = sol::property([](const InternalMessage::G2M_SET_SERVER_VARIABLE& self) { return self.byServerGroup; }, [](InternalMessage::G2M_SET_SERVER_VARIABLE& self, decltype(InternalMessage::G2M_SET_SERVER_VARIABLE::byServerGroup) value) { self.byServerGroup = value; });
    internal_message_g2m_set_server_variable_type["qwKey"] = sol::property([](const InternalMessage::G2M_SET_SERVER_VARIABLE& self) { return self.qwKey; }, [](InternalMessage::G2M_SET_SERVER_VARIABLE& self, decltype(InternalMessage::G2M_SET_SERVER_VARIABLE::qwKey) value) { self.qwKey = value; });
    internal_message_g2m_set_server_variable_type["bAbsoluteValue"] = sol::property([](const InternalMessage::G2M_SET_SERVER_VARIABLE& self) { return self.bAbsoluteValue; }, [](InternalMessage::G2M_SET_SERVER_VARIABLE& self, decltype(InternalMessage::G2M_SET_SERVER_VARIABLE::bAbsoluteValue) value) { self.bAbsoluteValue = value; });
    internal_message_g2m_set_server_variable_type["nVarValue"] = sol::property([](const InternalMessage::G2M_SET_SERVER_VARIABLE& self) { return self.nVarValue; }, [](InternalMessage::G2M_SET_SERVER_VARIABLE& self, decltype(InternalMessage::G2M_SET_SERVER_VARIABLE::nVarValue) value) { self.nVarValue = value; });
}

}
