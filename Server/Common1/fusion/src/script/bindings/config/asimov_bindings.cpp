#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/global_config.h"
#include "../../../../inc/asimov_config.h"

namespace cqyh::fusion::bindings {

void register_asimov_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto asimov_config_type = cqyh::lua::usertype<ASIMOV_CONFIG>(L, globals, "ASIMOV_CONFIG", "ASIMOV_CONFIG");
    asimov_config_type["Log"] = &ASIMOV_CONFIG::Log;
    asimov_config_type["Net"] = &ASIMOV_CONFIG::Net;
    asimov_config_type["szAddress"] = cqyh::lua::string_property(&ASIMOV_CONFIG::szAddress);
    asimov_config_type["dwPort"] = sol::property([](const ASIMOV_CONFIG& self) { return self.dwPort; }, [](ASIMOV_CONFIG& self, decltype(ASIMOV_CONFIG::dwPort) value) { self.dwPort = value; });
    asimov_config_type["nMaxSessionCount"] = sol::property([](const ASIMOV_CONFIG& self) { return self.nMaxSessionCount; }, [](ASIMOV_CONFIG& self, decltype(ASIMOV_CONFIG::nMaxSessionCount) value) { self.nMaxSessionCount = value; });
    asimov_config_type["nWorkThreadCount"] = sol::property([](const ASIMOV_CONFIG& self) { return self.nWorkThreadCount; }, [](ASIMOV_CONFIG& self, decltype(ASIMOV_CONFIG::nWorkThreadCount) value) { self.nWorkThreadCount = value; });
}

}
