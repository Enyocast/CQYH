#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/message/external_message_header.h"
#include "../../../../../../Common/message/c2g_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_external_client_to_game_gambling_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table external_message_namespace = globals["ExternalMessage"].get_or_create<sol::table>();
    auto external_message_c2g_gamble_type = cqyh::lua::usertype<ExternalMessage::C2G_GAMBLE>(L, external_message_namespace, "C2G_GAMBLE", "ExternalMessage::C2G_GAMBLE", sol::base_classes, sol::bases<ExternalMessage::MESSAGE_HEADER>());
    external_message_c2g_gamble_type.set_function("new", [](sol::table) -> decltype(auto) { return new ExternalMessage::C2G_GAMBLE(); });
    external_message_c2g_gamble_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<ExternalMessage::C2G_GAMBLE>(new ExternalMessage::C2G_GAMBLE()); });
    external_message_c2g_gamble_type["byEquipType"] = sol::property([](const ExternalMessage::C2G_GAMBLE& self) { return self.byEquipType; }, [](ExternalMessage::C2G_GAMBLE& self, decltype(ExternalMessage::C2G_GAMBLE::byEquipType) value) { self.byEquipType = value; });
    auto external_message_c2g_jigsaw_answer_type = cqyh::lua::usertype<ExternalMessage::C2G_JIGSAW_ANSWER>(L, external_message_namespace, "C2G_JIGSAW_ANSWER", "ExternalMessage::C2G_JIGSAW_ANSWER", sol::base_classes, sol::bases<ExternalMessage::MESSAGE_HEADER>());
    external_message_c2g_jigsaw_answer_type.set_function("new", [](sol::table) -> decltype(auto) { return new ExternalMessage::C2G_JIGSAW_ANSWER(); });
    external_message_c2g_jigsaw_answer_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<ExternalMessage::C2G_JIGSAW_ANSWER>(new ExternalMessage::C2G_JIGSAW_ANSWER()); });
    external_message_c2g_jigsaw_answer_type["byIndex"] = sol::property([](const ExternalMessage::C2G_JIGSAW_ANSWER& self) { return self.byIndex; }, [](ExternalMessage::C2G_JIGSAW_ANSWER& self, decltype(ExternalMessage::C2G_JIGSAW_ANSWER::byIndex) value) { self.byIndex = value; });
}

}
