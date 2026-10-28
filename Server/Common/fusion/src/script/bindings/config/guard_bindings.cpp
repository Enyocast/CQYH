#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/guard_config.h"

namespace cqyh::fusion::bindings {

void register_guard_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto guard_log_config_type = cqyh::lua::usertype<GUARD_LOG_CONFIG>(L, globals, "GUARD_LOG_CONFIG", "GUARD_LOG_CONFIG");
    guard_log_config_type["nLogLevelMask"] = sol::property([](const GUARD_LOG_CONFIG& self) { return self.nLogLevelMask; }, [](GUARD_LOG_CONFIG& self, decltype(GUARD_LOG_CONFIG::nLogLevelMask) value) { self.nLogLevelMask = value; });
    guard_log_config_type["nLogOutputMask"] = sol::property([](const GUARD_LOG_CONFIG& self) { return self.nLogOutputMask; }, [](GUARD_LOG_CONFIG& self, decltype(GUARD_LOG_CONFIG::nLogOutputMask) value) { self.nLogOutputMask = value; });
    guard_log_config_type["bEnableLogThread"] = sol::property([](const GUARD_LOG_CONFIG& self) { return static_cast<bool>(self.bEnableLogThread); }, [](GUARD_LOG_CONFIG& self, bool value) { self.bEnableLogThread = value; });
    guard_log_config_type["bPrintThreadID"] = sol::property([](const GUARD_LOG_CONFIG& self) { return static_cast<bool>(self.bPrintThreadID); }, [](GUARD_LOG_CONFIG& self, bool value) { self.bPrintThreadID = value; });
    guard_log_config_type["bFlushFile"] = sol::property([](const GUARD_LOG_CONFIG& self) { return static_cast<bool>(self.bFlushFile); }, [](GUARD_LOG_CONFIG& self, bool value) { self.bFlushFile = value; });
    auto guard_net_config_type = cqyh::lua::usertype<GUARD_NET_CONFIG>(L, globals, "GUARD_NET_CONFIG", "GUARD_NET_CONFIG");
    guard_net_config_type["nMaxAcceptor"] = sol::property([](const GUARD_NET_CONFIG& self) { return self.nMaxAcceptor; }, [](GUARD_NET_CONFIG& self, decltype(GUARD_NET_CONFIG::nMaxAcceptor) value) { self.nMaxAcceptor = value; });
    guard_net_config_type["nMaxConnector"] = sol::property([](const GUARD_NET_CONFIG& self) { return self.nMaxConnector; }, [](GUARD_NET_CONFIG& self, decltype(GUARD_NET_CONFIG::nMaxConnector) value) { self.nMaxConnector = value; });
    guard_net_config_type["nSendBufSize"] = sol::property([](const GUARD_NET_CONFIG& self) { return self.nSendBufSize; }, [](GUARD_NET_CONFIG& self, decltype(GUARD_NET_CONFIG::nSendBufSize) value) { self.nSendBufSize = value; });
    guard_net_config_type["nRecvBufSize"] = sol::property([](const GUARD_NET_CONFIG& self) { return self.nRecvBufSize; }, [](GUARD_NET_CONFIG& self, decltype(GUARD_NET_CONFIG::nRecvBufSize) value) { self.nRecvBufSize = value; });
    guard_net_config_type["nPacketBufferSize"] = sol::property([](const GUARD_NET_CONFIG& self) { return self.nPacketBufferSize; }, [](GUARD_NET_CONFIG& self, decltype(GUARD_NET_CONFIG::nPacketBufferSize) value) { self.nPacketBufferSize = value; });
    guard_net_config_type["nMaxSessionCount"] = sol::property([](const GUARD_NET_CONFIG& self) { return self.nMaxSessionCount; }, [](GUARD_NET_CONFIG& self, decltype(GUARD_NET_CONFIG::nMaxSessionCount) value) { self.nMaxSessionCount = value; });
    guard_net_config_type["nSmallPacketCount"] = sol::property([](const GUARD_NET_CONFIG& self) { return self.nSmallPacketCount; }, [](GUARD_NET_CONFIG& self, decltype(GUARD_NET_CONFIG::nSmallPacketCount) value) { self.nSmallPacketCount = value; });
    guard_net_config_type["nLargePacketCount"] = sol::property([](const GUARD_NET_CONFIG& self) { return self.nLargePacketCount; }, [](GUARD_NET_CONFIG& self, decltype(GUARD_NET_CONFIG::nLargePacketCount) value) { self.nLargePacketCount = value; });
    guard_net_config_type["nMaxOperationPerLoop"] = sol::property([](const GUARD_NET_CONFIG& self) { return self.nMaxOperationPerLoop; }, [](GUARD_NET_CONFIG& self, decltype(GUARD_NET_CONFIG::nMaxOperationPerLoop) value) { self.nMaxOperationPerLoop = value; });
    guard_net_config_type["nSendLoopBufferSize"] = sol::property([](const GUARD_NET_CONFIG& self) { return self.nSendLoopBufferSize; }, [](GUARD_NET_CONFIG& self, decltype(GUARD_NET_CONFIG::nSendLoopBufferSize) value) { self.nSendLoopBufferSize = value; });
    guard_net_config_type["nRecvLoopBufferSize"] = sol::property([](const GUARD_NET_CONFIG& self) { return self.nRecvLoopBufferSize; }, [](GUARD_NET_CONFIG& self, decltype(GUARD_NET_CONFIG::nRecvLoopBufferSize) value) { self.nRecvLoopBufferSize = value; });
    auto guard_config_type = cqyh::lua::usertype<GUARD_CONFIG>(L, globals, "GUARD_CONFIG", "GUARD_CONFIG");
    guard_config_type["Log"] = &GUARD_CONFIG::Log;
    guard_config_type["Net"] = &GUARD_CONFIG::Net;
    guard_config_type["szAddress"] = cqyh::lua::string_property(&GUARD_CONFIG::szAddress);
    guard_config_type["dwPort"] = sol::property([](const GUARD_CONFIG& self) { return self.dwPort; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::dwPort) value) { self.dwPort = value; });
    guard_config_type["nRegisterGuardTimeout"] = sol::property([](const GUARD_CONFIG& self) { return self.nRegisterGuardTimeout; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nRegisterGuardTimeout) value) { self.nRegisterGuardTimeout = value; });
    guard_config_type["nPingGuardTimeout"] = sol::property([](const GUARD_CONFIG& self) { return self.nPingGuardTimeout; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nPingGuardTimeout) value) { self.nPingGuardTimeout = value; });
    guard_config_type["nServerPingInterval"] = sol::property([](const GUARD_CONFIG& self) { return self.nServerPingInterval; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nServerPingInterval) value) { self.nServerPingInterval = value; });
    guard_config_type["nServerPingTimeout"] = sol::property([](const GUARD_CONFIG& self) { return self.nServerPingTimeout; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nServerPingTimeout) value) { self.nServerPingTimeout = value; });
    guard_config_type["nShareMemDisconnectTimeout"] = sol::property([](const GUARD_CONFIG& self) { return self.nShareMemDisconnectTimeout; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nShareMemDisconnectTimeout) value) { self.nShareMemDisconnectTimeout = value; });
    guard_config_type["nLocalGSCount"] = sol::property([](const GUARD_CONFIG& self) { return self.nLocalGSCount; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nLocalGSCount) value) { self.nLocalGSCount = value; });
    guard_config_type["nLocalGTCount"] = sol::property([](const GUARD_CONFIG& self) { return self.nLocalGTCount; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nLocalGTCount) value) { self.nLocalGTCount = value; });
    guard_config_type["nLocalBSCount"] = sol::property([](const GUARD_CONFIG& self) { return self.nLocalBSCount; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nLocalBSCount) value) { self.nLocalBSCount = value; });
    guard_config_type["nLocalDLCount"] = sol::property([](const GUARD_CONFIG& self) { return self.nLocalDLCount; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nLocalDLCount) value) { self.nLocalDLCount = value; });
    guard_config_type["nLocalLSCount"] = sol::property([](const GUARD_CONFIG& self) { return self.nLocalLSCount; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nLocalLSCount) value) { self.nLocalLSCount = value; });
    guard_config_type["nLocalDBCount"] = sol::property([](const GUARD_CONFIG& self) { return self.nLocalDBCount; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nLocalDBCount) value) { self.nLocalDBCount = value; });
    guard_config_type["nLocalMSCount"] = sol::property([](const GUARD_CONFIG& self) { return self.nLocalMSCount; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nLocalMSCount) value) { self.nLocalMSCount = value; });
    guard_config_type["nLocalGMCount"] = sol::property([](const GUARD_CONFIG& self) { return self.nLocalGMCount; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nLocalGMCount) value) { self.nLocalGMCount = value; });
    guard_config_type["nLocalMMCount"] = sol::property([](const GUARD_CONFIG& self) { return self.nLocalMMCount; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nLocalMMCount) value) { self.nLocalMMCount = value; });
    guard_config_type["nLocalMGCount"] = sol::property([](const GUARD_CONFIG& self) { return self.nLocalMGCount; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nLocalMGCount) value) { self.nLocalMGCount = value; });
    guard_config_type["szMTUser"] = cqyh::lua::string_property(&GUARD_CONFIG::szMTUser);
    guard_config_type["szMTPwd"] = cqyh::lua::string_property(&GUARD_CONFIG::szMTPwd);
    guard_config_type["szReportAbsolutePath"] = cqyh::lua::string_property(&GUARD_CONFIG::szReportAbsolutePath);
    guard_config_type["szServerVersionPath"] = cqyh::lua::string_property(&GUARD_CONFIG::szServerVersionPath);
    guard_config_type["szServerPatchPath"] = cqyh::lua::string_property(&GUARD_CONFIG::szServerPatchPath);
    guard_config_type["szServerRunPath"] = cqyh::lua::string_property(&GUARD_CONFIG::szServerRunPath);
    guard_config_type["szGuardPath"] = cqyh::lua::string_property(&GUARD_CONFIG::szGuardPath);
    guard_config_type["nLogCleanThreshold"] = sol::property([](const GUARD_CONFIG& self) { return self.nLogCleanThreshold; }, [](GUARD_CONFIG& self, decltype(GUARD_CONFIG::nLogCleanThreshold) value) { self.nLogCleanThreshold = value; });
}

}
