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

void register_internal_game_to_manage_mentorship_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_sync_master_exp_type = cqyh::lua::usertype<InternalMessage::G2M_SYNC_MASTER_EXP>(L, internal_message_namespace, "G2M_SYNC_MASTER_EXP", "InternalMessage::G2M_SYNC_MASTER_EXP", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_sync_master_exp_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_SYNC_MASTER_EXP(); });
    internal_message_g2m_sync_master_exp_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_SYNC_MASTER_EXP>(new InternalMessage::G2M_SYNC_MASTER_EXP()); });
    internal_message_g2m_sync_master_exp_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_SYNC_MASTER_EXP& self) { return self.dwRoleID; }, [](InternalMessage::G2M_SYNC_MASTER_EXP& self, decltype(InternalMessage::G2M_SYNC_MASTER_EXP::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_sync_master_exp_type["llMasterExp"] = sol::property([](const InternalMessage::G2M_SYNC_MASTER_EXP& self) { return self.llMasterExp; }, [](InternalMessage::G2M_SYNC_MASTER_EXP& self, decltype(InternalMessage::G2M_SYNC_MASTER_EXP::llMasterExp) value) { self.llMasterExp = value; });
    auto internal_message_g2m_master_cz_type = cqyh::lua::usertype<InternalMessage::G2M_MASTER_CZ>(L, internal_message_namespace, "G2M_MASTER_CZ", "InternalMessage::G2M_MASTER_CZ", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_master_cz_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_MASTER_CZ(); });
    internal_message_g2m_master_cz_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_MASTER_CZ>(new InternalMessage::G2M_MASTER_CZ()); });
    internal_message_g2m_master_cz_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_MASTER_CZ& self) { return self.dwRoleID; }, [](InternalMessage::G2M_MASTER_CZ& self, decltype(InternalMessage::G2M_MASTER_CZ::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_master_cz_type["dwTargetID"] = sol::property([](const InternalMessage::G2M_MASTER_CZ& self) { return self.dwTargetID; }, [](InternalMessage::G2M_MASTER_CZ& self, decltype(InternalMessage::G2M_MASTER_CZ::dwTargetID) value) { self.dwTargetID = value; });
    internal_message_g2m_master_cz_type["byCZLevel"] = sol::property([](const InternalMessage::G2M_MASTER_CZ& self) { return self.byCZLevel; }, [](InternalMessage::G2M_MASTER_CZ& self, decltype(InternalMessage::G2M_MASTER_CZ::byCZLevel) value) { self.byCZLevel = value; });
    internal_message_g2m_master_cz_type["byCZType"] = sol::property([](const InternalMessage::G2M_MASTER_CZ& self) { return self.byCZType; }, [](InternalMessage::G2M_MASTER_CZ& self, decltype(InternalMessage::G2M_MASTER_CZ::byCZType) value) { self.byCZType = value; });
    internal_message_g2m_master_cz_type["szText"] = cqyh::lua::string_property(&InternalMessage::G2M_MASTER_CZ::szText);
    auto internal_message_g2m_master_twitter_type = cqyh::lua::usertype<InternalMessage::G2M_MASTER_TWITTER>(L, internal_message_namespace, "G2M_MASTER_TWITTER", "InternalMessage::G2M_MASTER_TWITTER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_master_twitter_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_MASTER_TWITTER(); });
    internal_message_g2m_master_twitter_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_MASTER_TWITTER>(new InternalMessage::G2M_MASTER_TWITTER()); });
    internal_message_g2m_master_twitter_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_MASTER_TWITTER& self) { return self.dwRoleID; }, [](InternalMessage::G2M_MASTER_TWITTER& self, decltype(InternalMessage::G2M_MASTER_TWITTER::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_master_twitter_type["bTwitter"] = sol::property([](const InternalMessage::G2M_MASTER_TWITTER& self) { return static_cast<bool>(self.bTwitter); }, [](InternalMessage::G2M_MASTER_TWITTER& self, bool value) { self.bTwitter = value; });
}

}
