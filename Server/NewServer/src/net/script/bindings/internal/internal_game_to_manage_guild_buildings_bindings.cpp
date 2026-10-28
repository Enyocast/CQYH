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

void register_internal_game_to_manage_guild_buildings_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_guild_create_building_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_CREATE_BUILDING>(L, internal_message_namespace, "G2M_GUILD_CREATE_BUILDING", "InternalMessage::G2M_GUILD_CREATE_BUILDING", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_create_building_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_CREATE_BUILDING(); });
    internal_message_g2m_guild_create_building_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_CREATE_BUILDING>(new InternalMessage::G2M_GUILD_CREATE_BUILDING()); });
    internal_message_g2m_guild_create_building_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_CREATE_BUILDING& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_CREATE_BUILDING& self, decltype(InternalMessage::G2M_GUILD_CREATE_BUILDING::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_guild_create_building_type["qwNpcNameID"] = sol::property([](const InternalMessage::G2M_GUILD_CREATE_BUILDING& self) { return self.qwNpcNameID; }, [](InternalMessage::G2M_GUILD_CREATE_BUILDING& self, decltype(InternalMessage::G2M_GUILD_CREATE_BUILDING::qwNpcNameID) value) { self.qwNpcNameID = value; });
    internal_message_g2m_guild_create_building_type["nType"] = sol::property([](const InternalMessage::G2M_GUILD_CREATE_BUILDING& self) { return self.nType; }, [](InternalMessage::G2M_GUILD_CREATE_BUILDING& self, decltype(InternalMessage::G2M_GUILD_CREATE_BUILDING::nType) value) { self.nType = value; });
    auto internal_message_g2m_guild_upgrade_building_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_UPGRADE_BUILDING>(L, internal_message_namespace, "G2M_GUILD_UPGRADE_BUILDING", "InternalMessage::G2M_GUILD_UPGRADE_BUILDING", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_upgrade_building_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_UPGRADE_BUILDING(); });
    internal_message_g2m_guild_upgrade_building_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_UPGRADE_BUILDING>(new InternalMessage::G2M_GUILD_UPGRADE_BUILDING()); });
    internal_message_g2m_guild_upgrade_building_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_UPGRADE_BUILDING& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_UPGRADE_BUILDING& self, decltype(InternalMessage::G2M_GUILD_UPGRADE_BUILDING::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_guild_upgrade_building_type["qwNpcNameID"] = sol::property([](const InternalMessage::G2M_GUILD_UPGRADE_BUILDING& self) { return self.qwNpcNameID; }, [](InternalMessage::G2M_GUILD_UPGRADE_BUILDING& self, decltype(InternalMessage::G2M_GUILD_UPGRADE_BUILDING::qwNpcNameID) value) { self.qwNpcNameID = value; });
    internal_message_g2m_guild_upgrade_building_type["nType"] = sol::property([](const InternalMessage::G2M_GUILD_UPGRADE_BUILDING& self) { return self.nType; }, [](InternalMessage::G2M_GUILD_UPGRADE_BUILDING& self, decltype(InternalMessage::G2M_GUILD_UPGRADE_BUILDING::nType) value) { self.nType = value; });
    auto internal_message_g2m_guild_del_building_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_DEL_BUILDING>(L, internal_message_namespace, "G2M_GUILD_DEL_BUILDING", "InternalMessage::G2M_GUILD_DEL_BUILDING", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_del_building_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_DEL_BUILDING(); });
    internal_message_g2m_guild_del_building_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_DEL_BUILDING>(new InternalMessage::G2M_GUILD_DEL_BUILDING()); });
    internal_message_g2m_guild_del_building_type["nType"] = sol::property([](const InternalMessage::G2M_GUILD_DEL_BUILDING& self) { return self.nType; }, [](InternalMessage::G2M_GUILD_DEL_BUILDING& self, decltype(InternalMessage::G2M_GUILD_DEL_BUILDING::nType) value) { self.nType = value; });
    internal_message_g2m_guild_del_building_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_DEL_BUILDING& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_DEL_BUILDING& self, decltype(InternalMessage::G2M_GUILD_DEL_BUILDING::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_guild_del_building_type["qwNameID"] = sol::property([](const InternalMessage::G2M_GUILD_DEL_BUILDING& self) { return self.qwNameID; }, [](InternalMessage::G2M_GUILD_DEL_BUILDING& self, decltype(InternalMessage::G2M_GUILD_DEL_BUILDING::qwNameID) value) { self.qwNameID = value; });
    auto internal_message_g2m_guild_change_building_state_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE>(L, internal_message_namespace, "G2M_GUILD_CHANGE_BUILDING_STATE", "InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_change_building_state_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE(); });
    internal_message_g2m_guild_change_building_state_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE>(new InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE()); });
    internal_message_g2m_guild_change_building_state_type["dwGuildID"] = sol::property([](const InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE& self) { return self.dwGuildID; }, [](InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE& self, decltype(InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_g2m_guild_change_building_state_type["qwNameID"] = sol::property([](const InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE& self) { return self.qwNameID; }, [](InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE& self, decltype(InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE::qwNameID) value) { self.qwNameID = value; });
    internal_message_g2m_guild_change_building_state_type["dwReviveTime"] = sol::property([](const InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE& self) { return self.dwReviveTime; }, [](InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE& self, decltype(InternalMessage::G2M_GUILD_CHANGE_BUILDING_STATE::dwReviveTime) value) { self.dwReviveTime = value; });
}

}
