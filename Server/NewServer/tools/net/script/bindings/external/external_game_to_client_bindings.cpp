#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/message/external_message_header.h"
#include "../../../../../../Common/message/g2c_message.h"
#include "../../../../../../Common/define/dds_def.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/npc_def.h"
#include "../../../../../../Common/define/quest_def.h"
#include "../../../../../../Common/define/string_def.h"
#include "../../../../../../Common/define/variable_def.h"
#include "../../../../../../Common1/message/g2c_message.h"

namespace cqyh::net_tools::bindings {

void register_external_game_to_client_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table external_message_namespace = globals["ExternalMessage"].get_or_create<sol::table>();
    auto external_message_g2c_arena_finish_score_type = cqyh::lua::usertype<ExternalMessage::G2C_ARENA_FINISH_SCORE>(L, external_message_namespace, "G2C_ARENA_FINISH_SCORE", "ExternalMessage::G2C_ARENA_FINISH_SCORE", sol::base_classes, sol::bases<ExternalMessage::FLEX_MESSAGE_HEADER, ExternalMessage::MESSAGE_HEADER>());
    external_message_g2c_arena_finish_score_type.set_function("new", [](sol::table) -> decltype(auto) { return new ExternalMessage::G2C_ARENA_FINISH_SCORE(); });
    external_message_g2c_arena_finish_score_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<ExternalMessage::G2C_ARENA_FINISH_SCORE>(new ExternalMessage::G2C_ARENA_FINISH_SCORE()); });
    external_message_g2c_arena_finish_score_type["nCurScore"] = sol::property([](const ExternalMessage::G2C_ARENA_FINISH_SCORE& self) { return self.nCurScore; }, [](ExternalMessage::G2C_ARENA_FINISH_SCORE& self, decltype(ExternalMessage::G2C_ARENA_FINISH_SCORE::nCurScore) value) { self.nCurScore = value; });
    external_message_g2c_arena_finish_score_type["byCount"] = sol::property([](const ExternalMessage::G2C_ARENA_FINISH_SCORE& self) { return self.byCount; }, [](ExternalMessage::G2C_ARENA_FINISH_SCORE& self, decltype(ExternalMessage::G2C_ARENA_FINISH_SCORE::byCount) value) { self.byCount = value; });
    external_message_g2c_arena_finish_score_type["stScore"] = cqyh::lua::array_property(&ExternalMessage::G2C_ARENA_FINISH_SCORE::stScore);
}

}
