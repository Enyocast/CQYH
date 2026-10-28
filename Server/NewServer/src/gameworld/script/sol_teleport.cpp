#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../../Common/define/teleport_def.h"

int sol_teleport_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_TELEPORT_POINT_PER_SCENE"] = static_cast<lua_Number>(MAX_TELEPORT_POINT_PER_SCENE);
    globals["INVALID_TELEPORT_ID"] = static_cast<lua_Number>(INVALID_TELEPORT_ID);
    globals["MAX_TELEPORT_PLATFORM_COUNT"] = static_cast<lua_Number>(MAX_TELEPORT_PLATFORM_COUNT);
    auto type1 = cqyh::lua::usertype<SCENE_TELEPORTS>(L, globals, "SCENE_TELEPORTS", "SCENE_TELEPORTS");
    type1["ID"] = sol::property([](const SCENE_TELEPORTS& self) { return self.ID; }, [](SCENE_TELEPORTS& self, decltype(SCENE_TELEPORTS::ID) value) { self.ID = value; });
    type1["SrcSceneID"] = sol::property([](const SCENE_TELEPORTS& self) { return self.SrcSceneID; }, [](SCENE_TELEPORTS& self, decltype(SCENE_TELEPORTS::SrcSceneID) value) { self.SrcSceneID = value; });
    type1["SrcRadius"] = sol::property([](const SCENE_TELEPORTS& self) { return self.SrcRadius; }, [](SCENE_TELEPORTS& self, decltype(SCENE_TELEPORTS::SrcRadius) value) { self.SrcRadius = value; });
    type1["SrcSceneX"] = sol::property([](const SCENE_TELEPORTS& self) { return self.SrcSceneX; }, [](SCENE_TELEPORTS& self, decltype(SCENE_TELEPORTS::SrcSceneX) value) { self.SrcSceneX = value; });
    type1["SrcSceneY"] = sol::property([](const SCENE_TELEPORTS& self) { return self.SrcSceneY; }, [](SCENE_TELEPORTS& self, decltype(SCENE_TELEPORTS::SrcSceneY) value) { self.SrcSceneY = value; });
    type1["SrcSceneZ"] = sol::property([](const SCENE_TELEPORTS& self) { return self.SrcSceneZ; }, [](SCENE_TELEPORTS& self, decltype(SCENE_TELEPORTS::SrcSceneZ) value) { self.SrcSceneZ = value; });
    type1["TargetSceneID"] = sol::property([](const SCENE_TELEPORTS& self) { return self.TargetSceneID; }, [](SCENE_TELEPORTS& self, decltype(SCENE_TELEPORTS::TargetSceneID) value) { self.TargetSceneID = value; });
    type1["TargetSceneX"] = sol::property([](const SCENE_TELEPORTS& self) { return self.TargetSceneX; }, [](SCENE_TELEPORTS& self, decltype(SCENE_TELEPORTS::TargetSceneX) value) { self.TargetSceneX = value; });
    type1["TargetSceneY"] = sol::property([](const SCENE_TELEPORTS& self) { return self.TargetSceneY; }, [](SCENE_TELEPORTS& self, decltype(SCENE_TELEPORTS::TargetSceneY) value) { self.TargetSceneY = value; });
    type1["TargetSceneZ"] = sol::property([](const SCENE_TELEPORTS& self) { return self.TargetSceneZ; }, [](SCENE_TELEPORTS& self, decltype(SCENE_TELEPORTS::TargetSceneZ) value) { self.TargetSceneZ = value; });
    type1["TargetRotationYaw"] = sol::property([](const SCENE_TELEPORTS& self) { return self.TargetRotationYaw; }, [](SCENE_TELEPORTS& self, decltype(SCENE_TELEPORTS::TargetRotationYaw) value) { self.TargetRotationYaw = value; });
    type1["TargetRadius"] = sol::property([](const SCENE_TELEPORTS& self) { return self.TargetRadius; }, [](SCENE_TELEPORTS& self, decltype(SCENE_TELEPORTS::TargetRadius) value) { self.TargetRadius = value; });
    auto type2 = cqyh::lua::usertype<TELEPORT_PLATFORM>(L, globals, "TELEPORT_PLATFORM", "TELEPORT_PLATFORM");
    type2["ID"] = sol::property([](const TELEPORT_PLATFORM& self) { return self.ID; }, [](TELEPORT_PLATFORM& self, decltype(TELEPORT_PLATFORM::ID) value) { self.ID = value; });
    type2["nInitEnable"] = sol::property([](const TELEPORT_PLATFORM& self) { return self.nInitEnable; }, [](TELEPORT_PLATFORM& self, decltype(TELEPORT_PLATFORM::nInitEnable) value) { self.nInitEnable = value; });
    type2["nMoneyType"] = sol::property([](const TELEPORT_PLATFORM& self) { return self.nMoneyType; }, [](TELEPORT_PLATFORM& self, decltype(TELEPORT_PLATFORM::nMoneyType) value) { self.nMoneyType = value; });
    type2["nMoney"] = sol::property([](const TELEPORT_PLATFORM& self) { return self.nMoney; }, [](TELEPORT_PLATFORM& self, decltype(TELEPORT_PLATFORM::nMoney) value) { self.nMoney = value; });
    type2["nSceneID"] = sol::property([](const TELEPORT_PLATFORM& self) { return self.nSceneID; }, [](TELEPORT_PLATFORM& self, decltype(TELEPORT_PLATFORM::nSceneID) value) { self.nSceneID = value; });
    type2["nRadius"] = sol::property([](const TELEPORT_PLATFORM& self) { return self.nRadius; }, [](TELEPORT_PLATFORM& self, decltype(TELEPORT_PLATFORM::nRadius) value) { self.nRadius = value; });
    type2["nSceneX"] = sol::property([](const TELEPORT_PLATFORM& self) { return self.nSceneX; }, [](TELEPORT_PLATFORM& self, decltype(TELEPORT_PLATFORM::nSceneX) value) { self.nSceneX = value; });
    type2["nSceneY"] = sol::property([](const TELEPORT_PLATFORM& self) { return self.nSceneY; }, [](TELEPORT_PLATFORM& self, decltype(TELEPORT_PLATFORM::nSceneY) value) { self.nSceneY = value; });
    type2["nSceneZ"] = sol::property([](const TELEPORT_PLATFORM& self) { return self.nSceneZ; }, [](TELEPORT_PLATFORM& self, decltype(TELEPORT_PLATFORM::nSceneZ) value) { self.nSceneZ = value; });
    type2["nRotationYaw"] = sol::property([](const TELEPORT_PLATFORM& self) { return self.nRotationYaw; }, [](TELEPORT_PLATFORM& self, decltype(TELEPORT_PLATFORM::nRotationYaw) value) { self.nRotationYaw = value; });
    return 1;
}
