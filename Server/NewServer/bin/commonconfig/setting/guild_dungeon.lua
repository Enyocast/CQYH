guild_dungeon_define = {
	owner='陈凯',
	SceneTemplateID = {
		type = 'link',
		default = 0,
		refertable = 'scene',
		referfield = 'SceneID',
	},
	ConditionBuildingLvl = {	-- 开启地下城需求公会战事厅等级
		type = 'link',
		default = 0,
		refertable = 'guild_building',
		referfield = 'Level',
	},
	ConditionMoney = {	-- 需求金币
		type = 'number',
		default = 0,
		min = 1,
		max = 6,
	},
	PosX = {			-- 跳转进副本的x坐标
		type = 'number',
		default = 0,
		min = 1,
	},
	PosY = {  			-- 跳转进副本的Y坐标
		type = 'number',
		default = 0,
		min = 0,
	},
	PosZ = { 			-- 跳转进副本的Z坐标
		type = 'number',
		default = 0,
		min = 0,
	},
	Direction = {  		-- 跳转进副本的朝向,角度
		type = 'number',
		default = 0,
		min = 0,
	},

	for i = 1,8 then		-- 掉落
		guild_dungeon_define['DropChance'..i] = {
			type = 'number',
			default = 0,
			min = 0,
		};
		guild_dungeon_define['DropGroupID'..i] = {
			type = 'number',
			default = 0,
			min = 0,
		};
	end

	BestTeammateNum = {  		-- 副本推荐人数
		type = 'number',
		default = 0,
		min = 0,
	},

	for i = 1,8 then		-- 掉落
		guild_dungeon_define['Award'..i] = {
			type = 'number',
			default = 0,
			min = 0,
		};
	end

}
