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

void register_internal_manage_to_game_mail_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_mail_cost_check_type = cqyh::lua::usertype<InternalMessage::M2G_MAIL_COST_CHECK>(L, internal_message_namespace, "M2G_MAIL_COST_CHECK", "InternalMessage::M2G_MAIL_COST_CHECK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_mail_cost_check_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_MAIL_COST_CHECK(); });
    internal_message_m2g_mail_cost_check_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_MAIL_COST_CHECK>(new InternalMessage::M2G_MAIL_COST_CHECK()); });
    internal_message_m2g_mail_cost_check_type["dwSenderRoleID"] = sol::property([](const InternalMessage::M2G_MAIL_COST_CHECK& self) { return self.dwSenderRoleID; }, [](InternalMessage::M2G_MAIL_COST_CHECK& self, decltype(InternalMessage::M2G_MAIL_COST_CHECK::dwSenderRoleID) value) { self.dwSenderRoleID = value; });
    internal_message_m2g_mail_cost_check_type["dwReceiverRoleID"] = sol::property([](const InternalMessage::M2G_MAIL_COST_CHECK& self) { return self.dwReceiverRoleID; }, [](InternalMessage::M2G_MAIL_COST_CHECK& self, decltype(InternalMessage::M2G_MAIL_COST_CHECK::dwReceiverRoleID) value) { self.dwReceiverRoleID = value; });
    internal_message_m2g_mail_cost_check_type["szMailSubject"] = cqyh::lua::string_property(&InternalMessage::M2G_MAIL_COST_CHECK::szMailSubject);
    internal_message_m2g_mail_cost_check_type["szMailContent"] = cqyh::lua::string_property(&InternalMessage::M2G_MAIL_COST_CHECK::szMailContent);
    auto internal_message_m2g_mail_get_simple_attach_type = cqyh::lua::usertype<InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH>(L, internal_message_namespace, "M2G_MAIL_GET_SIMPLE_ATTACH", "InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_mail_get_simple_attach_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH(); });
    internal_message_m2g_mail_get_simple_attach_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH>(new InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH()); });
    internal_message_m2g_mail_get_simple_attach_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH& self) { return self.dwRoleID; }, [](InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH& self, decltype(InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_mail_get_simple_attach_type["dwMailID"] = sol::property([](const InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH& self) { return self.dwMailID; }, [](InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH& self, decltype(InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH::dwMailID) value) { self.dwMailID = value; });
    internal_message_m2g_mail_get_simple_attach_type["nItemID"] = sol::property([](const InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH& self) { return self.nItemID; }, [](InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH& self, decltype(InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH::nItemID) value) { self.nItemID = value; });
    internal_message_m2g_mail_get_simple_attach_type["nItemCount"] = sol::property([](const InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH& self) { return self.nItemCount; }, [](InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH& self, decltype(InternalMessage::M2G_MAIL_GET_SIMPLE_ATTACH::nItemCount) value) { self.nItemCount = value; });
    auto internal_message_m2g_mail_get_buffer_attach_type = cqyh::lua::usertype<InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH>(L, internal_message_namespace, "M2G_MAIL_GET_BUFFER_ATTACH", "InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_mail_get_buffer_attach_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH(); });
    internal_message_m2g_mail_get_buffer_attach_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH>(new InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH()); });
    internal_message_m2g_mail_get_buffer_attach_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH& self) { return self.dwRoleID; }, [](InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH& self, decltype(InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_mail_get_buffer_attach_type["dwMailID"] = sol::property([](const InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH& self) { return self.dwMailID; }, [](InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH& self, decltype(InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH::dwMailID) value) { self.dwMailID = value; });
    internal_message_m2g_mail_get_buffer_attach_type["byBufferLen"] = sol::property([](const InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH& self) { return self.byBufferLen; }, [](InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH& self, decltype(InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH::byBufferLen) value) { self.byBufferLen = value; });
    internal_message_m2g_mail_get_buffer_attach_type["acBuffer"] = cqyh::lua::string_property(&InternalMessage::M2G_MAIL_GET_BUFFER_ATTACH::acBuffer);
}

}
