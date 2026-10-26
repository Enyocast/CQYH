
item_define = {
	owner='谭勇',
	ID = {
		type = 'number',
		default = 0,
		min = 0,
	},
	Type = {								-- 	物品种类，最多有11种,ITEMTYPE_TOTAL
		type = 'number',
		default = 0,
		min = 0,
		max = 11,
	},
	SubType = {								--  物品种类，最多有15种,ITEMSUBTYPE_EQUIP_AVATAR最大
		type = 'number',
		default = 0,
		min = 0,
		max = 15,
	},
	RequireLevel = {
		type = 'number',
		default = 0,
		min = 0,
	},
	RequireClass = {
		type = 'number',
		default = 0,
		min = 0,
		max = 15,
	},
	RequireGender = {						--  性别，最多有3种,cstTotal最大
		type = 'number',
		default = 0,
		min = 0,
		max = 3,
	},
	MaxEquip = {
		type = 'number',
		default = 0,
		min = 0,
	},
	MaxOwn = {
		type = 'number',
		default = 0,
		min = 0,
		max = 99999,
	},
	Color = {								--  颜色，最多有7种,ITEMCOLOR_TOTAL最大
		type = 'number',
		default = 0,
		min = 0,
		max = 7,
	},
	BindType = {
		type = 'number',
		default = 0,
		min = 0,
		max = 10,
	},
	DurType = {								-- 持久度类型，最多有3种,DURTYPE_USE最大
		type = 'number',
		default = 0,
		min = 0,
		max = 3,
	},
	Dur = {
		type = 'number',
		default = 0,
		min = 0,
	},
	Price = {
		type = 'number',
		default = 0,
		min = 0,
	},
	SpellID = {
		type = 'link',
		default = 0,
		refertable = 'spell_var',
		referfield = 'ID',
	},
	SpellLevel = {
		type = 'number',
		default = 0,
		min = 0,
	},
	Script = {
		type = 'string',
		default = "Default",
		maxlen = 256,
	},
	Index = {
		type = 'number',
		default = 0,
		min = 0,
	},
	Name = {
		type = 'string',
		default = "Default",
		maxlen = 256,
	},
	UsedStatus = {
		type = 'number',
		default = 0,
		min = 0,
	},
	Drop = {
		type = 'number',
		default = 0,
		min = 0,
	},
	Storage = {
		type = 'number',
		default = 0,
		min = 0,
	},
	SelfCoolDown = {
		type = 'number',
		default = 0,
		min = 0,
	},
	GroupCoolDown = {
		type = 'number',
		default = 0,
		min = 0,
	},
	DisplayIcon = {
		type = 'string',
	},
	Description = {
		type = 'string',
	},
	DropMesh = {
		type = 'string',
	},
	SoundMaterialType = {
		type = 'string',
	},
	SoundActionType = {
		type = 'string',
	},
	ClothNoiseType = {
		type = 'string',
	},
	ItemLevel = {
		type = 'number',
		default = 0,
		min = 0,
	},
}