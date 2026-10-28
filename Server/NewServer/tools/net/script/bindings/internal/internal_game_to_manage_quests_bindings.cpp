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

void register_internal_game_to_manage_quests_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_publish_quest_type = cqyh::lua::usertype<InternalMessage::G2M_PUBLISH_QUEST>(L, internal_message_namespace, "G2M_PUBLISH_QUEST", "InternalMessage::G2M_PUBLISH_QUEST", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_publish_quest_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_PUBLISH_QUEST(); });
    internal_message_g2m_publish_quest_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_PUBLISH_QUEST>(new InternalMessage::G2M_PUBLISH_QUEST()); });
    internal_message_g2m_publish_quest_type["nQuestID"] = sol::property([](const InternalMessage::G2M_PUBLISH_QUEST& self) { return self.nQuestID; }, [](InternalMessage::G2M_PUBLISH_QUEST& self, decltype(InternalMessage::G2M_PUBLISH_QUEST::nQuestID) value) { self.nQuestID = value; });
    internal_message_g2m_publish_quest_type["nNum"] = sol::property([](const InternalMessage::G2M_PUBLISH_QUEST& self) { return self.nNum; }, [](InternalMessage::G2M_PUBLISH_QUEST& self, decltype(InternalMessage::G2M_PUBLISH_QUEST::nNum) value) { self.nNum = value; });
    internal_message_g2m_publish_quest_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_PUBLISH_QUEST& self) { return self.dwRoleID; }, [](InternalMessage::G2M_PUBLISH_QUEST& self, decltype(InternalMessage::G2M_PUBLISH_QUEST::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_publish_quest_type["dwStudentList"] = cqyh::lua::array_property(&InternalMessage::G2M_PUBLISH_QUEST::dwStudentList);
}

}
