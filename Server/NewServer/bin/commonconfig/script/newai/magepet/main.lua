LoadPackage("char_def.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("character.pkg")
LoadPackage("role.pkg")
LoadPackage("npc.pkg")

--Include("script/newai/sub_tree/sub_tree.lh")
Include("script/newai/sub_tree/pet_sub_tree.lua")

-- spell, aura, last time
local 	MAGE_PET_VIOLENT_AURA_ID = 25411;  -- 狂暴
local 	AURA_INHERIT_PET_LEVEL = 2511;     -- 叛变保护


function MeetToGod(owner)
	local processor = owner:GetAIProcessor();
	local npc = Cast(processor:GetOwner(), 'CNpc');

	local hostid = npc:GetHostID();
	local role = CGameWorld:GetInstance():FindRole(hostid);

	npc:TransformToNpc();

	--local aurainfo = CSpellConfig:GetInstance():FindAuraTemplate(MAGE_PET_VIOLENT_AURA_ID);
	--npc:AppendAura(aurainfo, npc, 0, NULL, 0, 0, 0, 1);

	local aurainfo = CSpellConfig:GetInstance():FindAuraTemplate(AURA_INHERIT_PET_LEVEL);
	npc:AppendAura(aurainfo, role, 0, NULL, 0, 0, 0, 1);

	local npcHP = npc:GetHp() / 10;
	if npcHP == 0 then
		npcHP = 1;
	end
	npc:SetHp(npcHP);

	return brvSuccess;
end


on_live_timer = { batSequencer,
					{ MeetToGod },
					{ batSetHome },
					{ batEnterIdle },
};


function _magepet_cast_all_spell()
	return
	{ batSequencer,
		{ batCheckCanCastSpell },
		--_scan_nearby(),
		{ batSelector,
			{ batSequencer,
				{ batCheckCharHp, param = { tarAITarget, boGTE, 0 } },
				__check_cd_timer(COOLDOWN_AI, nastGlobalCDTimer, d.nGlobalCDTime),
				{ batMagePetCastSpellToTarget },
				__set_cd_timer(COOLDOWN_AI, nastGlobalCDTimer, d.nGlobalCDTime),
			},
		},
	};
end

on_pet_cast_spell = _magepet_cast_all_spell();

evtAIInit = _pet_init_tree();
evtAIIdle = _pet_idle_tree();
evtAIFight = _pet_fight_tree();

Include("script/newai/pet/main.uh")
