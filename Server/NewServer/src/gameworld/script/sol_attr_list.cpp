#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "attr_list.h"
#include "../../../inc/gameworld/character.h"

int sol_attr_list_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CAttrList>(L, globals, "CAttrList", "CAttrList");
    type1.set_function("GetAttr", [](CAttrList* self, signed int eAttrType) -> decltype(auto) { return self->GetAttr(eAttrType); });
    type1.set_function("SetAttrBase", [](CAttrList* self, CCharacter* pSelf, signed int eAttrType, signed int nValue) -> decltype(auto) { self->SetAttrBase(pSelf,eAttrType,nValue); });
    type1.set_function("SetAttrA", [](CAttrList* self, CCharacter* pSelf, signed int eAttrType, signed int nValue) -> decltype(auto) { self->SetAttrA(pSelf,eAttrType,nValue); });
    type1.set_function("SetAttrB", [](CAttrList* self, CCharacter* pSelf, signed int eAttrType, signed int nValue) -> decltype(auto) { self->SetAttrB(pSelf,eAttrType,nValue); });
    type1.set_function("EnableAttr", [](CAttrList* self, signed int eAttrType, bool bEnable) -> decltype(auto) { self->EnableAttr(eAttrType,bEnable); });
    type1.set_function("AddAttrA", [](CAttrList* self, CCharacter* pSelf, signed int eAttrType, signed int nValue) -> decltype(auto) { self->AddAttrA(pSelf,eAttrType,nValue); });
    type1.set_function("AddAttrB", [](CAttrList* self, CCharacter* pSelf, signed int eAttrType, signed int nValue) -> decltype(auto) { self->AddAttrB(pSelf,eAttrType,nValue); });
    type1.set_function("CalculateAll", [](CAttrList* self, CCharacter* pSelf) -> decltype(auto) { self->CalculateAll(pSelf); });
    type1.set_function("ReCalculateAttr", [](CAttrList* self, CCharacter* pSelf, signed int eAttrType) -> decltype(auto) { self->ReCalculateAttr(pSelf,eAttrType); });
    return 1;
}
