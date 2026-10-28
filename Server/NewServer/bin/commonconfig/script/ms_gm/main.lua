LoadPackage("ms_guild.pkg")
LoadPackage("ms_guild_mgr.pkg")
LoadPackage("role_data.pkg")
LoadPackage("role_data_mgr.pkg")
LoadPackage("ms_guild_member.pkg")
LoadPackage("arena_mgr.pkg")
LoadPackage("online_role_data.pkg")
LoadPackage("global_config.pkg")


Include("script/ms_gm/gm_command.lua");
Include("script/arena/main.lua");
Include("script/guild/main.lua");


g_MSGuildMgr = CMsGuildMgr:GetInstance();
g_MSRoleDataMgr = CRoleDataMgr:GetInstance();

function AddGuildMoney(guild_name, m_type, num)
	print(guild_name);
	local 	guild = g_MSGuildMgr:FindGuildByName(guild_name);
	if guild ~= nil then
		if m_type == GUILD_ATTR_MONEY then
			guild:AddMoney(num, GUILD_CHEST_GM);
		elseif m_type == GUILD_ATTR_WOOD then
			guild:AddWood(num);
		elseif m_type == GUILD_ATTR_HERB then
			guild:AddHerb(num);
		elseif m_type == GUILD_ATTR_CRYSTAL then
			guild:AddCrystal(num);
		elseif m_type == GUILD_ATTR_SILVER then
			guild:AddSilver(num);
		end
	end
end

function AddGuildSalary(guild_name, role_name, num)
	local guild = g_MSGuildMgr:FindGuildByName(guild_name);
	local role = g_MSRoleDataMgr:FindRoleByName(role_name);

	if guild ~= nil and role ~= nil then
		local member = guild:GetMember(role.dwRoleID);
		if member ~= nil then
			member:AddSalary(num, true);
		end
	end
end

function ArenaOpen()
	for i= 0, MAX_SERVER_GROUP_COUNT,1 do
		local bValidGroup = IsValidGroup(i);
		if bValidGroup then
			set_server_var(i, esvtArena, avArenaCanOpen, 1);

			say(SelfRoleID, SelfRoleID, "arena open "..i);
		end
	end
end

function ArenaClose()
	for i= 0, MAX_SERVER_GROUP_COUNT,1 do
		local bValidGroup = IsValidGroup(i);
		if bValidGroup then
			set_server_var(i, esvtArena, avArenaCanOpen, 0);
			say(SelfRoleID, SelfRoleID, "arena close "..i);
		end
	end
end


function ArenaBegin()

	arena_begin();

	say(SelfRoleID, SelfRoleID, "arena begin ");
end

function ArenaEnd()

	arena_end();

	say(SelfRoleID, SelfRoleID, "arena end ");
end

function ArenaRewardBegin()
	arena_reward_begin();

	say(SelfRoleID, SelfRoleID, "arena reward begin ");
end

function ArenaRewardEnd()

	arena_reward_end();

	say(SelfRoleID, SelfRoleID, "arena reward end ");

end

function ClearRoleGuildCD()
	local pRole = g_MSRoleDataMgr:FindRole(SelfRoleID);

	pRole.dwJoinGuildCD = 0;

end


function ClearMasterCD()
	local onlineRole = COnlineRoleDataMgr:GetInstance():FindOnlineRoleByRoleID(SelfRoleID);

	print_ms("begin clear master cd "..onlineRole.pRoleData.dwRoleID.." "..onlineRole.dwMasterCD);
	onlineRole.dwMasterCD = 0;
	print_ms("end clear master cd "..onlineRole.dwMasterCD);
end


function Arrest(name, duration)
	arrest_role(name, duration);
end

function TestGpk(name)
	test_gpk(name);
end


function GuildWarOpen()
	print("guild war open");
	for i= 0, MAX_SERVER_GROUP_COUNT,1 do
		local bValidGroup = IsValidGroup(i);
		if bValidGroup then
			set_server_var(i, esvtGuild, avGuildWarCanOpen, 1);

			say(SelfRoleID, SelfRoleID, "guild war open "..i);
		end
	end
end


function GuildWarClose()
	print("guild war close");
	for i= 0, MAX_SERVER_GROUP_COUNT,1 do
		local bValidGroup = IsValidGroup(i);
		if bValidGroup then
			set_server_var(i, esvtGuild, avGuildWarCanOpen, 0);

			say(SelfRoleID, SelfRoleID, "guild war close "..i);
		end
	end
end


function GuildWarBegin()
	GuildWarBegin();
end

function GuildWarEnd()
	GuildWarEnd();
end


function UpGuild(guild_name, finallevel)
	local level = 0;

	--print("begin");
	local 	guild = g_MSGuildMgr:FindGuildByName(guild_name);

	if finallevel > 5 then
		finallevel = 5;
	end


	-- Main hall
	level = guild:GetBuildingMaxLevelByType(GUILD_B_MAIN);
	while level < finallevel do
		guild:LuaUpdateBuilding(SelfRoleID, 'main01', GUILD_B_MAIN);
		level = guild:GetBuildingMaxLevelByType(GUILD_B_MAIN);
	end

	-- Trading hall
	level = guild:GetBuildingMaxLevelByType(GUILD_B_BUSINESS);
	while level < finallevel do
		guild:LuaUpdateBuilding(SelfRoleID, 'Shop01', GUILD_B_BUSINESS);
		level = guild:GetBuildingMaxLevelByType(GUILD_B_BUSINESS);
	end

	-- Altar
	level = guild:GetBuildingMaxLevelByType(GUILD_B_DEITY);
	while level < finallevel do
		guild:LuaUpdateBuilding(SelfRoleID, 'God01', GUILD_B_DEITY);
		level = guild:GetBuildingMaxLevelByType(GUILD_B_DEITY);
	end

	-- Residence
	level = guild:GetBuildingMaxLevelByType(GUILD_B_HOUSE);
	while level < finallevel do
		guild:LuaUpdateBuilding(SelfRoleID, 'base901', GUILD_B_HOUSE);
		level = guild:GetBuildingMaxLevelByType(GUILD_B_HOUSE);
	end

	-- Treasury
	level = guild:GetBuildingMaxLevelByType(GUILD_B_STORAGE);
	while level < finallevel do
		guild:LuaUpdateBuilding(SelfRoleID, 'base902', GUILD_B_STORAGE);
		level = guild:GetBuildingMaxLevelByType(GUILD_B_STORAGE);
	end

	-- Granary
	level = guild:GetBuildingMaxLevelByType(GUILD_B_HERB_STORAGE);
	while level < finallevel do
		guild:LuaUpdateBuilding(SelfRoleID, 'base903', GUILD_B_HERB_STORAGE);
		level = guild:GetBuildingMaxLevelByType(GUILD_B_HERB_STORAGE);
	end

	-- Wood storehouse
	level = guild:GetBuildingMaxLevelByType(GUILD_B_WOOD_STORAGE);
	while level < finallevel do
		guild:LuaUpdateBuilding(SelfRoleID, 'base904', GUILD_B_WOOD_STORAGE);
		level = guild:GetBuildingMaxLevelByType(GUILD_B_WOOD_STORAGE);
	end

	-- Stone storehouse
	level = guild:GetBuildingMaxLevelByType(GUILD_B_CRYSTAL_STORAGE);
	while level < finallevel do
		guild:LuaUpdateBuilding(SelfRoleID, 'base905', GUILD_B_CRYSTAL_STORAGE);
		level = guild:GetBuildingMaxLevelByType(GUILD_B_CRYSTAL_STORAGE);
	end

	-- Ore storehouse
	level = guild:GetBuildingMaxLevelByType(GUILD_B_SILVER_STORAGE);
	while level < finallevel do
		guild:LuaUpdateBuilding(SelfRoleID, 'base906', GUILD_B_SILVER_STORAGE);
		level = guild:GetBuildingMaxLevelByType(GUILD_B_SILVER_STORAGE);
	end

	guild:AddMoney(100000000, GUILD_CHEST_CONTRIBUTE, false);
	guild:AddHerb(8000000);
	guild:AddWood(8000000);
	guild:AddCrystal(8000000);
	guild:AddSilver(8000000);

end
