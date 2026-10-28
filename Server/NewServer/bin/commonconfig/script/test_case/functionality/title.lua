LoadPackage("title.pkg")
LoadPackage("data_manager.pkg")
LoadPackage("attr_list.pkg")


TestCase.Title = {};

-- Test adding, equipping, replacing and removing
function TestCase.Title.Base()
    local user_name = "Title" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();


	local title_data = CDataManager_TITLE_TEMPLATE_:GetInstance():GetData(3);

	-- check pre condition    begin
		-- add
		ret = user:GMCommand("AddTitle(3)");
		check(ret, "failed to send gm command");

		msg = recv_msg(10, session_id, protocol.g2c_add_title);
		check(msg, "failed to recv g2c_add_title");

		ret = user:GMCommand("AddExp(100000)");
		check(ret, "failed to send gm command");

		local tempValue = role:GetAttr(title_data.m_Attr[0].shAttrType);
		print(title_data.m_Attr[0].shAttrType);
		print(title_data.m_Attr[0].shParam);
		print(tempValue);
		-- equip
		ret = user:GMCommand("EquipTitle(3)");
		check(ret, "failed to send gm command");

		msg = recv_msg(10, session_id, protocol.g2c_sync_attr_change);
		check(msg, "failed to recv g2c_sync_attr_change");
		wait(5);
		print(role:GetAttr(title_data.m_Attr[0].shAttrType) );
		check(role:GetAttr(title_data.m_Attr[0].shAttrType) > tempValue, "add value error!");

	-- check pre condition    end

	-- add
    ret = user:GMCommand("AddTitle(1)");
    check(ret, "failed to send gm command");

    msg = recv_msg(10, session_id, protocol.g2c_add_title);
    check(msg, "failed to recv g2c_add_title");

	-- del
    ret = user:GMCommand("DeleteTitle(1,1)");
    check(ret, "failed to send gm command");

    msg = recv_msg(10, session_id, protocol.g2c_del_title);
    check(msg, "failed to recv g2c_del_title");


	-- add
    ret = user:GMCommand("AddTitle(1)");
    check(ret, "failed to send gm command");

    msg = recv_msg(10, session_id, protocol.g2c_add_title);
    check(msg, "failed to recv g2c_add_title");

	-- add
    ret = user:GMCommand("AddTitle(2)");
    check(ret, "failed to send gm command");

    msg = recv_msg(10, session_id, protocol.g2c_add_title);
    check(msg, "failed to recv g2c_add_title");

	print(role:GetAttr(title_data.m_Attr[0].shAttrType));


	-- equip
	title_data = CDataManager_TITLE_TEMPLATE_:GetInstance():GetData(1);
	print(title_data.m_Attr[0].shAttrType);
	print(role:GetAttr(title_data.m_Attr[0].shAttrType));
    ret = user:GMCommand("EquipTitle(1)");
    check(ret, "failed to send gm command");

	wait(5);
    --msg = recv_msg(10, session_id, protocol.g2c_sync_attr_change);
    --check(msg, "failed to recv g2c_sync_attr_change");


	print(role:GetAttr(title_data.m_Attr[0].shAttrType));
	print(title_data.m_Attr[0].shAttrType);
	print(title_data.m_Attr[0].shParam);
	check(role:GetAttr(title_data.m_Attr[0].shAttrType) > title_data.m_Attr[0].shParam, "equip title attr value error");


	-- equip
    ret = user:GMCommand("UnEquipTitle()");
    check(ret, "failed to send gm command");

    msg = recv_msg(10, session_id, protocol.g2c_sync_attr_change);
    check(msg, "failed to recv g2c_sync_attr_change");
	check(role:GetAttr(title_data.m_Attr[0].shAttrType) < title_data.m_Attr[0].shParam, "unEquip title attr value error");

	-- equip
    ret = user:GMCommand("EquipTitle(1)");
    check(ret, "failed to send gm command");

    msg = recv_msg(10, session_id, protocol.g2c_sync_attr_change);
    check(msg, "failed to recv g2c_sync_attr_change");
	check(role:GetAttr(title_data.m_Attr[0].shAttrType) > title_data.m_Attr[0].shParam, "equip title attr value error");

	-- equip
	title_data = CDataManager_TITLE_TEMPLATE_:GetInstance():GetData(2);
	print(role:GetAttr(title_data.m_Attr[0].shAttrType));
	print(title_data.m_Attr[0].shAttrType);
	print(title_data.m_Attr[0].shParam);
	local 	temp_value2 = role:GetAttr(title_data.m_Attr[0].shAttrType);
    ret = user:GMCommand("EquipTitle(2)");
    check(ret, "failed to send gm command");

    msg = recv_msg(10, session_id, protocol.g2c_sync_attr_change);
	check(msg, "failed to recv g2c_sync_attr_change");
	msg = recv_msg(10, session_id, protocol.g2c_sync_attr_change);
    check(msg, "failed to recv g2c_sync_attr_change");

	print(role:GetAttr(title_data.m_Attr[0].shAttrType));
	print(title_data.m_Attr[0].shAttrType);
	print(title_data.m_Attr[0].shParam);

	--check(role:GetAttr(title_data.m_Attr[1].shAttrType) < title_data.m_Attr[1].shParam);
	check(role:GetAttr(title_data.m_Attr[0].shAttrType) > temp_value2, "equip title attr value error");

	-- equip
	title_data = CDataManager_TITLE_TEMPLATE_:GetInstance():GetData(1);
    ret = user:GMCommand("EquipTitle(1)");
    check(ret, "failed to send gm command");

    msg = recv_msg(10, session_id, protocol.g2c_sync_attr_change);
    check(msg, "failed to recv g2c_sync_attr_change");
	msg = recv_msg(10, session_id, protocol.g2c_sync_attr_change);
    check(msg, "failed to recv g2c_sync_attr_change");
	check(role:GetAttr(title_data.m_Attr[0].shAttrType) > title_data.m_Attr[0].shParam, "equip title attr value error");
	--check(role:GetAttr(15) < 2000);

	-- del
    --ret = user:GMCommand("DeleteTitle(2,1)");
    --check(ret, "failed to send gm command");

    --msg = recv_msg(10, session_id, protocol.g2c_del_title);
    --check(msg, "failed to recv g2c_del_title");

	-- equip failed check
    --ret = user:GMCommand("EquipTile(2)");
    --check(ret, "failed to send gm command");
--
    --msg = recv_msg(10, session_id, protocol.g2c_sync_attr_change);
    --check(msg, "failed to recv g2c_sync_attr_change");

	--Log out
    cleanup(user);
end


-- check relogin
function TestCase.Title.Reload()
    local user_name =  "Title" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

	
	-- add
    ret = user:GMCommand("AddTitle(1)");
    check(ret, "failed to send gm command");

    msg = recv_msg(10, session_id, protocol.g2c_add_title);
    check(msg, "failed to recv g2c_add_title");

	-- add
    ret = user:GMCommand("AddTitle(2)");
    check(ret, "failed to send gm command");

    msg = recv_msg(10, session_id, protocol.g2c_add_title);
    check(msg, "failed to recv g2c_add_title");
    
    cleanup(user);
    
    wait(5);
    
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id = user:GetSessionID();

	-- equip
	local title_data = CDataManager_TITLE_TEMPLATE_:GetInstance():GetData(2);
	
    ret = user:GMCommand("EquipTitle(2)");
    check(ret, "failed to send gm command");

	wait(5);
    --msg = recv_msg(10, session_id, protocol.g2c_sync_attr_change);
    --check(msg, "failed to recv g2c_sync_attr_change");
	check(role:GetAttr(title_data.m_Attr[0].shAttrType) > title_data.m_Attr[0].shAttrType);


	--Log out
    cleanup(user);

end


