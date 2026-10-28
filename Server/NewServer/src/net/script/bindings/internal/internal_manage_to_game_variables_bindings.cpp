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

void register_internal_manage_to_game_variables_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_guild_sync_variable_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF>(L, internal_message_namespace, "M2G_GUILD_SYNC_VARIABLE_NTF", "InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_sync_variable_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF(); });
    internal_message_m2g_guild_sync_variable_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF>(new InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF()); });
    internal_message_m2g_guild_sync_variable_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF& self, decltype(InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_sync_variable_ntf_type["nIndex"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF& self) { return self.nIndex; }, [](InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF& self, decltype(InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF::nIndex) value) { self.nIndex = value; });
    internal_message_m2g_guild_sync_variable_ntf_type["nValue"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF& self) { return self.nValue; }, [](InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF& self, decltype(InternalMessage::M2G_GUILD_SYNC_VARIABLE_NTF::nValue) value) { self.nValue = value; });
    auto internal_message_m2g_sync_server_variable_type = cqyh::lua::usertype<InternalMessage::M2G_SYNC_SERVER_VARIABLE>(L, internal_message_namespace, "M2G_SYNC_SERVER_VARIABLE", "InternalMessage::M2G_SYNC_SERVER_VARIABLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_sync_server_variable_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_SYNC_SERVER_VARIABLE(); });
    internal_message_m2g_sync_server_variable_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_SYNC_SERVER_VARIABLE>(new InternalMessage::M2G_SYNC_SERVER_VARIABLE()); });
    internal_message_m2g_sync_server_variable_type["byServerGroup"] = sol::property([](const InternalMessage::M2G_SYNC_SERVER_VARIABLE& self) { return self.byServerGroup; }, [](InternalMessage::M2G_SYNC_SERVER_VARIABLE& self, decltype(InternalMessage::M2G_SYNC_SERVER_VARIABLE::byServerGroup) value) { self.byServerGroup = value; });
    internal_message_m2g_sync_server_variable_type["VarList"] = cqyh::lua::array_property(&InternalMessage::M2G_SYNC_SERVER_VARIABLE::VarList);
    auto internal_message_m2g_update_server_variable_type = cqyh::lua::usertype<InternalMessage::M2G_UPDATE_SERVER_VARIABLE>(L, internal_message_namespace, "M2G_UPDATE_SERVER_VARIABLE", "InternalMessage::M2G_UPDATE_SERVER_VARIABLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_update_server_variable_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_UPDATE_SERVER_VARIABLE(); });
    internal_message_m2g_update_server_variable_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_UPDATE_SERVER_VARIABLE>(new InternalMessage::M2G_UPDATE_SERVER_VARIABLE()); });
    internal_message_m2g_update_server_variable_type["byServerGroup"] = sol::property([](const InternalMessage::M2G_UPDATE_SERVER_VARIABLE& self) { return self.byServerGroup; }, [](InternalMessage::M2G_UPDATE_SERVER_VARIABLE& self, decltype(InternalMessage::M2G_UPDATE_SERVER_VARIABLE::byServerGroup) value) { self.byServerGroup = value; });
    internal_message_m2g_update_server_variable_type["qwKey"] = sol::property([](const InternalMessage::M2G_UPDATE_SERVER_VARIABLE& self) { return self.qwKey; }, [](InternalMessage::M2G_UPDATE_SERVER_VARIABLE& self, decltype(InternalMessage::M2G_UPDATE_SERVER_VARIABLE::qwKey) value) { self.qwKey = value; });
    internal_message_m2g_update_server_variable_type["nValue"] = sol::property([](const InternalMessage::M2G_UPDATE_SERVER_VARIABLE& self) { return self.nValue; }, [](InternalMessage::M2G_UPDATE_SERVER_VARIABLE& self, decltype(InternalMessage::M2G_UPDATE_SERVER_VARIABLE::nValue) value) { self.nValue = value; });
}

}
