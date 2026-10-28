Include("script/stringtable/stringtable.lh")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
Include("script/newai/sub_tree/sub_tree.lh");
LoadPackage("chat_def.pkg")
LoadPackage('variable.pkg')

MAX_REWARD_COUNT = 1000;
DEFAULT_EXP_REWARD_RATE = 10000;

local g_oGameWorld = CGameWorld:GetInstance();

function add_exp(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local roleindex = g_oGameWorld:GetServerVariable(role:GetServerGroup(), svtServerStartIndex);
	local exp_reward_rate = g_oGameWorld:GetServerVariable(role:GetServerGroup(), svtStartRewardRate);

	if exp_reward_rate == 0 then
		exp_reward_rate = DEFAULT_EXP_REWARD_RATE;
		g_oGameWorld:SetServerVariable(role:GetServerGroup(), svtStartRewardRate, true, exp_reward_rate);
	end

	if role then
		--exp_reward_rate * A * player level * (1/N)^0.1; exp_reward_rate is the operations-controlled multiplier, A is the base (initially 1000), and N is the claim order
		local exp = exp_reward_rate * (role:GetLevel()) * ( 1 / (roleindex + 1) )^0.1 / 10;
		role:AddExp(exp, false, true);
		return brvSuccess;
	end

	return brvError;
end

function get_reward_count(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());

	return MAX_REWARD_COUNT - g_oGameWorld:GetServerVariable(role:GetServerGroup(), svtServerStartIndex);
end




Include("script/newai/6683/main.uh")