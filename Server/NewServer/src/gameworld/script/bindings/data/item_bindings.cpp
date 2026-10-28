#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/fusion/inc/item_data.h"
#include "../../../../../inc/baselib/data_manager.h"
#include "../../../../../inc/baselib/tabfile.h"
#include "../../../../../../Common/fusion/inc/attribute_data.h"
#include "../../../../../../Common/define/spell_def.h"
#include "../../../../../../Common/define/string_def.h"
#include "../../../../../../Common/fusion/inc/set_data.h"

namespace cqyh::gameworld::bindings {

void register_item_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto item_data_type = cqyh::lua::usertype<ITEM_DATA>(L, globals, "ITEM_DATA", "ITEM_DATA");
    item_data_type["m_nTemplateID"] = sol::property([](const ITEM_DATA& self) { return self.m_nTemplateID; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nTemplateID) value) { self.m_nTemplateID = value; });
    item_data_type["m_szName"] = cqyh::lua::string_property(&ITEM_DATA::m_szName);
    item_data_type["m_byItemLevel"] = sol::property([](const ITEM_DATA& self) { return self.m_byItemLevel; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byItemLevel) value) { self.m_byItemLevel = value; });
    item_data_type["m_byType"] = sol::property([](const ITEM_DATA& self) { return self.m_byType; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byType) value) { self.m_byType = value; });
    item_data_type["m_bySubType"] = sol::property([](const ITEM_DATA& self) { return self.m_bySubType; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_bySubType) value) { self.m_bySubType = value; });
    item_data_type["m_byUseInCombat"] = sol::property([](const ITEM_DATA& self) { return self.m_byUseInCombat; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byUseInCombat) value) { self.m_byUseInCombat = value; });
    item_data_type["m_byUseInArena"] = sol::property([](const ITEM_DATA& self) { return self.m_byUseInArena; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byUseInArena) value) { self.m_byUseInArena = value; });
    item_data_type["m_byRequireLevel"] = sol::property([](const ITEM_DATA& self) { return self.m_byRequireLevel; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byRequireLevel) value) { self.m_byRequireLevel = value; });
    item_data_type["m_byRequireClass"] = sol::property([](const ITEM_DATA& self) { return self.m_byRequireClass; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byRequireClass) value) { self.m_byRequireClass = value; });
    item_data_type["m_byRequireGender"] = sol::property([](const ITEM_DATA& self) { return self.m_byRequireGender; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byRequireGender) value) { self.m_byRequireGender = value; });
    item_data_type["m_byMaxEquip"] = sol::property([](const ITEM_DATA& self) { return self.m_byMaxEquip; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byMaxEquip) value) { self.m_byMaxEquip = value; });
    item_data_type["m_nMaxOwn"] = sol::property([](const ITEM_DATA& self) { return self.m_nMaxOwn; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nMaxOwn) value) { self.m_nMaxOwn = value; });
    item_data_type["m_byColor"] = sol::property([](const ITEM_DATA& self) { return self.m_byColor; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byColor) value) { self.m_byColor = value; });
    item_data_type["m_byBindType"] = sol::property([](const ITEM_DATA& self) { return self.m_byBindType; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byBindType) value) { self.m_byBindType = value; });
    item_data_type["m_byDurType"] = sol::property([](const ITEM_DATA& self) { return self.m_byDurType; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byDurType) value) { self.m_byDurType = value; });
    item_data_type["m_nDur"] = sol::property([](const ITEM_DATA& self) { return self.m_nDur; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nDur) value) { self.m_nDur = value; });
    item_data_type["m_nWeight"] = sol::property([](const ITEM_DATA& self) { return self.m_nWeight; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nWeight) value) { self.m_nWeight = value; });
    item_data_type["m_byCanDelete"] = sol::property([](const ITEM_DATA& self) { return self.m_byCanDelete; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byCanDelete) value) { self.m_byCanDelete = value; });
    item_data_type["m_byCanStorage"] = sol::property([](const ITEM_DATA& self) { return self.m_byCanStorage; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byCanStorage) value) { self.m_byCanStorage = value; });
    item_data_type["m_byCanSell"] = sol::property([](const ITEM_DATA& self) { return self.m_byCanSell; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byCanSell) value) { self.m_byCanSell = value; });
    item_data_type["m_nSellPrice"] = sol::property([](const ITEM_DATA& self) { return self.m_nSellPrice; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nSellPrice) value) { self.m_nSellPrice = value; });
    item_data_type["m_nSpellID"] = sol::property([](const ITEM_DATA& self) { return self.m_nSpellID; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nSpellID) value) { self.m_nSpellID = value; });
    item_data_type["m_nSpellLevel"] = sol::property([](const ITEM_DATA& self) { return self.m_nSpellLevel; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nSpellLevel) value) { self.m_nSpellLevel = value; });
    item_data_type["m_nSelfCoolDown"] = sol::property([](const ITEM_DATA& self) { return self.m_nSelfCoolDown; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nSelfCoolDown) value) { self.m_nSelfCoolDown = value; });
    item_data_type["m_nHandbookType"] = sol::property([](const ITEM_DATA& self) { return self.m_nHandbookType; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nHandbookType) value) { self.m_nHandbookType = value; });
    item_data_type["m_nHandbookIndex"] = sol::property([](const ITEM_DATA& self) { return self.m_nHandbookIndex; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nHandbookIndex) value) { self.m_nHandbookIndex = value; });
    auto item_data_cd_group_type = cqyh::lua::usertype<ITEM_DATA::CD_GROUP>(L, item_data_type, "CD_GROUP", "ITEM_DATA::CD_GROUP");
    item_data_cd_group_type["m_nCdGrpID"] = sol::property([](const ITEM_DATA::CD_GROUP& self) { return self.m_nCdGrpID; }, [](ITEM_DATA::CD_GROUP& self, decltype(ITEM_DATA::CD_GROUP::m_nCdGrpID) value) { self.m_nCdGrpID = value; });
    item_data_cd_group_type["m_nCdGrpValue"] = sol::property([](const ITEM_DATA::CD_GROUP& self) { return self.m_nCdGrpValue; }, [](ITEM_DATA::CD_GROUP& self, decltype(ITEM_DATA::CD_GROUP::m_nCdGrpValue) value) { self.m_nCdGrpValue = value; });
    item_data_type["m_nCdGrpCount"] = sol::property([](const ITEM_DATA& self) { return self.m_nCdGrpCount; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nCdGrpCount) value) { self.m_nCdGrpCount = value; });
    item_data_type["m_CdGrp"] = cqyh::lua::array_property(&ITEM_DATA::m_CdGrp);
    item_data_type["m_nDropLimitDuration"] = cqyh::lua::array_property(&ITEM_DATA::m_nDropLimitDuration);
    item_data_type["m_nDropLimitCount"] = cqyh::lua::array_property(&ITEM_DATA::m_nDropLimitCount);
    item_data_type["m_nDropFromServerStart"] = sol::property([](const ITEM_DATA& self) { return self.m_nDropFromServerStart; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nDropFromServerStart) value) { self.m_nDropFromServerStart = value; });
    item_data_type["m_byLog"] = sol::property([](const ITEM_DATA& self) { return self.m_byLog; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byLog) value) { self.m_byLog = value; });
    item_data_type["m_byStat"] = sol::property([](const ITEM_DATA& self) { return self.m_byStat; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byStat) value) { self.m_byStat = value; });
    item_data_type["m_byExpensiveItem"] = sol::property([](const ITEM_DATA& self) { return self.m_byExpensiveItem; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byExpensiveItem) value) { self.m_byExpensiveItem = value; });
    item_data_type["m_byDropBroadcast"] = sol::property([](const ITEM_DATA& self) { return self.m_byDropBroadcast; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byDropBroadcast) value) { self.m_byDropBroadcast = value; });
    item_data_type["m_bPkDrop"] = sol::property([](const ITEM_DATA& self) { return self.m_bPkDrop; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_bPkDrop) value) { self.m_bPkDrop = value; });
    item_data_type["m_bTeamAuction"] = sol::property([](const ITEM_DATA& self) { return self.m_bTeamAuction; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_bTeamAuction) value) { self.m_bTeamAuction = value; });
    item_data_type["m_bAuction"] = sol::property([](const ITEM_DATA& self) { return self.m_bAuction; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_bAuction) value) { self.m_bAuction = value; });
    item_data_type["m_nAuctionFee"] = cqyh::lua::array_property(&ITEM_DATA::m_nAuctionFee);
    item_data_type["m_byAuctionType"] = sol::property([](const ITEM_DATA& self) { return self.m_byAuctionType; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_byAuctionType) value) { self.m_byAuctionType = value; });
    item_data_type["m_nDefaultAuctionPrice"] = sol::property([](const ITEM_DATA& self) { return self.m_nDefaultAuctionPrice; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nDefaultAuctionPrice) value) { self.m_nDefaultAuctionPrice = value; });
    item_data_type["m_nPlayerDropTime"] = sol::property([](const ITEM_DATA& self) { return self.m_nPlayerDropTime; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nPlayerDropTime) value) { self.m_nPlayerDropTime = value; });
    item_data_type["m_nDropGroupID"] = sol::property([](const ITEM_DATA& self) { return self.m_nDropGroupID; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nDropGroupID) value) { self.m_nDropGroupID = value; });
    item_data_type["m_nShopTypeSell"] = sol::property([](const ITEM_DATA& self) { return self.m_nShopTypeSell; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nShopTypeSell) value) { self.m_nShopTypeSell = value; });
    item_data_type["m_nCanDecompose"] = sol::property([](const ITEM_DATA& self) { return self.m_nCanDecompose; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nCanDecompose) value) { self.m_nCanDecompose = value; });
    item_data_type["m_nTradeNeedIntimacy"] = sol::property([](const ITEM_DATA& self) { return self.m_nTradeNeedIntimacy; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nTradeNeedIntimacy) value) { self.m_nTradeNeedIntimacy = value; });
    item_data_type["m_nVarIndex"] = sol::property([](const ITEM_DATA& self) { return self.m_nVarIndex; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nVarIndex) value) { self.m_nVarIndex = value; });
    item_data_type["m_nClearGambleCount"] = sol::property([](const ITEM_DATA& self) { return self.m_nClearGambleCount; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nClearGambleCount) value) { self.m_nClearGambleCount = value; });
    item_data_type["m_nTradeOverWeight"] = sol::property([](const ITEM_DATA& self) { return self.m_nTradeOverWeight; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nTradeOverWeight) value) { self.m_nTradeOverWeight = value; });
    item_data_type["m_nResource"] = sol::property([](const ITEM_DATA& self) { return self.m_nResource; }, [](ITEM_DATA& self, decltype(ITEM_DATA::m_nResource) value) { self.m_nResource = value; });
    item_data_type["m_szScript"] = cqyh::lua::string_property(&ITEM_DATA::m_szScript);
    item_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, ITEM_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(ITEM_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    globals.set_function("GetItemData", [](signed int nTemplateID) -> decltype(auto) { return GetItemData(nTemplateID); });
    auto equip_data_type = cqyh::lua::usertype<EQUIP_DATA>(L, globals, "EQUIP_DATA", "EQUIP_DATA", sol::base_classes, sol::bases<ITEM_DATA>());
    equip_data_type["m_byEquipType"] = sol::property([](const EQUIP_DATA& self) { return self.m_byEquipType; }, [](EQUIP_DATA& self, decltype(EQUIP_DATA::m_byEquipType) value) { self.m_byEquipType = value; });
    equip_data_type["m_byIdentified"] = sol::property([](const EQUIP_DATA& self) { return self.m_byIdentified; }, [](EQUIP_DATA& self, decltype(EQUIP_DATA::m_byIdentified) value) { self.m_byIdentified = value; });
    equip_data_type["m_bySocketCountMin"] = sol::property([](const EQUIP_DATA& self) { return self.m_bySocketCountMin; }, [](EQUIP_DATA& self, decltype(EQUIP_DATA::m_bySocketCountMin) value) { self.m_bySocketCountMin = value; });
    equip_data_type["m_bySocketCountMax"] = sol::property([](const EQUIP_DATA& self) { return self.m_bySocketCountMax; }, [](EQUIP_DATA& self, decltype(EQUIP_DATA::m_bySocketCountMax) value) { self.m_bySocketCountMax = value; });
    equip_data_type["m_nFixAttr"] = cqyh::lua::array_property(&EQUIP_DATA::m_nFixAttr);
    equip_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, EQUIP_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(EQUIP_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_equip_data_type = cqyh::lua::usertype<CDataManager<EQUIP_DATA>>(L, globals, "CDataManager_EQUIP_DATA_", "CDataManager<EQUIP_DATA>");
    c_data_manager_equip_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<EQUIP_DATA>::GetInstance(); });
    c_data_manager_equip_data_type.set_function("GetDataCount", [](CDataManager<EQUIP_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_equip_data_type.set_function("GetData", [](CDataManager<EQUIP_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_equip_data_type.set_function("GetID", [](CDataManager<EQUIP_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_equip_data_type.set_function("GetFirstData", [](CDataManager<EQUIP_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_equip_data_type.set_function("GetNextData", [](CDataManager<EQUIP_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
    auto c_data_manager_item_data_type = cqyh::lua::usertype<CDataManager<ITEM_DATA>>(L, globals, "CDataManager_ITEM_DATA_", "CDataManager<ITEM_DATA>");
    c_data_manager_item_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<ITEM_DATA>::GetInstance(); });
    c_data_manager_item_data_type.set_function("GetDataCount", [](CDataManager<ITEM_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_item_data_type.set_function("GetData", [](CDataManager<ITEM_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_item_data_type.set_function("GetID", [](CDataManager<ITEM_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_item_data_type.set_function("GetFirstData", [](CDataManager<ITEM_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_item_data_type.set_function("GetNextData", [](CDataManager<ITEM_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
