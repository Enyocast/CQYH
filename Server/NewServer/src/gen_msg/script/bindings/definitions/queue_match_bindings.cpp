#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/queue_match_def.h"

namespace cqyh::gen_msg::bindings {

void register_queue_match_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_BATTLE_TEMPLATE_COUNT"] = static_cast<lua_Number>(MAX_BATTLE_TEMPLATE_COUNT);
    globals["MAX_ARENA_GROUP_COUNT"] = static_cast<lua_Number>(MAX_ARENA_GROUP_COUNT);
    globals["MAX_ARENA_MATCH_GROUP"] = static_cast<lua_Number>(MAX_ARENA_MATCH_GROUP);
    globals["MAX_ARENA_TEMPLATE_COUNT"] = static_cast<lua_Number>(MAX_ARENA_TEMPLATE_COUNT);
    globals["MAX_ABNORMAL_LEAVE_TIME"] = static_cast<lua_Number>(MAX_ABNORMAL_LEAVE_TIME);
    globals["MAX_JOIN_CONFIRM_TIME"] = static_cast<lua_Number>(MAX_JOIN_CONFIRM_TIME);
    sol::table battle_template_type_namespace = globals["BATTLE_TEMPLATE_TYPE"].get_or_create<sol::table>();
    battle_template_type_namespace["bttInvalid"] = static_cast<lua_Number>(bttInvalid);
    battle_template_type_namespace["bttFixed"] = static_cast<lua_Number>(bttFixed);
    battle_template_type_namespace["btt5V5"] = static_cast<lua_Number>(btt5V5);
    battle_template_type_namespace["btt10V10"] = static_cast<lua_Number>(btt10V10);
    battle_template_type_namespace["btt15V15"] = static_cast<lua_Number>(btt15V15);
    battle_template_type_namespace["btt10V10V10"] = static_cast<lua_Number>(btt10V10V10);
    battle_template_type_namespace["btt20V20"] = static_cast<lua_Number>(btt20V20);
    battle_template_type_namespace["bttTotal"] = static_cast<lua_Number>(bttTotal);
    sol::table battle_faction_namespace = globals["BATTLE_FACTION"].get_or_create<sol::table>();
    battle_faction_namespace["bfInvalid"] = static_cast<lua_Number>(bfInvalid);
    battle_faction_namespace["bfFirst"] = static_cast<lua_Number>(bfFirst);
    battle_faction_namespace["bfSecond"] = static_cast<lua_Number>(bfSecond);
    battle_faction_namespace["bfThrid"] = static_cast<lua_Number>(bfThrid);
    battle_faction_namespace["bfFourth"] = static_cast<lua_Number>(bfFourth);
    battle_faction_namespace["bfTotal"] = static_cast<lua_Number>(bfTotal);
    sol::table queue_state_namespace = globals["QUEUE_STATE"].get_or_create<sol::table>();
    queue_state_namespace["qsInvalid"] = static_cast<lua_Number>(qsInvalid);
    queue_state_namespace["qsNotInQueue"] = static_cast<lua_Number>(qsNotInQueue);
    queue_state_namespace["qsInQueue"] = static_cast<lua_Number>(qsInQueue);
    queue_state_namespace["qsQueueConfirm"] = static_cast<lua_Number>(qsQueueConfirm);
    queue_state_namespace["qsTotal"] = static_cast<lua_Number>(qsTotal);
    auto queue_data_type = cqyh::lua::usertype<QUEUE_DATA>(L, globals, "QUEUE_DATA", "QUEUE_DATA");
    queue_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new QUEUE_DATA(); });
    queue_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<QUEUE_DATA>(new QUEUE_DATA()); });
    queue_data_type["byQueue"] = sol::property([](const QUEUE_DATA& self) { return self.byQueue; }, [](QUEUE_DATA& self, decltype(QUEUE_DATA::byQueue) value) { self.byQueue = value; });
    queue_data_type["dwJoinConfirmTimeOut"] = sol::property([](const QUEUE_DATA& self) { return self.dwJoinConfirmTimeOut; }, [](QUEUE_DATA& self, decltype(QUEUE_DATA::dwJoinConfirmTimeOut) value) { self.dwJoinConfirmTimeOut = value; });
    queue_data_type["dwJoinSceneTempID"] = sol::property([](const QUEUE_DATA& self) { return self.dwJoinSceneTempID; }, [](QUEUE_DATA& self, decltype(QUEUE_DATA::dwJoinSceneTempID) value) { self.dwJoinSceneTempID = value; });
    queue_data_type["dwJoinSceneID"] = sol::property([](const QUEUE_DATA& self) { return self.dwJoinSceneID; }, [](QUEUE_DATA& self, decltype(QUEUE_DATA::dwJoinSceneID) value) { self.dwJoinSceneID = value; });
    queue_data_type["dwJoinSide"] = sol::property([](const QUEUE_DATA& self) { return self.dwJoinSide; }, [](QUEUE_DATA& self, decltype(QUEUE_DATA::dwJoinSide) value) { self.dwJoinSide = value; });
}

}
