LoadPackage("char_def.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("character.pkg")
LoadPackage("role.pkg")
LoadPackage("npc.pkg")

--灵兽
--Include("script/newai/sub_tree/sub_tree.lh")
Include("script/newai/sub_tree/pet_sub_tree.lua")

-- spell, aura, last time
local 	TRANSFORM_TO_DOG_AURA_ID = 60610;  -- 灵兽变化
local 	TRANSFORM_TO_DOG_SPELL_ID = 6061;  -- [神兽(灵兽印)]进入战斗
local 	TRANSFORM_TO_DOG_PERFORMANCE_TIME = 1063;

local 	TRANSFORM_TO_MAN_WAIT_TIME = 60000;
local 	TRANSFORM_TO_MAN_SPELL_ID = 6047;   -- [神兽(通用)]退出战斗
local 	TRANSFORM_TO_MAN_PERFORMANCE_TIME = 1750;

local 	MAGE_PET_VIOLENT_SPELL_ID = 25411;  -- 诱惑成功的特效 (VIOLENT, 暴击?)

local   HOLY_PET_HP_AURA_ID = 60461;  -- 神兽(通用)属性变化

-- cd
local 	PET_TRANSFORM_TO_IDLE_STATE_CD = nastCustom;  -- PET转换为空闲状态CD


-- 发现目标
on_pet_detect=
{ batSelector,
	{ batCheckAura, param = { tarSelf, TRANSFORM_TO_DOG_AURA_ID} },
	{ batSequencer,
		{ batAddAura, param = { tarSelf, HOLY_PET_HP_AURA_ID} },
		{ batCastSpellToTarget, param = { TRANSFORM_TO_DOG_SPELL_ID, tarSelf} },
		{ batSetCDTimer, param = { COOLDOWN_AI, PET_TRANSFORM_TO_IDLE_STATE_CD, TRANSFORM_TO_MAN_WAIT_TIME} },
	},
};

-- 进入空闲状态
on_pet_enter_idle =
{ batParallel,
	{ batSetCDTimer, param = { COOLDOWN_AI, PET_TRANSFORM_TO_IDLE_STATE_CD, TRANSFORM_TO_MAN_WAIT_TIME} },
};

-- 空闲状态
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
