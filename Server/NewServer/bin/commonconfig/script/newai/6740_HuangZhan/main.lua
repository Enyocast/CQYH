LoadPackage("chat_def.pkg")
LoadPackage("global_config.pkg");
Include("script/stringtable/stringtable.lh")

DIALOG_STR1 = 2030;    -- Register for the Imperial City battle
DIALOG_STR2 = 2031;    -- View registered guilds
DIALOG_STR3 = 2032;    -- Registration costs 5,000 gold

function check_sabac_disabled(owner)
	if g_GWConfig.Sabac.bEnabled then
		return brvFail
	else
		return brvSuccess
	end
end

Include("script/newai/sub_tree/sub_tree.lh")
Include("script/newai/6740_HuangZhan/main.uh")