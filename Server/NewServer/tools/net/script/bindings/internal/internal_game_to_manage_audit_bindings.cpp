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

void register_internal_game_to_manage_audit_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_gm_log_type = cqyh::lua::usertype<InternalMessage::G2M_GM_LOG>(L, internal_message_namespace, "G2M_GM_LOG", "InternalMessage::G2M_GM_LOG", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_gm_log_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GM_LOG(); });
    internal_message_g2m_gm_log_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GM_LOG>(new InternalMessage::G2M_GM_LOG()); });
    internal_message_g2m_gm_log_type["dwTime"] = sol::property([](const InternalMessage::G2M_GM_LOG& self) { return self.dwTime; }, [](InternalMessage::G2M_GM_LOG& self, decltype(InternalMessage::G2M_GM_LOG::dwTime) value) { self.dwTime = value; });
    internal_message_g2m_gm_log_type["nResult"] = sol::property([](const InternalMessage::G2M_GM_LOG& self) { return self.nResult; }, [](InternalMessage::G2M_GM_LOG& self, decltype(InternalMessage::G2M_GM_LOG::nResult) value) { self.nResult = value; });
    internal_message_g2m_gm_log_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GM_LOG& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GM_LOG& self, decltype(InternalMessage::G2M_GM_LOG::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_gm_log_type["szGMCmd"] = cqyh::lua::string_property(&InternalMessage::G2M_GM_LOG::szGMCmd);
}

}
