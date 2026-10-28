#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "quest_list.h"

int sol_quest_list_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<ACCEPTED_QUEST>(L, globals, "ACCEPTED_QUEST", "ACCEPTED_QUEST");
    type1["nQuestID"] = sol::property([](const ACCEPTED_QUEST& self) { return self.nQuestID; }, [](ACCEPTED_QUEST& self, decltype(ACCEPTED_QUEST::nQuestID) value) { self.nQuestID = value; });
    type1["dwAcceptTime"] = sol::property([](const ACCEPTED_QUEST& self) { return self.dwAcceptTime; }, [](ACCEPTED_QUEST& self, decltype(ACCEPTED_QUEST::dwAcceptTime) value) { self.dwAcceptTime = value; });
    type1["nKillNpcCount"] = cqyh::lua::array_property(&ACCEPTED_QUEST::nKillNpcCount);
    type1["nVariable"] = cqyh::lua::array_property(&ACCEPTED_QUEST::nVariable);
    auto type2 = cqyh::lua::usertype<CQuestList>(L, globals, "CQuestList", "CQuestList");
    type2.set_function("GetAcceptedQuest", [](CQuestList* self, signed int nQuestID) -> decltype(auto) { return self->GetAcceptedQuest(nQuestID); });
    type2.set_function("SetVariable", [](CQuestList* self, const ACCEPTED_QUEST* pAcceptedQuest, signed int nIndex, signed int nValue) -> decltype(auto) { self->SetVariable(pAcceptedQuest,nIndex,nValue); });
    type2.set_function("GetVariable", [](CQuestList* self, const ACCEPTED_QUEST* pAcceptedQuest, signed int nIndex) -> decltype(auto) { return self->GetVariable(pAcceptedQuest,nIndex); });
    type2.set_function("CanAbandon", [](CQuestList* self, signed int nQuestID) -> decltype(auto) { return self->CanAbandon(nQuestID); });
    type2.set_function("Abandon", [](CQuestList* self, signed int nQuestID) -> decltype(auto) { return self->Abandon(nQuestID); });
    type2.set_function("CanAccept", [](CQuestList* self, signed int nQuestID, signed int nAcceptType, signed int nSrcID) -> decltype(auto) { return self->CanAccept(nQuestID,nAcceptType,nSrcID); });
    type2.set_function("Accept", [](CQuestList* self, signed int nQuestID) -> decltype(auto) { return self->Accept(nQuestID); });
    type2.set_function("Complete", [](CQuestList* self, signed int nQuestID, sol::optional<signed int> nSelectedAwardIndex_arg) -> decltype(auto) { signed int nSelectedAwardIndex = nSelectedAwardIndex_arg.value_or(0); return self->Complete(nQuestID,nSelectedAwardIndex); });
    type2.set_function("SetQuestFailed", [](CQuestList* self, const ACCEPTED_QUEST* pAcceptedQuest) -> decltype(auto) { self->SetQuestFailed(pAcceptedQuest); });
    return 1;
}
