GameWorldConfig = {
    szConfigPath = "commonconfig",

	--- 所有距离单位是厘米
	--- 所有时间单位是毫秒，最小精度62.5毫秒
	--- 所有角度单位是度
	--- 所有速度单位是毫秒
	--- 所有几率都是万分率

	--- 强制同步距离
    nForceSyncDistance = 512,
	--- NPC交互距离
    nNpcInteractDistance = 2048,
	--- 紧急任务NPC交互距离
	nEmergencyNpcInteractDistance = 1024,
	--- Doodad交互距离
    nDoodadOperateDistance = 512,
	--- 队伍拾取权的有效距离
    nLootDistance = 9600,
	--- 比较成就距离
    nCompareAchievementDistance = 2000,

	--- 经验、魂值分享距离
    nExpShareDistance = 2000,

	--- 等级上限
	nLevelLimit = 40,

	--- 组队拍卖出价时间
	nTeamAuctionTimeout = 120000,
	--- 组队拍卖系统抽水比例(万分比的分子)
	nTeamAuctionTax = 500;

	--- 查询附近无队伍玩家和不满员队伍的最小间隔
    nAdjacentDataTimeLimit = 4 * 1000,
	--- 无加载跳转最大距离
	nInstantJumpRange = 800000,
	--- 最大场景加载等待时间
    nSceneLoadTimeOut = 600 * 1000,
	---每秒存储玩家数据数量
    nSaveRoleCountPerSecond = 16,
	--- 最小存储玩家数据间隔
    nSaveRoleMinTime = 60 * 1000,
	--- 每10秒放入的排队玩家数量
	nLoginRoleCountPer10Second = 50,
	--- 进入场景自动获取的BUFF ID
    nEnterSceneBuffID = 2230,
	--- 副本结束获取的BUFF ID
    nSceneFinishBuffID = 1042,
	--- 拾取物品最小间隔时间
	nLootTimeLimit = 250,
	--- PK保护等级（含）
    nPkProtectLevel = 7,
	--- 获得PK值的几率
    nGainPkValueChance = 7500,
	--- 获得的PK值数量
    nGainPkValue = 50,
	--- 黄名的最小PK值
    nYellowNamePkValueLimit = 100,
	--- 红名的最小PK值
    nRedNamePkValueLimit = 300,
	--- 灰名的持续时间
	nGreyNameDuration = 60 * 1000,
	--- 触发动态复活的NPC数量比例
	nDynamicRespawnPercent = 5000,
	--- 复活时间调整系数
	nRespawnTimeRate = 10000,
	--- 每日签到天数
	nCheckInValidDays = 30,

	--- 背包格子扩充价格
	nBagSlotCost =
	{
		[0]=2000,
		[1]=3000,
		[2]=4000,
		[3]=5000,
		[4]=6000,
		[5]=7000,
		[6]=8000,
		[7]=9000,
		[8]=10000,
		[9]=11000,
		[10]=12000,
		[11]=13000,
		[12]=14000,
		[13]=15000,
		[14]=16000,
		[15]=17000,
		[16]=20000,
		[17]=30000,
		[18]=40000,
		[19]=50000,
		[20]=60000,
		[21]=70000,
		[22]=80000,
		[23]=90000,
		[24]=100000,
		[25]=110000,
		[26]=120000,
		[27]=130000,
		[28]=140000,
		[29]=150000,
		[30]=160000,
		[31]=170000,
	},
	--- 银行格子扩充价格
	nBankSlotCost =
	{
		[0]=2000,
		[1]=3000,
		[2]=4000,
		[3]=5000,
		[4]=6000,
		[5]=7000,
		[6]=8000,
		[7]=9000,
		[8]=10000,
		[9]=11000,
		[10]=12000,
		[11]=13000,
		[12]=14000,
		[13]=15000,
		[14]=16000,
		[15]=17000,
		[16]=18000,
		[17]=19000,
		[18]=20000,
		[19]=21000,
		[20]=22000,
		[21]=23000,
		[22]=24000,
		[23]=25000,
		[24]=30000,
		[25]=40000,
		[26]=50000,
		[27]=60000,
		[28]=70000,
		[29]=80000,
		[30]=90000,
		[31]=100000,
		[32]=110000,
		[33]=120000,
		[34]=130000,
		[35]=140000,
		[36]=150000,
		[37]=160000,
		[38]=170000,
		[39]=180000,
		[40]=190000,
		[41]=200000,
		[42]=210000,
		[43]=220000,
		[44]=230000,
		[45]=240000,
		[46]=250000,
		[47]=260000,
		[48]=270000,
		[49]=280000,
		[50]=290000,
		[51]=300000,
		[52]=310000,
		[53]=320000,
		[54]=330000,
		[55]=340000,
	},
	--- 资源包裹扩充价格
	nResourceSlotCost =
	{
		[0]=10000,
		[1]=10000,
		[2]=10000,
		[3]=10000,
		[4]=10000,
		[5]=10000,
		[6]=10000,
		[7]=10000,
		[8]=10000,
		[9]=10000,
		[10]=10000,
		[11]=10000,
		[12]=10000,
		[13]=10000,
		[14]=10000,
		[15]=10000,
		[16]=10000,
		[17]=10000,
		[18]=10000,
		[19]=10000,
		[20]=10000,
		[21]=10000,
		[22]=10000,
		[23]=10000,
		[24]=10000,
		[25]=10000,
		[26]=10000,
		[27]=10000,
		[28]=10000,
		[29]=10000,
		[30]=10000,
		[31]=10000,
		[32]=10000,
		[33]=10000,
		[34]=10000,
		[35]=10000,
		[36]=10000,
		[37]=10000,
		[38]=10000,
		[39]=10000,
		[40]=20000,
		[41]=20000,
		[42]=20000,
		[43]=20000,
		[44]=20000,
		[45]=20000,
		[46]=20000,
		[47]=20000,
		[48]=20000,
		[49]=20000,
		[50]=20000,
		[51]=20000,
		[52]=20000,
		[53]=20000,
		[54]=20000,
		[55]=20000,
		[56]=20000,
		[57]=20000,
		[58]=20000,
		[59]=20000,
		[60]=20000,
		[61]=20000,
		[62]=20000,
		[63]=20000,
		[64]=20000,
		[65]=20000,
		[66]=20000,
		[67]=20000,
		[68]=20000,
		[69]=20000,
		[70]=20000,
		[71]=20000,
		[72]=20000,
		[73]=20000,
		[74]=20000,
		[75]=20000,
		[76]=20000,
		[77]=20000,
		[78]=20000,
		[79]=20000,
		[80]=20000,
		[81]=20000,
		[82]=20000,
		[83]=20000,
		[84]=20000,
		[85]=20000,
		[86]=20000,
		[87]=20000,
		[88]=20000,
		[89]=20000,
		[90]=20000,
		[91]=20000,
		[92]=20000,
		[93]=20000,
		[94]=20000,
		[95]=20000,
		[96]=20000,
		[97]=20000,
		[98]=20000,
		[99]=20000,
		[100]=20000,
		[101]=20000,
		[102]=20000,
		[103]=20000,
		[104]=20000,
		[105]=20000,
		[106]=20000,
		[107]=20000,
		[108]=20000,
		[109]=20000,
		[110]=20000,
		[111]=20000,
		[112]=30000,
		[113]=30000,
		[114]=30000,
		[115]=30000,
		[116]=30000,
		[117]=30000,
		[118]=30000,
		[119]=30000,
		[120]=30000,
		[121]=30000,
		[122]=30000,
		[123]=30000,
		[124]=30000,
		[125]=30000,
		[126]=30000,
		[127]=30000,
		[128]=30000,
		[129]=30000,
		[130]=30000,
		[131]=30000,
		[132]=30000,
		[133]=30000,
		[134]=30000,
		[135]=30000,
		[136]=30000,
		[137]=30000,
		[138]=30000,
		[139]=30000,
		[140]=30000,
		[141]=30000,
		[142]=30000,
		[143]=30000,
		[144]=30000,
		[145]=30000,
		[146]=30000,
		[147]=30000,
		[148]=30000,
		[149]=30000,
		[150]=30000,
		[151]=30000,
		[152]=30000,
		[153]=30000,
		[154]=30000,
		[155]=30000,
		[156]=30000,
		[157]=30000,
		[158]=30000,
		[159]=30000,
		[160]=30000,
		[161]=30000,
		[162]=30000,
		[163]=30000,
		[164]=30000,
		[165]=30000,
		[166]=30000,
		[167]=30000,
		[168]=30000,
		[169]=30000,
		[170]=30000,
		[171]=30000,
		[172]=30000,
		[173]=30000,
		[174]=30000,
		[175]=30000,
		[176]=30000,
		[177]=30000,
		[178]=30000,
		[179]=30000,
		[180]=30000,
		[181]=30000,
		[182]=30000,
		[183]=30000,
	},

	nWeaponOverWeightAuraID = 2505,
	nArmorOverWeightAuraID = 2506,
	nBagOverWeightAuraID = 2507,
	nGMAuraID = 2516,

	--发送邮件间隔(秒)
	dwSendMailTimeInterval = 10,

	--发送邮件花费
	nSendMailCost = 1000,

	--- 被玩家杀死后，普通道具掉落几率
    nBagNormalItemDropRateByPlayer =
    {
	    [0] = 3000,
	    [1] = 3000,
	    [2] = 10000
    },
	--- 被玩家杀死后，贵重道具掉落几率
    nBagExpensiveItemDropRateByPlayer =
    {
	    [0] = 500,
	    [1] = 1500,
	    [2] = 3000
    },
	--- 被非玩家杀死后，普通道具掉落几率
    nBagNormalItemDropRateByNonPlayer =
    {
	    [0] = 1000,
	    [1] = 2000,
	    [2] = 4000
    },
	--- 被非玩家杀死后，贵重道具掉落几率
    nBagExpensiveItemDropRateByNonPlayer =
    {
	    [0] = 500,
	    [1] = 1500,
	    [2] = 3000
    },
	--- 强化特效1对应的强化等级
    shRefineFxLevel1 = 10,
	--- 强化特效2对应的强化等级
    shRefineFxLevel2 = 20,
	--- 摆摊交互距离
    nStallDistance = 384,
	--- 摆摊税率，万分比
	nStallTax =
	{
		[0] = 500,
		[1] = 1000,
		[2] = 2000
	},

	--首饰幸运修正概率，[0]代表碎裂概率，[1]代表+1概率，[2]代表+2概率，[3]代表+3概率
	--幸运值=∑首饰战斗力*LuckModifier/10000,LuckModifier在装备表中配置
	nEquipLevelupLuckModifier =
	{
		[0] = {nModifier = {[0] = 0, [1] = 5000, [2] = 0, [3] = 0}},						--幸运值区间0~0.99
		[1] = {nModifier = {[0] = 0, [1] = 10000, [2] = 0, [3] = 0}},						--幸运值区间1~1.99
		[2] = {nModifier = {[0] = 0, [1] = 0, [2] = 10000, [3] = 0}},						--幸运值区间2~2.99
		[3] = {nModifier = {[0] = 0, [1] = 0, [2] = 0, [3] = 10000}},						--幸运值区间3~3.99
		[4] = {nModifier = {[0] = 0, [1] = 5000, [2] = 5000, [3] = 0}},						--幸运值区间4~4.99
		[5] = {nModifier = {[0] = 0, [1] = 0, [2] = 5000, [3] = 5000}},						--幸运值区间5~5.99
		[6] = {nModifier = {[0] = 10000, [1] = 0, [2] = 0, [3] = 0}},						--幸运值区间6+
	},
	--黑铁纯度修正概率，[0]代表-2概率，[1]代表-1概率，[2]代表不变概率，[3]代表+1概率
	nEquipLevelupPurityModifier =
	{
		[0] = {nModifier = {[0] = 0, [1] = 0, [2] = 0, [3] = 0}},					  		--纯度区间0~9
		[1] = {nModifier = {[0] = 10000, [1] = 0, [2] = 0, [3] = 0}},					  	--纯度区间10~19
		[2] = {nModifier = {[0] = 0, [1] = 10000, [2] = 0, [3] = 0}},					  	--纯度区间20~29
		[3] = {nModifier = {[0] = 0, [1] = 0, [2] = 10000, [3] = 0}},					  	--纯度区间30~39
		[4] = {nModifier = {[0] = 0, [1] = 0, [2] = 0, [3] = 10000}},					  	--纯度区间40~49
		[5] = {nModifier = {[0] = 2000, [1] = 2000, [2] = 2000, [3] = 2000}},				--纯度区间50+
	},

	--武器升级立即取回花费金币
	nEquipLevelupImmediateCost = 100000,

	--- 仇恨消退时间（副本中永不消退）
    nThreatFadeTime = 30000,
    nRageRecoveryParam = 150;
    nFearDist = 1000;

    nAbilityPtsToPerProgressPts = 1,
    nBaseSecondsConvertingPerAbilityPts = 1800,

    nKnockBackDistance = 250;
    nKnockBackSpeed = 2000;

	-- 对npc的伤害系数修正 x = x * nDmgToNpcParam1 / nDmgToNpcParam2
	nDmgToNpcParam1 = 6;
	nDmgToNpcParam2 = 5;


	-- HP/MP自然回复系数
	nHpRecoveryParam = 75;
	nMpRecoveryParam = 18;

	nHpTapWalk = -10;
	nMpTapWalk = 0;
	nHpTapRun = -60;
	nMpTapRun = -10;
	nHpTapPhyAtk = -30;
	nMpTapPhyAtk = -100;
	nHpTapMagAtk = 0;
	nMpTapMagAtk = -450;
	nHpTapDig = -30;
	nMpTapDig = -50;

	-- HP/MP药物回复系数
	nDrugCureParam1 = 10;
	nDrugCureParam2 = 5;

	nDrugCureTapRunning = -1;
	nDrugCureTapMining = -2;
	nDrugCureTapMin = 1;

	-- HP/MP技能回复系数
	nHpSpellCureMax = 300;
	nHpSpellCure = 5;

	-- 硬直参数
    nStiffParamA = 500;
    nStiffParamB = -8000;
    nStiffIntervalB = 16; -- in frame

    nControlParamA = 80;
    nControlParamB = -2000;
    nControlIntervalB = 16;

	nHardParamA = 813;
	nHardParamB = 400;
	nHardParamC = 13;
	nHardParamD = 60;

    nGlobalSubstituteAuraID = 1001;

    nHeroExpGainRate = 10000;
    nHeroExpSubRate = 500;

    nAIIDWhenSeduced = 9993;

	nLastHurtResetTime = 7000;

	--- 杀死各种品质的NPC所获得的声望值和最大声望值
    AddReputation =
    {
	    [1] = {		-- nqNormal1
		    nReputation = 1,
		    nMaxReputation = 100000,
	    },
	    [2] = {		--nqNormal2
		    nReputation = 1,
		    nMaxReputation = 100000,
	    },
	    [3] = {		--nqNormal3
		    nReputation = 1,
		    nMaxReputation = 100000,
	    },
	    [4] = {		--nqNormal4
		    nReputation = 1,
		    nMaxReputation = 100000,
	    },
	    [5] = {		--nqNormal5
		    nReputation = 1,
		    nMaxReputation = 100000,
	    },
	    [6] = {		--nqElite
		    nReputation = 10,
		    nMaxReputation = 100000,
	    },
	    [7] = {		--nqRare
		    nReputation = 20,
		    nMaxReputation = 100000,
	    },
	    [8] = {		--nqBoss
		    nReputation = 100,
		    nMaxReputation = 100000,
	    },
    },

	--- 杀死各种品质的NPC所损失的声望值
    SubReputation =
    {
	    [1] = -1,		--nqNormal1
	    [2] = -1,		--nqNormal2
	    [3] = -2,		--nqNormal3
	    [4] = -2,		--nqNormal4
	    [5] = -2,		--nqNormal5
	    [6] = -3,		--nqElite
	    [7] = -4,		--nqRare
	    [8] = -5,		--nqBoss
    },

    HeroAiId =
    {
	    [0] = {
		    AiId = {
			    [0] = 12,		--follow
			    [1] = 13,		--active
			    [2] = 14,		--passive
			    [3] = 1,		--standstill
		    },
	    },
	    [1] = {
		    AiId = {
			    [0] = 15,		--follow
			    [1] = 16,		--active
			    [2] = 17,		--passive
			    [3] = 1,		--standstill
		    },
	    },
	    [2] = {
		    AiId = {
			    [0] = 18,		--follow
			    [1] = 19,		--active
			    [2] = 20,		--passive
			    [3] = 1,		--standstill
		    },
	    },
	    [3] = {
		    AiId = {
			    [0] = 21,		--follow
			    [1] = 22,		--active
			    [2] = 23,		--passive
			    [3] = 1,		--standstill
		    },
	    },
    },

    HeroDefaultName =
    {
	    [0] = {
		    Sex =
		    {
			    [1] = { szName = '男战士' },
			    [2] = { szName = '女战士' },
		    },
	    },
	    [1] = {
		    Sex =
		    {
			    [1] = { szName = '男法师' },
			    [2] = { szName = '女法师' },
		    },
	    },
	    [2] = {
		    Sex =
		    {
			    [1] = { szName = '男刺客' },
			    [2] = { szName = '女刺客' },
		    },
	    },
	    [3] = {
		    Sex =
		    {
			    [1] = { szName = '男弓箭手' },
			    [2] = { szName = '女弓箭手' },
		    },
	    },

    },

    BaseWeaponSpeed =
    {
	    [0] = 10000,    -- Unarmed
	    [1] = 10000,    -- One-Hand Sword
	    [2] = 9000,     -- One-Hand Hammer
	    [3] = 10000,    -- Two-Hand Sword
	    [4] = 10000,    -- Great Axe
	    [5] = 8000,     -- Twin Sword
	    [6] = 12000,    -- Spear
	    [7] = 15000,    -- Glove
	    [8] = 10000,    -- Dagger
	    [9] = 12000,    -- Chain Blade
	    [10] = 10000,   -- Twin CrossBow
	    [11] = 20000,   -- CrossBow
	    [12] = 15000,   -- Bow
	    [13] = 8000,    -- Knife
	    [14] = 10000,   -- Staff
	    [15] = 10000,   -- Great Shield
	    [16] = 10000,   -- Small Shield
	    [17] = 10000,   -- Magic
    },

    BaseWeaponStiffFactor =
    {
	    [0] = 10000,    -- Unarmed
	    [1] = 10000,    -- One-Hand Sword
	    [2] = 9000,     -- One-Hand Hammer
	    [3] = 10000,    -- Two-Hand Sword
	    [4] = 10000,    -- Great Axe
	    [5] = 8000,     -- Twin Sword
	    [6] = 12000,    -- Spear
	    [7] = 15000,    -- Glove
	    [8] = 10000,    -- Dagger
	    [9] = 15000,    -- Chain Blade
	    [10] = 10000,   -- Twin CrossBow
	    [11] = 20000,   -- CrossBow
	    [12] = 15000,   -- Bow
	    [13] = 8000,    -- Knife
	    [14] = 10000,   -- Staff
	    [15] = 10000,   -- Great Shield
	    [16] = 10000,   -- Small Shield
	    [17] = 10000,   -- Magic
    },

    DodgeConst = 12000;

    CritConst =
    {
	    [1] = 12000,	-- phy attack
	    [2] = 12000,	-- mag attack
    },

    DefConst =
    {
	    [1] = 12000,	-- phy def
	    [2] = 12000,	-- mag def
    },

    ReviveParam =
    {
	    [1] = {		-- crtAtCurrentPos
		    nRequireItemID = 100001;
		    nRequireItemCount = 1,
--		    nRequireItemMaxCount = 20000,
--		    nDelayTime = 0,
		    nHpPercent = 10000,
	    },

	    [2] = {		-- crtInstant
		    nRequireItemID = MONEYTYPE_02,
		    nRequireItemCount = 100,
--		    nRequireItemMaxCount = 1,
--		    nDelayTime = 10000,
		    nHpPercent = 10000,
	    },

	    [3] = {		-- crtFree
		    nRequireItemID = 0,
		    nRequireItemCount = 0,
--		    nRequireItemMaxCount = 0,
--		    nDelayTime = 0,
		    nHpPercent = 3000,
	    },
    },

	-- 强制复活时间
    nReviveTimeout = 5 * 60 * 1000;

    -------复活延时时间 Min(nFreeReviveParam1, nFreeReviveParam2 x nKilledByPlayer)

	nReviveTimesResetTime = 180000;
	nFreeReviveParam1 = 0;
	nFreeReviveParam2 = 0;

    NormalPracticeParam =
    {
	    [1] = {
		    nSeconds = 1800,
		    nConvertedAbilityPts = 1,
	    },
	    [2] = {
		    nSeconds = 10800,
		    nConvertedAbilityPts = 6,
	    },
	    [3] = {
		    nSeconds = 86400,
		    nConvertedAbilityPts = 48,
	    },
    },

    nFastPracticeRate = 360,

    FastPracticeMoneyCost =
    {
	    [1] = 5,		--MONEYTYPE_01
	    [2] = 1,		--MONEYTYPE_02
    },

    FastPracticeSpeedupCost =
    {
	    [1] = {
		    nMoneyType = 1,
		    nMoneyCount = 100,
		    nRate = 3,
	    },
	    [2] = {
		    nMoneyType = 2,
		    nMoneyCount = 200,
		    nRate = 5,
	    },
	    [3] = {
		    nMoneyType = 2,
		    nMoneyCount = 300,
		    nRate = 10,
	    },
    },

	-- 数组下标代表了已经跑的帧数
	MagHitRateToRunningTarget =
	{
		[0] = 7500,
		[1] = 7500,
		[2] = 7500,
		[3] = 5000,
		[4] = 5000,
		[5] = 2500,
		[6] = 2500,
		[7] = 2500,
		[8] = 0,
		[9] = 0,
		[10] = 1000,
		[11] = 2500,
		[12] = 2500,
	},
	--因为是额外命中率,所以属于Bonus判定,兼顾猫步特性,降低命中
	PhyHitRateToWalkingTarget =
	{
		[0] = 2500,
		[1] = 2000,
		[2] = 1500,
		[3] = 1500,
		[4] = 1000,
		[5] = 0,
		[6] = 0,
		[7] = 0,
		[8] = 0,
		[9] = 0,
		[10] = 0,
		[11] = 0,
		[12] = 0,
	},
	--因为是额外命中率,所以属于Bonus判定
	PhyHitRateToRunningTarget =
	{
		[0] = 7500,
		[1] = 5000,
		[2] = 4000,
		[3] = 3000,
		[4] = 1500,
		[5] = 1000,
		[6] = 1000,
		[7] = 0,
		[8] = 0,
		[9] = 0,
		[10] = 0,
		[11] = 0,
		[12] = 0,
	},

	--- 异常返回点
    nErrorReturnSceneTempID = 145 ,
	ErrorReturnPos = {x=31200, y=55200, z=5000},

	--- 红名村
    nRedNameSceneTempID = 147,
	RedNameReturnPos = {x=16350, y=36587, z=6456},

	--- 默认复活点
    nDefaultReviveSceneTempID = 142 ,
	DefaultRevivePos = {x=25990, y=56905, z=4750},

    TeamDefaultName = '的队伍',

	--- VIP待遇配置
    VIPData = {
        [vlLevel0] = { --- 非VIP
            nDecreasePkValuePer5Min = 1,		--- 每5分钟消退的仇恨值
            nRewardQuestCount = 0,				--- 悬赏任务数量
            nDailyFatigue = 100,				--- 每天获得的活力值
            nDailyUseMoneyType01Percent = 0,	--- 每天绑金使用上限加成
        },
        [vlLevel1] = {
            nDecreasePkValuePer5Min = 2,
            nRewardQuestCount = 1,
            nDailyFatigue = 110,
            nDailyUseMoneyType01Percent = 3000,
        },
        [vlLevel2] = {
            nDecreasePkValuePer5Min = 3,
            nRewardQuestCount = 2,
            nDailyFatigue = 120,
            nDailyUseMoneyType01Percent = 6000,
        },
        [vlLevel3] = {
            nDecreasePkValuePer5Min = 5,
            nRewardQuestCount = 4,
            nDailyFatigue = 150,
            nDailyUseMoneyType01Percent = 10000,
        },
    },

	--- 组队经验根据人数的单人缩减系数
    nTeamExpRate =
    {
        [1] = 10000,
        [2] = 12000,
        [3] = 13000,
        [4] = 14000,
        [5] = 15000,
        [6] = 16000,
        [7] = 17000,
        [8] = 18000,
        [9] = 19000,
        [10] = 20000,
        [11] = 21000,
        [12] = 22000,
        [13] = 23000,
        [14] = 24000,
        [15] = 25000,
        [16] = 26000,
        [17] = 27000,
        [18] = 28000,
        [19] = 29000,
        [20] = 30000,
    },
	--- 等级差的经验加成比例
    nLevelExpRate =
    {
        [0] = 5000,  --- NpcLevel - RoleLevel = -15
        [1] = 6000,  --- NpcLevel - RoleLevel = -14
        [2] = 7000,  --- NpcLevel - RoleLevel = -13
        [3] = 8000,  --- NpcLevel - RoleLevel = -12
        [4] = 9000,  --- NpcLevel - RoleLevel = -11
        [5] = 10000,  --- NpcLevel - RoleLevel = -10
        [6] = 10000,  --- NpcLevel - RoleLevel = -9
        [7] = 10000,  --- NpcLevel - RoleLevel = -8
        [8] = 10000,  --- NpcLevel - RoleLevel = -7
        [9] = 10000,  --- NpcLevel - RoleLevel = -6
        [10] = 10000,  --- NpcLevel - RoleLevel = -5
        [11] = 10000,  --- NpcLevel - RoleLevel = -4
        [12] = 10000,  --- NpcLevel - RoleLevel = -3
        [13] = 10000,  --- NpcLevel - RoleLevel = -2
        [14] = 10000,  --- NpcLevel - RoleLevel = -1
        [15] = 10000,  --- NpcLevel - RoleLevel = 0
        [16] = 10000,  --- NpcLevel - RoleLevel = 1
        [17] = 10000,  --- NpcLevel - RoleLevel = 2
        [18] = 10000,  --- NpcLevel - RoleLevel = 3
        [19] = 10000,  --- NpcLevel - RoleLevel = 4
        [20] = 10000,  --- NpcLevel - RoleLevel = 5
        [21] = 10000,  --- NpcLevel - RoleLevel = 6
        [22] = 10000,  --- NpcLevel - RoleLevel = 7
        [23] = 10000,  --- NpcLevel - RoleLevel = 8
        [24] = 10000,  --- NpcLevel - RoleLevel = 9
        [25] = 10000,  --- NpcLevel - RoleLevel = 10
        [26] = 10000,  --- NpcLevel - RoleLevel = 11
        [27] = 10000,  --- NpcLevel - RoleLevel = 12
        [28] = 10000,  --- NpcLevel - RoleLevel = 13
        [29] = 10000,  --- NpcLevel - RoleLevel = 14
        [30] = 10000,  --- NpcLevel - RoleLevel = 15
    },

	--- 师徒经验加成比例
	nTeacherExpRate = 1500,
	nStudentExpRate = 5000,

	--- 额外经验加成比例
    nExtraExpRate = 1000000,
	--- 全局经验加成比例
    nGlobalExpRate = 1000000,
	--- 经验惩罚比例
	nPunishExpRate = 5000,
	--- 经验惩罚时长（秒）
	nPunishExpDuration = 6000 * 60,

	--- 等级差额外双倍经验值加成系数
	nLevelDiffExtraExpRate =
	{
		[0] = 10000,		[1] = 10000,		[2] = 10000,		[3] = 10000,		[4] = 10000,
		[5] = 15000,		[6] = 15000,		[7] = 15000,		[8] = 15000,		[9] = 15000,
		[10] = 20000,		[11] = 20000,		[12] = 20000,		[13] = 20000,		[14] = 20000,
		[15] = 20000,		[16] = 20000,		[17] = 20000,		[18] = 20000,		[19] = 20000,
		[20] = 20000,		[21] = 20000,		[22] = 20000,		[23] = 20000,		[24] = 20000,
		[25] = 20000,		[26] = 20000,		[27] = 20000,		[28] = 20000,		[29] = 20000,
		[30] = 20000,		[31] = 20000,		[32] = 20000,		[33] = 20000,		[34] = 20000,
		[35] = 20000,		[36] = 20000,		[37] = 20000,		[38] = 20000,		[39] = 20000,
		[40] = 20000,		[41] = 20000,		[42] = 20000,		[43] = 20000,		[44] = 20000,
		[45] = 20000,		[46] = 20000,		[47] = 20000,		[48] = 20000,		[49] = 20000,
		[50] = 20000,		[51] = 20000,		[52] = 20000,		[53] = 20000,		[54] = 20000,
		[55] = 20000,		[56] = 20000,		[57] = 20000,		[58] = 20000,		[59] = 20000,
		[60] = 20000,		[61] = 20000,		[62] = 20000,		[63] = 20000,		[64] = 20000,
		[65] = 20000,		[66] = 20000,		[67] = 20000,		[68] = 20000,		[69] = 20000,
		[70] = 20000,		[71] = 20000,		[72] = 20000,		[73] = 20000,		[74] = 20000,
		[75] = 20000,		[76] = 20000,		[77] = 20000,		[78] = 20000,		[79] = 20000,
		[80] = 20000,		[81] = 20000,		[82] = 20000,		[83] = 20000,		[84] = 20000,
		[85] = 20000,		[86] = 20000,		[87] = 20000,		[88] = 20000,		[89] = 20000,
		[90] = 20000,		[91] = 20000,		[92] = 20000,		[93] = 20000,		[94] = 20000,
		[95] = 20000,		[96] = 20000,		[97] = 20000,		[98] = 20000,		[99] = 20000
	},


	--- 打低等级NPC的物品掉落调整比例
    nDropChanceRate =
    {
        [0] = 10000,
        [1] = 10000,
        [2] = 10000,
        [3] = 10000,
        [4] = 10000,
        [5] = 10000,
        [6] = 9500,
        [7] = 9000,
        [8] = 8500,
        [9] = 8000,
        [10] = 7500,
        [11] = 7000,
        [12] = 6500,
        [13] = 6000,
        [14] = 5500,
        [15] = 5000,
        [16] = 4500,
        [17] = 4000,
        [18] = 4000,
        [19] = 4000,
        [20] = 4000,
        [21] = 4000,
        [22] = 4000,
        [23] = 4000,
        [24] = 4000,
        [25] = 4000,
        [26] = 4000,
        [27] = 4000,
        [28] = 4000,
        [29] = 4000,
	[30] = 4000,
        [31] = 4000,
        [32] = 4000,
        [33] = 4000,
        [34] = 4000,
        [35] = 4000,
        [36] = 4000,
        [37] = 4000,
        [38] = 4000,
        [39] = 4000,
	[40] = 4000,
        [41] = 4000,
        [42] = 4000,
        [43] = 4000,
        [44] = 4000,
        [45] = 4000,
        [46] = 4000,
        [47] = 4000,
        [48] = 4000,
        [49] = 4000,
	[50] = 4000,
        [51] = 4000,
        [52] = 4000,
        [53] = 4000,
        [54] = 4000,
        [55] = 4000,
        [56] = 4000,
        [57] = 4000,
        [58] = 4000,
        [59] = 4000,
	[60] = 4000,
        [61] = 4000,
        [62] = 4000,
        [63] = 4000,
        [64] = 4000,
        [65] = 4000,
        [66] = 4000,
        [67] = 4000,
        [68] = 4000,
        [69] = 4000,
	[70] = 4000,
        [71] = 4000,
        [72] = 4000,
        [73] = 4000,
        [74] = 4000,
        [75] = 4000,
        [76] = 4000,
        [77] = 4000,
        [78] = 4000,
        [79] = 4000,
	[80] = 4000,
        [81] = 4000,
        [82] = 4000,
        [83] = 4000,
        [84] = 4000,
        [85] = 4000,
        [86] = 4000,
        [87] = 4000,
        [88] = 4000,
        [89] = 4000,
    	[90] = 4000,
        [91] = 4000,
        [92] = 4000,
        [93] = 4000,
        [94] = 4000,
        [95] = 4000,
        [96] = 4000,
        [97] = 4000,
        [98] = 4000,
        [99] = 4000
    },
	--- 全局道具掉率比例
    nGlobalDropRate = 1000000,

	--- 免费小号等级
	nFreeRoleLevel = 6,
	nFreeRoleLevel = 6,
	nFreeRoleTime = 86400,
	nFreeRoleSceneID = 143,
	nFreeRoleScenePosX = 148701184,
	nFreeRoleScenePosY = 76218368,
	nFreeRoleScenePosZ = 44777472,
	nFreeRoleSceneFaceDirection = 7168,
	nFreeModeCheckTimePeriod = 10,

	--
	-- 解除师徒关系的发起方的经验惩罚，万分比
	nMasterRewardExpPunishRate = 5000,
	-- 未拜师角色推送师傅的最高等级
	nMasterFindTeacherLevelLimit = 15,
	-- 师傅接受推送的cd, 秒
    nMasterTwitterCD = 60,

	-- master
	nMasterLvlOneStudentNum = 3,
	nMasterLevelTwoStudentNum = 4,
	nMasterLevelThreeStudentNum = 5,

	nMasterLvlTwoExp = 2000000,
	nMasterLvlThreeExp = 5000000,

	nMasterGradGiftMailIDForS = 4060,
	nMasterGradGiftMailIDForT = 4059,

	-- 开除徒弟扣除名师值万分比
	nMasterFireStudentPercent = 10000000,

	--出师师父经验系数
	nTeacherExpRewardRate = 900,
	--出师徒弟经验系数
	nStudentExpRewardRate = 300,
	--出师师父金币系数
	nTeacherExp2MoneyRate = 3333,
	--出师徒弟金币系数
	nStudentExp2MoneyRate = 3333,
	--练级道义值系数
	nMoralRate = 1000,
	--出师名师值值系数
	nMasterExpRate = 1000,


	--- 副本评分相关参数
	DungeonScore = {
	    nTimeScoreRate = { 0, 20000, 15000, 12000, 10000, 8000 },
	    nAttackScoreRate = { 0, 3000, 5000, 7000, 9000, 10000 },
	    nTotalAttackValue = { 0, 4, 6, 8, 10, 12 },
        nKillBossScore = 0,
        nKillEliteNpcScore = 0,
        nSwiftTimeScore = 0,
        nNeverDieScore = 0,
	    nGoalScoreDiff = { 999, 12, 9, 6, 3, 0 },
	    nTotalScore = { 0, 5, 8, 11, 14, 16 },
	},

	--- 调试选项
	DebugOption = {
	    debugai = false,
	    bShowErrorDialog = true,
	    debugsp = false,
	    dropstat = false,
		anticheat = true,
		nRetryTimesOnTransferError = 3,
		gpkauth = true,
		logfps = false,
		loghd = false,
		swapfreelist = false,
		debugitem = false,
		minestat = false,
		npcstat = false,
		bActivityRewardEnabled =  true,
	},

	--- GPK系统配置
	GpkPunishOption = {
		-- 是否打开旁路系统
		bEnableSidewayPunish = true,
		-- 是否打开心跳包发送
		bEnableGpkKeepAlive = true,
		-- 心跳包超时是否踢人
		bEnableKeepAliveTimeoutKick = false,
		-- 心跳包返回异常错误码4是否踢人
		bEnableKeepAliveReturn4Kick = false,
		-- 抓人人数下限
		nCatchMin = 300,
		-- 抓人人数上限
		nCatchMax = 700,
		-- 抓人队列长度
		nCatchDelayQueueLen = 600,
		-- 抓人队列超时(秒)
		nCatchDelayTimeout = 600,
		-- 客户端GPK漏报上限
		nClientGpkLostMax = 5,
		-- 客户端GPK漏报惩罚（金币池惩罚等级: 1, 2, 3）
		nClientGpkLostPunishType = 2,
		-- 客户端GPK被踢上限
		nClientGpkKickMax = 2,
		-- 客户端GPK心跳包间隔时间（秒）
		nKeepAliveInternal = 120,
		-- 是否只在特定场景踢人
		bOnlyKickInSpecialScene = true,
	},


	stArena = {
		nWashoutTime = {
			[0] = 1,
			[1] = 9,
			[2] = 50,
			[3] = 120
		},
		nSystemFollow = 10000,
		nSystemBase = 15000000,
		nRoleConsumption = 20000,
		nSceneTemplateID = 71,
		nSystemFollowCount = 2000,
		nTotalRewardNum = 100,
		nGetRewardPercent = 9000,
		nRewardChatMsgID = 0,

		nArenaBeginHour = 20,
		nArenaBeginMin	= 0,
		nArenaBeginTime = 72000,

		nArenaEndHour = 20,
		nArenaEndMin = 40,
		nArenaEndTime = 74400,

		nArenaRewardBeginHour = 20,
		nArenaRewardBeginMin = 40,
		nArenaRewardBeginTime = 74400,

		nArenaRewardEndHour	= 0,
		nArenaRewardEndMin = 0,
		nArenaRewardEndTime = 86400,

		nActivityLastTime = 2400,
	},

	-- 反外挂拼图发放时间间隔(秒)
	nAntiCheatInterval =
	{
		[0] = 15 * 60,
		[1] = 22 * 60,
		[2] = 30 * 60,
		[3] = 45 * 60,
		[4] = 60 * 60,
		[5] = 90 * 60,
	};

	-- 反外挂惩罚时间
	nAntiCheatPunishTime =
	{
		[0] = 0,
		[1] = 15 * 60,
		[2] = 60 * 60,
		[3] = 180 * 60,
	};

	-- 决定新角色拼图发放时间
	nInitAntiCheatLevel = 2;
	-- 拼图超时时间（秒）
	nAntiCheatTimeout = 600;
	-- 拼图发放间隔浮动比例
	nAntiCheatIntervalFloatPct = 2000;
	-- 是否踢人
	nAntiCheatKickRole = 1;

--------------沙巴克争霸战

	Sabac = {
		bEnabled = true,
		nSceneTempID = 152,
		OccupiedZoneLeftTop = {x=89665, y=49306, z=4355},
		OccupiedZoneRightBottom = {x=94727, y=49306, z=7935},
		WarZone1LeftTop = {x=1293, y=49236, z=3871},
		WarZone1RightBottom = {x=88125, y=49236, z=8524},
		WarZone2LeftTop = {x=89665, y=49306, z=4355},
		WarZone2RightBottom = {x=94727, y=49306, z=7935},


----复活点
		DefendRevivePos = {x=50152, y=47707, z=6373},
		nAttackReviveSceneID = 147,
		AttackRevivePos = {x=39442, y=55254, z=6612},
		nOtherReviveSceneID = 147,
		OtherRevivePos = {x=39442, y=55254, z=6612},

-----开始结束时间
		nStartTime = 2000,
		nStartOccupyTime = 2010,
		nErectStatusCost = 100000,
		nEndTime = 2200,
		nEnrollCost = 50000,
		nEnrollItemID = 90196,
		nEnrollItemCount = 1,

----树立雕像金币
		nErectStatusCost = 100000,

----胜利奖励
	--	nLeaderAwardItemID = 0,
	--	nMemberAwardItemID = 0,

------公告消息
		nAwardMailTitleStringID = 2013,
		nAwardMailContentStringID = 2014,
	},
------ 问卷调查
	Survey = {
		[0] = {nMaxLevel = 100, 	szSurveyPath = 'http://wenjuan.sdo.com:9091/survey/survey?surveyId=13834'},
		[1] = {nMaxLevel = 100, 	szSurveyPath = 'http://wenjuan.sdo.com:9091/survey/survey?surveyId=9439'},
		[2] = {nMaxLevel = 100, 	szSurveyPath = 'http://wenjuan.sdo.com:9091/survey/survey?surveyId=9441'},

	},

	nSceneBusyPercent = 6000,
	nSceneFullPercent = 8000,

----- 公会淘汰时间, 秒, 最小周期是1天
	nWashoutDeletedGuildTime = 604800,
----- 师徒淘汰时间，秒，最小周期是1天
	nWashoutDeletedMasterTime = 604800,

	nTeleportRingCDTime = 10000,
	nProbeNecklaceCDTime = 10000,
	nMemoSuitCDTime = 180000,
	szRecallFailMessage = "无法对%s使用天地合一功能",

	nMineInterval = 1438,
	nMineMaxValue = 500000,
	nMineCDTime = 20 * 60 * 1000,
	nMineDropRate = 10000,

	ChatConfig = {
		nNormalMsgInterval = 1000,
        nGroupMsgInterval = 1000,
		nMaxDailyGroupMsg = 1000000,
		nTrumpetItemID = 2201,
		nGroupChatLevel = 7,
		nGroupChatCost = 1000;
		nGlobalChatAwardInterval = 2000;	-- 新增 聊天违规减免间隔控制(毫秒)
		nAutoForbidTime = 600;				-- 新增 自动禁言时间(秒)
		nMaxFoulTimes = 10;					-- 新增 最大违规次数
		bCanChatInSafeArea = false;			-- 新增 是否可在安全区聊天
	},

	GpkPunishGoldPool = {
		[1]=-10000,
		[2]=-100000,
		[3]=-500000,
	},

	ArrestConfig = {
		nSceneTempID = 179,
		Pos = { x= 9500, y = 11000, z = 2100 },
		nDefaultDuration = 12 * 3600 * 1000,
	},

	-- pet,unit: sec
	nPetDisappearTime = 0,

	-- exp_bottle经验瓶
	nExpBottlePortion = 10000,  --储存比例
	nExpBottleFactor = 4000,    --折损后储存比例

	-- low level
	nRoleLowLevel = 7,

	-- server moneytype_02 limit: hourly
	nServerMoneytype02Limit = 2000000000,
	-- use rune weight 2
	nRuneTimesBeforeWeight2 = 10000,

	nGambleItemCountBeforeDropGroup2 = 180000,

	-- spell book gambole
	nSpellBookGambleCostItemID = 111003,
	nSpellBookGambleCostItemCount = 60,
	nSpellBookGambleDropGroupID = 30000,
	nSpellBookGambleDropGroupID2 = 30001,
	dwSpellBookGambleSuccessRate = 2000,
	nSpellBookGambleItemCountBeforeDropGroup2 = 36000,

	-- 每日好感度上限
	nMaxIntimacyEveryday = 335,
	-- 最大好感度，不超过65535
	nMaxIntimacy = 10000,
	-- 同队伍同场景好感度增加值
	nTeamIntimacyValue = 2,
	-- 队伍好感度刷新间隔，最小5分钟
	nUpdateTeamIntimacyInterval = 5 * 60 * 1000,
	-- 聊天好感度增加值
	nChatIntimacyValue = 1,
	-- 聊天好感度刷新间隔
	nUpdateChatIntimacyInterval = 12 * 60 * 1000,
	-- 公会好感度增加值
	nGuildIntimacyValue = 50,
	-- 公会好感度刷新间隔，最小30分钟
	nUpdateGuildIntimacyInterval = 1440 * 60 * 1000,
	-- 交易需要好感度
	nTradeNeedIntimacyValue = 1000,

--------至尊拍卖行

	--拍卖行是否开放
	bAuctionOpen = true;
	--拍卖行交易税（万分比）
	nAuctionTax = 200,
	--拍卖行吃保证金扣税（万分比）
	nAuctionDepositTax = 1000,
	--最多拍卖物品
	nMaxAuctionSellingItems = 5,
	--最多竞标物品
	nMaxAuctionBuyingItems = 5,
	--最多已拍卖物品
	nMaxAuctionSoldItems = 100,
	--最多已购买物品
	nMaxAuctionBoughtItems = 100,
	--3种拍卖时间长度（单位：小时）
	nAuctionTimeInterval =
	{
		[0] = 6,
		[1] = 12,
		[2] = 24
	},
	--公开拍卖花费
	nAuctionOpenCost = 1000000,
	--邮件中金币冷却时间（单位：秒）
	nAuctionMoneyCDTime = 86400,
	--拍卖行防压秒时间（单位：秒）
	nAuctionFinishDelayTime = 120,
	--拍卖行等待尾款时间（单位：小时）
	nAuctionWaitForPaymentTime = 24,

	--是否启用动态密码验证
	bNeedDynamicPasswordVerification = true,
	--动态密码验证间隔(秒)
	nDynamicPasswordCheckInterval = 7200,

	--换线等待时间
	nChangeLineDuration = 5 * 1000,

	----客户端打开拍卖行按钮
	dwClientOption = 7,
	
	-------安全区泡点，增加双倍经验值
	ExtraExpPos1 = {
		nSceneTempID = 143,
		x = 62700,
		y = 48000,
		z = 43840,
		nRange = 128 * 20,
	},
	ExtraExpPos2 = {
		nSceneTempID = 147,
		x = 39100,
		y = 55300,
		z = 6576,
		nRange = 128 * 18,

	},
	
};

function convert(pos)
	pos.x, pos.y, pos.z = ConvertCoordO2N(pos.x, pos.y, pos.z);
end

function convert_rectangle(lt, rb)
	local p1 = { x = lt.x, y = lt.y, z = lt.z };
	local p2 = { x = lt.x, y = rb.y, z = lt.z };
	local p3 = { x = rb.x, y = rb.y, z = lt.z };
	local p4 = { x = rb.x, y = lt.y, z = lt.z };

	convert(p1);
	convert(p2);
	convert(p3);
	convert(p4);

	lt.x = p2.x;
	lt.y = p1.y;
	rb.x = p4.x;
	rb.y = p3.y;
end

convert(GameWorldConfig.ErrorReturnPos);
convert(GameWorldConfig.RedNameReturnPos);
convert(GameWorldConfig.DefaultRevivePos);

convert_rectangle(GameWorldConfig.Sabac.OccupiedZoneLeftTop, GameWorldConfig.Sabac.OccupiedZoneRightBottom);
convert_rectangle(GameWorldConfig.Sabac.WarZone1LeftTop, GameWorldConfig.Sabac.WarZone1RightBottom);
convert_rectangle(GameWorldConfig.Sabac.WarZone2LeftTop, GameWorldConfig.Sabac.WarZone2RightBottom);

convert(GameWorldConfig.Sabac.DefendRevivePos);
convert(GameWorldConfig.Sabac.AttackRevivePos);
convert(GameWorldConfig.Sabac.OtherRevivePos);

convert(GameWorldConfig.ArrestConfig.Pos);

convert(GameWorldConfig.ExtraExpPos1);
convert(GameWorldConfig.ExtraExpPos2);

Include("globalconfig/censored_word_list.lua");
Include("globalconfig/game_world_table.lua");
