LoadPackage("common.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
LoadPackage("score_def.pkg")

Include("script/include/btnod.lua")
Include("script/scene/ProgIsland/scene_bt.lua")
Include("script/stringtable/stringtable.lh")

Include("script/include/common_dungeon.lh")
--Include("script/include/common_dungeon_bt.lua")

Include("script/include/common_arena.lh")
--Include("script/include/common_arena_bt.lua")

-----------------------------Dungeon Test--------------------------
--Stage
--DUNGEON_STAGE_VAR_INDEX = 1;

--Dungeon Time
--DUNGEON_INIT_DURATION = 2 * 1000;
--DUNGEON_FINISH_WAIT_DURATION = 0.5 * 60 * 1000;
--DUNGEON_REWARD_WAIT_DURATION = 1 * 60 * 1000;
--DUNGEON_CLOSE_WAIT_DURATION = 2 * 60 * 1000;
--DUNGEON_MAX_DURATION = 200 * 60 * 1000;
--------------------------------------------------------------------


-----------------------------Arena Test-----------------------------
--Stage
--ARENA_STAGE_VAR_INDEX = 1;

--Dungeon Time
--ARENA_INIT_DURATION = 60 * 1000;
--ARENA_CLOSE_WAIT_DURATION = 1 * 60 * 1000;
--ARENA_MAX_DURATION = 5 * 60 * 1000;
--------------------------------------------------------------------
function InformRoleEnterScene(owner)
	return brvSuccess
end

function p( txt )
	print( txt );
end

