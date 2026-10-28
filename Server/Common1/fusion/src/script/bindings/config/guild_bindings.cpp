#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/guild_config.h"

namespace cqyh::fusion::bindings {

void register_guild_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto guild_config_type = cqyh::lua::usertype<GUILD_CONFIG>(L, globals, "GUILD_CONFIG", "GUILD_CONFIG");
    guild_config_type["nInitGuildCount"] = sol::property([](const GUILD_CONFIG& self) { return self.nInitGuildCount; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nInitGuildCount) value) { self.nInitGuildCount = value; });
    guild_config_type["nInitGuildAppPoolCount"] = sol::property([](const GUILD_CONFIG& self) { return self.nInitGuildAppPoolCount; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nInitGuildAppPoolCount) value) { self.nInitGuildAppPoolCount = value; });
    guild_config_type["nInitDiplomatAppPoolCount"] = sol::property([](const GUILD_CONFIG& self) { return self.nInitDiplomatAppPoolCount; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nInitDiplomatAppPoolCount) value) { self.nInitDiplomatAppPoolCount = value; });
    guild_config_type["nInitHistoryEventPoolCount"] = sol::property([](const GUILD_CONFIG& self) { return self.nInitHistoryEventPoolCount; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nInitHistoryEventPoolCount) value) { self.nInitHistoryEventPoolCount = value; });
    guild_config_type["nGuildUpgradeTriggerPool"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildUpgradeTriggerPool; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildUpgradeTriggerPool) value) { self.nGuildUpgradeTriggerPool = value; });
    guild_config_type["nGuildGuildWarPool"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildGuildWarPool; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildGuildWarPool) value) { self.nGuildGuildWarPool = value; });
    guild_config_type["nGuildFightingPool"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildFightingPool; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildFightingPool) value) { self.nGuildFightingPool = value; });
    guild_config_type["nInitStorageEventPoolCount"] = sol::property([](const GUILD_CONFIG& self) { return self.nInitStorageEventPoolCount; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nInitStorageEventPoolCount) value) { self.nInitStorageEventPoolCount = value; });
    guild_config_type["nGuildBuildingRevivePool"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildBuildingRevivePool; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildBuildingRevivePool) value) { self.nGuildBuildingRevivePool = value; });
    guild_config_type["nCanCreateGuildItemTypeID"] = sol::property([](const GUILD_CONFIG& self) { return self.nCanCreateGuildItemTypeID; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nCanCreateGuildItemTypeID) value) { self.nCanCreateGuildItemTypeID = value; });
    guild_config_type["nCanCreateGuildItemNum"] = sol::property([](const GUILD_CONFIG& self) { return self.nCanCreateGuildItemNum; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nCanCreateGuildItemNum) value) { self.nCanCreateGuildItemNum = value; });
    guild_config_type["nCanCreateGuildMoney"] = sol::property([](const GUILD_CONFIG& self) { return self.nCanCreateGuildMoney; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nCanCreateGuildMoney) value) { self.nCanCreateGuildMoney = value; });
    guild_config_type["nCanCreateGuildLevel"] = sol::property([](const GUILD_CONFIG& self) { return self.nCanCreateGuildLevel; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nCanCreateGuildLevel) value) { self.nCanCreateGuildLevel = value; });
    guild_config_type["nCanJoinGuildLevel"] = sol::property([](const GUILD_CONFIG& self) { return self.nCanJoinGuildLevel; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nCanJoinGuildLevel) value) { self.nCanJoinGuildLevel = value; });
    guild_config_type["nInitGuildMoney"] = sol::property([](const GUILD_CONFIG& self) { return self.nInitGuildMoney; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nInitGuildMoney) value) { self.nInitGuildMoney = value; });
    guild_config_type["nWood"] = sol::property([](const GUILD_CONFIG& self) { return self.nWood; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nWood) value) { self.nWood = value; });
    guild_config_type["nHerb"] = sol::property([](const GUILD_CONFIG& self) { return self.nHerb; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nHerb) value) { self.nHerb = value; });
    guild_config_type["nCrystal"] = sol::property([](const GUILD_CONFIG& self) { return self.nCrystal; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nCrystal) value) { self.nCrystal = value; });
    guild_config_type["nSilver"] = sol::property([](const GUILD_CONFIG& self) { return self.nSilver; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nSilver) value) { self.nSilver = value; });
    guild_config_type["nInitGuildPositionRight"] = cqyh::lua::array_property(&GUILD_CONFIG::nInitGuildPositionRight);
    guild_config_type["nInitGuildStorageRight"] = cqyh::lua::array_property(&GUILD_CONFIG::nInitGuildStorageRight);
    guild_config_type["nGuildDisbandLevelLimit"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildDisbandLevelLimit; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildDisbandLevelLimit) value) { self.nGuildDisbandLevelLimit = value; });
    guild_config_type["dwReJoinGuildCD"] = sol::property([](const GUILD_CONFIG& self) { return self.dwReJoinGuildCD; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::dwReJoinGuildCD) value) { self.dwReJoinGuildCD = value; });
    guild_config_type["nGuildApplicationLastTime"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildApplicationLastTime; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildApplicationLastTime) value) { self.nGuildApplicationLastTime = value; });
    guild_config_type["nGuildPopItemComsumeMoney"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildPopItemComsumeMoney; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildPopItemComsumeMoney) value) { self.nGuildPopItemComsumeMoney = value; });
    guild_config_type["nInitGuildMaxSalary"] = sol::property([](const GUILD_CONFIG& self) { return self.nInitGuildMaxSalary; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nInitGuildMaxSalary) value) { self.nInitGuildMaxSalary = value; });
    guild_config_type["nGuildDrawSalaryPercent"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildDrawSalaryPercent; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildDrawSalaryPercent) value) { self.nGuildDrawSalaryPercent = value; });
    guild_config_type["nGuildObtainMoneyLimitPerWeek"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildObtainMoneyLimitPerWeek; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildObtainMoneyLimitPerWeek) value) { self.nGuildObtainMoneyLimitPerWeek = value; });
    guild_config_type["nDrawSalaryPeriod"] = sol::property([](const GUILD_CONFIG& self) { return self.nDrawSalaryPeriod; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nDrawSalaryPeriod) value) { self.nDrawSalaryPeriod = value; });
    guild_config_type["nMaxDonateMoneyPerDay"] = cqyh::lua::array_property(&GUILD_CONFIG::nMaxDonateMoneyPerDay);
    guild_config_type["nMaxDonateResPerDay"] = cqyh::lua::array_property(&GUILD_CONFIG::nMaxDonateResPerDay);
    guild_config_type["nAllianceConsumeMoney"] = cqyh::lua::array_property(&GUILD_CONFIG::nAllianceConsumeMoney);
    guild_config_type["nEnemyConsumeMoney"] = cqyh::lua::array_property(&GUILD_CONFIG::nEnemyConsumeMoney);
    guild_config_type["nGuildDiplomatLastTime"] = cqyh::lua::array_property(&GUILD_CONFIG::nGuildDiplomatLastTime);
    guild_config_type["nDiplomatAppLastTime"] = sol::property([](const GUILD_CONFIG& self) { return self.nDiplomatAppLastTime; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nDiplomatAppLastTime) value) { self.nDiplomatAppLastTime = value; });
    guild_config_type["nBuildingUpgradeRefundPercent"] = sol::property([](const GUILD_CONFIG& self) { return self.nBuildingUpgradeRefundPercent; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nBuildingUpgradeRefundPercent) value) { self.nBuildingUpgradeRefundPercent = value; });
    guild_config_type["nDelBuildingRefundPercent"] = sol::property([](const GUILD_CONFIG& self) { return self.nDelBuildingRefundPercent; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nDelBuildingRefundPercent) value) { self.nDelBuildingRefundPercent = value; });
    guild_config_type["nWelfareBufferUpgradeRefundPercent"] = sol::property([](const GUILD_CONFIG& self) { return self.nWelfareBufferUpgradeRefundPercent; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nWelfareBufferUpgradeRefundPercent) value) { self.nWelfareBufferUpgradeRefundPercent = value; });
    guild_config_type["nAddResourceInterval"] = sol::property([](const GUILD_CONFIG& self) { return self.nAddResourceInterval; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nAddResourceInterval) value) { self.nAddResourceInterval = value; });
    guild_config_type["dwSceneTemplateID"] = sol::property([](const GUILD_CONFIG& self) { return self.dwSceneTemplateID; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::dwSceneTemplateID) value) { self.dwSceneTemplateID = value; });
    guild_config_type["nEnterMapPosX"] = sol::property([](const GUILD_CONFIG& self) { return self.nEnterMapPosX; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nEnterMapPosX) value) { self.nEnterMapPosX = value; });
    guild_config_type["nEnterMapPosY"] = sol::property([](const GUILD_CONFIG& self) { return self.nEnterMapPosY; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nEnterMapPosY) value) { self.nEnterMapPosY = value; });
    guild_config_type["nEnterMapPosZ"] = sol::property([](const GUILD_CONFIG& self) { return self.nEnterMapPosZ; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nEnterMapPosZ) value) { self.nEnterMapPosZ = value; });
    guild_config_type["nEnterMapDirection"] = sol::property([](const GUILD_CONFIG& self) { return self.nEnterMapDirection; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nEnterMapDirection) value) { self.nEnterMapDirection = value; });
    guild_config_type["dwServerPoint"] = sol::property([](const GUILD_CONFIG& self) { return self.dwServerPoint; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::dwServerPoint) value) { self.dwServerPoint = value; });
    guild_config_type["dwTargetGuildServerPoint"] = sol::property([](const GUILD_CONFIG& self) { return self.dwTargetGuildServerPoint; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::dwTargetGuildServerPoint) value) { self.dwTargetGuildServerPoint = value; });
    guild_config_type["dwPalaceSceneTemplateID"] = sol::property([](const GUILD_CONFIG& self) { return self.dwPalaceSceneTemplateID; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::dwPalaceSceneTemplateID) value) { self.dwPalaceSceneTemplateID = value; });
    guild_config_type["szBMainNameID"] = cqyh::lua::string_property(&GUILD_CONFIG::szBMainNameID);
    guild_config_type["szBBusinessNameID"] = cqyh::lua::string_property(&GUILD_CONFIG::szBBusinessNameID);
    guild_config_type["szBDeityNameID"] = cqyh::lua::string_property(&GUILD_CONFIG::szBDeityNameID);
    guild_config_type["szBWonderNameID"] = cqyh::lua::string_property(&GUILD_CONFIG::szBWonderNameID);
    auto change_weather_condition_type = cqyh::lua::usertype<GUILD_CONFIG::CHANGE_WEATHER_CONDITION>(L, guild_config_type, "CHANGE_WEATHER_CONDITION", "GUILD_CONFIG::CHANGE_WEATHER_CONDITION");
    change_weather_condition_type["nMoney"] = sol::property([](const GUILD_CONFIG::CHANGE_WEATHER_CONDITION& self) { return self.nMoney; }, [](GUILD_CONFIG::CHANGE_WEATHER_CONDITION& self, decltype(GUILD_CONFIG::CHANGE_WEATHER_CONDITION::nMoney) value) { self.nMoney = value; });
    change_weather_condition_type["nTime"] = sol::property([](const GUILD_CONFIG::CHANGE_WEATHER_CONDITION& self) { return self.nTime; }, [](GUILD_CONFIG::CHANGE_WEATHER_CONDITION& self, decltype(GUILD_CONFIG::CHANGE_WEATHER_CONDITION::nTime) value) { self.nTime = value; });
    guild_config_type["arrWeatherCondition"] = cqyh::lua::array_property(&GUILD_CONFIG::arrWeatherCondition);
    guild_config_type["nRoutineConsumeTime"] = sol::property([](const GUILD_CONFIG& self) { return self.nRoutineConsumeTime; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nRoutineConsumeTime) value) { self.nRoutineConsumeTime = value; });
    guild_config_type["nGuildWarBeginTime"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildWarBeginTime; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildWarBeginTime) value) { self.nGuildWarBeginTime = value; });
    guild_config_type["nGuildWarScriptBeginTime"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildWarScriptBeginTime; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildWarScriptBeginTime) value) { self.nGuildWarScriptBeginTime = value; });
    guild_config_type["nGuildWarEndTime"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildWarEndTime; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildWarEndTime) value) { self.nGuildWarEndTime = value; });
    guild_config_type["nGuildWarProtectionTime"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildWarProtectionTime; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildWarProtectionTime) value) { self.nGuildWarProtectionTime = value; });
    guild_config_type["nGuildWarAttackCD"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildWarAttackCD; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildWarAttackCD) value) { self.nGuildWarAttackCD = value; });
    guild_config_type["nGuildDeclareBeginTime"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildDeclareBeginTime; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildDeclareBeginTime) value) { self.nGuildDeclareBeginTime = value; });
    guild_config_type["nGuildDeclareEndTime"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildDeclareEndTime; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildDeclareEndTime) value) { self.nGuildDeclareEndTime = value; });
    guild_config_type["nGuildSpecifyWarLevelLimit"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildSpecifyWarLevelLimit; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildSpecifyWarLevelLimit) value) { self.nGuildSpecifyWarLevelLimit = value; });
    guild_config_type["nGuildWarAttackEndAuraID"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildWarAttackEndAuraID; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildWarAttackEndAuraID) value) { self.nGuildWarAttackEndAuraID = value; });
    guild_config_type["nGuildWarDefendEndAuraID"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildWarDefendEndAuraID; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildWarDefendEndAuraID) value) { self.nGuildWarDefendEndAuraID = value; });
    guild_config_type["nGuildWarMoneyPlunderPercent"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildWarMoneyPlunderPercent; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildWarMoneyPlunderPercent) value) { self.nGuildWarMoneyPlunderPercent = value; });
    guild_config_type["nGuildWarResPlunderPercent"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildWarResPlunderPercent; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildWarResPlunderPercent) value) { self.nGuildWarResPlunderPercent = value; });
    guild_config_type["nGuildWarMoneyPlunder"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildWarMoneyPlunder; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildWarMoneyPlunder) value) { self.nGuildWarMoneyPlunder = value; });
    guild_config_type["nGuildWarResPlunder"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildWarResPlunder; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildWarResPlunder) value) { self.nGuildWarResPlunder = value; });
    guild_config_type["nGuildMatchWarLevelLimit"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildMatchWarLevelLimit; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildMatchWarLevelLimit) value) { self.nGuildMatchWarLevelLimit = value; });
    guild_config_type["nGuildMatchWarCountLimit"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildMatchWarCountLimit; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildMatchWarCountLimit) value) { self.nGuildMatchWarCountLimit = value; });
    guild_config_type["nGuildMatchWarMoneyConsumption"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildMatchWarMoneyConsumption; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildMatchWarMoneyConsumption) value) { self.nGuildMatchWarMoneyConsumption = value; });
    guild_config_type["nGuildMatchWarBeginTime"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildMatchWarBeginTime; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildMatchWarBeginTime) value) { self.nGuildMatchWarBeginTime = value; });
    guild_config_type["nGuildMatchWarEndTime"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildMatchWarEndTime; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildMatchWarEndTime) value) { self.nGuildMatchWarEndTime = value; });
    guild_config_type["nGuildDungeonUpdateTime"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildDungeonUpdateTime; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildDungeonUpdateTime) value) { self.nGuildDungeonUpdateTime = value; });
    guild_config_type["nGuildDungeonSalaryPercent"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildDungeonSalaryPercent; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildDungeonSalaryPercent) value) { self.nGuildDungeonSalaryPercent = value; });
    guild_config_type["nGuildMemberBaseProsperity"] = sol::property([](const GUILD_CONFIG& self) { return self.nGuildMemberBaseProsperity; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::nGuildMemberBaseProsperity) value) { self.nGuildMemberBaseProsperity = value; });
    guild_config_type["dwDeclaredGuildWarToAllID"] = sol::property([](const GUILD_CONFIG& self) { return self.dwDeclaredGuildWarToAllID; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::dwDeclaredGuildWarToAllID) value) { self.dwDeclaredGuildWarToAllID = value; });
    guild_config_type["dwGuildAllianceTVID"] = sol::property([](const GUILD_CONFIG& self) { return self.dwGuildAllianceTVID; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::dwGuildAllianceTVID) value) { self.dwGuildAllianceTVID = value; });
    guild_config_type["dwGuildEnemyTVID"] = sol::property([](const GUILD_CONFIG& self) { return self.dwGuildEnemyTVID; }, [](GUILD_CONFIG& self, decltype(GUILD_CONFIG::dwGuildEnemyTVID) value) { self.dwGuildEnemyTVID = value; });
    globals["g_GuildConfig"] = &g_GuildConfig;
}

}
