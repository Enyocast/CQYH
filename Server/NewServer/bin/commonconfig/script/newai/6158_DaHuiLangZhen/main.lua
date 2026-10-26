Include("script/stringtable/stringtable.lh")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
Include("script/newai/sub_tree/sub_tree.lh");
LoadPackage("chat_def.pkg")
LoadPackage('variable.pkg')

MAX_NPC_REWARD_COUNT = 20;

function get_zongzi_num(owner, index, MAX_NPC_REWARD_COUNT)
	return MAX_NPC_REWARD_COUNT - (owner:GetAIProcessor():GetVariable(index));
end



Include("script/newai/6158_DaHuiLangZhen/main.uh")


