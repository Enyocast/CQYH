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

	-- 帮派创建需求物品类型ID
	nCanCreateGuildItemTypeID = 80002,
	-- 物品数量
    nCanCreateGuildItemNum = 1,
	-- 创建需求金钱
    nCanCreateGuildMoney = 50000,
	-- 创建需求人物等级
    nCanCreateGuildLevel = 10,
	-- 初始帮派金钱
    nInitGuildMoney = 10000,
	-- 初始木材
	nWood = 10000,
	-- 初始药草
	nHerb = 10000,
	-- 初始水晶
	nCrystal = 10000,
	-- 初始秘银
	nSilver = 10000,

	-- 职位权限
	nInitGuildPositionRight =	-- 7 = GUILD_POSITION_COUNT
	{
		[0] = 0,		-- none
		[1] = 4095,		-- 帮主
		[2] = 2047,		-- 副帮主
		[3] = 255,		-- 长老
		[4] = 15,		-- 殿主
		[5] = 7,		-- 执事
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
    dwReJoinGuildCD = 7200,

	-- 帮派申请存在时间， 单位： 秒
	nGuildApplicationLastTime = 300,

	-- 从帮派仓库取物品每次消耗金钱，默认是金钱类型1（即绑定金钱）
	nGuildPopItemComsumeMoney = 100,




	-- 最多一次可领取的薪水上限
	nInitGuildMaxSalary = 10000,

	-- 一次领取薪水占功勋的百分比
	nGuildDrawSalaryPercent = 80,

	-- 功勋获得周上限
	nGuildObtainMoneyLimitPerWeek = 10000,

	-- 帮派发薪水的时间周期, (604800 为一周的秒数)
	--nDrawSalaryPeriod = 604800,
	nDrawSalaryPeriod = 3600,

	-- 每天获得帮派贡献上限
	nEarnMaxContributionPerDay = 10000,
	-- 每周获得帮派贡献上限
	nEarnMaxContributionPerWeek = 100000,



	-- 联盟 消耗金钱
	nAllianceConsumeMoney =
	{
		[0] = 100,		-- 1天
		[1] = 500,		-- 3天
		[2] = 2000,		-- 7天
		[3] = 10000,	-- 30天
	},

	-- 敌对消耗金钱
	nEnemyConsumeMoney =
	{
		[0] = 1000,		-- 1天
		[1] = 5000,		-- 3天
		[2] = 20000,	-- 7天
		[3] = 100000,	-- 30天
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
	-- 取消buffer升级返回资源百分比
    nWelfareBufferUpgradeRefundPercent = 50,
	-- 资源自动增长百分比
    nAddResourceInterval = 3600,

	--帮派属地TEMPLATE ID
	dwSceneTemplateID = 127,
	-- 进入帮派属地坐标，朝向
	nEnterMapPosX = 51283,
	nEnterMapPosY = 17682,
	nEnterMapPosZ = 16288,
	nEnterMapDirection = 1,

	-- 进入公会属地的坐标 SERVER_POINT
	dwServerPoint = 14,
	-- 公会战进入对方属地的坐标
	dwTargetGuildServerPoint = 15,

	-- 王城地图TEMPLATE ID
	dwPalaceSceneTemplateID = 101,


	--帮派建筑
	arrBuildingData = {
		[0] = {nSvrUniqueID = 1, nLevel = 1},	-- none
		[1] = {nSvrUniqueID = 28, nLevel = 1},	-- 主殿
		[2] = {nSvrUniqueID = 8, nLevel = 1},	-- 演武堂
		[3] = {nSvrUniqueID = 14, nLevel = 1},	-- 商会
		--[3] = {nSvrUniqueID = 7, nLevel = 1},	-- 战事堂
		[4] = {nSvrUniqueID = 33, nLevel = 1},	-- 聚贤馆
		[5] = {nSvrUniqueID = 15, nLevel = 1},	-- 金库
		[6] = {nSvrUniqueID = 39, nLevel = 1},	-- 军机处
		[7] = {nSvrUniqueID = 12, nLevel = 1},	-- 图腾
		[8] = {nSvrUniqueID = 23, nLevel = 1},	-- 农场
		[9] = {nSvrUniqueID = 20, nLevel = 1},	-- 林场
		[10] = {nSvrUniqueID = 16, nLevel = 1},	-- 石场
		[11] = {nSvrUniqueID = 18, nLevel = 1},	-- 矿场
		[12] = {nSvrUniqueID = 22, nLevel = 1},	-- 粮仓
		[13] = {nSvrUniqueID = 21, nLevel = 1},	-- 木仓
		[14] = {nSvrUniqueID = 17, nLevel = 1},	-- 石仓
		[15] = {nSvrUniqueID = 19, nLevel = 1},	-- 矿仓
	},

	-- 改变王城或者帮派属地天气的条件, {金币，持续时间/秒}
	arrWeatherCondition = {
		[0] = {nMoney = 9999999, nTime = 9999999}, -- invalid
		[1] = {nMoney = 50000, nTime = 300},		-- 50000 money, 300 s
		[2] = {nMoney = 100000, nTime = 600},	-- 100000, 600s
		[3] = {nMoney = 200000, nTime = 1800},	-- 200000, 1800s
	},

	-- 帮派维护开始时刻
	nRoutineConsumeTime = 4,		-- 每天4点开始

	-- 帮派副本薪水占副本扣除金币的百分比
	nGuildDungeonSalaryPercent = 50,


	-- 公会战cd,单位：秒
	nGuildWarCD = 80000,

	-- 每天宣战开始时间， 单位秒数， 比如每天下午1点=下午13点 = 3600*13
	nGuildDeclareBeginTime = 0,--64800,

	-- 每天宣战结束时间， 单位秒数
	nGuildDeclareEndTime = 86400,--79200,

	-- 家族战 可加入的最低公会等级
	nGuildJoinWarLevelLimit = 1,--3,

	-- 宣战需要资金
	nGuildDeclareWarMoney = 500000,
	-- 公会战胜利,返还功勋
	nGuildWarPlunderOfSalary = 250000,

	-- 帮派战宣战后等待时间（1分钟）
	nGuildWarWaitingTime = 60,

	-- 帮派战最长持续时间（半小时）
	nGuildWarLastedTimeLimit = 1800,

	-- 和Scene的evt里面对应的， 那边是毫秒
	nGuildWarEndWaitingTimeLimit = 30,

	-- 帮派战结束后等待传送时间, 已经挪到帮派属地的evtGuildWarEnd的tree里面， main.lua配置里
	-- 请找策划妹子 平怡 更新。 那边的单位是毫秒

	-- 公会战结束，攻击方buffer, 无法移动，无法释放技能，buffer结束被传出地图
	nGuildWarAttackEndAuraID = 4501,

	-- 公会战结束，防守方buffer,无法移动， 无法释放技能，buffer结束不会被传出地图
	nGuildWarDefendEndAuraID = 4509,


	-- 公会战胜利， 战利品占总量的百分比
	nGuildWarPlunderPercent = 30,
	-- 公会战胜利，额外战利品百分比
	nGuildWarExtraPlunder = 50,
	-- 公会战胜利后，下发薪水占宣战资金百分比
	nGuildWarSalaryPercent = 50,

	-- 公会副本刷新时间, 凌晨4点的秒数
	nGuildDungeonUpdateTime = 14400,

}
