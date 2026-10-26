
npc_affix_define = {
	owner='高华翔',
	ID = {
		type = 'number',
		default = 0,
		min = 0,
	},
	LevelLow = {
		type = 'number',
		default = 0,
		min = 1,
	},
	LevelHigh = {
		type = 'number',
		default = 0,
		min = 1,
	},
	AffixID = {
		type = 'link',
		default = 0,
		refertable = 'affix',
		referfield = 'AffixID',
	},
}
