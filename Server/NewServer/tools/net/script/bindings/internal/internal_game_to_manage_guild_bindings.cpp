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

void register_internal_game_to_manage_guild_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_guild_create_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_CREATE>(L, internal_message_namespace, "G2M_GUILD_CREATE", "InternalMessage::G2M_GUILD_CREATE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_create_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_CREATE(); });
    internal_message_g2m_guild_create_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_CREATE>(new InternalMessage::G2M_GUILD_CREATE()); });
    internal_message_g2m_guild_create_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_CREATE& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_CREATE& self, decltype(InternalMessage::G2M_GUILD_CREATE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_guild_create_type["szGuildName"] = cqyh::lua::string_property(&InternalMessage::G2M_GUILD_CREATE::szGuildName);
    internal_message_g2m_guild_create_type["szAnnounce"] = cqyh::lua::string_property(&InternalMessage::G2M_GUILD_CREATE::szAnnounce);
    auto internal_message_g2m_pre_create_guild_ack_type = cqyh::lua::usertype<InternalMessage::G2M_PRE_CREATE_GUILD_ACK>(L, internal_message_namespace, "G2M_PRE_CREATE_GUILD_ACK", "InternalMessage::G2M_PRE_CREATE_GUILD_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_pre_create_guild_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_PRE_CREATE_GUILD_ACK(); });
    internal_message_g2m_pre_create_guild_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_PRE_CREATE_GUILD_ACK>(new InternalMessage::G2M_PRE_CREATE_GUILD_ACK()); });
    internal_message_g2m_pre_create_guild_ack_type["nResult"] = sol::property([](const InternalMessage::G2M_PRE_CREATE_GUILD_ACK& self) { return self.nResult; }, [](InternalMessage::G2M_PRE_CREATE_GUILD_ACK& self, decltype(InternalMessage::G2M_PRE_CREATE_GUILD_ACK::nResult) value) { self.nResult = value; });
    internal_message_g2m_pre_create_guild_ack_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_PRE_CREATE_GUILD_ACK& self) { return self.dwRoleID; }, [](InternalMessage::G2M_PRE_CREATE_GUILD_ACK& self, decltype(InternalMessage::G2M_PRE_CREATE_GUILD_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_pre_create_guild_ack_type["szName"] = cqyh::lua::string_property(&InternalMessage::G2M_PRE_CREATE_GUILD_ACK::szName);
    auto internal_message_g2m_guild_contribute_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_CONTRIBUTE>(L, internal_message_namespace, "G2M_GUILD_CONTRIBUTE", "InternalMessage::G2M_GUILD_CONTRIBUTE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_contribute_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_CONTRIBUTE(); });
    internal_message_g2m_guild_contribute_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_CONTRIBUTE>(new InternalMessage::G2M_GUILD_CONTRIBUTE()); });
    internal_message_g2m_guild_contribute_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_CONTRIBUTE& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_CONTRIBUTE& self, decltype(InternalMessage::G2M_GUILD_CONTRIBUTE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_guild_contribute_type["nType"] = sol::property([](const InternalMessage::G2M_GUILD_CONTRIBUTE& self) { return self.nType; }, [](InternalMessage::G2M_GUILD_CONTRIBUTE& self, decltype(InternalMessage::G2M_GUILD_CONTRIBUTE::nType) value) { self.nType = value; });
    internal_message_g2m_guild_contribute_type["nMoney"] = sol::property([](const InternalMessage::G2M_GUILD_CONTRIBUTE& self) { return self.nMoney; }, [](InternalMessage::G2M_GUILD_CONTRIBUTE& self, decltype(InternalMessage::G2M_GUILD_CONTRIBUTE::nMoney) value) { self.nMoney = value; });
    auto internal_message_g2m_guild_change_res_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_CHANGE_RES>(L, internal_message_namespace, "G2M_GUILD_CHANGE_RES", "InternalMessage::G2M_GUILD_CHANGE_RES", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_change_res_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_CHANGE_RES(); });
    internal_message_g2m_guild_change_res_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_CHANGE_RES>(new InternalMessage::G2M_GUILD_CHANGE_RES()); });
    internal_message_g2m_guild_change_res_type["dwNpcID"] = sol::property([](const InternalMessage::G2M_GUILD_CHANGE_RES& self) { return self.dwNpcID; }, [](InternalMessage::G2M_GUILD_CHANGE_RES& self, decltype(InternalMessage::G2M_GUILD_CHANGE_RES::dwNpcID) value) { self.dwNpcID = value; });
    internal_message_g2m_guild_change_res_type["dwGuildID"] = sol::property([](const InternalMessage::G2M_GUILD_CHANGE_RES& self) { return self.dwGuildID; }, [](InternalMessage::G2M_GUILD_CHANGE_RES& self, decltype(InternalMessage::G2M_GUILD_CHANGE_RES::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_g2m_guild_change_res_type["nResourceType"] = sol::property([](const InternalMessage::G2M_GUILD_CHANGE_RES& self) { return self.nResourceType; }, [](InternalMessage::G2M_GUILD_CHANGE_RES& self, decltype(InternalMessage::G2M_GUILD_CHANGE_RES::nResourceType) value) { self.nResourceType = value; });
    internal_message_g2m_guild_change_res_type["nChangeType"] = sol::property([](const InternalMessage::G2M_GUILD_CHANGE_RES& self) { return self.nChangeType; }, [](InternalMessage::G2M_GUILD_CHANGE_RES& self, decltype(InternalMessage::G2M_GUILD_CHANGE_RES::nChangeType) value) { self.nChangeType = value; });
    internal_message_g2m_guild_change_res_type["nCount"] = sol::property([](const InternalMessage::G2M_GUILD_CHANGE_RES& self) { return self.nCount; }, [](InternalMessage::G2M_GUILD_CHANGE_RES& self, decltype(InternalMessage::G2M_GUILD_CHANGE_RES::nCount) value) { self.nCount = value; });
    internal_message_g2m_guild_change_res_type["nReason"] = sol::property([](const InternalMessage::G2M_GUILD_CHANGE_RES& self) { return self.nReason; }, [](InternalMessage::G2M_GUILD_CHANGE_RES& self, decltype(InternalMessage::G2M_GUILD_CHANGE_RES::nReason) value) { self.nReason = value; });
    internal_message_g2m_guild_change_res_type["byCtxType"] = sol::property([](const InternalMessage::G2M_GUILD_CHANGE_RES& self) { return self.byCtxType; }, [](InternalMessage::G2M_GUILD_CHANGE_RES& self, decltype(InternalMessage::G2M_GUILD_CHANGE_RES::byCtxType) value) { self.byCtxType = value; });
}

}
