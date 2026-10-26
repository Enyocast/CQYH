

-- 1 or nil
TEST_ENVIRONMENT = 1;


MS_GM_COMMAND = 1;
GS_GM_COMMAND = 2;

GM_COMMAND_PERMISSION_LVL_1 = 1;
GM_COMMAND_PERMISSION_LVL_2 = 2;
GM_COMMAND_PERMISSION_LVL_3 = 3;
GM_COMMAND_PERMISSION_LVL_4 = 4;
GM_COMMAND_PERMISSION_LVL_5 = 5;
GM_COMMAND_PERMISSION_LVL_6 = 6;


gm = {
	help = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'gm_help',
		'help [command] : 帮助指令'
	},
	
	
	-- 自己新增加的GM命令 begin
	kick = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'Kick',
		'kick(RoleID): 指定角色ID, 踢下线',
	},
	kickall = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'KickAll',
		'kickall(GroupID) : 指定服务器ID, 全服踢下线',
	},
	additemtorole = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddItemToRole',
		'additemtorole(ItemID,Count,RoleID): 给指定角色[发道具], 参数(物品ID,物品数量,角色ID)',
	},
	addmoneytorole = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddMoneyToRole',
		'addmoneytorole(MoneyType,Amount,RoleID): 给指定角色[增加货币], 参数(货币类型,数量,角色ID)',
	},
	submoneytorole = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SubMoneyToRole',
		'submoneytorole(MoneyType,Amount,RoleID): 给指定角色[扣除货币], 参数(货币类型,数量,角色ID)',
	},
	addexptorole = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'AddExpToRole',
		'addexptorole(n,RoleID) : 给指定角色, 增加n点经验值',
	},
	leveltorole = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetLevelToRole',
		'leveltorole(n,RoleID) : 给指定角色的等级设置为n级',
	},
	completetorole = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'CompleteQuestToRole',
		'completetorole(questID,RoleID) : 给指定角色, 完成指定任务'
	},
	accepttorole = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AcceptQuestToRole',
		'accepttorole(questID,RoleID) : 给指定角色, 接取指定任务',
	},
	learnspelltorole = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'LearnSpellToRole',
		'learnspelltorole(spellID,level,RoleID) : 给指定角色, 学会指定ID和等级的技能',
	},
	removespelltorole = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'RemoveSpellToRole',
		'removespelltorole(spell,RoleID) : 给指定角色, 遗忘指定ID的技能',
	},
	addtitletorole = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddTitleToRole',
		'addtitle(titleID,RoleID) : 给指定角色, 获得指定的称号',
	},
	deltitletorole = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'DeleteTitleToRole',
		'deltitletorole(title,del_type,RoleID) : 给指定角色, 删除指定称号',
	},
	setfreemodetorole = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetFreeModeToRole',
		'setfreemodetorole(byFreeMode,RoleID) : 给指定角色, 设置FreeMode标志, 1=有限制, 0=无限制',
	},
	qfgg = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'qfgg',
		'qfgg(location,message) : 发全服公告',
	},
	-- 自己新增加的GM命令 end
	
	
	-- 默认代码的GM命令
	summonnpc = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'SummonNpc',
		'summonnpc {npc} [level] [{quality}] : 召唤指定名字或模板ID的NPC',
	},
	jump = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'Jump',
		'jump {jump_point} : 跳转到指定的跳转点',
		'jump x y [z] : 跳转到本场景的指定坐标',
		'jump sceneTempID sceneID x y [z] : 跳转到指定副本的指定坐标',
		'jump roleName : 跳转到指定角色处',
		'jump {teleport_id} : 跳转到本场景的指定的场景传送点',
	},
	kill = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'Kill',
		'kill char_id : 杀死指定ID的角色（包含玩家和NPC）',
	},
	killallnpc = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'KillAllNpc',
		'KillAllNpc : 杀死场景内所有npc',
	},
	suicide = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'Suicide',
		'suicide : 自杀'
	},
	revive = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'Revive',
		'revive : 复活当前角色',
	},
	addexp = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'AddExp',
		'addexp n : 增加n点经验值',
	},
	learnspell = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'LearnSpell',
		'learnspell {spell} level : 学会指定ID和等级的技能',
	},
	forgetspell = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'RemoveSpell',
		'forgetspell {spell} : 遗忘指定ID的技能',
	},
	additem = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddItem',
		'additem {item} count : 获得指定ID和叠加数量的道具',
	},
	refine = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetRefineLevel',
		'refine slot level : 将slot部位的强化等级设为level',
	},
	addmoney = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddMoney',
		'addmoney {money} amount : 增加指定类型的货币',
	},
	submoney = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SubMoney',
		'submoney {money} amount : 增加指定类型的货币',
	},
	setmoney = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetMoney',
		'setmoney {money} amount : 将指定类型的货币设置为指定数量',
	},
	addmasterexp = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddMasterExp',
		'AddMasterExp count : 增加指定数量的名师值',
	},
	goldpool = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'PrintGoldPool',
		'goldpool : 显示金币池数据',
	},
	add_ability_pts = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddAbilityPts',
		'add_ability_pts n : 获得n点技能点数',
	},
	reputation = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetReputation',
		'reputation force value : 将当前角色的指定声望设置为指定值',
	},
	speed = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'SetSpeed',
		'speed v : 将当前角色的速度设置为指定值',
	},
	level = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetLevel',
		'level n : 当前角色的等级设置为n级',
	},
	fullhp = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'FullHp',
		'fullhp : 当前角色血量全满',
	},
	fullmp = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'FullMp',
		'fullmp : 当前角色能量全满',
	},
	sethp = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetHp',
		'sethp n : 将当前角色的血量设为n',
	},
	cd = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'EnableCD',
		'cd enabled : 当前角色CD计时器是否有效',
	},

	debugline = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'DrawDebugLine',
		'debugline draw : 当前角色CD计时器是否有效',
	},

	door = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'ToggleDoor',
		'door id : 翻转第id号门',
	},
	summondoodad = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SummonDoodad',
		'doodad {doodad} : 生成指定ID的Doodad',
	},
	god = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'God',
		'god disabled : 设置无敌状态',
	},
	pk = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'PkMode',
		'pk {pkmode} : 设置Pk模式',
	},
	dis = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'Distance',
		'dis : 显示和焦点的x和y轴距离',
	},
	complete = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'CompleteQuest',
		'complete {quest} : 完成指定任务'
	},
	accept = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AcceptQuest',
		'accept {quest} : 接取指定任务',
	},
	printfocus = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'PrintFocus',
		'printfocus : 显示焦点的主要角色属性',
	},
	addtitle = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddTitle',
		'addtitle {title} : 获得指定的称号',
	},
	deltitle = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'DeleteTitle',
		'deltitle {title} del_type : 删除指定称号',
	},
	equiptitle = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'EquipTitle',
		'equiptitle {title} : 装备指定的称号',
	},
	unequiptitle = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'UnEquipTitle',
		'unequiptitle : 卸下指定的称号',
	},
	equiprune = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'EquipRune',
		'equiprune	{spell} rune_slot : 装备符文',
	},
	complete_av = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'CompleteAchievement',
		'complete_av {av} : 完成指定的成就',
	},
	pkvalue = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetPkValue',
		'pkvalue value : 设置Pk值',
	},
	setqv = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetQV',
		'setqv {quest} var_index value : 设置任务变量'
	},
	power = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'Power',
		'power : 提升攻击力、防御力、移动速度',
	},
	hire = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'HireHero',
		'hire level class sex : 雇佣指定等级、职业、性别的英雄',
	},
	heroai = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetHeroAi',
		'heroai {hero_ai} : 设置当前英雄的AI类型',
	},
	testbt = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'TestBT',
		'testbt {bt_action} [p0] [p1] [p2] [p3] : 测试bt action 功能',
	},
	weather = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'Weather',
		'weather {weather} duration : 改变当前场景的天气',
	},
	vip = {
	    GS_GM_COMMAND,
	    GM_COMMAND_PERMISSION_LVL_1,
	    'VIP',
	    'vip month : 订阅VIP功能',
	},
	dropmax = {
	    GS_GM_COMMAND,
	    GM_COMMAND_PERMISSION_LVL_1,
	    'DropMax',
	    'dropmax: 当前场景所在的GS，开关掉率100%',
	},
	droprate = {
	    GS_GM_COMMAND,
	    GM_COMMAND_PERMISSION_LVL_1,
	    'DropRate',
	    'droprate {倍率} : 查看或设置当前场景所在的GS物品掉率 (万分比)',
	},
	exprate = {
	    GS_GM_COMMAND,
	    GM_COMMAND_PERMISSION_LVL_1,
	    'ExpRate',
	    'exprate {倍率} : 查看或设置当前场景所在的经验值倍率 (万分比)',
	},
	addgmoney = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddGuildMoney',
		'AddGuildMoney :  参数一：帮派名。 参数二：货币类型(GUILD_ATTR_ENUM:GUILD_ATTR_MONEY, GUILD_ATTR_WOOD, GUILD_ATTR_HERB, GUILD_ATTR_CRYSTAL, GUILD_ATTR_SILVER)， 参数三：增加帮派资源',
	},
	addspiritpts  = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddSpiritPts',
		'AddSpiritPts:  参数：需要增加的修炼点',
	},
	setspiritairlevel  = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetSpiritAirLevel',
		'SetSpiritAirLevel:  参数：炼气等级',
	},
	setspiritlevel  = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetSpiritLevel',
		'SetSpiritLevel:  参数：境界等级',
	},
	addguildsalary = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddGuildSalary',
		'AddGuildSalary :  参数一：帮派名。 参数二：角色名， 参数三：数量',
	},
	finfo = {
	    GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
	    'FocusInfo',
	    'finfo : 显示目标信息',
	},
	-- sinfo = {
	    -- GS_GM_COMMAND,
		-- GM_COMMAND_PERMISSION_LVL_1,
	    -- 'SceneInfo',
	    -- 'sinfo : 显示当前场景信息',
	-- },
	me = {
	    GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
	    'SelfInfo',
	    'me : 显示自身的信息',
	},
	take = {
	    GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
	    'TakeRole',
	    'take [name] : 将指定名字的玩家拉到自己身边',
	},
	option = {
	    GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
	    'SetOption',
	    'option [option_name] : 切换指定的调试开关',
	},
	arenabegin = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'BroadcastArenaBegin',
		'braoad cast to ntf client, arena begin'
	},
	clearguildcd = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'ClearRoleGuildCD',
		'clear role guild cd',
	},
	clearmastercd = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'ClearMasterCD',
		'clear role master cd',
	},
	beginguildwar = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'BeginGuildWar',
		'begin guild war at once',
	},
	sync = {
	    GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
	    'Sync',
	    'sync : 强制同步坐标',
	},
	extraexp = {
	    GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
	    'AddExtraExp',
	    'extraexp : 增加额外经验值',
	},
	callpet = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
	    'CallPet',
	    'callpet : 召唤召唤兽',
	},
	addpetexp = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddPetExp',
		'AddPetExp:增加所有召唤兽经验',
	},
	changepetstate = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'ChangePetState',
		'changepetstate:改变宠物状态，休息or战斗',
	},
	jumpguildmap = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'JumpToGuildMap',
		'jumpguildmap:跳转到公会属地, 参数 llx，lly，llz',
	},
	msg = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'SetMsg',
		'msg id [state]',
	},
	arrest = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'Arrest',
		'arrest name duration 逮捕指定名字的玩家若干秒',
	},
	hide = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'Hide',
		'hide 隐身或现身',
	},
	occupysabac = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'OccupySabac',
		'occupysabac 占领沙巴克',
	},
	exercise = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'AddExerciseTime',
		'exercise 历练点',
	},
	testgpk = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'TestGpk',
		'TestGpk :  name',
	},
	arenaopen = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'ArenaOpen',
		'可以开启1v1',
	},
	arenaclose = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'ArenaClose',
		'不可开启1v1',
	},
	arenabegin = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'ArenaBegin',
		'1v1开启',
	},
	arenaend = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'ArenaEnd',
		'1v1结束',
	},
	arenarewardbegin = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'ArenaRewardBegin',
		'1v1领奖开始',
	},
	arenarewardend = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'ArenaRewardEnd',
		'1v1领奖结束',
	},
	upguild = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'UpGuild',
		'升级公会建筑，参数：公会名，等级',
	},
	guildwaropen = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'GuildWarOpen',
		'可以开启公会战',
	},
	guildwarclose = {
		MS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_1,
		'GuildWarClose',
		'不可以开启公会战',
	},
	mingwen = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'MingWen',
		'mingwen {runeid1} runeid2 :  将当前装备的武器附上铭文',
	},
	xingyun = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'XingYun',
		'xingyun v : 将当前装备的武器附上幸运',
	},
	qianghua = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'QiangHua',
		'qianghua {class} v : 将当前装备的武器附上强化',
	},
	lvzi = {
		GS_GM_COMMAND,
		GM_COMMAND_PERMISSION_LVL_4,
		'LvZi',
		'lvzi {class} v : 将当前装备的武器附上绿字',
	},
};


