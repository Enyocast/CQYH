LoadPackage("gameworld.pkg");
LoadPackage("scene.pkg");
LoadPackage("scene_object.pkg");
LoadPackage("character.pkg");
LoadPackage("npc.pkg");
LoadPackage("role.pkg");
LoadPackage("data_manager.pkg");
LoadPackage("chat_def.pkg");
LoadPackage("id_def.pkg");

function NpcSay()   
	npc_tpl_id = 101; 
--[[    
	local targetid = MakeObjectID(otChannel,cctScene);
	local command =  "local oScene = role:GetScene(); "
    		.."local oNpc = oScene:SpawnNpc("..npc_tpl_id
    		..", role:GetX()+10*POINT_PER_CM, role:GetY(), role:GetZ(), 0, nstSummon, 0, 0, false);"	
            .."oNpc:Say( "..targetid..",oNpc:GetObjID() );"
	ret = user:GMCommand(command);	
	check(ret, "failed to summon npc with nAIID = "..nAIID.." to scene");	
	 
    --local msg = recv_msg(5, session_id, protocol.g2c_char_appear);
    --check(msg, "failed to recv g2c_char_appear");
    
	-- recv_msg chat
	local msg = recv_msg(120, session_id, protocol.g2c_chat_message);
	check(msg, "fail to recv chat_message");	
	check(msg.dwTargetID == targetid, "fail to receive msg with correct type");	
	local npc_id = tonumber(msg.szMessage);
--]]	
end

g_role = nil;
function log( Words )
	print( "role( "..g_role:GetObjID().." ): "..Words );	

	-- role say
	local targetid = MakeObjectID(otChannel,cctScreen);
	ret = g_role:Say(targetid, Words );
	--check(ret, "failed to send screen chat message");
end

function SummonNpcSetAI( user, role, nAIID )
    
    local npc_tpl_id = 101;		-- AI 测试专用, alwaysRun
    local npc_data = CDataManager_NPC_DATA_:GetInstance():GetData( npc_tpl_id );
    check( npc_data, "fail to find npc data, id="..npc_tpl_id );

    --local ret = user:GMCommand("SummonNpc("..npc_tpl_id..")");
    --check(ret, "failed to summon npc");
  
	local command =  "local oScene = SelfRole:GetScene(); "
    		.."local oNpc = oScene:SpawnNpc("..npc_tpl_id..", SelfRole:GetX(), SelfRole:GetY(), SelfRole:GetZ(), 0, nstSummon, 0, 0, 0, 0);"
            .."oNpc:SetAIProcessor( "..nAIID.." );"              
    local ret = user:GMCommand( command );
    check(ret, "failed to set npc ai");
     
    local msg = recv_msg(5, user:GetSessionID(), protocol.g2c_char_appear);
    check(msg, "failed to recv g2c_char_appear");
    
    local npc_id = msg.stAppearData.dwCharID;
    print( "npc appear, id="..npc_id);
 
	local npc = g_oGameWorld:FindNpc( npc_id );
	check( npc, "fail to find npc by id "..npc_id);
	print("npc client g_oGameWorld pos: x="..npc:GetX()..",y="..npc:GetY() );
	print("npc client server g2c_char_appear msg pos: msg.x="..msg.stAppearData.nCurrentX..",msg.y="..msg.stAppearData.nCurrentY );
    check( npc:GetX()==msg.stAppearData.nCurrentX and  npc:GetY()==msg.stAppearData.nCurrentY, "client g_oGameWorld and server g2c_char_appear msg 's pos don't match" );
	    
    return  npc_id, npc, npc_data;
end

function until_stop(  user, role, npc  )
	
	local npc_path = {};	
	local role_path = {};
	for i = 1, 10000 do
		if( #npc_path > 2  -- 连续3次都没移动则认为npc追击已结束
		  and npc_path[#npc_path-2].x == npc:GetX()/POINT_PER_CM/100 
		  and npc_path[#npc_path-2].y == npc:GetY()/POINT_PER_CM/100
		  and role_path[#role_path-2].x == role:GetX()/POINT_PER_CM/100 
		  and role_path[#role_path-2].y == role:GetY()/POINT_PER_CM/100  ) then
			print( "break, role stopped, and npc stopped: x="..npc_path[#npc_path-2].x..",y="..npc_path[#npc_path-2].y );
			break;
		end
		--[[  		--]]
		local npcX, npcY = (npc:GetX()/POINT_PER_CM/100), (npc:GetY()/POINT_PER_CM/100);
		table.insert( npc_path, { x=npcX, y=npcY } );
		print("npc pos: x="..npcX..",y="..npcY );
		
		local roleX, roleY = (role:GetX()/POINT_PER_CM/100), (role:GetY()/POINT_PER_CM/100);
		table.insert( role_path, { x=roleX, y=roleY } );
		print("== role pos: x="..roleX..",y="..roleY );

		--wait(1);
		local msg = recv_msg_and(1, user:GetSessionID(), protocol.g2c_object_disappear,
									user:GetSessionID(), protocol.g2c_char_cast_spell,
									user:GetSessionID(), protocol.g2c_char_move);
		if( msg ) then	
			if( msg.wMsg == protocol.g2c_object_disappear ) then	    
				local disappear_id = msg.dwObjID;
				print( "****** receive obj disappear, id="..disappear_id);
				if( disappear_id == npc:GetObjID() ) then
					return disappear_id;
				end
			elseif ( msg.wMsg == protocol.g2c_char_cast_spell ) then   
				local caster_id = msg.dwCasterID;
				local spell_id = msg.wSpellID;
				print( "****** receive spell msg, caster: "..caster_id..", spell_id:"..spell_id );
			elseif	 ( msg.wMsg == protocol.g2c_char_move ) then 
				print( "receive char move msg, msg.dwCharID="..msg.dwCharID",npc:GetObjID()="..npc:GetObjID());
				if( msg.dwCharID == npc:GetObjID() ) then   					
					local npcX, npcY = (msg.nDestX/POINT_PER_CM/100), (msg.nDestY/POINT_PER_CM/100);
					table.insert( npc_path, { x=npcX, y=npcY } );
					print("msg npc pos: x="..npcX..",y="..npcY );
				elseif( msg.dwCharID == role:GetObjID() ) then	  					  
					local roleX, roleY = (msg.nDestX/POINT_PER_CM/100), (msg.nDestY/POINT_PER_CM/100);
					table.insert( role_path, { x=roleX, y=roleY } );
					print("msg role pos: x="..roleX..",y="..roleY );
				end  
			end
		end
	end
end

function testAI( user, role, ai_data) 
	local session_id = user:GetSessionID();
 
    -- 召唤 monster with ai
    local npc_id, npc, npc_data = SummonNpcSetAI( user, role, ai_data.nAIID );
	log( "Summon Npc="..npc_id );
    local npc_homeX, npc_homeY = npc:GetX(), npc:GetY();
	wait(1);
		
	-- check range 
	local chase_range = ai_data.nChaseRange;
	local scan_range = ai_data.nScanEnemyRange;	
	log( "ai("..ai_data.nAIID..") 's chase_range="..chase_range..",scan_range="..scan_range );
	
	local npc_radius = npc_data.nRadius;
	local role_radius = role:GetRadius();
	local max_offset = npc_radius + role_radius + ai_data.nPreferDistance + ai_data.nPreferDistanceOffset;
	log( "npc_radius="..npc_radius..", role_radius="..role_radius..
		",ai_data.nPreferDistance="..ai_data.nPreferDistance..
		",ai_data.nPreferDistanceOffset="..ai_data.nPreferDistanceOffset..
		",max_offset="..max_offset );
	
	-- 技能
--[[	
	local spells = {};
	for k,v in ipairs( ai_data.nSpellID ) do
		spells[v] = k;
	end
	
    local msg = recv_msg(1, session_id, protocol.g2c_char_cast_spell);
    if( msg ) then
		check(msg, "failed to  recv g2c_char_cast_spell");
	    
		local caster_id = msg.dwCasterID;
		local spell_id = msg.wSpellID;
		check( caster_id == npc_id, " other guy hit me,caster: "..caster_id );
		check( spells[spell_id], "npc use unconfigured spell:"..spell_id );	
	end		
--]]

	
    -- 逃跑至 monster gohome范围边缘以内,确认 monster 追击过来
    local targetX, targetY = role:GetX(), role:GetY() + chase_range - max_offset;
    role:MoveTo( targetX, targetY  );	    
	local role_speed = role:GetCurrentSpeed();
	log( "start move to target in range, target x="..targetX..", y="..targetY..", role_speed="..role_speed.."cm/s" );

	local disappear_id = until_stop( user, role, npc );
	if( disappear_id and disappear_id == npc_id ) then
		log( "****** npc disappear when chase role in range!" );
		check( 0, "error!" );		
	end

	if( 0 == scan_range ) then
		check( npc_homeX == npc:GetX() and npc_homeY == npc:GetY(), "npc scan_range ==0, but chase role!" );
		log( "no need more test: chase_range"..chase_range );
		return;
	end
	if( 0 == chase_range ) then
		check( npc_homeX == npc:GetX() and npc_homeY == npc:GetY(), "npc chase_range ==0, but chase role!" );
		log( "no need more test: scan_range="..scan_range );
		return;
	end	
	-- 确认 monster 追击过来 
	local chase_distance = math.pow( role:GetX() - npc:GetX(), 2 ) + math.pow( role:GetY() - npc:GetY(), 2 );
	local max_distance = math.pow( max_offset, 2 );
	print( "chase_distance="..chase_distance..",max_distance="..max_distance);
	check( chase_distance < max_distance, "npc chase fail when in range!"	);
	log( "npc chase success when role in range!" );
    
    -- 逃跑至 monster gohome范围边缘以外
    targetX, targetY = role:GetX(), role:GetY() + max_offset *2 + 100 * POINT_PER_CM;
    role:MoveTo( targetX, targetY  ); 
    log( "start to go out of range, target x="..targetX..", y="..targetY );
 
	local disappear_id2 = until_stop( user, role, npc );  	
  	
	-- 确认 monster 不再追击过来  	
	-- npc disappear 说明 gohome了( 超出 region 了不一定能收到 appear 消息)	  		
	local npc_distance = math.pow( npc:GetX() - npc_homeX, 2 ) + math.pow( npc:GetY() - npc_homeY, 2 );	
	local max_distance = math.pow( chase_range, 2 );  
	print( "out: npc_distance="..npc_distance..", max_distance="..max_distance );
    check(  disappear_id2 == npc_id 
			or npc_distance < max_distance 
			or( npc:GetX() == npc_homeX and npc:GetY() == npc_homeY ),
		"npc chase fail when out of range!"	);
end

function EnterInstanceAndTestAI( ai_data )
     
	if( ai_data.szScriptName ~= "" ) then
		print( "ai("..ai_data.nAIID..") won't be tested, as it has ai_data.szScriptName="..ai_data.szScriptName );
		return ;
	end	 
	
    -- 登陆
    local user_name1 = "test_ai_"..ai_data.nAIID.."_"..os.date("%H%M%S");
    --local user_name1 = "testgs1"..os.date("%H%M%S");
    local user, role = startup(user_name1, user_name1 );
    check(user, "failed to create user");
    check(role, "failed to create role");
    g_role = role;
    log( "successfully enter game" );
    
    -- jump 到 ProgIsland
    prog_scene_id = 1;
    
    local cmd = "Jump("..prog_scene_id..", 0, 30000, 200 )";
    print(cmd);
    ret = user:GMCommand(cmd);
    check(ret, "exec GMCommand JumpTo error");
    log( "successfully enter instance id = "..prog_scene_id );
    wait(2);
 
	-- 开始测试
    print( "processing ai_data.nAIID = "..ai_data.nAIID ); 			        
    ret = testAI( user, role, ai_data);
    print( "== finished processing ai_data.nAIID="..ai_data.nAIID );    
    	
    --测试完成，登出
    cleanup(user);
end

function TestCase.MonsterAIAll()
  
	local data_mgr = CDataManager_AI_DATA_:GetInstance();
	
    -- 挨个测试 npc 数据
    local ai_data = data_mgr:GetFirstData(); 
    if 0 == ai_data.nAIID then  -- default config 
		ai_data = data_mgr:GetNextData();
	end
	
    while( ai_data ) do
		check(ai_data, "failed to GetFirstai_data ");
		
        print( "processing ai_data.nAIID = "..ai_data.nAIID );			        
        ret = EnterInstanceAndTestAI( ai_data);
        print( "== finished processing ai_data.nAIID="..ai_data.nAIID );
		
        ai_data = data_mgr:GetNextData();
    end
    
end

function TestCase.MonsterAIOne()
  
	local data_mgr = CDataManager_AI_DATA_:GetInstance();
	
    -- 挨个测试 npc 数据
    local ai_data = data_mgr:GetData(90);   
	check(ai_data, "failed to GetData ");

    print( "processing ai_data.nAIID = "..ai_data.nAIID );      
    ret = EnterInstanceAndTestAI( ai_data);
    print( "== finished processing ai_data.nAIID="..ai_data.nAIID );
	    
end
