class MMOUIJourneyViewPanel extends MMOUIBase
	dependson(Quest)
	native(UI);

var int _CurJourneyId;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallUpdateJourneyList(GFxObject dataProvider, int selectIndex)
{
	ActionScriptVoid("updateItemsData");
}

event CallUpdateJourneyInfo(GFxObject dataProvider)
{
	ActionScriptVoid("UpdateSelected");
}

native function ASUpdateJourneyInfo(int journeyId);
native function ASGetCompleteAwards(int journeyId);

DefaultProperties
{
	_CurJourneyId=0
	DefaultVisible=false
}