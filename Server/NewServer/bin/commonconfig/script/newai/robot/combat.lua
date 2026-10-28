
function do_cancel_cutscene(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
end

function do_select_focus(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	-- lixg: run error
	--local focus_id = select_focus(role);
	--user:SelectFocus(focus_id);
end

function do_cancel_spell(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	if role:IsCasting() then
		local slot = role:GetLastSlot();
		user:CancelSpell(slot);
	end
end

function do_spell_levelup(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	local i = math.random(qssActiveBegin, qssActiveEnd - 1);
	local slot = role:GetSpellSlot(i);
	local main_spell_id = slot:GetMainSpellID();

	user:SpellLevelUp(main_spell_id);
end

function do_combat_pose_switch(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	local i = math.random(2);

	if i == 1 then
		user:CombatPoseSwitch(true);
	else
		user:CombatPoseSwitch(false);
	end
end

function do_cancel_aura(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
--[[-- lixg: run error
	local aura_list = role:GetAuraList();	-- no export to pkg

	for i = auetNone, auetTotal do
		local aura = aura_list:BeginAura(i);
		while aura ~= nil do
			user:CancelAura(aura:GetInstanceID());
			aura = aura_list:NextAura(i, aura);
		end
	end
--]]
end

function do_on_mount(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	user:GMCommand(".ActivateMount()");
	user:OnMount(1);
end

function do_off_mount(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	user:OffMount();
end

function do_adjust_target_pt(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	if role:IsCasting() then
		local casting_spell = role:GetCastingSpell();
		local scanner = casting_spell:GetScanner();

		user:AdjustTargetPt(scanner:GetTargetX() + 100, scanner:GetTargetY() + 100, scanner:GetTargetZ());
	end
end

function do_equip_spell(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
end

function do_cast_spell(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	local i = math.random(qssActiveBegin, qssActiveEnd);
	local focus = CGameWorld:GetInstance():FindValidCharacter(role:GetFocusID());

	if focus ~= nil then
		user:CastSpell(i, role:GetFocusID(), focus:GetX(), focus:GetY(), focus:GetZ());
		user:SetLastSlot(i);
	end
end

function do_directly_cast_spell(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
end
