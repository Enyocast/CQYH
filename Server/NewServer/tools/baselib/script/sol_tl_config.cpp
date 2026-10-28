#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../inc/baselib/log.h"
#include "../../inc/baselib/tl_config.h"

int sol_tl_config_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["lotNone"] = static_cast<lua_Number>(lotNone);
    globals["lotConsole"] = static_cast<lua_Number>(lotConsole);
    globals["lotFile"] = static_cast<lua_Number>(lotFile);
    globals["lotTrace"] = static_cast<lua_Number>(lotTrace);
    globals["lotCustom"] = static_cast<lua_Number>(lotCustom);
    globals["lotAll"] = static_cast<lua_Number>(lotAll);
    globals["lltNone"] = static_cast<lua_Number>(lltNone);
    globals["lltDebug"] = static_cast<lua_Number>(lltDebug);
    globals["lltInfo"] = static_cast<lua_Number>(lltInfo);
    globals["lltWarning"] = static_cast<lua_Number>(lltWarning);
    globals["lltError"] = static_cast<lua_Number>(lltError);
    globals["lltCritical"] = static_cast<lua_Number>(lltCritical);
    globals["lltSDU"] = static_cast<lua_Number>(lltSDU);
    globals["lltMove"] = static_cast<lua_Number>(lltMove);
    globals["lltLua"] = static_cast<lua_Number>(lltLua);
    globals["lltSpell"] = static_cast<lua_Number>(lltSpell);
    globals["lltSys"] = static_cast<lua_Number>(lltSys);
    globals["lltAll"] = static_cast<lua_Number>(lltAll);
    globals["PING_SVR_INTERNAL"] = static_cast<lua_Number>(PING_SVR_INTERNAL);
    globals["PING_SVR_TIMEOUT"] = static_cast<lua_Number>(PING_SVR_TIMEOUT);
    globals["RECONNECT_TIME"] = static_cast<lua_Number>(RECONNECT_TIME);
    globals["SMALL_PACKET_COUNT"] = static_cast<lua_Number>(SMALL_PACKET_COUNT);
    globals["LARGE_PACKET_COUNT"] = static_cast<lua_Number>(LARGE_PACKET_COUNT);
    globals["MAX_ACCEPTOR"] = static_cast<lua_Number>(MAX_ACCEPTOR);
    globals["MAX_CONNECTOR"] = static_cast<lua_Number>(MAX_CONNECTOR);
    globals["MAX_SESSION_COUNT"] = static_cast<lua_Number>(MAX_SESSION_COUNT);
    globals["SEND_BUF_SIZE"] = static_cast<lua_Number>(SEND_BUF_SIZE);
    globals["RECV_BUF_SIZE"] = static_cast<lua_Number>(RECV_BUF_SIZE);
    globals["PACKET_BUFFER_SIZE"] = static_cast<lua_Number>(PACKET_BUFFER_SIZE);
    globals["RELOGIN_INTERNAL"] = static_cast<lua_Number>(RELOGIN_INTERNAL);
    globals["CMD_DATA_POOL_COUNT"] = static_cast<lua_Number>(CMD_DATA_POOL_COUNT);
    globals["GM_MAX_SERVER_COUNT"] = static_cast<lua_Number>(GM_MAX_SERVER_COUNT);
    auto type1 = cqyh::lua::usertype<GM_GROUP_DATA>(L, globals, "GM_GROUP_DATA", "GM_GROUP_DATA");
    type1["szGroupName"] = cqyh::lua::string_property(&GM_GROUP_DATA::szGroupName);
    auto type2 = cqyh::lua::usertype<GM_SVR>(L, globals, "GM_SVR", "GM_SVR");
    type2["nSvrID"] = sol::property([](const GM_SVR& self) { return self.nSvrID; }, [](GM_SVR& self, decltype(GM_SVR::nSvrID) value) { self.nSvrID = value; });
    type2["szName"] = cqyh::lua::string_property(&GM_SVR::szName);
    type2["szAddr"] = cqyh::lua::string_property(&GM_SVR::szAddr);
    type2["dwPort"] = sol::property([](const GM_SVR& self) { return self.dwPort; }, [](GM_SVR& self, decltype(GM_SVR::dwPort) value) { self.dwPort = value; });
    type2["groupList"] = cqyh::lua::array_property(&GM_SVR::groupList);
    auto type3 = cqyh::lua::usertype<TL_CONFIG>(L, globals, "TL_CONFIG", "TL_CONFIG");
    auto type4 = cqyh::lua::usertype<TL_CONFIG::GM_SVR_LIST>(L, type3, "GM_SVR_LIST", "TL_CONFIG::GM_SVR_LIST");
    type4["nSvrNum"] = sol::property([](const TL_CONFIG::GM_SVR_LIST& self) { return self.nSvrNum; }, [](TL_CONFIG::GM_SVR_LIST& self, decltype(TL_CONFIG::GM_SVR_LIST::nSvrNum) value) { self.nSvrNum = value; });
    type4["arrGMList"] = cqyh::lua::array_property(&TL_CONFIG::GM_SVR_LIST::arrGMList);
    type3["ServerList"] = &TL_CONFIG::ServerList;
    globals.set_function("GetTLConfig", []() -> decltype(auto) { return GetTLConfig(); });
    return 1;
}
