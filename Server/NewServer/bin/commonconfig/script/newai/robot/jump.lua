
-----------------jump scene function---------------------------------------------
function JumpToScene(user, role, nSceneTempID, nSceneID, X, Y, Z)
	
	local oSrcSceneTempID = 0;
	local oSrcSceneID = 0;
	local oSrcScene = role:GetScene();
	
	if oSrcScene then
		oSrcSceneTempID = oSrcScene:GetSceneTempID();
		oSrcSceneID = oSrcScene:GetSceneID();
	end
	
    local cmd = "Jump("..nSceneTempID..","..nSceneID..","..X..","..Y..","..Z..")";
    print(cmd);
    
    user:GMCommand(cmd);
   
    if oSrcSceneTempID ~= nSceneTempID then
        --role:Say(cctGroup, cltNormal, role:GetName()..' jump to scene ('..nSceneTempID..', '..X..', '..Y..', '..Z..')');
    end
end

function jump_current_scene(user, role)
	local oScene = role:GetScene();
	local nSceneTempID = oScene:GetSceneTempID();
	
	if g_scene[nSceneTempID] then
		local randIndex = math.random(1, #g_scene[nSceneTempID]);
		local pos = g_scene[nSceneTempID][randIndex];
		JumpToScene(user, role, nSceneTempID, oScene:GetSceneID(), pos.X, pos.Y, pos.Z);
	else
		JumpToScene(user, role, oScene:GetSceneTempID(), oScene:GetSceneID(), 
			role:GetX()/POINT_PER_CM, role:GetY()/POINT_PER_CM, role:GetZ()/POINT_PER_CM);
	end
end

function jump_static_scene(user, role)
	local nRandIndex = math.random(1, 100);
	
	if nRandIndex < 80 then
		local nRandIndex = math.random(1, g_lineSceneCount);
		
		if g_lineScene[nRandIndex] ~= nil then
			JumpToScene(user, role, g_lineScene[nRandIndex].sceneTempID, 0, 
				g_lineScene[nRandIndex].X, 
				g_lineScene[nRandIndex].Y, 
				g_lineScene[nRandIndex].Z);
		end
	else
		local nRandIndex = math.random(1, g_staticSceneCount);
		
		if g_staticScene[nRandIndex] ~= nil then
			JumpToScene(user, role, g_staticScene[nRandIndex].sceneTempID, 1, 
				g_staticScene[nRandIndex].X, 
				g_staticScene[nRandIndex].Y, 
				g_staticScene[nRandIndex].Z);
		end
	end
end

function do_jump_action(owner)
	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
    local user =  CUserMgr:GetInstance():FindUser(role:GetSessionID());

	local nRandIndex = math.random(1, 1000);
    if nRandIndex < 50 then
    	jump_static_scene(user, role);	
    else
		if nRandIndex < 100 then
			local scene = role:GetScene();
			local sceneData = scene:GetSceneData();
			local sceneID = scene:GetSceneID();
			if sceneData.nType == estLine and sceneID > 1 then
				user:ChangeLine(math.random(1, sceneID - 1));
				return;
			end
		end

        jump_current_scene(user, role);
    end
    
    return brvSuccess;
end

jump_tree = 
{ batSequencer,
    { batCheckCDTimer, param = { COOLDOWN_AI, JUMP_CD_TIMER } },
    { batSetCDTimer, param  = { COOLDOWN_AI, JUMP_CD_TIMER, JUMP_SCENE_INTERVAL } },		
    { do_jump_action },
    { batWait, param = { 8 * 1000 } },
    { batSetHome },
};

rotate_tree = 
{ batSequencer,
    { batCheckCDTimer, param = { COOLDOWN_AI, ROTATE_CD_TIMER } },
    { batSetCDTimer, param  = { COOLDOWN_AI, ROTATE_CD_TIMER, ROTATE_INTERVAL } },		
	{ batCheckCharMoveState, param = { tarSelf, CMS_STAND } },
	{ batRotateTo, param = { tarSelf, 90, 0 } },
};
