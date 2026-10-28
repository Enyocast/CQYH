#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/mt_config.h"

namespace cqyh::fusion::bindings {

void register_mt_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto maintain_config_type = cqyh::lua::usertype<MAINTAIN_CONFIG>(L, globals, "MAINTAIN_CONFIG", "MAINTAIN_CONFIG");
    maintain_config_type["nLogLevelMask"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nLogLevelMask; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nLogLevelMask) value) { self.nLogLevelMask = value; });
    maintain_config_type["nLogOutputMask"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nLogOutputMask; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nLogOutputMask) value) { self.nLogOutputMask = value; });
    maintain_config_type["bEnableLogThread"] = sol::property([](const MAINTAIN_CONFIG& self) { return static_cast<bool>(self.bEnableLogThread); }, [](MAINTAIN_CONFIG& self, bool value) { self.bEnableLogThread = value; });
    maintain_config_type["bFlushFile"] = sol::property([](const MAINTAIN_CONFIG& self) { return static_cast<bool>(self.bFlushFile); }, [](MAINTAIN_CONFIG& self, bool value) { self.bFlushFile = value; });
    maintain_config_type["nMaxAcceptor"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nMaxAcceptor; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nMaxAcceptor) value) { self.nMaxAcceptor = value; });
    maintain_config_type["nMaxConnector"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nMaxConnector; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nMaxConnector) value) { self.nMaxConnector = value; });
    maintain_config_type["nMaxSessionCount"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nMaxSessionCount; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nMaxSessionCount) value) { self.nMaxSessionCount = value; });
    maintain_config_type["nSendBufSize"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nSendBufSize; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nSendBufSize) value) { self.nSendBufSize = value; });
    maintain_config_type["nRecvBufSize"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nRecvBufSize; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nRecvBufSize) value) { self.nRecvBufSize = value; });
    maintain_config_type["nPacketBufferSize"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nPacketBufferSize; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nPacketBufferSize) value) { self.nPacketBufferSize = value; });
    maintain_config_type["nSmallPacketCount"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nSmallPacketCount; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nSmallPacketCount) value) { self.nSmallPacketCount = value; });
    maintain_config_type["nLargePacketCount"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nLargePacketCount; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nLargePacketCount) value) { self.nLargePacketCount = value; });
    maintain_config_type["nPingTimeout"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nPingTimeout; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nPingTimeout) value) { self.nPingTimeout = value; });
    maintain_config_type["nServerPingInterval"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nServerPingInterval; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nServerPingInterval) value) { self.nServerPingInterval = value; });
    maintain_config_type["bPrintThreadID"] = sol::property([](const MAINTAIN_CONFIG& self) { return static_cast<bool>(self.bPrintThreadID); }, [](MAINTAIN_CONFIG& self, bool value) { self.bPrintThreadID = value; });
    maintain_config_type["nReconnectTime"] = sol::property([](const MAINTAIN_CONFIG& self) { return self.nReconnectTime; }, [](MAINTAIN_CONFIG& self, decltype(MAINTAIN_CONFIG::nReconnectTime) value) { self.nReconnectTime = value; });
    maintain_config_type["szVersionPath"] = cqyh::lua::string_property(&MAINTAIN_CONFIG::szVersionPath);
    maintain_config_type["szPatchPath"] = cqyh::lua::string_property(&MAINTAIN_CONFIG::szPatchPath);
    maintain_config_type["szAreaConfigPath"] = cqyh::lua::string_property(&MAINTAIN_CONFIG::szAreaConfigPath);
    auto s_area_config_type = cqyh::lua::usertype<MAINTAIN_CONFIG::SAreaConfig>(L, maintain_config_type, "SAreaConfig", "MAINTAIN_CONFIG::SAreaConfig");
    s_area_config_type["nAreaShowID"] = sol::property([](const MAINTAIN_CONFIG::SAreaConfig& self) { return self.nAreaShowID; }, [](MAINTAIN_CONFIG::SAreaConfig& self, decltype(MAINTAIN_CONFIG::SAreaConfig::nAreaShowID) value) { self.nAreaShowID = value; });
    s_area_config_type["nAreaID"] = sol::property([](const MAINTAIN_CONFIG::SAreaConfig& self) { return self.nAreaID; }, [](MAINTAIN_CONFIG::SAreaConfig& self, decltype(MAINTAIN_CONFIG::SAreaConfig::nAreaID) value) { self.nAreaID = value; });
    s_area_config_type["szVersion"] = cqyh::lua::string_property(&MAINTAIN_CONFIG::SAreaConfig::szVersion);
    s_area_config_type["szAreaName"] = cqyh::lua::string_property(&MAINTAIN_CONFIG::SAreaConfig::szAreaName);
    s_area_config_type["szAreaFolderName"] = cqyh::lua::string_property(&MAINTAIN_CONFIG::SAreaConfig::szAreaFolderName);
    auto s_remote_guard_type = cqyh::lua::usertype<MAINTAIN_CONFIG::SAreaConfig::SRemoteGuard>(L, s_area_config_type, "SRemoteGuard", "MAINTAIN_CONFIG::SAreaConfig::SRemoteGuard");
    s_remote_guard_type["szAddress"] = cqyh::lua::string_property(&MAINTAIN_CONFIG::SAreaConfig::SRemoteGuard::szAddress);
    s_remote_guard_type["nPort"] = sol::property([](const MAINTAIN_CONFIG::SAreaConfig::SRemoteGuard& self) { return self.nPort; }, [](MAINTAIN_CONFIG::SAreaConfig::SRemoteGuard& self, decltype(MAINTAIN_CONFIG::SAreaConfig::SRemoteGuard::nPort) value) { self.nPort = value; });
    s_remote_guard_type["szGuardVersion"] = cqyh::lua::string_property(&MAINTAIN_CONFIG::SAreaConfig::SRemoteGuard::szGuardVersion);
    s_area_config_type["guardList"] = cqyh::lua::array_property(&MAINTAIN_CONFIG::SAreaConfig::guardList);
    maintain_config_type["AreaConfig"] = cqyh::lua::array_property(&MAINTAIN_CONFIG::AreaConfig);
}

}
