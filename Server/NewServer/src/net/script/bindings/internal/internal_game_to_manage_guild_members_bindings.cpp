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

void register_internal_game_to_manage_guild_members_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_guild_draw_salary_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_DRAW_SALARY>(L, internal_message_namespace, "G2M_GUILD_DRAW_SALARY", "InternalMessage::G2M_GUILD_DRAW_SALARY", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_draw_salary_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_DRAW_SALARY(); });
    internal_message_g2m_guild_draw_salary_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_DRAW_SALARY>(new InternalMessage::G2M_GUILD_DRAW_SALARY()); });
    internal_message_g2m_guild_draw_salary_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_DRAW_SALARY& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_DRAW_SALARY& self, decltype(InternalMessage::G2M_GUILD_DRAW_SALARY::dwRoleID) value) { self.dwRoleID = value; });
}

}
