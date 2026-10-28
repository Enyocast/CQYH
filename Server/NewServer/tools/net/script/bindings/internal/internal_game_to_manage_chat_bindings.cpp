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

void register_internal_game_to_manage_chat_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_chat_message_type = cqyh::lua::usertype<InternalMessage::G2M_CHAT_MESSAGE>(L, internal_message_namespace, "G2M_CHAT_MESSAGE", "InternalMessage::G2M_CHAT_MESSAGE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_chat_message_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_CHAT_MESSAGE(); });
    internal_message_g2m_chat_message_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_CHAT_MESSAGE>(new InternalMessage::G2M_CHAT_MESSAGE()); });
    internal_message_g2m_chat_message_type["dwSourceID"] = sol::property([](const InternalMessage::G2M_CHAT_MESSAGE& self) { return self.dwSourceID; }, [](InternalMessage::G2M_CHAT_MESSAGE& self, decltype(InternalMessage::G2M_CHAT_MESSAGE::dwSourceID) value) { self.dwSourceID = value; });
    internal_message_g2m_chat_message_type["dwTargetID"] = sol::property([](const InternalMessage::G2M_CHAT_MESSAGE& self) { return self.dwTargetID; }, [](InternalMessage::G2M_CHAT_MESSAGE& self, decltype(InternalMessage::G2M_CHAT_MESSAGE::dwTargetID) value) { self.dwTargetID = value; });
    internal_message_g2m_chat_message_type["byLocation"] = sol::property([](const InternalMessage::G2M_CHAT_MESSAGE& self) { return self.byLocation; }, [](InternalMessage::G2M_CHAT_MESSAGE& self, decltype(InternalMessage::G2M_CHAT_MESSAGE::byLocation) value) { self.byLocation = value; });
    internal_message_g2m_chat_message_type["byServerGroupID"] = sol::property([](const InternalMessage::G2M_CHAT_MESSAGE& self) { return self.byServerGroupID; }, [](InternalMessage::G2M_CHAT_MESSAGE& self, decltype(InternalMessage::G2M_CHAT_MESSAGE::byServerGroupID) value) { self.byServerGroupID = value; });
    internal_message_g2m_chat_message_type["bGM"] = sol::property([](const InternalMessage::G2M_CHAT_MESSAGE& self) { return self.bGM; }, [](InternalMessage::G2M_CHAT_MESSAGE& self, decltype(InternalMessage::G2M_CHAT_MESSAGE::bGM) value) { self.bGM = value; });
    internal_message_g2m_chat_message_type["szName"] = cqyh::lua::string_property(&InternalMessage::G2M_CHAT_MESSAGE::szName);
    internal_message_g2m_chat_message_type["szMessage"] = cqyh::lua::string_property(&InternalMessage::G2M_CHAT_MESSAGE::szMessage);
}

}
