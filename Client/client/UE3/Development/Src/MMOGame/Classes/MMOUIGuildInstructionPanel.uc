class MMOUIGuildInstructionPanel extends MMOUIBase
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

event CallSetContent(String content)
{
	ActionScriptVoid("UCSetContent");
}

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
