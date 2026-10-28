LoadPackage("char_def.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("character.pkg")
LoadPackage("role.pkg")
LoadPackage("npc.pkg")

Include("script/newai/sub_tree/sub_tree.lh")

-- spell, aura, last time
local 	TRANSFORM_TO_DOG_AURA_ID = 60460;  -- 神兽变化
local 	TRANSFORM_TO_DOG_SPELL_ID = 6046;  -- [神兽(普通)]进入战斗
local 	TRANSFORM_TO_DOG_PERFORMANCE_TIME = 1063;

local 	TRANSFORM_TO_MAN_WAIT_TIME = 60000;
local 	TRANSFORM_TO_MAN_SPELL_ID = 6047;  -- [神兽(通用)]退出战斗
local 	TRANSFORM_TO_MAN_PERFORMANCE_TIME = 1750;

local 	MAGE_PET_VIOLENT_SPELL_ID = 25411;

-- cd
local 	PET_TRANSFORM_TO_IDLE_STATE_CD = nastCustom;

on_enter_fight= { batSelector,
					{ batCheckAura, param = { tarSelf, TRANSFORM_TO_DOG_AURA_ID} },
					{ batSequencer,
						{ batCastSpellToTarget, param = { TRANSFORM_TO_DOG_SPELL_ID, tarSelf} },
						{ batWait, param = { TRANSFORM_TO_DOG_PERFORMANCE_TIME} },
					},
};

--function MeetToGod(owner)
--	local processor = owner:GetAIProcessor();
--	local npc = Cast(processor:GetOwner(), 'CNpc');

--	local hostid = npc:GetHostID();
--	local role = CGameWorld:GetInstance():FindRole(hostid);

--	if role:GetClass() == clsTaoist then
--		npc:Die(0);
--	elseif role:GetClass() == clsMage then
--		npc:TransformToNpc();
--		npc:CastSpell(MAGE_PET_VIOLENT_SPELL_ID, npc, npc:GetX(), npc:GetY(), npc:GetZ());
--	else
--		npc:Die(0);
--	end

--	return brvSuccess;
--end

function _pet_enter_idle()
	return { batSequencer,
				{batSetCDTimer, param = { COOLDOWN_AI, PET_TRANSFORM_TO_IDLE_STATE_CD, TRANSFORM_TO_MAN_WAIT_TIME}},
				{batEnterIdle},
	};
end

function _pet_check_transform_timer()
	return { batSequencer,
				{ batCheckAura, param = { tarSelf, TRANSFORM_TO_DOG_AURA_ID} },
				{ batCheckCDTimer, param = { COOLDOWN_AI, PET_TRANSFORM_TO_IDLE_STATE_CD } },
				{ batCastSpellToTarget, param = {TRANSFORM_TO_MAN_SPELL_ID, tarSelf}},
				{ batWait, param = { TRANSFORM_TO_MAN_PERFORMANCE_TIME} },
	};
end

function __check_pet_live_timer()
	return
		{ batSequencer,
			{ batCheckCDTimer, param = { COOLDOWN_AI, nastLiveTimer } },
			{ batSuicide },
		};
end

function _pet_detect_enemy()
    local scan_table = { batSelector };

    if d.nScanEnemyRange > 0 then
        table.insert(scan_table,
			{ batSelector,
				{ batSequencer,
					{ batScanHostThreatList, param = { d.nScanEnemyRange } },
					{ batAddTargetThreat, param = { 50 } },
				},
				{
					batSequencer,
						{ batScanEnemy, param = { d.nScanEnemyRange } },
						{ batAddTargetThreat, param = { 50 } },
				},
			}
        );
    end

    result =
    { batSequencer,
        { batParallel,
            scan_table,
        },
        { batSequencer,
            { batCheckInCombat },
            { batParallel,
                { batGetTargetFromThreatList, param = { d.nChaseRange } },
                _cast_template_spell(nastEnterFightSpell, tarAITarget, 0),
                __set_cd_timer(COOLDOWN_AI, nastNormalSpell2, d.nSpellCDTime[nastNormalSpell2]),
                __set_cd_timer(COOLDOWN_AI, nastNormalSpell3, d.nSpellCDTime[nastNormalSpell3]),
                __set_cd_timer(COOLDOWN_AI, nastNormalSpell4, d.nSpellCDTime[nastNormalSpell4]),
                __set_cd_timer(COOLDOWN_AI, nastChaseSpell, d.nSpellCDTime[nastChaseSpell]),
                _set_home(),
                { batEnterFight },
                'on_enter_fight',
            },
        },
    };

    return result;
end


function __pet_check_out_of_range(chase_range)
    if chase_range == nil or chase_range == 0 then
        return nil;
    else
        return
        { batSequencer,
            -- { batCheckCharOutOfHomeRange, param = { tarAITarget, chase_range } },
            { batCheckDistance, param = { tarAITarget, boGT, chase_range } },  
            { batSelector,
                { batGetTargetFromThreatList, param = { chase_range } },
                _pet_enter_idle(),
            },
        };
    end
end

function __pet_check_target_die(chase_range)
    if chase_range == nil or chase_range == 0 then
        return nil;
    else
        return
        { batSequencer,
            { batCheckCharHp, param = { tarAITarget, boLTE, 0 } },
            { batSelector,
                { batGetTargetFromThreatList, param = { chase_range } },
                _pet_enter_idle(),
            },
        };
    end
end


function _pet_idle_tree()
    local result =
    { batSelector,
        __check_pet_live_timer(),
		_pet_check_transform_timer(),
        _pet_detect_enemy(),
        __cast_spell(d.nSpellID[nastIdleSpell], tarSelf, d.nSpellChance[nastIdleSpell], d.nSpellCDTime[nastIdleSpell], d.nGlobalCDTime),
        _follow(),
    };

    return result;
end

function _pet_fight_tree()
    local result =
    { batParallel,
        { batSelector,
            __check_pet_live_timer(),
            __pet_check_out_of_range(d.nChaseRange),
            __pet_check_target_die(d.nChaseRange),
            'on_fight_move',
            __fight_move(d.nPreferDistance, d.nWithdrawThreshold, d.nChaseThreshold, d.nRunSpeed * 1000 / GAME_FPS, d.nStepAroundChance, d.nStepAroundCDTime),
            'on_cast_spell',
            _cast_all_spell(),
            __chase(d.nRunSpeed * 1000 / GAME_FPS, d.nPreferDistance, d.nChaseThreshold, d.nChaseDelayTime),
        },
    };

    return result;
end

function _pet_init_tree()
    local result =
    { batParallel,
        'on_init',
        _set_scan_param(),
		_set_follow_param(),
        __cast_init_spell(d.nSpellID[nastInitSpell1], d.nSpellChance[nastInitSpell1]),
        __cast_init_spell(d.nSpellID[nastInitSpell2], d.nSpellChance[nastInitSpell2]),
        __cast_init_spell(d.nSpellID[nastInitSpell3], d.nSpellChance[nastInitSpell3]),
		_add_init_aura(),
    };

    return result;
end


evtAIInit = _pet_init_tree();
evtAIIdle = _pet_idle_tree();
evtAIFight = _pet_fight_tree();

Include("script/newai/pet/main.uh")
