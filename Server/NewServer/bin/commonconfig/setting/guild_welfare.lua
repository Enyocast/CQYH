guild_welfare_define = {
	owner='陈凯',
	ID = {
		type = 'number',
		default = 0,
		min = 1,
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
	},
	AuraID = {			-- 购买的buffer id
		type = 'link',
		default = 0,
		refertable = 'aura',
		referfield = 'ID',
	},
	Kind = {  			-- 福利buffer所属的组
		type = 'number',
		default = 0,
		min = 0,
	},
	MaxLevel = { 		--
		type = 'number',
		default = 0,
		min = 0,
	},
	UpgradeTime = {		-- 升级需要时间， 单位：秒
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
	PurchaseLevelRequirement = {  	-- 兑换buffer的角色等级需求
		type = 'number',
		default = 0,
		min = 0,
	},
	PurchaseMoneyConsumption = {  -- 兑换buffer的角色金钱需求
		type = 'number',
		default = 0,
		min = 0,
	},
	PurchaseGuildCurrencyConsumption = {  -- 兑换buffer的家族贡献需求
		type = 'number',
		default = 0,
		min = 0,
	},
	PurchaseLimit = {  			-- 兑换次数限制
		type = 'number',
		default = 0,
		min = 0,
	},
	UpgradeMoneyConsumption = {  -- 升级金钱消耗
		type = 'number',
		default = 0,
		min = 0,
	},
	UpgradeHerbConsumption = { -- 升级草药消耗
		type = 'number',
		default = 0,
		min = 0,
	},
	UpgradeWoodConsumption = {  -- 升级木材消耗
		type = 'number',
		default = 0,
		min = 0,
	},
	UpgradeCrystalConsumption = {  -- 升级水晶消耗
		type = 'number',
		default = 0,
		min = 0,
	},
	UpgradeSilverConsumption = {  -- 升级秘银消耗
		type = 'number',
		default = 0,
		min = 0,
	},

}
