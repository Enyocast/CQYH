class MMOUIReputationPanel extends MMOUIBase
native(UI)
config(UIVisibleMask);

struct native ReputationData2
{
	var int     TempIndex;
	var int     type;
	var int     ForceID;
	var int	    ForceLevel;
	var int     InitValue;
	var int     MaxValue;
	var init String  ForceName;
	var init String  ForceTips;
	var init String  ForceInfo;
	var bool    Visible;
	var bool    awardState;
};

var array<ReputationData2> ReputationList;
//var array<string> ReputationName;
//var array<int> ReputationValue;

var int  SelectListID;

var array<GFxObject> ItemSlot;

native function int KeyToNumber(String Key, int index);
native function InitReputationData();
native function UpdateReputationData();
native function UpdateRewordSlot(GFxObject SlotObj);
native function ChangeReputationType(int ID,int ReputationType);
native function SetItemBarData( GFxObject mc , Item item , int slotId , int num); 

native function AwardClick(int ForceID);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
	InitReputationData();
}

event InitOnce()
{
	super.InitOnce();

}

event CallUpdateItemsData(GFxObject Provider)
{
	ActionScriptVoid("updateItemsData");
}

//event CallInitList(int InTraceListIndex)
//{
//	ActionScriptVoid("initList");
//}

event CallSetSelectedItem(int SelectedForceID)
{
	ActionScriptVoid("SetSelectedItem");
}

event CallRefreshReputationSelected()
{
	ActionScriptVoid("RefreshSelected");
}

function RefreshReputationSelected()
{
	CallRefreshReputationSelected();
}

native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

function ASChangeReputationType( int ID,int ReputationType )
{
	ChangeReputationType( ID, ReputationType );
}

function ASUpdateRewordSlot(GFxObject SlotObj)
{
	UpdateRewordSlot(SlotObj);
}

function ASAwardClick(int ForceID)
{
	AwardClick(ForceID);
}

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=true
	SelectListID=-1
}
