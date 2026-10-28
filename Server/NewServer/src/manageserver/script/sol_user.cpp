#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "client/user.h"
#include "client/usermgr.h"
#include "../../../inc/baselib/base_list.h"

int sol_user_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["USER_STATE_INVALID"] = static_cast<lua_Number>(USER_STATE_INVALID);
    globals["USER_STATE_AUTHED"] = static_cast<lua_Number>(USER_STATE_AUTHED);
    globals["USER_STATE_QUEUEFINISHED"] = static_cast<lua_Number>(USER_STATE_QUEUEFINISHED);
    globals["USER_STATE_LOGIN_WAIT_CREATE_SCENE"] = static_cast<lua_Number>(USER_STATE_LOGIN_WAIT_CREATE_SCENE);
    globals["USER_STATE_LOGIN_PRE_ENTER_GS"] = static_cast<lua_Number>(USER_STATE_LOGIN_PRE_ENTER_GS);
    globals["USER_STATE_LOGIN_GSREADY"] = static_cast<lua_Number>(USER_STATE_LOGIN_GSREADY);
    globals["USER_STATE_INGAME"] = static_cast<lua_Number>(USER_STATE_INGAME);
    globals["USER_STATE_EXIT_GS_PREENTER"] = static_cast<lua_Number>(USER_STATE_EXIT_GS_PREENTER);
    globals["USER_STATE_EXIT_GS"] = static_cast<lua_Number>(USER_STATE_EXIT_GS);
    globals["USER_STATE_EXIT_2GS"] = static_cast<lua_Number>(USER_STATE_EXIT_2GS);
    globals["USER_STATE_WAIT_EXIT_DB"] = static_cast<lua_Number>(USER_STATE_WAIT_EXIT_DB);
    globals["USER_STATE_EXIT_DB"] = static_cast<lua_Number>(USER_STATE_EXIT_DB);
    globals["USER_STATE_EXIT_GS_RETURN"] = static_cast<lua_Number>(USER_STATE_EXIT_GS_RETURN);
    globals["USER_STATE_EXIT_DB_RETURN"] = static_cast<lua_Number>(USER_STATE_EXIT_DB_RETURN);
    globals["USER_STATE_JUMP_EXIT_TGT"] = static_cast<lua_Number>(USER_STATE_JUMP_EXIT_TGT);
    globals["USER_STATE_JUMP_WAIT_CREATE_SCENE"] = static_cast<lua_Number>(USER_STATE_JUMP_WAIT_CREATE_SCENE);
    globals["USER_STATE_JUMP_PRE_ENTER_GS"] = static_cast<lua_Number>(USER_STATE_JUMP_PRE_ENTER_GS);
    globals["USER_STATE_JUMP_EXIT_SRC"] = static_cast<lua_Number>(USER_STATE_JUMP_EXIT_SRC);
    globals["USER_STATE_JUMP_ENTER_TARGET"] = static_cast<lua_Number>(USER_STATE_JUMP_ENTER_TARGET);
    globals["USER_STATE_JUMP_GSREADY"] = static_cast<lua_Number>(USER_STATE_JUMP_GSREADY);
    auto type1 = cqyh::lua::usertype<MS_USER>(L, globals, "MS_USER", "MS_USER");
    type1["szUserName"] = cqyh::lua::string_property(&MS_USER::szUserName);
    type1["dwCliSessionID"] = sol::property([](const MS_USER& self) { return self.dwCliSessionID; }, [](MS_USER& self, decltype(MS_USER::dwCliSessionID) value) { self.dwCliSessionID = value; });
    type1["dwClientIp"] = sol::property([](const MS_USER& self) { return self.dwClientIp; }, [](MS_USER& self, decltype(MS_USER::dwClientIp) value) { self.dwClientIp = value; });
    type1["bIpWhiteList"] = sol::property([](const MS_USER& self) { return static_cast<bool>(self.bIpWhiteList); }, [](MS_USER& self, bool value) { self.bIpWhiteList = value; });
    type1["bUserWhiteList"] = sol::property([](const MS_USER& self) { return static_cast<bool>(self.bUserWhiteList); }, [](MS_USER& self, bool value) { self.bUserWhiteList = value; });
    type1["szMac"] = cqyh::lua::array_property(&MS_USER::szMac);
    type1["WaitListNode"] = &MS_USER::WaitListNode;
    type1["dwLoginTime"] = sol::property([](const MS_USER& self) { return self.dwLoginTime; }, [](MS_USER& self, decltype(MS_USER::dwLoginTime) value) { self.dwLoginTime = value; });
    type1["szOASessionID"] = cqyh::lua::string_property(&MS_USER::szOASessionID);
    type1["szPGT"] = cqyh::lua::string_property(&MS_USER::szPGT);
    type1["bAdult"] = sol::property([](const MS_USER& self) { return self.bAdult; }, [](MS_USER& self, decltype(MS_USER::bAdult) value) { self.bAdult = value; });
    type1["byFcmState"] = sol::property([](const MS_USER& self) { return self.byFcmState; }, [](MS_USER& self, decltype(MS_USER::byFcmState) value) { self.byFcmState = value; });
    type1["eState"] = sol::property([](const MS_USER& self) { return self.eState; }, [](MS_USER& self, decltype(MS_USER::eState) value) { self.eState = value; });
    type1["qwTimer"] = &MS_USER::qwTimer;
    type1["dwCurRoleID"] = sol::property([](const MS_USER& self) { return self.dwCurRoleID; }, [](MS_USER& self, decltype(MS_USER::dwCurRoleID) value) { self.dwCurRoleID = value; });
    type1["nShutdownType"] = sol::property([](const MS_USER& self) { return self.nShutdownType; }, [](MS_USER& self, decltype(MS_USER::nShutdownType) value) { self.nShutdownType = value; });
    type1["bKicked"] = sol::property([](const MS_USER& self) { return static_cast<bool>(self.bKicked); }, [](MS_USER& self, bool value) { self.bKicked = value; });
    type1["bFreeMode"] = sol::property([](const MS_USER& self) { return static_cast<bool>(self.bFreeMode); }, [](MS_USER& self, bool value) { self.bFreeMode = value; });
    type1["dwFreeModeLastCheckTime"] = sol::property([](const MS_USER& self) { return self.dwFreeModeLastCheckTime; }, [](MS_USER& self, decltype(MS_USER::dwFreeModeLastCheckTime) value) { self.dwFreeModeLastCheckTime = value; });
    type1["nDianquan"] = sol::property([](const MS_USER& self) { return self.nDianquan; }, [](MS_USER& self, decltype(MS_USER::nDianquan) value) { self.nDianquan = value; });
    type1["nTimeLeft"] = sol::property([](const MS_USER& self) { return self.nTimeLeft; }, [](MS_USER& self, decltype(MS_USER::nTimeLeft) value) { self.nTimeLeft = value; });
    type1["dwBeginTime"] = sol::property([](const MS_USER& self) { return self.dwBeginTime; }, [](MS_USER& self, decltype(MS_USER::dwBeginTime) value) { self.dwBeginTime = value; });
    type1.set_function("SetFreeMode", [](MS_USER* self, bool fm) -> decltype(auto) { self->SetFreeMode(fm); });
    auto type2 = cqyh::lua::usertype<CUserMgr>(L, globals, "CUserMgr", "CUserMgr");
    type2.set_function("GetInstance", []() -> decltype(auto) { return CUserMgr::GetInstance(); });
    type2.set_function("Count", [](CUserMgr* self) -> decltype(auto) { return self->Count(); });
    type2.set_function("GetCountPerGroup", [](CUserMgr* self, signed int nServerGroup) -> decltype(auto) { return self->GetCountPerGroup(nServerGroup); });
    type2.set_function("GetCountByIP", [](CUserMgr* self, const char* pcszIDAddress) -> decltype(auto) { return self->GetCountByIP(pcszIDAddress); });
    return 1;
}
