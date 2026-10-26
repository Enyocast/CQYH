class MMOUIActivityQuitPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);


var int  nCurSortType;
var int  nSortAdd;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallSetWindowTitle(string title)
{
	ActionScriptVoid("SetWindowTitle");
}

event CallUpdateActivityQuitList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateActivityQuitListData");
}

event CallUpdateQuitActivityValue(String data)
{
	ActionScriptVoid("UCUpdateActivityValue");
}

event CallUpdateRememberContent(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateRememberContent");
}

event CallUpdateQuitActivityReward(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateQuitActivityReward");
}

event CallShowRewardBar(bool bShow)
{
	ActionScriptVoid("UCShowRewardBar");
}

native function ASClickQuitListHeadSort(int type);
native function ASClickOpenActivityPanel();
native function ASClickBackGame();
native function ASClickBackLogin();
native function ASClickQuitGame();
native function ASClickQuitGetReward(int nIndex);

DefaultProperties
{	
	IsDynamicLoad=true
	DefaultVisible = false
	nCurSortType = -1;
	nSortAdd = 0;
}
