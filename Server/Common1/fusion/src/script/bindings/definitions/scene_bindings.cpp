#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/scene_def.h"

namespace cqyh::fusion::bindings {

void register_scene_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["POINT_PER_CM"] = static_cast<lua_Number>(POINT_PER_CM);
    globals["POINT_PER_METER"] = static_cast<lua_Number>(POINT_PER_METER);
    globals["GAME_FPS"] = static_cast<lua_Number>(GAME_FPS);
    globals["GRID_WIDTH"] = static_cast<lua_Number>(GRID_WIDTH);
    globals["GRID_LAYER_HEIGHT"] = static_cast<lua_Number>(GRID_LAYER_HEIGHT);
    globals["ZONE_WIDTH"] = static_cast<lua_Number>(ZONE_WIDTH);
    globals["REGION_WIDTH"] = static_cast<lua_Number>(REGION_WIDTH);
    globals["MAX_SCENE_WIDTH"] = static_cast<lua_Number>(MAX_SCENE_WIDTH);
    globals["MAX_REGION_PER_SCENE"] = static_cast<lua_Number>(MAX_REGION_PER_SCENE);
    globals["MAX_ZONE_PER_SCENE"] = static_cast<lua_Number>(MAX_ZONE_PER_SCENE);
    globals["GRID_PER_ZONE"] = static_cast<lua_Number>(GRID_PER_ZONE);
    globals["MAX_MOVE_SPEED"] = static_cast<lua_Number>(MAX_MOVE_SPEED);
    globals["MAX_NPC_SPAWN_POINT_PER_SMALL_GROUP"] = static_cast<lua_Number>(MAX_NPC_SPAWN_POINT_PER_SMALL_GROUP);
    globals["MAX_NPC_SMALL_GROUP_PER_MEDIUM_GROUP"] = static_cast<lua_Number>(MAX_NPC_SMALL_GROUP_PER_MEDIUM_GROUP);
    globals["MAX_NPC_MEDIUM_GROUP_PER_LARGE_GROUP"] = static_cast<lua_Number>(MAX_NPC_MEDIUM_GROUP_PER_LARGE_GROUP);
    globals["MAX_NPC_MEDIUM_GROUP_COUNT"] = static_cast<lua_Number>(MAX_NPC_MEDIUM_GROUP_COUNT);
    globals["MAX_NPC_LARGE_GROUP_COUNT"] = static_cast<lua_Number>(MAX_NPC_LARGE_GROUP_COUNT);
    globals["MAX_NPC_TEMPLATE_COUNT"] = static_cast<lua_Number>(MAX_NPC_TEMPLATE_COUNT);
    globals["MAX_SINGLE_NPC_COUNT"] = static_cast<lua_Number>(MAX_SINGLE_NPC_COUNT);
    globals["MAX_DOODAD_SPAWN_GROUP_COUNT"] = static_cast<lua_Number>(MAX_DOODAD_SPAWN_GROUP_COUNT);
    globals["MAX_DOODAD_SPAWN_POINT_COUNT"] = static_cast<lua_Number>(MAX_DOODAD_SPAWN_POINT_COUNT);
    globals["MAX_DOODAD_COUNT_PER_GROUP"] = static_cast<lua_Number>(MAX_DOODAD_COUNT_PER_GROUP);
    globals["MAX_SCENE_ENTER_DISTANCE"] = static_cast<lua_Number>(MAX_SCENE_ENTER_DISTANCE);
    globals["MAX_DOOR_ID"] = static_cast<lua_Number>(MAX_DOOR_ID);
    globals["MAX_SCENE_TEMPLATE_COUNT"] = static_cast<lua_Number>(MAX_SCENE_TEMPLATE_COUNT);
    globals["MAX_VOLUME_COUNT"] = static_cast<lua_Number>(MAX_VOLUME_COUNT);
    globals["MAX_RANDOM_WEATHER_COUNT"] = static_cast<lua_Number>(MAX_RANDOM_WEATHER_COUNT);
    globals["MAX_SYNC_CHAR_COUNT"] = static_cast<lua_Number>(MAX_SYNC_CHAR_COUNT);
    globals["MAX_SYNC_DOODAD_COUNT"] = static_cast<lua_Number>(MAX_SYNC_DOODAD_COUNT);
    globals["MAX_VELOCITY_Z"] = static_cast<lua_Number>(MAX_VELOCITY_Z);
    globals["GLOBAL_GRAVITY"] = static_cast<lua_Number>(GLOBAL_GRAVITY);
    globals["SCENE_READY_TIME"] = static_cast<lua_Number>(SCENE_READY_TIME);
    globals["MAX_SIDE_COUNT"] = static_cast<lua_Number>(MAX_SIDE_COUNT);
    globals["MAX_FACTION_COUNT"] = static_cast<lua_Number>(MAX_FACTION_COUNT);
    globals["ROLE_HEIGHT"] = static_cast<lua_Number>(ROLE_HEIGHT);
    globals["SYNC_BATTLE_MEMBER_TIME"] = static_cast<lua_Number>(SYNC_BATTLE_MEMBER_TIME);
    globals["MAX_LINE_SCENE_NUMBER"] = static_cast<lua_Number>(MAX_LINE_SCENE_NUMBER);
    globals["DAYTIME_HOURS"] = static_cast<lua_Number>(DAYTIME_HOURS);
    globals["DL_RECORD_ROLET_INTERVAL"] = static_cast<lua_Number>(DL_RECORD_ROLET_INTERVAL);
    globals["MAX_MINE_DROP_GROUP"] = static_cast<lua_Number>(MAX_MINE_DROP_GROUP);
    globals["swtInvalid"] = static_cast<lua_Number>(swtInvalid);
    globals["swtNormal"] = static_cast<lua_Number>(swtNormal);
    globals["swtFog"] = static_cast<lua_Number>(swtFog);
    globals["swtThunder"] = static_cast<lua_Number>(swtThunder);
    globals["swtRain"] = static_cast<lua_Number>(swtRain);
    globals["swtSnow"] = static_cast<lua_Number>(swtSnow);
    globals["swtStorm"] = static_cast<lua_Number>(swtStorm);
    globals["swtEclipse"] = static_cast<lua_Number>(swtEclipse);
    globals["swtTotal"] = static_cast<lua_Number>(swtTotal);
    globals["sdtInvalid"] = static_cast<lua_Number>(sdtInvalid);
    globals["sdtDay"] = static_cast<lua_Number>(sdtDay);
    globals["sdtNight"] = static_cast<lua_Number>(sdtNight);
    globals["sdtTotal"] = static_cast<lua_Number>(sdtTotal);
    globals["esvtInvalid"] = static_cast<lua_Number>(esvtInvalid);
    globals["esvtSceneLostFaction"] = static_cast<lua_Number>(esvtSceneLostFaction);
    globals["esvtTotal"] = static_cast<lua_Number>(esvtTotal);
    globals["estInvalid"] = static_cast<lua_Number>(estInvalid);
    globals["estStatic"] = static_cast<lua_Number>(estStatic);
    globals["estDungeon"] = static_cast<lua_Number>(estDungeon);
    globals["estBattleField"] = static_cast<lua_Number>(estBattleField);
    globals["estArena"] = static_cast<lua_Number>(estArena);
    globals["estLine"] = static_cast<lua_Number>(estLine);
    globals["estBirth"] = static_cast<lua_Number>(estBirth);
    globals["estGuild"] = static_cast<lua_Number>(estGuild);
    globals["estGuildDungeon"] = static_cast<lua_Number>(estGuildDungeon);
    globals["estUnique"] = static_cast<lua_Number>(estUnique);
    globals["estSoloDungeon"] = static_cast<lua_Number>(estSoloDungeon);
    globals["estTotal"] = static_cast<lua_Number>(estTotal);
    globals["lssInvalid"] = static_cast<lua_Number>(lssInvalid);
    globals["lssNormal"] = static_cast<lua_Number>(lssNormal);
    globals["lssBusy"] = static_cast<lua_Number>(lssBusy);
    globals["lssFull"] = static_cast<lua_Number>(lssFull);
    globals["lssTotal"] = static_cast<lua_Number>(lssTotal);
    globals["bodyInvalid"] = static_cast<lua_Number>(bodyInvalid);
    globals["body0x0"] = static_cast<lua_Number>(body0x0);
    globals["body1x1"] = static_cast<lua_Number>(body1x1);
    globals["body3x3"] = static_cast<lua_Number>(body3x3);
    globals["bodyTotal"] = static_cast<lua_Number>(bodyTotal);
    auto absolute_scene_pos_type = cqyh::lua::usertype<ABSOLUTE_SCENE_POS>(L, globals, "ABSOLUTE_SCENE_POS", "ABSOLUTE_SCENE_POS");
    absolute_scene_pos_type["nSceneTempID"] = sol::property([](const ABSOLUTE_SCENE_POS& self) { return self.nSceneTempID; }, [](ABSOLUTE_SCENE_POS& self, decltype(ABSOLUTE_SCENE_POS::nSceneTempID) value) { self.nSceneTempID = value; });
    absolute_scene_pos_type["nSceneID"] = sol::property([](const ABSOLUTE_SCENE_POS& self) { return self.nSceneID; }, [](ABSOLUTE_SCENE_POS& self, decltype(ABSOLUTE_SCENE_POS::nSceneID) value) { self.nSceneID = value; });
    absolute_scene_pos_type["nX"] = sol::property([](const ABSOLUTE_SCENE_POS& self) { return self.nX; }, [](ABSOLUTE_SCENE_POS& self, decltype(ABSOLUTE_SCENE_POS::nX) value) { self.nX = value; });
    absolute_scene_pos_type["nY"] = sol::property([](const ABSOLUTE_SCENE_POS& self) { return self.nY; }, [](ABSOLUTE_SCENE_POS& self, decltype(ABSOLUTE_SCENE_POS::nY) value) { self.nY = value; });
    absolute_scene_pos_type["nZ"] = sol::property([](const ABSOLUTE_SCENE_POS& self) { return self.nZ; }, [](ABSOLUTE_SCENE_POS& self, decltype(ABSOLUTE_SCENE_POS::nZ) value) { self.nZ = value; });
    absolute_scene_pos_type["nFaceDirection"] = sol::property([](const ABSOLUTE_SCENE_POS& self) { return self.nFaceDirection; }, [](ABSOLUTE_SCENE_POS& self, decltype(ABSOLUTE_SCENE_POS::nFaceDirection) value) { self.nFaceDirection = value; });
    auto enter_pos_type = cqyh::lua::usertype<ENTER_POS>(L, globals, "ENTER_POS", "ENTER_POS");
    enter_pos_type["nSceneTempID"] = sol::property([](const ENTER_POS& self) { return self.nSceneTempID; }, [](ENTER_POS& self, decltype(ENTER_POS::nSceneTempID) value) { self.nSceneTempID = value; });
    enter_pos_type["nSceneID"] = sol::property([](const ENTER_POS& self) { return self.nSceneID; }, [](ENTER_POS& self, decltype(ENTER_POS::nSceneID) value) { self.nSceneID = value; });
    enter_pos_type["bySide"] = sol::property([](const ENTER_POS& self) { return self.bySide; }, [](ENTER_POS& self, decltype(ENTER_POS::bySide) value) { self.bySide = value; });
    globals.set_function("ConvertCoordS2N", [](signed int llCoordination) -> decltype(auto) { return ConvertCoordS2N(llCoordination); });
    globals.set_function("ConvertCoordN2S", [](unsigned short wCoordination) -> decltype(auto) { return ConvertCoordN2S(wCoordination); });
    globals.set_function("I64_2_Double", [](signed int llPos) -> decltype(auto) { return I64_2_Double(llPos); });
    globals.set_function("ConvertCoordO2N", [](signed int rnX, signed int rnY, signed int rnZ) -> decltype(auto) { ConvertCoordO2N(rnX,rnY,rnZ); return std::make_tuple(rnX, rnY, rnZ); });
    globals.set_function("ConvertCoordN2O", [](signed int rnX, signed int rnY, signed int rnZ) -> decltype(auto) { ConvertCoordN2O(rnX,rnY,rnZ); return std::make_tuple(rnX, rnY, rnZ); });
}

}
