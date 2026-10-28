#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "title.h"
#include "../../../inc/gameworld/role.h"

int sol_title_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CTitle>(L, globals, "CTitle", "CTitle");
    type1.set_function("Init", [](CTitle* self, CRole* role) -> decltype(auto) { return static_cast<bool>(self->Init(role)); });
    type1.set_function("clear", [](CTitle* self) -> decltype(auto) { return static_cast<bool>(self->clear()); });
    type1.set_function("SetOwner", [](CTitle* self, CRole* role) -> decltype(auto) { self->SetOwner(role); });
    type1.set_function("GetEquipedTitleID", [](CTitle* self) -> decltype(auto) { return self->GetEquipedTitleID(); });
    type1.set_function("AddTitle", [](CTitle* self, unsigned char titleTemplateID) -> decltype(auto) { return static_cast<bool>(self->AddTitle(titleTemplateID)); });
    type1.set_function("DeleteTitle", [](CTitle* self, unsigned char titleTemplateID, unsigned char nDelType) -> decltype(auto) { return static_cast<bool>(self->DeleteTitle(titleTemplateID,nDelType)); });
    type1.set_function("EquipTile", [](CTitle* self, unsigned char titleTemplateID) -> decltype(auto) { return self->EquipTile(titleTemplateID); });
    type1.set_function("UnEquipTitle", [](CTitle* self) -> decltype(auto) { return static_cast<bool>(self->UnEquipTitle()); });
    type1.set_function("IsTitleExist", [](CTitle* self, unsigned char wTitleTemplateID) -> decltype(auto) { return static_cast<bool>(self->IsTitleExist(wTitleTemplateID)); });
    return 1;
}
