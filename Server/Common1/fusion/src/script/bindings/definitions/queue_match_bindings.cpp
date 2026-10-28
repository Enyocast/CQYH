#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/queue_match_def.h"

namespace cqyh::fusion::bindings {

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
    globals["bttInvalid"] = static_cast<lua_Number>(bttInvalid);
    globals["bttFixed"] = static_cast<lua_Number>(bttFixed);
    globals["btt5V5"] = static_cast<lua_Number>(btt5V5);
    globals["btt10V10"] = static_cast<lua_Number>(btt10V10);
    globals["btt15V15"] = static_cast<lua_Number>(btt15V15);
    globals["btt10V10V10"] = static_cast<lua_Number>(btt10V10V10);
    globals["btt20V20"] = static_cast<lua_Number>(btt20V20);
    globals["bttTotal"] = static_cast<lua_Number>(bttTotal);
    globals["bfInvalid"] = static_cast<lua_Number>(bfInvalid);
    globals["bfFirst"] = static_cast<lua_Number>(bfFirst);
    globals["bfSecond"] = static_cast<lua_Number>(bfSecond);
    globals["bfThrid"] = static_cast<lua_Number>(bfThrid);
    globals["bfFourth"] = static_cast<lua_Number>(bfFourth);
    globals["bfTotal"] = static_cast<lua_Number>(bfTotal);
    globals["qsInvalid"] = static_cast<lua_Number>(qsInvalid);
    globals["qsNotInQueue"] = static_cast<lua_Number>(qsNotInQueue);
    globals["qsInQueue"] = static_cast<lua_Number>(qsInQueue);
    globals["qsQueueConfirm"] = static_cast<lua_Number>(qsQueueConfirm);
    globals["qsTotal"] = static_cast<lua_Number>(qsTotal);
    auto queue_data_type = cqyh::lua::usertype<QUEUE_DATA>(L, globals, "QUEUE_DATA", "QUEUE_DATA");
    queue_data_type["byQueue"] = sol::property([](const QUEUE_DATA& self) { return self.byQueue; }, [](QUEUE_DATA& self, decltype(QUEUE_DATA::byQueue) value) { self.byQueue = value; });
    queue_data_type["dwJoinConfirmTimeOut"] = sol::property([](const QUEUE_DATA& self) { return self.dwJoinConfirmTimeOut; }, [](QUEUE_DATA& self, decltype(QUEUE_DATA::dwJoinConfirmTimeOut) value) { self.dwJoinConfirmTimeOut = value; });
    queue_data_type["dwJoinSceneTempID"] = sol::property([](const QUEUE_DATA& self) { return self.dwJoinSceneTempID; }, [](QUEUE_DATA& self, decltype(QUEUE_DATA::dwJoinSceneTempID) value) { self.dwJoinSceneTempID = value; });
    queue_data_type["dwJoinSceneID"] = sol::property([](const QUEUE_DATA& self) { return self.dwJoinSceneID; }, [](QUEUE_DATA& self, decltype(QUEUE_DATA::dwJoinSceneID) value) { self.dwJoinSceneID = value; });
    queue_data_type["dwJoinSide"] = sol::property([](const QUEUE_DATA& self) { return self.dwJoinSide; }, [](QUEUE_DATA& self, decltype(QUEUE_DATA::dwJoinSide) value) { self.dwJoinSide = value; });
}

}
