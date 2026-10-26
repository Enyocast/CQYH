class MMOUIGuildWarStartPanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallSetWindowTitle(string title)
{
	ActionScriptVoid("UCSetWindowTitle");
}

event CallUpdateGuildWarStartInfo(string icon, string text)
{
	ActionScriptVoid("UCUpdateGuildWarStartInfo");
}

// ≤Œ’Ω
native final function ASJoinWar();

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
