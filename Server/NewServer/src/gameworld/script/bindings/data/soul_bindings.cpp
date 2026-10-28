#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/fusion/inc/soul_data.h"
#include "../../../../../inc/baselib/data_manager.h"
#include "../../../../../inc/baselib/tabfile.h"
#include "../../../../../../Common/fusion/inc/attribute_data.h"

namespace cqyh::gameworld::bindings {

void register_soul_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto soul_data_type = cqyh::lua::usertype<SOUL_DATA>(L, globals, "SOUL_DATA", "SOUL_DATA");
    soul_data_type["m_nTemplateID"] = sol::property([](const SOUL_DATA& self) { return self.m_nTemplateID; }, [](SOUL_DATA& self, decltype(SOUL_DATA::m_nTemplateID) value) { self.m_nTemplateID = value; });
    soul_data_type["m_nAttrID"] = sol::property([](const SOUL_DATA& self) { return self.m_nAttrID; }, [](SOUL_DATA& self, decltype(SOUL_DATA::m_nAttrID) value) { self.m_nAttrID = value; });
    soul_data_type["m_nMatchSocket"] = sol::property([](const SOUL_DATA& self) { return self.m_nMatchSocket; }, [](SOUL_DATA& self, decltype(SOUL_DATA::m_nMatchSocket) value) { self.m_nMatchSocket = value; });
    soul_data_type["m_nSoulLevel"] = sol::property([](const SOUL_DATA& self) { return self.m_nSoulLevel; }, [](SOUL_DATA& self, decltype(SOUL_DATA::m_nSoulLevel) value) { self.m_nSoulLevel = value; });
    soul_data_type["m_nPriceValue"] = sol::property([](const SOUL_DATA& self) { return self.m_nPriceValue; }, [](SOUL_DATA& self, decltype(SOUL_DATA::m_nPriceValue) value) { self.m_nPriceValue = value; });
    soul_data_type["m_nUpgradeSoulID"] = sol::property([](const SOUL_DATA& self) { return self.m_nUpgradeSoulID; }, [](SOUL_DATA& self, decltype(SOUL_DATA::m_nUpgradeSoulID) value) { self.m_nUpgradeSoulID = value; });
    soul_data_type["m_nRemovePrice"] = sol::property([](const SOUL_DATA& self) { return self.m_nRemovePrice; }, [](SOUL_DATA& self, decltype(SOUL_DATA::m_nRemovePrice) value) { self.m_nRemovePrice = value; });
    soul_data_type["m_pAttrData"] = sol::readonly(&SOUL_DATA::m_pAttrData);
    soul_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, SOUL_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(SOUL_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_soul_data_type = cqyh::lua::usertype<CDataManager<SOUL_DATA>>(L, globals, "CDataManager_SOUL_DATA_", "CDataManager<SOUL_DATA>");
    c_data_manager_soul_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<SOUL_DATA>::GetInstance(); });
    c_data_manager_soul_data_type.set_function("GetDataCount", [](CDataManager<SOUL_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_soul_data_type.set_function("GetData", [](CDataManager<SOUL_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_soul_data_type.set_function("GetID", [](CDataManager<SOUL_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_soul_data_type.set_function("GetFirstData", [](CDataManager<SOUL_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_soul_data_type.set_function("GetNextData", [](CDataManager<SOUL_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
