LoadPackage("common.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("ai.pkg")
LoadPackage("scene.pkg")
LoadPackage("arena.pkg")
LoadPackage("scene_object.pkg")
LoadPackage("chat_def.pkg")
LoadPackage("spell.pkg")
LoadPackage("character.pkg")
LoadPackage("char_def.pkg")





-- JJC 角色数量
ARENA_ROLE_NUM_INDEX = 1;
-- JJC 开始准备时间
ARENA_START_TIME_INDEX = 2;
-- JJC state
ARENA_STATE_INDEX = 3;
-- 竞技场开门的场景变量
ARENA_DOOR_TOGGLE_INDEX = 4;




-- JJC 第一个角色的角色roleid
ARENA_FIRST_ROLE_INDEX = 11;
-- JJC 第二个角色的角色roleid
ARENA_SECOND_ROLE_INDEX = 12;



-- JJC READY
ARENA_STATE_READY = 1;
-- JJC BEGIN
ARENA_STATE_BEGIN = 2;
-- JJC END
ARENA_STATE_END = 3;




ARENA_FACTION_FIRST = 1;
ARENA_FACTION_SECOND = 2;


-- JJC 等待关闭地图时间
--ARENA_CLOSE_WAIT_DURATION = 120000;
ARENA_CLOSE_WAIT_DURATION = 10000;

-- JJC 持续时间
ARENA_LAST_TIME = 600000;

-- 减益buff id
ARENA_DEC_ROLE_ATTR_AURA_ID = 2150;

-- 增益buff id
ARENA_ADD_ROLE_ATTR_AURA_ID = 2050;





g_GameWorld = CGameWorld:GetInstance();

-- internal
local function RoleWinArena(dwRoleID)
	local role = g_GameWorld:FindRole(dwRoleID);

	local ret = role:GetArena():Win();

	return ret;
end

-- for action
function GetRoleID(owner)
	return get_ctx_role_id();
end

function CanInheritArenaHp(owner)
	local role = g_GameWorld:FindRole(get_ctx_role_id());
	local nHp = role:GetArena():GetHP();

	if 0 == nHp then
		return brvFail;
	end

	return brvSuccess;
end


function GetArenaHp(owner)
	local role = g_GameWorld:FindRole(get_ctx_role_id());

	local nHp = role:GetArena():GetHP();
	if 0 == nHp then
		nHp = role:GetHp();
	end

	return nHp;
end

function SetRoleHp(owner)
	local role = g_GameWorld:FindRole(get_ctx_role_id());

	local oldHp = role:GetArena():GetHP();
	if 0 ~= oldHp then
		role:ChangeHp(oldHp - role:GetHp(), cdrAIBehavior);
	end

	return brvSuccess;
end


function AddAura(owner, AuraID)

	local role = g_GameWorld:FindRole(get_ctx_role_id());
	local info = CSpellConfig:GetInstance():FindAuraTemplate(AuraID);

	role:AppendAura(info, role, 0, NULL, 0, 0);

	return brvSuccess;
end

function DelAura(owner, AuraID)

	local role = g_GameWorld:FindRole(get_ctx_role_id());
	local auraInstance = role:GetFirstAura(AuraID);

	if auraInstance ~= nil then
		role:RemoveAura(auraInstance, false);
	end

	return brvSuccess;

end


function OnlyJoinArenaSceneWin(owner)

	local dwRoleID = owner:GetVariable(ARENA_FIRST_ROLE_INDEX);

	RoleWinArena(dwRoleID);

	return brvSuccess;
end


function DeadRoleArenaDefeat(owner)

	local dwRoleID = get_ctx_role_id();
	local role = g_GameWorld:FindRole(dwRoleID);
	local ret = role:GetArena():Defeated();

	return brvSuccess;

end


function DeadRoleArenaCompetitorWin(owner)
	local dwRoleID = 0;
	local dwDeadRoleID = get_ctx_role_id();

	if dwDeadRoleID == owner:GetVariable(ARENA_FIRST_ROLE_INDEX) then
		dwRoleID = owner:GetVariable(ARENA_SECOND_ROLE_INDEX);
	else
		dwRoleID = owner:GetVariable(ARENA_FIRST_ROLE_INDEX);
	end

	RoleWinArena(dwRoleID);

	return brvSuccess;
end


Include("script/include/btnod.lua")
Include("script/scene/CommonArena/main.uh")


