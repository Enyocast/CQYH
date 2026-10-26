Include("script/include/btnod.lua")

--------------------------------------------------------------------------------
--overwrie ai data
d.nWalkSpeed = 500 * GAME_FPS / 1000;
d.nRunSpeed = 750 * GAME_FPS / 1000;
d.nWanderRange = 80 * 100;
d.nWanderInterval = 2 * 1000;
d.nPreferDistance = 0;
d.nWithdrawThreshold = 0;
d.nChaseThreshold = 250;
d.nScanEnemyRange = 16 * 100;
d.nScanFriendRange = 8 * 100;
d.nChaseRange = 80 * 100;
d.nChaseDelayTime = 0;
d.nGlobalCDTime = 500;
d.nNormalSpell1 = 0;
d.nNormalSpell1Chance = 0;
d.nNormalSpell1CDTime = 0;
d.nSelfHpPercent1 = 10000;

d.nStepAroundChance = 5000;
d.nStepAroundCDTime = 4000;
d.nChangeTargetChance = 2000;
d.nChangeTargetCDTime = 16000;


--------------------------------------------------------------------------------

Include("script/newai/sub_tree/sub_tree.lh")

LoadPackage("chat_def.pkg")
LoadPackage("attribute_def.pkg")
LoadPackage("id_def.pkg")
LoadPackage("scene.pkg")
LoadPackage("role.pkg")
LoadPackage("spell.pkg")
LoadPackage("spell_book.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("asimov_user.pkg")
LoadPackage("asimov_user_mgr.pkg")
LoadPackage("robot_message_handler.pkg")
LoadPackage("data_manager.pkg")
LoadPackage("teleport.pkg")
LoadPackage("item_bag.pkg")
LoadPackage("item.pkg")
LoadPackage("msg.pkg")
LoadPackage("stall.pkg");

--------------------------------------------------------------------------------

CHAT_CD_TIMER      		= nastCustom + 1;
TEAM_CD_TIMER      		= nastCustom + 2;
JUMP_CD_TIMER      		= nastCustom + 3;
SCAN_ENEMY_CD_TIMER		= nastCustom + 4;
IDLE_FIGHT_CD_TIMER		= nastCustom + 5;
FIGHT_CD_TIMER			= nastCustom + 7;
INTERACT_CD_TIMER		= nastCustom + 8;
QUERY_ROLE_POW_CD_TIMER	= nastCustom +10;
ROTATE_CD_TIMER			= nastCustom +11;
DO_ACTION_TIMER			= nastCustom +12;
STALL_CD_TIMER          = nastCustom +13;
TRADE_CD_TIMER          = nastCustom +14;

JUMP_SCENE_INTERVAL		= 2 * 60 * 1000;
SPELL_INTERVAL			= 1000;
INTERACT_INTERVAL		= 10 * 60 * 1000;
QUERY_ROLE_POW_INTERVAL	= 1 * 60 * 1000;
ROTATE_INTERVAL			= 120 * 1000;
IN_IDLE_INTERVAL		= 30 * 1000;
IN_FIGHT_INTERVAL		= 30 * 1000;
DO_ACTION_INTERVAL		= 1 * 1000;
STALL_INTERVAL          = 60 * 60 * 1000;
TRADE_INTERVAL          = IN_IDLE_INTERVAL / 2;
--------------------------------------------------------------------------------

g_RobotMessageHandler = CRobotMessageHandler:GetInstance();
g_GameWorld = CGameWorld:GetInstance();

g_staticSceneCount = 0;
g_staticScene = {};
g_lineSceneCount = 0;
g_lineScene = {};
--g_dungeonSceneCount = 0;
--g_dungeonScene = {};
g_scene = {};

g_shop_npc = {};

g_ChatString = "1234567890";
g_ActionList = {};

--------------------------------------------------------------------------------
Include("script/newai/robot/stall.lua");
Include("script/newai/robot/chat.lua");
Include("script/newai/robot/team.lua");
Include("script/newai/robot/mail.lua");
Include("script/newai/robot/item.lua");
Include("script/newai/robot/auction.lua");
Include("script/newai/robot/jump.lua");
Include("script/newai/robot/vip.lua");
Include("script/newai/robot/query.lua");
Include("script/newai/robot/combat.lua");
Include("script/newai/robot/title.lua");
Include("script/newai/robot/master.lua");
Include("script/newai/robot/guild.lua");
Include("script/newai/robot/spirit.lua");
Include("script/newai/robot/achievement.lua");
Include("script/newai/robot/ranklist.lua");
Include("script/newai/robot/trade.lua");

ACTION_LIST = {

	-- trade: must in idle
	--{ func_name = "do_trade_action", cd_min = 150, cd_max = 300 },

	{ func_name = "do_chat_action", cd_min = 60, cd_max = 120 },
	{ func_name = "do_team_action", cd_min = 600, cd_max = 1200 },
	{ func_name = "do_mail_action", cd_min = 60, cd_max = 120 },
	{ func_name = "do_auction_action", cd_min = 60, cd_max = 120 },
	{ func_name = "do_vip_action", cd_min = 600, cd_max = 1800 },
	{ func_name = "do_query_role_detail_data", cd_min = 60, cd_max = 120 },
	{ func_name = "do_query_role_pow", cd_min = 60, cd_max = 120 },
	
	-- item prot:
	{ func_name = "do_move_item_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_split_item_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_delete_item_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_pickup_item_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_buy_item_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_sell_item_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_use_item_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_view_sold_item_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_buy_back_item_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_repair_item_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_repair_all_equipped_item_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_refine_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_buy_container_slot_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_organize_bag_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_confirm_randomize_item_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_use_moneytype01_only_action", cd_min = 150, cd_max = 300 },
	{ func_name = "do_check_npc_shop_data_action", cd_min = 150, cd_max = 300 },

	-- combat prot:
	{ func_name = "do_cancel_cutscene", cd_min = 150, cd_max = 300 },
	{ func_name = "do_select_focus", cd_min = 150, cd_max = 300 },
	{ func_name = "do_cancel_spell", cd_min = 150, cd_max = 300 },
	{ func_name = "do_spell_levelup", cd_min = 150, cd_max = 300 },
	{ func_name = "do_combat_pose_switch", cd_min = 150, cd_max = 300 },
	{ func_name = "do_cancel_aura", cd_min = 150, cd_max = 300 },
	{ func_name = "do_adjust_target_pt", cd_min = 150, cd_max = 300 },
	{ func_name = "do_equip_spell", cd_min = 150, cd_max = 300 },
	{ func_name = "do_cast_spell", cd_min = 150, cd_max = 300 },
	{ func_name = "do_directly_cast_spell", cd_min = 150, cd_max = 300 },

	-- title prot:
	{ func_name = "performance_add_title", cd_min = 600, cd_max = 1800 },
	{ func_name = "performance_equip_title", cd_min = 600, cd_max = 1800 },
	{ func_name = "performance_unequip_title", cd_min = 600, cd_max = 1800 },

	-- friend prot:
	{ func_name = "ShieldRole", cd_min = 600, cd_max = 1800 },
	{ func_name = "UnShieldRole", cd_min = 600, cd_max = 1800 },

--[[
	-- master prot:  现在超过20级自动成为师傅，要求机器人初始等级不超过20级
	{ func_name = "BeMaster", cd_min = 600, cd_max = 1800 },
	{ func_name = "GetMasterInfo", cd_min = 600, cd_max = 1800 },
	{ func_name = "GetMasterRecruitList", cd_min = 600, cd_max = 1800 },
	{ func_name = "GetMasterSoloList", cd_min = 600, cd_max = 1800 },
	--{ func_name = "ApplyToTeacher", cd_min = 600, cd_max = 1800 },
	{ func_name = "TeacherAgreeApp", cd_min = 600, cd_max = 1800 },
	{ func_name = "TeacherRefuseApp", cd_min = 600, cd_max = 1800 },
	--{ func_name = "SoloCancelApp", cd_min = 600, cd_max = 1800 },
	{ func_name = "ApplyToStudent", cd_min = 600, cd_max = 1800 },
	{ func_name = "StudentAgreeApp", cd_min = 600, cd_max = 1800 },
	{ func_name = "StudentRefuseApp", cd_min = 600, cd_max = 1800 },
	{ func_name = "TeacherCancelApp", cd_min = 600, cd_max = 1800 },
	{ func_name = "LeaveTeacher", cd_min = 1200, cd_max = 1800 },
	{ func_name = "FireStudent", cd_min = 1800, cd_max = 3600 },
	--{ func_name = "MasterCZ", cd_min = 600, cd_max = 1800 },
	{ func_name = "DesireGraduate", cd_min = 600, cd_max = 1800 },
	{ func_name = "AgreeGraduate", cd_min = 600, cd_max = 1800 },
	{ func_name = "ForceGraduate", cd_min = 600, cd_max = 1800 },
--]]

	-- guild prot:
	{ func_name = "CreateGuild", cd_min = 600, cd_max = 1800 },
	{ func_name = "ViewGuildList", cd_min = 600, cd_max = 1800 },
	{ func_name = "ApplyToJoinGuild", cd_min = 600, cd_max = 1800 },
	{ func_name = "GetApplyGuildAppList", cd_min = 600, cd_max = 1800 },
	{ func_name = "RefuseGuildApp", cd_min = 600, cd_max = 1800 },
	{ func_name = "AgreeGuildApp", cd_min = 600, cd_max = 1800 },
	{ func_name = "InviteToJoinGuild", cd_min = 600, cd_max = 1800 },
	{ func_name = "RevertGuildInvitation", cd_min = 600, cd_max = 1800 },
	{ func_name = "Disband", cd_min = 600, cd_max = 1800 },
	{ func_name = "ChangeNotice", cd_min = 600, cd_max = 1800 },
	{ func_name = "ChangePosition", cd_min = 600, cd_max = 1800 },
	{ func_name = "LeaveGuild", cd_min = 600, cd_max = 1800 },
	{ func_name = "BanishRole", cd_min = 600, cd_max = 1800 },
	{ func_name = "Demise", cd_min = 600, cd_max = 1800 },
	{ func_name = "ForbidChat", cd_min = 600, cd_max = 1800 },
	{ func_name = "DrawSalary", cd_min = 600, cd_max = 1800 },
	{ func_name = "ContributeFund", cd_min = 600, cd_max = 1800 },
	{ func_name = "ChangeWeather", cd_min = 600, cd_max = 1800 },
	{ func_name = "MoreGuildInfo", cd_min = 600, cd_max = 1800 },
	{ func_name = "FindGuild", cd_min = 600, cd_max = 1800 },
	{ func_name = "MoreHistory", cd_min = 600, cd_max = 1800 },
	{ func_name = "MoreChest", cd_min = 600, cd_max = 1800 },
	{ func_name = "ChangeStorageRight", cd_min = 600, cd_max = 1800 },

	{ func_name = "DiplomatApp", cd_min = 600, cd_max = 1800 },
	{ func_name = "GetApplyUnionList", cd_min = 600, cd_max = 1800 },
	{ func_name = "ReplyUnionApp", cd_min = 600, cd_max = 1800 },


	-- spirit prot:
	{ func_name = "performance_spirit_exp_change", cd_min = 600, cd_max = 1800 },
	{ func_name = "performance_spirit_add_air", cd_min = 600, cd_max = 1800 },
	{ func_name = "performance_spirit_move_air", cd_min = 600, cd_max = 1800 },
	{ func_name = "performance_spirit_merge_air", cd_min = 600, cd_max = 1800 },
	{ func_name = "performance_spirit_buy_air_slot", cd_min = 600, cd_max = 1800 },
	{ func_name = "performance_spirit_exchange_air", cd_min = 600, cd_max = 1800 },
	{ func_name = "performance_spirit_open_blood", cd_min = 600, cd_max = 1800 },
	{ func_name = "performance_spirit_brush_slot", cd_min = 600, cd_max = 1800 },

	-- achievement port:
	--{ func_name = "performance_achievement_complete", cd_min = 600, cd_max = 1800 },

	-- ranklist port:
	{ func_name = "performance_ranklist_query", cd_min = 600, cd_max = 1800 },

};

--------------------------------------------------------------------------------
--progrom code
--------------------------------------------------------------------------------

function insert_into_action_list(node, action, trigger_frame)
	local new_node = { next = nil, data = action, frame = trigger_frame };

	while node.next do
		if node.next.frame <= trigger_frame then
			node = node.next;
		else
			break;
		end
	end

	new_node.next = node.next;
	node.next = new_node;
end

function init_action_list(owner)
	local id = owner:GetObjID();
	if g_ActionList[id] == nil then
		g_ActionList[id] = { next = nil, data = nil, frame = 0 };
		for i,v in ipairs(ACTION_LIST) do
			if _G[v.func_name] == nil then
				print("cannot find action function "..v.func_name);
			else
				local trigger_frame = math.random(v.cd_min, v.cd_max) * GAME_FPS + g_GameWorld:GetGameFrame();
				insert_into_action_list(g_ActionList[id], v, trigger_frame);
			end
		end
	end

	return brvSuccess;
end

function do_action(owner)
	local currentFrame = g_GameWorld:GetGameFrame();
	local id = owner:GetObjID();

	if g_ActionList[id] == nil then
		print("empty g_ActionList["..id.."]");
		return brvFail;
	end
	local node = g_ActionList[id].next;
	if node == nil then
		print("empty action list");
		return brvError;
	end
	if node.frame <= currentFrame then
		local action = node.data;
		print("role "..owner:GetName().." trigger action "..action.func_name);
		_G[action.func_name](owner);

		g_ActionList[id].next = node.next;
		local trigger_frame = math.random(action.cd_min, action.cd_max) * GAME_FPS + g_GameWorld:GetGameFrame();
		insert_into_action_list(g_ActionList[id], action, trigger_frame);

		return brvSuccess;
	end

	return brvFail;
end

function reset_pk_value(owner)
	local currentFrame = g_GameWorld:GetGameFrame();
	local id = owner:GetObjID();
	if (id % (GAME_FPS * 30) ) ~= (currentFrame % (GAME_FPS * 30) ) then
		return brvSuccess;
	end

    local role = tolua.cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
	if user == nil then
		print("can't get user by SessionID");
		return brvError;
	end

    user:GMCommand("TargetRole:SetPkValue(0)");
	role:SetPkValue(0);
	return brvSuccess;
end

function add_jump_point(scene_id, x, y, z)
    local scene_data = CDataManager_SCENE_DATA_:GetInstance():GetData(scene_id)
    if scene_data == nil then
		print("can't find scene_data "..scene_id);
        return
    end

    local pos = get_near_pos(scene_id, x, y, z, 16, 1);
	if not pos then
		print("cannot find near pos for ["..x..","..y..","..z.."]@"..scene_id);
		return
	end
    if #pos > 0 then
        local scene_pos = {};
        scene_pos.sceneTempID = scene_id;
        scene_pos.X = pos[1].x / POINT_PER_CM;
        scene_pos.Y = pos[1].y / POINT_PER_CM;
        scene_pos.Z = pos[1].z / POINT_PER_CM;

		local sx, sy, sz = ConvertCoordN2O(scene_pos.X,scene_pos.Y,scene_pos.Z);
        scene_pos.X = sx;
        scene_pos.Y = sy;
        scene_pos.Z = sz;

        if scene_data.nType == estStatic then
	        g_staticSceneCount = g_staticSceneCount + 1;
	        g_staticScene[g_staticSceneCount] = scene_pos;
        elseif scene_data.nType == estLine then
	        g_lineSceneCount = g_lineSceneCount + 1;
	        g_lineScene[g_lineSceneCount] = scene_pos;
        end

        if not g_scene[scene_id] then
			g_scene[scene_id] = {};
		end
		table.insert(g_scene[scene_id], scene_pos);
    end
end

function performance_init()
	if g_staticSceneCount > 0 then
		return brvSuccess;
	end

	for i = 50, 256 do
		local sceneData = CDataManager_SCENE_DATA_:GetInstance():GetData(i);
		if sceneData ~= nil then
			local oStaticData = CSceneFileMgr:GetInstance():GetStaticData(i);
			if oStaticData ~= nil then
				local oTeleport;
				local shop_npc_list = {};

				for j = 0, oStaticData:GetSingleNpcCount() do
					local npc_info = {};
					local spawn_pt, npc_data = get_npc(oStaticData, j);
					if npc_data ~= nil and npc_data.nShopID ~= 0 then
						npc_info.x = spawn_pt.nX;
						npc_info.y = spawn_pt.nY;
						npc_info.z = spawn_pt.nZ;
						npc_info.template_id = npc_data.nTemplateID;
						npc_info.single_npc_id = j;
						table.insert(shop_npc_list, npc_info);
					end
				end

				g_shop_npc[i] = shop_npc_list;

				for j = 1, 31 do
					oTeleport = oStaticData:FindTeleportPoint(j);
				    if oTeleport ~= nil then
				        add_jump_point(oTeleport.SrcSceneID, oTeleport.SrcSceneX, oTeleport.SrcSceneY, oTeleport.SrcSceneZ);
				        add_jump_point(oTeleport.TargetSceneID, oTeleport.TargetSceneX, oTeleport.TargetSceneY, oTeleport.TargetSceneZ);
					--[[
					    local srcSceneData = CDataManager_SCENE_DATA_:GetInstance():GetData(oTeleport.SrcSceneID);
					    local targetSceneData = CDataManager_SCENE_DATA_:GetInstance():GetData(oTeleport.TargetSceneID);

						if srcSceneData == nil or oTeleport.SrcSceneID ~= i or targetSceneData == nil then
							print("cannot find srcSceneData "..i.." or don't match oTeleport.SrcSceneID "..oTeleport.SrcSceneID );
							print("cannot find targetScene "..oTeleport.TargetSceneID.." for oTeleport "..j.." of scene "..i );
						else
							if (srcSceneData.nType == estStatic or srcSceneData.nType == estLine) and
								targetSceneData.nType == estDungeon then
								table.insert(g_dungeonScene, oTeleport);
								g_dungeonSceneCount = g_dungeonSceneCount + 1;
							end
						end
					--]]
					end
				end

				for x = 100 * POINT_PER_METER, oStaticData:GetMaxZoneX() * ZONE_WIDTH, 50 * POINT_PER_METER do
				    for y = 100 * POINT_PER_METER, oStaticData:GetMaxZoneY() * ZONE_WIDTH, 50 * POINT_PER_METER do
				        add_jump_point(i, x, y, 100000 * POINT_PER_CM);
				    end
				end

                init_stall_pos(i, oStaticData);
			end
		end
	end

	for k,v in pairs(g_scene) do
		local sceneData = CDataManager_SCENE_DATA_:GetInstance():GetData(k);
		if sceneData.nType == estDungeon then
			print("dungeon scene "..k.." pos "..#v);
		end
	end

	for k,v in pairs(g_scene) do
		local sceneData = CDataManager_SCENE_DATA_:GetInstance():GetData(k);
		if sceneData.nType ~= estDungeon then
			print("static scene "..k.." pos "..#v);
		end
	end

    return brvSuccess;
end

local validSpellTable = {};

function performance_fight(owner)
	local processor = owner:GetAIProcessor();
    local role = tolua.cast(owner, 'CRole');
    local user =  CUserMgr:GetInstance():FindUser(role:GetSessionID());

    if role:IsCasting() then
		return brvFail;
    end

	local role_id = role:GetSessionID();
	if not validSpellTable[role_id] then
		validSpellTable[role_id] = {};
		for k = qssKey0, qssKey11 do
			if role:GetSpellSlot(k) ~= nil then
				--print("role "..role_id.." add valid spell slot "..k);
				table.insert(validSpellTable[role_id],k);
			end
		end
	end

	local dwTargetID = processor:GetTargetID();
	local poTarget = g_GameWorld:FindCharacter(dwTargetID);
	if poTarget ~= nil then
		--local spellSlot = math.random(qssKey0, qssKey11);
		local spellSlot = validSpellTable[role_id][math.random(1,#(validSpellTable[role_id]))];
		--print("role "..role_id.." cast valid spell slot "..spellSlot);
	--[[
		if role:GetClass() == clsWarrior and 
		   spell:GetAttr(satCastType) == spctSwitch
		 then
			user:CastSwitchSpell(spellSlot, dwTargetID, poTarget:GetX(), poTarget:GetY(), poTarget:GetZ());
		end
	--]]
		user:CastSpell(spellSlot, dwTargetID, poTarget:GetX(), poTarget:GetY(), poTarget:GetZ());
		return brvSuccess;
	end

    return brvFail;
end

InteractNpcIDTable = {};

function init_npc_table()
    local npc_data = CDataManager_NPC_DATA_:GetInstance():GetFirstData();
    while npc_data do
        if npc_data.nForceID == 26 then
            table.insert(InteractNpcIDTable, npc_data.nTemplateID);
        end
        npc_data = CDataManager_NPC_DATA_:GetInstance():GetNextData();
    end
    print("init npc data "..#InteractNpcIDTable);
end

Include("script/newai/robot/main.uh");
