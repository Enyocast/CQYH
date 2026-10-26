class MMOUIQuestPanel extends MMOUIBase
	dependson(Quest)
	native(UI)
	config(UIVisibleMask);

enum EQuestItemType
{
	EQIT_Group,
	EQIT_Title,
};

var int _CurQuestStateGroup;
var int _CurQuestId;
var bool _ShowLowLvQuest;

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

event CallUpdateQuestList(GFxObject questList, int complete, int total)
{
	ActionScriptVoid("UCUpdateQuestList");
}

event CallUpdateQuestDetail(GFxObject questData)
{
	ActionScriptVoid("UCUpdateQuestDetailData");
}

native final function ASUpdateQuestList(int group);
native final function ASUpdateQuestDetail(int id);
native final function ASTraceQuest(int id, bool traced);
native final function ASTraceAllQuest(bool traced);
native final function ASFilterLowLevelQuest(bool showLowLvQuest);
native final function ASShareQuest(int id);
native final function AbortQuest(int id);
native final function ASAbortCurQuest(int id);
native final function ASAcceptQuestWithoutNpc(int id);
native final function ASCompleteQuestWithoutNpc(int id);

function AbortQuestOK(GFxObject mc)
{
	local int questID;
	questID = mc.GetInt("iteminfoid");
	AbortQuest(questID);
}

function AbortQuestCanel(GFxObject mc)
{
}

function RefreshTopLevelRewardQuestOK(GFxObject mc)
{
}

function RefreshTopLevelRewardQuestCancel(GFxObject mc)
{
}

DefaultProperties
{	
	IsDynamicLoad=true
}
