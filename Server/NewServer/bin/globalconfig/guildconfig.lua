GuildConfig = {


	-- guild
	nInitGuildCount = 256,
	--nInitGuildCount = 64000,
    nInitGuildAppPoolCount = 512,
	--nInitGuildAppPoolCount = 100000,
    nInitDiplomatAppPoolCount = 128,
	--nInitDiplomatAppPoolCount = 64000,
    nInitHistoryEventPoolCount = 4096,
	nInitStorageEventPoolCount = 4096,
	--nInitHistoryEventPoolCount = 16000000,
	nGuildUpgradeTriggerPool  = 1024,
	nGuildGuildWarPool	= 512,
	nGuildFightingPool	= 128,
	--nGuildSaveItemBufferPool  = 32000,
	nGuildBuildingRevivePool = 128,
	-- Item type ID required to create a guild
	nCanCreateGuildItemTypeID = 80002,
	-- Item quantity
    nCanCreateGuildItemNum = 1,
	-- Money required to create a guild
    nCanCreateGuildMoney = 200000,
	-- Character level required to create a guild
    nCanCreateGuildLevel = 17,
	-- Minimum level to join a guild
	nCanJoinGuildLevel = 17,
	-- Initial guild money
    nInitGuildMoney = 100000,
	-- Initial grain
	nWood = 100000,
	-- Initial wood
	nHerb = 100000,
	-- Initial stone
	nCrystal = 100000,
	-- Initial iron
	nSilver = 100000,

	-- Position permissions
	nInitGuildPositionRight =	-- 7 = GUILD_POSITION_COUNT
	{
		[0] = 0,		-- none
		[1] = 4095,		-- Guild leader
		[2] = 4095,		-- Deputy guild leader
		[3] = 495,		-- Elder
		[4] = 15,		-- Supervisor
		[5] = 3,		-- Deacon
		[6] = 1,		-- Registrar
		[7] = 0,		-- Guild member
	},

	-- Storage permissions
    nInitGuildStorageRight =		-- 7 = GUILD_POSITION_COUNT
	{
		[0] = 4095,		-- Guild leader
		[1] = 0,		-- Deputy guild leader
		[2] = 0,		-- Elder
		[3] = 0,		-- Hall master
		[4] = 0,		-- Deacon
		[5] = 0,		-- Registrar
		[6] = 0,		-- Guild member
	},

	-- Guild disband level limit
	nGuildDisbandLevelLimit = 3,

	-- Guild leave cooldown in seconds
    dwReJoinGuildCD = 0,

	-- Guild application lifetime in seconds
	nGuildApplicationLastTime = 300,

	-- Cost per guild storage withdrawal, defaulting to currency type 1 (bound money)
	nGuildPopItemComsumeMoney = 0,


	-- Maximum salary claim per withdrawal
	nInitGuildMaxSalary = 10000,

	-- Percentage of merit claimed as salary per withdrawal
	nGuildDrawSalaryPercent = 80,

	-- Weekly merit gain limit
	nGuildObtainMoneyLimitPerWeek = 10000,

	-- Guild salary interval (604800 seconds is one week)
	--nDrawSalaryPeriod = 604800,
	nDrawSalaryPeriod = 3600,

	-- Daily gold donation limit
	nMaxDonateMoneyPerDay =
	{
		[0] = 1,
		[1] = 100000000,		-- Guild leader
		[2] = 100000000,		-- Deputy
		[3] = 100000000,		-- Elder
		[4] = 100000000,
		[5] = 100000000,
		[6] = 100000000,
		[7] = 100000000,		-- Guild member
	},
	-- Daily resource donation limit
	nMaxDonateResPerDay =
	{
		[0] = 1,
		[1] = 100000000,		-- Guild leader
		[2] = 100000000,		-- Deputy
		[3] = 100000000,		-- Elder
		[4] = 100000000,
		[5] = 100000000,
		[6] = 100000000,
		[7] = 100000000,		-- Guild member
	},



	-- Alliance cost
	nAllianceConsumeMoney =
	{
		[0] = 100000,		-- 1 day
		[1] = 200000,		-- 3 days
		[2] = 500000,		-- 7 days
		[3] = 1000000,		-- 30 days
	},

	-- Enmity cost
	nEnemyConsumeMoney =
	{
		[0] = 100000,		-- 1 day
		[1] = 200000,		-- 3 days
		[2] = 500000,		-- 7 days
		[3] = 1000000,		-- 30 days
	},

	-- Guild alliance or enmity duration in seconds
	nGuildDiplomatLastTime =
	{
		[0] = 86400,		-- 1 day
		[1] = 259200,		-- 3 days
		[2] = 604800,		-- 7
		[3] = 2592000,		-- 30
	},

	-- Alliance application duration
	nDiplomatAppLastTime = 300,


	-- Resource refund percentage for canceling a building upgrade
	nBuildingUpgradeRefundPercent = 50,
	-- Resource refund percentage for deleting a building
	nDelBuildingRefundPercent = 33,
	-- Resource refund percentage for canceling a buff upgrade
    nWelfareBufferUpgradeRefundPercent = 50,
	-- Automatic resource growth percentage
    nAddResourceInterval = 3600,

	--Guild territory template ID
	dwSceneTemplateID = 127,
	-- Guild territory entry coordinates and facing
	nEnterMapPosX = 41355,
	nEnterMapPosY = 50258,
	nEnterMapPosZ = 7753,
	nEnterMapDirection = 1,

	-- Guild territory entry coordinates, SERVER_POINT
	dwServerPoint = 14,
	-- Entry coordinates for the opposing territory during a guild war
	dwTargetGuildServerPoint = 3,

	-- Royal city map template ID
	dwPalaceSceneTemplateID = 101,


	--Guild buildings
	szBMainNameID 		= "main01",
	szBBusinessNameID	= "Shop01";		-- Commerce hall
	szBDeityNameID		= "God01";		-- Shrine
	szBWonderNameID		= "Gtot01";

	-- Conditions to change royal city or guild territory weather: {gold, duration in seconds}
	arrWeatherCondition = {
		[0] = {nMoney = 9999999, nTime = 9999999}, -- invalid
		[1] = {nMoney = 50000, nTime = 300},		-- 50000 money, 300 s
		[2] = {nMoney = 100000, nTime = 600},	-- 100000, 600s
		[3] = {nMoney = 200000, nTime = 1800},	-- 200000, 1800s
	},

	-- Guild maintenance start time
	nRoutineConsumeTime = 4,		-- Starts daily at 04:00

	-- Guild activity reset time
	nGuildActivityResetHour = 4,

	nGuildActivityBeginHour1 = 0,
    nGuildActivityEndHour1 = 2,
    nGuildActivityBeginHour2 = 10,
    nGuildActivityEndHour2 = 24,


    ---------------------------- war ------------------------------------
	-- Guild war defense protection duration in seconds, measured from the day’s war start
	nGuildWarProtectionTime = 106200,

	-- War declaration cooldown in seconds, measured from the day’s war start
	nGuildWarAttackCD = 106200,



	-- Daily guild war start time in seconds; for example 13:00 = 3600*13; starts at 18:30
	nGuildWarReadyHour = 18,
	nGuildWarReadyMin = 20,

	nGuildWarBeginHour = 18,
	nGuildWarBeginMin = 30,

	nGuildWar10TipHour = 19,
	nGuildWar10TipMin = 20,

	nGuildWarEndHour = 19,
	nGuildWarEndMin = 30,


	-- Daily war declaration end time in seconds; entries below must match those above
	nGuildWarBeginTime = 66600,
	nGuildWarEndTime = 70200,--70200,

	-- Guild level required to participate in guild war
	nGuildSpecifyWarLevelLimit = 5,--3,

	-- Post-war teleport wait moved to the guild territory evtGuildWarEnd tree in main.lua
	-- Ask designer Ping Yi to update it; the unit there is milliseconds

	-- After a guild war, attackers cannot move or cast while the buff lasts and are teleported out when it expires
	nGuildWarAttackEndAuraID = 2500,

	-- After a guild war, defenders cannot move or cast while the buff lasts but are not teleported out on expiry
	nGuildWarDefendEndAuraID = 2500,


	-- Guild war victory spoils as a fraction of the total, in ten-thousandths
	nGuildWarMoneyPlunderPercent = 3000,
	nGuildWarResPlunderPercent = 3000,


	-- Additional guild war victory spoils, in ten-thousandths
	nGuildWarMoneyPlunder = 5000,
	nGuildWarResPlunder = 5000,

	---------------------------------------------------------------------

	--
	----------------------------- match war -----------------------------
	-- Minimum guild level for matched guild wars
	nGuildMatchWarLevelLimit = 1,

	-- Daily matched guild war limit
	nGuildMatchWarCountLimit = 5,

	-- Guild fund cost for a matched war
	nGuildMatchWarMoneyConsumption = 5000,

	-- Matched guild war event start time
	nGuildMatchWarBeginTime = 0,

	-- Matched guild war event end time
	nGuildMatchWarEndTime = 86400,


	nGuildWarAttackSuccMailID = 2018,
    nGuildWarAttackFailMailID = 2019,
    nGuildWarDefendSuccMailID = 2020,
    nGuildWarDefendFailMailID = 2021,

	---------------------------------------------------------------------


	-- Guild dungeon salary as a percentage of deducted dungeon gold
	nGuildDungeonSalaryPercent = 50,
	-- Guild dungeon refresh time: 04:00 expressed in seconds
	nGuildDungeonUpdateTime = 14400,

	-- Prosperity provided by guild members
	nGuildMemberBaseProsperity = 3,


	-- string map id
    dwDeclaredGuildWarToAllID = 2054,
    --dwBeginGuildWarToAllID = 2055,
    --dwBeginGuildWarToAttackID  = 2056,
    --dwBeginGuildWarToDefenceID = 2057,
    --dwGuildWarWonderDieToAttackID = 2058,
    --dwGuildWarWonderDieToDefenceID = 2059,
    --dwGuildWarEndAttackSuccessToAllID = 2060,
    --dwGuildWarEndAttackDefeatToAllID = 2061,
    --dwGuildWarEndAttackSuccessToAttackID = 2062,
    --dwGuildWarEndAttackSuccessToDefenceID = 2063,
    --dwGuildWarEndAttackDefeatToAttackID = 2064,
    --dwGuildWarEndAttackDefeatToDefenceID = 2065,
    dwGuildAllianceTVID = 2066,
    dwGuildEnemyTVID = 2067,

};

GuildConfig.nEnterMapPosX, GuildConfig.nEnterMapPosY, GuildConfig.nEnterMapPosZ =
	ConvertCoordO2N(GuildConfig.nEnterMapPosX, GuildConfig.nEnterMapPosY, GuildConfig.nEnterMapPosZ);
