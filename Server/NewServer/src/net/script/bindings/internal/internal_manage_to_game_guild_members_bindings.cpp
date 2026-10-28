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

void register_internal_manage_to_game_guild_members_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_guild_add_member_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_ADD_MEMBER_NTF>(L, internal_message_namespace, "M2G_GUILD_ADD_MEMBER_NTF", "InternalMessage::M2G_GUILD_ADD_MEMBER_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_add_member_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_ADD_MEMBER_NTF(); });
    internal_message_m2g_guild_add_member_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_ADD_MEMBER_NTF>(new InternalMessage::M2G_GUILD_ADD_MEMBER_NTF()); });
    internal_message_m2g_guild_add_member_ntf_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_GUILD_ADD_MEMBER_NTF& self) { return self.dwRoleID; }, [](InternalMessage::M2G_GUILD_ADD_MEMBER_NTF& self, decltype(InternalMessage::M2G_GUILD_ADD_MEMBER_NTF::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_guild_add_member_ntf_type["byPosition"] = sol::property([](const InternalMessage::M2G_GUILD_ADD_MEMBER_NTF& self) { return self.byPosition; }, [](InternalMessage::M2G_GUILD_ADD_MEMBER_NTF& self, decltype(InternalMessage::M2G_GUILD_ADD_MEMBER_NTF::byPosition) value) { self.byPosition = value; });
    internal_message_m2g_guild_add_member_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_ADD_MEMBER_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_ADD_MEMBER_NTF& self, decltype(InternalMessage::M2G_GUILD_ADD_MEMBER_NTF::dwGuildID) value) { self.dwGuildID = value; });
    auto internal_message_m2g_guild_del_member_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_DEL_MEMBER_NTF>(L, internal_message_namespace, "M2G_GUILD_DEL_MEMBER_NTF", "InternalMessage::M2G_GUILD_DEL_MEMBER_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_del_member_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_DEL_MEMBER_NTF(); });
    internal_message_m2g_guild_del_member_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_DEL_MEMBER_NTF>(new InternalMessage::M2G_GUILD_DEL_MEMBER_NTF()); });
    internal_message_m2g_guild_del_member_ntf_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_GUILD_DEL_MEMBER_NTF& self) { return self.dwRoleID; }, [](InternalMessage::M2G_GUILD_DEL_MEMBER_NTF& self, decltype(InternalMessage::M2G_GUILD_DEL_MEMBER_NTF::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_guild_del_member_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_DEL_MEMBER_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_DEL_MEMBER_NTF& self, decltype(InternalMessage::M2G_GUILD_DEL_MEMBER_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_del_member_ntf_type["dwCD"] = sol::property([](const InternalMessage::M2G_GUILD_DEL_MEMBER_NTF& self) { return self.dwCD; }, [](InternalMessage::M2G_GUILD_DEL_MEMBER_NTF& self, decltype(InternalMessage::M2G_GUILD_DEL_MEMBER_NTF::dwCD) value) { self.dwCD = value; });
    auto internal_message_guild_member_info_type = cqyh::lua::usertype<InternalMessage::GUILD_MEMBER_INFO>(L, internal_message_namespace, "GUILD_MEMBER_INFO", "InternalMessage::GUILD_MEMBER_INFO");
    internal_message_guild_member_info_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GUILD_MEMBER_INFO(); });
    internal_message_guild_member_info_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GUILD_MEMBER_INFO>(new InternalMessage::GUILD_MEMBER_INFO()); });
    internal_message_guild_member_info_type["dwRoleID"] = sol::property([](const InternalMessage::GUILD_MEMBER_INFO& self) { return self.dwRoleID; }, [](InternalMessage::GUILD_MEMBER_INFO& self, decltype(InternalMessage::GUILD_MEMBER_INFO::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_guild_member_info_type["byPosition"] = sol::property([](const InternalMessage::GUILD_MEMBER_INFO& self) { return self.byPosition; }, [](InternalMessage::GUILD_MEMBER_INFO& self, decltype(InternalMessage::GUILD_MEMBER_INFO::byPosition) value) { self.byPosition = value; });
    auto internal_message_m2g_guild_draw_salary_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_DRAW_SALARY>(L, internal_message_namespace, "M2G_GUILD_DRAW_SALARY", "InternalMessage::M2G_GUILD_DRAW_SALARY", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_draw_salary_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_DRAW_SALARY(); });
    internal_message_m2g_guild_draw_salary_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_DRAW_SALARY>(new InternalMessage::M2G_GUILD_DRAW_SALARY()); });
    internal_message_m2g_guild_draw_salary_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_GUILD_DRAW_SALARY& self) { return self.dwRoleID; }, [](InternalMessage::M2G_GUILD_DRAW_SALARY& self, decltype(InternalMessage::M2G_GUILD_DRAW_SALARY::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_guild_draw_salary_type["nSalary"] = sol::property([](const InternalMessage::M2G_GUILD_DRAW_SALARY& self) { return self.nSalary; }, [](InternalMessage::M2G_GUILD_DRAW_SALARY& self, decltype(InternalMessage::M2G_GUILD_DRAW_SALARY::nSalary) value) { self.nSalary = value; });
    auto internal_message_m2g_guild_change_position_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF>(L, internal_message_namespace, "M2G_GUILD_CHANGE_POSITION_NTF", "InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_change_position_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF(); });
    internal_message_m2g_guild_change_position_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF>(new InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF()); });
    internal_message_m2g_guild_change_position_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF& self, decltype(InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_change_position_ntf_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF& self) { return self.dwRoleID; }, [](InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF& self, decltype(InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_guild_change_position_ntf_type["nPosition"] = sol::property([](const InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF& self) { return self.nPosition; }, [](InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF& self, decltype(InternalMessage::M2G_GUILD_CHANGE_POSITION_NTF::nPosition) value) { self.nPosition = value; });
    auto internal_message_m2g_guild_sync_member_salary_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF>(L, internal_message_namespace, "M2G_GUILD_SYNC_MEMBER_SALARY_NTF", "InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_sync_member_salary_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF(); });
    internal_message_m2g_guild_sync_member_salary_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF>(new InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF()); });
    internal_message_m2g_guild_sync_member_salary_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF& self, decltype(InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_sync_member_salary_ntf_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF& self) { return self.dwRoleID; }, [](InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF& self, decltype(InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_guild_sync_member_salary_ntf_type["nSalary"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF& self) { return self.nSalary; }, [](InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF& self, decltype(InternalMessage::M2G_GUILD_SYNC_MEMBER_SALARY_NTF::nSalary) value) { self.nSalary = value; });
}

}
