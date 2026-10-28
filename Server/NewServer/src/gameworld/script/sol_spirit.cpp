#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "spirit.h"

int sol_spirit_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CSpirit>(L, globals, "CSpirit", "CSpirit");
    type1.set_function("SetLevel", [](CSpirit* self, signed int nLevel) -> decltype(auto) { return self->SetLevel(nLevel); });
    type1.set_function("SetProductAirLevel", [](CSpirit* self, signed int nLevel) -> decltype(auto) { return self->SetProductAirLevel(nLevel); });
    type1.set_function("GetLevel", [](CSpirit* self) -> decltype(auto) { return self->GetLevel(); });
    type1.set_function("GetNextExp2PtsTime", [](CSpirit* self) -> decltype(auto) { return self->GetNextExp2PtsTime(); });
    type1.set_function("SetProductAirLevel", sol::overload([](CSpirit* self, signed int nLevel) -> decltype(auto) { return self->SetProductAirLevel(nLevel); }, [](CSpirit* self, signed int nLevel) -> decltype(auto) { return self->SetProductAirLevel(nLevel); }));
    type1.set_function("ProductAir", [](CSpirit* self, signed int nIndex) -> decltype(auto) { return self->ProductAir(nIndex); });
    type1.set_function("AddAir", [](CSpirit* self, signed int nTemplateID, signed int Exp) -> decltype(auto) { return self->AddAir(nTemplateID,Exp); });
    type1.set_function("MergeAir", [](CSpirit* self, signed int nSrcCon) -> decltype(auto) { return self->MergeAir(nSrcCon); });
    type1.set_function("MoveAir", [](CSpirit* self, signed int SrcType, signed int SrcIndex, signed int TarType, signed int TarIndex) -> decltype(auto) { return self->MoveAir(SrcType,SrcIndex,TarType,TarIndex); });
    type1.set_function("ExchangeAir", [](CSpirit* self, signed int nAirID) -> decltype(auto) { return self->ExchangeAir(nAirID); });
    type1.set_function("AddSlot", [](CSpirit* self, signed int nType, signed int nCount) -> decltype(auto) { return self->AddSlot(nType,nCount); });
    type1.set_function("GetHigherAirLevelIndex", [](CSpirit* self) -> decltype(auto) { return self->GetHigherAirLevelIndex(); });
    type1.set_function("GetBagContainerSize", [](CSpirit* self) -> decltype(auto) { return self->GetBagContainerSize(); });
    type1.set_function("GetStallContainerSize", [](CSpirit* self) -> decltype(auto) { return self->GetStallContainerSize(); });
    type1.set_function("GetEquipContainerSize", [](CSpirit* self) -> decltype(auto) { return self->GetEquipContainerSize(); });
    type1.set_function("GetAir", [](CSpirit* self, signed int nBagType, signed int nBagIndex) -> decltype(auto) { return self->GetAir(nBagType,nBagIndex); });
    type1.set_function("BrushBloodSlot", [](CSpirit* self, signed int nPage, signed int nIndex) -> decltype(auto) { return self->BrushBloodSlot(nPage,nIndex); });
    type1.set_function("OpenBlood", [](CSpirit* self, signed int nPage) -> decltype(auto) { return self->OpenBlood(nPage); });
    type1.set_function("SetBlood", [](CSpirit* self, signed int nPage, signed int nSlot, signed int nNewNumber) -> decltype(auto) { return self->SetBlood(nPage,nSlot,nNewNumber); });
    type1.set_function("IsBloodOpen", [](CSpirit* self, signed int nPage) -> decltype(auto) { return self->IsBloodOpen(nPage); });
    type1.set_function("GetBlood", [](CSpirit* self, signed int nPage, signed int nSlot) -> decltype(auto) { return self->GetBlood(nPage,nSlot); });
    return 1;
}
