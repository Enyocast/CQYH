#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "achievement_list.h"

int sol_achievement_list_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CAchievementsList>(L, globals, "CAchievementsList", "CAchievementsList");
    type1.set_function("CanComplete", [](CAchievementsList* self, signed int nAchievementID) -> decltype(auto) { return self->CanComplete(nAchievementID); });
    type1.set_function("Complete", [](CAchievementsList* self, signed int nAchievementID) -> decltype(auto) { return self->Complete(nAchievementID); });
    type1.set_function("GetCompletedCount", [](CAchievementsList* self) -> decltype(auto) { return self->GetCompletedCount(); });
    type1.set_function("CanReward", [](CAchievementsList* self, signed int nAchievementID) -> decltype(auto) { return self->CanReward(nAchievementID); });
    type1.set_function("Reward", [](CAchievementsList* self, signed int nAchievementID) -> decltype(auto) { return self->Reward(nAchievementID); });
    type1.set_function("GetVariable", [](CAchievementsList* self, signed int nIndex) -> decltype(auto) { return self->GetVariable(nIndex); });
    type1.set_function("SetVariable", [](CAchievementsList* self, signed int nIndex, signed int nValue) -> decltype(auto) { self->SetVariable(nIndex,nValue); });
    type1.set_function("AddVariable", [](CAchievementsList* self, signed int nIndex, signed int nCount) -> decltype(auto) { self->AddVariable(nIndex,nCount); });
    type1.set_function("ActivateHandbook", [](CAchievementsList* self, signed int nHandbookType, signed int nIndex) -> decltype(auto) { self->ActivateHandbook(nHandbookType,nIndex); });
    return 1;
}
