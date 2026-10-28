#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/grid_def.h"

namespace cqyh::fusion::bindings {

void register_grid_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["GRID_LAYER_HEIGHT_BIT"] = static_cast<lua_Number>(GRID_LAYER_HEIGHT_BIT);
    globals["NEXT_GRID_BIT"] = static_cast<lua_Number>(NEXT_GRID_BIT);
    globals["MAX_NEXT_GRID"] = static_cast<lua_Number>(MAX_NEXT_GRID);
    globals["GRID_VOLUME_BIT"] = static_cast<lua_Number>(GRID_VOLUME_BIT);
    globals["GRID_DOOR_BIT"] = static_cast<lua_Number>(GRID_DOOR_BIT);
    globals["EDGE_INDEX_BIT"] = static_cast<lua_Number>(EDGE_INDEX_BIT);
    globals["MAX_DOOR_PER_ZONE"] = static_cast<lua_Number>(MAX_DOOR_PER_ZONE);
    globals["MAX_VOLUME_PER_ZONE"] = static_cast<lua_Number>(MAX_VOLUME_PER_ZONE);
    globals["MAX_EDGE_INDEX_PER_ZONE"] = static_cast<lua_Number>(MAX_EDGE_INDEX_PER_ZONE);
    globals["MAX_CHAR_PER_GRID"] = static_cast<lua_Number>(MAX_CHAR_PER_GRID);
    globals["MAX_DROP_PER_GRID"] = static_cast<lua_Number>(MAX_DROP_PER_GRID);
    globals["MAX_QUEST_PER_ZONE"] = static_cast<lua_Number>(MAX_QUEST_PER_ZONE);
    globals["gptInvalid"] = static_cast<lua_Number>(gptInvalid);
    globals["gptNormal"] = static_cast<lua_Number>(gptNormal);
    globals["gptFree"] = static_cast<lua_Number>(gptFree);
    globals["gptSafe"] = static_cast<lua_Number>(gptSafe);
    globals["gptTotal"] = static_cast<lua_Number>(gptTotal);
    auto grid_data_type = cqyh::lua::usertype<GRID_DATA>(L, globals, "GRID_DATA", "GRID_DATA");
    grid_data_type["uNextGrid"] = sol::property([](const GRID_DATA& self) { return self.uNextGrid; }, [](GRID_DATA& self, decltype(GRID_DATA::uNextGrid) value) { self.uNextGrid = value; });
    grid_data_type["uNoObstacle"] = sol::property([](const GRID_DATA& self) { return self.uNoObstacle; }, [](GRID_DATA& self, decltype(GRID_DATA::uNoObstacle) value) { self.uNoObstacle = value; });
    grid_data_type["uVolume"] = sol::property([](const GRID_DATA& self) { return self.uVolume; }, [](GRID_DATA& self, decltype(GRID_DATA::uVolume) value) { self.uVolume = value; });
    grid_data_type["uDoor"] = sol::property([](const GRID_DATA& self) { return self.uDoor; }, [](GRID_DATA& self, decltype(GRID_DATA::uDoor) value) { self.uDoor = value; });
    grid_data_type["uPkType"] = sol::property([](const GRID_DATA& self) { return self.uPkType; }, [](GRID_DATA& self, decltype(GRID_DATA::uPkType) value) { self.uPkType = value; });
    grid_data_type["bBorder"] = sol::property([](const GRID_DATA& self) { return self.bBorder; }, [](GRID_DATA& self, decltype(GRID_DATA::bBorder) value) { self.bBorder = value; });
    grid_data_type["uStallLevel"] = sol::property([](const GRID_DATA& self) { return self.uStallLevel; }, [](GRID_DATA& self, decltype(GRID_DATA::uStallLevel) value) { self.uStallLevel = value; });
    grid_data_type["bQuest"] = sol::property([](const GRID_DATA& self) { return self.bQuest; }, [](GRID_DATA& self, decltype(GRID_DATA::bQuest) value) { self.bQuest = value; });
    grid_data_type["bBlockMove"] = sol::property([](const GRID_DATA& self) { return self.bBlockMove; }, [](GRID_DATA& self, decltype(GRID_DATA::bBlockMove) value) { self.bBlockMove = value; });
    grid_data_type["bBlockLeap"] = sol::property([](const GRID_DATA& self) { return self.bBlockLeap; }, [](GRID_DATA& self, decltype(GRID_DATA::bBlockLeap) value) { self.bBlockLeap = value; });
    grid_data_type["bBlockMissile"] = sol::property([](const GRID_DATA& self) { return self.bBlockMissile; }, [](GRID_DATA& self, decltype(GRID_DATA::bBlockMissile) value) { self.bBlockMissile = value; });
    grid_data_type["bBlockBullet"] = sol::property([](const GRID_DATA& self) { return self.bBlockBullet; }, [](GRID_DATA& self, decltype(GRID_DATA::bBlockBullet) value) { self.bBlockBullet = value; });
    grid_data_type["bNotBlockChar"] = sol::property([](const GRID_DATA& self) { return self.bNotBlockChar; }, [](GRID_DATA& self, decltype(GRID_DATA::bNotBlockChar) value) { self.bNotBlockChar = value; });
    grid_data_type["bMine"] = sol::property([](const GRID_DATA& self) { return self.bMine; }, [](GRID_DATA& self, decltype(GRID_DATA::bMine) value) { self.bMine = value; });
    grid_data_type["bCannotTeleport"] = sol::property([](const GRID_DATA& self) { return self.bCannotTeleport; }, [](GRID_DATA& self, decltype(GRID_DATA::bCannotTeleport) value) { self.bCannotTeleport = value; });
    grid_data_type["bRoleCannotLoseItem"] = sol::property([](const GRID_DATA& self) { return self.bRoleCannotLoseItem; }, [](GRID_DATA& self, decltype(GRID_DATA::bRoleCannotLoseItem) value) { self.bRoleCannotLoseItem = value; });
    grid_data_type["bRoleCannotDropItem"] = sol::property([](const GRID_DATA& self) { return self.bRoleCannotDropItem; }, [](GRID_DATA& self, decltype(GRID_DATA::bRoleCannotDropItem) value) { self.bRoleCannotDropItem = value; });
    grid_data_type["bSlayerArea"] = sol::property([](const GRID_DATA& self) { return self.bSlayerArea; }, [](GRID_DATA& self, decltype(GRID_DATA::bSlayerArea) value) { self.bSlayerArea = value; });
    grid_data_type["bCannotDropItem"] = sol::property([](const GRID_DATA& self) { return self.bCannotDropItem; }, [](GRID_DATA& self, decltype(GRID_DATA::bCannotDropItem) value) { self.bCannotDropItem = value; });
    grid_data_type["uMineLevel"] = sol::property([](const GRID_DATA& self) { return self.uMineLevel; }, [](GRID_DATA& self, decltype(GRID_DATA::uMineLevel) value) { self.uMineLevel = value; });
    grid_data_type["bTeleportPoint"] = sol::property([](const GRID_DATA& self) { return self.bTeleportPoint; }, [](GRID_DATA& self, decltype(GRID_DATA::bTeleportPoint) value) { self.bTeleportPoint = value; });
    grid_data_type["uReserved1"] = sol::property([](const GRID_DATA& self) { return self.uReserved1; }, [](GRID_DATA& self, decltype(GRID_DATA::uReserved1) value) { self.uReserved1 = value; });
    grid_data_type["uReserved2"] = sol::property([](const GRID_DATA& self) { return self.uReserved2; }, [](GRID_DATA& self, decltype(GRID_DATA::uReserved2) value) { self.uReserved2 = value; });
    grid_data_type["uLowLayer"] = sol::property([](const GRID_DATA& self) { return self.uLowLayer; }, [](GRID_DATA& self, decltype(GRID_DATA::uLowLayer) value) { self.uLowLayer = value; });
    grid_data_type["uHighLayer"] = sol::property([](const GRID_DATA& self) { return self.uHighLayer; }, [](GRID_DATA& self, decltype(GRID_DATA::uHighLayer) value) { self.uHighLayer = value; });
    grid_data_type["uEdge"] = sol::property([](const GRID_DATA& self) { return self.uEdge; }, [](GRID_DATA& self, decltype(GRID_DATA::uEdge) value) { self.uEdge = value; });
    grid_data_type["bOutOfPoly"] = sol::property([](const GRID_DATA& self) { return self.bOutOfPoly; }, [](GRID_DATA& self, decltype(GRID_DATA::bOutOfPoly) value) { self.bOutOfPoly = value; });
    grid_data_type["bInServerPointRange"] = sol::property([](const GRID_DATA& self) { return self.bInServerPointRange; }, [](GRID_DATA& self, decltype(GRID_DATA::bInServerPointRange) value) { self.bInServerPointRange = value; });
    grid_data_type["uReserved3"] = sol::property([](const GRID_DATA& self) { return self.uReserved3; }, [](GRID_DATA& self, decltype(GRID_DATA::uReserved3) value) { self.uReserved3 = value; });
    auto grid_instance_data_type = cqyh::lua::usertype<GRID_INSTANCE_DATA>(L, globals, "GRID_INSTANCE_DATA", "GRID_INSTANCE_DATA");
    grid_instance_data_type["uCharRef"] = sol::property([](const GRID_INSTANCE_DATA& self) { return self.uCharRef; }, [](GRID_INSTANCE_DATA& self, decltype(GRID_INSTANCE_DATA::uCharRef) value) { self.uCharRef = value; });
    grid_instance_data_type["uDropRef"] = sol::property([](const GRID_INSTANCE_DATA& self) { return self.uDropRef; }, [](GRID_INSTANCE_DATA& self, decltype(GRID_INSTANCE_DATA::uDropRef) value) { self.uDropRef = value; });
    grid_instance_data_type["uMissileTag1"] = sol::property([](const GRID_INSTANCE_DATA& self) { return self.uMissileTag1; }, [](GRID_INSTANCE_DATA& self, decltype(GRID_INSTANCE_DATA::uMissileTag1) value) { self.uMissileTag1 = value; });
    grid_instance_data_type["uMissileTag2"] = sol::property([](const GRID_INSTANCE_DATA& self) { return self.uMissileTag2; }, [](GRID_INSTANCE_DATA& self, decltype(GRID_INSTANCE_DATA::uMissileTag2) value) { self.uMissileTag2 = value; });
    grid_instance_data_type["uReserved"] = sol::property([](const GRID_INSTANCE_DATA& self) { return self.uReserved; }, [](GRID_INSTANCE_DATA& self, decltype(GRID_INSTANCE_DATA::uReserved) value) { self.uReserved = value; });
}

}
