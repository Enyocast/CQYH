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

void register_internal_manage_to_game_siege_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_enroll_sabac_type = cqyh::lua::usertype<InternalMessage::M2G_ENROLL_SABAC>(L, internal_message_namespace, "M2G_ENROLL_SABAC", "InternalMessage::M2G_ENROLL_SABAC", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_enroll_sabac_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_ENROLL_SABAC(); });
    internal_message_m2g_enroll_sabac_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_ENROLL_SABAC>(new InternalMessage::M2G_ENROLL_SABAC()); });
    internal_message_m2g_enroll_sabac_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_ENROLL_SABAC& self) { return self.dwGuildID; }, [](InternalMessage::M2G_ENROLL_SABAC& self, decltype(InternalMessage::M2G_ENROLL_SABAC::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_enroll_sabac_type["dwEnrollTime"] = sol::property([](const InternalMessage::M2G_ENROLL_SABAC& self) { return self.dwEnrollTime; }, [](InternalMessage::M2G_ENROLL_SABAC& self, decltype(InternalMessage::M2G_ENROLL_SABAC::dwEnrollTime) value) { self.dwEnrollTime = value; });
    auto internal_message_m2g_occupy_sabac_type = cqyh::lua::usertype<InternalMessage::M2G_OCCUPY_SABAC>(L, internal_message_namespace, "M2G_OCCUPY_SABAC", "InternalMessage::M2G_OCCUPY_SABAC", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_occupy_sabac_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_OCCUPY_SABAC(); });
    internal_message_m2g_occupy_sabac_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_OCCUPY_SABAC>(new InternalMessage::M2G_OCCUPY_SABAC()); });
    internal_message_m2g_occupy_sabac_type["dwOldGuildID"] = sol::property([](const InternalMessage::M2G_OCCUPY_SABAC& self) { return self.dwOldGuildID; }, [](InternalMessage::M2G_OCCUPY_SABAC& self, decltype(InternalMessage::M2G_OCCUPY_SABAC::dwOldGuildID) value) { self.dwOldGuildID = value; });
    internal_message_m2g_occupy_sabac_type["dwNewGuildID"] = sol::property([](const InternalMessage::M2G_OCCUPY_SABAC& self) { return self.dwNewGuildID; }, [](InternalMessage::M2G_OCCUPY_SABAC& self, decltype(InternalMessage::M2G_OCCUPY_SABAC::dwNewGuildID) value) { self.dwNewGuildID = value; });
}

}
