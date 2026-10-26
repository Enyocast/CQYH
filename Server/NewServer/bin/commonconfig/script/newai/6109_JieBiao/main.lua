Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
LoadPackage("role.pkg");
LoadPackage("gameworld.pkg");
LoadPackage("quest_list.pkg");
LoadPackage("quest_def.pkg");
LoadPackage("npc.pkg");
LoadPackage("npc_def.pkg");
LoadPackage("scene.pkg");
LoadPackage("error_def.pkg");


Include("script/newai/sub_tree/sub_tree.lh")
Include("script/include/escort.lh")

DIALOG_SUBMIT_ESCORT = 50064;
DIALOG_SUBMIT_ESCORT_SUCCESS_CONFIRM = 50065;
DIALOG_SUBMIT_ESCORT_FAIL_CONFIRM = 50066;
DIALOG_SUBMIT_ESCORT_NONE = 50067;

Include("script/newai/6109_JieBiao/main.uh")


