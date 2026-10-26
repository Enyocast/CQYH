LoadPackage("char_def.pkg")
LoadPackage("scene.pkg")
LoadPackage("data_manager.pkg")
LoadPackage("attr_list.pkg")
Include("script/include/btnod.lua")
Include("script/newai/sub_tree/sub_tree.lh")

LoadPackage("gameworld.pkg")
LoadPackage("character.pkg")
LoadPackage("npc.pkg")
LoadPackage("id_def.pkg")

--
local 	PET_ENTER_IDLE_GRID_NUM = 19;
local 	PET_JUMP_TO_HOST_GRID_NUM	= 20;
local 	CM_PER_GRID	= GRID_WIDTH / POINT_PER_CM;

local 	PET_CHASE_TIME = 8000;
local   WANDER_CHANCE = 9500;
local 	PET_INTERESTING_TIME = 30000;


-- cd index
local nastPetChaseTimer = nastCustom + 1;
local nastPetFightTimer = nastCustom + 2;
local nastPetLoseInterestingTimer = nastCustom + 3;

--
local PET_NONE  = 0;
local PET_IDLE  = 1;
local PET_FIGHT = 2;
local PET_CHASE = 3;

--
on_pet_enter_idle = { batParallel };
on_pet_idle = { batSequencer };
on_pet_detect = { batSequencer };

on_pet_cast_spell = { batSequencer };
_pet_init_aura = { batSequencer };
--

local pet_set_follow_param = { batSetFollowParam, param = { 0, 0, -256, 0} };

local pet_wander =
{ batParallel,
	{ batSequencer,
		{ batCheckDice, param = { boGT, WANDER_CHANCE} },
		{ batPetWander, param = { d.nWanderRange, d.nWanderInterval } },
	},
};


local pet_follow =
{ batSelector,
	{ batNot,
		{ batCheckCanMove, },
	},
	{ batNot,
		{ batPetCheckRoleState, },
	},
	{ batSequencer,
		{ batCheckDistance, param = { tarHost, boLTE, d.nWanderRange} },
		--{ batSetAIVariable, param = { PET_AI_GO_HOME, 0 } },
		{ batPetCheckHostDirection, },
		pet_wander,
	},
	{ batSequencer,
		{ batCheckDistance, param = { tarHost, boLT, PET_JUMP_TO_HOST_GRID_NUM * CM_PER_GRID} },
		--{ batCheckCanMove, },
		{ batPetFollow, param = { d.nWalkSpeed * 1000 / GAME_FPS } },
	},

	{ batSequencer,
		{ batCheckDistance, param = { tarHost, boGT, PET_JUMP_TO_HOST_GRID_NUM * CM_PER_GRID} },
		--{ batCheckCanMove, },
		{ batSelector,
			{ batJumpToHost, },
			{ batSuicide, param = { false, false } },	-- 跳地图失败，就去死
		},
	},
};


local check_pet_state =
{ batSelector,
	{ batCheckAIVariable, param = { boEQ, PET_AI_CONTROL, psIdle} },

	{ batNot,
		{ batParallel,
			{ batSequencer,
				{ batCheckAIVariable, param = { boEQ, PET_AI_IS_EXTRA_WALK, 1} },
				{ batSetAIVariable, param = {PET_AI_IS_EXTRA_WALK, 0} },
				pet_follow,
			},
		},

	},
};

local check_live_time =
{ batSequencer,
	{ batCheckCDTimer, param = { COOLDOWN_AI, nastLiveTimer } },
	{ batSelector,
		'on_live_timer',
		{ batSuicide, param = { false, false } },
	},
};


-- idle tree

function CheckTargetIsPet(owner)
	local processor = owner:GetAIProcessor();
	local npc = tolua.cast(processor:GetOwner(), 'CNpc');

	local targetid = processor:GetTargetID();
	local tarobj = CGameWorld:GetInstance():FindValidCharacter(targetid);
	if tarobj ~= nil then
		if tarobj:GetHostID() == 0 then
			return brvSuccess;
		end

		if GetTypeFromID(tarobj:GetHostID()) == otRole then
			local host = CGameWorld:GetInstance():FindValidCharacter(npc:GetHostID());
			local tarHost = CGameWorld:GetInstance():FindValidCharacter(tarobj:GetHostID());
			if host:GetLastCasterID() == targetid or host:GetLastTargetID() == targetid then

				return brvSuccess;
			end
		else
			return brvSuccess;
		end
	end

	return brvFail;
end

-- 发现敌人
local pet_detect_enemy =
{ batSequencer,
	{ batPetScanEnemy, param = { 60, 700, 64 } },
	--{ CheckTargetIsPet },
	{ batParallel,
		{ batSetCDTimer, param = {COOLDOWN_AI, nastPetLoseInterestingTimer, PET_INTERESTING_TIME} },
		'on_pet_detect',
	},
	{ batSequencer,
		{ batCheckDistance, param = { tarAITarget, boLTE, d.nScanEnemyRange} },
		{ batNot,
			{ batCheckHost, param = { tarAITarget } },
		},
		{ batParallel,
			_cast_template_spell(nastEnterFightSpell, tarAITarget, 0),
			__set_cd_timer(COOLDOWN_AI, nastNormalSpell2, d.nSpellCDTime[nastNormalSpell2]),
			__set_cd_timer(COOLDOWN_AI, nastNormalSpell3, d.nSpellCDTime[nastNormalSpell3]),
			__set_cd_timer(COOLDOWN_AI, nastNormalSpell4, d.nSpellCDTime[nastNormalSpell4]),
			__set_cd_timer(COOLDOWN_AI, nastChaseSpell, d.nSpellCDTime[nastChaseSpell]),
			_set_home(),
			{ batRotateTo, param = { tarAITarget, 0, 0, 360 } },
			--{ batClearThreatList, },
			{ batEnterFight },
		},
	},
};


function _pet_enter_idle()
	return
	{ batSelector,
		{ batSequencer,
			{ batCheckDistance, param = { tarHost, boLT, PET_JUMP_TO_HOST_GRID_NUM * CM_PER_GRID} },
			--{ batPetChangeFightTarget, param = { d.nScanEnemyRange } },
			{ batPetChangeFightTarget, param = { 185 } },
			{ batRotateTo, param = { tarAITarget, 0, 0,  360 } }, --d.nRotateSpeed
			{ batSetCDTimer, param = {COOLDOWN_AI, nastPetLoseInterestingTimer, PET_INTERESTING_TIME} },
		},
		{ batSequencer,
			{ batPetDelSbFromThreatenList, },
			{ batPetDelSbFromThreatList },
			{ batPetClearHostTarget, },
			'on_pet_enter_idle',
			{ batEnterIdle },
			{ batSetAIVariable, param = { PET_AIV_FIGHT_STATE_INDEX, PET_IDLE } },
			{ batSetCDTimer, param = {COOLDOWN_AI, nastPetFightTimer, 0} },
			{ batSelector,
				check_pet_state,
				pet_follow,
			},
		},
	};
end


function _pet_idle_tree()
    local result =
	--{ batDebug,
	{ batSelector,
        check_live_time,
		'on_pet_idle',
		--{ batSequencer,
			--{ batCheckAIVariable, param = { boNEQ, PET_AI_GO_HOME, 1 } },
			pet_detect_enemy,
		--},
		check_pet_state,
        pet_follow,
    --},
	};

    return result;
end




-- fight tree

local pet_check_out_of_range =
{ batSequencer,
	{ batCheckTargetType, param = { tarAITarget, otRole } },
	{ batCheckDistance, param = { tarHost, boGTE, PET_ENTER_IDLE_GRID_NUM * CM_PER_GRID } },
	--{ batCheckDistance, param = { tarHost, boGTE, PET_JUMP_TO_HOST_GRID_NUM * CM_PER_GRID} },
	_pet_enter_idle(),
};


local pet_check_target_die =
{ batSequencer,
	{ batCheckCharHp, param = { tarAITarget, boLTE, 0 } },
	_pet_enter_idle(),
};

local pet_check_distance =
{ batSequencer,
	{ batCheckDistance, param = {tarAITarget, boGT, d.nScanEnemyRange} },
	_pet_enter_idle(),
};


local pet_chase =
{ batSequencer,
	{ batPetCheckNeedChase, param = { d.nChaseThreshold } },
	--{ batPetCheckNeedChase, param = { 85 } },
	{ batSelector,
		{ batSequencer,
			{ batCheckDistance, param = { tarAITarget, boGT, d.nChaseRange } },
			--{ batSetAIVariable, param = { PET_AI_GO_HOME, 1 } },
			_pet_enter_idle(),
		},

		-- if first chase, set cd
		{ batNot,
			{ batParallel,
				{ batSequencer,
					{ batCheckAIVariable, param = { boNEQ, PET_AIV_FIGHT_STATE_INDEX, PET_CHASE } },
					{ batSetAIVariable, param = { PET_AIV_FIGHT_STATE_INDEX, PET_CHASE } },
					{ batSetCDTimer, param = {COOLDOWN_AI, nastPetChaseTimer, PET_CHASE_TIME} },
				},
			},
		},

		{ batSequencer,
			{ batPetGetCaster, },
			{ batRotateTo, param = { tarAITarget, 0, 0, 360 } },
			{ batSetAIVariable, param = { PET_AIV_FIGHT_STATE_INDEX, PET_NONE } },
		},

		-- check cd, change target
		{ batSequencer,
			{ batCheckCDTimer, param = { COOLDOWN_AI, nastPetChaseTimer} },
			{ batSelector,
				{ batSequencer,
					{ batSetCDTimer, param = {COOLDOWN_AI, nastPetChaseTimer, PET_CHASE_TIME} },
					{ batPetChangeChaseTarget, param = { d.nScanEnemyRange } },
					--{ batPetChangeChaseTarget, param = { 20 } },
					{ batRotateTo, param = { tarAITarget, 0, 0, 360 } },
					{ batSetCDTimer, param = {COOLDOWN_AI, nastPetLoseInterestingTimer, PET_INTERESTING_TIME} },
					{ batSetAIVariable, param = { PET_AIV_FIGHT_STATE_INDEX, PET_NONE } },
				},
				--_pet_enter_idle(),
			},
		},

		{ batSequencer,
			{ batCheckAIVariable, param = { boEQ, PET_AI_CONTROL, psFight} },
			{ batPetChase, param = { d.prefer_distance, d.nChaseThreshold, chase_delay } },
		},
	},

};

local pet_fight =
{ batSelector,
	{ batNot,
		{ batParallel,
			{ batSequencer,
				{ batCheckAIVariable, param = { boNEQ, PET_AIV_FIGHT_STATE_INDEX, PET_FIGHT } },
				{ batCheckCDTimer, param = { COOLDOWN_AI, nastPetFightTimer} },
				{ batSetCDTimer, param = {COOLDOWN_AI, nastPetFightTimer, d.nChangeTargetCDTime} },
				--{ batSetCDTimer, param = {COOLDOWN_AI, nastPetLoseInterestingTimer, PET_INTERESTING_TIME} },
			},
		},
	},


	{ batSequencer,
		{ batSelector,
			{ batPetCheckHostTarget, param = { otRole } },
			{ batCheckCDTimer, param = { COOLDOWN_AI, nastPetFightTimer} },
		},

		{ batSequencer,
			{ batSetCDTimer, param = {COOLDOWN_AI, nastPetFightTimer, d.nChangeTargetCDTime} },
			--{ batPetChangeFightTarget, param = { d.nScanEnemyRange } },
			{ batPetChangeFightTarget, param = { 185 } },
			{ batRotateTo, param = { tarAITarget, 0, 0, 360 } }, --d.nRotateSpeed
			{ batSetCDTimer, param = {COOLDOWN_AI, nastPetLoseInterestingTimer, PET_INTERESTING_TIME} },
			{ batSetAIVariable, param = { PET_AIV_FIGHT_STATE_INDEX, PET_NONE } },
		},
	},


	{ batParallel,
		{ batSetAIVariable, param = { PET_AIV_FIGHT_STATE_INDEX, PET_FIGHT } },
		{ batSelector,
			{ batSequencer,
				{ batCheckAIVariable, param = { boEQ, PET_AI_CONTROL, psFight} },
				'on_pet_cast_spell',  -- 释放技能
			},
			--_pet_enter_idle(),
		},

	},
};

local pet_check_valid_target =
{ batNot,
	{ batSequencer,
		{ batSelector,
			{ batPetCheckValidTarget, param = { d.nScanEnemyRange } },    -- pet scan enemy range
			{ batSetTarget, param = {0} },
		},
		{ batCheckTarget, param = { tarAITarget } },
	},
};


function _pet_fight_tree()
    local result =
	--{ batDebug,
	{batSelector,
		check_live_time,
		pet_check_out_of_range,
		pet_check_distance,
		pet_check_target_die,
		pet_check_valid_target,

		{ batNot,
			{ batParallel,
				{ batSequencer ,
					{ batCheckAIVariable, param = { boEQ, PET_AI_CONTROL, psFight} },
					check_pet_state,
				},
			},
		},

		{ batSequencer,
			{ batCheckCDTimer, param = { COOLDOWN_AI, nastPetLoseInterestingTimer} },
			{ batNot,
				{ batCheckThreatFadeTime, param = { tarSelf, tarAITarget, PET_INTERESTING_TIME} },
			},
			_pet_enter_idle(),
		},

		--check_pet_state,
		pet_chase,
		{ batParallel,
			{ batRotateTo, param = { tarAITarget, 0, 0, 360 } },
			pet_fight,  -- 攻击
			pet_check_target_die,
		},
	--},
	};

    return result;
end


-- init tree
function GetPetAttackSpeed(born_type, init_level)
	local attack_speed = 8;
	
	-- 召唤神兽, 设置攻击速度
	if born_type == petBornHoly then
		attack_speed = (500 - init_level * 50) * GAME_FPS / 1000;
	elseif born_type == petBornSkeleton then
		attack_speed = (2000 - init_level * 600) * GAME_FPS / 1000;
	elseif born_type == petBornByMage then
		attack_speed = (1000 - init_level * 200) * GAME_FPS / 1000;
	end

	return attack_speed;
end

function GetPetWalkSpeed(born_type, init_level)
	local walk_speed = 8;

	-- 召唤骷髅, 设置攻击速度
	if born_type == petBornHoly then
		walk_speed = (500 - init_level * 30) * GAME_FPS / 1000;
	elseif born_type == petBornSkeleton then
		walk_speed = (1200 - init_level * 250) * GAME_FPS / 1000;
	elseif born_type == petBornByMage then
		walk_speed = (1500 - init_level * 200) * GAME_FPS / 1000;
	end

	return walk_speed;
end

function PetAiInit(owner)
	local npc = tolua.cast(owner, 'CNpc');
	local npc_data = npc:GetNpcData();
	local init_level = npc:GetPetInitLevel();
	local pet_data = GetPetData(npc:GetPetType(), init_level);
	local original_ai_id = npc:GetOriginalAiID();
	local original_ai_data = CDataManager_NEW_AI_DATA_:GetInstance():GetData(original_ai_id);
	local ai_processor = npc:GetAIProcessor();
	local host_id = npc:GetHostID();
	local host = CGameWorld:GetInstance():FindValidRole(host_id);

	local origin_walk_spd = npc:GetAttr(catWalkSpeed);
	local origin_atk_spd = npc:GetGlobalCDDelayFrame();
	local walk_spd = GetPetWalkSpeed(pet_data.nBornType, init_level);
	local atk_spd = GetPetAttackSpeed(pet_data.nBornType, init_level);

	--print("old walk "..origin_walk_spd);
	--print("new walk "..walk_spd);
	--print(atk_spd);

	if pet_data.nBornType == petBornByMage then
		if walk_spd >= origin_walk_spd then
				walk_spd = origin_walk_spd;
		end

		if atk_spd >= origin_atk_spd then
				atk_spd = origin_atk_spd;
		end
	end

	--print("final walk "..walk_spd);

	npc:GetAttrList():SetAttrA(npc, catWalkSpeed, walk_spd);
	npc:SetGlobalCDDelayFrame(atk_spd);

	ai_processor:SetVariable(PET_AI_IS_EXTRA_WALK, 0);
	ai_processor:SetVariable(PET_AIV_MAGE_PET_SPELL_ID, original_ai_data.nSpellID[nastNormalSpell1]);
	ai_processor:SetVariable(PET_AI_MAGE_CHASE_THRESHOLD, original_ai_data.nChaseThreshold * POINT_PER_CM);
	ai_processor:SetVariable(PET_AI_MAGE_PREFER_DISTANCE, original_ai_data.nPreferDistance * POINT_PER_CM);
	ai_processor:SetIgnoreInvisible(npc_data.bIgnoreInvisible);
	ai_processor:SetCounterInvisible(npc_data.bCounterInvisible);

	npc:ChangePetAI(host:GetPetState());

	return brvSuccess;
end

function _pet_init_tree()
    local result =
    { batParallel,
		{ PetAiInit },
        _set_scan_param(),
		pet_set_follow_param,
		__cast_init_spell(d.nSpellID[nastInitSpell1], d.nSpellChance[nastInitSpell1]),
        __cast_init_spell(d.nSpellID[nastInitSpell2], d.nSpellChance[nastInitSpell2]),
        __cast_init_spell(d.nSpellID[nastInitSpell3], d.nSpellChance[nastInitSpell3]),
        _add_init_aura(),
		--_pet_init_aura,
		pet_follow,
    };

    return result;
end
