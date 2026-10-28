LoadPackage("char_def.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("character.pkg")
LoadPackage("role.pkg")
LoadPackage("npc.pkg")

--Sacred beast
--Include("script/newai/sub_tree/sub_tree.lh")
Include("script/newai/sub_tree/pet_sub_tree.lua")

-- spell, aura, last time
local 	TRANSFORM_TO_DOG_AURA_ID = 60520;
local 	TRANSFORM_TO_DOG_SPELL_ID = 6052;
local 	TRANSFORM_TO_DOG_PERFORMANCE_TIME = 1063;

local 	TRANSFORM_TO_MAN_WAIT_TIME = 60000;
local 	TRANSFORM_TO_MAN_SPELL_ID = 6047;
local 	TRANSFORM_TO_MAN_PERFORMANCE_TIME = 1750;

local 	MAGE_PET_VIOLENT_SPELL_ID = 25411;

local   HOLY_PET_HP_AURA_ID = 60461;

-- cd
local 	PET_TRANSFORM_TO_IDLE_STATE_CD = nastCustom;



on_pet_detect=
{ batSelector,
	{ batCheckAura, param = { tarSelf, TRANSFORM_TO_DOG_AURA_ID} },
	{ batSequencer,
		{ batAddAura, param = { tarSelf, HOLY_PET_HP_AURA_ID} },
		{ batCastSpellToTarget, param = { TRANSFORM_TO_DOG_SPELL_ID, tarSelf} },
		{ batSetCDTimer, param = { COOLDOWN_AI, PET_TRANSFORM_TO_IDLE_STATE_CD, TRANSFORM_TO_MAN_WAIT_TIME} },
	},
};

on_pet_enter_idle =
{ batParallel,
	{ batSetCDTimer, param = { COOLDOWN_AI, PET_TRANSFORM_TO_IDLE_STATE_CD, TRANSFORM_TO_MAN_WAIT_TIME} },
};


on_pet_idle =
{ batSequencer,
	{ batCheckAura, param = { tarSelf, TRANSFORM_TO_DOG_AURA_ID} },
	{ batCheckCDTimer, param = { COOLDOWN_AI, PET_TRANSFORM_TO_IDLE_STATE_CD } },
	{ batParallel,
		{ batSequencer,
			{ batCheckAura, param = { tarSelf, HOLY_PET_HP_AURA_ID} },
			{ batReduceAura, param = { tarSelf, HOLY_PET_HP_AURA_ID, 1} },
		},
	},
	{ batCastSpellToTarget, param = {TRANSFORM_TO_MAN_SPELL_ID, tarSelf}},
};


on_pet_cast_spell = _cast_all_spell();

evtAIInit = _pet_init_tree();
evtAIIdle = _pet_idle_tree();
evtAIFight = _pet_fight_tree();

Include("script/newai/pet/main.uh")
