class MMOUIJourneyCompletePanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallJourneyComplete(string content)
{
	ActionScriptVoid("UCShowEffect");
}

native function ASJourneyComplete();

DefaultProperties
{
	DefaultVisible=false
	CloseOnEsc=false
}