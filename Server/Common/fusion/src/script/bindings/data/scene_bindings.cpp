#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/scene_data.h"
#include "../../../../../../NewServer/inc/baselib/data_manager.h"
#include "../../../../../../NewServer/inc/baselib/weight_rand.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"
#include "../../../../../define/item_def.h"

namespace cqyh::fusion::bindings {

void register_scene_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto scene_data_type = cqyh::lua::usertype<SCENE_DATA>(L, globals, "SCENE_DATA", "SCENE_DATA");
    scene_data_type["nSceneID"] = sol::property([](const SCENE_DATA& self) { return self.nSceneID; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nSceneID) value) { self.nSceneID = value; });
    scene_data_type["szConfigName"] = cqyh::lua::string_property(&SCENE_DATA::szConfigName);
    scene_data_type["szMapDisplayName"] = cqyh::lua::string_property(&SCENE_DATA::szMapDisplayName);
    scene_data_type["nType"] = sol::property([](const SCENE_DATA& self) { return self.nType; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nType) value) { self.nType = value; });
    scene_data_type["nMaxRoleCount"] = sol::property([](const SCENE_DATA& self) { return self.nMaxRoleCount; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nMaxRoleCount) value) { self.nMaxRoleCount = value; });
    scene_data_type["nFinishTarget"] = sol::property([](const SCENE_DATA& self) { return self.nFinishTarget; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nFinishTarget) value) { self.nFinishTarget = value; });
    scene_data_type["bCannotUseScroll"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotUseScroll); }, [](SCENE_DATA& self, bool value) { self.bCannotUseScroll = value; });
    scene_data_type["bCannotUseTeleportRing"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotUseTeleportRing); }, [](SCENE_DATA& self, bool value) { self.bCannotUseTeleportRing = value; });
    scene_data_type["bCannotBeRecalled"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotBeRecalled); }, [](SCENE_DATA& self, bool value) { self.bCannotBeRecalled = value; });
    scene_data_type["bCannotTrade"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotTrade); }, [](SCENE_DATA& self, bool value) { self.bCannotTrade = value; });
    scene_data_type["bCannotLoseDurability"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotLoseDurability); }, [](SCENE_DATA& self, bool value) { self.bCannotLoseDurability = value; });
    scene_data_type["bCannotSendMail"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotSendMail); }, [](SCENE_DATA& self, bool value) { self.bCannotSendMail = value; });
    scene_data_type["bCannotUseExchange"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotUseExchange); }, [](SCENE_DATA& self, bool value) { self.bCannotUseExchange = value; });
    scene_data_type["bCannotUseAuction"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotUseAuction); }, [](SCENE_DATA& self, bool value) { self.bCannotUseAuction = value; });
    scene_data_type["bCannotJoinTeam"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotJoinTeam); }, [](SCENE_DATA& self, bool value) { self.bCannotJoinTeam = value; });
    scene_data_type["bEnableAntiCheat"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bEnableAntiCheat); }, [](SCENE_DATA& self, bool value) { self.bEnableAntiCheat = value; });
    scene_data_type["bBlockRole"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bBlockRole); }, [](SCENE_DATA& self, bool value) { self.bBlockRole = value; });
    scene_data_type["bCannotGroupChat"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotGroupChat); }, [](SCENE_DATA& self, bool value) { self.bCannotGroupChat = value; });
    scene_data_type["bCannotSceneChat"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotSceneChat); }, [](SCENE_DATA& self, bool value) { self.bCannotSceneChat = value; });
    scene_data_type["bCannotScreenChat"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotScreenChat); }, [](SCENE_DATA& self, bool value) { self.bCannotScreenChat = value; });
    scene_data_type["bCannotWhisperChat"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotWhisperChat); }, [](SCENE_DATA& self, bool value) { self.bCannotWhisperChat = value; });
    scene_data_type["bCannotTeamChat"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotTeamChat); }, [](SCENE_DATA& self, bool value) { self.bCannotTeamChat = value; });
    scene_data_type["bCannotGuildChat"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotGuildChat); }, [](SCENE_DATA& self, bool value) { self.bCannotGuildChat = value; });
    scene_data_type["bCannotFriendChat"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bCannotFriendChat); }, [](SCENE_DATA& self, bool value) { self.bCannotFriendChat = value; });
    scene_data_type["nMinPortalLevel"] = sol::property([](const SCENE_DATA& self) { return self.nMinPortalLevel; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nMinPortalLevel) value) { self.nMinPortalLevel = value; });
    scene_data_type["nMaxPortalLevel"] = sol::property([](const SCENE_DATA& self) { return self.nMaxPortalLevel; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nMaxPortalLevel) value) { self.nMaxPortalLevel = value; });
    auto weather_data_type = cqyh::lua::usertype<SCENE_DATA::WEATHER_DATA>(L, scene_data_type, "WEATHER_DATA", "SCENE_DATA::WEATHER_DATA");
    weather_data_type["nWeather"] = sol::property([](const SCENE_DATA::WEATHER_DATA& self) { return self.nWeather; }, [](SCENE_DATA::WEATHER_DATA& self, decltype(SCENE_DATA::WEATHER_DATA::nWeather) value) { self.nWeather = value; });
    weather_data_type["nWeight"] = sol::property([](const SCENE_DATA::WEATHER_DATA& self) { return self.nWeight; }, [](SCENE_DATA::WEATHER_DATA& self, decltype(SCENE_DATA::WEATHER_DATA::nWeight) value) { self.nWeight = value; });
    weather_data_type["nMinDuration"] = sol::property([](const SCENE_DATA::WEATHER_DATA& self) { return self.nMinDuration; }, [](SCENE_DATA::WEATHER_DATA& self, decltype(SCENE_DATA::WEATHER_DATA::nMinDuration) value) { self.nMinDuration = value; });
    weather_data_type["nMaxDuration"] = sol::property([](const SCENE_DATA::WEATHER_DATA& self) { return self.nMaxDuration; }, [](SCENE_DATA::WEATHER_DATA& self, decltype(SCENE_DATA::WEATHER_DATA::nMaxDuration) value) { self.nMaxDuration = value; });
    scene_data_type["WeatherData"] = cqyh::lua::array_property(&SCENE_DATA::WeatherData);
    scene_data_type["nMinWeatherRefreshInterval"] = sol::property([](const SCENE_DATA& self) { return self.nMinWeatherRefreshInterval; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nMinWeatherRefreshInterval) value) { self.nMinWeatherRefreshInterval = value; });
    scene_data_type["nMaxWeatherRefreshInterval"] = sol::property([](const SCENE_DATA& self) { return self.nMaxWeatherRefreshInterval; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nMaxWeatherRefreshInterval) value) { self.nMaxWeatherRefreshInterval = value; });
    scene_data_type["RandWeather"] = &SCENE_DATA::RandWeather;
    scene_data_type["nMinPlayerLevel"] = sol::property([](const SCENE_DATA& self) { return self.nMinPlayerLevel; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nMinPlayerLevel) value) { self.nMinPlayerLevel = value; });
    scene_data_type["nMaxPlayerLevel"] = sol::property([](const SCENE_DATA& self) { return self.nMaxPlayerLevel; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nMaxPlayerLevel) value) { self.nMaxPlayerLevel = value; });
    scene_data_type["nInitCount"] = sol::property([](const SCENE_DATA& self) { return self.nInitCount; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nInitCount) value) { self.nInitCount = value; });
    scene_data_type["nSideCount"] = sol::property([](const SCENE_DATA& self) { return self.nSideCount; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nSideCount) value) { self.nSideCount = value; });
    scene_data_type["nBattleType"] = sol::property([](const SCENE_DATA& self) { return self.nBattleType; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nBattleType) value) { self.nBattleType = value; });
    scene_data_type["nMinRoleLimitPerSide"] = sol::property([](const SCENE_DATA& self) { return self.nMinRoleLimitPerSide; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nMinRoleLimitPerSide) value) { self.nMinRoleLimitPerSide = value; });
    scene_data_type["nMaxRoleLimitPerSide"] = sol::property([](const SCENE_DATA& self) { return self.nMaxRoleLimitPerSide; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nMaxRoleLimitPerSide) value) { self.nMaxRoleLimitPerSide = value; });
    scene_data_type["nHandbookType"] = sol::property([](const SCENE_DATA& self) { return self.nHandbookType; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nHandbookType) value) { self.nHandbookType = value; });
    scene_data_type["nHandbookIndex"] = sol::property([](const SCENE_DATA& self) { return self.nHandbookIndex; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nHandbookIndex) value) { self.nHandbookIndex = value; });
    scene_data_type["nLoginJumpSceneTempID"] = sol::property([](const SCENE_DATA& self) { return self.nLoginJumpSceneTempID; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nLoginJumpSceneTempID) value) { self.nLoginJumpSceneTempID = value; });
    scene_data_type["nLoginJumpX"] = sol::property([](const SCENE_DATA& self) { return self.nLoginJumpX; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nLoginJumpX) value) { self.nLoginJumpX = value; });
    scene_data_type["nLoginJumpY"] = sol::property([](const SCENE_DATA& self) { return self.nLoginJumpY; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nLoginJumpY) value) { self.nLoginJumpY = value; });
    scene_data_type["nLoginJumpZ"] = sol::property([](const SCENE_DATA& self) { return self.nLoginJumpZ; }, [](SCENE_DATA& self, decltype(SCENE_DATA::nLoginJumpZ) value) { self.nLoginJumpZ = value; });
    scene_data_type["bEnableIntimacy"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bEnableIntimacy); }, [](SCENE_DATA& self, bool value) { self.bEnableIntimacy = value; });
    scene_data_type["bGpkPunish"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bGpkPunish); }, [](SCENE_DATA& self, bool value) { self.bGpkPunish = value; });
    scene_data_type["bGpkKick"] = sol::property([](const SCENE_DATA& self) { return static_cast<bool>(self.bGpkKick); }, [](SCENE_DATA& self, bool value) { self.bGpkKick = value; });
    scene_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, SCENE_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(SCENE_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    auto c_data_manager_scene_data_type = cqyh::lua::usertype<CDataManager<SCENE_DATA>>(L, globals, "CDataManager_SCENE_DATA_", "CDataManager<SCENE_DATA>");
    c_data_manager_scene_data_type.set_function("GetInstance", []() -> decltype(auto) { return CDataManager<SCENE_DATA>::GetInstance(); });
    c_data_manager_scene_data_type.set_function("GetDataCount", [](CDataManager<SCENE_DATA>* self) -> decltype(auto) { return self->GetDataCount(); });
    c_data_manager_scene_data_type.set_function("GetData", [](CDataManager<SCENE_DATA>* self, signed int nDataID) -> decltype(auto) { return self->GetData(nDataID); });
    c_data_manager_scene_data_type.set_function("GetID", [](CDataManager<SCENE_DATA>* self, const char* pcszName) -> decltype(auto) { return self->GetID(pcszName); });
    c_data_manager_scene_data_type.set_function("GetFirstData", [](CDataManager<SCENE_DATA>* self) -> decltype(auto) { return self->GetFirstData(); });
    c_data_manager_scene_data_type.set_function("GetNextData", [](CDataManager<SCENE_DATA>* self) -> decltype(auto) { return self->GetNextData(); });
}

}
