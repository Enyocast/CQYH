class MMOUIWeatherChangePanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallSetWeatherChangeString(string content)
{
	ActionScriptVoid("UCSetWeatherChangeString");
}

native function ASWeatherChangePlayEnd();

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible = false
}