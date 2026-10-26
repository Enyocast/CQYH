
GS_COMMAND = 1;
MS_COMMAND = 2;

command_table = {
	speed = {
		GS_COMMAND,
		10,
		"SetSpeed"
	},
	jump = {
		GS_COMMAND,
		5,
		"Jump"
	},
	take = {
		GS_COMMAND,
		10,
		"TakeRole"
	},
	transfer = {
		GS_COMMAND,
		10,
		"TransferRole"
	},
	hide = {
		GS_COMMAND,
		10,
		"Hide"
	},
	god = {
		GS_COMMAND,
		10,
		"God"
	},
	recover = {
		GS_COMMAND,
		10,
		"Recover"
	},
	revive = {
		GS_COMMAND,
		10,
		"Revive"
	},
	summonnpc = {
		GS_COMMAND,
		20,
		"SummonNpc"
	},
	kill = {
		GS_COMMAND,
		20,
		"Kill"
	},
	summondoodad = {
		GS_COMMAND,
		20,
		"SummonDoodad"
	},
	kick = {
		MS_COMMAND,
		10,
		"Kick"
	},
	kickall = {
		MS_COMMAND,
		30,
		"KickAll"
	},
	switch = {
		MS_COMMAND,
		40,
		"Switch"
	},
	accept = {
		GS_COMMAND,
		20,
		"AcceptQuest"
	},
	complete = {
		GS_COMMAND,
		20,
		"CompleteQuest"
	},
	abandon = {
		GS_COMMAND,
		20,
		"AbandonQuest"
	},
	createguild = {
		MS_COMMAND,
		20,
		"CreateGuild"
	},
	joinguild = {
		MS_COMMAND,
		20,
		"JoinGuild"
	},
	leaveguild = {
		MS_COMMAND,
		20,
		"LeaveGuild"
	},
	setguildposition = {
		MS_COMMAND,
		20,
		"SetGuildPosition"
	},
	deleteguild = {
		MS_COMMAND,
		20,
		"DelGuild"
	},
	addguildfund = {
		MS_COMMAND,
		20,
		"AddGuildFund"
	},
	delallenemy = {
		MS_COMMAND,
		20,
		"DelAllEnemy"
	},
	delguildalliance = {
		MS_COMMAND,
		20,
		"DelAllAlliance"
	},
	addmasterrelation = {
		MS_COMMAND,
		20,
		"AddMasterRelation"
	},
	delmasterrelation = {
		MS_COMMAND,
		20,
		"DelMasterRelation"
	},
	bemaster = {
		MS_COMMAND,
		20,
		"BeMaster"
	},
	announce = {
		MS_COMMAND,
		20,
		"Announce"
	},
	lighting = {
		MS_COMMAND,
		20,
		"AnnounceLighting"
	},
	tvshow = {
		MS_COMMAND,
		20,
		"AnnounceTvShow"
	},
	trumpet = {
		MS_COMMAND,
		20,
		"AnnounceTrumpet"
	},
	addtitle = {
		GS_COMMAND,
		20,
		"AddTitle"
	},
	deltitle = {
		GS_COMMAND,
		20,
		"DelTitle"
	},
	additem = {
		GS_COMMAND,
		30,
		"AddItem"
	},
	me = {
		GS_COMMAND,
		10,
		"SelfInfo"
	},
	finfo = {
		GS_COMMAND,
		10,
		"FocusInfo"
	},
	-- sinfo = {
		-- MS_COMMAND + GS_COMMAND,
		-- 10,
		-- "SceneInfo"
	-- },
	gm = {
		GS_COMMAND,
		40,
		"GMLevel"
	},
	level = {
		GS_COMMAND,
		30,
		"Level"
	},
	addmoney = {
		GS_COMMAND,
		30,
		"AddMoney"
	},
	addmasterexp = {
		GS_COMMAND,
		30,
		"AddMasterExp"
	},
	addguildexp = {
		GS_COMMAND,
		30,
		"AddGuildExp"
	},
	addmoralvalue = {
		GS_COMMAND,
		30,
		"AddMoralValue"
	},
	addavpts = {
		GS_COMMAND,
		30,
		"AddAchievementPts"
	},
	givemoney = {
		GS_COMMAND,
		30,
		"GiveMoney"
	},
	givemasterexp = {
		GS_COMMAND,
		30,
		"GiveMasterExp"
	},
	giveguildexp = {
		GS_COMMAND,
		30,
		"GiveGuildExp"
	},
	givemoralvalue = {
		GS_COMMAND,
		30,
		"GiveMoralValue"
	},
	giveavpts = {
		GS_COMMAND,
		30,
		"GiveAchievementPts"
	},
	spiritlevel = {
		GS_COMMAND,
		30,
		"SetSpiritLevel"
	},
	droprate = {
		MS_COMMAND,
		40,
		"SetDropRate"
	},
	exprate = {
		MS_COMMAND,
		40,
		"SetExpRate"
	},
	spellpts = {
		GS_COMMAND,
		30,
		"AddSpellPts"
	},
	exp = {
		GS_COMMAND,
		30,
		"AddExp"
	},
	arrest = {
		MS_COMMAND,
		20,
		"Arrest"
	},
	clearredname = {
		GS_COMMAND,
		30,
		"ClearRedName"
	},
	rolecount = {
		MS_COMMAND,
		30,
		"RoleCount"
	},
	iprolecount = {
		MS_COMMAND,
		30,
		"IPRoleCount"
	},
	arresttime = {
		GS_COMMAND,
		30,
		"ArrestTime"
	},
	delspell = {
		GS_COMMAND,
		30,
		"DelSpell"
	},
	setrune = {
		GS_COMMAND,
		30,
		"SetRune"
	},
	enrollsabac = {
		MS_COMMAND,
		40,
		"EnrollSabac"
	},
	startdate = {
		GS_COMMAND,
		10,
		"StartDate"
	},
	deletenpc = {
		GS_COMMAND,
		30,
		"DeleteNpc",
	},
	collectlognow= {
		MS_COMMAND,
		40,
		"CollectLogNow",
	},
	gpk = {
		MS_COMMAND,
		40,
		"EnableGPKPunish",
	},
	cligpk = {
		GS_COMMAND,
		40,
		"EnableClientGPK",
	},
	gpkcatchlimit = {
		MS_COMMAND,
		40,
		"GPKCatchLimit",
	},
	gpkdelaylimit = {
		MS_COMMAND,
		40,
		"GPKDelayLimit",
	},
	gamble = {
		GS_COMMAND,
		40,
		"SetNextGambleID",
	},
	gettotalgamblecount = {
		GS_COMMAND,
		40,
		"GetTotalGambleCount",
	},
	getgamblecount = {
		GS_COMMAND,
		40,
		"GetGambleCount",
	},
	setgamblecount = {
		GS_COMMAND,
		100,
		"SetGambleCount",
	},
	getworldgamblecount = {
		MS_COMMAND,
		40,
		"GetWorldGambleCount",
	},
	setworldgamblecount = {
		MS_COMMAND,
		100,
		"SetWorldGambleCount",
	},
	rankaward = {
		MS_COMMAND,
		40,
		"SendRankListAward",
	},
	arenaopen = {
		MS_COMMAND,
		40,
		"ArenaOpen",
	},
	arenaclose = {
		MS_COMMAND,
		40,
		"ArenaClose",
	},
	addarenascore = {
		GS_COMMAND,
		40,
		"AddArenaScore",
	},
	addarenamoney = {
		GS_COMMAND,
		40,
		"AddArenaMoney",
	},

	addactivitypts = {
		GS_COMMAND,
		40,
		"AddActivityPts"
	},
	guildwaropen = {
		MS_COMMAND,
		40,
		"GuildWarOpen",
	},
	guildwarclose = {
		MS_COMMAND,
		40,
		"GuildWarClose",
	},
	ver = {
		GS_COMMAND,
		5,
		"Version",
	},
	mingwen = {
		GS_COMMAND,
		10,
		"MingWen"
	},
	xingyun = {
		GS_COMMAND,
		10,
		"XingYun"
	},
	qianghua = {
		GS_COMMAND,
		10,
		"QiangHua"
	},
	lvzi = {
		GS_COMMAND,
		10,
		"LvZi"
	},
	dakong = {
		GS_COMMAND,
		10,
		"DaKong"
	},
};

command_table['加速'] = command_table.speed;
command_table['跳转'] = command_table.jump;
command_table['拉人'] = command_table.take;
command_table['传人'] = command_table.transfer;
command_table['隐身'] = command_table.hide;
command_table['无敌'] = command_table.god;
command_table['满状态'] = command_table.recover;
command_table['复活'] = command_table.revive;
command_table['召怪'] = command_table.summonnpc;
command_table['秒杀'] = command_table.kill;
command_table['召物'] = command_table.summondoodad;
command_table['踢人'] = command_table.kick;
command_table['踢所有人'] = command_table.kickall;
command_table['设置服务器开关'] = command_table.switch;
command_table['接受任务'] = command_table.accept;
command_table['完成任务'] = command_table.complete;
command_table['放弃任务'] = command_table.abandon;
command_table['创建工会'] = command_table.createguild;
command_table['逐出公会'] = command_table.leaveguild;
command_table['加入工会'] = command_table.joinguild;
command_table["删除公会"] = command_table.deleteguild;
command_table["变更公会职位"] = command_table.setguildposition;
command_table["公会资源"] = command_table.addguildfund;
command_table["添加徒弟"] = command_table.addmasterrelation;
command_table["删除徒弟"] = command_table.delmasterrelation;
command_table['发公告'] = command_table.announce;
command_table['走马灯'] = command_table.lighting;
command_table['电视机'] = command_table.tvshow;
command_table['小喇叭'] = command_table.trumpet;
command_table['添加称号'] = command_table.addtitle;
command_table['删除称号'] = command_table.deltitle;
command_table['制造'] = command_table.additem;
command_table['自己信息'] = command_table.me;
command_table['角色信息'] = command_table.finfo;
command_table['场景信息'] = command_table.sinfo;
command_table['GM权限'] = command_table.gm;
command_table['升级'] = command_table.level;
command_table['加钱'] = command_table.addmoney;
command_table['加名师值'] = command_table.addmasterexp;
command_table['加公会贡献'] = command_table.addguildexp;
command_table['加道义值'] = command_table.addmoralvalue;
command_table['加成就点'] = command_table.addavpts;
command_table['给钱'] = command_table.givemoney;
command_table['给名师值'] = command_table.givemasterxp;
command_table['给公会贡献'] = command_table.giveguildexp;
command_table['给道义值'] = command_table.givemoralvalue;
command_table['给成就点'] = command_table.giveavpts;
command_table['升级境界'] = command_table.spiritlevel;
command_table['多倍爆率'] = command_table.droprate;
command_table['多倍经验'] = command_table.exprate;
command_table['增加技能点'] = command_table.spellpts;
command_table['增加经验'] = command_table.exp;
command_table['囚禁'] = command_table.arrest;
command_table['增加铭文'] = command_table.setrune;

command_table['洗红名'] = command_table.clearredname;
command_table['在线人数'] = command_table.rolecount;
command_table['查询ip人数'] = command_table.iprolecount;
command_table['查看囚禁时间'] = command_table.arresttime;
command_table['删除技能'] = command_table.delspell;
command_table['报名沙巴克'] = command_table.enrollsabac;
command_table['开服时间'] = command_table.startdate;
command_table['删除NPC'] = command_table.DeleteNpc;
command_table['生成汇总数据'] = command_table.CollectLogNow;
command_table['下次赌博'] = command_table.gamble;
command_table['监狱人数修改'] = command_table.gpkcatchlimit;
command_table['监狱队列修改'] = command_table.gpkdelaylimit;
command_table['查询重铸总次数'] = command_table.gettotalgamblecount;
command_table['查询重铸次数'] = command_table.getgamblecount;
command_table['设置重铸次数'] = command_table.setgamblecount;
command_table['查询世界重铸次数'] = command_table.getworldgamblecount;
command_table['设置世界重铸次数'] = command_table.setworldgamblecount;
command_table['排行榜玩家发奖'] = command_table.rankaward;
command_table['开启竞技场'] = command_table.arenaopen;
command_table['关闭竞技场'] = command_table.arenaclose;
command_table['增加擂台币'] = command_table.addarenamoney;
command_table['增加擂台积分'] = command_table.addarenascore;
command_table['开启公会战'] = command_table.guildwaropen;
command_table['关闭公会战'] = command_table.guildwarclose;
