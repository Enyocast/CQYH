#pragma once
#include "sol_bindings.h"

inline int sol_gm_config_open(lua_State* L) {
    sol::state_view lua(L);
    auto address = cqyh::lua::usertype<SVR_ADDR>(L, lua.globals(), "SVR_ADDR", "SVR_ADDR");
    address["nSvrID"] = &SVR_ADDR::nSvrID;
    address["szName"] = cqyh::lua::string_property(&SVR_ADDR::szName);
    address["szAddr"] = cqyh::lua::string_property(&SVR_ADDR::szAddr);
    address["dwPort"] = &SVR_ADDR::dwPort;
    auto config = cqyh::lua::usertype<GM_CONFIG>(L, lua.globals(), "GM_CONFIG", "GM_CONFIG");
    auto common = cqyh::lua::usertype<GM_CONFIG::GM_COMMON_CONFIG>(L, config, "GM_COMMON_CONFIG", "GM_CONFIG::GM_COMMON_CONFIG");
    common["nPingSvrInternal"] = &GM_CONFIG::GM_COMMON_CONFIG::nPingSvrInternal;
    common["nPingSvrTimeout"] = &GM_CONFIG::GM_COMMON_CONFIG::nPingSvrTimeout;
    common["nSmallPacketCount"] = &GM_CONFIG::GM_COMMON_CONFIG::nSmallPacketCount;
    common["nLargePacketCount"] = &GM_CONFIG::GM_COMMON_CONFIG::nLargePacketCount;
    common["nMaxAcceptor"] = &GM_CONFIG::GM_COMMON_CONFIG::nMaxAcceptor;
    common["nMaxConnector"] = &GM_CONFIG::GM_COMMON_CONFIG::nMaxConnector;
    common["nMaxSessionCount"] = &GM_CONFIG::GM_COMMON_CONFIG::nMaxSessionCount;
    common["nSendBufSize"] = &GM_CONFIG::GM_COMMON_CONFIG::nSendBufSize;
    common["nRecvBufSize"] = &GM_CONFIG::GM_COMMON_CONFIG::nRecvBufSize;
    common["nPacketBufferSize"] = &GM_CONFIG::GM_COMMON_CONFIG::nPacketBufferSize;
    common["nReLoginInternal"] = &GM_CONFIG::GM_COMMON_CONFIG::nReLoginInternal;
    auto list = cqyh::lua::usertype<GM_CONFIG::SVR_LIST>(L, config, "SVR_LIST", "GM_CONFIG::SVR_LIST");
    list["nSvrNum"] = &GM_CONFIG::SVR_LIST::nSvrNum;
    list["arrSvrList"] = cqyh::lua::array_property(&GM_CONFIG::SVR_LIST::arrSvrList);
    config["GMCommonConfig"] = &GM_CONFIG::GMCommonConfig;
    config["SvrList"] = &GM_CONFIG::SvrList;
    lua.set_function("GetGMConfig", []() -> GM_CONFIG& { return GetGMConfig(); });
    return 1;
}
