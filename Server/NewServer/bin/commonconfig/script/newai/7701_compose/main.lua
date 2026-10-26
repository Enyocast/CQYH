Include("script/stringtable/stringtable.lh")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
Include("script/newai/sub_tree/sub_tree.lh");
LoadPackage("chat_def.pkg")
Include("script/newai/7701_compose/main.uh")

local g_oGameWorld = CGameWorld:GetInstance();