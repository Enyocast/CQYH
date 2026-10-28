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
	-- 帮派创建需求物品类型ID
	nCanCreateGuildItemTypeID = 80002,
	-- 物品数量
    nCanCreateGuildItemNum = 1,
	-- 创建需求金钱
    nCanCreateGuildMoney = 200000,
	-- 创建需求人物等级
    nCanCreateGuildLevel = 17,
	-- 加入公会最低等级
	nCanJoinGuildLevel = 17,
	-- 初始帮派金钱
    nInitGuildMoney = 100000,
	-- 初始粮
	nWood = 100000,
	-- 初始木
	nHerb = 100000,
	-- 初始石
	nCrystal = 100000,
	-- 初始铁
	nSilver = 100000,

	-- 职位权限
	nInitGuildPositionRight =	-- 7 = GUILD_POSITION_COUNT
	{
		[0] = 0,		-- none
		[1] = 4095,		-- 帮主
		[2] = 4095,		-- 副帮主
		[3] = 495,		-- 长老
		[4] = 15,		-- 监事
		[5] = 3,		-- 执事
		[6] = 1,		-- 主簿
		[7] = 0,		-- 帮众
	},

	-- 仓库权限
    nInitGuildStorageRight =		-- 7 = GUILD_POSITION_COUNT
	{
		[0] = 4095,		-- 帮主
		[1] = 0,		-- 副帮主
		[2] = 0,		-- 长老
		[3] = 0,		-- 殿主
		[4] = 0,		-- 执事
		[5] = 0,		-- 主簿
		[6] = 0,		-- 帮众
	},

	-- 帮派解散等级限制
	nGuildDisbandLevelLimit = 3,

	-- 退出帮派cd时间，单位：秒
    dwReJoinGuildCD = 0,

	-- 帮派申请存在时间， 单位： 秒
	nGuildApplicationLastTime = 300,

	-- 从帮派仓库取物品每次消耗金钱，默认是金钱类型1（即绑定金钱）
	nGuildPopItemComsumeMoney = 0,


	-- 最多一次可领取的薪水上限
	nInitGuildMaxSalary = 10000,

	-- 一次领取薪水占功勋的百分比
	nGuildDrawSalaryPercent = 80,

	-- 功勋获得周上限
	nGuildObtainMoneyLimitPerWeek = 10000,

	-- 帮派发薪水的时间周期, (604800 为一周的秒数)
	--nDrawSalaryPeriod = 604800,
	nDrawSalaryPeriod = 3600,

	-- 每天捐赠金币上限
	nMaxDonateMoneyPerDay =
	{
		[0] = 1,
		[1] = 100000000,		-- 帮主
		[2] = 100000000,		-- 副
		[3] = 100000000,		-- 长老
		[4] = 100000000,
		[5] = 100000000,
		[6] = 100000000,
		[7] = 100000000,		-- 帮众
	},
	-- 每天捐赠资源上限
	nMaxDonateResPerDay =
	{
		[0] = 1,
		[1] = 100000000,		-- 帮主
		[2] = 100000000,		-- 副
		[3] = 100000000,		-- 长老
		[4] = 100000000,
		[5] = 100000000,
		[6] = 100000000,
		[7] = 100000000,		-- 帮众
	},



	-- 联盟 消耗金钱
	nAllianceConsumeMoney =
	{
		[0] = 100000,		-- 1天
		[1] = 200000,		-- 3天
		[2] = 500000,		-- 7天
		[3] = 1000000,		-- 30天
	},

	-- 敌对消耗金钱
	nEnemyConsumeMoney =
	{
		[0] = 100000,		-- 1天
		[1] = 200000,		-- 3天
		[2] = 500000,		-- 7天
		[3] = 1000000,		-- 30天
	},

	-- 帮派联盟或者敌对持续时间，单位：秒数
	nGuildDiplomatLastTime =
	{
		[0] = 86400,		-- 1天
		[1] = 259200,		-- 3天
		[2] = 604800,		-- 7
		[3] = 2592000,		-- 30
	},

	-- 联盟申请持续时间
	nDiplomatAppLastTime = 300,


	-- 取消建筑升级返回资源百分比
	nBuildingUpgradeRefundPercent = 50,
	-- 删除建筑返还资源百分比
	nDelBuildingRefundPercent = 33,
	-- 取消buffer升级返回资源百分比
    nWelfareBufferUpgradeRefundPercent = 50,
	-- 资源自动增长百分比
    nAddResourceInterval = 3600,

	--帮派属地TEMPLATE ID
	dwSceneTemplateID = 127,
	-- 进入帮派属地坐标，朝向
	nEnterMapPosX = 41355,
	nEnterMapPosY = 50258,
	nEnterMapPosZ = 7753,
	nEnterMapDirection = 1,

	-- 进入公会属地的坐标 SERVER_POINT
	dwServerPoint = 14,
	-- 公会战进入对方属地的坐标
	dwTargetGuildServerPoint = 3,

	-- 王城地图TEMPLATE ID
	dwPalaceSceneTemplateID = 101,


	--帮派建筑
	szBMainNameID 		= "main01",
	szBBusinessNameID	= "Shop01";		-- 商会
	szBDeityNameID		= "God01";		-- 神坛
	szBWonderNameID		= "Gtot01";

	-- 改变王城或者帮派属地天气的条件, {金币，持续时间/秒}
	arrWeatherCondition = {
		[0] = {nMoney = 9999999, nTime = 9999999}, -- invalid
		[1] = {nMoney = 50000, nTime = 300},		-- 50000 money, 300 s
		[2] = {nMoney = 100000, nTime = 600},	-- 100000, 600s
		[3] = {nMoney = 200000, nTime = 1800},	-- 200000, 1800s
	},

	-- 帮派维护开始时刻
	nRoutineConsumeTime = 4,		-- 每天4点开始

	-- 公会活动重置时间
	nGuildActivityResetHour = 4,

	nGuildActivityBeginHour1 = 0,
    nGuildActivityEndHour1 = 2,
    nGuildActivityBeginHour2 = 10,
    nGuildActivityEndHour2 = 24,


    ---------------------------- war ------------------------------------
	-- 公会战被打保护时间，秒，从当天公会战开始时算起
	nGuildWarProtectionTime = 106200,

	-- 公会宣战cd,单位：秒，从当天公会战开始时算起
	nGuildWarAttackCD = 106200,



	-- 每天公会战开始时间， 单位秒数， 比如每天下午1点=下午13点 = 3600*13,下午6点30开始
	nGuildWarReadyHour = 18,
	nGuildWarReadyMin = 20,

	nGuildWarBeginHour = 18,
	nGuildWarBeginMin = 30,

	nGuildWar10TipHour = 19,
	nGuildWar10TipMin = 20,

	nGuildWarEndHour = 19,
	nGuildWarEndMin = 30,


	-- 每天宣战结束时间， 单位秒数, 下面必须和上面对应
	nGuildWarBeginTime = 66600,
	nGuildWarEndTime = 70200,--70200,

	-- 家族战 指定公会战参战等级
	nGuildSpecifyWarLevelLimit = 5,--3,

	-- 帮派战结束后等待传送时间, 已经挪到帮派属地的evtGuildWarEnd的tree里面， main.lua配置里
	-- 请找策划妹子 平怡 更新。 那边的单位是毫秒

	-- 公会战结束，攻击方buffer, 无法移动，无法释放技能，buffer结束被传出地图
	nGuildWarAttackEndAuraID = 2500,

	-- 公会战结束，防守方buffer,无法移动， 无法释放技能，buffer结束不会被传出地图
	nGuildWarDefendEndAuraID = 2500,


	-- 公会战胜利， 战利品占总量的万分比
	nGuildWarMoneyPlunderPercent = 3000,
	nGuildWarResPlunderPercent = 3000,


	-- 公会战胜利，额外战利品万分比
	nGuildWarMoneyPlunder = 5000,
	nGuildWarResPlunder = 5000,

	---------------------------------------------------------------------

	--
	----------------------------- match war -----------------------------
	-- 匹配公会战最低等级限制
	nGuildMatchWarLevelLimit = 1,

	-- 匹配公会战每日次数限制
	nGuildMatchWarCountLimit = 5,

	-- 匹配战公会资金消耗
	nGuildMatchWarMoneyConsumption = 5000,

	-- 匹配公会战活动 开始时间
	nGuildMatchWarBeginTime = 0,

	-- 匹配公会战活动 结束时间
	nGuildMatchWarEndTime = 86400,


	nGuildWarAttackSuccMailID = 2018,
    nGuildWarAttackFailMailID = 2019,
    nGuildWarDefendSuccMailID = 2020,
    nGuildWarDefendFailMailID = 2021,

	---------------------------------------------------------------------


	-- 帮派副本薪水占副本扣除金币的百分比
	nGuildDungeonSalaryPercent = 50,
	-- 公会副本刷新时间, 凌晨4点的秒数
	nGuildDungeonUpdateTime = 14400,

	-- 公会成员提供的繁荣度
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
