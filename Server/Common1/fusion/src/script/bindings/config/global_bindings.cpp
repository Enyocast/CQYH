#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/global_config.h"

namespace cqyh::fusion::bindings {

void register_global_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto log_config_type = cqyh::lua::usertype<LOG_CONFIG>(L, globals, "LOG_CONFIG", "LOG_CONFIG");
    log_config_type["nLogLevelMask"] = sol::property([](const LOG_CONFIG& self) { return self.nLogLevelMask; }, [](LOG_CONFIG& self, decltype(LOG_CONFIG::nLogLevelMask) value) { self.nLogLevelMask = value; });
    log_config_type["nLogOutputMask"] = sol::property([](const LOG_CONFIG& self) { return self.nLogOutputMask; }, [](LOG_CONFIG& self, decltype(LOG_CONFIG::nLogOutputMask) value) { self.nLogOutputMask = value; });
    log_config_type["bEnableLogThread"] = sol::property([](const LOG_CONFIG& self) { return static_cast<bool>(self.bEnableLogThread); }, [](LOG_CONFIG& self, bool value) { self.bEnableLogThread = value; });
    log_config_type["bPrintThreadID"] = sol::property([](const LOG_CONFIG& self) { return static_cast<bool>(self.bPrintThreadID); }, [](LOG_CONFIG& self, bool value) { self.bPrintThreadID = value; });
    log_config_type["bFlushFile"] = sol::property([](const LOG_CONFIG& self) { return static_cast<bool>(self.bFlushFile); }, [](LOG_CONFIG& self, bool value) { self.bFlushFile = value; });
    auto net_config_type = cqyh::lua::usertype<NET_CONFIG>(L, globals, "NET_CONFIG", "NET_CONFIG");
    net_config_type["nMaxAcceptor"] = sol::property([](const NET_CONFIG& self) { return self.nMaxAcceptor; }, [](NET_CONFIG& self, decltype(NET_CONFIG::nMaxAcceptor) value) { self.nMaxAcceptor = value; });
    net_config_type["nMaxConnector"] = sol::property([](const NET_CONFIG& self) { return self.nMaxConnector; }, [](NET_CONFIG& self, decltype(NET_CONFIG::nMaxConnector) value) { self.nMaxConnector = value; });
    net_config_type["nSendBufSize"] = sol::property([](const NET_CONFIG& self) { return self.nSendBufSize; }, [](NET_CONFIG& self, decltype(NET_CONFIG::nSendBufSize) value) { self.nSendBufSize = value; });
    net_config_type["nRecvBufSize"] = sol::property([](const NET_CONFIG& self) { return self.nRecvBufSize; }, [](NET_CONFIG& self, decltype(NET_CONFIG::nRecvBufSize) value) { self.nRecvBufSize = value; });
    net_config_type["nPacketBufferSize"] = sol::property([](const NET_CONFIG& self) { return self.nPacketBufferSize; }, [](NET_CONFIG& self, decltype(NET_CONFIG::nPacketBufferSize) value) { self.nPacketBufferSize = value; });
    net_config_type["nMaxSessionCount"] = sol::property([](const NET_CONFIG& self) { return self.nMaxSessionCount; }, [](NET_CONFIG& self, decltype(NET_CONFIG::nMaxSessionCount) value) { self.nMaxSessionCount = value; });
    net_config_type["nSmallPacketCount"] = sol::property([](const NET_CONFIG& self) { return self.nSmallPacketCount; }, [](NET_CONFIG& self, decltype(NET_CONFIG::nSmallPacketCount) value) { self.nSmallPacketCount = value; });
    net_config_type["nLargePacketCount"] = sol::property([](const NET_CONFIG& self) { return self.nLargePacketCount; }, [](NET_CONFIG& self, decltype(NET_CONFIG::nLargePacketCount) value) { self.nLargePacketCount = value; });
    net_config_type["nMaxOperationPerLoop"] = sol::property([](const NET_CONFIG& self) { return self.nMaxOperationPerLoop; }, [](NET_CONFIG& self, decltype(NET_CONFIG::nMaxOperationPerLoop) value) { self.nMaxOperationPerLoop = value; });
    net_config_type["nSendLoopBufferSize"] = sol::property([](const NET_CONFIG& self) { return self.nSendLoopBufferSize; }, [](NET_CONFIG& self, decltype(NET_CONFIG::nSendLoopBufferSize) value) { self.nSendLoopBufferSize = value; });
    net_config_type["nRecvLoopBufferSize"] = sol::property([](const NET_CONFIG& self) { return self.nRecvLoopBufferSize; }, [](NET_CONFIG& self, decltype(NET_CONFIG::nRecvLoopBufferSize) value) { self.nRecvLoopBufferSize = value; });
}

}
