#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/new_role_config.h"

namespace cqyh::fusion::bindings {

void register_new_role_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto new_role_config_type = cqyh::lua::usertype<NEW_ROLE_CONFIG>(L, globals, "NEW_ROLE_CONFIG", "NEW_ROLE_CONFIG");
    new_role_config_type["nSceneTempID"] = sol::property([](const NEW_ROLE_CONFIG& self) { return self.nSceneTempID; }, [](NEW_ROLE_CONFIG& self, decltype(NEW_ROLE_CONFIG::nSceneTempID) value) { self.nSceneTempID = value; });
    new_role_config_type["nX"] = sol::property([](const NEW_ROLE_CONFIG& self) { return self.nX; }, [](NEW_ROLE_CONFIG& self, decltype(NEW_ROLE_CONFIG::nX) value) { self.nX = value; });
    new_role_config_type["nY"] = sol::property([](const NEW_ROLE_CONFIG& self) { return self.nY; }, [](NEW_ROLE_CONFIG& self, decltype(NEW_ROLE_CONFIG::nY) value) { self.nY = value; });
    new_role_config_type["nZ"] = sol::property([](const NEW_ROLE_CONFIG& self) { return self.nZ; }, [](NEW_ROLE_CONFIG& self, decltype(NEW_ROLE_CONFIG::nZ) value) { self.nZ = value; });
    new_role_config_type["wFaceDirection"] = sol::property([](const NEW_ROLE_CONFIG& self) { return self.wFaceDirection; }, [](NEW_ROLE_CONFIG& self, decltype(NEW_ROLE_CONFIG::wFaceDirection) value) { self.wFaceDirection = value; });
    auto new_equip_type = cqyh::lua::usertype<NEW_ROLE_CONFIG::NEW_EQUIP>(L, new_role_config_type, "NEW_EQUIP", "NEW_ROLE_CONFIG::NEW_EQUIP");
    new_equip_type["nMainHand"] = sol::property([](const NEW_ROLE_CONFIG::NEW_EQUIP& self) { return self.nMainHand; }, [](NEW_ROLE_CONFIG::NEW_EQUIP& self, decltype(NEW_ROLE_CONFIG::NEW_EQUIP::nMainHand) value) { self.nMainHand = value; });
    new_equip_type["nBody"] = sol::property([](const NEW_ROLE_CONFIG::NEW_EQUIP& self) { return self.nBody; }, [](NEW_ROLE_CONFIG::NEW_EQUIP& self, decltype(NEW_ROLE_CONFIG::NEW_EQUIP::nBody) value) { self.nBody = value; });
    new_equip_type["nBack"] = sol::property([](const NEW_ROLE_CONFIG::NEW_EQUIP& self) { return self.nBack; }, [](NEW_ROLE_CONFIG::NEW_EQUIP& self, decltype(NEW_ROLE_CONFIG::NEW_EQUIP::nBack) value) { self.nBack = value; });
    new_role_config_type["MaleNewEquip"] = cqyh::lua::array_property(&NEW_ROLE_CONFIG::MaleNewEquip);
    new_role_config_type["FemaleNewEquip"] = cqyh::lua::array_property(&NEW_ROLE_CONFIG::FemaleNewEquip);
    globals["g_NewRoleConfig"] = &g_NewRoleConfig;
}

}
