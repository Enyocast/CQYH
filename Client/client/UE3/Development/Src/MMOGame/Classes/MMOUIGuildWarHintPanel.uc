class MMOUIGuildWarHintPanel extends MMOUIBase
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

event CallUpdateGuildWarHintInfo(string attack, string defend, string timeTitle, string time)
{
	ActionScriptVoid("UCUpdateGuildWarHintInfo");
}

event CallUpdateGuildWarHintTime(string time)
{
	ActionScriptVoid("UCUpdateGuildWarHintTime");
}

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
	CloseOnEsc=false
}
