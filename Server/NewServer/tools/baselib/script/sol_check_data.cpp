#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../inc/baselib/checkdata.h"
#include "../../../inc/baselib/tabfile.h"

int sol_check_data_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CCheckData>(L, globals, "CCheckData", "CCheckData");
    type1.set_function("new", [](sol::table) -> decltype(auto) { return new CCheckData(); });
    type1.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<CCheckData>(new CCheckData()); });
    type1.set_function("delete", [](CCheckData* self) -> decltype(auto) { delete self; });
    type1.set_function("Check", [](CCheckData* self, const char* pPath, const char* pFoledrName) -> decltype(auto) { return self->Check(pPath,pFoledrName); });
    type1.set_function("GetDataByName", [](CCheckData* self, const char* pName) -> decltype(auto) { return self->GetDataByName(pName); });
    type1.set_function("GetTabRowCount", [](CCheckData* self, CTabFile* pTab) -> decltype(auto) { return self->GetTabRowCount(pTab); });
    type1.set_function("GetNumber", [](CCheckData* self, CTabFile* pTab, const char* pCol_arg, INT32 nRow) -> decltype(auto) { char* pCol = const_cast<char*>(pCol_arg); return self->GetNumber(pTab,pCol,nRow); });
    type1.set_function("PrintInfo", [](CCheckData* self, const char* pInfo_arg) -> decltype(auto) { char* pInfo = const_cast<char*>(pInfo_arg); self->PrintInfo(pInfo); });
    type1.set_function("PrintWrn", [](CCheckData* self, const char* pWrn_arg) -> decltype(auto) { char* pWrn = const_cast<char*>(pWrn_arg); self->PrintWrn(pWrn); });
    type1.set_function("GetInstance", []() -> decltype(auto) { return CCheckData::GetInstance(); });
    return 1;
}
