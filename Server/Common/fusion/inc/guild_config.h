#ifndef _GUILD_CONFIG_H_
#define _GUILD_CONFIG_H_

#include "guild_def.h"
#pragma pack(push, 8)

struct GUILD_CONFIG 
{
    //guild
    INT32       nInitGuildCount;
    INT32       nInitGuildAppPoolCount;
    INT32       nInitDiplomatAppPoolCount;
    INT32       nInitHistoryEventPoolCount;
    INT32       nGuildUpgradeTriggerPool;
    INT32       nGuildGuildWarPool;
    INT32       nGuildFightingPool;
    INT32       nInitStorageEventPoolCount;
     INT32       nGuildBuildingRevivePool;

    INT32       nCanCreateGuildItemTypeID;
    INT32       nCanCreateGuildItemNum;
    INT32       nCanCreateGuildMoney;
    INT32       nCanCreateGuildLevel;
    INT32       nCanJoinGuildLevel;

    INT32       nInitGuildMoney;
    INT32       nWood;
    INT32       nHerb;
    INT32       nCrystal;
    INT32       nSilver;

    INT16       nInitGuildPositionRight[8]; // GUILD_POSITION_COUNT; skip index 0
    INT16       nInitGuildStorageRight[7];  // GUILD_POSITION_COUNT

    INT32       nGuildDisbandLevelLimit;
    UINT32      dwReJoinGuildCD;
    INT32       nGuildApplicationLastTime;
    INT32       nGuildPopItemComsumeMoney;

    // Salary
    INT32       nInitGuildMaxSalary;
    INT32       nGuildDrawSalaryPercent;
    INT32       nGuildObtainMoneyLimitPerWeek;
    INT32       nDrawSalaryPeriod;
    INT32       nMaxDonateMoneyPerDay[GUILD_POSITION_TOTAL];
    INT32       nMaxDonateResPerDay[GUILD_POSITION_TOTAL];

    INT32       nAllianceConsumeMoney[4];
    INT32       nEnemyConsumeMoney[4];
    UINT32      nGuildDiplomatLastTime[4];
    INT32       nDiplomatAppLastTime;


    // Refund percentage when canceling an upgrade
    INT32       nBuildingUpgradeRefundPercent;
    INT32       nDelBuildingRefundPercent;
    INT32       nWelfareBufferUpgradeRefundPercent;
    INT32       nAddResourceInterval;

    // Guild territory
    UINT32      dwSceneTemplateID;
    INT32       nEnterMapPosX;
    INT32       nEnterMapPosY;
    INT32       nEnterMapPosZ;
    INT32       nEnterMapDirection;
    UINT32      dwServerPoint;
    UINT32      dwTargetGuildServerPoint;

    // Royal city map
    UINT32      dwPalaceSceneTemplateID;

    char        szBMainNameID[8];
    char        szBBusinessNameID[8];
    char        szBDeityNameID[8];
    char        szBWonderNameID[8];

    struct CHANGE_WEATHER_CONDITION 
    {
        INT32       nMoney;
        INT32       nTime;
    };
    CHANGE_WEATHER_CONDITION    arrWeatherCondition[4];    // GUILD_CW_TIME_END

    INT32           nRoutineConsumeTime;

    INT32           nGuildActivityResetHour;

    INT32           nGuildActivityBeginHour1;
    INT32           nGuildActivityEndHour1;
    INT32           nGuildActivityBeginHour2;
    INT32           nGuildActivityEndHour2;

    //////////////////////////////////////////////////////////////////////////
    // guild war
    INT32           nGuildWarReadyHour;
    INT32           nGuildWarReadyMin;
    INT32           nGuildWarBeginHour;
    INT32           nGuildWarBeginMin;
    INT32           nGuildWar10TipHour;
    INT32           nGuildWar10TipMin;
    INT32           nGuildWarEndHour;
    INT32           nGuildWarEndMin;

    INT32           nGuildWarBeginTime;
    INT32           nGuildWarEndTime;
    INT32           nGuildWarScriptBeginTime;     // Additional code

    INT32           nGuildWarProtectionTime;
    INT32           nGuildWarAttackCD;
    INT32           nGuildSpecifyWarLevelLimit;

    INT32           nGuildWarAttackEndAuraID;
    INT32           nGuildWarDefendEndAuraID;

    INT32           nGuildWarMoneyPlunderPercent;       // Guild funds package rate, in ten-thousandths
    INT32           nGuildWarResPlunderPercent;         // Resource package rate, in ten-thousandths
    INT32           nGuildWarMoneyPlunder;              // Share of the opposing guild’s funds awarded for winning a guild war, in ten-thousandths
    INT32           nGuildWarResPlunder;                // Share of the opposing guild’s resources awarded for winning a guild war, in ten-thousandths
    //////////////////////////////////////////////////////////////////////////

    // match war
    INT32           nGuildMatchWarLevelLimit;
    INT32           nGuildMatchWarCountLimit;
    INT32           nGuildMatchWarMoneyConsumption;
    INT32           nGuildMatchWarBeginTime;
    INT32           nGuildMatchWarEndTime;


    INT32           nGuildWarAttackSuccMailID;
    INT32           nGuildWarAttackFailMailID;
    INT32           nGuildWarDefendSuccMailID;
    INT32           nGuildWarDefendFailMailID;

    //////////////////////////////////////////////////////////////////////////

    INT32           nGuildDungeonUpdateTime;        // Time of 4 a.m. in seconds
    INT32           nGuildDungeonSalaryPercent;

    // guild prosperity
    INT32           nGuildMemberBaseProsperity;

    // string map id
    UINT32          dwDeclaredGuildWarToAllID;
    //UINT32          dwBeginGuildWarToAllID;
    //UINT32          dwBeginGuildWarToAttackID;
    //UINT32          dwBeginGuildWarToDefenceID;
    //UINT32          dwGuildWarWonderDieToAttackID;
    //UINT32          dwGuildWarWonderDieToDefenceID;
    //UINT32          dwGuildWarEndAttackSuccessToAllID;
    //UINT32          dwGuildWarEndAttackDefeatToAllID;
    //UINT32          dwGuildWarEndAttackSuccessToAttackID;
    //UINT32          dwGuildWarEndAttackSuccessToDefenceID;
    //UINT32          dwGuildWarEndAttackDefeatToAttackID;
    //UINT32          dwGuildWarEndAttackDefeatToDefenceID;
    UINT32          dwGuildAllianceTVID;
    UINT32          dwGuildEnemyTVID;



};

extern GUILD_CONFIG g_GuildConfig;

#pragma pack(pop)


#endif  // _GUILD_CONFIG_H_