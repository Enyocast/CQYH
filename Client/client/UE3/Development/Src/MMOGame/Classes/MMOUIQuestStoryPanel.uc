class MMOUIQuestStoryPanel extends MMOUIBase
	dependson(Quest)
	native(UI)
	config(UIVisibleMask);

var int _CurQuestId;

native function PlayerLevelChange( int lastLv , int newLv );
native function ItemChange(int ContainerID, int SlotID);
native function ItemDelete(int ContainerID, int SlotID);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event CallSetWindowTitle(string title)
{
	ActionScriptVoid("UCSetWindowTitle");
}

event CallUpdateQuestStoryOverDesc(string desc)
{
	ActionScriptVoid("UCUpdateQuestStoryOverDesc");
}

event CallUpdateQuestStoryDetailInfo(GFxObject data)
{
	ActionScriptVoid("UCUpdateQuestDetailData");
}

event CallUpdateQuestStoryChapterList(GFxObject list)
{
	ActionScriptVoid("UCUpdateQuestStoryChapterList");
}

event CallUpdateQuestStoryStageList(GFxObject list)
{
	ActionScriptVoid("UCUpdateQuestStoryStageList");
}

event CallUpdateQuestStoryStageInfo(string caption, string desc)
{
	ActionScriptVoid("UCUpdateQuestStoryStageInfo");
}

native final function ASUpdateCurQuestInfo();
native final function ASUpdateQuestChapterList();
native final function ASUpdateQuestStageList(int chapter);
native final function ASViewStoryQuestStageInfo(int chapter, int stage);

DefaultProperties
{	
	IsDynamicLoad=true
}
