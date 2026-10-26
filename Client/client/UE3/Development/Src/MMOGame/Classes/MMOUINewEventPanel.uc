class MMOUINewEventPanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallShowNewEvent(int type, string text)
{
	ActionScriptVoid("UCShowNewEvent");
}

DefaultProperties
{
	DefaultVisible = false
}