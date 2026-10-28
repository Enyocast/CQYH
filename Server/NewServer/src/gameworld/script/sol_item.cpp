#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "item.h"
#include "../../../../Common/fusion/inc/item_data.h"

int sol_item_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<ItemInfo>(L, globals, "ItemInfo", "ItemInfo");
    type1["m_llGuid"] = sol::property([](const ItemInfo& self) { return self.m_llGuid; }, [](ItemInfo& self, decltype(ItemInfo::m_llGuid) value) { self.m_llGuid = value; });
    type1["m_nTemplateID"] = sol::property([](const ItemInfo& self) { return self.m_nTemplateID; }, [](ItemInfo& self, decltype(ItemInfo::m_nTemplateID) value) { self.m_nTemplateID = value; });
    type1["m_byConSlot"] = sol::property([](const ItemInfo& self) { return self.m_byConSlot; }, [](ItemInfo& self, decltype(ItemInfo::m_byConSlot) value) { self.m_byConSlot = value; });
    type1["m_byItemSlot"] = sol::property([](const ItemInfo& self) { return self.m_byItemSlot; }, [](ItemInfo& self, decltype(ItemInfo::m_byItemSlot) value) { self.m_byItemSlot = value; });
    type1["m_nCurDur"] = sol::property([](const ItemInfo& self) { return self.m_nCurDur; }, [](ItemInfo& self, decltype(ItemInfo::m_nCurDur) value) { self.m_nCurDur = value; });
    type1["m_nMaxDur"] = sol::property([](const ItemInfo& self) { return self.m_nMaxDur; }, [](ItemInfo& self, decltype(ItemInfo::m_nMaxDur) value) { self.m_nMaxDur = value; });
    type1["m_byBindType"] = sol::property([](const ItemInfo& self) { return self.m_byBindType; }, [](ItemInfo& self, decltype(ItemInfo::m_byBindType) value) { self.m_byBindType = value; });
    type1["m_byIdentified"] = sol::property([](const ItemInfo& self) { return self.m_byIdentified; }, [](ItemInfo& self, decltype(ItemInfo::m_byIdentified) value) { self.m_byIdentified = value; });
    type1["m_wRandomAttrID"] = cqyh::lua::array_property(&ItemInfo::m_wRandomAttrID);
    type1["m_dwRoleID"] = sol::property([](const ItemInfo& self) { return self.m_dwRoleID; }, [](ItemInfo& self, decltype(ItemInfo::m_dwRoleID) value) { self.m_dwRoleID = value; });
    type1["m_dwCostMoney"] = sol::property([](const ItemInfo& self) { return self.m_dwCostMoney; }, [](ItemInfo& self, decltype(ItemInfo::m_dwCostMoney) value) { self.m_dwCostMoney = value; });
    type1["m_byLuck"] = sol::property([](const ItemInfo& self) { return self.m_byLuck; }, [](ItemInfo& self, decltype(ItemInfo::m_byLuck) value) { self.m_byLuck = value; });
    type1["m_byLevelupTimes"] = sol::property([](const ItemInfo& self) { return self.m_byLevelupTimes; }, [](ItemInfo& self, decltype(ItemInfo::m_byLevelupTimes) value) { self.m_byLevelupTimes = value; });
    type1["m_byLevelupPhyPoint"] = sol::property([](const ItemInfo& self) { return self.m_byLevelupPhyPoint; }, [](ItemInfo& self, decltype(ItemInfo::m_byLevelupPhyPoint) value) { self.m_byLevelupPhyPoint = value; });
    type1["m_byLevelupMagPoint"] = sol::property([](const ItemInfo& self) { return self.m_byLevelupMagPoint; }, [](ItemInfo& self, decltype(ItemInfo::m_byLevelupMagPoint) value) { self.m_byLevelupMagPoint = value; });
    type1["m_byLevelupTaoPoint"] = sol::property([](const ItemInfo& self) { return self.m_byLevelupTaoPoint; }, [](ItemInfo& self, decltype(ItemInfo::m_byLevelupTaoPoint) value) { self.m_byLevelupTaoPoint = value; });
    type1["m_byLevelupTypeHidden"] = sol::property([](const ItemInfo& self) { return self.m_byLevelupTypeHidden; }, [](ItemInfo& self, decltype(ItemInfo::m_byLevelupTypeHidden) value) { self.m_byLevelupTypeHidden = value; });
    type1["m_byLevelupPointHidden"] = sol::property([](const ItemInfo& self) { return self.m_byLevelupPointHidden; }, [](ItemInfo& self, decltype(ItemInfo::m_byLevelupPointHidden) value) { self.m_byLevelupPointHidden = value; });
    type1["m_wRune"] = cqyh::lua::array_property(&ItemInfo::m_wRune);
    type1["m_dwSocketCombination"] = sol::property([](const ItemInfo& self) { return self.m_dwSocketCombination; }, [](ItemInfo& self, decltype(ItemInfo::m_dwSocketCombination) value) { self.m_dwSocketCombination = value; });
    type1["m_nSoulID"] = cqyh::lua::array_property(&ItemInfo::m_nSoulID);
    auto type2 = cqyh::lua::usertype<Item>(L, globals, "Item", "Item");
    type2["m_pTemplate"] = sol::readonly(&Item::m_pTemplate);
    type2["m_iteminfo"] = &Item::m_iteminfo;
    type2.set_function("SetAttribute", [](Item* self, signed int index, unsigned short attrid) -> decltype(auto) { return static_cast<bool>(self->SetAttribute(index,attrid)); });
    type2.set_function("SetSocketColor", [](Item* self, signed int index, unsigned char color) -> decltype(auto) { return static_cast<bool>(self->SetSocketColor(index,color)); });
    type2.set_function("SetSoul", [](Item* self, signed int index, signed int soulid) -> decltype(auto) { return static_cast<bool>(self->SetSoul(index,soulid)); });
    return 1;
}
