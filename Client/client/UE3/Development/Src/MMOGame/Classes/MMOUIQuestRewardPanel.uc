class MMOUIQuestRewardPanel extends MMOUIBase
	dependson(Quest)
	native(UI)
	config(UIVisibleMask);

var int _CurQuestId;
var bool _ShowCompleteQuest;

var GFxObject RefreshNowConfirmBox;
var GFxObject RefreshTopConfirmBox;
var GFxObject CompleteAllConfirmBox;
var GFxObject UpgradeLimitConfirmBox;
var GFxObject AbandonLowConfirmBox;
var GFxObject AbandonHighConfirmBox;

native function PlayerLevelChange( int lastLv , int newLv );
native function ItemChange(int ContainerID, int SlotID);
native function ItemDelete(int ContainerID, int SlotID);

native function AgreeRefreshNow(GFxObject mc);
native function RefuseRefreshNow(GFxObject mc);

native function AgreeUpgradeLimit(GFxObject mc);
native function RefuseUpgradeLimit(GFxObject mc);

native function AgreeCompleteAll(GFxObject mc);
native function RefuseCompleteAll(GFxObject mc);

native function AgreeAbandonLow(GFxObject mc);
native function RefuseAbandonLow(GFxObject mc);

native function AgreeAbandonHigh(GFxObject mc);
native function RefuseAbandonHigh(GFxObject mc);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event CallSetWindowTitle(string title)
{
	ActionScriptVoid("UCSetWindowTitle");
}

event CallUpdateRewardQuestList(GFxObject questList)
{
	ActionScriptVoid("UCUpdateRewardQuestList");
}

event CallUpdateRewardQuestDetail(GFxObject questData)
{
	ActionScriptVoid("UCUpdateRewardQuestDetailData");
}

event CallUpdateRewardQuestAvailableLimit(int cur)
{
	ActionScriptVoid("UCUpdateRewardQuestAvailableLimit");
}

event CallUpdateRewardQuestRefreshTime(int hour, int min, int sec)
{
	ActionScriptVoid("UCUpdateRewardQuestRefreshTime");
}

native final function ASUpdateRewardQuestDetail(int id);
native final function ASUpgradeAvailableLimit();
native final function ASRefreshRewardQuestList(bool autoRefresh);
native final function ASCompleteAllRewardQuest();
native final function ASShowCompletedRewardQuest(bool show);
native final function ASRefreshTopLevelRewardQuest(bool refresh);
native final function ASAcceptRewardQuest(int id);
native final function ASAbandonRewardQuest(int id);

DefaultProperties
{	
	IsDynamicLoad=true
	IsTargetOutDistanceClose = true
}
