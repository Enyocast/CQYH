LoadPackage("char_def.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("character.pkg")
LoadPackage("role.pkg")
LoadPackage("npc.pkg")

--Include("script/newai/sub_tree/sub_tree.lh")
Include("script/newai/sub_tree/pet_sub_tree.lua")

local 	PET_INIT_AURA_BY_HOST = 25470;


function _pet_die_tree()
    if d.nSpellID[nastDeadSpell] == 0 or d.nSpellChance[nastDeadSpell] == 0  then
        return nil;
    else
        return
        { batParallel,
            { batInvincible, param = { true } },
            { batSyncBreakCast, param = { true } },
            { batSyncCastSpellToTargetPos, param = {d.nSpellID[nastDeadSpell], tarSelf, 0, 0} },
            { batInvincible, param = { false } },
        };
    end
end

on_pet_cast_spell = _cast_all_spell();


function InitAura(owner)
	local processor = owner:GetAIProcessor();
	local npc = Cast(processor:GetOwner(), 'CNpc');

	local hostid = npc:GetHostID();
	local role = CGameWorld:GetInstance():FindRole(hostid);

	local aurainfo = CSpellConfig:GetInstance():FindAuraTemplate(PET_INIT_AURA_BY_HOST);
	npc:AppendAura(aurainfo, role, 0, NULL, 0, 0, 0, 1);

	print("append aura");

	return brvSuccess;
end

_pet_init_aura = { InitAura };

evtAIInit = _pet_init_tree();
evtAIIdle = _pet_idle_tree();
evtAIFight = _pet_fight_tree();
evtAIDie = _pet_die_tree();

Include("script/newai/pet/main.uh")
