LoadPackage("robot_message_handler.pkg")
LoadPackage("guild_def.pkg")
LoadPackage("scene_def.pkg")

TestCase.Guild = {};

function PreCreateGuild(user, role)
	ret = user:GMCommand("AddItem 80002 10");
	check(ret, "failed to send gm command");

	ret = user:GMCommand("Level 15");
	check(ret, "failed to send gm command");

	ret = user:GMCommand("AddExp 3000000");
	check(ret, "failed to send gm command");

	ret = user:GMCommand("AddMoney 1 5000000");
	check(ret, "failed to send gm command");

	ret = user:GMCommand("AddMoney 2 5000000");
	check(ret, "failed to send gm command");
end


function NewUser()
	local user_name = "Ga" .. os.date("%Y%H%M%S");
	local user, role = startup(user_name, user_name, 1);
    check(user, "failed to create user");
    check(role, "failed to create role");
	local session_id = user:GetSessionID();

	return user, role, session_id, user_name;
end

function ReLogin(user_name)
	local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
	local session_id = user:GetSessionID();

	return user, role, session_id;
end

function CreateGuild(role, user, session_id, user_name, guild_name, announce)
	local msg;
	PreCreateGuild(user, role);
	wait(10);
	g_RobotMessageHandler:DoGuildCreate(role, guild_name, announce);
	msg = recv_msg(10, session_id,  protocol.m2c_create_guild_ack);
	check(msg, "failed to recv m2c_create_guild_ack");
end

function GetGuildIDByFind(role, session_id, guild_name)
	local msg;
	g_RobotMessageHandler:DoFindGuild(role, guild_name);
	msg = recv_msg(10, session_id, protocol.m2c_find_guild_ack);
	check(msg, "failed to recv protocol.m2c_find_guild_ack");

	return msg.data.dwGuildID;
end

function GetGuildMemberApp(role, session_id)
	local	msg;
	g_RobotMessageHandler:DoGetApplyGuildList(role);
	msg = recv_msg(10, session_id, protocol.m2c_get_apply_guild_list_ack);
	check(msg, "failed to recv protocol.m2c_get_apply_guild_list_ack");
	print("get guild member app num: "..msg.wAppCount);

	return msg;
end

function ApplyToJoinGuild(role, session_id, guild_id)
	local msg;
	print("role: "..role:GetObjID().." begin to apply!");
	g_RobotMessageHandler:DoGuildApplyToJoinGuild(role, guild_id);
	--msg = recv_msg(80, session_id, protocol.m2c_apply_to_join_guild_ack);
	--check(msg, "failed to recv protocol.m2c_apply_to_join_guild_ack");
	--check(msg.dwGuildID == guild_id, "failed to apply guild member!");
end

function TestCase.Guild.GuildApply()
	local guild_name = "惜缘阁";
	--local guild_name = "G"..os.date("%Y%H%M%S");
	local announce = "only test";
	local guild_id = 0;
	local app_role_table = {};
	local user, role, session_id, user_name;
	local applicant_num= 4;	-- 一级50个人，因为已经有帮主了，所以49个人申请

	user, role, session_id, user_name = NewUser();

	CreateGuild(role, user, session_id, user_name, guild_name, announce);
	cleanup(user);

	wait(1);
	-- apply
	for i = 1,applicant_num,1 do
		app_role_table[i] = {};
		app_role_table[i].user, app_role_table[i].role, app_role_table[i].session_id, app_role_table[i].user_name = NewUser();
		print("NewUser:  "..i);
		wait(1);
	end

	check(1, "create user success");
	-- 通过find取到guild id
	guild_id = GetGuildIDByFind(app_role_table[1].role, app_role_table[1].session_id, guild_name);
	print(guild_id);

	check(1, "find guild success");

	for k, v in pairs(app_role_table) do
		print("check role id: "..v.role:GetObjID());
		ApplyToJoinGuild(v.role, v.session_id, guild_id);
		wait(0.5);
	end

	check(1, "join guild success");
	for k, v in pairs(app_role_table) do
		cleanup(v.user);
		wait(0.5);
	end

	-- get apply guild list
	user, role, session_id = ReLogin(user_name);

	local msg_data = GetGuildMemberApp(role, session_id);
	check(msg_data.wAppCount > 0, "protocol.m2c_get_apply_guild_list_ack data error!");


	local roleID_table = {};
	for i = 0, msg_data.wAppCount - 1, 1 do
		roleID_table[i] = msg_data.info[i].dwRoleID;
	end
	roleID_table.count = msg_data.wAppCount - 1;

	-- refuse
	for i = 0, roleID_table.count do
		print(i.." "..roleID_table[i]);

		g_RobotMessageHandler:DoGetRevertGuildApp(role, 1, roleID_table[i]);
		msg = recv_msg(10, session_id, protocol.m2c_revert_guild_apply_ack);
		check(msg, "failed to recv protocol.m2c_revert_guild_apply_ack");
		check(msg.dwRoleID == roleID_table[i], "recv protocol.m2c_revert_guild_apply_ack data error");
	end

	-- double check
	msg_data = GetGuildMemberApp(role, session_id);
	check(0 == msg_data.wAppCount, "protocol.m2c_get_apply_guild_list_ack data error!");
	cleanup(user);


	--
	--
	-- apply again
	--for k,v in pairs(app_role_table) do
		--v.user, v.role, v.session_id = ReLogin(v.user_name);
		--wait(0.5);
	--end
	for i = 1,applicant_num,1 do
		app_role_table[i].user, app_role_table[i].role, app_role_table[i].session_id = ReLogin(app_role_table[i].user_name);
		wait(0.5);
	end

	for k,v in pairs(app_role_table) do
		ApplyToJoinGuild(v.role, v.session_id, guild_id);
		wait(0.5);
	end

	print("Apply to join Guild Success!");

	-- get apply guild list
	user, role, session_id = ReLogin(user_name);
	msg_data = GetGuildMemberApp(role, session_id);
	check(msg_data.wAppCount > 0, "protocol.m2c_get_apply_guild_list_ack data error!");

	--  agree
	print("app_count "..msg_data.wAppCount);
	for i = 1, msg_data.wAppCount, 1 do
		g_RobotMessageHandler:DoGetRevertGuildApp(role, 2, app_role_table[i].role:GetObjID());
		msg = recv_msg(10, app_role_table[i].session_id, protocol.m2c_guild_info_ntf);
		check(msg, "failed to recv protocol.m2c_guild_info_ntf");
		wait(0.5);
	end

	print("Agree to join Guild Success!");

	-- double check
	msg_data = GetGuildMemberApp(role, session_id);
	check(0 == msg_data.wAppCount, "protocol.m2c_get_apply_guild_list_ack data error!");

	-- demise
	g_RobotMessageHandler:DoGuildDemise(role, app_role_table[1].role:GetObjID());
	msg = recv_msg(10,  app_role_table[1].session_id, protocol.m2c_guild_demise_ntf);
	check(msg, "failed to recv m2c_guild_demise_ntf");

	cleanup(user);
	for k, v in pairs(app_role_table) do
		cleanup(v.user);
		wait(0.5);
	end
end

function InviteAndSoOn()
	local guild_name = "G"..os.date("%Y%H%M%S");
	local announce = "only test";

	local user, role, session_id, user_name = NewUser();
	wait(1);
	local app_user, app_role, app_session_id, app_user_name = NewUser();

	PreCreateGuild(user, role);
	wait(10);

	g_RobotMessageHandler:DoGuildCreate(role, guild_name, announce);
	msg = recv_msg(50, session_id,  protocol.m2c_create_guild_ack);
	check(msg, "failed to recv m2c_create_guild_ack");

	-- invite
	g_RobotMessageHandler:DoInviteToJointGuild(role, app_user_name);
	msg = recv_msg(50, app_session_id, protocol.m2c_be_invited_to_join_guild);
	check(msg, "failed to recv m2c_be_invited_to_join_guild");

	-- revert the invitation
	g_RobotMessageHandler:DoRevertTheInvitation(app_role, 1, msg.dwRoleID);	-- refuse
	msg = recv_msg(50, session_id, protocol.m2c_invite_to_join_guild_ack);
	check(msg, "failed to recv m2c_invite_to_join_guild_ack");

	wait(3);

	-- invite
	g_RobotMessageHandler:DoInviteToJointGuild(role, app_user_name);
	msg = recv_msg(50, app_session_id, protocol.m2c_be_invited_to_join_guild);
	check(msg, "failed to recv m2c_be_invited_to_join_guild");

	-- revert the invitation
	g_RobotMessageHandler:DoRevertTheInvitation(app_role, 2, msg.dwRoleID);	-- agree
	msg = recv_msg(50, app_session_id, protocol.m2c_guild_info_ntf);
	check(msg, "failed to recv protocol.m2c_guild_info_ntf");


	-- forbid chat
	g_RobotMessageHandler:DoGuildForbidChat(role, 1, app_role:GetObjID());
	msg = recv_msg(50, app_session_id, protocol.m2c_guild_forbid_chat_ntf);
	check(msg, "failed to recv m2c_guild_forbid_chat_ntf");

	-- change position
	g_RobotMessageHandler:DoGuildChangePosition(role, 6, app_role:GetObjID());
	msg  = recv_msg(50, app_session_id, protocol.m2c_guild_change_position_ntf);
	check(msg, "failed to recv m2c_guild_change_position_ntf");

	-- donation
	--g_RobotMessageHandler:DoGuildDonation(role, 1000);
	--msg = recv_msg(50, session_id, protocol.m2c_guild_attr_modify_ntf);
	--check(msg, "failed to recv m2c_guild_attr_modify_ntf");

	-- change storage right
	g_RobotMessageHandler:DoGuildStorageRight(role, 7, 0);
	msg = recv_msg(50, session_id, protocol.m2c_guild_change_storage_right_ntf);
	check(msg, "failed to recv m2c_guild_change_storage_right_ntf");

	-- leave
	--g_RobotMessageHandler:DoGuildRoleLeave(app_role);
	--msg = recv_msg(50, app_session_id, protocol.m2c_guild_role_leave_ack);
	--check(msg , "failed to recv m2c_guild_role_leave_ack");

	-- banish
	g_RobotMessageHandler:DoGuildBanish(role, app_role:GetObjID());
	msg = recv_msg(50, app_session_id, protocol.m2c_guild_role_leave_ack);
	check(msg , "failed to recv m2c_guild_role_leave_ack");


	cleanup(user);
	cleanup(app_user);
end

function DiplomatEnemy()
    local ret;
    local msg;
	local apply_guild_name = "G"..os.date("%Y%H%M%S").."a";
	local revert_guild_name = "G"..os.date("%Y%H%M%S").."r";
	local announce = "only test";
	local apply_guild_id , revert_guild_id;

	-- craete guild
	local apply_user, apply_role, apply_session_id, apply_user_name = NewUser();
	wait(1);
	local revert_user, revert_role, revert_session_id, revert_user_name = NewUser();

	PreCreateGuild(apply_user, apply_role);
	wait(5);
	g_RobotMessageHandler:DoGuildCreate(apply_role, apply_guild_name, announce);
	msg = recv_msg(50, apply_session_id,  protocol.m2c_create_guild_ack);
	check(msg, "failed to recv m2c_create_guild_ack");
	apply_guild_id = msg.dwGuildID;

	PreCreateGuild(revert_user, revert_role);
	wait(5);
	g_RobotMessageHandler:DoGuildCreate(revert_role, revert_guild_name, announce);
	msg = recv_msg(50, revert_session_id,  protocol.m2c_create_guild_ack);
	check(msg, "failed to recv m2c_create_guild_ack");
	revert_guild_id = msg.dwGuildID;

	print(revert_session_id);

	-- donation
	g_RobotMessageHandler:DoGuildDonation(apply_role, 0, 10000);
	msg = recv_msg(50, apply_session_id, protocol.m2c_guild_attr_modify_ntf);
	check(msg, "failed to recv m2c_guild_attr_modify_ntf");

	wait(3);

	g_RobotMessageHandler:DoGuildDonation(revert_role, 0, 10000);
	msg = recv_msg(50, revert_session_id, protocol.m2c_guild_attr_modify_ntf);
	check(msg, "failed to recv m2c_guild_attr_modify_ntf");

	-- Diplomat
	-- enemy
	print(revert_session_id);
	g_RobotMessageHandler:DoGuildDiplomatApply(apply_role, 2, 1, revert_guild_name);
	msg = recv_msg(50, revert_session_id, protocol.m2c_guild_add_diplomat_ntf);
	--msg = recv_msg_and(50, revert_session_id, protocol.m2c_guild_add_diplomat_ntf,
	--						apply_session_id, protocol.m2c_guild_add_diplomat_ntf);
	check(msg, "failed to recv m2c_guild_add_diplomat_ntf");
	--local temp_count = 0;
	--for k,v in pairs(msg) do
	--	if v.msgID == protocol.m2c_guild_add_diplomat_ntf then
	--		temp_count = temp_count + 1;
	--	else
	--		check(nil, "failed to recv m2c_guild_add_diplomat_ntf msg");
	--	end
	--end
	--print(temp_count);
	--check(2 == temp_count, "failed to recv m2c_guild_add_diplomat_ntf");

	-- failed check
	g_RobotMessageHandler:DoGuildDiplomatApply(apply_role, 2, 1, revert_guild_name);
	msg = recv_msg(10, apply_session_id, protocol.m2c_guild_add_diplomat_ntf);
	check(msg == nil, "failed to recv m2c_guild_add_diplomat_ntf");

	g_RobotMessageHandler:DoGuildDiplomatApply(revert_role, 2, 1, apply_guild_name);
	msg = recv_msg(10, revert_session_id, protocol.m2c_guild_add_diplomat_ntf);
	check(msg == nil, "failed to recv m2c_guild_add_diplomat_ntf");

	cleanup(apply_user);
	cleanup(revert_user);
end

function DiplomatAlliance()
    local ret;
    local msg;
	local apply_guild_name = "G1"..os.date("%Y%H%M%S");
	local revert_guild_name = "G2"..os.date("%Y%H%M%S");
	local announce = "only test";
	local apply_guild_id , revert_guild_id;

	--
	local apply_user, apply_role, apply_session_id, apply_user_name = NewUser();
	wait(2);
	local revert_user, revert_role, revert_session_id, revert_user_name = NewUser();

	PreCreateGuild(apply_user, apply_role);
	wait(10);
	g_RobotMessageHandler:DoGuildCreate(apply_role, apply_guild_name, announce);
	msg = recv_msg(10, apply_session_id,  protocol.m2c_create_guild_ack);
	check(msg, "failed to recv m2c_create_guild_ack");
	apply_guild_id = msg.dwGuildID;

	PreCreateGuild(revert_user, revert_role);
	wait(10);
	g_RobotMessageHandler:DoGuildCreate(revert_role, revert_guild_name, announce);
	msg = recv_msg(10, revert_session_id,  protocol.m2c_create_guild_ack);
	check(msg, "failed to recv m2c_create_guild_ack");
	revert_guild_id = msg.dwGuildID;

	-- donation
	g_RobotMessageHandler:DoGuildDonation(apply_role, 0, 10000);
	msg = recv_msg(10, apply_session_id, protocol.m2c_guild_attr_modify_ntf);
	check(msg, "failed to recv m2c_guild_attr_modify_ntf");

	wait(3);

	g_RobotMessageHandler:DoGuildDonation(revert_role, 0, 10000);
	msg = recv_msg(10, revert_session_id, protocol.m2c_guild_attr_modify_ntf);
	check(msg, "failed to recv m2c_guild_attr_modify_ntf");

	-- Diplomat
	-- alliance
	g_RobotMessageHandler:DoGuildDiplomatApply(apply_role, 1, 1, revert_guild_name);
	msg = recv_msg(10, apply_session_id, protocol.m2c_guild_apply_alliance_ack);
	check(msg, "failed to recv m2c_guild_add_diplomat_ntf");
	-- failed check
	g_RobotMessageHandler:DoGuildDiplomatApply(apply_role, 1, 1, revert_guild_name);
	msg = recv_msg(10, apply_session_id, protocol.m2c_guild_apply_alliance_ack);
	check(nil == msg, "failed to recv m2c_guild_add_diplomat_ntf");

	g_RobotMessageHandler:DoGuildGetApplyUnionList(revert_role);
	msg = recv_msg(10, revert_session_id, protocol.m2c_guild_get_apply_union_list_ack);
	check(msg, "failed to recv m2c_guild_get_apply_union_list_ack");
	-- refuse
	g_RobotMessageHandler:DoGuildRevertUnionApp(revert_role, 1, msg.info[0].dwGuildID);
	msg = recv_msg(10, revert_session_id, protocol.m2c_guild_reply_union_app_ack);
	check(msg, "failed to recv m2c_guild_reply_union_app_ack");

	-- alliance again
	g_RobotMessageHandler:DoGuildDiplomatApply(apply_role, 1, 1, revert_guild_name);
	msg = recv_msg(10, apply_session_id, protocol.m2c_guild_apply_alliance_ack);
	check(msg, "failed to recv m2c_guild_add_diplomat_ntf");

	g_RobotMessageHandler:DoGuildGetApplyUnionList(revert_role);
	msg = recv_msg(10, revert_session_id, protocol.m2c_guild_get_apply_union_list_ack);
	check(msg, "failed to recv m2c_guild_get_apply_union_list_ack");
	-- agree
	g_RobotMessageHandler:DoGuildRevertUnionApp(revert_role, 2, msg.info[0].dwGuildID);
	msg = recv_msg(10, apply_session_id, protocol.m2c_guild_add_diplomat_ntf);
	check(msg, "failed to recv m2c_guild_add_diplomat_ntf");


	-- failed check
	g_RobotMessageHandler:DoGuildDiplomatApply(apply_role, 2, 1, revert_guild_name);
	msg = recv_msg(10, apply_session_id, protocol.m2c_guild_add_diplomat_ntf);
	check(msg == nil, "failed to recv m2c_guild_add_diplomat_ntf");

	g_RobotMessageHandler:DoGuildDiplomatApply(apply_role, 1, 1, revert_guild_name);
	msg = recv_msg(10, apply_session_id, protocol.m2c_guild_add_diplomat_ntf);
	check(msg == nil, "failed to recv m2c_guild_add_diplomat_ntf");

	g_RobotMessageHandler:DoGuildDiplomatApply(revert_role, 1, 1, apply_guild_name);
	msg = recv_msg(10, revert_session_id, protocol.m2c_guild_add_diplomat_ntf);
	check(msg == nil, "failed to recv m2c_guild_add_diplomat_ntf");

	cleanup(apply_user);
	cleanup(revert_user);

end


function TestCase.Guild.GuildStorage()
	local 	ret;
	local 	msg;
	local 	user, role, session_id, user_name;
	local 	guild_name = "RobotTestN4";
	local 	announce = "temp";
	local	guild_id;

	local user, role, session_id, user_name = NewUser();
	guild_name = user_name;

	wait(2);
	PreCreateGuild(user, role);
	wait(5);
	g_RobotMessageHandler:DoGuildCreate(role, guild_name, announce);
	msg = recv_msg(5, session_id,  protocol.m2c_create_guild_ack);
	check(msg, "failed to recv m2c_create_guild_ack");
	guild_id = msg.dwGuildID;

	g_RobotMessageHandler:DoGuildViewStorage(role, 0);


	ret = user:GMCommand("AddItem(101, 1)");
	check(ret, "failed to send gm command");

	msg = recv_msg(10, session_id, protocol.g2c_item_change);
	check(msg, "failed to recv m2c_guild_push_item_ack");


	g_RobotMessageHandler:DoGuildPushItem(role, 1, 0, 0, 0);
	msg = recv_msg(10, session_id, protocol.m2c_guild_push_item_ack);
	check(msg, "failed to recv m2c_guild_push_item_ack");

	local 	conSlot = 0;
	local 	itemSlot = 0;
	conSlot = msg.byStorageConSlot;
	itemSlot = msg.byStorageSlot;


	g_RobotMessageHandler:DoGuildPopItem(role, conSlot, itemSlot, 1, 5);
	msg = recv_msg(10, session_id, protocol.m2c_guild_pop_item_ack);
	check(msg, "failed to recv m2c_guild_pop_item_ack");

	g_RobotMessageHandler:DoGuildPushItem(role, 1, 5, 0, 1);
	msg = recv_msg(10, session_id, protocol.m2c_guild_push_item_ack);
	check(msg, "failed to recv m2c_guild_push_item_ack");
	conSlot = msg.byStorageConSlot;
	itemSlot = msg.byStorageSlot;

	g_RobotMessageHandler:DoGuildMoveItem(role, 0, 1, 0, 2);
	msg = recv_msg(10, session_id, protocol.m2c_guild_move_item_ack);
	check(msg, "failed to recv m2c_guild_move_item_ack");


	cleanup(user);
end


function TestCase.Guild.GuildBasic()
    local ret;
    local msg;
	local guild_name = "G"..os.date("%Y%H%M%S");
	local announce = "only test";

	-- create
	local user, role, session_id, user_name = NewUser();
	PreCreateGuild(user, role);

	wait(5);
	g_RobotMessageHandler:DoGuildCreate(role, guild_name, announce);
	msg = recv_msg(50, session_id,  protocol.m2c_create_guild_ack);
	check(msg, "failed to recv m2c_create_guild_ack");

	msg = recv_msg(50, session_id, protocol.m2c_guild_info_ntf);
	check(msg, "failed to recv protocol.m2c_guild_info_ntf");

	-- view
	--local user2, role2, session_id2, user_name2 = NewUser();
	g_RobotMessageHandler:DoGuildView(role, 0);
	msg = recv_msg(50, session_id, protocol.m2c_view_guild_list_ack);
	check(msg, "failed to recv protocol.m2c_view_guild_list_ack");

	-- change notice
	g_RobotMessageHandler:DoGuildChangeNotice(role, "hega only test");
	msg = recv_msg(50, session_id, protocol.m2c_guild_notice_change);
	check(msg, "failed to recv m2c_guild_notice_change");


	-- donation
	g_RobotMessageHandler:DoGuildDonation(role, GUILD_ATTR_MONEY, 10000);
	msg = recv_msg(10, session_id, protocol.m2c_guild_attr_modify_ntf);
	check(msg, "failed to recv m2c_guild_attr_modify_ntf");
	check(msg.byGuildAttrType == GUILD_ATTR_MONEY, "m2c_guild_attr_modify_ntf type error!");

	g_RobotMessageHandler:DoGuildDonation(role, GUILD_ATTR_WOOD, 10000);
	msg = recv_msg(10, session_id, protocol.m2c_guild_attr_modify_ntf);
	check(msg, "failed to recv m2c_guild_attr_modify_ntf");
	check(msg.byGuildAttrType == GUILD_ATTR_WOOD, "m2c_guild_attr_modify_ntf type error!");

	g_RobotMessageHandler:DoGuildDonation(role, GUILD_ATTR_HERB, 10000);
	msg = recv_msg(10, session_id, protocol.m2c_guild_attr_modify_ntf);
	check(msg, "failed to recv m2c_guild_attr_modify_ntf");
	check(msg.byGuildAttrType == GUILD_ATTR_HERB, "m2c_guild_attr_modify_ntf type error!");

	g_RobotMessageHandler:DoGuildDonation(role, GUILD_ATTR_CRYSTAL, 10000);
	msg = recv_msg(10, session_id, protocol.m2c_guild_attr_modify_ntf);
	check(msg, "failed to recv m2c_guild_attr_modify_ntf");
	check(msg.byGuildAttrType == GUILD_ATTR_CRYSTAL, "m2c_guild_attr_modify_ntf type error!");

	g_RobotMessageHandler:DoGuildDonation(role, GUILD_ATTR_SILVER, 10000);
	msg = recv_msg(10, session_id, protocol.m2c_guild_attr_modify_ntf);
	check(msg, "failed to recv m2c_guild_attr_modify_ntf");
	check(msg.byGuildAttrType == GUILD_ATTR_SILVER, "m2c_guild_attr_modify_ntf type error!");


	-- demise
	g_RobotMessageHandler:DoDisbandGuild(role);
	msg = recv_msg(50, session_id, protocol.m2c_disband_guild_ntf);
	check(msg, "failed to recv m2c_disband_guild_ntf");

	--cleanup(user2);
	cleanup(user);


	-- join guild
	GuildApply();
	InviteAndSoOn();

	-- diplomat
	DiplomatAlliance();
	DiplomatEnemy();

end


function TestCase.Guild.Advanced()

    local ret;
    local msg;
	local guild_name = "G"..os.date("%Y%H%M%S");
	local announce = "only test";

	-- create
	--local user_name = "heh1";
	--local user, role, session_id = ReLogin(user_name);
	local user, role, session_id, user_name = NewUser();
	PreCreateGuild(user, role);

	wait(5);
	g_RobotMessageHandler:DoGuildCreate(role, guild_name, announce);
	msg = recv_msg(10, session_id,  protocol.m2c_create_guild_ack);
	check(msg, "failed to recv m2c_create_guild_ack");

	msg = recv_msg(10, session_id, protocol.m2c_guild_info_ntf);
	check(msg, "failed to recv protocol.m2c_guild_info_ntf");

	-- change weather , failed
	--g_RobotMessageHandler:DoGuildChangeWeather(role, swtRain, GUILD_CW_TIME_5M);
	--msg = recv_msg(10, session_id, protocol.g2c_update_weather);
	--check(msg == nil, "failed to recv g2c_update_weather");

	--cleanup(user);
	--wait(1);
	--ReLogin(user_name);

	wait(5);
	-- enter guild map
	g_RobotMessageHandler:DoGuildEnterMap(role);
	msg = recv_msg(20, session_id, protocol.g2c_changescene_enter);
	check(msg, "failed to recv g2c_changescene_enter");

	wait(5);

	user:GMCommand("SummonNpc(6879)");
	msg = recv_msg(10, session_id, protocol.g2c_char_appear);
	check(msg, "failed to summon npc");
	check(msg.stAppearData.dwCharID ~= 0, "failed to summon npc with id");

	print(msg.stAppearData.dwCharID);
	ret = user:InteractWithNpc(msg.stAppearData.dwCharID);
	check(ret, "failed to interact with npc");
	msg = recv_msg(10, session_id, protocol.g2c_interact_result);
	check(msg, "failed to summon npc");


	-- change weather
	g_RobotMessageHandler:DoGuildChangeWeather(role, swtSnow, GUILD_CW_TIME_5M);
	msg = recv_msg(10, session_id, protocol.g2c_update_weather);
	check(msg, "failed to recv g2c_update_weather");


	cleanup(user);
end

function StableUser(name)
	local user_name = "Gt322" .. name;
	local user, role = startup(user_name, user_name, 1);
    check(user, "failed to create user");
    check(role, "failed to create role");
	local session_id = user:GetSessionID();

	return user, role, session_id, user_name;
end


function TestCase.Guild.CreateMember()

    local ret;
    local msg;
	local guild_name = "gguildL3";
	local applicant_num = 250;
	local app_role_table = {};

	-- apply
	for i = 1,applicant_num,1 do
		app_role_table[i] = {};
		app_role_table[i].user, app_role_table[i].role, app_role_table[i].session_id, app_role_table[i].user_name = StableUser(i);
		print("NewUser:  "..i);
		wait(0.5);
		ret = app_role_table[i].user:GMCommand("Level 15");
		check(ret, "failed to send gm command");

		local x = math.random(100, 14000);
		local y = math.random(100, 14000);

		local mapID = 1;
		if 0 == i / 3 then
			mapID = 1;
		elseif 1 == i/3 then
			mapID = 2;
		else
			mapID = 3;
		end

		ret = app_role_table[i].user:GMCommand("jump ".. mapID .." 0 "..x.." "..y);
		check(ret, "failed to send gm command");

		wait(1);
	end
end

function TestCase.Guild.FHLogin()
    local ret;
    local msg;
	local guild_name = "gguildL6";
	local applicant_num = 252;
	local app_role_table = {};

	local user_name = "guildL6";
	local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
	local session_id = user:GetSessionID();

	--ret = user:GMCommand("CreateGuild('"..guild_name.."', '123')");
	--check(ret, "failed to send gm command");

	-- apply
	for i = 1,applicant_num,1 do
		app_role_table[i] = {};
		app_role_table[i].user, app_role_table[i].role, app_role_table[i].session_id, app_role_table[i].user_name = StableUser(i);
		print("NewUser:  "..i);
		wait(0.5);
		ret = app_role_table[i].user:GMCommand("Level 15");
		check(ret, "failed to send gm command");

		local x = math.random(100, 14000);
		local y = math.random(100, 14000);

		local mapID = 1;
		if 0 == i / 3 then
			mapID = 1;
		elseif 1 == i/3 then
			mapID = 2;
		else
			mapID = 3;
		end

		ret = app_role_table[i].user:GMCommand("jump ".. mapID .." 0 "..x.." "..y);
		check(ret, "failed to send gm command");

		wait(0.5);
	end

end


function TestCase.Guild.TestFH()

    local ret;
    local msg;
	local guild_name = "gguildL6";
	local applicant_num = 252;
	local app_role_table = {};

	local user_name = "guildL6";
	local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
	local session_id = user:GetSessionID();

	--ret = user:GMCommand("CreateGuild('"..guild_name.."', '123')");
	--check(ret, "failed to send gm command");

	-- apply
	for i = 1,applicant_num,1 do
		app_role_table[i] = {};
		app_role_table[i].user, app_role_table[i].role, app_role_table[i].session_id, app_role_table[i].user_name = StableUser(i);
		print("NewUser:  "..i);
		wait(0.5);
		ret = app_role_table[i].user:GMCommand("Level 15");
		check(ret, "failed to send gm command");

		local x = math.random(100, 14000);
		local y = math.random(100, 14000);

		local mapID = 1;
		if 0 == i / 3 then
			mapID = 1;
		elseif 1 == i/3 then
			mapID = 2;
		else
			mapID = 3;
		end

		ret = app_role_table[i].user:GMCommand("jump ".. mapID .." 0 "..x.." "..y);
		check(ret, "failed to send gm command");

		wait(0.5);
	end

	check(1, "create user success");
	-- 通过find取到guild id
	--local guild_id = GetGuildIDByFind(role, session_id, guild_name);
	--print(guild_id);
	local guild_id = 1610612750;

	check(1, "find guild success");

	for k, v in pairs(app_role_table) do
		print("check role id: "..v.role:GetObjID());
		ApplyToJoinGuild(v.role, v.session_id, guild_id);
		wait(0.6);

		local msg_data = GetGuildMemberApp(role, session_id);
		check(msg_data.wAppCount > 0, "protocol.m2c_get_apply_guild_list_ack data error!");

		local roleID_table = {};
		for i = 0, msg_data.wAppCount - 1, 1 do
			roleID_table[i] = msg_data.info[i].dwRoleID;
		end
		roleID_table.count = msg_data.wAppCount - 1;

		-- refuse
		for i = 0, roleID_table.count do
			print(i.." "..roleID_table[i]);

			g_RobotMessageHandler:DoGetRevertGuildApp(role, 2, roleID_table[i]);
			msg = recv_msg(10, session_id, protocol.m2c_revert_guild_apply_ack);
			check(msg, "failed to recv protocol.m2c_revert_guild_apply_ack");
			check(msg.dwRoleID == roleID_table[i], "recv protocol.m2c_revert_guild_apply_ack data error");
		end

	end

	wait(40);

	--for k, v in pairs(app_role_table) do
	--	cleanup(v.user);
	--	wait(0.2);
	--end

end

