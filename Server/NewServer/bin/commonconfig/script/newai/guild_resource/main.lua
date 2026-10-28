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


-- Character variable index 190 records the amount of guild resources added


-- Contribution gained from resources
function CalcContribute(res_count)
	return res_count / 10;
end

function GetItemCount(owner, itemid, bIncludeBank)
	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	local count = role:GetItemBag():GetItemCount(itemid, bIncludeBank);
	return count;
end


-- Check the daily resource donation limit
function CheckCanDonateRes(owner, res_type, res_count)
	local processor = owner:GetAIProcessor();
	local npc = Cast(processor:GetOwner(), 'CNpc');

	if res_count == 0 then
		return brvFail;
	end

	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	local guild = CGuildMgr:GetInstance():FindGuild(role:GetGuildID());
	local member = guild:GetMember(role:GetObjID());

	if guild:GetRes(res_type) + res_count > guild:GetMaxRes(res_type) then
		return brvFail;
	end

	-- Check the limit
	local final_res = role:GetRoleGuildData():CalculateResLimit(member.nPosition, res_count);
    if final_res < res_count then
		return brvFail;
	end

	return brvSuccess;
end

-- Add guild food without contribution
function GuildHerbNoContribute(owner, res_count)
	local processor = owner:GetAIProcessor();
	local npc = Cast(processor:GetOwner(), 'CNpc');

	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	local guild = CGuildMgr:GetInstance():FindGuild(role:GetGuildID());
	local member = guild:GetMember(role:GetObjID());

	-- Check the limit
	local final_res = role:GetRoleGuildData():CalculateResLimit(member.nPosition, res_count);
    if final_res == 0 then
		return brvFail;
	end

	-- Add food
	SendMSToAddRes(role:GetObjID(), GUILD_ATTR_HERB, final_res);

	return brvSuccess;
end

-- Guild wood without contribution
function GuildWoodNoContribute(owner, res_count)
	local processor = owner:GetAIProcessor();
	local npc = Cast(processor:GetOwner(), 'CNpc');

	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	local guild = CGuildMgr:GetInstance():FindGuild(role:GetGuildID());
	local member = guild:GetMember(role:GetObjID());

	-- Check the limit
	local final_res = role:GetRoleGuildData():CalculateResLimit(member.nPosition, res_count);
    if final_res == 0 then
		return brvFail;
	end

	SendMSToAddRes(role:GetObjID(), GUILD_ATTR_WOOD, final_res);

	return brvSuccess;
end

-- Guild stone without contribution
function GuildCrystalNoContribute(owner, res_count)
	local processor = owner:GetAIProcessor();
	local npc = Cast(processor:GetOwner(), 'CNpc');

	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	local guild = CGuildMgr:GetInstance():FindGuild(role:GetGuildID());
	local member = guild:GetMember(role:GetObjID());

	-- Check the limit
	local final_res = role:GetRoleGuildData():CalculateResLimit(member.nPosition, res_count);
    if final_res == 0 then
		return brvFail;
	end

	SendMSToAddRes(role:GetObjID(), GUILD_ATTR_CRYSTAL, final_res);

	return brvSuccess;
end

-- Guild iron ore without contribution
function GuildSilverNoContribute(owner, res_count)
	local processor = owner:GetAIProcessor();
	local npc = Cast(processor:GetOwner(), 'CNpc');

	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	local guild = CGuildMgr:GetInstance():FindGuild(role:GetGuildID());
	local member = guild:GetMember(role:GetObjID());

	-- Check the limit
	local final_res = role:GetRoleGuildData():CalculateResLimit(member.nPosition, res_count);
    if final_res == 0 then
		return brvFail;
	end

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

	local role_id = get_ctx_role_id();
	local role = g_GameWorld:FindRole(role_id);

	ret = role:GetItemBag():DeleteItemId(itemid, itemcount, ITEMLOG_SCRIPT, false, 0);
	if ret == errSuccess then
		if res_type == GUILD_ATTR_HERB then
			GuildHerbNoContribute(owner, res_total);
		elseif res_type == GUILD_ATTR_WOOD then
			GuildWoodNoContribute(owner, res_total);
		elseif res_type == GUILD_ATTR_CRYSTAL then
			GuildCrystalNoContribute(owner, res_total);
		elseif res_type == GUILD_ATTR_SILVER then
			GuildSilverNoContribute(owner, res_total);
		end
	end

	return brvSuccess;
end


Include("script/include/btnod.lua")
Include("script/newai/sub_tree/sub_tree.lh");
Include("script/newai/guild_resource/main.uh")


