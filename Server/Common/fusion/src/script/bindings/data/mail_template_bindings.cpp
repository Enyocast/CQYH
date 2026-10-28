#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/mail_template_data.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"

namespace cqyh::fusion::bindings {

void register_mail_template_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto mail_template_data_type = cqyh::lua::usertype<MAIL_TEMPLATE_DATA>(L, globals, "MAIL_TEMPLATE_DATA", "MAIL_TEMPLATE_DATA");
    mail_template_data_type["m_nTemplateID"] = sol::property([](const MAIL_TEMPLATE_DATA& self) { return self.m_nTemplateID; }, [](MAIL_TEMPLATE_DATA& self, decltype(MAIL_TEMPLATE_DATA::m_nTemplateID) value) { self.m_nTemplateID = value; });
    mail_template_data_type["m_szMailSubject"] = cqyh::lua::string_property(&MAIL_TEMPLATE_DATA::m_szMailSubject);
    mail_template_data_type["m_szMailContent"] = cqyh::lua::string_property(&MAIL_TEMPLATE_DATA::m_szMailContent);
    mail_template_data_type["m_nItemID"] = sol::property([](const MAIL_TEMPLATE_DATA& self) { return self.m_nItemID; }, [](MAIL_TEMPLATE_DATA& self, decltype(MAIL_TEMPLATE_DATA::m_nItemID) value) { self.m_nItemID = value; });
    mail_template_data_type["m_nItemCount"] = sol::property([](const MAIL_TEMPLATE_DATA& self) { return self.m_nItemCount; }, [](MAIL_TEMPLATE_DATA& self, decltype(MAIL_TEMPLATE_DATA::m_nItemCount) value) { self.m_nItemCount = value; });
    mail_template_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, MAIL_TEMPLATE_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(MAIL_TEMPLATE_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_mail_template_data_type = cqyh::lua::usertype<CDataManager<MAIL_TEMPLATE_DATA>>(L, globals, "CDataManager_MAIL_TEMPLATE_DATA_", "CDataManager<MAIL_TEMPLATE_DATA>");
    c_data_manager_mail_template_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<MAIL_TEMPLATE_DATA>::GetInstance(); });
    c_data_manager_mail_template_data_type.set_function("GetDataCount", [](CDataManager<MAIL_TEMPLATE_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_mail_template_data_type.set_function("GetData", [](CDataManager<MAIL_TEMPLATE_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_mail_template_data_type.set_function("GetID", [](CDataManager<MAIL_TEMPLATE_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_mail_template_data_type.set_function("GetFirstData", [](CDataManager<MAIL_TEMPLATE_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_mail_template_data_type.set_function("GetNextData", [](CDataManager<MAIL_TEMPLATE_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
