#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "role_data.h"
#include "../../../inc/baselib/base_list.h"

int sol_role_data_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<MS_ROLE_DATA>(L, globals, "MS_ROLE_DATA", "MS_ROLE_DATA");
    type1["dwRoleID"] = sol::property([](const MS_ROLE_DATA& self) { return self.dwRoleID; }, [](MS_ROLE_DATA& self, decltype(MS_ROLE_DATA::dwRoleID) value) { self.dwRoleID = value; });
    type1["szRoleName"] = cqyh::lua::array_property(&MS_ROLE_DATA::szRoleName);
    type1["byGroup"] = sol::property([](const MS_ROLE_DATA& self) { return self.byGroup; }, [](MS_ROLE_DATA& self, decltype(MS_ROLE_DATA::byGroup) value) { self.byGroup = value; });
    type1["byLevel"] = sol::property([](const MS_ROLE_DATA& self) { return self.byLevel; }, [](MS_ROLE_DATA& self, decltype(MS_ROLE_DATA::byLevel) value) { self.byLevel = value; });
    type1["bySex"] = sol::property([](const MS_ROLE_DATA& self) { return self.bySex; }, [](MS_ROLE_DATA& self, decltype(MS_ROLE_DATA::bySex) value) { self.bySex = value; });
    type1["byClass"] = sol::property([](const MS_ROLE_DATA& self) { return self.byClass; }, [](MS_ROLE_DATA& self, decltype(MS_ROLE_DATA::byClass) value) { self.byClass = value; });
    type1["nLastLoginTime"] = sol::property([](const MS_ROLE_DATA& self) { return self.nLastLoginTime; }, [](MS_ROLE_DATA& self, decltype(MS_ROLE_DATA::nLastLoginTime) value) { self.nLastLoginTime = value; });
    type1["nSceneTempID"] = sol::property([](const MS_ROLE_DATA& self) { return self.nSceneTempID; }, [](MS_ROLE_DATA& self, decltype(MS_ROLE_DATA::nSceneTempID) value) { self.nSceneTempID = value; });
    type1["nSceneID"] = sol::property([](const MS_ROLE_DATA& self) { return self.nSceneID; }, [](MS_ROLE_DATA& self, decltype(MS_ROLE_DATA::nSceneID) value) { self.nSceneID = value; });
    type1["dwTeamID"] = sol::property([](const MS_ROLE_DATA& self) { return self.dwTeamID; }, [](MS_ROLE_DATA& self, decltype(MS_ROLE_DATA::dwTeamID) value) { self.dwTeamID = value; });
    type1["dwMailCounts"] = sol::property([](const MS_ROLE_DATA& self) { return self.dwMailCounts; }, [](MS_ROLE_DATA& self, decltype(MS_ROLE_DATA::dwMailCounts) value) { self.dwMailCounts = value; });
    type1["lstMails"] = &MS_ROLE_DATA::lstMails;
    type1["dwGuildID"] = sol::property([](const MS_ROLE_DATA& self) { return self.dwGuildID; }, [](MS_ROLE_DATA& self, decltype(MS_ROLE_DATA::dwGuildID) value) { self.dwGuildID = value; });
    type1["dwJoinGuildCD"] = sol::property([](const MS_ROLE_DATA& self) { return self.dwJoinGuildCD; }, [](MS_ROLE_DATA& self, decltype(MS_ROLE_DATA::dwJoinGuildCD) value) { self.dwJoinGuildCD = value; });
    return 1;
}
