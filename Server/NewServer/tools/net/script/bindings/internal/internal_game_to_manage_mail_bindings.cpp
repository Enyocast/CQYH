#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/g2m_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_game_to_manage_mail_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_mail_cost_check_type = cqyh::lua::usertype<InternalMessage::G2M_MAIL_COST_CHECK>(L, internal_message_namespace, "G2M_MAIL_COST_CHECK", "InternalMessage::G2M_MAIL_COST_CHECK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_mail_cost_check_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_MAIL_COST_CHECK(); });
    internal_message_g2m_mail_cost_check_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_MAIL_COST_CHECK>(new InternalMessage::G2M_MAIL_COST_CHECK()); });
    internal_message_g2m_mail_cost_check_type["nResult"] = sol::property([](const InternalMessage::G2M_MAIL_COST_CHECK& self) { return self.nResult; }, [](InternalMessage::G2M_MAIL_COST_CHECK& self, decltype(InternalMessage::G2M_MAIL_COST_CHECK::nResult) value) { self.nResult = value; });
    internal_message_g2m_mail_cost_check_type["dwSenderRoleID"] = sol::property([](const InternalMessage::G2M_MAIL_COST_CHECK& self) { return self.dwSenderRoleID; }, [](InternalMessage::G2M_MAIL_COST_CHECK& self, decltype(InternalMessage::G2M_MAIL_COST_CHECK::dwSenderRoleID) value) { self.dwSenderRoleID = value; });
    internal_message_g2m_mail_cost_check_type["dwReceiverRoleID"] = sol::property([](const InternalMessage::G2M_MAIL_COST_CHECK& self) { return self.dwReceiverRoleID; }, [](InternalMessage::G2M_MAIL_COST_CHECK& self, decltype(InternalMessage::G2M_MAIL_COST_CHECK::dwReceiverRoleID) value) { self.dwReceiverRoleID = value; });
    internal_message_g2m_mail_cost_check_type["szMailSubject"] = cqyh::lua::string_property(&InternalMessage::G2M_MAIL_COST_CHECK::szMailSubject);
    internal_message_g2m_mail_cost_check_type["szMailContent"] = cqyh::lua::string_property(&InternalMessage::G2M_MAIL_COST_CHECK::szMailContent);
    auto internal_message_g2m_send_system_mail_type = cqyh::lua::usertype<InternalMessage::G2M_SEND_SYSTEM_MAIL>(L, internal_message_namespace, "G2M_SEND_SYSTEM_MAIL", "InternalMessage::G2M_SEND_SYSTEM_MAIL", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_send_system_mail_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_SEND_SYSTEM_MAIL(); });
    internal_message_g2m_send_system_mail_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_SEND_SYSTEM_MAIL>(new InternalMessage::G2M_SEND_SYSTEM_MAIL()); });
    internal_message_g2m_send_system_mail_type["dwReceiverRoleID"] = sol::property([](const InternalMessage::G2M_SEND_SYSTEM_MAIL& self) { return self.dwReceiverRoleID; }, [](InternalMessage::G2M_SEND_SYSTEM_MAIL& self, decltype(InternalMessage::G2M_SEND_SYSTEM_MAIL::dwReceiverRoleID) value) { self.dwReceiverRoleID = value; });
    internal_message_g2m_send_system_mail_type["szMailSubject"] = cqyh::lua::string_property(&InternalMessage::G2M_SEND_SYSTEM_MAIL::szMailSubject);
    internal_message_g2m_send_system_mail_type["szMailContent"] = cqyh::lua::string_property(&InternalMessage::G2M_SEND_SYSTEM_MAIL::szMailContent);
    auto internal_message_g2m_send_system_mail_with_simple_attach_type = cqyh::lua::usertype<InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH>(L, internal_message_namespace, "G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH", "InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_send_system_mail_with_simple_attach_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH(); });
    internal_message_g2m_send_system_mail_with_simple_attach_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH>(new InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH()); });
    internal_message_g2m_send_system_mail_with_simple_attach_type["dwReceiverRoleID"] = sol::property([](const InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH& self) { return self.dwReceiverRoleID; }, [](InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH& self, decltype(InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH::dwReceiverRoleID) value) { self.dwReceiverRoleID = value; });
    internal_message_g2m_send_system_mail_with_simple_attach_type["szMailSubject"] = cqyh::lua::string_property(&InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH::szMailSubject);
    internal_message_g2m_send_system_mail_with_simple_attach_type["szMailContent"] = cqyh::lua::string_property(&InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH::szMailContent);
    internal_message_g2m_send_system_mail_with_simple_attach_type["nItemID"] = sol::property([](const InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH& self) { return self.nItemID; }, [](InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH& self, decltype(InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH::nItemID) value) { self.nItemID = value; });
    internal_message_g2m_send_system_mail_with_simple_attach_type["nItemCount"] = sol::property([](const InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH& self) { return self.nItemCount; }, [](InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH& self, decltype(InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH::nItemCount) value) { self.nItemCount = value; });
    auto internal_message_g2m_send_system_mail_with_buffer_attach_type = cqyh::lua::usertype<InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH>(L, internal_message_namespace, "G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH", "InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_send_system_mail_with_buffer_attach_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH(); });
    internal_message_g2m_send_system_mail_with_buffer_attach_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH>(new InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH()); });
    internal_message_g2m_send_system_mail_with_buffer_attach_type["dwReceiverRoleID"] = sol::property([](const InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH& self) { return self.dwReceiverRoleID; }, [](InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH& self, decltype(InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH::dwReceiverRoleID) value) { self.dwReceiverRoleID = value; });
    internal_message_g2m_send_system_mail_with_buffer_attach_type["szMailSubject"] = cqyh::lua::string_property(&InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH::szMailSubject);
    internal_message_g2m_send_system_mail_with_buffer_attach_type["szMailContent"] = cqyh::lua::string_property(&InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH::szMailContent);
    internal_message_g2m_send_system_mail_with_buffer_attach_type["byBufferLen"] = sol::property([](const InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH& self) { return self.byBufferLen; }, [](InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH& self, decltype(InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH::byBufferLen) value) { self.byBufferLen = value; });
    internal_message_g2m_send_system_mail_with_buffer_attach_type["ItemBuffer"] = cqyh::lua::string_property(&InternalMessage::G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH::ItemBuffer);
    auto internal_message_g2m_mail_get_attach_type = cqyh::lua::usertype<InternalMessage::G2M_MAIL_GET_ATTACH>(L, internal_message_namespace, "G2M_MAIL_GET_ATTACH", "InternalMessage::G2M_MAIL_GET_ATTACH", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_mail_get_attach_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_MAIL_GET_ATTACH(); });
    internal_message_g2m_mail_get_attach_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_MAIL_GET_ATTACH>(new InternalMessage::G2M_MAIL_GET_ATTACH()); });
    internal_message_g2m_mail_get_attach_type["nResult"] = sol::property([](const InternalMessage::G2M_MAIL_GET_ATTACH& self) { return self.nResult; }, [](InternalMessage::G2M_MAIL_GET_ATTACH& self, decltype(InternalMessage::G2M_MAIL_GET_ATTACH::nResult) value) { self.nResult = value; });
    internal_message_g2m_mail_get_attach_type["dwMailID"] = sol::property([](const InternalMessage::G2M_MAIL_GET_ATTACH& self) { return self.dwMailID; }, [](InternalMessage::G2M_MAIL_GET_ATTACH& self, decltype(InternalMessage::G2M_MAIL_GET_ATTACH::dwMailID) value) { self.dwMailID = value; });
}

}
