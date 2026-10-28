#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/item_def.h"
#include "../../../../../inc/gameworld/item_bag.h"
#include "../../../../../inc/gameworld/item.h"
#include "../../../../../../Common/fusion/inc/black_market_data.h"
#include "../../../../../../Common/fusion/inc/set_data.h"
#include "../../../../../inc/gameworld/aura_instance.h"
#include "../../../../../inc/gameworld/character.h"
#include "../../../../../inc/gameworld/hero.h"
#include "../../../../../inc/gameworld/role.h"

namespace cqyh::gameworld::bindings {

void register_item_bag_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto c_item_bag_type = cqyh::lua::usertype<CItemBag>(L, globals, "CItemBag", "CItemBag");
    c_item_bag_type.set_function("AddItem", [](CItemBag* self, signed int itemid, signed int itemcount, EItemLog reason, UINT64 userdefine, bool forcebinded) -> decltype(auto) { return self->AddItem(itemid,itemcount,reason,userdefine,forcebinded); });
    c_item_bag_type.set_function("AddItem", sol::overload([](CItemBag* self, Item* item, EItemLog reason, UINT64 userdefine) -> decltype(auto) { return self->AddItem(item,reason,userdefine); }, [](CItemBag* self, signed int itemid, signed int itemcount, EItemLog reason, UINT64 userdefine, bool forcebinded) -> decltype(auto) { return self->AddItem(itemid,itemcount,reason,userdefine,forcebinded); }));
    c_item_bag_type.set_function("UseItem", [](CItemBag* self, unsigned char conslot, unsigned char itemslot) -> decltype(auto) { return self->UseItem(conslot,itemslot); });
    c_item_bag_type.set_function("MoveItem", [](CItemBag* self, unsigned char srcconslot, unsigned char srcitemslot, unsigned char dstconslot, unsigned char dstitemslot) -> decltype(auto) { return self->MoveItem(srcconslot,srcitemslot,dstconslot,dstitemslot); });
    c_item_bag_type.set_function("SplitItem", [](CItemBag* self, unsigned char srcconslot, unsigned char srcitemslot, unsigned char dstconslot, unsigned char dstitemslot, signed short itemcount) -> decltype(auto) { return self->SplitItem(srcconslot,srcitemslot,dstconslot,dstitemslot,itemcount); });
    c_item_bag_type.set_function("DeleteItemPos", [](CItemBag* self, unsigned char conslot, unsigned char itemslot, signed short itemcount, EItemLog reason, UINT64 qwUserDefinedID) -> decltype(auto) { return self->DeleteItemPos(conslot,itemslot,itemcount,reason,qwUserDefinedID); });
    c_item_bag_type.set_function("GetItemCount", [](CItemBag* self, signed int itemid, bool includebank) -> decltype(auto) { return self->GetItemCount(itemid,includebank); });
    c_item_bag_type.set_function("DeleteItemId", [](CItemBag* self, signed int itemid, signed short itemcount, EItemLog reason, bool includebank, UINT64 qwUserDefinedID) -> decltype(auto) { return self->DeleteItemId(itemid,itemcount,reason,includebank,qwUserDefinedID); });
    c_item_bag_type.set_function("GetFreeSlots", [](CItemBag* self, unsigned char conslot) -> decltype(auto) { return self->GetFreeSlots(conslot); });
    c_item_bag_type.set_function("IdentifyItem", [](CItemBag* self, unsigned char conslot, unsigned char itemslot) -> decltype(auto) { return self->IdentifyItem(conslot,itemslot); });
    c_item_bag_type.set_function("Refine", [](CItemBag* self, unsigned char refineslot, unsigned char addequip, unsigned char conslot, unsigned char itemslot) -> decltype(auto) { return self->Refine(refineslot,addequip,conslot,itemslot); });
    c_item_bag_type.set_function("SetRefineLevel", [](CItemBag* self, unsigned char refineslot, unsigned short level) -> decltype(auto) { self->SetRefineLevel(refineslot,level); });
    c_item_bag_type.set_function("RandomizeItem", [](CItemBag* self, unsigned char conslot, unsigned char itemslot) -> decltype(auto) { return self->RandomizeItem(conslot,itemslot); });
    c_item_bag_type.set_function("AddSoul", [](CItemBag* self, unsigned char equipconslot, unsigned char equipitemslot, unsigned char socketindex, unsigned char soulconslot, unsigned char soulitemslot) -> decltype(auto) { return self->AddSoul(equipconslot,equipitemslot,socketindex,soulconslot,soulitemslot); });
    c_item_bag_type.set_function("GetItem", [](CItemBag* self, unsigned char conslot, unsigned char itemslot) -> decltype(auto) { return self->GetItem(conslot,itemslot); });
    c_item_bag_type.set_function("LoseWeaponDur", [](CItemBag* self) -> decltype(auto) { self->LoseWeaponDur(); });
    c_item_bag_type.set_function("LoseArmorDur", [](CItemBag* self, signed int damage) -> decltype(auto) { self->LoseArmorDur(damage); });
    c_item_bag_type.set_function("BuySlots", [](CItemBag* self, unsigned char conslot, unsigned char slotcount) -> decltype(auto) { return self->BuySlots(conslot,slotcount); });
    c_item_bag_type.set_function("EquipItemOnBirth", [](CItemBag* self, signed int itemid, unsigned char itemslot) -> decltype(auto) { return static_cast<bool>(self->EquipItemOnBirth(itemid,itemslot)); });
    c_item_bag_type.set_function("EquipHeroItemOnBirth", [](CItemBag* self, signed int itemid, unsigned char itemslot) -> decltype(auto) { return static_cast<bool>(self->EquipHeroItemOnBirth(itemid,itemslot)); });
    c_item_bag_type.set_function("GetMoney", [](CItemBag* self, signed int moneytype) -> decltype(auto) { return self->GetMoney(moneytype); });
    c_item_bag_type.set_function("AddMoney", [](CItemBag* self, signed int moneytype, signed int nCount, EMoneyLog reason, unsigned int dwSourceID) -> decltype(auto) { return self->AddMoney(moneytype,nCount,reason,dwSourceID); });
    c_item_bag_type.set_function("SubMoney", [](CItemBag* self, signed int moneytype, signed int nCount, EMoneyLog reason, unsigned int dwTargetID) -> decltype(auto) { return self->SubMoney(moneytype,nCount,reason,dwTargetID); });
    c_item_bag_type.set_function("SetMoney", [](CItemBag* self, signed int moneytype, signed int nCount) -> decltype(auto) { return self->SetMoney(moneytype,nCount); });
    c_item_bag_type.set_function("GetGoldPool", [](CItemBag* self) -> decltype(auto) { return self->GetGoldPool(); });
    c_item_bag_type.set_function("GetChanceByGoldPool", [](CItemBag* self) -> decltype(auto) { return self->GetChanceByGoldPool(); });
    c_item_bag_type.set_function("SetUseMoneytype01Only", [](CItemBag* self, unsigned char use) -> decltype(auto) { self->SetUseMoneytype01Only(use); });
    c_item_bag_type.set_function("GetUseMoneytype01Only", [](CItemBag* self) -> decltype(auto) { return self->GetUseMoneytype01Only(); });
    c_item_bag_type.set_function("GetWeaponType", [](CItemBag* self) -> decltype(auto) { return self->GetWeaponType(); });
    c_item_bag_type.set_function("GetHeroWeaponType", [](CItemBag* self) -> decltype(auto) { return self->GetHeroWeaponType(); });
    c_item_bag_type.set_function("Begin", [](CItemBag* self, unsigned char conslot) -> decltype(auto) { self->Begin(conslot); });
    c_item_bag_type.set_function("Next", [](CItemBag* self, unsigned char conslot) -> decltype(auto) { return self->Next(conslot); });
    c_item_bag_type.set_function("SetWeaponLuck", [](CItemBag* self, signed char v) -> decltype(auto) { self->SetWeaponLuck(v); });
    c_item_bag_type.set_function("IncreaseWeaponLuck", [](CItemBag* self, signed char v) -> decltype(auto) { self->IncreaseWeaponLuck(v); });
    c_item_bag_type.set_function("DecreaseWeaponLuck", [](CItemBag* self) -> decltype(auto) { self->DecreaseWeaponLuck(); });
    c_item_bag_type.set_function("RuneTest", [](CItemBag* self, signed int nRuneID) -> decltype(auto) { return self->RuneTest(nRuneID); });
    c_item_bag_type.set_function("EquipAddSocket", [](CItemBag* self, signed int nIndex) -> decltype(auto) { return self->EquipAddSocket(nIndex); });
    c_item_bag_type.set_function("SetSocketColor", [](CItemBag* self, signed int nIndex, signed int nColor) -> decltype(auto) { return self->SetSocketColor(nIndex,nColor); });
    c_item_bag_type.set_function("AddDestinyWeapon", [](CItemBag* self, signed int nItemID, signed int nLevel) -> decltype(auto) { return self->AddDestinyWeapon(nItemID,nLevel); });
}

}
