LoadPackage("chat_def.pkg")
LoadPackage("global_config.pkg");
Include("script/stringtable/stringtable.lh")

DIALOG_STR1 = 2030;    -- 报名皇城争霸战
DIALOG_STR2 = 2031;    -- 查看已报名公会
DIALOG_STR3 = 2032;    -- 报名需要扣除5000金币

function check_sabac_disabled(owner)
	if g_GWConfig.Sabac.bEnabled then
		return brvFail
	else
		return brvSuccess
	end
end

Include("script/newai/sub_tree/sub_tree.lh")
Include("script/newai/6740_HuangZhan/main.uh")