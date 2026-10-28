LoadPackage("common.pkg")
LoadPackage("scene.pkg")
LoadPackage("guild_def.pkg")
LoadPackage("gs_guild.pkg")
LoadPackage("guild_mgr.pkg")
LoadPackage("data_manager.pkg")
LoadPackage("character.pkg")
LoadPackage("npc.pkg")
LoadPackage("char_def.pkg")
LoadPackage("role.pkg")
LoadPackage("ai.pkg")


-- 公会温泉

-- attack
GUILD_WAR_FACTION_A = 1;
-- defend
GUILD_WAR_FACTION_D = 2;

-- raw
RAW_FACTION = 0;

REPUTATION_TYPE = 26;

WAIT_TO_TELEPORT_TIME = 30000;		-- ms


-- deity npc
DEITY_NPC_NAMEID = "Insc01";
DEITY_NPC_ID_LIST =
{
	[0] = 6898;    -- 0级
	[1] = 6899;    -- 1级
	[2] = 6900;
	[3] = 6901;
	[4] = 6902;
	[5] = 6903;
	[6] = 6903;    -- 6级
};


g_GuildMgr = CGuildMgr:GetInstance();



function BuildingDead(scene, npc_id, building_type, building_level)
	local npc = scene:FindNpc(npc_id);
	local building_template = CDataManager_GUILD_BUILDING_DATA_:GetInstance():GetData(building_type * 65536 + building_level);

	local old_ai_id = npc:GetNpcData().nAIID;
	npc:SetLevel(building_level);
	npc:SetTemplateData(building_template.dwDeadNpcTemplateID);
	npc:IncControlCount(cclInvincible);

	local new_ai_id = npc:GetNpcData().nAIID;

	if old_ai_id ~= new_ai_id then
		npc:GetAIProcessor():CallInitBT();
	end
end



function RefreshBuilding(scene, npc_id, building_type, building_level, npc_level, bInvincible)
	local npc = scene:FindNpc(npc_id);
	local building_template = CDataManager_GUILD_BUILDING_DATA_:GetInstance():GetData(building_type * 65536 + building_level);

	local old_ai_id = npc:GetNpcData().nAIID;

	--print("building"..building_type.."npcid"..npc_id);
	npc:SetLevel(npc_level);
	npc:SetTemplateData(building_template.dwNpcTemplateID);

	if bInvincible == true then
		npc:IncControlCount(cclInvincible);
	else
		npc:DecControlCount(cclInvincible);
	end

	local new_ai_id = npc:GetNpcData().nAIID;

	if old_ai_id ~= new_ai_id then
		npc:GetAIProcessor():CallInitBT();
	end

	--npc:GetAIProcessor():SetVariable(2, 1);
end


function DisplayingUpgradeBuilding(scene, npc_id, building_type, building_level)
	local npc = scene:FindNpc(npc_id);
	local building_template = CDataManager_GUILD_BUILDING_DATA_:GetInstance():GetData(building_type * 65536 + building_level);

	npc:CastSpell(building_template.dwUpgradingSpellID, npc, npc:GetX(), npc:GetY(), npc:GetZ());
end


function RefreshDeity(scene, npc_id, building_level, npc_level, revive_time)
	-- main
	if revive_time == 0 then
		RefreshBuilding(scene, npc_id, GUILD_B_DEITY, building_level, npc_level, false);
	else
		BuildingDead(scene, npc_id, GUILD_B_DEITY, building_level);
		return ;
	end

	-- npc
	local npc_spawn_point = scene:GetStaticData():GetSingleNpc(DEITY_NPC_NAMEID);
	local npc = scene:FindNpc(npc_spawn_point.nID);

	npc:SetTemplateData(DEITY_NPC_ID_LIST[building_level]);

end


function RefreshMainBuilding(scene, npc_id, building_level, npc_level, revive_time)

	-- main
	if revive_time == 0 then
		RefreshBuilding(scene, npc_id, GUILD_B_MAIN, building_level, npc_level, false);
	else
		BuildingDead(scene, npc_id, GUILD_B_MAIN, building_level);
		return ;
	end

	--local guild = g_GuildMgr:FindGuild(scene:GetSceneID());

	-- wall
	--local npc_spawn_point = scene:GetStaticData():GetSingleNpcByName(g_GuildMgr:GetWallID());
	--local building = guild:GetBuildingDataByNpcID(npc_spawn_point.qwNameID);

	--if building.dwReviveTime == 0 then
	--	RefreshBuilding(scene, npc_spawn_point.nID, GUILD_B_WALL, building_level, npc_level, false);
	--else
	--	BuildingDead(scene, npc_spawn_point.nID, GUILD_B_WALL, building.nLevel);
	--end

	-- gate
	--for i = 0, g_GuildMgr:GetGateNum() - 1, 1 do
	--	npc_spawn_point = scene:GetStaticData():GetSingleNpcByName(g_GuildMgr:GetGateID(i));
	--	building = guild:GetBuildingDataByNpcID(npc_spawn_point.qwNameID);

	--	if building.dwReviveTime == 0 then
	--		RefreshBuilding(scene, npc_spawn_point.nID, GUILD_B_GATE, building_level, npc_level, false);
	--	else
	--		BuildingDead(scene, npc_spawn_point.nID, GUILD_B_GATE, building.nLevel);
	--	end
	--end

	-- protector
	--npc_spawn_point = scene:GetStaticData():GetSingleNpcByName(g_GuildMgr:GetProtectorID());
	--building = guild:GetBuildingDataByNpcID(npc_spawn_point.qwNameID);
	--if building.dwReviveTime == 0 then
	--	RefreshBuilding(scene, npc_spawn_point.nID, GUILD_B_PROTECTOR, building_level, npc_level, false);
	--else
	--	BuildingDead(scene, npc_spawn_point.nID, GUILD_B_PROTECTOR, building.nLevel);
	--end
end





-- evt
function UpgradeBuilding(owner)
	DisplayingUpgradeBuilding(owner, owner:GetVariable(1), owner:GetVariable(2), owner:GetVariable(3));
	return brvSuccess;
end

function UpdateBuilding(owner)

	local building_type = owner:GetVariable(2);
	if building_type == GUILD_B_MAIN then
		RefreshMainBuilding(owner, owner:GetVariable(1), owner:GetVariable(3), owner:GetVariable(3), 0);
	elseif building_type == GUILD_B_DEITY then
		RefreshDeity(owner, owner:GetVariable(1), owner:GetVariable(3), owner:GetVariable(3), 0);
	else
		RefreshBuilding(owner, owner:GetVariable(1), owner:GetVariable(2), owner:GetVariable(3), owner:GetVariable(3), false);
	end
	return brvSuccess;
end

function DeleteBuilding(owner)
	RefreshBuilding(owner, owner:GetVariable(1), owner:GetVariable(2), owner:GetVariable(3), 1, true);
	return brvSuccess;
end


-- evt
function InitGuildBuilding(owner)
	local scene = owner;

	local guild = g_GuildMgr:FindGuild(scene:GetSceneID());

	-- function building
	for i = GUILD_B_MAIN, GUILD_B_FUNATIONAL_NUM - 1, 1 do
		local building = guild:GetFunBuildingDataByType(i);

		if building.nType ~= 0 then
			local npc_spawn_point = scene:GetStaticData():GetSingleNpcByName(building.qwNameID);
			if npc_spawn_point ~= nil then
				if building.nType == GUILD_B_MAIN then
					RefreshMainBuilding(scene, npc_spawn_point.nID, building.nLevel, building.nLevel, building.dwReviveTime);
				elseif building.nType == GUILD_B_DEITY then
					RefreshDeity(scene, npc_spawn_point.nID, building.nLevel, building.nLevel, building.dwReviveTime);
				else
					if building.dwReviveTime == 0 then
						RefreshBuilding(scene, npc_spawn_point.nID, building.nType, building.nLevel, building.nLevel, false);
					else
						BuildingDead(scene, npc_spawn_point.nID, building.nType, building.nLevel);
					end
				end
			end
		end
	end

	-- unfunction building
	local ub = guild:FirstUnFunBuilding();
	while ub ~= nil do
		if ub.nType ~= GUILD_B_WALL and ub.nType ~= GUILD_B_GATE and ub.nType ~= GUILD_B_PROTECTOR then
			local npc_spawn_point = scene:GetStaticData():GetSingleNpcByName(ub.qwNameID);
			if npc_spawn_point ~= nil then
				if ub.dwReviveTime == 0 then
					RefreshBuilding(scene, npc_spawn_point.nID, ub.nType, ub.nLevel, ub.nLevel, false);
				else
					BuildingDead(scene, npc_spawn_point.nID, ub.nType, ub.nLevel);
				end
			end
		end

		ub = guild:NextUnFunBuilding();
	end


	-- upgrade building
	local u = guild:FirstUpgradeBuilding();
	while u ~= nil do
		local npc_spawn_point = scene:GetStaticData():GetSingleNpcByName(u.qwNameID);
		if npc_spawn_point ~= nil then
			DisplayingUpgradeBuilding(scene, npc_spawn_point.nID, u.nType, u.nLevel);
		end

		u = guild:NextUpgradeBuilding();
	end

	return brvSuccess;
end



Include("script/include/btnod.lua")
Include("script/scene/MirGd01/scene_bt.lua")

