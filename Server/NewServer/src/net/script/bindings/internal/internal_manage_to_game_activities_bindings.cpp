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

void register_internal_manage_to_game_activities_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_award_type = cqyh::lua::usertype<InternalMessage::M2G_AWARD>(L, internal_message_namespace, "M2G_AWARD", "InternalMessage::M2G_AWARD", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_award_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_AWARD(); });
    internal_message_m2g_award_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_AWARD>(new InternalMessage::M2G_AWARD()); });
    internal_message_m2g_award_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_AWARD& self) { return self.dwRoleID; }, [](InternalMessage::M2G_AWARD& self, decltype(InternalMessage::M2G_AWARD::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_award_type["nItemID"] = sol::property([](const InternalMessage::M2G_AWARD& self) { return self.nItemID; }, [](InternalMessage::M2G_AWARD& self, decltype(InternalMessage::M2G_AWARD::nItemID) value) { self.nItemID = value; });
    internal_message_m2g_award_type["nItemCount"] = sol::property([](const InternalMessage::M2G_AWARD& self) { return self.nItemCount; }, [](InternalMessage::M2G_AWARD& self, decltype(InternalMessage::M2G_AWARD::nItemCount) value) { self.nItemCount = value; });
}

}
