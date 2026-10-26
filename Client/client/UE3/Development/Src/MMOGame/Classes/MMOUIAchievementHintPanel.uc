class MMOUIAchievementHintPanel extends MMOUIBase
	native(UI);

var int _CurId;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

// UC->AS
event CallSetNewAchievementData(int id, string icon, string title, int point)
{
	ActionScriptVoid("UCSetNewAchievementData");
}

native final function ASPlayAchievementHintEnd();
native final function ASShowAchievementPanelById(int id);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
	LastVisibleRecover=false
	_CurId=0
}
