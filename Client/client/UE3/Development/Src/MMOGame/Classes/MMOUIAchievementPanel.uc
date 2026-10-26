class MMOUIAchievementPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

var int _GetRewardAchievementId;
var int _CurBaseClass;
var int _CurSubClass;
var int _CurId;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallSetWindowTitle(string title)
{
	ActionScriptVoid("UCSetWindowTitle");
}

event CallSetState(bool compare)
{
	ActionScriptVoid("UCSetState");
}

event CallUpdateCagetoryData(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateCagetoryData");
}

event CallUpdateCagetoryComplete(int baseClass, int baseCount, int subClass, int subCount)
{
	ActionScriptVoid("UCUpdateCagetoryComplete");
}

event CallUpdateAchievementSummaryData(int curTotal, int maxTotal, GFxObject dataSub, String recentTitle, GFxObject dataRecent)
{
	ActionScriptVoid("UCUpdateAchievementSummaryData");
}

event CallUpdateAchievementData(String roleName, int point, int complete, int total, String roleNameComp, int pointComp, int completeComp, int totalComp)
{
	ActionScriptVoid("UCUpdateAchievementData");
}

event CallUpdateAchievementList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateAchievementList");
}

event CallUpdateAchievementListData(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateAchievementListData");
}

event CallShowAchievementList()
{
	ActionScriptVoid("UCShowAchievementList");
}

event CallShowAchievementListItem(int id)
{
	ActionScriptVoid("UCShowAchievementListItem");
}

event CallHasGuild(bool has)
{
	ActionScriptVoid("UCHasGuild");
}

event CallSetTab(int type)
{
	ActionScriptVoid("UCUpdateSelectedTab");
}

event CallSetPlayerDead(bool dead)
{
	ActionScriptVoid("UCSetPlayerDead");
}

native final function ASUpdateCagetoryData(int type);
native final function ASUpdateSummaryData(int type);
native final function ASUpdateAchievementData(int baseClass, int subClass);
native final function ASUpdateAchievementList(int baseClass, int subClass);
native final function ASShowAchievementListByClass(int baseClass, int subClass);
native final function ASShowAchievementListById(int id);
native final function ASObtainRewardItem(int id);
native final function ASTriggerAchievementTrace(int id, bool trace);

DefaultProperties
{
	_GetRewardAchievementId=0
    _CurBaseClass=0
    _CurSubClass=0
	_CurId=0
	IsDynamicLoad=true
	DefaultVisible = false
}
