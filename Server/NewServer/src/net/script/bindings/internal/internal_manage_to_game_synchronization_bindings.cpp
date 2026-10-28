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

void register_internal_manage_to_game_synchronization_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_sync_rsakey_type = cqyh::lua::usertype<InternalMessage::M2G_SYNC_RSAKEY>(L, internal_message_namespace, "M2G_SYNC_RSAKEY", "InternalMessage::M2G_SYNC_RSAKEY", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_sync_rsakey_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_SYNC_RSAKEY(); });
    internal_message_m2g_sync_rsakey_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_SYNC_RSAKEY>(new InternalMessage::M2G_SYNC_RSAKEY()); });
    internal_message_m2g_sync_rsakey_type["szData"] = cqyh::lua::string_property(&InternalMessage::M2G_SYNC_RSAKEY::szData);
    auto internal_message_m2g_sync_gm_data_type = cqyh::lua::usertype<InternalMessage::M2G_SYNC_GM_DATA>(L, internal_message_namespace, "M2G_SYNC_GM_DATA", "InternalMessage::M2G_SYNC_GM_DATA", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_sync_gm_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_SYNC_GM_DATA(); });
    internal_message_m2g_sync_gm_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_SYNC_GM_DATA>(new InternalMessage::M2G_SYNC_GM_DATA()); });
    internal_message_m2g_sync_gm_data_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_SYNC_GM_DATA& self) { return self.dwRoleID; }, [](InternalMessage::M2G_SYNC_GM_DATA& self, decltype(InternalMessage::M2G_SYNC_GM_DATA::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_sync_gm_data_type["dwForbidChatTime"] = sol::property([](const InternalMessage::M2G_SYNC_GM_DATA& self) { return self.dwForbidChatTime; }, [](InternalMessage::M2G_SYNC_GM_DATA& self, decltype(InternalMessage::M2G_SYNC_GM_DATA::dwForbidChatTime) value) { self.dwForbidChatTime = value; });
}

}
