class MMOUIGuildWeatherPanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallUpdateGuildWeatherInfo(GFxObject object)
{
	ActionScriptVoid("UCUpdateGuildWeatherInfo");
}

native final function ASChangeWeather(int weatherType, int durationType);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
