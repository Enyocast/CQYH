class MMOGFXPlayer_Achievement extends MMOGFXPlayer
	native(UI);

var MMOUIAchievementPanel _AchievementPanel;
var MMOUIAchievementHintPanel _AchievementHintPanel;

event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	//local int res;
	//res = _AchievementHintPanel.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
	//if (res == 0)
	//{
	//	return false;
	//}

	return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}

// AS->UC
function ASRegisterAchievementPanel(MMOUIAchievementPanel mc)
{ 
	_AchievementPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_Achievement);
}

function ASRegisterAchievementHintPanel(MMOUIAchievementHintPanel mc)
{
	_AchievementHintPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_AchievementHint);
}

native final function ASUpdateCagetoryData(int type);
native final function ASUpdateSummaryData(int type);
native final function ASUpdateAchievementData(int baseClass, int subClass);
native final function ASUpdateAchievementList(int baseClass, int subClass);
native final function ASShowAchievementListByClass(int baseClass, int subClass);
native final function ASShowAchievementListById(int id);
native final function ASObtainRewardItem(int id);
native final function ASPlayAchievementHintEnd();
native final function ASShowAchievementPanelById(int id);

DefaultProperties
{
	MovieInfoStr="UI_Achievement.Achievement"
	Priority = 5
}
