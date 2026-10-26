LoadPackage("gameworld.pkg")

Include("script/include/btnod.lua")
Include("script/include/desert_battle.lh")


function InformRoleEnterScene(owner)
	return brvSuccess
end

Include("script/scene/DesertBattle02/scene_bt.lua")