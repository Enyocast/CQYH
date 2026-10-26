LoadPackage("math_ex.pkg")
LoadPackage("character.pkg")
LoadPackage("npc.pkg")
LoadPackage("spell.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("scene_def.pkg")
Include("script/newai/sub_tree/sub_tree.lh")
Include("script/newai/5216_ImmolithBOSS02/main.uh");


--[[
fire_pos={
	[1]={x=16070*POINT_PER_CM, y=45541*POINT_PER_CM, dir=45/360* MAX_DIRECTION_COUNT,},
	[2]={x=17504*POINT_PER_CM, y=45174*POINT_PER_CM, dir=45/360* MAX_DIRECTION_COUNT,},
	[3]={x=18763*POINT_PER_CM, y=46431*POINT_PER_CM, dir=45/360* MAX_DIRECTION_COUNT,},
	[4]={x=18586*POINT_PER_CM, y=48060*POINT_PER_CM, dir=45/360* MAX_DIRECTION_COUNT,},
	[5]={x=16964*POINT_PER_CM, y=48237*POINT_PER_CM, dir=45/360* MAX_DIRECTION_COUNT,},
	[6]={x=15709*POINT_PER_CM, y=46979*POINT_PER_CM, dir=45/360* MAX_DIRECTION_COUNT,},
	[7]={x=17324*POINT_PER_CM, y=46795*POINT_PER_CM, dir=45/360* MAX_DIRECTION_COUNT,},
	[7]={x=17324*POINT_PER_CM, y=46795*POINT_PER_CM, dir=45/360* MAX_DIRECTION_COUNT,},
};

PHASE_INCREASE_WHEN_CD_TIMES = 4;
FIRE_SPELL_DURATION = 7 * GAME_FPS;

function FireAround( owner, npcid )
	local gameworld = CGameWorld:GetInstance();
	local current_frame = gameworld:GetGameFrame();
	local processor = owner:GetAIProcessor();
	local scene = owner:GetScene();
	local owner_level = owner:GetLevel();

	local target_char = gameworld:FindCharacter( processor:GetTargetID() );
  if( not target_char ) then
		return brvError;
  end

	-- get phase
	local phase = processor:GetVariable(0);
	phase = phase + 1;
	if( phase % 100 >= PHASE_INCREASE_WHEN_CD_TIMES
			and math.floor(phase/100) + 1 < table.maxn(fire_pos) ) then
		phase = ( math.floor(phase/100) + 1 ) * 100;
	end
	print("FireAround:new phase="..phase);
	processor:SetVariable( 0, phase );

	local fire_num = math.floor( phase/100 ) + 1;

	local on_fire = {};
	local on_fire_num = 0;
	local off_fire = {};
	local off_fire_num = 0;

	--  sort pos
	for i = 1, table.maxn(fire_pos) do
		local fire_start_frame = processor:GetVariable(i);
		if ( fire_start_frame + FIRE_SPELL_DURATION <= current_frame ) then
			off_fire[i] = true;
			off_fire_num = off_fire_num + 1;
		else
			on_fire[i] = true;
			on_fire_num = on_fire_num + 1;
		end
	end

	-- decide pos
	local need_fire_index = {};
	local need_fire_num = fire_num - on_fire_num;
	print( "FireAround: fire_num="..fire_num..",need_fire_num="..need_fire_num );

	if( need_fire_num > 0 ) then
		for i,v in ipairs( off_fire ) do
			table.insert( need_fire_index, i );
			need_fire_num  = need_fire_num - 1;
			if( need_fire_num <= 0 ) then
				break;
			end
		end
	end

	-- random
	--[-[
	for i=1, ( table.maxn( fire_pos )/2 ) do
		local index = math.random( table.maxn( fire_pos ) );

		if( index == i )then
			index = i+1;
 		end

		local temp = fire_pos[i];
		fire_pos[i] = fire_pos[index];
		fire_pos[index] = temp;
	end
	--]-]

	-- fire
	for i=1, table.maxn(need_fire_index) do
		assert( need_fire_index[i] > 0 and need_fire_index[i] < 8 );
		local index = need_fire_index[i];
		print("FireAround: fire index="..index);
		local npc = scene:SpawnNpc( npcid, owner_level, nqNormal, fire_pos[index].x, fire_pos[index].y, owner:GetZ(), fire_pos[ index ].dir, 0, nil);
		if( npc ) then

			processor:SetVariable( need_fire_index[i], current_frame );
		end
	end

	return brvSuccess;
end]]--


