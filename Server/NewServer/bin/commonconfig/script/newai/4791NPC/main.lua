
Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
Include("script/newai/sub_tree/sub_tree.lh")

local sign_indexvariable = 141;

local sign_reward_table = 
		{
			0,
			321,
			301,
			302,
			322,
			303,
			323,
			363,
		};

local collection_variable = 143;
local collection_reward = 373;
local collection_check_table = 
		{
			321,
			301,
			302,
			322,
			303,
			323,
		};

Include("script/newai/4791NPC/main.uh")


