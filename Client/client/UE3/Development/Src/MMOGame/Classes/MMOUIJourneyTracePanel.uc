class MMOUIJourneyTracePanel extends MMOUIBase
	dependson(Quest)
	native(UI);

var int _CurJourneyId;
var int _CurExpandType;

native function OnFocusGained();
native function OnFocusLost();

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallUpdateJourneyTraceList(GFxObject dataProvider, int curJourneyId)
{
	ActionScriptVoid("UCSetChapterData");
}

event CallUpdateJourneyTraceInfo(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateJourneyTraceInfo");
}

event CallUpdateJourneyQuestData(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateQuestTraceListItemData");
}

event CallShowChangeLevelHint(bool show, string content)
{
	ActionScriptVoid("ShowChangeLevelHint");
}

event CallUpdateJourneyReputation(int curReputation, int maxReputation, int minReputation, string tips, bool chapterComplete, bool hasGetReward)
{
	ActionScriptVoid("UCUpdateJourneyTraceProgress");
}

final native function ASGotoChapter(int journeyId);
final native function ASUpdateNPCTips(int index);
final native function ASShowAwardsPanel(int journeyId);
final native function ASSetCurItemState(int journeyType, bool expand);
final native function ASObtainAchievementReward(int achievementId);
final native function ASShowJourneyTracePanle(bool show);

event CallShowActivateJourneyType(bool show, int type, string guide_name)
{
	ActionScriptVoid("UCShowGuideArrow");
}

event CallClearGuideEffect()
{
	ActionScriptVoid("UCClearGuideArrow");
}

event CallSetPlayerDead(bool dead)
{
	ActionScriptVoid("UCSetPlayerDead");
}

event CallSetTracePanelEnable(bool enable)
{
	ActionScriptVoid("UCSetTracePanelEnable");
}

native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

DefaultProperties
{
	_CurJourneyId=0
	_CurExpandType=0
	DefaultVisible=true
	CloseOnEsc=false
}