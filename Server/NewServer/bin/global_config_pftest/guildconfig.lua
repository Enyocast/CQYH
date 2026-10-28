GLOBAL_CONFIG["GuildConfig"] = {


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
	nGuildGuildWarTriggerPool	= 512,
	--nGuildSaveItemBufferPool  = 32000,

	-- Item type ID required to create a guild
	nCanCreateGuildItemTypeID = 80002,
	-- Item quantity
    nCanCreateGuildItemNum = 1,
	-- Money required to create a guild
    nCanCreateGuildMoney = 50000,
	-- Character level required to create a guild
    nCanCreateGuildLevel = 10,
	-- Initial guild money
    nInitGuildMoney = 10000,
	-- Initial wood
	nWood = 10000,
	-- Initial herbs
	nHerb = 10000,
	-- Initial crystals
	nCrystal = 10000,
	-- Initial mithril
	nSilver = 10000,

	-- Position permissions
	nInitGuildPositionRight =	-- 7 = GUILD_POSITION_COUNT
	{
		[0] = 0,		-- none
		[1] = 4095,		-- Guild leader
		[2] = 2047,		-- Deputy guild leader
		[3] = 255,		-- Elder
		[4] = 15,		-- Hall master
		[5] = 7,		-- Deacon
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
    dwReJoinGuildCD = 7200,

	-- Guild application lifetime in seconds
	nGuildApplicationLastTime = 300,

	-- Cost per guild storage withdrawal, defaulting to currency type 1 (bound money)
	nGuildPopItemComsumeMoney = 100,




	-- Maximum salary claim per withdrawal
	nInitGuildMaxSalary = 10000,

	-- Percentage of merit claimed as salary per withdrawal
	nGuildDrawSalaryPercent = 80,

	-- Weekly merit gain limit
	nGuildObtainMoneyLimitPerWeek = 10000,

	-- Guild salary interval (604800 seconds is one week)
	--nDrawSalaryPeriod = 604800,
	nDrawSalaryPeriod = 3600,

	-- Daily guild contribution gain limit
	nEarnMaxContributionPerDay = 10000,
	-- Weekly guild contribution gain limit
	nEarnMaxContributionPerWeek = 100000,



	-- Alliance cost
	nAllianceConsumeMoney =
	{
		[0] = 100,		-- 1 day
		[1] = 500,		-- 3 days
		[2] = 2000,		-- 7 days
		[3] = 10000,	-- 30 days
	},

	-- Enmity cost
	nEnemyConsumeMoney =
	{
		[0] = 1000,		-- 1 day
		[1] = 5000,		-- 3 days
		[2] = 20000,	-- 7 days
		[3] = 100000,	-- 30 days
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
	-- Resource refund percentage for canceling a buff upgrade
    nWelfareBufferUpgradeRefundPercent = 50,
	-- Automatic resource growth percentage
    nAddResourceInterval = 3600,

	--Guild territory template ID
	dwSceneTemplateID = 127,
	-- Guild territory entry coordinates and facing
	nEnterMapPosX = 51283,
	nEnterMapPosY = 17682,
	nEnterMapPosZ = 16288,
	nEnterMapDirection = 1,

	-- Guild territory entry coordinates, SERVER_POINT
	dwServerPoint = 14,
	-- Entry coordinates for the opposing territory during a guild war
	dwTargetGuildServerPoint = 15,

	-- Royal city map template ID
	dwPalaceSceneTemplateID = 101,


	--Guild buildings
	arrBuildingData = {
		[0] = {nSvrUniqueID = 1, nLevel = 1},	-- none
		[1] = {nSvrUniqueID = 28, nLevel = 1},	-- Main hall
		[2] = {nSvrUniqueID = 8, nLevel = 1},	-- Training hall
		[3] = {nSvrUniqueID = 14, nLevel = 1},	-- Commerce hall
		--[3] = {nSvrUniqueID = 7, nLevel = 1},	-- War hall
		[4] = {nSvrUniqueID = 33, nLevel = 1},	-- Hall of Worthies
		[5] = {nSvrUniqueID = 15, nLevel = 1},	-- Treasury
		[6] = {nSvrUniqueID = 39, nLevel = 1},	-- War council
		[7] = {nSvrUniqueID = 12, nLevel = 1},	-- Totem
		[8] = {nSvrUniqueID = 23, nLevel = 1},	-- Farm
		[9] = {nSvrUniqueID = 20, nLevel = 1},	-- Lumber yard
		[10] = {nSvrUniqueID = 16, nLevel = 1},	-- Quarry
		[11] = {nSvrUniqueID = 18, nLevel = 1},	-- Mine
		[12] = {nSvrUniqueID = 22, nLevel = 1},	-- Granary
		[13] = {nSvrUniqueID = 21, nLevel = 1},	-- Lumber storage
		[14] = {nSvrUniqueID = 17, nLevel = 1},	-- Stone storage
		[15] = {nSvrUniqueID = 19, nLevel = 1},	-- Ore storage
	},

	-- Conditions to change royal city or guild territory weather: {gold, duration in seconds}
	arrWeatherCondition = {
		[0] = {nMoney = 9999999, nTime = 9999999}, -- invalid
		[1] = {nMoney = 50000, nTime = 300},		-- 50000 money, 300 s
		[2] = {nMoney = 100000, nTime = 600},	-- 100000, 600s
		[3] = {nMoney = 200000, nTime = 1800},	-- 200000, 1800s
	},

	-- Guild maintenance start time
	nRoutineConsumeTime = 4,		-- Starts daily at 04:00

	-- Guild dungeon salary as a percentage of deducted dungeon gold
	nGuildDungeonSalaryPercent = 50,


	-- Guild war cooldown in seconds
	nGuildWarCD = 80000,

	-- Daily war declaration start in seconds; for example 13:00 = 3600*13
	nGuildDeclareBeginTime = 0,--64800,

	-- Daily war declaration end in seconds
	nGuildDeclareEndTime = 86400,--79200,

	-- Minimum guild level to join a guild war
	nGuildJoinWarLevelLimit = 1,--3,

	-- Funds required to declare war
	nGuildDeclareWarMoney = 500000,
	-- Return merit on guild war victory
	nGuildWarPlunderOfSalary = 250000,

	-- Wait after guild war declaration (1 minute)
	nGuildWarWaitingTime = 60,

	-- Maximum guild war duration (half an hour)
	nGuildWarLastedTimeLimit = 1800,

	-- Corresponds to the Scene event, where the unit is milliseconds
	nGuildWarEndWaitingTimeLimit = 30,

	-- Post-war teleport wait moved to the guild territory evtGuildWarEnd tree in main.lua
	-- Ask designer Ping Yi to update it; the unit there is milliseconds

	-- After a guild war, attackers cannot move or cast while the buff lasts and are teleported out when it expires
	nGuildWarAttackEndAuraID = 4501,

	-- After a guild war, defenders cannot move or cast while the buff lasts but are not teleported out on expiry
	nGuildWarDefendEndAuraID = 4509,


	-- Guild war victory spoils as a percentage of total resources
	nGuildWarPlunderPercent = 30,
	-- Additional guild war victory spoils percentage
	nGuildWarExtraPlunder = 50,
	-- Salary paid after guild war victory as a percentage of declaration funds
	nGuildWarSalaryPercent = 50,

	-- Guild dungeon refresh time: 04:00 expressed in seconds
	nGuildDungeonUpdateTime = 14400,

}
