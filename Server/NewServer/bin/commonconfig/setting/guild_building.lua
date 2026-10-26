guild_building_define = {
	owner='陈凯',
	ID = {
		type = 'number',
		default = 0,
		min = 1,
		max = 15,
	},
	Name = {
		type = 'string'
		default = "Default",
		maxlen = 256,
	},
	Level = {
		type = 'number',
		default = 0,
		min = 1,
		max = 6,
	},
	MaxLevel = {
		type = 'number',
		default = 0,
		min = 1,
	},
	MoneyConsumption = {  -- 升级金钱消耗
		type = 'number',
		default = 0,
		min = 0,
	},
	HerbConsumption = { -- 升级草药消耗
		type = 'number',
		default = 0,
		min = 0,
	},
	WoodConsumption = {  -- 升级木材消耗
		type = 'number',
		default = 0,
		min = 0,
	},
	CrystalConsumption = {  -- 升级水晶消耗
		type = 'number',
		default = 0,
		min = 0,
	},
	SilverConsumption = {  -- 升级秘银消耗
		type = 'number',
		default = 0,
		min = 0,
	},
	UpgradeTime = {	-- 升级需要时间， 单位：秒
		type = 'number',
		default = 0,
		min = 0,
	},
	RoutineConsumption = {	-- 日常消耗， 每小时消耗家族资金
		type = 'number',
		default = 0,
		min = 0,
	},
	ConditionBuildingID = {	-- 升级前置公会建筑ID
		type = 'link',
		default = 0,
		refertable = 'guild_building',
		referfield = 'ID',
	},
	ConditionBuildingLvl = {	-- 升级前置公会建筑等级
		type = 'link',
		default = 0,
		refertable = 'guild_building',
		referfield = 'Level',
	},
	UpgradeSpellID = {		-- 升级后，建筑npc对自己释放的spell id
		type = 'link',
		default = 0,
		refertable = 'spell',
		referfield = 'ID',
	},
	Param1 = {		-- 策划自定义
		type = 'number',
		default = 0,
		min = 0,
	},
	Param2 = {
		type = 'number',
		default = 0,
		min = 0,
	},
	Param3 = {
		type = 'number',
		default = 0,
		min = 0,
	},
	Param4 = {
		type = 'number',
		default = 0,
		min = 0,
	},
	Effect = {
		type = 'number',
		default = 0,
		min = 0,
	},
	Description = {
		type = 'string'
		default = "Default",
		maxlen = 256,
	},

}
