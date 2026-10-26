
PACKAGE_TABLE = {
--	{
--		func = 'sampel_func',
--		maxitemcount = 2,    --包裹需要空格数
--		checkvariable = 145, --领取礼包时间所在的变量号
--		waittime = 1800,     --需要等待的时间，单位：秒
--		opentimesvariable = 152, --打开次数所在变量号
--		maxopentimes = 1,    可打开次数

--		{ itemid = 1, itemcount = 5, percent = 80 },
--		{ itemid = 2, itemcount = 4, class = clsWarrior },
--		{ itemid = 3, itemcount = 3, class = clsMage },
--		{ itemid = 4, itemcount = 2, class = clsRogue },
--		{ itemid = 5, itemcount = 1, class = clsArcher },
--		{ itemid = 6, itemcount = 7, sex = cstMale },
--		{ itemid = 7, itemcount = 6, sex = cstFemale },
--		{ select =
--			{
--				{itemid = 1, itemcount = 4, weight = 1},
--				{itemid = 2, itemcount = 3, weight = 2},
--				{itemid = 3, itemcount = 2, weight = 4},
--				{itemid = 4, itemcount = 1, weight = 8},
--			}
--		},
--		{ exp = 100 },
--		{ title = 1 },
--		{ moneytype = MONEYTYPE_02, moneyamount = 100 },
--		{ questid = 1, varid = 0, varvalue = 1 },
--		{ doodadid = 3283}, --doodad id
--		{ pkvalue = 100, chance = 50 },
--		{ announce = '{role_name}使用了一个火炬！'}, --公告内容，"{*}"为需要替换的内容，新替换内容参考ANNOUNCE_REPL_STRING_FUNC_TABLE表定义
--		{ aura = 1 }, 获得一个aura
--	},

	{
		func = 'biqiyongshi',
		maxitemcount = 6,
		{ title = 91 },
		{ moneytype = MONEYTYPE_02, moneyamount = 2000 },
		--{ itemid = 10121, itemcount = 2 },
		{ itemid = 381, itemcount = 1 },
		{ itemid = 381, itemcount = 1 },
		{ itemid = 381, itemcount = 1 },
		{ itemid = 381, itemcount = 1 },
		{ itemid = 381, itemcount = 1 },
		{ itemid = 381, itemcount = 1 },
		--{ itemid = 10552131, itemcount = 20,percent = 10 },
		--{ itemid = 10552132, itemcount = 20,percent = 10 },
		--{ itemid = 10552133, itemcount = 20,percent = 10 },
		--{ itemid = 10552134, itemcount = 20,percent = 10 },

	},

	{
		func = 'biqibazhu',
		maxitemcount = 8,
		{ title = 92 },
		{ moneytype = MONEYTYPE_02, moneyamount = 10000 },
		--{ itemid = 10610251, itemcount = 1 },
		--{ itemid = 10122, itemcount = 2 },


		--绑定道具
		--{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1 },
		{ itemid = 382, itemcount = 1 },
		{ itemid = 382, itemcount = 1 },
		{ itemid = 382, itemcount = 1 },
		{ itemid = 382, itemcount = 1 },
		{ itemid = 382, itemcount = 1 },
		{ itemid = 382, itemcount = 1 },
		{ itemid = 99900026, itemcount = 1 },
		--{ itemid = 10552131, itemcount = 20,percent = 50 },
		--{ itemid = 10552132, itemcount = 20,percent = 50 },
		--{ itemid = 10552133, itemcount = 20,percent = 50 },
		--{ itemid = 10552134, itemcount = 20,percent = 50 },

	},
	--------回归礼盒
	{
		func = 'huigui_lihe',
		maxitemcount = 2,
		{ title = 103 },
		{ itemid = 2800150, itemcount = 1, bind = true }, 
		{itemid = 199900019, itemcount = 1, class = clsWarrior},
		{itemid = 199900018, itemcount = 1, class = clsMage},
		{itemid = 199900021, itemcount = 1, class = clsTaoist},
	

	},
	------------------------劳动凭证
	{
		func = 'laodong',
		maxitemcount = 0,
		{ exp = 20000 },
	},
	------------------------回归礼包
	{
		func = 'huigui',
		maxitemcount = 1,    --包裹需要空格数

		{	select =
			{

				{ itemid = 1800015, itemcount = 1, weight = 5455  ,bind = true }, --海4券		5.45500%
				{ itemid = 1800020, itemcount = 2, weight = 7273  ,bind = true }, --魔虫窟		7.27300%
				{ itemid = 1500201, itemcount = 2, weight = 21818 ,bind = true }, --金创中*3	21.81800%
				{ itemid = 1500204, itemcount = 2, weight = 21818 ,bind = true }, --魔法中*3	21.81800%
				{ itemid = 1500206, itemcount = 2, weight = 21818 ,bind = true }, --太阳水*3	21.81800%
				{ itemid = 1500210, itemcount = 2, weight = 10909 ,bind = true }, --超金创*3	10.90900%
				{ itemid = 1500211, itemcount = 2, weight = 10909 ,bind = true }, --超魔法*3	10.90900%

			},
			--announce_expensive = ' {role_name} 从回归礼包里获得了道具:[item_name]',
		},
	},

	------------------------联盟礼包
	{
		func = 'lianmeng',
		maxitemcount = 2,    --包裹需要空格数
		{ title = 1 },
	},
	
	{
		func = 'LiaoShangYao6',
		maxitemcount = 6, 
		{ itemid = 383, itemcount = 1 },
		{ itemid = 383, itemcount = 1 },
		{ itemid = 383, itemcount = 1 },
		{ itemid = 383, itemcount = 1 },
		{ itemid = 383, itemcount = 1 },
		{ itemid = 383, itemcount = 1 },
	},

	------------------------灰狼的馈赠
	{
		func = 'jineng',
		maxitemcount = 1,    --包裹需要空格数

		{	select =
			{
				{ itemid = 1800009, itemcount = 1, weight = 960000 }, --小金币包
				{ itemid = 33012, itemcount = 1, weight = 16615 }, --群愈
				{ itemid = 31035, itemcount = 1, weight = 10385 }, --野蛮
				{ itemid = 32537, itemcount = 1, weight = 2386 }, --冰咆哮
				{ itemid = 31037, itemcount = 1, weight = 2386 }, --狮子吼
				{ itemid = 31036, itemcount = 1, weight = 1364 }, --烈火
				{ itemid = 33015, itemcount = 1, weight = 1591 }, --无极
				{ itemid = 33018, itemcount = 1, weight = 4773 }, --气功波
				{ itemid = 32535, itemcount = 1, weight = 139 }, --魔法盾
				{ itemid = 33008, itemcount = 1, weight = 111 }, --召唤
				{ itemid = 31038, itemcount = 1, weight = 58 }, --逐日
				{ itemid = 32540, itemcount = 1, weight = 96 }, --流星
				{ itemid = 3000, itemcount = 1, weight = 96 }, --嗜血


			},
		},
	},

	------------------------宝箱
	{
		func = 'baoxiang',
		maxitemcount = 1,    --包裹需要空格数
		deleteid = 1800052;
		{	select =
			{
				{ itemid = 2211, itemcount = 1,  weight  = 250000 },	--蛋糕烟花		1
				{ itemid = 2201, itemcount = 1, weight = 90000 },		--千里传音		3
				{ itemid = 80003, itemcount = 1, weight = 60000 },		--祝福油			5
				{ itemid = 383, itemcount = 1, weight = 60000 },		--疗伤包			5
				{ itemid = 91102, itemcount = 1, weight = 30000},		--幽冥海入场券		2
				{ itemid =1800009, itemcount = 1, weight = 200000},		--小金币包		10

				{ itemid = 21001, itemcount = 1, weight = 29286},		--战士铭文石		15
				{ itemid = 21002, itemcount = 1, weight = 85857},		--法师铭文石		5
				{ itemid = 21003, itemcount = 1, weight = 85857},		--道士铭文石		5

				{ itemid = 90217, itemcount = 1, weight = 16667},		--烈火剑法残卷		15
				{ itemid = 90218, itemcount = 1, weight = 25000},		--冰咆哮残卷		10
				{ itemid = 90219, itemcount = 1, weight = 8333},		--召唤神兽残卷		30

				{ itemid = 1800011, itemcount = 1, weight = 35000},		--大金币包		100

				{ itemid = 1800033, itemcount = 1, weight = 5000},		--BOSS召唤残券		1500
				{ itemid = 1800019, itemcount = 1, weight = 3334},		--500W经验丹		1000
				{ itemid = 2800018, itemcount = 1, weight = 1666},		--10%经验丹		3000

				{ itemid = 2800003, itemcount = 1, weight = 2500},		--沃玛解封券		1500
				{ itemid = 2800004, itemcount = 1, weight = 1667},		--祖玛解封券		1000
				{ itemid = 2800005, itemcount = 1, weight = 833 },		--赤月解封券		3000

			},
			announce_expensive = ' {role_name} 从三月宝箱里获得了道具:[item_name]',
		},
	},
------------------------武器宝箱
	{
		func = 'wqbaoxiang',
		maxitemcount = 1,    --包裹需要空格数

		{	select =
			{

			--消耗		20.00%
			--空奖		77.834%
			--沃玛		2.00%
			--2.5		0.141%
			--祖玛		0.025%
				{ itemid = 2212, itemcount = 1, weight = 28708 }, --礼花
				{ itemid = 383, itemcount = 1, weight = 11483 }, --药包
				{ itemid = 383, itemcount = 1, weight = 11486 }, --魔法药(中)包
				{ itemid = 2201, itemcount = 1, weight = 28708 }, --千里传音
				{ itemid = 100002, itemcount = 1, weight = 57416 }, --初级红名
				{ itemid = 100003, itemcount = 1, weight = 19138 }, --中级红名
				{ itemid = 80003, itemcount = 1, weight = 14354 }, --祝福油
				{ itemid = 91102, itemcount = 1, weight = 28708 }, --幽冥海入场券

				{ itemid = 1800009, itemcount = 1, weight = 778340 }, --小金币包

				{ itemid = 99900018, itemcount = 1, weight = 6667 }, --魔杖
				{ itemid = 99900019, itemcount = 1, weight = 6666 }, --炼狱
				{ itemid = 99900021, itemcount = 1, weight = 6667 }, --银蛇

				{ itemid = 99900023, itemcount = 1, weight = 587 }, --血饮
				{ itemid = 99900024, itemcount = 1, weight = 587 }, --无尽棍
				{ itemid = 99900022, itemcount = 1, weight = 235 }, --井中月

				{ itemid = 99900025, itemcount = 1, weight = 50 }, --裁决
				{ itemid = 99900027, itemcount = 1, weight = 100 }, --龙纹
				{ itemid = 99900028, itemcount = 1, weight = 100 }, --骨玉

			},
			announce_expensive = ' {role_name} 从装备宝箱里获得了道具:[item_name]',
		},
	},

------------------------包总专用
	{
		func = 'dabaozong',
		maxitemcount = 1,    --包裹需要空格数

		{	select =
			{

				{ itemid = 99900025, itemcount = 1, weight = 1 }, --裁决之杖
				{ itemid = 99900025, itemcount = 1, weight = 1 }, --裁决之杖
			},
			announce_expensive = ' {role_name} 从装备宝箱里获得了道具:[item_name]',
		},
	},
--*********************五月宝箱
	{
		func = 'wuyuebaoxiang',
		maxitemcount = 1,    --包裹需要空格数
		deleteid = 1800052;
		{	select =
			{
				{ itemid = 2211, itemcount = 1,  weight  = 200000 },	--蛋糕烟花		1
				{ itemid = 2201, itemcount = 1, weight = 110000 },		--千里传音		3
				{ itemid = 80003, itemcount = 1, weight = 60000 },		--祝福油			5
				{ itemid = 383, itemcount = 1, weight = 60000 },		--疗伤包			5
				{ itemid = 91102, itemcount = 1, weight = 65000},		--幽冥海入场券		2
				{ itemid =1800009, itemcount = 1, weight = 150000},		--小金币包		10
				{ itemid = 1800033, itemcount = 1, weight = 30000 },	--BOSS召唤卷碎片
				{ itemid = 2800003, itemcount = 1, weight = 40000 },	--沃玛解封卷

				{ itemid = 21001, itemcount = 1, weight = 29286},		--战士铭文石		15
				{ itemid = 21002, itemcount = 1, weight = 85857},		--法师铭文石		5
				{ itemid = 21003, itemcount = 1, weight = 85857},		--道士铭文石		5

				{ itemid = 90217, itemcount = 1, weight = 14000},		--烈火剑法残卷		15
				{ itemid = 90218, itemcount = 1, weight = 25000},		--冰咆哮残卷		10
				{ itemid = 90219, itemcount = 1, weight = 8333},		--召唤神兽残卷		30

				{ itemid = 1800011, itemcount = 1, weight = 25000},		--大金币包		100

				{ itemid = 31036, itemcount = 1, weight = 1667 },		--烈火剑法		1500
				{ itemid = 32537, itemcount = 1, weight = 2500},		--冰咆哮			1000
				{ itemid = 33008, itemcount = 1, weight = 833 },		--召唤神兽		3000

				{ itemid = 2800004, itemcount = 1, weight = 5833 },		--祖玛解封卷
				{ itemid = 1800019, itemcount = 1, weight = 833 },		--五百万经验丹

			},
			announce_expensive = ' {role_name} 从五月宝箱里获得了道具:[item_name]',
		},
	},
	--*********************未知征兆
	{
		func = 'weizhi',
		maxitemcount = 1,    --包裹需要空格数
		deleteid = 2800046;
		xingyun = 10;
		{	select =
			{
				{ itemid = 2800006, itemcount = 1, weight = 160284 }, --幸运碎片
				{ itemid = 2201, itemcount = 1, weight = 45795 }, --千里传音
				{ itemid = 80003, itemcount = 1, weight = 32057 }, --祝福油
				{ itemid = 383, itemcount = 1, weight = 80142 }, --疗伤包
				{ itemid = 1800009, itemcount = 1, weight = 70387 }, --小金币
				{ itemid = 1800011, itemcount = 1, weight = 4580 }, --大金币
				{ itemid = 21001, itemcount = 1, weight = 32057 }, --战士铭文
				{ itemid = 21002, itemcount = 1, weight = 53428 }, --法师铭文
				{ itemid = 21003, itemcount = 1, weight = 53428 }, --道士铭文
				{ itemid = 1800015, itemcount = 1, weight = 4505 }, --海4传送券
				{ itemid = 2800003, itemcount = 1, weight = 32057 }, --沃玛解封券
				{ itemid = 1800033, itemcount = 1, weight = 22898 }, --BOSS召唤碎片
				{ itemid = 2800055, itemcount = 10, weight = 160284 }, --玛法1
				{ itemid = 2800056, itemcount = 10, weight = 80142 }, --玛法2
				{ itemid = 2800057, itemcount = 10, weight = 53428 }, --玛法3
				{ itemid = 2800051, itemcount = 1, weight = 16028 }, --玛法100
				{ itemid = 2800047, itemcount = 1, weight = 31667 }, --沃战礼盒
				{ itemid = 2800048, itemcount = 1, weight = 31667 }, --沃法礼盒
				{ itemid = 2800049, itemcount = 1, weight = 31667 }, --沃道礼盒
				{ itemid = 2800050, itemcount = 1, weight = 3000 }, --祖玛礼盒
				{ itemid = 2800062, itemcount = 1, weight = 500 }, --赤月礼盒

			},
		},
	},
--*********************沃玛战士宝箱
	{
		func = 'wozhan',
		maxitemcount = 1,    --包裹需要空格数
		{	select =
			{
				{   itemid   =   299920016  ,   itemcount   =   1  ,   weight   =   1600   }, -- 沃玛战士项链
				{   itemid   =   399930018  ,   itemcount   =   1  ,   weight   =   3400   }, --  沃玛战士戒指
				{   itemid   =   399940020  ,   itemcount   =   1  ,   weight   =   5000   }, --  沃玛战士手镯
			},
		},
	},
--*********************沃玛法师宝箱
	{
		func = 'wofa',
		maxitemcount = 1,    --包裹需要空格数
		{	select =
			{
				{   itemid   =   299920020  ,   itemcount   =   1  ,   weight   =   1600   }, -- 沃玛法师项链
				{   itemid   =   399930017  ,   itemcount   =   1  ,   weight   =   3400   }, --  沃玛法师戒指
				{   itemid   =   399940011  ,   itemcount   =   1  ,   weight   =   5000   }, --  沃玛法师手镯
			},
		},
	},
	
	--*********************沃玛道士宝箱
	{
		func = 'wodao',
		maxitemcount = 1,    --包裹需要空格数
		{	select =
			{
				{   itemid   =   299920021  ,   itemcount   =   1  ,   weight   =   1600   }, -- 沃玛道士项链
				{   itemid   =   399930014  ,   itemcount   =   1  ,   weight   =   3400   }, --  沃玛道士戒指
				{   itemid   =   399940015  ,   itemcount   =   1  ,   weight   =   5000   }, --  沃玛道士手镯
			},
		},
	},
	
	--*********************祖玛盒子
	{
		func = 'zuma',
		maxitemcount = 1,    --包裹需要空格数
		{  select =
			{
				{   itemid   =   299920017  ,   itemcount   =   1  ,   weight   =   600   }, --  绿色项链·战
				{   itemid   =   399930019  ,   itemcount   =   1  ,   weight   =   456   }, --  力量戒指·传
				{   itemid   =   299930019  ,   itemcount   =   1  ,   weight   =   456   }, --  力量戒指·奇
				{   itemid   =   399940012  ,   itemcount   =   1  ,   weight   =   683   }, --  骑士手镯·永
				{   itemid   =   299940012  ,   itemcount   =   1  ,   weight   =   683   }, --  骑士手镯·恒
				{   itemid   =   399940021  ,   itemcount   =   1  ,   weight   =   683   }, --  阎罗手套·永
				{   itemid   =   299940021  ,   itemcount   =   1  ,   weight   =   683   }, --  阎罗手套·恒
				{   itemid   =   299920019  ,   itemcount   =   1  ,   weight   =   600   }, --  恶魔铃铛·法
				{   itemid   =   399930020  ,   itemcount   =   1  ,   weight   =   456   }, --  紫碧螺·传
				{   itemid   =   299930020  ,   itemcount   =   1  ,   weight   =   456   }, --  紫碧螺·奇
				{   itemid   =   399940016  ,   itemcount   =   1  ,   weight   =   683   }, --  龙之手镯·永
				{   itemid   =   299940016  ,   itemcount   =   1  ,   weight   =   683   }, --  龙之手镯·恒
				{   itemid   =   299920018  ,   itemcount   =   1  ,   weight   =   600   }, --  灵魂项链·道
				{   itemid   =   399930021  ,   itemcount   =   1  ,   weight   =   456   }, --  灵魂项链·道
				{   itemid   =   299930021  ,   itemcount   =   1  ,   weight   =   456   }, --  灵魂项链·道
				{   itemid   =   399940010  ,   itemcount   =   1  ,   weight   =   683   }, --  灵魂项链·道
				{   itemid   =   299940010  ,   itemcount   =   1  ,   weight   =   683   }, --  灵魂项链·道
			},
		},
	},
	
	--*********************赤月盒子
	{
		func = 'chiyue',
		maxitemcount = 1,    --包裹需要空格数
		{  select =
			{
				{ itemid = 299920027, itemcount = 1, weight = 303 }, --圣战项链·战
				{ itemid = 299930033, itemcount = 1, weight = 606 }, --圣战戒指·传
				{ itemid = 399930033, itemcount = 1, weight = 606 }, --圣战戒指·奇
				{ itemid = 299940024, itemcount = 1, weight = 909 }, --圣战手镯·永
				{ itemid = 399940024, itemcount = 1, weight = 909 }, --圣战手镯·恒
				{ itemid = 299920028, itemcount = 1, weight = 303 }, --法神项链·法
				{ itemid = 299930034, itemcount = 1, weight = 606 }, --法神戒指·传
				{ itemid = 399930034, itemcount = 1, weight = 606 }, --法神戒指·奇
				{ itemid = 299940025, itemcount = 1, weight = 909 }, --法神手镯·永
				{ itemid = 399940025, itemcount = 1, weight = 909 }, --法神手镯·恒
				{ itemid = 299920029, itemcount = 1, weight = 303 }, --天尊项链·道
				{ itemid = 299930035, itemcount = 1, weight = 606 }, --天尊戒指·传
				{ itemid = 399930035, itemcount = 1, weight = 606 }, --天尊戒指·奇
				{ itemid = 299940026, itemcount = 1, weight = 909 }, --天尊手镯·永
				{ itemid = 399940026, itemcount = 1, weight = 909 }, --天尊手镯·恒

			},
		},
	},
	
	--********************下面是主播礼包
	--******************20*******************************
	{
		func = 'zhubo20',
		maxitemcount = 5,    --包裹需要空格数

		{ itemid = 386, itemcount = 1, bind = true },
		{ itemid = 386, itemcount = 1, bind = true },
		{ itemid = 386, itemcount = 1, bind = true },
		{ itemid = 386, itemcount = 1, bind = true },
		{ itemid = 386, itemcount = 1, bind = true },
		{ itemid = 2800029, itemcount = 1, bind = true },

	},
	--******************35*******************************
	{
		func = 'zhubo35',
		maxitemcount = 5,    --包裹需要空格数

		{ itemid = 388, itemcount = 1, bind = true },
		{ itemid = 388, itemcount = 1, bind = true },
		{ itemid = 388, itemcount = 1, bind = true },
		{ itemid = 388, itemcount = 1, bind = true },
		{ itemid = 388, itemcount = 1, bind = true },

	},
	--**************************************************************

	{
		func = 'shengwangbaoshi1',
		maxitemcount = 5,

		{ itemid = 10110, itemcount = 1 },
		{ itemid = 10210, itemcount = 1 },
		{ itemid = 10310, itemcount = 1 },
		{ itemid = 10410, itemcount = 1 },
		{ itemid = 10510, itemcount = 1 },

	},
	{
		func = 'shengwangbaoshi2',
		maxitemcount = 5,

		{ itemid = 10120, itemcount = 1 },
		{ itemid = 10220, itemcount = 1 },
		{ itemid = 10320, itemcount = 1 },
		{ itemid = 10420, itemcount = 1 },
		{ itemid = 10520, itemcount = 1 },

	},
	{
		func = 'OnUseNovicePackage',
		maxitemcount = 2,

		{ itemid = 361, itemcount = 1 },
		{ itemid = 1000015, itemcount = 1 },

	},

	{
		func = 'OnUseNovicePackage2',
		maxitemcount = 2,

		{ itemid = 100001, itemcount = 5 },
		{ itemid = 1000015, itemcount = 1 },

	},

	{
		func = 'OnUseNovicePackage3',
		maxitemcount = 2,

		{ itemid = 100001, itemcount = 5 },


	},


	{
		func = 'OnUseTestPackage1',
		maxitemcount = 1,

		{ itemid = 361, itemcount = 1 },
		--{ itemid = 1100010, itemcount = 5 },
		--{ itemid = 2, itemcount = 100000 },
		--{ itemid = 1, itemcount = 1000},

	},

	{
		func = 'OnUseTestPackage2',
		maxitemcount = 1,
		{ itemid = 361, itemcount = 1 },
		--{ itemid = 6, itemcount = 300 },
		--{ itemid = 1100015, itemcount = 1 },
		--{ itemid = 2, itemcount = 500000 },


	},

	{
		func = 'OnUseTestPackage3',
		maxitemcount = 1,
		{ itemid = 361, itemcount = 1 },
		{ moneytype = MONEYTYPE_02, moneyamount = 100 },
		--{ itemid = 21001, itemcount = 2 },
		--{ itemid = 110001, itemcount = 5 },
		--{ itemid = 110002, itemcount = 1 },
		--{ itemid = 1100020, itemcount = 1 },
		{ moneytype = MONEYTYPE_02, moneyamount = 1000000 },
		--{ itemid = 20310121, itemcount = 1, class = clsWarrior },
		--{ itemid = 121512, itemcount = 1, class = clsWarrior },
		--{ itemid = 20340121, itemcount = 1, class = clsMage },
		--{ itemid = 121523, itemcount = 1, class = clsMage },
		--{ itemid = 20320121, itemcount = 1, class = clsRogue },
		--{ itemid = 121533, itemcount = 1, class = clsRogue },
		--{ itemid = 20336121, itemcount = 1, class = clsArcher },
		--{ itemid = 121543, itemcount = 1, class = clsArcher },
	},

	{
		func = 'OnUseTestPackage4',
		maxitemcount = 1,
		{ moneytype = MONEYTYPE_02, moneyamount = 1000000 },
	--	{ itemid = 361, itemcount = 1 },
		--{ itemid = 6, itemcount = 500 },
		--{ itemid = 20001, itemcount = 2 },
		--{ itemid = 1010001, itemcount = 1 },
		--{ itemid = 10100, itemcount = 1 },
		--{ itemid = 10200, itemcount = 1 },
		--{ itemid = 10300, itemcount = 1 },

		--{ itemid = 20310121, itemcount = 1, class = clsWarrior },
		--{ itemid = 121512, itemcount = 1, class = clsWarrior },
		--{ itemid = 20340121, itemcount = 1, class = clsMage },
		--{ itemid = 121523, itemcount = 1, class = clsMage },
		--{ itemid = 20320121, itemcount = 1, class = clsRogue },
		--{ itemid = 121533, itemcount = 1, class = clsRogue },
		--{ itemid = 20336121, itemcount = 1, class = clsArcher },
		--{ itemid = 121543, itemcount = 1, class = clsArcher },
	},

	{
		func = 'OnUseMasterPackage',
		maxitemcount = 2,
		{ moneytype = MONEYTYPE_02, moneyamount = 100 },
		--{ itemid = 122, itemcount = 5 },
		{ itemid = 100001, itemcount = 10 },

	},

	{
		func = 'OnUseMasterPackage101',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1 },
		--{ itemid = 1030012, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage102',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1 },
		--{ itemid = 1030012, itemcount = 2 },

	},
	{
		func = 'OnUseMasterPackage103',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1 },
		--{ itemid = 1030012, itemcount = 3 },

	},
	{
		func = 'OnUseMasterPackage104',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1 },
		--{ itemid = 1030012, itemcount = 4 },

	},
	{
		func = 'OnUseMasterPackage105',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1 },
		--{ itemid = 1030012, itemcount = 5 },

	},
	{
		func = 'OnUseMasterPackage106',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1 },
		--{ itemid = 1030012, itemcount = 6 },

	},
	{
		func = 'OnUseMasterPackage107',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1 },
		--{ itemid = 1030012, itemcount = 7 },

	},
	{
		func = 'OnUseMasterPackage108',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1 },
		--{ itemid = 1030012, itemcount = 8 },

	},
	{
		func = 'OnUseMasterPackage109',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1 },
		--{ itemid = 1030012, itemcount = 9 },

	},
------------徒弟被强制出师时徒弟获得的道具
	{
		func = 'OnUseMasterPackage110',
		maxitemcount = 2,
		{ exp = 10000 },
		{ itemid = 363, itemcount = 1 },
		--{ itemid = 1030012, itemcount = 3 },

	},
------------徒弟正常出师时徒弟获得的道具
	{
		func = 'OnUseMasterPackage111',
		maxitemcount = 2,
		{ exp = 20000 },
		{ itemid = 363, itemcount = 1 },
		--{ itemid = 1030012, itemcount = 5 },

	},
	{
		func = 'OnUseMasterPackage201',
		maxitemcount = 3,

		{ itemid = 363, itemcount = 1 },
		{ itemid = 80003, itemcount = 1 },
		{ itemid = 1350001, itemcount = 1 },
	},
	{
		func = 'OnUseMasterPackage202',
		maxitemcount = 3,

		{ itemid = 363, itemcount = 1 },
		{ itemid = 80003, itemcount = 1 },
		{ itemid = 1350001, itemcount = 1 },
	},
	{
		func = 'OnUseMasterPackage203',
		maxitemcount = 3,

		{ itemid = 363, itemcount = 1 },
		{ itemid = 80003, itemcount = 1 },
		{ itemid = 1350001, itemcount = 1 },
	},
	{
		func = 'OnUseMasterPackage204',
		maxitemcount = 3,

		{ itemid = 363, itemcount = 1 },
		{ itemid = 80003, itemcount = 1 },
		{ itemid = 1350001, itemcount = 1 },
	},
	{
		func = 'OnUseMasterPackage205',
		maxitemcount = 3,

		{ itemid = 363, itemcount = 1 },
		{ itemid = 80003, itemcount = 1 },
		{ itemid = 1350001, itemcount = 1 },
	},
	{
		func = 'OnUseMasterPackage206',
		maxitemcount = 3,

		{ itemid = 363, itemcount = 1 },
		{ itemid = 80003, itemcount = 1 },
		{ itemid = 1350001, itemcount = 1 },
	},
	{
		func = 'OnUseMasterPackage207',
		maxitemcount = 3,

		{ itemid = 363, itemcount = 1 },
		{ itemid = 80003, itemcount = 1 },
		{ itemid = 1350001, itemcount = 1 },
	},
	{
		func = 'OnUseMasterPackage208',
		maxitemcount = 3,

		{ itemid = 363, itemcount = 1 },
		{ itemid = 80003, itemcount = 1 },
		{ itemid = 1350001, itemcount = 1 },
	},
	{
		func = 'OnUseMasterPackage209',
		maxitemcount = 3,

		{ itemid = 363, itemcount = 1 },
		{ itemid = 80003, itemcount = 1 },
		{ itemid = 1350001, itemcount = 1 },
	},

------------徒弟出师时师傅获得的道具
	{
		func = 'OnUseMasterPackage210',
		maxitemcount = 3,
		{ exp = 15000 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 80003, itemcount = 1 },
		{ itemid = 1350002, itemcount = 1 },
	},

------------药水包
	{
		func = 'jcybao1',
		maxitemcount = 6,
		{ itemid = 301, itemcount = 1 },
		{ itemid = 301, itemcount = 1 },
		{ itemid = 301, itemcount = 1 },
		{ itemid = 301, itemcount = 1 },
		{ itemid = 301, itemcount = 1 },
		{ itemid = 301, itemcount = 1 },

	},
	{
		func = 'jcybao2',
		maxitemcount = 6,
		{ itemid = 302, itemcount = 1 },
		{ itemid = 302, itemcount = 1 },
		{ itemid = 302, itemcount = 1 },
		{ itemid = 302, itemcount = 1 },
		{ itemid = 302, itemcount = 1 },
		{ itemid = 302, itemcount = 1 },

	},
	{
		func = 'jcybao3',
		maxitemcount = 6,
		{ itemid = 303, itemcount = 1 },
		{ itemid = 303, itemcount = 1 },
		{ itemid = 303, itemcount = 1 },
		{ itemid = 303, itemcount = 1 },
		{ itemid = 303, itemcount = 1 },
		{ itemid = 303, itemcount = 1 },
	},
	{
		func = 'jcybao6',
		maxitemcount = 6,
		{ itemid = 306, itemcount = 1 },
		{ itemid = 306, itemcount = 1 },
		{ itemid = 306, itemcount = 1 },
		{ itemid = 306, itemcount = 1 },
		{ itemid = 306, itemcount = 1 },
		{ itemid = 306, itemcount = 1 },

	},
	{
		func = 'jcybao7',
		maxitemcount = 6,
		{ itemid = 307, itemcount = 1 },
		{ itemid = 307, itemcount = 1 },
		{ itemid = 307, itemcount = 1 },
		{ itemid = 307, itemcount = 1 },
		{ itemid = 307, itemcount = 1 },
		{ itemid = 307, itemcount = 1 },

	},
	{
		func = 'jcybao8',
		maxitemcount = 6,
		{ itemid = 308, itemcount = 1 },
		{ itemid = 308, itemcount = 1 },
		{ itemid = 308, itemcount = 1 },
		{ itemid = 308, itemcount = 1 },
		{ itemid = 308, itemcount = 1 },
		{ itemid = 308, itemcount = 1 },
	},
	{
		func = 'mfybao1',
		maxitemcount = 6,
		{ itemid = 321, itemcount = 1 },
		{ itemid = 321, itemcount = 1 },
		{ itemid = 321, itemcount = 1 },
		{ itemid = 321, itemcount = 1 },
		{ itemid = 321, itemcount = 1 },
		{ itemid = 321, itemcount = 1 },

	},
	{
		func = 'mfybao2',
		maxitemcount = 6,
		{ itemid = 322, itemcount = 1 },
		{ itemid = 322, itemcount = 1 },
		{ itemid = 322, itemcount = 1 },
		{ itemid = 322, itemcount = 1 },
		{ itemid = 322, itemcount = 1 },
		{ itemid = 322, itemcount = 1 },

	},
	{
		func = 'mfybao3',
		maxitemcount = 6,
		{ itemid = 323, itemcount = 1 },
		{ itemid = 323, itemcount = 1 },
		{ itemid = 323, itemcount = 1 },
		{ itemid = 323, itemcount = 1 },
		{ itemid = 323, itemcount = 1 },
		{ itemid = 323, itemcount = 1 },

	},
	{
		func = 'mfybao6',
		maxitemcount = 6,
		{ itemid = 326, itemcount = 1 },
		{ itemid = 326, itemcount = 1 },
		{ itemid = 326, itemcount = 1 },
		{ itemid = 326, itemcount = 1 },
		{ itemid = 326, itemcount = 1 },
		{ itemid = 326, itemcount = 1 },

	},
	{
		func = 'mfybao7',
		maxitemcount = 6,
		{ itemid = 327, itemcount = 1 },
		{ itemid = 327, itemcount = 1 },
		{ itemid = 327, itemcount = 1 },
		{ itemid = 327, itemcount = 1 },
		{ itemid = 327, itemcount = 1 },
		{ itemid = 327, itemcount = 1 },

	},
	{
		func = 'mfybao8',
		maxitemcount = 6,
		{ itemid = 328, itemcount = 1 },
		{ itemid = 328, itemcount = 1 },
		{ itemid = 328, itemcount = 1 },
		{ itemid = 328, itemcount = 1 },
		{ itemid = 328, itemcount = 1 },
		{ itemid = 328, itemcount = 1 },

	},
	{
		func = 'tysbao1',
		maxitemcount = 6,
		{ itemid = 351, itemcount = 1 },
		{ itemid = 351, itemcount = 1 },
		{ itemid = 351, itemcount = 1 },
		{ itemid = 351, itemcount = 1 },
		{ itemid = 351, itemcount = 1 },
		{ itemid = 351, itemcount = 1 },

	},
	{
		func = 'tysbao2',
		maxitemcount = 6,
		{ itemid = 352, itemcount = 1 },
		{ itemid = 352, itemcount = 1 },
		{ itemid = 352, itemcount = 1 },
		{ itemid = 352, itemcount = 1 },
		{ itemid = 352, itemcount = 1 },
		{ itemid = 352, itemcount = 1 },

	},
	{
		func = 'lsybao',
		maxitemcount = 6,
		{ itemid = 353, itemcount = 1 },
		{ itemid = 353, itemcount = 1 },
		{ itemid = 353, itemcount = 1 },
		{ itemid = 353, itemcount = 1 },
		{ itemid = 353, itemcount = 1 },
		{ itemid = 353, itemcount = 1 },

	},
	
	{
		func = 'wnxsbao',
		maxitemcount = 6,
		{ itemid = 354, itemcount = 1 },
		{ itemid = 354, itemcount = 1 },
		{ itemid = 354, itemcount = 1 },
		{ itemid = 354, itemcount = 1 },
		{ itemid = 354, itemcount = 1 },
		{ itemid = 354, itemcount = 1 },

	},
		{
		func = 'tysbao6',
		maxitemcount = 6,
		{ itemid = 356, itemcount = 1 },
		{ itemid = 356, itemcount = 1 },
		{ itemid = 356, itemcount = 1 },
		{ itemid = 356, itemcount = 1 },
		{ itemid = 356, itemcount = 1 },
		{ itemid = 356, itemcount = 1 },

	},
	{
		func = 'tysbao7',
		maxitemcount = 6,
		{ itemid = 357, itemcount = 1 },
		{ itemid = 357, itemcount = 1 },
		{ itemid = 357, itemcount = 1 },
		{ itemid = 357, itemcount = 1 },
		{ itemid = 357, itemcount = 1 },
		{ itemid = 357, itemcount = 1 },

	},
	{
		func = 'lsybao2',
		maxitemcount = 6,
		{ itemid = 358, itemcount = 1 },
		{ itemid = 358, itemcount = 1 },
		{ itemid = 358, itemcount = 1 },
		{ itemid = 358, itemcount = 1 },
		{ itemid = 358, itemcount = 1 },
		{ itemid = 358, itemcount = 1 },

	},
	{
		func = 'wnxsbao2',
		maxitemcount = 6,
		{ itemid = 359, itemcount = 1 },
		{ itemid = 359, itemcount = 1 },
		{ itemid = 359, itemcount = 1 },
		{ itemid = 359, itemcount = 1 },
		{ itemid = 359, itemcount = 1 },
		{ itemid = 359, itemcount = 1 },

	},

-----------回城卷包-------------
	{
		func = 'bqhcjb',
		maxitemcount = 6,
		{ itemid = 80001, itemcount = 1 },
		{ itemid = 80001, itemcount = 1 },
		{ itemid = 80001, itemcount = 1 },
		{ itemid = 80001, itemcount = 1 },
		{ itemid = 80001, itemcount = 1 },
		{ itemid = 80001, itemcount = 1 },

	},
	{
		func = 'mzhcjb',
		maxitemcount = 6,
		{ itemid = 80007, itemcount = 1 },
		{ itemid = 80007, itemcount = 1 },
		{ itemid = 80007, itemcount = 1 },
		{ itemid = 80007, itemcount = 1 },
		{ itemid = 80007, itemcount = 1 },
		{ itemid = 80007, itemcount = 1 },

	},
	
	{
		func = 'mlchcjb',
		maxitemcount = 6,
		{ itemid = 80009, itemcount = 1 },
		{ itemid = 80009, itemcount = 1 },
		{ itemid = 80009, itemcount = 1 },
		{ itemid = 80009, itemcount = 1 },
		{ itemid = 80009, itemcount = 1 },
		{ itemid = 80009, itemcount = 1 },

	},
	
	{
		func = 'cydhcjb',
		maxitemcount = 6,
		{ itemid = 80106, itemcount = 1 },
		{ itemid = 80106, itemcount = 1 },
		{ itemid = 80106, itemcount = 1 },
		{ itemid = 80106, itemcount = 1 },
		{ itemid = 80106, itemcount = 1 },
		{ itemid = 80106, itemcount = 1 },

	},
	{
		func = 'sbkhcjb',
		maxitemcount = 6,
		{ itemid = 80008, itemcount = 1 },
		{ itemid = 80008, itemcount = 1 },
		{ itemid = 80008, itemcount = 1 },
		{ itemid = 80008, itemcount = 1 },
		{ itemid = 80008, itemcount = 1 },
		{ itemid = 80008, itemcount = 1 },

	},
	{
		func = 'sjcsjb',
		maxitemcount = 6,
		{ itemid = 80005, itemcount = 1 },
		{ itemid = 80005, itemcount = 1 },
		{ itemid = 80005, itemcount = 1 },
		{ itemid = 80005, itemcount = 1 },
		{ itemid = 80005, itemcount = 1 },
		{ itemid = 80005, itemcount = 1 },

	},


-----------师徒礼包begin-------------
	{
		func = 'OnUseMasterPackage1331501',
		maxitemcount = 2,
		{  exp = 600 },
		{ itemid = 361, itemcount = 1 },
		{ itemid = 371, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1332001',
		maxitemcount = 2,
		{  exp = 1700 },
		{ itemid = 361, itemcount = 1 },
		{ itemid = 371, itemcount = 1 },


	},
	{
		func = 'OnUseMasterPackage1332501',
		maxitemcount = 2,
		{  exp = 4800 },
		{ itemid = 361, itemcount = 1 },
		{ itemid = 371, itemcount = 1 },

	},

	{
		func = 'OnUseMasterPackage1333001',
		maxitemcount = 2,
		{  exp = 8000 },
		{ itemid = 361, itemcount = 1 },
		{ itemid = 371, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1333501',
		maxitemcount = 2,
		{  exp = 10000 },
		{ itemid = 361, itemcount = 1 },
		{ itemid = 371, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1334001',
		maxitemcount = 2,
		{  exp = 10000 },
		{ itemid = 361, itemcount = 1 },
		{ itemid = 371, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1331502',
		maxitemcount = 2,
		{  exp = 800 },
		{ itemid = 362, itemcount = 1 },
		{ itemid = 372, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1332002',
		maxitemcount = 2,
		{  exp = 2300 },
		{ itemid = 362, itemcount = 1 },
		{ itemid = 372, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1332502',
		maxitemcount = 2,
		{  exp = 6200 },
		{ itemid = 362, itemcount = 1 },
		{ itemid = 372, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1333002',
		maxitemcount = 2,
		{  exp = 10400 },
		{ itemid = 362, itemcount = 1 },
		{ itemid = 372, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1333502',
		maxitemcount = 2,
		{  exp = 15000 },
		{ itemid = 362, itemcount = 1 },
		{ itemid = 372, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1334002',
		maxitemcount = 2,
		{  exp = 15000 },
		{ itemid = 362, itemcount = 1 },
		{ itemid = 372, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1331503',
		maxitemcount = 2,
		{  exp = 950 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1332003',
		maxitemcount = 2,
		{  exp = 2800 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1332503',
		maxitemcount = 2,
		{  exp = 7600 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1333003',
		maxitemcount = 2,
		{  exp = 13000 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1333503',
		maxitemcount = 2,
		{  exp = 20000 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1334003',
		maxitemcount = 2,
		{  exp = 20000 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1344501',
		maxitemcount = 1,
		{ exp = 2000 },
		{ itemid = 361, itemcount = 1 },
		{ itemid = 371, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1345001',
		maxitemcount = 1,
		{ exp = 2000 },
		{ itemid = 361, itemcount = 1 },
		{ itemid = 371, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1345501',
		maxitemcount = 1,
		{ exp = 2000 },
		{ itemid = 361, itemcount = 1 },
		{ itemid = 371, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1344502',
		maxitemcount = 1,
		{  exp = 3000 },
		{ itemid = 362, itemcount = 1 },
		{ itemid = 372, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1345002',
		maxitemcount = 1,
		{  exp = 3000 },
		{ itemid = 362, itemcount = 1 },
		{ itemid = 372, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1345502',
		maxitemcount = 1,
		{  exp = 3000 },
		{ itemid = 362, itemcount = 1 },
		{ itemid = 372, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1344503',
		maxitemcount = 1,
		{  exp = 4000 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1345003',
		maxitemcount = 1,
		{  exp = 4000 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },

	},
	{
		func = 'OnUseMasterPackage1345503',
		maxitemcount = 1,
		{  exp = 4000 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },

	},
	{
		func = 'OnUseAddMasterExp1',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_MASTER_EXP, moneyamount = 1 },
	},
	{
		func = 'OnUseAddMasterExp80',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_MASTER_EXP, moneyamount = 80 },
	},

	{
		func = 'Hexin',
		maxitemcount = 3,

		--{ itemid = 1030012, itemcount = 1 },
		{ itemid = 361, itemcount = 1},
		{ itemid = 371, itemcount = 1},

	},

	{
		func = 'Sihailihe',
		maxitemcount = 3,

		--{ itemid = 1030013, itemcount = 1 },
		{ itemid = 362, itemcount = 1},
		{ itemid = 372, itemcount = 1},

	},

	{
		func = 'Longjingongli',
		maxitemcount = 3,

		--{ itemid = 1030014, itemcount = 1 },
		{ itemid = 363, itemcount = 1},
		{ itemid = 373, itemcount = 1},

	},


--增加道义值
	{
		func = 'daoyishujuan1',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 10000 },

	},

	{
		func = 'daoyishujuan2',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 40000 },

	},

	{
		func = 'daoyishujuan3',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 70000 },

	},

	{
		func = 'daoyishujuan4',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 10000 },

	},

	{
		func = 'daoyishujuan5',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 70000 },

	},

	{
		func = 'daoyishujuan6',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 140000 },

	},

	{
		func = 'daoyishujuan7',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 10000 },

	},

	{
		func = 'daoyishujuan8',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 110000 },

	},

	{
		func = 'daoyishujuan9',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 200000 },

	},

	{
		func = 'daoyishujuan10',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 10000 },

	},

	{
		func = 'daoyishujuan11',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 170000 },

	},

	{
		func = 'daoyishujuan12',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 290000 },

	},

	{
		func = 'daoyishujuan13',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 130000 },

	},

	{
		func = 'daoyishujuan14',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 140000 },

	},

	{
		func = 'daoyishujuan15',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 150000 },

	},

	{
		func = 'daoyishujuan16',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 160000 },

	},

	{
		func = 'daoyishujuan17',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 170000 },

	},

	{
		func = 'daoyishujuan18',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 180000 },

	},

	{
		func = 'daoyishujuan19',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 190000 },

	},

	{
		func = 'daoyishujuan20',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 200000 },

	},

	{
		func = 'daoyishujuan21',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 210000 },

	},

	{
		func = 'daoyishujuan22',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 220000 },

	},

	{
		func = 'daoyishujuan23',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 230000 },

	},

	{
		func = 'daoyishujuan24',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 240000 },

	},

	{
		func = 'daoyishujuan25',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 250000 },

	},

	{
		func = 'daoyishujuan26',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 260000 },

	},

	{
		func = 'daoyishujuan27',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 270000 },

	},

	{
		func = 'daoyishujuan28',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 280000 },

	},

	{
		func = 'daoyishujuan29',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 290000 },

	},

	{
		func = 'daoyishujuan30',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 300000 },

	},

	{
		func = 'daoyishujuan31',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 310000 },

	},

	{
		func = 'daoyishujuan32',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 320000 },

	},

	{
		func = 'daoyishujuan33',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 330000 },

	},

	{
		func = 'daoyishujuan34',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 340000 },

	},

	{
		func = 'daoyishujuan35',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 350000 },

	},

	{
		func = 'daoyishujuan36',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 360000 },

	},

	{
		func = 'daoyishujuan37',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 370000 },

	},

	{
		func = 'daoyishujuan38',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 380000 },

	},

	{
		func = 'daoyishujuan39',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 390000 },

	},

	{
		func = 'daoyishujuan40',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 400000 },

	},

	{
		func = 'daoyishujuan41',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 410000 },

	},

	{
		func = 'daoyishujuan42',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 420000 },

	},

	{
		func = 'daoyishujuan43',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 430000 },

	},

	{
		func = 'daoyishujuan44',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 440000 },

	},

	{
		func = 'daoyishujuan45',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 450000 },

	},

	{
		func = 'daoyishujuan46',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 460000 },

	},

	{
		func = 'daoyishujuan47',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 470000 },

	},

	{
		func = 'daoyishujuan48',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 480000 },

	},

	{
		func = 'daoyishujuan49',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 490000 },

	},

	{
		func = 'daoyishujuan50',
		maxitemcount = 0,

		{ moneytype = MONEYTYPE_MORAL, moneyamount = 500000 },

	},



-----------师徒礼包end---------------
	{
		func = 'OnUseQiYuPackage',
		maxitemcount = 3,
		{ itemid = 363, itemcount = 1 },

		{ itemid = 80003, itemcount = 15,percent = 20 },
		{ itemid = 110001, itemcount = 20,percent = 50 },

	},

	{
		func = 'OnUsePackage1200001',
		maxitemcount = 10,
		{ itemid = 10111, itemcount = 1 },
		{ itemid = 10121, itemcount = 1 },
		{ itemid = 10211, itemcount = 1 },
		{ itemid = 10221, itemcount = 1 },
		{ itemid = 10311, itemcount = 1 },
		{ itemid = 10321, itemcount = 1 },
		{ itemid = 10411, itemcount = 1 },
		{ itemid = 10421, itemcount = 1 },
		{ itemid = 10511, itemcount = 1 },
		{ itemid = 10521, itemcount = 1 },
	},

---------------------------活动礼包--------------
	{
		func = 'ceshilihe1',
		maxitemcount = 1,    --包裹需要空格数
		checkvariable = 145, --领取礼包时间所在的变量号
		waittime = 1800,     --需要等待的时间，单位：秒
		{ moneytype = MONEYTYPE_02, moneyamount = 1000 },
		{ itemid = 99980212, itemcount = 1, class = clsWarrior },
		{ itemid = 99990222, itemcount = 1, class = clsMage },
		{ itemid = 99990232, itemcount = 1, class = clsTaoist },

	},
	{
		func = 'ceshilihe2',
		maxitemcount = 1,    --包裹需要空格数
		checkvariable = 146, --领取礼包时间所在的变量号
		waittime = 1800,     --需要等待的时间，单位：秒
		{ moneytype = MONEYTYPE_02, moneyamount = 3000 },
		{ itemid = 99980314, itemcount = 1, class = clsWarrior },
		{ itemid = 99990324, itemcount = 1, class = clsMage },
		{ itemid = 99990334, itemcount = 1, class = clsTaoist },

	},
	{
		func = 'ceshilihe3',
		maxitemcount = 1,    --包裹需要空格数
		checkvariable = 147, --领取礼包时间所在的变量号
		waittime = 1800,     --需要等待的时间，单位：秒
		{ moneytype = MONEYTYPE_02, moneyamount = 5000 },

		{ itemid = 99980413, itemcount = 1, class = clsWarrior },
		{ itemid = 99990423, itemcount = 1, class = clsMage },
		{ itemid = 99990433, itemcount = 1, class = clsTaoist },

	},
	{
		func = 'ceshilihe4',
		maxitemcount = 1,    --包裹需要空格数
		checkvariable = 148, --领取礼包时间所在的变量号
		waittime = 1800,     --需要等待的时间，单位：秒
		{ moneytype = MONEYTYPE_02, moneyamount = 7000 },

		{ itemid = 99980416, itemcount = 1, class = clsWarrior },
		{ itemid = 99990426, itemcount = 1, class = clsMage },
		{ itemid = 99990436, itemcount = 1, class = clsTaoist },

	},
	{
		func = 'ceshilihe5',
		maxitemcount = 1,    --包裹需要空格数
		checkvariable = 149, --领取礼包时间所在的变量号
		waittime = 1800,     --需要等待的时间，单位：秒
		{ moneytype = MONEYTYPE_02, moneyamount = 9000 },

		{ itemid = 99980515, itemcount = 1, class = clsWarrior },
		{ itemid = 99990525, itemcount = 1, class = clsMage },
		{ itemid = 99990535, itemcount = 1, class = clsTaoist },

	},

	{
		func = 'ceshilihe6',
		maxitemcount = 1,    --包裹需要空格数
		checkvariable = 150, --领取礼包时间所在的变量号
		waittime = 1800,     --需要等待的时间，单位：秒
		{ moneytype = MONEYTYPE_02, moneyamount = 11000},

		{ itemid = 99980517, itemcount = 1, class = clsWarrior },
		{ itemid = 99990527, itemcount = 1, class = clsMage },
		{ itemid = 99990537, itemcount = 1, class = clsTaoist },

	},

	{
		func = 'ceshilihe7',
		maxitemcount = 1,    --包裹需要空格数
		checkvariable = 151, --领取礼包时间所在的变量号
		waittime = 1800,     --需要等待的时间，单位：秒
		{ moneytype = MONEYTYPE_02, moneyamount = 13000 },

		{ itemid = 99900030, itemcount = 1, class = clsWarrior },
		{ itemid = 99900028, itemcount = 1, class = clsMage },
		{ itemid = 99900031, itemcount = 1, class = clsTaoist },

	},

	----我爱传奇永恒礼包
	{
		func = 'woaicqyh',
		maxitemcount = 2,    --包裹需要空格数

		{ itemid = 99990315, itemcount = 1 },
		{ itemid = 99990317, itemcount = 1 },

	},

	------------------------公会扶持礼包

	{
		func = 'GongHuiFuChi',
		maxitemcount = 11,    --包裹需要空格数
		opentimesvariable = 208,
		maxopentimes = 1,

		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 80203, itemcount = 1, bind = true },
		{ itemid = 21001, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 21002, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 21003, itemcount = 1, class = clsTaoist, bind = true },

	},

	------------------------属地升级礼包

	{
		func = 'ShuDiShengJi',
		maxitemcount = 16,    --包裹需要空格数
		opentimesvariable = 209,
		maxopentimes = 1,

		{ itemid = 120001, itemcount = 200, bind = true },
		{ itemid = 120002, itemcount = 200, bind = true },
		{ itemid = 120003, itemcount = 200, bind = true },
		{ itemid = 120004, itemcount = 200, bind = true },

	},

	------------------------礼品粽子

	{
		func = 'ZongZi',
		maxitemcount = 1,    --包裹需要空格数
		{	select =
			{

				{ itemid = 2800006,	itemcount = 1, weight = 172543 }, --幸运碎片
				{ itemid = 2201,	itemcount = 1, weight = 172543 }, --千里传音
				{ itemid = 80003,	itemcount = 1, weight = 86271 }, --祝福油
				{ itemid = 383, 	itemcount = 1, weight = 172543 }, --疗伤包
				{ itemid = 1800009, itemcount = 1, weight = 172543  }, --小金币
				{ itemid = 1800011, itemcount = 1, weight = 15686}, --大金币
				{ itemid = 2800052, itemcount = 1, weight = 49298 }, --40J直升丹
				{ itemid = 2800064, itemcount = 1, weight = 28757}, --强化油
				{ itemid = 32535, 	itemcount = 1, weight = 49298}, --魔法盾
				{ itemid = 32537,	itemcount = 1, weight = 34509}, --冰咆哮
				{ itemid = 31036, 	itemcount = 1, weight = 23006}, --烈火剑法
				{ itemid = 33008, 	itemcount = 1, weight = 23006}, --召唤神兽

			},
			announce_expensive = ' {role_name} 从端午节粽子礼包里获得了道具:[item_name]',
		},
	},

	------------------------荣归装备包

	{
		func = 'RongGui1',
		maxitemcount = 6,    --包裹需要空格数

		{ itemid = 69910041, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 69910042, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 69910043, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 69900009, itemcount = 1, bind = true },
		{ itemid = 69910021, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 69910022, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 69910023, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 69910021, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 69910022, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 69910023, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 69910031, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 69910032, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 69910033, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 69910031, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 69910032, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 69910033, itemcount = 1, class = clsTaoist, bind = true },
		{ title = 103 },
		{ aura = 2531 },

	},
	------------------------14天英雄帖礼包

	{
		func = '14YingXiongTie',
		maxitemcount = 6,    --包裹需要空格数

		{ select =
			{
				{itemid = 99920016, itemcount = 1, weight = 1000},
				{itemid = 99920020, itemcount = 1, weight = 1000},
				{itemid = 99920021, itemcount = 1, weight = 1000},
				{itemid = 99930018, itemcount = 1, weight = 1000},
				{itemid = 99930017, itemcount = 1, weight = 1000},
				{itemid = 99930014, itemcount = 1, weight = 1000},
				{itemid = 99940020, itemcount = 1, weight = 1000},
				{itemid = 99940011, itemcount = 1, weight = 1000},
				{itemid = 99940015, itemcount = 1, weight = 1000},
			},
		},
	},

	------------------------风云公会专属礼包

	{
		func = 'FYGHZhuangShu',
		maxitemcount = 6,    --包裹需要空格数
		opentimesvariable = 191,
		maxopentimes = 1,

		{ itemid = 363, itemcount = 1 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },
		{ moneytype = MONEYTYPE_02, moneyamount = 100000 },

	},

	------------------------琅琊公会专属礼包

	{
		func = 'LYGHZhuangShu',
		maxitemcount = 6,    --包裹需要空格数
		opentimesvariable = 192,
		maxopentimes = 1,

		{ itemid = 363, itemcount = 1 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },
		{ moneytype = MONEYTYPE_02, moneyamount = 200000 },

	},

	------------------------媒体礼包

	{
		func = 'MeiTi1',
		maxitemcount = 10,    --包裹需要空格数
		opentimesvariable = 193,
		maxopentimes = 1,

		{ itemid = 363, itemcount = 1 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 363, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },
		{ itemid = 373, itemcount = 1 },
		{ moneytype = MONEYTYPE_02, moneyamount = 50000 },

	},

	------------------------支付宝礼包

	{
		func = 'ZhiFuBao1',
		maxitemcount = 5,    --包裹需要空格数
		opentimesvariable = 199,
		maxopentimes = 1,

		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },

	},

	------------------------CJ活动礼包

	{
		func = 'CJHuoDong1',
		maxitemcount = 6,    --包裹需要空格数
		opentimesvariable = 200,
		maxopentimes = 1,

		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 353, itemcount = 1, bind = true },
		{ itemid = 353, itemcount = 1, bind = true },
		{ itemid = 353, itemcount = 1, bind = true },

	},

	------------------------各种公测的媒体或活动礼包

	{
		func = '173TQGC',
		maxitemcount = 9,

		{ itemid = 388, itemcount = 1, bind = true },
		{ itemid = 388, itemcount = 1, bind = true },
		{ itemid = 388, itemcount = 1, bind = true },
		{ itemid = 388, itemcount = 1, bind = true },
		{ itemid = 388, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 69900008, itemcount = 1, bind = true },

	},

	{
		func = '173ZSGC',
		maxitemcount = 6,

		{ itemid = 388, itemcount = 1, bind = true },
		{ itemid = 388, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 69900007, itemcount = 1, bind = true },

	},

        {
		func = 'GongHuiZhiZun',
		maxitemcount = 19,
		opentimesvariable = 227,
		maxopentimes = 1,

		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 91102, itemcount = 1, bind = true },
		{ itemid = 91102, itemcount = 1, bind = true },
		{ itemid = 91102, itemcount = 1, bind = true },
		{ itemid = 80203, itemcount = 1, bind = true },
		{ itemid = 80201, itemcount = 1, bind = true },
		{ itemid = 80202, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ title = 104 },
	},

        {
		func = 'GongHuiDianCang',
		maxitemcount = 17,
		opentimesvariable = 228,
		maxopentimes = 1,

		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 91102, itemcount = 1, bind = true },
		{ itemid = 91102, itemcount = 1, bind = true },
		{ itemid = 91102, itemcount = 1, bind = true },
		{ itemid = 80203, itemcount = 1, bind = true },
		{ itemid = 80201, itemcount = 1, bind = true },
		{ itemid = 80202, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ title = 105 },
	},

        {
		func = 'DuoWanGC',
		maxitemcount = 12,
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 80203, itemcount = 1, bind = true },
		{ itemid = 80201, itemcount = 1, bind = true },
		{ itemid = 80202, itemcount = 1, bind = true },

	},

        {
		func = 'XinLangGC',
		maxitemcount = 12,
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 80203, itemcount = 1, bind = true },
		{ itemid = 80201, itemcount = 1, bind = true },
		{ itemid = 80202, itemcount = 1, bind = true },

	},

        {
		func = 'MeiTiGC',
		maxitemcount = 7,
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 80201, itemcount = 1, bind = true },

	},

        {
		func = 'ChuanYong',
		maxitemcount = 9,
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 387, itemcount = 1, bind = true },

	},

        {
		func = 'CaiYuanGunGun',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 880000 },

	},

        {
		func = 'LaoDaJieZhi',
		maxitemcount = 1,
		{ itemid = 69900008, itemcount = 1, bind = true },

	},

        {
		func = 'TianLongXiangLian',
		maxitemcount = 1,
		{ itemid = 69900009, itemcount = 1, bind = true },

	},

        {
		func = 'HuaTuoZaiShi',
		maxitemcount = 2,
		{ itemid = 382, itemcount = 1 },
		{ itemid = 383, itemcount = 1 },

	},

	{
		func = 'CanJuanHe',
		maxitemcount = 1,

		{ select =
			{
				{itemid = 90217, itemcount = 1, weight = 2500},
				{itemid = 90218, itemcount = 1, weight = 5000},
				{itemid = 90219, itemcount = 1, weight = 2500},
			}
		},

	},


	------------------------英雄礼包
	{
		func = 'YingXiongBSD',
		maxitemcount = 1,
		{ itemid = 99900025, itemcount = 1, class = clsWarrior },
		{ itemid = 99900028, itemcount = 1, class = clsMage },
		{ itemid = 99900027, itemcount = 1, class = clsTaoist },

	},


	------------------------沃玛号角礼包
	{
		func = 'HaoJiao',
		maxitemcount = 1,
		{ itemid = 80002, itemcount = 1, bind = true },

	},


	------------------问卷礼包

	{
		func = 'wenjuan10',
		maxitemcount = 2,
		opentimesvariable = 153,
		maxopentimes = 1,

		{ moneytype = MONEYTYPE_02, moneyamount = 10000 },
		{ itemid = 361, itemcount = 1 },
		{ itemid = 361, itemcount = 1 },

	},
	{
		func = 'wenjuan20',
		maxitemcount = 2,
		opentimesvariable = 154,
		maxopentimes = 1,

		{ moneytype = MONEYTYPE_02, moneyamount = 20000 },
		{ itemid = 362, itemcount = 1 },
		{ itemid = 362, itemcount = 1 },

	},
	{
		func = 'wenjuan30',
		maxitemcount = 2,
		opentimesvariable = 155,
		maxopentimes = 1,

		{ moneytype = MONEYTYPE_02, moneyamount = 50000 },
		{ itemid = 381, itemcount = 1 },
		{ itemid = 381, itemcount = 1 },

	},

	------------------------问卷礼包，只给钱

	{
		func = 'wenjuan0321',
	--	maxitemcount = 7,    --包裹需要空格数
		opentimesvariable = 157,
		maxopentimes = 1,
		{ moneytype = MONEYTYPE_02, moneyamount = 20000 },

	},


	------------------------成长礼包

	{
		func = 'ZhanShiChengZhangLiBao1',
		maxitemcount = 3,

		{ moneytype = MONEYTYPE_02, moneyamount = 10000 },
		{ itemid = 361, itemcount = 1, bind = true },
		{ itemid = 361, itemcount = 1, bind = true },
		{ itemid = 1380012, itemcount = 1, bind = true },

	},
	{
		func = 'ZhanShiChengZhangLiBao2',
		maxitemcount = 4,

		{ moneytype = MONEYTYPE_02, moneyamount = 20000 },
		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 99900010, itemcount = 1, bind = true },
		{ itemid = 1380013, itemcount = 1, bind = true },

	},
	{
		func = 'ZhanShiChengZhangLiBao3',
		maxitemcount = 5,

		{ moneytype = MONEYTYPE_02, moneyamount = 50000 },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 99980413, itemcount = 1, sex = cstMale, bind = true },
		{ itemid = 99990413, itemcount = 1, sex = cstFemale, bind = true },
		{ itemid = 99930016, itemcount = 1, bind = true },
		{ itemid = 1380014, itemcount = 1, bind = true },

	},
	{
		func = 'ZhanShiChengZhangLiBao4',
		maxitemcount = 8,

		{ moneytype = MONEYTYPE_02, moneyamount = 100000 },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 99900019, itemcount = 1, bind = true },
		{ itemid = 99920016, itemcount = 1, bind = true },
		{ itemid = 21001, itemcount = 10, bind = true },
		{ itemid = 1380015, itemcount = 1, bind = true },

	},
	{
		func = 'ZhanShiChengZhangLiBao5',
		maxitemcount = 12,

		{ moneytype = MONEYTYPE_02, moneyamount = 300000 },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 99930019, itemcount = 1, bind = true },
		{ itemid = 99940012, itemcount = 1, bind = true },
		{ itemid = 21001, itemcount = 20, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 10420, itemcount = 1, bind = true },
		{ itemid = 31034, itemcount = 1, bind = true },

	},

	{
		func = 'FaShiChengZhangLiBao1',
		maxitemcount = 3,

		{ moneytype = MONEYTYPE_02, moneyamount = 10000 },
		{ itemid = 361, itemcount = 1, bind = true },
		{ itemid = 371, itemcount = 1, bind = true },
		{ itemid = 1380022, itemcount = 1, bind = true },

	},
	{
		func = 'FaShiChengZhangLiBao2',
		maxitemcount = 4,

		{ moneytype = MONEYTYPE_02, moneyamount = 20000 },
		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 372, itemcount = 1, bind = true },
		{ itemid = 99900009, itemcount = 1, bind = true },
		{ itemid = 1380023, itemcount = 1, bind = true },

	},
	{
		func = 'FaShiChengZhangLiBao3',
		maxitemcount = 5,

		{ moneytype = MONEYTYPE_02, moneyamount = 50000 },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 99980423, itemcount = 1, sex = cstMale, bind = true },
		{ itemid = 99990423, itemcount = 1, sex = cstFemale, bind = true },
		{ itemid = 99930013, itemcount = 1, bind = true },
		{ itemid = 1380024, itemcount = 1, bind = true },

	},
	{
		func = 'FaShiChengZhangLiBao4',
		maxitemcount = 8,

		{ moneytype = MONEYTYPE_02, moneyamount = 100000 },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 99900018, itemcount = 1, bind = true },
		{ itemid = 99920020, itemcount = 1, bind = true },
		{ itemid = 21002, itemcount = 10, bind = true },
		{ itemid = 1380025, itemcount = 1, bind = true },

	},
	{
		func = 'FaShiChengZhangLiBao5',
		maxitemcount = 12,

		{ moneytype = MONEYTYPE_02, moneyamount = 300000 },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 99930020, itemcount = 1, bind = true },
		{ itemid = 99940016, itemcount = 1, bind = true },
		{ itemid = 21002, itemcount = 20, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 10320, itemcount = 1, bind = true },
		{ itemid = 32546, itemcount = 1, bind = true },

	},
	{
		func = 'DaoShiChengZhangLiBao1',
		maxitemcount = 3,

		{ moneytype = MONEYTYPE_02, moneyamount = 10000 },
		{ itemid = 361, itemcount = 1, bind = true },
		{ itemid = 371, itemcount = 1, bind = true },
		{ itemid = 1380032, itemcount = 1, bind = true },

	},
	{
		func = 'DaoShiChengZhangLiBao2',
		maxitemcount = 4,

		{ moneytype = MONEYTYPE_02, moneyamount = 20000 },
		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 372, itemcount = 1, bind = true },
		{ itemid = 99900011, itemcount = 1, bind = true },
		{ itemid = 1380033, itemcount = 1, bind = true },

	},
	{
		func = 'DaoShiChengZhangLiBao3',
		maxitemcount = 5,

		{ moneytype = MONEYTYPE_02, moneyamount = 50000 },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 99980433, itemcount = 1, sex = cstMale, bind = true },
		{ itemid = 99990433, itemcount = 1, sex = cstFemale, bind = true },
		{ itemid = 99930013, itemcount = 1, bind = true },
		{ itemid = 1380034, itemcount = 1, bind = true },

	},
	{
		func = 'DaoShiChengZhangLiBao4',
		maxitemcount = 8,

		{ moneytype = MONEYTYPE_02, moneyamount = 100000 },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 99900021, itemcount = 1, bind = true },
		{ itemid = 99920021, itemcount = 1, bind = true },
		{ itemid = 21003, itemcount = 10, bind = true },
		{ itemid = 1380035, itemcount = 1, bind = true },

	},
	{
		func = 'DaoShiChengZhangLiBao5',
		maxitemcount = 12,

		{ moneytype = MONEYTYPE_02, moneyamount = 300000 },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 99930021, itemcount = 1, bind = true },
		{ itemid = 99940010, itemcount = 1, bind = true },
		{ itemid = 21003, itemcount = 20, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 10110, itemcount = 1, bind = true },
		{ itemid = 33012, itemcount = 1, bind = true },

	},

	----------------------改版后师父赠送徒弟礼包

	{
		func = 'Lv10HeXin',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 372, itemcount = 1, bind = true },

	},
	{
		func = 'Lv10ZhuFuLiHe',
		maxitemcount = 3,

		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 372, itemcount = 1, bind = true },
		{ itemid = 99990111, itemcount = 1, bind = true },

	},
	{
		func = 'Lv10ChuanShiLiHe',
		maxitemcount = 4,

		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 372, itemcount = 1, bind = true },
		{ itemid = 99990111, itemcount = 1, bind = true },
		{ itemid = 99980213, itemcount = 1, sex = cstMale, bind = true },
		{ itemid = 99990213, itemcount = 1, sex = cstFemale, bind = true },

	},
	{
		func = 'Lv15HeXin',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 372, itemcount = 1, bind = true },

	},
	{
		func = 'Lv15ZhuFuLiHe',
		maxitemcount = 3,

		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 372, itemcount = 1, bind = true },
		{ itemid = 99900010, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 99900009, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 99900011, itemcount = 1, class = clsTaoist, bind = true },

	},
	{
		func = 'Lv15ChuanShiLiHe',
		maxitemcount = 5,

		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 372, itemcount = 1, bind = true },
		{ itemid = 99990211, itemcount = 1, bind = true },
		{ itemid = 99980313, itemcount = 1, sex = cstMale, bind = true },
		{ itemid = 99990313, itemcount = 1, sex = cstFemale, bind = true },
		{ itemid = 99900010, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 99900009, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 99900011, itemcount = 1, class = clsTaoist, bind = true },

	},
	{
		func = 'Lv20HeXin',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 372, itemcount = 1, bind = true },

	},
	{
		func = 'Lv20ZhuFuLiHe',
		maxitemcount = 3,

		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 372, itemcount = 1, bind = true },
		{ itemid = 99900016, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 99900013, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 99900015, itemcount = 1, class = clsTaoist, bind = true },

	},
	{
		func = 'Lv20ChuanShiLiHe',
		maxitemcount = 6,

		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 372, itemcount = 1, bind = true },
		{ itemid = 99900016, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 99900013, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 99900015, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 99920011, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 99920010, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 99920012, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 99930008, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 99930009, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 99930007, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 99940027, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 99940008, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 99940007, itemcount = 1, class = clsTaoist, bind = true },

	},
	{
		func = 'Lv25HeXin',
		maxitemcount = 2,

		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },

	},
	{
		func = 'Lv25ZhuFuLiHe',
		maxitemcount = 3,

		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 99900020, itemcount = 1, bind = true },

	},
	{
		func = 'Lv25ChuanShiLiHe',
		maxitemcount = 5,

		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 99900020, itemcount = 1, bind = true },
		{ itemid = 99930010, itemcount = 1, bind = true },
		{ itemid = 99940009, itemcount = 1, bind = true },
	},


	------------------------签到礼包

	{
		func = 'QianDaoJCY',
		maxitemcount = 2,

		{ itemid = 362, itemcount = 1, bind = true },

	},
	{
		func = 'QianDaoPiFeng',
		maxitemcount = 2,

		{ itemid = 99950003, itemcount = 1 },

	},
	{
		func = 'QianDaoTYS',
		maxitemcount = 1,

		{ itemid = 381, itemcount = 1, bind = true },

	},
	{
		func = 'QianDaoLingShi',
		maxitemcount = 2,

		{ itemid = 10420, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 10320, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 10110, itemcount = 1, class = clsTaoist, bind = true },

	},
	{
		func = 'QianDaoMingWen',
		maxitemcount = 2,
		{ itemid = 21001, itemcount = 5, class = clsWarrior, bind = true },
		{ itemid = 21002, itemcount = 5, class = clsMage, bind = true },
		{ itemid = 21003, itemcount = 5, class = clsTaoist, bind = true },

	},
	{
		func = 'QianDaoHeiTie',
		maxitemcount = 6,
		{ itemid = 114015, itemcount = 1, bind = true },
		{ itemid = 114015, itemcount = 1, bind = true },
		{ itemid = 114015, itemcount = 1, bind = true },
		{ itemid = 114015, itemcount = 1, bind = true },
		{ itemid = 114015, itemcount = 1, bind = true },
	},
	{
		func = 'QianDaoJinBi',
		maxitemcount = 1,
		{ moneytype = MONEYTYPE_02, moneyamount = 100000 },

	},
	{
		func = 'QianDaoShiPin',
		maxitemcount = 5,

		{ itemid = 99920022, itemcount = 1, bind = true },
		{ itemid = 99930025, itemcount = 1, percent = 30, bind = true },
		{ itemid = 99930028, itemcount = 1, percent = 30, bind = true },
		{ itemid = 99930030, itemcount = 1, percent = 10, bind = true },

	},
	{
		func = 'QianDaoJiNeng',
		maxitemcount = 2,

		{ itemid = 31036, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 32535, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 33008, itemcount = 1, class = clsTaoist, bind = true },

	},
	{
		func = 'QianDaoCJJCY',
		maxitemcount = 6,

		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },
		{ itemid = 363, itemcount = 1, bind = true },

	},
	{
		func = 'QianDaoCJMFY',
		maxitemcount = 6,

		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },
		{ itemid = 373, itemcount = 1, bind = true },

	},
	{
		func = 'QianDaoQXTYS',
		maxitemcount = 6,

		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },
		{ itemid = 382, itemcount = 1, bind = true },

	},
	{
		func = 'QianDaoZFY',
		maxitemcount = 4,

		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, bind = true },

	},

	------------------------封测媒体礼包

	{
		func = '17173FC',
		maxitemcount = 3,

		{ moneytype = MONEYTYPE_02, moneyamount = 50000 },
		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 69900001, itemcount = 1, bind = true },

	},
	{
		func = 'XinLangFC',
		maxitemcount = 8,
		maxopentimes = 5,

		--{ moneytype = MONEYTYPE_02, moneyamount = 40000 },
		{ itemid = 1500023, itemcount = 1, bind = true },
		{ itemid = 80203, itemcount = 1, bind = true },
		{ itemid = 80201, itemcount = 1, bind = true },
		{ itemid = 31031, itemcount = 1, bind = true, class = clsWarrior },
		{ itemid = 32531, itemcount = 1, bind = true, class = clsMage },
		{ itemid = 32541, itemcount = 1, bind = true, class = clsMage },
		{ itemid = 33002, itemcount = 1, bind = true, class = clsTaoist },
		{ itemid = 33001, itemcount = 1, bind = true, class = clsTaoist },
	},
	{
		func = 'DuoWanFC',
		maxitemcount = 6,

		{ moneytype = MONEYTYPE_02, moneyamount = 40000 },
		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 69900001, itemcount = 1, bind = true },

	},
	{
		func = 'GongHuiFC',
		maxitemcount = 2,

		{ moneytype = MONEYTYPE_02, moneyamount = 60000 },
		{ itemid = 362, itemcount = 1, bind = true },
		{ itemid = 362, itemcount = 1, bind = true },

	},

	------------------------玛法传说经验礼包

	{
		func = 'MFCSJingYan1',
		maxitemcount = 0,
		{ exp = 3300 },
	},
	{
		func = 'MFCSJingYan2',
		maxitemcount = 0,
		{ exp = 8700 },
	},
	{
		func = 'MFCSJingYan3',
		maxitemcount = 0,
		{ exp = 17000 },
	},
	{
		func = 'MFCSJingYan4',
		maxitemcount = 0,
		{ exp = 63000 },
	},
	{
		func = 'MFCSJingYan5',
		maxitemcount = 0,
		{ exp = 122000 },
	},
	{
		func = 'MFCSJingYan6',
		maxitemcount = 0,
		{ exp = 152000 },
	},
	{
		func = 'MFCSJingYan7',
		maxitemcount = 0,
		{ exp = 204000 },
	},
	{
		func = 'MFCSJingYan8',
		maxitemcount = 0,
		{ exp = 276000 },
	},
	{
		func = 'MFCSJingYan9',
		maxitemcount = 0,
		{ exp = 330000 },
	},
	{
		func = 'MFCSJingYan10',
		maxitemcount = 0,
		{ exp = 410000 },
	},
	{
		func = 'MFCSJingYan11',
		maxitemcount = 0,
		{ exp = 500000 },
	},


	------------------------玛法传说金币礼包

	{
		func = 'MFCSJinBi1',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 3000 },
	},
	{
		func = 'MFCSJinBi2',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 8000 },
	},
	{
		func = 'MFCSJinBi3',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 15000 },
	},
	{
		func = 'MFCSJinBi4',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 25000 },
	},
	{
		func = 'MFCSJinBi5',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 40000 },
	},
	{
		func = 'MFCSJinBi6',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 50000 },
	},
	{
		func = 'MFCSJinBi7',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 70000 },
	},
	{
		func = 'MFCSJinBi8',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 100000 },
	},
	{
		func = 'MFCSJinBi9',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 110000 },
	},
	{
		func = 'MFCSJinBi10',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 135000 },
	},
	{
		func = 'MFCSJinBi11',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 160000 },
	},


	------------------------皇室宝库

	{
		func = 'HuangShiBaoXiang',
		maxitemcount = 2,

		{ select =
			{
				{itemid = 99900019, itemcount = 1, weight = 50   },  -- 
				{itemid = 99900018, itemcount = 1, weight = 50   },  -- 
				{itemid = 99900021, itemcount = 1, weight = 50   },  -- 
				{itemid = 99920016, itemcount = 1, weight = 50   },  -- 
				{itemid = 99920020, itemcount = 1, weight = 50   },  -- 
				{itemid = 99920021, itemcount = 1, weight = 50   },  -- 
				{itemid = 99930018, itemcount = 1, weight = 50   },  -- 
				{itemid = 99930017, itemcount = 1, weight = 50   },  -- 
				{itemid = 99930014, itemcount = 1, weight = 50   },  -- 
				{itemid = 99940020, itemcount = 1, weight = 50   },  -- 
				{itemid = 99940011, itemcount = 1, weight = 50   },  -- 
				{itemid = 99940015, itemcount = 1, weight = 50   },  -- 
				{itemid = 99990315, itemcount = 1, weight = 200  },  -- 
				{itemid = 99990317, itemcount = 1, weight = 200  },  -- 
				{itemid = 99990415, itemcount = 1, weight = 20   },  -- 
				{itemid = 99990417, itemcount = 1, weight = 20   },  -- 
				{itemid = 80003,    itemcount = 1, weight = 300  },  -- 
				{itemid = 303,      itemcount = 1, weight = 2500 },  -- 
				{itemid = 323,      itemcount = 1, weight = 2500 },  -- 
				{itemid = 352,      itemcount = 1, weight = 3550 },  -- 
				{itemid = 99990312, itemcount = 1, weight = 50   },  -- 
				{itemid = 99990322, itemcount = 1, weight = 50   },  -- 
				{itemid = 99990332, itemcount = 1, weight = 50   },  -- 

			},

			announce_expensive = ' {role_name} 从皇室宝箱里获得了道具:[item_name]',
		},
		{itemid = 2800166, itemcount = 5},
	},


	------------------------1级灵石盒

	{
		func = 'LingShiHe1',
		maxitemcount = 1,

		{ select =
			{
				{itemid = 10110, itemcount = 1, weight = 50},
				{itemid = 10120, itemcount = 1, weight = 50},
				{itemid = 10220, itemcount = 1, weight = 50},
				{itemid = 10320, itemcount = 1, weight = 50},
				{itemid = 10420, itemcount = 1, weight = 50},
				{itemid = 10520, itemcount = 1, weight = 50},
			}
		},

	},

	------------------------2级灵石盒

	{
		func = 'LingShiHe2',
		maxitemcount = 1,

		{ select =
			{
				{itemid = 10111, itemcount = 1, weight = 50},
				{itemid = 10121, itemcount = 1, weight = 50},
				{itemid = 10221, itemcount = 1, weight = 50},
				{itemid = 10321, itemcount = 1, weight = 50},
				{itemid = 10421, itemcount = 1, weight = 50},
				{itemid = 10521, itemcount = 1, weight = 50},
			}
		},

	},

	{
		func = 'DecPKValue10',
		maxitemcount = 0,
		{ pkvalue = 10 },
	},
	{
		func = 'DecPKValue50',
		maxitemcount = 0,
		{ pkvalue = 50 },
	},
	{
		func = 'DecPKValue200',
		maxitemcount = 0,
		{ pkvalue = 200 },
	},
	{
		func = 'RouGanDecPKValue',
		maxitemcount = 0,
		{ pkvalue = 5, chance = 50 },
	},

	------------------------备用礼包

	{
		func = 'GongHuiBY',
		maxitemcount = 0,
		{ exp = 300 },

	},
	{
		func = 'GanEnBY',
		maxitemcount = 0,
		{ exp = 300 },

	},
	{
		func = 'BuChangBY',
		maxitemcount = 2,    --包裹需要空格数
		{ title = 1 },
		{itemid = 1800018, itemcount = 1,bind = true },
		{itemid = 80205, itemcount = 1,bind = true },
	},
	{
		func = 'YaoShuiBY',
		maxitemcount = 0,
		{ exp = 300 },

	},
	{
		func = 'ZhuangBeiBY',
		maxitemcount = 0,
		{ exp = 300 },

	},
	{
		func = 'JingYanBY',
		maxitemcount = 0,
		{ exp = 300 },

	},
	{
		func = 'ShenMiBY',
		maxitemcount = 0,
		{ exp = 300 },

	},
	{
		func = 'JingXiBY',
		maxitemcount = 0,
		{ exp = 300 },

	},

	------------------------烟花和蛋糕
	{
		func = 'FireWorksCake',
		maxitemcount = 0,
		{ doodadid = 3479},
		{ announce = '{role_name}豪掷蛋糕烟花为大家送上祝福！'},
	},

		{
		func = 'FireWorks1',
		maxitemcount = 0,
		{ doodadid = 3480},
	},

	------------------------签到礼包
	------------------------中红包
	{
		func = 'QianDao1',
		maxitemcount = 3,
		{ itemid = 367, itemcount = 1, bind = true },
		{ itemid = 367, itemcount = 1, bind = true },
		{ itemid = 367, itemcount = 1, bind = true },
	},

	------------------------中蓝包
	{
		func = 'QianDao4',
		maxitemcount = 3,
		{ itemid = 377, itemcount = 1, bind = true },
		{ itemid = 377, itemcount = 1, bind = true },
		{ itemid = 377, itemcount = 1, bind = true },
	},

	------------------------神秘礼包
	{
		func = 'QianDao5',
		maxitemcount = 10,
		{itemid = 80003, itemcount = 1, percent = 2, bind = true},
		{itemid = 21001, itemcount = 1, percent = 5, class = clsWarrior, bind = true },
		{itemid = 21002, itemcount = 1, percent = 5, class = clsMage, bind = true },
		{itemid = 21003, itemcount = 1, percent = 5, class = clsTaoist, bind = true },
		{itemid = 2212, itemcount = 5, percent = 10, bind = true},
		{itemid = 2201, itemcount = 3, percent = 5, bind = true},
		{itemid = 705, itemcount = 1, percent = 10, bind = true},
		{itemid = 80203, itemcount = 1, percent = 3, bind = true},
		{itemid = 114020, itemcount = 1, percent = 10, bind = true},
		{itemid = 387, itemcount = 1, percent = 100, bind = true},
		{itemid = 701, itemcount = 1, percent = 10, class = clsWarrior, bind = true},
		{itemid = 702, itemcount = 1, percent = 10, class = clsMage, bind = true},
		{itemid = 703, itemcount = 1, percent = 10, class = clsTaoist, bind = true},

	},

	------------------------太阳水包
	{
		func = 'QianDao6',
		maxitemcount = 3,
		{ itemid = 386, itemcount = 1, bind = true },
		{ itemid = 386, itemcount = 1, bind = true },
		{ itemid = 386, itemcount = 1, bind = true },
	},

	------------------------挖矿包
	{
		func = 'QianDao7',
		maxitemcount = 2,
		{ itemid = 99900041, itemcount = 1, bind = true },
		{ itemid = 99900040, itemcount = 1, bind = true },

	},

	------------------------神水
	{
		func = 'QianDao8',
		maxitemcount = 1,
		{ itemid = 701, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 702, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 703, itemcount = 1, class = clsTaoist, bind = true },

	},

	------------------------大红包
	{
		func = 'QianDao10',
		maxitemcount = 3,
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
		{ itemid = 368, itemcount = 1, bind = true },
	},

	------------------------大蓝包
	{
		func = 'QianDao11',
		maxitemcount = 3,
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
		{ itemid = 378, itemcount = 1, bind = true },
	},

	------------------------神水包
	{
		func = 'QianDao13',
		maxitemcount = 2,
		{ itemid = 705, itemcount = 1, bind = true },
		{ itemid = 706, itemcount = 1, bind = true },
	},

	------------------------铭文石
	{
		func = 'QianDao22',
		maxitemcount = 1,
		{ itemid = 21001, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 21002, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 21003, itemcount = 1, class = clsTaoist, bind = true },

	},

	------------------------黑铁矿石
	{
		func = 'QianDao24',
		maxitemcount = 5,
		{ itemid = 114015, itemcount = 1, bind = true },
		{ itemid = 114015, itemcount = 1, bind = true },
		{ itemid = 114015, itemcount = 1, bind = true },
		{ itemid = 114015, itemcount = 1, bind = true },
		{ itemid = 114015, itemcount = 1, bind = true },
	},


	------------------------签到礼包附录
	------------------------金币包
	{
		func = 'QianDao50',
		maxitemcount = 0,
		{ moneytype = MONEYTYPE_02, moneyamount = 10000 },
	},


	------------------------佣兵灵匣
	{
		func = 'YongBingLingXia',
		maxitemcount = 0,
		{ exp = 10000 },
	},


------------------------活跃礼包
	{
		func = 'HuoYue1',
		maxitemcount = 2,
		{ itemid = 386, itemcount = 1, bind = true },
		{ itemid = 99900042, itemcount = 1 },
	},
	{
		func = 'HuoYue2',
		maxitemcount = 2,
		{ itemid = 386, itemcount = 1, bind = true },
		{ itemid = 99900042, itemcount = 1 },
	},
	{
		func = 'HuoYue3',
		maxitemcount = 3,
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 99900042, itemcount = 1 },
		{ select =
			{
				{itemid = 111006, itemcount = 1, weight = 50},
				{itemid = 111009, itemcount = 1, weight = 50},
			}, percent = 50
		},
	},
	{
		func = 'HuoYue4',
		maxitemcount = 3,
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 99900042, itemcount = 1 },
		{ select =
			{
				{itemid = 111006, itemcount = 1, weight = 50},
				{itemid = 111009, itemcount = 1, weight = 50},
			}, percent = 50
		},
	},
	{
		func = 'HuoYue5',
		maxitemcount = 3,
		{ itemid = 387, itemcount = 1, bind = true },
		{ itemid = 80003, itemcount = 1, percent = 5 },
		{ select =
			{
				{itemid = 21001, itemcount = 1, weight = 50},
				{itemid = 21002, itemcount = 1, weight = 50},
				{itemid = 21003, itemcount = 1, weight = 50},
			}, percent = 15
		},
		{ select =
			{
				{itemid = 111006, itemcount = 1, weight = 50},
				{itemid = 111009, itemcount = 1, weight = 50},
			}, percent = 50
		},
	},
	
	-----by.xxp----增加了商城礼包
	{
		func = 'MingWenStone',
		maxitemcount = 1,
		{itemid = 21001, itemcount = 1, class = clsWarrior},
		{itemid = 21002, itemcount = 2, class = clsMage},
		{itemid = 21003, itemcount = 2, class = clsTaoist},

	},
	{
		func = 'BlackIron',
		maxitemcount = 5,
		{ select =
			{
				{itemid = 114003, itemcount = 1, weight = 100},
				{itemid = 114004, itemcount = 1, weight = 200},
				{itemid = 114005, itemcount = 1, weight = 200},
				{itemid = 114006, itemcount = 1, weight = 200},
				{itemid = 114007, itemcount = 1, weight = 300},
				{itemid = 114008, itemcount = 1, weight = 300},
				{itemid = 114009, itemcount = 1, weight = 300},
				{itemid = 114010, itemcount = 1, weight = 300},
				{itemid = 114011, itemcount = 1, weight = 300},
				{itemid = 114012, itemcount = 1, weight = 400},
				{itemid = 114013, itemcount = 1, weight = 400},
				{itemid = 114014, itemcount = 1, weight = 500},
				{itemid = 114015, itemcount = 1, weight = 500},
				{itemid = 114016, itemcount = 1, weight = 500},
				{itemid = 114017, itemcount = 1, weight = 1000},
				{itemid = 114018, itemcount = 1, weight = 1500},
				{itemid = 114019, itemcount = 1, weight = 1000},
				{itemid = 114020, itemcount = 1, weight = 500},
				{itemid = 114021, itemcount = 1, weight = 400},
				{itemid = 114022, itemcount = 1, weight = 300},
				{itemid = 114023, itemcount = 1, weight = 300},
				{itemid = 114024, itemcount = 1, weight = 200},
				{itemid = 114025, itemcount = 1, weight = 200},
				{itemid = 114026, itemcount = 1, weight = 100},
			},
		},
		{ select =
			{
				{itemid = 114003, itemcount = 1, weight = 100},
				{itemid = 114004, itemcount = 1, weight = 200},
				{itemid = 114005, itemcount = 1, weight = 200},
				{itemid = 114006, itemcount = 1, weight = 200},
				{itemid = 114007, itemcount = 1, weight = 300},
				{itemid = 114008, itemcount = 1, weight = 300},
				{itemid = 114009, itemcount = 1, weight = 300},
				{itemid = 114010, itemcount = 1, weight = 300},
				{itemid = 114011, itemcount = 1, weight = 300},
				{itemid = 114012, itemcount = 1, weight = 400},
				{itemid = 114013, itemcount = 1, weight = 400},
				{itemid = 114014, itemcount = 1, weight = 500},
				{itemid = 114015, itemcount = 1, weight = 500},
				{itemid = 114016, itemcount = 1, weight = 500},
				{itemid = 114017, itemcount = 1, weight = 1000},
				{itemid = 114018, itemcount = 1, weight = 1500},
				{itemid = 114019, itemcount = 1, weight = 1000},
				{itemid = 114020, itemcount = 1, weight = 500},
				{itemid = 114021, itemcount = 1, weight = 400},
				{itemid = 114022, itemcount = 1, weight = 300},
				{itemid = 114023, itemcount = 1, weight = 300},
				{itemid = 114024, itemcount = 1, weight = 200},
				{itemid = 114025, itemcount = 1, weight = 200},
				{itemid = 114026, itemcount = 1, weight = 100},
			},
		},
		{ select =
			{
				{itemid = 114003, itemcount = 1, weight = 100},
				{itemid = 114004, itemcount = 1, weight = 200},
				{itemid = 114005, itemcount = 1, weight = 200},
				{itemid = 114006, itemcount = 1, weight = 200},
				{itemid = 114007, itemcount = 1, weight = 300},
				{itemid = 114008, itemcount = 1, weight = 300},
				{itemid = 114009, itemcount = 1, weight = 300},
				{itemid = 114010, itemcount = 1, weight = 300},
				{itemid = 114011, itemcount = 1, weight = 300},
				{itemid = 114012, itemcount = 1, weight = 400},
				{itemid = 114013, itemcount = 1, weight = 400},
				{itemid = 114014, itemcount = 1, weight = 500},
				{itemid = 114015, itemcount = 1, weight = 500},
				{itemid = 114016, itemcount = 1, weight = 500},
				{itemid = 114017, itemcount = 1, weight = 1000},
				{itemid = 114018, itemcount = 1, weight = 1500},
				{itemid = 114019, itemcount = 1, weight = 1000},
				{itemid = 114020, itemcount = 1, weight = 500},
				{itemid = 114021, itemcount = 1, weight = 400},
				{itemid = 114022, itemcount = 1, weight = 300},
				{itemid = 114023, itemcount = 1, weight = 300},
				{itemid = 114024, itemcount = 1, weight = 200},
				{itemid = 114025, itemcount = 1, weight = 200},
				{itemid = 114026, itemcount = 1, weight = 100},
			},
		},
		{ select =
			{
				{itemid = 114003, itemcount = 1, weight = 100},
				{itemid = 114004, itemcount = 1, weight = 200},
				{itemid = 114005, itemcount = 1, weight = 200},
				{itemid = 114006, itemcount = 1, weight = 200},
				{itemid = 114007, itemcount = 1, weight = 300},
				{itemid = 114008, itemcount = 1, weight = 300},
				{itemid = 114009, itemcount = 1, weight = 300},
				{itemid = 114010, itemcount = 1, weight = 300},
				{itemid = 114011, itemcount = 1, weight = 300},
				{itemid = 114012, itemcount = 1, weight = 400},
				{itemid = 114013, itemcount = 1, weight = 400},
				{itemid = 114014, itemcount = 1, weight = 500},
				{itemid = 114015, itemcount = 1, weight = 500},
				{itemid = 114016, itemcount = 1, weight = 500},
				{itemid = 114017, itemcount = 1, weight = 1000},
				{itemid = 114018, itemcount = 1, weight = 1500},
				{itemid = 114019, itemcount = 1, weight = 1000},
				{itemid = 114020, itemcount = 1, weight = 500},
				{itemid = 114021, itemcount = 1, weight = 400},
				{itemid = 114022, itemcount = 1, weight = 300},
				{itemid = 114023, itemcount = 1, weight = 300},
				{itemid = 114024, itemcount = 1, weight = 200},
				{itemid = 114025, itemcount = 1, weight = 200},
				{itemid = 114026, itemcount = 1, weight = 100},
			}, percent = 50
		},
		{ select =
			{
				{itemid = 114003, itemcount = 1, weight = 100},
				{itemid = 114004, itemcount = 1, weight = 200},
				{itemid = 114005, itemcount = 1, weight = 200},
				{itemid = 114006, itemcount = 1, weight = 200},
				{itemid = 114007, itemcount = 1, weight = 300},
				{itemid = 114008, itemcount = 1, weight = 300},
				{itemid = 114009, itemcount = 1, weight = 300},
				{itemid = 114010, itemcount = 1, weight = 300},
				{itemid = 114011, itemcount = 1, weight = 300},
				{itemid = 114012, itemcount = 1, weight = 400},
				{itemid = 114013, itemcount = 1, weight = 400},
				{itemid = 114014, itemcount = 1, weight = 500},
				{itemid = 114015, itemcount = 1, weight = 500},
				{itemid = 114016, itemcount = 1, weight = 500},
				{itemid = 114017, itemcount = 1, weight = 1000},
				{itemid = 114018, itemcount = 1, weight = 1500},
				{itemid = 114019, itemcount = 1, weight = 1000},
				{itemid = 114020, itemcount = 1, weight = 500},
				{itemid = 114021, itemcount = 1, weight = 400},
				{itemid = 114022, itemcount = 1, weight = 300},
				{itemid = 114023, itemcount = 1, weight = 300},
				{itemid = 114024, itemcount = 1, weight = 200},
				{itemid = 114025, itemcount = 1, weight = 200},
				{itemid = 114026, itemcount = 1, weight = 100},
			},percent = 50
		},
	},
	{
		func = 'GuildItem',
		maxitemcount = 4,
		{itemid = 120001, itemcount = 10},
		{itemid = 120002, itemcount = 10},
		{itemid = 120003, itemcount = 10},
		{itemid = 120004, itemcount = 10},
	},
	{
		func = 'XinRenChengZhang7',
		maxitemcount = 6,
		{itemid = 1800005, itemcount = 1, bind = true },
		{itemid = 99900003, itemcount = 1, bind = true },
		{ itemid = 366, itemcount = 2, bind = true },
		{ itemid = 376, itemcount = 2, bind = true },
		{ itemid = 31031, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 32531, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 33002, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 33001, itemcount = 1, class = clsTaoist, bind = true },
	

	},
	{
		func = 'XinRenChengZhang17',
		maxitemcount = 10,
		{itemid = 1800006, itemcount = 1, bind = true },
		{ itemid = 367, itemcount = 2, bind = true },
		{ itemid = 377, itemcount = 2, bind = true },
		{ itemid = 99980213, itemcount = 1, sex = cstMale, bind = true },
		{ itemid = 99990213, itemcount = 1, sex = cstFemale, bind = true },
		{ itemid = 99900010, itemcount = 1, class = clsWarrior, bind = true },		
		{ itemid = 31032, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 99900009, itemcount = 1, class = clsMage, bind = true },		
		{ itemid = 32531, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 32544, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 32541, itemcount = 1, class = clsMage, bind = true },		
		{ itemid = 99900011, itemcount = 1, class = clsTaoist, bind = true },	
		{ itemid = 33004, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 33005, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 33003, itemcount = 1, class = clsTaoist, bind = true },
	},
	{
		func = 'XinRenChengZhang22',
		maxitemcount = 10,
		{ itemid = 368, itemcount = 2, bind = true },
		{ itemid = 378, itemcount = 2, bind = true },
		{ itemid = 99980313, itemcount = 1, sex = cstMale, bind = true },
		{ itemid = 99990313, itemcount = 1, sex = cstFemale, bind = true },
		{ itemid = 99900016, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 31033, itemcount = 1, class = clsWarrior, bind = true },
		{ itemid = 99900013, itemcount = 1, class = clsMage, bind = true },		
		{ itemid = 32545, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 32533, itemcount = 1, class = clsMage, bind = true },
		{ itemid = 99900015, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 33009, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 33014, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 33006, itemcount = 1, class = clsTaoist, bind = true },
		{ itemid = 33007, itemcount = 1, class = clsTaoist, bind = true },
	},

------------------------VIP充值
	{
		func = 'VIPChongZhi',
		maxitemcount = 8,

		{ itemid = 1800019, itemcount = 1, bind = true  },		--500W经验丹
		{ itemid = 1800016, itemcount = 1, bind = true  },			--直升丹
		-----------------------战士----------------
		{ itemid = 21001, itemcount = 5, class = clsWarrior, bind = true },------战士铭文
		{ itemid = 99900019, itemcount = 1, class = clsWarrior, bind = true },------战士武器
		{ itemid = 99980413, itemcount = 1, class = clsWarrior,sex = cstMale, bind = true },------男战士衣服
		{ itemid = 99990413, itemcount = 1, class = clsWarrior,sex = cstFemale, bind = true },------女战士衣服
		{ itemid = 99920016, itemcount = 1, class = clsWarrior, bind = true },------战士首饰
		{ itemid = 99930018, itemcount = 1, class = clsWarrior, bind = true },------战士首饰
		{ itemid = 99940020, itemcount = 1, class = clsWarrior, bind = true },------战士首饰
		{ itemid = 99930018, itemcount = 1, class = clsWarrior, bind = true },------战士首饰
		{ itemid = 99940020, itemcount = 1, class = clsWarrior, bind = true },------战士首饰
		-----------------------法师----------------
		{ itemid = 21002, itemcount = 5, class = clsMage, bind = true },
		{ itemid = 99900018, itemcount = 1, class = clsMage, bind = true },------法师武器
		{ itemid = 99980423, itemcount = 1, class = clsMage,sex = cstMale, bind = true },------男法师衣服
		{ itemid = 99990423, itemcount = 1, class = clsMage,sex = cstFemale, bind = true },------女法师衣服
		{ itemid = 99920020, itemcount = 1, class = clsMage, bind = true },------法师首饰
		{ itemid = 99930017, itemcount = 1, class = clsMage, bind = true },------法师首饰
		{ itemid = 99940011, itemcount = 1, class = clsMage, bind = true },------法师首饰
		{ itemid = 99930017, itemcount = 1, class = clsMage, bind = true },------法师首饰
		{ itemid = 99940011, itemcount = 1, class = clsMage, bind = true },------法师首饰
		-----------------------道士----------------
		{ itemid = 21003, itemcount = 5, class = clsTaoist, bind = true },
		{ itemid = 99900021, itemcount = 1, class = clsTaoist, bind = true },------道士武器
		{ itemid = 99980433, itemcount = 1, class = clsTaoist,sex = cstMale, bind = true },------男道士衣服
		{ itemid = 99990433, itemcount = 1, class = clsTaoist,sex = cstFemale, bind = true },------女道士衣服
		{ itemid = 99920021, itemcount = 1, class = clsTaoist, bind = true },------道士首饰
		{ itemid = 99930014, itemcount = 1, class = clsTaoist, bind = true },------道士首饰
		{ itemid = 99940015, itemcount = 1, class = clsTaoist, bind = true },------道士首饰
		{ itemid = 99930014, itemcount = 1, class = clsTaoist, bind = true },------道士首饰
		{ itemid = 99940015, itemcount = 1, class = clsTaoist, bind = true },------道士首饰
	},
	{
		func = 'woma_first',--沃玛首杀宝箱
		maxitemcount = 2,
		{itemid = 2800101, itemcount = 1,bind = true},
		{itemid = 2800077, itemcount = 2,bind = true},
	},
	
	{
		func = 'chulongshen_first',--触龙神首杀宝箱
		maxitemcount = 2,
		{itemid = 2800101, itemcount = 1,bind = true},
		{itemid = 2800077, itemcount = 5,bind = true},
	},
	
	{
		func = 'zuma_first',--祖玛首杀宝箱
		maxitemcount = 2,
		{itemid = 2800101, itemcount = 1,bind = true},
		{itemid = 2800077, itemcount = 10,bind = true},
	},
	{
		func = 'hongmo_first',--虹魔首杀宝箱
		maxitemcount = 2,
		{itemid = 2800101, itemcount = 1,bind = true},
		{itemid = 2800077, itemcount = 5,bind = true},
	},
	{
		func = 'lieyan_first',--烈焰恶魔首杀宝箱
		maxitemcount = 2,
		{itemid = 2800101, itemcount = 1,bind = true},
		{itemid = 2800077, itemcount = 20,bind = true},
	},
	
	{
		func = 'anyue_first',--暗月妖王首杀宝箱
		maxitemcount = 1,
			{ select =
			{
				{itemid = 99900025, itemcount = 1,weight = 10},
				{itemid = 99900027, itemcount = 1,weight = 45},
				{itemid = 99900028, itemcount = 1,weight = 45},
			},
		},
	},
	
	
	{
		func = 'suipian_1',--碎片宝箱鞋子腰带
		maxitemcount = 1,
			{ select =
			{
				{itemid = 2800172, itemcount = 1,weight = 10},
				{itemid = 2800173, itemcount = 1,weight = 10},
	
			},
		},
	},
	
	{
		func = 'suipian_2',--碎片宝箱披风
		maxitemcount = 1,
			{ select =
			{
				{itemid = 2800177, itemcount = 1,weight = 10},
				{itemid = 2800178, itemcount = 1,weight = 10},
				{itemid = 2800179, itemcount = 1,weight = 10},
			},
		},
	},
	
	
	{
		func = 'fudai_xinnian',--新年福袋
		maxitemcount = 1,
		{itemid = 2800357, itemcount = 1,bind = false},
	},
	
	{
		func = 'chiyue_first',--赤月首杀宝箱
		maxitemcount = 2,
		{itemid = 2800101, itemcount = 1,bind = true},
		{itemid = 2800077, itemcount = 20,bind = true},
	},
	{
		func = 'langwang_first',--狼王首杀宝箱
		maxitemcount = 2,
		{itemid = 2800101, itemcount = 1,bind = true},
		{itemid = 2800077, itemcount = 1,bind = true},
	},
	{
		func = 'shiwang_first',--尸王首杀宝箱
		maxitemcount = 2,
		{itemid = 2800101, itemcount = 1,bind = true},
		{itemid = 2800077, itemcount = 2,bind = true},
	},

	{
		func = 'Huguo_wq',
		maxitemcount = 1,
		{ select =
			{
				{itemid = 99900022, itemcount = 1, weight = 60},
				{itemid = 99900023, itemcount = 1, weight = 60},
				{itemid = 99900024, itemcount = 1, weight = 60},
				{itemid = 99900032, itemcount = 1, weight = 30},
				{itemid = 99900033, itemcount = 1, weight = 30},
				{itemid = 99900031, itemcount = 1, weight = 30},
				{itemid = 69910071, itemcount = 1, weight = 10},
				{itemid = 69910072, itemcount = 1, weight = 10},
				{itemid = 69910073, itemcount = 1, weight = 10},
			},
		},
	},
	{
		func = 'Huguo_yf',
		maxitemcount = 1,
		{ select =
			{
				{itemid = 99980513, itemcount = 1, weight = 60},
				{itemid = 99990513, itemcount = 1, weight = 60},
				{itemid = 99980523, itemcount = 1, weight = 60},
				{itemid = 99990523, itemcount = 1, weight = 60},
				{itemid = 99980533, itemcount = 1, weight = 60},
				{itemid = 99990533, itemcount = 1, weight = 60},
				{itemid = 99980613, itemcount = 1, weight = 30},
				{itemid = 99990613, itemcount = 1, weight = 30},
				{itemid = 99980623, itemcount = 1, weight = 30},
				{itemid = 99990623, itemcount = 1, weight = 30},
				{itemid = 99980633, itemcount = 1, weight = 30},
				{itemid = 99990633, itemcount = 1, weight = 30},
				{itemid = 99980713, itemcount = 1, weight = 10},
				{itemid = 99990713, itemcount = 1, weight = 10},
				{itemid = 99980723, itemcount = 1, weight = 10},
				{itemid = 99990723, itemcount = 1, weight = 10},
				{itemid = 99980733, itemcount = 1, weight = 10},
				{itemid = 99990733, itemcount = 1, weight = 10},
			}, 
		},
	},

	{
		func = 'Huguo_ss',
		maxitemcount = 1,
		{ select =
			{
				{itemid = 99920017, itemcount = 1, weight = 60},
				{itemid = 99930019, itemcount = 1, weight = 60},
				{itemid = 99940012, itemcount = 1, weight = 60},
				{itemid = 99920019, itemcount = 1, weight = 60},
				{itemid = 99930020, itemcount = 1, weight = 60},
				{itemid = 99940016, itemcount = 1, weight = 60},
				{itemid = 99920018, itemcount = 1, weight = 60},
				{itemid = 99930021, itemcount = 1, weight = 60},
				{itemid = 99940010, itemcount = 1, weight = 60},
				{itemid = 99920027, itemcount = 1, weight = 30},
				{itemid = 99920028, itemcount = 1, weight = 30},
				{itemid = 99920029, itemcount = 1, weight = 30},
				{itemid = 99940024, itemcount = 1, weight = 30},
				{itemid = 99940025, itemcount = 1, weight = 30},
				{itemid = 99940026, itemcount = 1, weight = 30},
				{itemid = 99930033, itemcount = 1, weight = 30},
				{itemid = 99930034, itemcount = 1, weight = 30},
				{itemid = 99930035, itemcount = 1, weight = 30},
				{itemid = 99920032, itemcount = 1, weight = 10},
				{itemid = 99920033, itemcount = 1, weight = 10},
				{itemid = 99920034, itemcount = 1, weight = 10},
				{itemid = 99930038, itemcount = 1, weight = 10},
				{itemid = 99930039, itemcount = 1, weight = 10},
				{itemid = 99930040, itemcount = 1, weight = 10},
				{itemid = 99940030, itemcount = 1, weight = 10},
				{itemid = 99940031, itemcount = 1, weight = 10},
				{itemid = 99940032, itemcount = 1, weight = 10},
			},
		},
	},
	
	{
		func = 'xingyun_lihe1',
		maxitemcount = 2,
		{ itemid = 80003, itemcount = 1200,  bind = false },
		{ itemid = 2800134, itemcount = 1,  bind = false },
	},
	{
		func = 'xingyun_lihe2',
		maxitemcount = 2,
		{ itemid = 80003, itemcount = 2500,  bind = false },
		{ itemid = 2800135, itemcount = 1, bind = false },
	},
	{
		func = 'xingyun_lihe3',
		maxitemcount = 3,
		{ itemid = 80003, itemcount = 5000,  bind = false },
		{ itemid = 2800134, itemcount = 1,  bind = false },
		{ itemid = 2800135, itemcount = 1,  bind = false },
	},
	{
		func = 'xingyun_lihe4',
		maxitemcount = 1,
		{ itemid = 80003, itemcount = 6000,  bind = false },
		{ itemid = 2800135, itemcount = 1,  bind = false },
		{ itemid = 2800135, itemcount = 1,  bind = false },
	},
	{
		func = 'huchi_xianglian',
		maxitemcount = 1,
		{ itemid = 999200111, itemcount = 1, class = clsWarrior, bind = false },
		{ itemid = 999200121, itemcount = 1, class = clsMage, bind = false },
		{ itemid = 999200131, itemcount = 1, class = clsTaoist, bind = false },
	},
	
	{
		func = 'jiyi_xianglian',
		maxitemcount = 1,
		{ itemid = 999200213, itemcount = 1, class = clsWarrior, bind = false },
		{ itemid = 999200223, itemcount = 1, class = clsMage, bind = false },
		{ itemid = 999200233, itemcount = 1, class = clsTaoist, bind = false },
	},

	
	{
		func = 'Huguo_cl',
		maxitemcount = 1,
		{ select =
			{
				{itemid = 21001, itemcount = 1, weight = 60},
				{itemid = 21002, itemcount = 1, weight = 60},
				{itemid = 21003, itemcount = 1, weight = 60},
				{itemid = 80003, itemcount = 1, weight = 60},
				{itemid = 1800040, itemcount = 1, weight = 30},
				{itemid = 1800015, itemcount = 1, weight = 30},
				{itemid = 2800064, itemcount = 1, weight = 10},
			},
		},
	},
	
	
	{
		func = 'xinhun_libao',
		maxitemcount = 9,
		{ itemid = 2800225, itemcount = 1,  bind = true },
		--{ itemid = 2800227, itemcount = 3,  bind = true },
		{ itemid = 384, itemcount = 1,  bind = true },
		{ itemid = 384, itemcount = 1,  bind = true },
		{ itemid = 384, itemcount = 1,  bind = true },
		{ itemid = 384, itemcount = 1,  bind = true },
		{ itemid = 384, itemcount = 1,  bind = true },
		{ itemid = 384, itemcount = 1,  bind = true },
		{ itemid = 384, itemcount = 1,  bind = true },
		{ itemid = 2212, itemcount = 77,  bind = true },
	},
	
	
	
	{
		func = 'VIPJinBi',
		maxitemcount = 1,
		{ moneytype = MONEYTYPE_02, moneyamount = 500000},
	},
	{
		func = 'MoLongKu',
		maxitemcount = 2,
				{itemid = 21001, itemcount = 1, class = clsWarrior, bind = true},
				{itemid = 21002, itemcount = 1, class = clsMage, bind = true},
				{itemid = 21003, itemcount = 1, class = clsTaoist, bind = true},
		{ select =
			{
				{itemid = 21001, itemcount = 1, weight = 50},
				{itemid = 21002, itemcount = 1, weight = 50},
				{itemid = 21003, itemcount = 1, weight = 50},
			},percent = 20
		},
	},
	{
		func = 'ShengDanKuaiLe',
		maxitemcount = 1,
		{ select =
			{
				{itemid = 999806131, itemcount = 1, weight = 50},
				{itemid = 999906131, itemcount = 1, weight = 50},
				{itemid = 999806231, itemcount = 1, weight = 50},
				{itemid = 999906231, itemcount = 1, weight = 50},
				{itemid = 999806331, itemcount = 1, weight = 50},
				{itemid = 999906331, itemcount = 1, weight = 50},
				{itemid = 999000261, itemcount = 1, weight = 50},
				{itemid = 999300021, itemcount = 1, weight = 50},
				{itemid = 999300031, itemcount = 1, weight = 50},
				{itemid = 999300041, itemcount = 1, weight = 50},
				{itemid = 999400011, itemcount = 1, weight = 50},
				{itemid = 999400012, itemcount = 1, weight = 50},
				{itemid = 999400013, itemcount = 1, weight = 50},
				{itemid = 999200011, itemcount = 1, weight = 50},
			},
		},
	},
	{
		func = 'NewSuiPian1',
		maxitemcount = 1,
		{ select =
			{
				{itemid = 1800034, itemcount = 7, weight = 40},
				{itemid = 1800034, itemcount = 8, weight = 40},
				{itemid = 1800034, itemcount = 9, weight = 50},
				{itemid = 1800034, itemcount = 10, weight = 50},
				{itemid = 1800034, itemcount = 11, weight = 50},
				{itemid = 1800034, itemcount = 12, weight = 40},
				{itemid = 1800034, itemcount = 13, weight = 35},
				{itemid = 1800034, itemcount = 14, weight = 30},

			},
		},
	},
	{
		func = 'NewSuiPian2',
		maxitemcount = 1,
		{ select =
			{
				{itemid = 1800034, itemcount = 70, weight = 30},
				{itemid = 1800034, itemcount = 80, weight = 30},
				{itemid = 1800034, itemcount = 90, weight = 50},
				{itemid = 1800034, itemcount = 100, weight = 50},
				{itemid = 1800034, itemcount = 110, weight = 50},
				{itemid = 1800034, itemcount = 120, weight = 40},
				{itemid = 1800034, itemcount = 130, weight = 30},
				{itemid = 1800034, itemcount = 140, weight = 20},

			},
		},
	},
	{
		func = 'XinYunSuiPian1',
		maxitemcount = 1,
		{ select =
			{
				{itemid = 2800006, itemcount = 7, weight = 30},
				{itemid = 2800006, itemcount = 8, weight = 30},
				{itemid = 2800006, itemcount = 9, weight = 50},
				{itemid = 2800006, itemcount = 10, weight = 50},
				{itemid = 2800006, itemcount = 11, weight = 50},
				{itemid = 2800006, itemcount = 12, weight = 40},
				{itemid = 2800006, itemcount = 13, weight = 30},
				{itemid = 2800006, itemcount = 14, weight = 20},

			},
		},
	},
	{
		func = 'XinYunSuiPian2',
		maxitemcount = 1,
		{ select =
			{
				{itemid = 2800006, itemcount = 70, weight = 30},
				{itemid = 2800006, itemcount = 80, weight = 30},
				{itemid = 2800006, itemcount = 90, weight = 50},
				{itemid = 2800006, itemcount = 100, weight = 50},
				{itemid = 2800006, itemcount = 110, weight = 50},
				{itemid = 2800006, itemcount = 120, weight = 40},
				{itemid = 2800006, itemcount = 130, weight = 30},
				{itemid = 2800006, itemcount = 140, weight = 20},

			},
		},
	},
	{
		func = 'DiYiCao',
		maxitemcount = 1,
		{itemid = 21111, itemcount = 1, class = clsWarrior},
		{itemid = 21112, itemcount = 1, class = clsMage},
		{itemid = 21113, itemcount = 1, class = clsTaoist},
	},
	{
		func = 'DiErCao',
		maxitemcount = 1,
		{itemid = 21211, itemcount = 1, class = clsWarrior},
		{itemid = 21212, itemcount = 1, class = clsMage},
		{itemid = 21213, itemcount = 1, class = clsTaoist},
	},
	{
		func = 'warriorrune',
		maxitemcount = 1,
		{itemid = 21001, itemcount = 4},
	},
	{
		func = 'magerune',
		maxitemcount = 1,
		{itemid = 21002, itemcount = 4},
	},
	{
		func = 'taoistrune',
		maxitemcount = 1,
		{itemid = 21003, itemcount = 4},
	},

	--[[{
		func = 'YaoQing_LiBao',
		maxitemcount = 5,
		{itemid = 3800005, itemcount = 1,bind = true},
		{itemid = 1800019, itemcount = 1,bind = true},
		{itemid = 21001, itemcount = 5,class = clsWarrior,bind = true},
		{itemid = 21002, itemcount = 5, class = clsMage,bind = true},
		{itemid = 21003, itemcount = 5, class = clsTaoist,bind = true},
		{itemid = 31034, itemcount = 1,class = clsWarrior,bind = true},
		{itemid = 32546, itemcount = 1, class = clsMage,bind = true},
		{itemid = 33012, itemcount = 1, class = clsTaoist,bind = true},
		{itemid = 2800145, itemcount = 1,class = clsWarrior,bind = true},
		{itemid = 2800146, itemcount = 1, class = clsMage,bind = true},
		{itemid = 2800147, itemcount = 1, class = clsTaoist,bind = true},
		
	},]]--
	
	{
		func = 'Woma_Zhanshi',
		maxitemcount = 1,
		{ select =
			{
			{ itemid = 99900019, itemcount = 1,weight = 30 , bind = true },------战士武器
			{ itemid = 99980413, itemcount = 1,weight = 30 ,sex = cstMale, bind = true },------男战士衣服
			{ itemid = 99990413, itemcount = 1,weight = 30 ,sex = cstFemale, bind = true },------女战士衣服
			{ itemid = 99920016, itemcount = 1,weight = 30, bind = true },------战士首饰
			{ itemid = 99930018, itemcount = 1,weight = 30 , bind = true },------战士首饰
			{ itemid = 99940020, itemcount = 1,weight = 30 , bind = true },------战士首饰
			},
		},
	},
	
	{
		func = 'Woma_Fashi',
		maxitemcount = 1,
		{ select =
			{
			{ itemid = 99900018, itemcount = 1, weight = 30 , bind = true },------法师武器
			{ itemid = 99980423, itemcount = 1, weight = 30 ,sex = cstMale, bind = true },------男法师衣服
			{ itemid = 99990423, itemcount = 1, weight = 30 ,sex = cstFemale, bind = true },------女法师衣服
			{ itemid = 99920020, itemcount = 1, weight = 30 , bind = true },------法师首饰
			{ itemid = 99930017, itemcount = 1, weight = 30 , bind = true },------法师首饰
			{ itemid = 99940011, itemcount = 1, weight = 30 , bind = true },------法师首饰
			},
		},
	},
	
	{
		func = 'Woma_Daoshi',
		maxitemcount = 1,
		{ select =
			{
			{ itemid = 99900021, itemcount = 1, weight = 30, bind = true },------道士武器
			{ itemid = 99980433, itemcount = 1, weight = 30,sex = cstMale, bind = true },------男道士衣服
			{ itemid = 99990433, itemcount = 1, weight = 30,sex = cstFemale, bind = true },------女道士衣服
			{ itemid = 99920021, itemcount = 1, weight = 30, bind = true },------道士首饰
			{ itemid = 99930014, itemcount = 1, weight = 30, bind = true },------道士首饰
			{ itemid = 99940015, itemcount = 1, weight = 30, bind = true },------道士首饰
			},
		},
	},
	--2020-4-11 赤柱宝箱
	{
		func = 'choujiangxiangzi',
		maxitemcount = 2,
		{ select =
			{
				{ itemid = 383, itemcount = 1, weight = 193388, },------疗伤药盒子
				{ itemid = 1800009, itemcount = 1, weight = 193388, },------小金币包
				{ itemid = 80003, itemcount = 1, weight =193388, },------祝福油
				{ itemid = 1800040, itemcount = 1, weight = 66293, },------特修券
				{ itemid = 1800011, itemcount = 1, weight =67686, },------大金币包
				{ itemid = 99900022, itemcount = 1, weight =97, },------井中月
				{ itemid = 99900023, itemcount = 1, weight =155, },------血饮
				{ itemid = 99900024, itemcount = 1, weight =155, },------无极棍
				{ itemid = 99900028, itemcount = 1, weight =155, },------骨玉
				{ itemid = 90218, itemcount = 1, weight =9669, },------冰咆哮残卷
				{ itemid = 90217, itemcount = 1, weight =9669, },------烈火剑法残卷
				{ itemid = 90219, itemcount = 1, weight =9669, },------召唤神兽残卷
				{ itemid = 32537, itemcount = 1, weight =290, },------冰咆哮
				{ itemid = 31036, itemcount = 1, weight =290, },------烈火剑法
				{ itemid = 33008, itemcount = 1, weight =290, },------召唤神兽
				{ itemid = 99900027, itemcount = 1, weight =97, },------龙纹
				{ itemid = 99900025, itemcount = 1, weight =10, },------裁决
				{ itemid = 99900032, itemcount = 1, weight =19, },------怒斩
				{ itemid = 99900031, itemcount = 1, weight =19, },------逍遥扇
				{ itemid = 701, itemcount = 1, weight =63818, },------攻击神水
				{ itemid = 702, itemcount = 1, weight =63818, },------魔力药水
				{ itemid = 703, itemcount = 1, weight =63818, },------精神药水
				{ itemid = 705, itemcount = 1, weight =63818, },------体力药水
			},
			announce_expensive = ' {role_name} 从积分抽奖中获得了道具:[item_name]',	
		},
		{itemid = 2800161, itemcount = 1},
	},
	--2020-5-21 中环宝箱
	--[[{
		func = 'choujiangxiangzi1',
		maxitemcount = 2,
		{select =
			{
				{ itemid = 383, itemcount = 1, weight = 193388, },------疗伤药盒子
				{ itemid = 1800009, itemcount = 1, weight = 193388, },------小金币包
				{ itemid = 80003, itemcount = 1, weight =193388, },------祝福油
				{ itemid = 1800040, itemcount = 1, weight = 66293, },------特修券
				{ itemid = 1800011, itemcount = 1, weight =67686, },------大金币包
				{ itemid = 99900022, itemcount = 1, weight =97, },------井中月
				{ itemid = 99900023, itemcount = 1, weight =155, },------血饮
				{ itemid = 99900024, itemcount = 1, weight =155, },------无极棍
				{ itemid = 99900028, itemcount = 1, weight =155, },------骨玉
				{ itemid = 90218, itemcount = 1, weight =9669, },------冰咆哮残卷
				{ itemid = 90217, itemcount = 1, weight =9669, },------烈火剑法残卷
				{ itemid = 90219, itemcount = 1, weight =9669, },------召唤神兽残卷
				{ itemid = 32537, itemcount = 1, weight =290, },------冰咆哮
				{ itemid = 31036, itemcount = 1, weight =290, },------烈火剑法
				{ itemid = 33008, itemcount = 1, weight =290, },------召唤神兽
				{ itemid = 99900027, itemcount = 1, weight =97, },------龙纹
				{ itemid = 99900025, itemcount = 1, weight =10, },------裁决
				{ itemid = 99900032, itemcount = 1, weight =19, },------怒斩
				{ itemid = 99900031, itemcount = 1, weight =19, },------逍遥扇
				{ itemid = 701, itemcount = 1, weight =63818, },------攻击神水
				{ itemid = 702, itemcount = 1, weight =63818, },------魔力药水
				{ itemid = 703, itemcount = 1, weight =63818, },------精神药水
				{ itemid = 705, itemcount = 1, weight =63818, },------体力药水
			},
			announce_expensive = ' {role_name} 从积分抽奖中获得了道具:[item_name]',	
		},
		{itemid = 2800161, itemcount = 1},
		
		{ moneytype = MONEYTYPE_02, moneyamount = 10000 },
	},]]--
	
	
	--[[{
		func = 'choujiangxiangzi1',
		maxitemcount = 1,
		yuanbao = 1000,
		{ select =
			{
				{ itemid = 2800209, itemcount = 1, weight = 10000, },---1元元宝券
				{ itemid = 2800081, itemcount = 1, weight = 20000, },---5元元宝券
				{ itemid = 383, itemcount = 1, weight =5000, },------疗伤药
				{ itemid = 90217, itemcount = 1, weight = 4000, },------烈火残页
				{ itemid = 90218, itemcount = 1, weight =500, },------冰咆哮残页
				{ itemid = 90219, itemcount = 1, weight =500, },------召唤神兽残页
				{ itemid = 2800171, itemcount = 1, weight =10000, },------裁决碎片
				{ itemid = 99900024, itemcount = 1, weight =10, },------无极棍
				{ itemid = 99900028, itemcount = 1, weight =10, },------骨玉
				{ itemid = 99900025, itemcount = 1, weight =10, },------裁决
				
			},
			--announce_expensive = ' {role_name} 从积分抽奖中获得了道具:[item_name]',	
		},
	},]]--
	--2020-7-18	签到送的运1礼盒
	{
		func = 'yun1_xianglian',
		maxitemcount = 1,
		{itemid = 999200141, itemcount = 1,class = clsWarrior,bind = true},
		{itemid = 999200151, itemcount = 1, class = clsMage,bind = true},
		{itemid = 999200161, itemcount = 1, class = clsTaoist,bind = true},
	},
	--2020-7-18	签到送的运1礼盒
	{
		func = 'yun1_xianglian1',
		maxitemcount = 1,
		{itemid = 999200243, itemcount = 1,class = clsWarrior,bind = true},
		{itemid = 999200253, itemcount = 1, class = clsMage,bind = true},
		{itemid = 999200263, itemcount = 1, class = clsTaoist,bind = true},
	},
	---神物行礼盒
	{
		func = 'shenwuxing_huangdaxian',
		maxitemcount = 1,
		{ select =
			{
				{ itemid = 2800171, itemcount = 1, weight =200 },
				{ itemid = 1800033, itemcount = 1, weight =100 },
				{ itemid = 90217, itemcount = 1, weight =100 },
				{ itemid = 90218, itemcount = 1, weight =100 },
				{ itemid = 90219, itemcount = 1, weight =100 },
				{ itemid = 2800203, itemcount = 1, weight =80 },
				{ itemid = 2800204, itemcount = 1, weight =80 },
				{ itemid = 2800205, itemcount = 1, weight =80 },
				{ itemid = 2800206, itemcount = 4, weight =100 },
				{ itemid = 2800177, itemcount = 1, weight =100 },
				{ itemid = 2800178, itemcount = 1, weight =100 },
				{ itemid = 2800179, itemcount = 1, weight =100 },
				{ itemid = 2800172, itemcount = 1, weight =100 },
				{ itemid = 2800173, itemcount = 1, weight =100 },
				{ itemid = 2800174, itemcount = 1, weight =100 },
				{ itemid = 2800175, itemcount = 1, weight =100 },
				{ itemid = 2800176, itemcount = 1, weight =100 },
				{ itemid = 1800001, itemcount = 8, weight =100 },
				{ itemid = 2800200, itemcount = 1, weight =100 },
				{ itemid = 2800081, itemcount = 1, weight =100 },
				{ itemid = 2800082, itemcount = 1, weight =50 },
				{ itemid = 1800058, itemcount = 1, weight =20 }, --88元宝
				{ itemid = 2800208, itemcount = 1, weight =200 },
				{ itemid = 1500056, itemcount = 1, weight =100 }, --沃玛首饰盒子
				{ itemid = 2800207, itemcount = 1, weight =200 },
			},
		announce_expensive = ' {role_name} 从神物行宝箱中获得了道具:[item_name]',		
		},	
	},
	
	
	{
		func = 'WoMaShouShi',--沃玛首饰盒子
		maxitemcount = 1,
		{select = 
			{
				{ itemid = 99920016, itemcount = 1, weight =100 },
				{ itemid = 99930018, itemcount = 1, weight =100 },
				{ itemid = 99940020, itemcount = 1, weight =100 },
				{ itemid = 99920020, itemcount = 1, weight =100 },
				{ itemid = 99930017, itemcount = 1, weight =100 },
				{ itemid = 99940011, itemcount = 1, weight =80 },
				{ itemid = 99920021, itemcount = 1, weight =80 },
				{ itemid = 99930014, itemcount = 1, weight =80 },
				{ itemid = 99940015, itemcount = 1, weight =80 },
			},
		},			
	},

	{
		func = 'BLG_lihe',--冰裂狗碎片随机
		maxitemcount = 1,
		{select = 
			{
				{ itemid = 90217, itemcount = 1, weight =100 },
				{ itemid = 90218, itemcount = 1, weight =100 },
				{ itemid = 90219, itemcount = 1, weight =100 },
			},
		},			
	},

	{
		func = 'baoshi_lihe',--普通宝石随机
		maxitemcount = 1,
		{select = 
			{
				{ itemid = 10110, itemcount = 1, weight =100 },--最大道术+1
				{ itemid = 10120, itemcount = 1, weight =100 },--体力+5
				{ itemid = 10220, itemcount = 1, weight =100 },--最大防御+1
				{ itemid = 10320, itemcount = 1, weight =100 },--最大魔法+1
				{ itemid = 10420, itemcount = 1, weight =100 },--最大攻击+1
				{ itemid = 10520, itemcount = 1, weight =100 },--最大魔防+1
			},
		},			
	},
	{
		func = 'MingWen_FuDai',--发布会版本铭文福袋 本职业铭文一个
		maxitemcount = 1,
		{ itemid = 21001, itemcount = 50, class = clsWarrior, bind = true },
		{ itemid = 21002, itemcount = 50, class = clsMage, bind = true },
		{ itemid = 21003, itemcount = 50, class = clsTaoist, bind = true },			
	},
	{
		func = 'jinsheng_lihe',--晋升礼盒
		maxitemcount = 1,
		{select = 
			{
				{ itemid = 21001, itemcount = 1, weight =1800 },--战士铭文
				{ itemid = 21002, itemcount = 1, weight =1800 },--法师铭文
				{ itemid = 21003, itemcount = 1, weight =1800 },--道士铭文
				{ itemid = 80003, itemcount = 1, weight =1800 },--祝福油
				{ itemid = 2800357, itemcount = 1, weight =1800 },--10积分
				{ itemid = 2800357, itemcount = 5, weight =400 },--50积分
				{ itemid = 10110, itemcount = 1, weight =30 },--最大道术+1
				{ itemid = 10120, itemcount = 1, weight =30 },--体力+5
				{ itemid = 10220, itemcount = 1, weight =30 },--最大防御+1
				{ itemid = 10320, itemcount = 1, weight =30 },--最大魔法+1
				{ itemid = 10420, itemcount = 1, weight =30 },--最大攻击+1
				{ itemid = 10520, itemcount = 1, weight =30 },--最大魔防+1
			},
		},			
	},
	{
		func = 'xinnian_liwu',--新年礼物
		maxitemcount = 1,
		{select = 
			{
				{ itemid = 21001, itemcount = 1, weight =1800 },--战士铭文
				{ itemid = 21002, itemcount = 1, weight =1800 },--法师铭文
				{ itemid = 21003, itemcount = 1, weight =1800 },--道士铭文
				{ itemid = 80003, itemcount = 1, weight =1800 },--祝福油
				{ itemid = 383, itemcount = 1, weight =1800 },--疗伤药
				{ itemid = 2800138, itemcount = 1, weight =100 },--祝福油
				{ itemid = 2800357, itemcount = 1, weight =100 },--10积分
			},
		},			
	},
	
	{
		func = 'manghe_1',   --盲盒1
		maxitemcount = 1,    --包裹需要空格数

		{	select =
			{
				{ itemid = 10110, itemcount = 1, weight = 1  ,bind = true }, --驭朱灵石1级
				{ itemid = 10210, itemcount = 1, weight = 1  ,bind = true }, --命朱灵石1级
				{ itemid = 10120, itemcount = 1, weight = 1 ,bind = true }, --新阳灵石1级
				{ itemid = 10220, itemcount = 1, weight = 1 ,bind = true }, --	守阳灵石1级
				{ itemid = 10310, itemcount = 1, weight = 1 ,bind = true }, --透蓝灵石1级
				{ itemid = 10320, itemcount = 1, weight = 1 ,bind = true }, --蔚蓝灵石1级
				{ itemid = 10410, itemcount = 1, weight = 1 ,bind = true }, --盈绿灵石1级
				{ itemid = 10420, itemcount = 1, weight = 1 ,bind = true },--精绿灵石1级
				{ itemid = 10510, itemcount = 1, weight = 1 ,bind = true },--韧紫灵石1级
				{ itemid = 10520, itemcount = 1, weight = 1 ,bind = true },--纯紫灵石1级
				{ itemid = 10340, itemcount = 1, weight = 1 ,bind = true },--速蓝灵石1级
				{ itemid = 10140, itemcount = 1, weight = 1 ,bind = true },--敏朱灵石1级
				{ itemid = 10230, itemcount = 1, weight = 1 ,bind = true },--魔闪灵石1级
				{ itemid = 10440, itemcount = 1, weight = 1 ,bind = true },--准绿灵石1级
			},
			
		},
	},
	
	{
		func = 'manghe_2',   --盲盒2
		maxitemcount = 1,    --包裹需要空格数

		{	select =
			{
				{ itemid = 10111, itemcount = 1, weight = 1  ,bind = false }, --驭朱灵石2级
				{ itemid = 10211, itemcount = 1, weight = 1  ,bind = false }, --命朱灵石2级
				{ itemid = 10121, itemcount = 1, weight = 1 ,bind = false }, --新阳灵石2级
				{ itemid = 10221, itemcount = 1, weight = 1 ,bind = false }, --	守阳灵石2级
				{ itemid = 10311, itemcount = 1, weight = 1 ,bind = false }, --透蓝灵石2级
				{ itemid = 10321, itemcount = 1, weight = 1 ,bind = false }, --蔚蓝灵石2级
				{ itemid = 10411, itemcount = 1, weight = 1 ,bind = false }, --盈绿灵石2级
				{ itemid = 10421, itemcount = 1, weight = 1 ,bind = false },--精绿灵石2级
				{ itemid = 10511, itemcount = 1, weight = 1 ,bind = false },--韧紫灵石2级
				{ itemid = 10521, itemcount = 1, weight = 1 ,bind = false },--纯紫灵石2级
				{ itemid = 10341, itemcount = 1, weight = 1 ,bind = false },--速蓝灵石2级
				{ itemid = 10141, itemcount = 1, weight = 1 ,bind = false },--敏朱灵石2级
				{ itemid = 10231, itemcount = 1, weight = 1 ,bind = false },--魔闪灵石2级
				{ itemid = 10441, itemcount = 1, weight = 1 ,bind = false },--准绿灵石2级
			},
			
		},
	},
	
	{
		func = 'lihe_chiyuewuqi', --赤月武器礼盒
		maxitemcount = 1,    --包裹需要空格数
				{itemid = 99900032, itemcount = 1,class = clsWarrior}, --怒斩
				{itemid = 99900033, itemcount = 1, class = clsMage},--龙牙
				{itemid = 99900031, itemcount = 1, class = clsTaoist},--逍遥扇
	},
	
	{
		func = 'lihe_zumawuqi', --祖玛武器礼盒
		maxitemcount = 1,    --包裹需要空格数
				{itemid = 99900022, itemcount = 1,class = clsWarrior}, --井中月
				{itemid = 99900023, itemcount = 1, class = clsMage},--血饮
				{itemid = 99900024, itemcount = 1, class = clsTaoist},--无极棍
	},
	
	{
		func = 'lihe_pifeng3', --三级披风礼盒
		maxitemcount = 1,    --包裹需要空格数
				{itemid = 99950013, itemcount = 1,class = clsWarrior}, --魔牙战麾·燃烧
				{itemid = 99950023, itemcount = 1, class = clsMage},--魔法斗篷·燃烧
				{itemid = 99950033, itemcount = 1, class = clsTaoist},--霜焰披风·燃烧
	},
	
	{
		func = 'lihe_gaojijineng',   --高级技能碎片礼盒
		maxitemcount = 1,    --包裹需要空格数

		{	select =
			{
				{ itemid = 2800377, itemcount = 1, weight = 1  ,bind = false }, --狮子吼
				{ itemid = 2800378, itemcount = 1, weight = 1  ,bind = false }, --逐日剑法
				{ itemid = 2800379, itemcount = 1, weight = 1 ,bind = false }, --寒冰掌
				{ itemid = 2800380, itemcount = 1, weight = 1 ,bind = false }, --	灭天火
				{ itemid = 2800381, itemcount = 1, weight = 1 ,bind = false }, --流星火雨
				{ itemid = 2800382, itemcount = 1, weight = 1 ,bind = false }, --无极真气
				{ itemid = 2800383, itemcount = 1, weight = 1 ,bind = false }, --噬血术
			},
			
		},
	},

	{
		func = 'lihe_chiyuewuqisuipian',   --赤月武器碎片礼盒
		maxitemcount = 1,    --包裹需要空格数
		{	select =
			{
				{ itemid = 2800385, itemcount = 1, weight = 1  ,bind = false }, --井中月碎片
				{ itemid = 2800386, itemcount = 1, weight = 1  ,bind = false }, --血饮碎片
				{ itemid = 2800387, itemcount = 1, weight = 1 ,bind = false }, --无极棍碎片				
			},
		},
	},
	
	
------------------------自己新增加的礼包 begin

-- 50%幸运2项链(白色虎齿)
	{
		func = 'yun2_HuChi_50',
		maxitemcount = 1,
		{ itemid = 99999120, itemcount = 1, percent = 50 },
	},

-- 100%幸运2项链(白色虎齿)
	{
		func = 'yun2_HuChi_100',
		maxitemcount = 1,    --包裹需要空格数
		{ itemid = 99999120, itemcount = 1, class = clsWarrior },
		{ itemid = 99999120, itemcount = 1, class = clsMage },
		{ itemid = 99999120, itemcount = 1, class = clsTaoist },
	},

-- 100%幸运2项链(记忆)
	{
		func = 'yun2_JiYi',
		maxitemcount = 1,    --包裹需要空格数
		{ itemid = 99999130, itemcount = 1, class = clsWarrior },
		{ itemid = 99999140, itemcount = 1, class = clsMage },
		{ itemid = 99999150, itemcount = 1, class = clsTaoist },
	},

-- 每日宣传礼包
	{
		func = 'EveryDayInviteGift',
		maxitemcount = 1,    --包裹需要空格数
		{ moneytype = MONEYTYPE_02, moneyamount = 200000 },    -- 20万金币
		{ itemid = 21001, itemcount = 5, bind = true, class = clsWarrior }, -- 本职业铭文5个
		{ itemid = 21002, itemcount = 5, bind = true, class = clsMage },
		{ itemid = 21003, itemcount = 5, bind = true, class = clsTaoist },
	},

-- 战士沃玛装备
	{
		func = 'WoMaEquip_ZhanShi',
		maxitemcount = 11,
		{ itemid = 99900019, itemcount = 1, bind = false },
		{ itemid = 99990411, itemcount = 1, bind = false },
		{ itemid = 99980413, itemcount = 1, bind = false },
		{ itemid = 99990413, itemcount = 1, bind = false },
		{ itemid = 99990415, itemcount = 1, bind = false },
		{ itemid = 99990417, itemcount = 1, bind = false },
		{ itemid = 99920016, itemcount = 1, bind = false },
		{ itemid = 99930018, itemcount = 1, bind = false },
		{ itemid = 99930018, itemcount = 1, bind = false },
		{ itemid = 99940020, itemcount = 1, bind = false },
		{ itemid = 99940020, itemcount = 1, bind = false },
	},
-- 战士祖玛装备
	{
		func = 'ZuMaEquip_ZhanShi',
		maxitemcount = 11,
		{ itemid = 99900022, itemcount = 1, bind = false },
		{ itemid = 99990511, itemcount = 1, bind = false },
		{ itemid = 99980513, itemcount = 1, bind = false },
		{ itemid = 99990513, itemcount = 1, bind = false },
		{ itemid = 99990515, itemcount = 1, bind = false },
		{ itemid = 99990517, itemcount = 1, bind = false },
		{ itemid = 99920017, itemcount = 1, bind = false },
		{ itemid = 99930019, itemcount = 1, bind = false },
		{ itemid = 99930019, itemcount = 1, bind = false },
		{ itemid = 99940012, itemcount = 1, bind = false },
		{ itemid = 99940012, itemcount = 1, bind = false },
	},
-- 战士赤月装备
	{
		func = 'ChiYueEquip_ZhanShi',
		maxitemcount = 12,
		{ itemid = 99900025, itemcount = 1, bind = false },
		{ itemid = 99900032, itemcount = 1, bind = false },
		{ itemid = 99990611, itemcount = 1, bind = false },
		{ itemid = 99980613, itemcount = 1, bind = false },
		{ itemid = 99990613, itemcount = 1, bind = false },
		{ itemid = 99990615, itemcount = 1, bind = false },
		{ itemid = 99990617, itemcount = 1, bind = false },
		{ itemid = 99920027, itemcount = 1, bind = false },
		{ itemid = 99930033, itemcount = 1, bind = false },
		{ itemid = 99930033, itemcount = 1, bind = false },
		{ itemid = 99940024, itemcount = 1, bind = false },
		{ itemid = 99940024, itemcount = 1, bind = false },
	},

-- 法师沃玛装备
	{
		func = 'WoMaEquip_FaShi',
		maxitemcount = 11,
		{ itemid = 99900018, itemcount = 1, bind = false },
		{ itemid = 99990411, itemcount = 1, bind = false },
		{ itemid = 99980423, itemcount = 1, bind = false },
		{ itemid = 99990423, itemcount = 1, bind = false },
		{ itemid = 99990415, itemcount = 1, bind = false },
		{ itemid = 99990417, itemcount = 1, bind = false },
		{ itemid = 99920020, itemcount = 1, bind = false },
		{ itemid = 99930017, itemcount = 1, bind = false },
		{ itemid = 99930017, itemcount = 1, bind = false },
		{ itemid = 99940011, itemcount = 1, bind = false },
		{ itemid = 99940011, itemcount = 1, bind = false },
	},
-- 法师祖玛装备
	{
		func = 'ZuMaEquip_FaShi',
		maxitemcount = 11,
		{ itemid = 99900023, itemcount = 1, bind = false },
		{ itemid = 99990511, itemcount = 1, bind = false },
		{ itemid = 99980523, itemcount = 1, bind = false },
		{ itemid = 99990523, itemcount = 1, bind = false },
		{ itemid = 99990515, itemcount = 1, bind = false },
		{ itemid = 99990517, itemcount = 1, bind = false },
		{ itemid = 99920019, itemcount = 1, bind = false },
		{ itemid = 99930020, itemcount = 1, bind = false },
		{ itemid = 99930020, itemcount = 1, bind = false },
		{ itemid = 99940016, itemcount = 1, bind = false },
		{ itemid = 99940016, itemcount = 1, bind = false },
	},
-- 法师赤月装备
	{
		func = 'ChiYueEquip_FaShi',
		maxitemcount = 12,
		{ itemid = 99900028, itemcount = 1, bind = false },
		{ itemid = 99900033, itemcount = 1, bind = false },
		{ itemid = 99990621, itemcount = 1, bind = false },
		{ itemid = 99980623, itemcount = 1, bind = false },
		{ itemid = 99990623, itemcount = 1, bind = false },
		{ itemid = 99990615, itemcount = 1, bind = false },
		{ itemid = 99990617, itemcount = 1, bind = false },
		{ itemid = 99920028, itemcount = 1, bind = false },
		{ itemid = 99930034, itemcount = 1, bind = false },
		{ itemid = 99930034, itemcount = 1, bind = false },
		{ itemid = 99940025, itemcount = 1, bind = false },
		{ itemid = 99940025, itemcount = 1, bind = false },
	},

-- 道士沃玛装备
	{
		func = 'WoMaEquip_DaoShi',
		maxitemcount = 11,
		{ itemid = 99900021, itemcount = 1, bind = false },
		{ itemid = 99990411, itemcount = 1, bind = false },
		{ itemid = 99980433, itemcount = 1, bind = false },
		{ itemid = 99990433, itemcount = 1, bind = false },
		{ itemid = 99990415, itemcount = 1, bind = false },
		{ itemid = 99990417, itemcount = 1, bind = false },
		{ itemid = 99920021, itemcount = 1, bind = false },
		{ itemid = 99930014, itemcount = 1, bind = false },
		{ itemid = 99930014, itemcount = 1, bind = false },
		{ itemid = 99940015, itemcount = 1, bind = false },
		{ itemid = 99940015, itemcount = 1, bind = false },
	},
-- 道士祖玛装备
	{
		func = 'ZuMaEquip_DaoShi',
		maxitemcount = 11,
		{ itemid = 99900024, itemcount = 1, bind = false },
		{ itemid = 99990511, itemcount = 1, bind = false },
		{ itemid = 99980533, itemcount = 1, bind = false },
		{ itemid = 99990533, itemcount = 1, bind = false },
		{ itemid = 99990515, itemcount = 1, bind = false },
		{ itemid = 99990517, itemcount = 1, bind = false },
		{ itemid = 99920018, itemcount = 1, bind = false },
		{ itemid = 99930021, itemcount = 1, bind = false },
		{ itemid = 99930021, itemcount = 1, bind = false },
		{ itemid = 99940010, itemcount = 1, bind = false },
		{ itemid = 99940010, itemcount = 1, bind = false },
	},
-- 道士赤月装备
	{
		func = 'ChiYueEquip_DaoShi',
		maxitemcount = 12,
		{ itemid = 99900027, itemcount = 1, bind = false },
		{ itemid = 99900031, itemcount = 1, bind = false },
		{ itemid = 99990631, itemcount = 1, bind = false },
		{ itemid = 99980633, itemcount = 1, bind = false },
		{ itemid = 99990633, itemcount = 1, bind = false },
		{ itemid = 99990615, itemcount = 1, bind = false },
		{ itemid = 99990617, itemcount = 1, bind = false },
		{ itemid = 99920029, itemcount = 1, bind = false },
		{ itemid = 99930035, itemcount = 1, bind = false },
		{ itemid = 99930035, itemcount = 1, bind = false },
		{ itemid = 99940026, itemcount = 1, bind = false },
		{ itemid = 99940026, itemcount = 1, bind = false },
	},

-- 2000041-签到铭文礼包(10个)
	{
		func = 'QianDaoMingWen_10',
		maxitemcount = 2,
		{ itemid = 21001, itemcount = 10, class = clsWarrior, bind = true },
		{ itemid = 21002, itemcount = 10, class = clsMage,    bind = true },
		{ itemid = 21003, itemcount = 10, class = clsTaoist,  bind = true },
	},

-- 2000042-签到黑铁礼包
	{
		func = 'QianDao_HeiTie26_6',
		maxitemcount = 6,
		{ itemid = 114026, itemcount = 1, bind = true },
		{ itemid = 114026, itemcount = 1, bind = true },
		{ itemid = 114026, itemcount = 1, bind = true },
		{ itemid = 114026, itemcount = 1, bind = true },
		{ itemid = 114026, itemcount = 1, bind = true },
		{ itemid = 114026, itemcount = 1, bind = true },
	},

-- 2000043-测试奖励铭文礼包
	{
		func = 'TestGiftRuneStones',
		maxitemcount = 1,
		{ itemid = 21001, itemcount = 10, bind = true, class = clsWarrior }, -- 本职业铭文5个
		{ itemid = 21002, itemcount = 10, bind = true, class = clsMage },
		{ itemid = 21003, itemcount = 10, bind = true, class = clsTaoist },
	},



------------------------自己新增加的礼包 end
	
};

ANNOUNCE_REPL_STRING_FUNC_TABLE =
{
	role_name = function (pRole)
		return pRole:GetName();
	end,

	item_name = function (d)
		return d.m_szName;
	end,
};

function _award(v, class, sex, itembag, pRole, itemid)
	-- 设置种子
	math.randomseed(os.time() * 1000 + os.clock() * 1000000);
	
	if v.class and v.class ~= class then
		return;
	end

	if v.sex and v.sex ~= sex then
		return;
	end

	if v.percent then
		if math.random(100) >= v.percent then
			return;
		end
	end

	if v.select then
		local totalweight = 0;
		for index,item in ipairs(v.select) do
			if item.itemid and item.itemcount and item.weight and item.weight > 0 then
				totalweight = totalweight + item.weight;
				-- print('debug: index:' .. index .. ', itemid:' .. item.itemid .. ', itemcount:' .. item.itemcount .. ', weight:' .. item.weight);
			else
				print('wrong setting for package select');
				return;
			end
		end
		-- print('debug: totalweight:' .. totalweight);
		
		local random_number = math.random(totalweight);
		-- print ('debug: random_number:' .. random_number);
		
		for i=1,#v.select do
			if random_number <= v.select[i].weight then
					local item_data = GetItemData(v.select[i].itemid);
					itembag:AddItem(v.select[i].itemid, v.select[i].itemcount, ITEMLOG_PACKAGE, itemid, false);
					-- print("debug: get item :"..item_data.m_szName);
					
					-- 贵重物品, 公告
					if v.announce_expensive and item_data.m_byExpensiveItem == 1 then
							local msg = string.gsub(v.announce_expensive, "%\[(.-)%\]",
							function (s)
									if ANNOUNCE_REPL_STRING_FUNC_TABLE[s] and type(ANNOUNCE_REPL_STRING_FUNC_TABLE[s]) == 'function' then
											return ANNOUNCE_REPL_STRING_FUNC_TABLE[s](item_data);
									end
							end
							);

							msg = string.gsub(msg, "%{(.-)%}",
							function (s)
									if ANNOUNCE_REPL_STRING_FUNC_TABLE[s] and type(ANNOUNCE_REPL_STRING_FUNC_TABLE[s]) == 'function' then
											return ANNOUNCE_REPL_STRING_FUNC_TABLE[s](pRole);
									end
							end
							);

							local scene = pRole:GetScene();

							scene:Say(cctServer, cltLighting, msg);
					end
					
					break;
			end
			random_number = random_number - v.select[i].weight;
		end
		
	elseif v.itemid and v.itemcount then
		if (v.bind) then
			itembag:AddItem(v.itemid, v.itemcount, ITEMLOG_PACKAGE, itemid, true);
		else
			itembag:AddItem(v.itemid, v.itemcount, ITEMLOG_PACKAGE, itemid, false);
		end
	elseif v.exp then
        	pRole:AddExp(v.exp,false,false);
	elseif v.moneytype and v.moneyamount then
   		itembag:AddMoney(v.moneytype, v.moneyamount, MONEYLOG_PACKAGE, 0);
		if moneytype == MONEYTYPE_MASTER_EXP and pRole:GetMaster() then
			pRole:GetMaster():LuaSyncMasterExpToMS(pRole);
		end
	elseif v.title then
		pRole:GetTitle():AddTitle(v.title);
	elseif v.questid and v.questvar and v.questvalue then
		local quest = pRole:GetQuestList():GetAcceptedQuest(v.questid);
		if quest then
			pRole:GetQuestList():SetVariable(quest, v.varid, v.varvalue);
		end
	elseif v.doodadid then
		local scene = pRole:GetScene();
		local doodad = scene:SpawnDoodad(v.doodadid, pRole:GetX(), pRole:GetY(), pRole:GetZ(), pRole:GetFaceDirection());
	elseif v.pkvalue then
		local tempPkValue = pRole:GetPkValue();
		if v.chance == nil or math.random(1,100) <= v.chance then
			tempPkValue = tempPkValue - v.pkvalue;
		end
		if tempPkValue < 0 then
			tempPkValue = 0;
		end
		pRole:SetPkValue(tempPkValue);
	elseif v.aura then
		local aurainfo = CSpellConfig:GetInstance():FindAuraTemplate(v.aura);
		pRole:AppendAura(aurainfo, pRole, 0, NULL, 0, 0, 0, 1);
	end

	if v.announce then
		local message = string.gsub(v.announce, "%{(.-)%}",
			function (s)
				if ANNOUNCE_REPL_STRING_FUNC_TABLE[s] and type(ANNOUNCE_REPL_STRING_FUNC_TABLE[s]) == 'function' then
					return ANNOUNCE_REPL_STRING_FUNC_TABLE[s](pRole);
				end
			end
		);
		pRole:Say(cctGroup, cltTvShow, message);
	end
end

for _,p in ipairs(PACKAGE_TABLE) do
	if _G[p.func] then
		print('detected duplicated package function name '..p.func);
	end

	_G[p.func] = function(pItem, pRole)
		local itembag = pRole:GetItemBag();
		local free_slot_count = itembag:GetFreeSlots(CONSLOT_DEFAULT);
		local class = pRole:GetClass();
		local sex = pRole:GetSex();
		local itemid = pItem.m_pTemplate.m_nTemplateID;
		
		if p.deleteid then
			local a = pRole:GetItemBag():DeleteItemId(p.deleteid, 1, ITEMLOG_PACKAGE, false, 0);
			if a ~= 1 then
				return errItemNotEnough;
			end
		end
		
		if p.xingyun then
			local a = pRole:GetVariable(1023);
			a = a + p.xingyun;
			pRole:SetVariable(1023,a);
		end

		if p.yuanbao then
			local yuanbao = pRole:GetItemBag():GetMoney(3);
			if yuanbao< p.yuanbao then
				return errRealMoneyBuyNotEnoughMoney;
			end
			pRole:GetItemBag():ChangeYuanbao(pRole:GetUserName(),p.yuanbao,false,2800160,1);
		end

		--------CQT2 additional survey by wubin 2015.03.21
		--if (pRole:GetLevel() >= 15 and pRole:GetVariable(156) < 1) then
		--	pRole:Say(pRole:GetObjID(), cltUrl, "Welcome to take survey:‘http://wenjuan.sdo.com:9091/survey/survey?surveyId=8292’");
		--	pRole:SetVariable(156, 1);
		--end
		--------CQT2 additional survey end

		if (free_slot_count < p.maxitemcount) then
			return errItemBagFull;
		end

		if (p.checkvariable and p.waittime) then
			if (pRole:GetTotalOnlineTime() - pRole:GetVariable(p.checkvariable) < p.waittime) then
				return errItemOpenPackageEarly;
			end
		end

		if (p.opentimesvariable and p.maxopentimes) then
			local open_times = pRole:GetVariable(p.opentimesvariable);
			if (open_times >= p.maxopentimes) then
				return errItemOpenPackageTooMany;
			else
				pRole:SetVariable(p.opentimesvariable, open_times+1);
			end
		end
		
		for _,v in ipairs(p) do
			if type(v) == 'table' then
				_award(v, class, sex, itembag, pRole, itemid);
			end
		end

		return errSuccess;

	end
end
