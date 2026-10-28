#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/item_data.h"
#include "../../../../inc/shop_data.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"

namespace cqyh::fusion::bindings {

void register_shop_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto shop_data_type = cqyh::lua::usertype<SHOP_DATA>(L, globals, "SHOP_DATA", "SHOP_DATA");
    shop_data_type["m_nShopID"] = sol::property([](const SHOP_DATA& self) { return self.m_nShopID; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nShopID) value) { self.m_nShopID = value; });
    shop_data_type["m_nIndex"] = sol::property([](const SHOP_DATA& self) { return self.m_nIndex; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nIndex) value) { self.m_nIndex = value; });
    shop_data_type["m_szShopName"] = cqyh::lua::string_property(&SHOP_DATA::m_szShopName);
    shop_data_type["m_nItemID"] = sol::property([](const SHOP_DATA& self) { return self.m_nItemID; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nItemID) value) { self.m_nItemID = value; });
    shop_data_type["m_nItemCount"] = sol::property([](const SHOP_DATA& self) { return self.m_nItemCount; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nItemCount) value) { self.m_nItemCount = value; });
    shop_data_type["m_nCostItemID1"] = sol::property([](const SHOP_DATA& self) { return self.m_nCostItemID1; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nCostItemID1) value) { self.m_nCostItemID1 = value; });
    shop_data_type["m_nCostValue1"] = sol::property([](const SHOP_DATA& self) { return self.m_nCostValue1; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nCostValue1) value) { self.m_nCostValue1 = value; });
    shop_data_type["m_nCostItemID2"] = sol::property([](const SHOP_DATA& self) { return self.m_nCostItemID2; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nCostItemID2) value) { self.m_nCostItemID2 = value; });
    shop_data_type["m_nCostValue2"] = sol::property([](const SHOP_DATA& self) { return self.m_nCostValue2; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nCostValue2) value) { self.m_nCostValue2 = value; });
    shop_data_type["m_nRequireForceID"] = sol::property([](const SHOP_DATA& self) { return self.m_nRequireForceID; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nRequireForceID) value) { self.m_nRequireForceID = value; });
    shop_data_type["m_nReputation"] = sol::property([](const SHOP_DATA& self) { return self.m_nReputation; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nReputation) value) { self.m_nReputation = value; });
    shop_data_type["m_nRequireGuildBuildingID"] = sol::property([](const SHOP_DATA& self) { return self.m_nRequireGuildBuildingID; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nRequireGuildBuildingID) value) { self.m_nRequireGuildBuildingID = value; });
    shop_data_type["m_nBuildingLevel"] = sol::property([](const SHOP_DATA& self) { return self.m_nBuildingLevel; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nBuildingLevel) value) { self.m_nBuildingLevel = value; });
    shop_data_type["m_nShopTypeSell"] = sol::property([](const SHOP_DATA& self) { return self.m_nShopTypeSell; }, [](SHOP_DATA& self, decltype(SHOP_DATA::m_nShopTypeSell) value) { self.m_nShopTypeSell = value; });
    shop_data_type["m_pItemTemplate"] = sol::readonly(&SHOP_DATA::m_pItemTemplate);
    shop_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, SHOP_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(SHOP_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_shop_data_type = cqyh::lua::usertype<CDataManager<SHOP_DATA>>(L, globals, "CDataManager_SHOP_DATA_", "CDataManager<SHOP_DATA>");
    c_data_manager_shop_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<SHOP_DATA>::GetInstance(); });
    c_data_manager_shop_data_type.set_function("GetDataCount", [](CDataManager<SHOP_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_shop_data_type.set_function("GetData", [](CDataManager<SHOP_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_shop_data_type.set_function("GetID", [](CDataManager<SHOP_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_shop_data_type.set_function("GetFirstData", [](CDataManager<SHOP_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_shop_data_type.set_function("GetNextData", [](CDataManager<SHOP_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
