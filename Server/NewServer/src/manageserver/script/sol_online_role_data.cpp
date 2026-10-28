#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "onlinerole/online_role_data.h"
#include "onlinerole/online_role_data_mgr.h"
#include "../role_data.h"
#include "../client/user.h"

int sol_online_role_data_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<MS_ONLINE_ROLE_DATA>(L, globals, "MS_ONLINE_ROLE_DATA", "MS_ONLINE_ROLE_DATA");
    type1["pUser"] = &MS_ONLINE_ROLE_DATA::pUser;
    type1["pRoleData"] = &MS_ONLINE_ROLE_DATA::pRoleData;
    type1["nGMLevel"] = sol::property([](const MS_ONLINE_ROLE_DATA& self) { return self.nGMLevel; }, [](MS_ONLINE_ROLE_DATA& self, decltype(MS_ONLINE_ROLE_DATA::nGMLevel) value) { self.nGMLevel = value; });
    type1["nCurrentHp"] = sol::property([](const MS_ONLINE_ROLE_DATA& self) { return self.nCurrentHp; }, [](MS_ONLINE_ROLE_DATA& self, decltype(MS_ONLINE_ROLE_DATA::nCurrentHp) value) { self.nCurrentHp = value; });
    type1["nCurrentMp"] = sol::property([](const MS_ONLINE_ROLE_DATA& self) { return self.nCurrentMp; }, [](MS_ONLINE_ROLE_DATA& self, decltype(MS_ONLINE_ROLE_DATA::nCurrentMp) value) { self.nCurrentMp = value; });
    type1["nMaxHp"] = sol::property([](const MS_ONLINE_ROLE_DATA& self) { return self.nMaxHp; }, [](MS_ONLINE_ROLE_DATA& self, decltype(MS_ONLINE_ROLE_DATA::nMaxHp) value) { self.nMaxHp = value; });
    type1["nMaxMp"] = sol::property([](const MS_ONLINE_ROLE_DATA& self) { return self.nMaxMp; }, [](MS_ONLINE_ROLE_DATA& self, decltype(MS_ONLINE_ROLE_DATA::nMaxMp) value) { self.nMaxMp = value; });
    type1["dwLastSpeakTime"] = sol::property([](const MS_ONLINE_ROLE_DATA& self) { return self.dwLastSpeakTime; }, [](MS_ONLINE_ROLE_DATA& self, decltype(MS_ONLINE_ROLE_DATA::dwLastSpeakTime) value) { self.dwLastSpeakTime = value; });
    type1["dwLastQueryRoleInfoTime"] = sol::property([](const MS_ONLINE_ROLE_DATA& self) { return self.dwLastQueryRoleInfoTime; }, [](MS_ONLINE_ROLE_DATA& self, decltype(MS_ONLINE_ROLE_DATA::dwLastQueryRoleInfoTime) value) { self.dwLastQueryRoleInfoTime = value; });
    type1["byQueryRoleInfoCount"] = sol::property([](const MS_ONLINE_ROLE_DATA& self) { return self.byQueryRoleInfoCount; }, [](MS_ONLINE_ROLE_DATA& self, decltype(MS_ONLINE_ROLE_DATA::byQueryRoleInfoCount) value) { self.byQueryRoleInfoCount = value; });
    type1["dwCliSessionID"] = sol::property([](const MS_ONLINE_ROLE_DATA& self) { return self.dwCliSessionID; }, [](MS_ONLINE_ROLE_DATA& self, decltype(MS_ONLINE_ROLE_DATA::dwCliSessionID) value) { self.dwCliSessionID = value; });
    type1["dwGSSessionID"] = sol::property([](const MS_ONLINE_ROLE_DATA& self) { return self.dwGSSessionID; }, [](MS_ONLINE_ROLE_DATA& self, decltype(MS_ONLINE_ROLE_DATA::dwGSSessionID) value) { self.dwGSSessionID = value; });
    type1["dwSaveTime"] = sol::property([](const MS_ONLINE_ROLE_DATA& self) { return self.dwSaveTime; }, [](MS_ONLINE_ROLE_DATA& self, decltype(MS_ONLINE_ROLE_DATA::dwSaveTime) value) { self.dwSaveTime = value; });
    type1["dwMasterCD"] = sol::property([](const MS_ONLINE_ROLE_DATA& self) { return self.dwMasterCD; }, [](MS_ONLINE_ROLE_DATA& self, decltype(MS_ONLINE_ROLE_DATA::dwMasterCD) value) { self.dwMasterCD = value; });
    auto type2 = cqyh::lua::usertype<COnlineRoleDataMgr>(L, globals, "COnlineRoleDataMgr", "COnlineRoleDataMgr");
    type2.set_function("GetInstance", []() -> decltype(auto) { return COnlineRoleDataMgr::GetInstance(); });
    type2.set_function("FindOnlineRoleByName", [](COnlineRoleDataMgr* self, const char* pcszRoleName) -> decltype(auto) { return self->FindOnlineRoleByName(pcszRoleName); });
    type2.set_function("FindOnlineRoleByRoleID", [](COnlineRoleDataMgr* self, unsigned int dwRoleID) -> decltype(auto) { return self->FindOnlineRoleByRoleID(dwRoleID); });
    type2.set_function("FindOnlineRoleByNameInGroup", [](COnlineRoleDataMgr* self, const char* pcszRoleName, unsigned char byGroupID) -> decltype(auto) { return self->FindOnlineRoleByNameInGroup(pcszRoleName,byGroupID); });
    type2.set_function("FindOnlineRoleByRoleIDInGroup", [](COnlineRoleDataMgr* self, unsigned int dwRoleID, unsigned char byGroupID) -> decltype(auto) { return self->FindOnlineRoleByRoleIDInGroup(dwRoleID,byGroupID); });
    type2.set_function("GetRoleNumberCount", [](COnlineRoleDataMgr* self, unsigned char byGroupIndex) -> decltype(auto) { return self->GetRoleNumberCount(byGroupIndex); });
    type2.set_function("GetRoleNumberCount", sol::overload([](COnlineRoleDataMgr* self) -> decltype(auto) { return self->GetRoleNumberCount(); }, [](COnlineRoleDataMgr* self, unsigned char byGroupIndex) -> decltype(auto) { return self->GetRoleNumberCount(byGroupIndex); }));
    return 1;
}
