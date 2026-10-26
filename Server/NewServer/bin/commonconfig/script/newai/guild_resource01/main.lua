LoadPackage("character.pkg")
LoadPackage("npc.pkg")
LoadPackage("guild_def.pkg")
LoadPackage("gs_guild.pkg")
LoadPackage("guild_mgr.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("data_manager.pkg")
LoadPackage("ai.pkg")
LoadPackage("role.pkg")
LoadPackage("item_bag.pkg")
LoadPackage("money_def.pkg")
LoadPackage("error_def.pkg")


g_GuildMgr = CGuildMgr:GetInstance();
g_GameWorld = CGameWorld:GetInstance();

--g_DropGenerator = CDropGenerator:GetInstance();


-- 角色变量的index 190 记录的是增加的公会资源数量


-- 资源转换成多少贡献
function CalcContribute(res_count)
	return res_count / 10;
end

function GetItemCount(owner, itemid, bIncludeBank)
	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	local count = role:GetItemBag():GetItemCount(itemid, bIncludeBank);
	return count;
end

-- 检查每日资源捐献上限
function CheckCanDonateRes(owner, res_type, res_count)
	if res_count == 0 then
		return brvFail;
	end

	local processor = owner:GetAIProcessor();
	local npc = tolua.cast(processor:GetOwner(), 'CNpc');

	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	local guild = CGuildMgr:GetInstance():FindGuild(role:GetGuildID());
	local member = guild:GetMember(role:GetObjID());

	if guild:GetRes(res_type) + res_count > guild:GetMaxRes(res_type) then
		return brvFail;
	end

	-- 检查上限
	local final_res = role:GetRoleGuildData():CalculateResLimit(member.nPosition, res_count);
    if final_res < res_count then
		return brvFail;
	end

	return brvSuccess;
end

-- 增加公会粮食，有贡献
function GuildHerb(owner, res_count)
	local processor = owner:GetAIProcessor();
	local npc = tolua.cast(processor:GetOwner(), 'CNpc');

	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	local guild = CGuildMgr:GetInstance():FindGuild(role:GetGuildID());
	local member = guild:GetMember(role:GetObjID());

	-- 检查上限
	local final_res = role:GetRoleGuildData():CalculateResLimit(member.nPosition, res_count);
    if final_res == 0 then
		return brvFail;
	end

	local con_count = CalcContribute(final_res);

	-- 增加 con_count 公会贡献点数
	role:GetItemBag():AddMoney(MONEYTYPE_GUILD, con_count, MONEYLOG_INVALID, 0, 0);
	SendMSToAddRes(role:GetObjID(), GUILD_ATTR_HERB, final_res);

	return brvSuccess;
end

-- 公会木材，有贡献
function GuildWood(owner, res_count)
	local processor = owner:GetAIProcessor();
	local npc = tolua.cast(processor:GetOwner(), 'CNpc');

	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	local guild = CGuildMgr:GetInstance():FindGuild(role:GetGuildID());
	local member = guild:GetMember(role:GetObjID());

	-- 检查上限
	local final_res = role:GetRoleGuildData():CalculateResLimit(member.nPosition, res_count);
    if final_res == 0 then
		return brvFail;
	end

	local con_count = CalcContribute(final_res);
	role:GetItemBag():AddMoney(MONEYTYPE_GUILD, con_count, MONEYLOG_INVALID, 0, 0);
	SendMSToAddRes(role:GetObjID(), GUILD_ATTR_WOOD, final_res);

	return brvSuccess;
end

-- 公会石材，有贡献
function GuildCrystal(owner, res_count)
	local processor = owner:GetAIProcessor();
	local npc = tolua.cast(processor:GetOwner(), 'CNpc');

	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	local guild = CGuildMgr:GetInstance():FindGuild(role:GetGuildID());
	local member = guild:GetMember(role:GetObjID());

	-- 检查上限
	local final_res = role:GetRoleGuildData():CalculateResLimit(member.nPosition, res_count);
    if final_res == 0 then
		return brvFail;
	end

	local con_count = CalcContribute(final_res);
	role:GetItemBag():AddMoney(MONEYTYPE_GUILD, con_count, MONEYLOG_INVALID, 0, 0);
	SendMSToAddRes(role:GetObjID(), GUILD_ATTR_CRYSTAL, final_res);

	return brvSuccess;
end

-- 公会铁矿，有贡献
function GuildSilver(owner, res_count)
	local processor = owner:GetAIProcessor();
	local npc = tolua.cast(processor:GetOwner(), 'CNpc');

	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	local guild = CGuildMgr:GetInstance():FindGuild(role:GetGuildID());
	local member = guild:GetMember(role:GetObjID());

	-- 检查上限
	local final_res = role:GetRoleGuildData():CalculateResLimit(member.nPosition, res_count);
    if final_res == 0 then
		return brvFail;
	end

	local con_count = CalcContribute(final_res);
	role:GetItemBag():AddMoney(MONEYTYPE_GUILD, con_count, MONEYLOG_INVALID, 0, 0);
	SendMSToAddRes(role:GetObjID(), GUILD_ATTR_SILVER, final_res);

	return brvSuccess;
end

function TryToDonateAllRes(owner, res_type, itemid, res_per_item)
	local itemcount = GetItemCount(owner, itemid, false);

	if itemcount == 0 then
		return brvSuccess;
	end

	local res_total = res_per_item * itemcount;
	local ret = CheckCanDonateRes(owner, res_type, res_total);
	if ret ~= brvSuccess then
		return ret;
	end

	-- ajust itemcount




	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	ret = role:GetItemBag():DeleteItemId(itemid, itemcount, ITEMLOG_SCRIPT, false, 0);
	if ret == errSuccess then
		if res_type == GUILD_ATTR_HERB then
			GuildHerb(owner, res_total);
		elseif res_type == GUILD_ATTR_WOOD then
			GuildWood(owner, res_total);
		elseif res_type == GUILD_ATTR_CRYSTAL then
			GuildCrystal(owner, res_total);
		elseif res_type == GUILD_ATTR_SILVER then
			GuildSilver(owner, res_total);
		end
	end

	return brvSuccess;
end



Include("script/include/btnod.lua")
Include("script/newai/sub_tree/sub_tree.lh");
Include("script/newai/guild_resource01/main.uh")


