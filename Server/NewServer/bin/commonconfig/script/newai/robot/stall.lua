STALL_SCENE_TEMPLATE_ID = 143;
STALL_GOODS_TEMPLATE_ID = 80002;

g_stall_pos = {};

function init_stall_pos(scene_id, scene_static_data)

    if scene_id ~= STALL_SCENE_TEMPLATE_ID then
        return;
    end
    
	print("init_stall_pos start scene_id@" .. scene_id);
    
    local grid_data = nil;
	local z = 100000 * POINT_PER_CM;
    local sz, sy, sz;
    for x = GRID_WIDTH / 2, scene_static_data:GetMaxZoneX() * ZONE_WIDTH, 3 * GRID_WIDTH do
        for y = GRID_WIDTH / 2, scene_static_data:GetMaxZoneY() * ZONE_WIDTH, 3 * GRID_WIDTH do
            
            grid_data = scene_static_data:GetGroundGrid(x, y);
            if grid_data and grid_data.uStallLevel > 0 then
                local pos = get_near_pos(scene_id, x, y, z, 16, 1);
	            if not pos then
		            print("init_stall_pos find near pos fail for [" .. x .. "," .. y .. "," .. z .. "]@" .. scene_id);
                else
                    if #pos > 0 then
                        local scene_pos = {};
                        scene_pos.X = pos[1].x / POINT_PER_CM;
                        scene_pos.Y = pos[1].y / POINT_PER_CM;
                        scene_pos.Z = pos[1].z / POINT_PER_CM;

		                sx, sy, sz = ConvertCoordN2O(scene_pos.X,scene_pos.Y,scene_pos.Z);
                        scene_pos.X = sx;
                        scene_pos.Y = sy;
                        scene_pos.Z = sz;

		                table.insert(g_stall_pos, scene_pos);
                    end
	            end
            end
		end
	end

	print("init_stall_pos find stall pos count=" .. #g_stall_pos);
end

function open_stall(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
	if role:GetObjID() % 9 >= 1 then
		return brvFail;
	end

    if role:GetStall():GetStallState() ~= essNotOpen then
        print("********** open_stall stall state is not essNotOpen" .. "  " .. role:GetName() .. "@" .. role:GetObjID());
        return brvFail;
    end

    if role:GetMoveState() ~= CMS_STAND then
        return brvFail;
    end

    if role:GetGrid().uStallLevel <= 0 then
        return brvFail;
    end

    user:OpenStall();
    
    local itembag = role:GetItemBag();
    local freeSlots = itembag:GetFreeSlots(CONSLOT_DEFAULT);
    local itemCount = itembag:GetItemCount(STALL_GOODS_TEMPLATE_ID, false);
    if itemCount < 3 then
        if freeSlots >= 3 then
            user:GMCommand("AddItem " .. STALL_GOODS_TEMPLATE_ID .. " 1 ");
            user:GMCommand("AddItem " .. STALL_GOODS_TEMPLATE_ID .. " 1 ");
            user:GMCommand("AddItem " .. STALL_GOODS_TEMPLATE_ID .. " 1 ");
        else
            for i = 1, freeSlots, 1 do
                user:GMCommand("AddItem " .. STALL_GOODS_TEMPLATE_ID .. " 1 ");
            end
        end
    end

    if itembag:GetMoney(MONEYTYPE_02) < 1000000 then
        local needAddMoney = 1000000 - itembag:GetMoney(MONEYTYPE_02);
        user:GMCommand("AddMoney 1 " .. needAddMoney);
    end

    return brvSuccess;
end

function close_stall(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
    if role:GetStall():GetStallState() ~= essOpen then
        print("********** close_stall stall state is not essNotOpen" .. "  " .. role:GetName() .. "@" .. role:GetObjID());
        return brvFail;
    end
    
    user:CloseStall();

    return brvSuccess;
end

function real_open_stall(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
    if role:GetStall():GetStallState() ~= essPreparing then
        print("********** real_open_stall stall state is not essPreparing" .. "  " .. role:GetName() .. "@" .. role:GetObjID());
        return brvFail;
    end
    
    user:ChangeStallName(role:GetName());
    user:RealOpenStall();
    print("real_open_stall" .. "  " .. role:GetName() .. "@" .. role:GetObjID());
    
    return brvSuccess;
end

function real_close_stall(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
    if role:GetStall():GetStallState() ~= essPreparing and role:GetStall():GetStallState() ~= essOpen then
        print("********** real_close_stall stall state is not essPreparing or essOpen" .. "  " .. role:GetName() .. "@" .. role:GetObjID());
        return brvFail;
    end
    
    user:RealCloseStall();
    print("real_close_stall" .. "  " .. role:GetName() .. "@" .. role:GetObjID());
    
    return brvSuccess;
end

function add_stall_item(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
    if role:GetStall():GetStallState() ~= essPreparing then
        print("********** add_stall_item stall state is not essPreparing" .. "  " .. role:GetName() .. "@" .. role:GetObjID());
        return brvFail;
    end
    
    local itembag = role:GetItemBag();
    local nextaddgoodslot = role:GetStall():GetNextAddGoodSolt();
    if nextaddgoodslot == -1 then
        return brvSuccess;
    end

    local bFoundItem = false;
    local found_item_solt = -1;
    itembag:Begin(CONSLOT_DEFAULT);
    local item = itembag:Next(CONSLOT_DEFAULT);
    while item ~= nil do
        if item.m_iteminfo.m_nTemplateID == STALL_GOODS_TEMPLATE_ID and item.m_iteminfo.m_byBindType ~= BINDTYPE_BINDED and item.m_iteminfo.m_dwRoleID == 0 then
            local bInStall = role:GetStall():IsItemAlreadyInStall(item.m_iteminfo.m_byConSlot, item.m_iteminfo.m_byItemSlot);
            if not bInStall then
                found_item_solt = item.m_iteminfo.m_byItemSlot;
                bFoundItem = true;
                break;        
            end
        end

        item = itembag:Next(CONSLOT_DEFAULT);
    end

    if not bFoundItem then
        return brvSuccess;
    end
    
    user:AddStallItem(nextaddgoodslot, CONSLOT_DEFAULT, found_item_solt, 1, 100);

    return brvSuccess;
end

function remove_stall_item(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
    if role:GetStall():GetStallState() ~= essPreparing then
        print("********** remove_stall_item stall state is not essPreparing" .. "  " .. role:GetName() .. "@" .. role:GetObjID());
        return brvFail;
    end

    local stallfirstslot = role:GetStall():GetFirstGoodSolt();
    if stallfirstslot == -1 then
        return brvSuccess;
    end
    
    user:RemoveStallItem(stallfirstslot);

    return brvSuccess;
end

function upgrade_stall(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
    if role:GetStall():GetStallState() ~= essPreparing then
        print("********** upgrade_stall stall state is not essPreparing" .. "  " .. role:GetName() .. "@" .. role:GetObjID());
        return brvFail;
    end

    if role:GetStall():GetStallLevelUpExpireTime() >= g_GameWorld:GetGameTime() then
        return brvSuccess;
    end

    local stall_type = 1;
    
    user:UpgradeStall(stall_type);

    return brvSuccess;
end

function sync_stall_item(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
    user:ViewStallItem(role:GetObjID());
    
    return brvSuccess;
end

function view_stall_item(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
	if role:GetObjID() % 9 <= 7 then
		return brvFail;
	end

    for i = 1, 1000, 1 do
        local stall_user = CUserMgr:GetInstance():RandAnotherUser(user);
        if stall_user then
            local stall_role = stall_user:GetPlayingRole();
            if stall_role and stall_role:CheckDistance(role) and stall_role:GetStall():GetStallState() == essOpen then
                user:ViewStallItem(stall_role:GetObjID());
                print("view_stall_item" .. "  " .. role:GetName() .. "@" .. role:GetObjID());
                return brvSuccess;
            end
        end
    end
    
    return brvSuccess;
end

function buy_stall_item(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
	if role:GetObjID() % 9 <= 7 then
		return brvFail;
	end

    for i = 1, 1000, 1 do
        local stall_user = CUserMgr:GetInstance():RandAnotherUser(user);
        if stall_user then
            local stall_role = stall_user:GetPlayingRole();
            if stall_role and stall_role:CheckDistance(role) and stall_role:GetStall():GetStallState() == essOpen and stall_role:GetStall():GetFirstGoodSolt() ~= -1 then
                user:BuyStallItem(stall_role:GetObjID(), stall_role:GetStall():GetFirstGoodSolt(), 1, stall_role:GetStall():GetFirstGoodModifyFrame());
                print("buy_stall_item" .. "  " .. role:GetName() .. "@" .. role:GetObjID());
                return brvSuccess;
            end
        end
    end
    
    return brvSuccess;
end

function find_staller(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
	if role:GetObjID() % 9 <= 7 then
		return brvFail;
	end

    for i = 1, 1000, 1 do
        local stall_user = CUserMgr:GetInstance():RandAnotherUser(user);
        if stall_user then
            local stall_role = stall_user:GetPlayingRole();
            if stall_role and stall_role:GetStall():GetStallState() == essOpen and stall_role:GetStall():GetFirstGoodSolt() ~= -1 then
		        local sx, sy, sz = ConvertCoordN2O(stall_role:GetX()/POINT_PER_CM,stall_role:GetY()/POINT_PER_CM,stall_role:GetZ()/POINT_PER_CM);
	            JumpToScene(user, role, STALL_SCENE_TEMPLATE_ID, 1, sx, sy, sz);
                return brvSuccess;
            end
        end
    end
    
    return brvFail;
end

function jump_stall_pos(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
	local oScene = role:GetScene();

	if role:GetObjID() % 9 >= 1 then
		return brvFail;
	end
    
    if role:GetStall():GetStallState() ~= essNotOpen then
        return brvSuccess;
    end

    if role:GetGrid().uStallLevel > 0 then
        return brvSuccess;
    end

    if #g_stall_pos <= 0 then
        print("********** jump_stall_pos g_stall_pos empty !" .. "  " .. role:GetName() .. "@" .. role:GetObjID());
        return brvFail;
    end

    local pos_index = math.random(1, #g_stall_pos);
	JumpToScene(user, role, STALL_SCENE_TEMPLATE_ID, 1, g_stall_pos[pos_index].X, g_stall_pos[pos_index].Y, g_stall_pos[pos_index].Z);

    return brvSuccess;
end

stall_tree = 
{ batSequencer,
    { batCheckCDTimer, param = { COOLDOWN_AI, STALL_CD_TIMER } },
    { batSetCDTimer, param  = { COOLDOWN_AI, STALL_CD_TIMER, STALL_INTERVAL } },	
    { batSelector,

        -- create stall
        { batSequencer,
            { jump_stall_pos },
            { batWait, param = { 10 * 1000 } },
            { open_stall },
            { batWait, param = { 3 * 1000 } },
            { add_stall_item },
            { batWait, param = { 3 * 1000 } },
            { add_stall_item },
            { batWait, param = { 3 * 1000 } },
            { add_stall_item },
            { batWait, param = { 3 * 1000 } },
            { real_open_stall },
            { batWait, param = { 3 * 1000 } },
            { sync_stall_item },
            { batWait, param = { 10 * 60 * 1000 } },
            { close_stall },
            { batWait, param = { 3 * 1000 } },
            { upgrade_stall },
            { batWait, param = { 3 * 1000 } },
            { remove_stall_item },
            { batWait, param = { 3 * 1000 } },
            { real_open_stall },
            { batWait, param = { 3 * 1000 } },
            { sync_stall_item },
            { batWait, param = { 10 * 60 * 1000 } },
            { real_close_stall },
        },

        -- view and buy stall goods
        { batSequencer,
            { find_staller },
            { batWait, param = { 10 * 1000 } },
            { view_stall_item },
            { batWait, param = { 5 * 1000 } },
            { buy_stall_item },
        },                                                   
    },
};