class MMOUIGuildWarEndPanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallUpdateGuildWarEndList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildWarEndList");
}

event CallUpdateGuildWarEndTime(string time)
{
	ActionScriptVoid("UCUpdateGuildWarEndTime");
}

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
