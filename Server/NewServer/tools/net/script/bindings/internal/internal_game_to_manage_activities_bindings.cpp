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

void register_internal_game_to_manage_activities_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_send_award_to_ump_type = cqyh::lua::usertype<InternalMessage::G2M_SEND_AWARD_TO_UMP>(L, internal_message_namespace, "G2M_SEND_AWARD_TO_UMP", "InternalMessage::G2M_SEND_AWARD_TO_UMP", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_send_award_to_ump_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_SEND_AWARD_TO_UMP(); });
    internal_message_g2m_send_award_to_ump_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_SEND_AWARD_TO_UMP>(new InternalMessage::G2M_SEND_AWARD_TO_UMP()); });
    internal_message_g2m_send_award_to_ump_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_SEND_AWARD_TO_UMP& self) { return self.dwRoleID; }, [](InternalMessage::G2M_SEND_AWARD_TO_UMP& self, decltype(InternalMessage::G2M_SEND_AWARD_TO_UMP::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_send_award_to_ump_type["nAwardType"] = sol::property([](const InternalMessage::G2M_SEND_AWARD_TO_UMP& self) { return self.nAwardType; }, [](InternalMessage::G2M_SEND_AWARD_TO_UMP& self, decltype(InternalMessage::G2M_SEND_AWARD_TO_UMP::nAwardType) value) { self.nAwardType = value; });
    internal_message_g2m_send_award_to_ump_type["chAwardNumber"] = cqyh::lua::string_property(&InternalMessage::G2M_SEND_AWARD_TO_UMP::chAwardNumber);
}

}
