#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/gameworld/item_mgr.h"
#include "../../../../../inc/gameworld/item.h"
#include "../../../../../../Common/fusion/inc/item_data.h"
#include "../../../../../../Common/define/attribute_def.h"
#include "../../../../../../Common/fusion/inc/rune_data.h"

namespace cqyh::gameworld::bindings {

void register_item_mgr_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto c_item_mgr_type = cqyh::lua::usertype<CItemMgr>(L, globals, "CItemMgr", "CItemMgr");
    c_item_mgr_type.set_function("GetInstance", []() -> decltype(auto) { return CItemMgr::GetInstance(); });
    c_item_mgr_type.set_function("GenerateItem", [](CItemMgr* self, signed int nTemplateID, signed int nItemCount) -> decltype(auto) { return self->GenerateItem(nTemplateID,nItemCount); });
    c_item_mgr_type.set_function("GenerateItem", sol::overload([](CItemMgr* self, const ITEM_DATA* itemdata, signed int nItemCount) -> decltype(auto) { return self->GenerateItem(itemdata,nItemCount); }, [](CItemMgr* self, signed int nTemplateID, signed int nItemCount) -> decltype(auto) { return self->GenerateItem(nTemplateID,nItemCount); }));
    c_item_mgr_type.set_function("DestroyItem", [](CItemMgr* self, Item* item) -> decltype(auto) { return static_cast<bool>(self->DestroyItem(item)); });
}

}
