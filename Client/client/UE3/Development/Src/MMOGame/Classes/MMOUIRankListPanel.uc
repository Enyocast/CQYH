class MMOUIRankListPanel extends MMOUIBase
	dependson(UIKeyMapManager)
	native(UI)
	config(UIVisibleMask);

var float currentTime;
var bool refresh;

var float freshTime;

var float showRankTime;

native function NativeInitLoad();
native function NativeInitOnce();

native function OnPersonTreeItemClick(INT index);
native function OnGuildTreeItemClick(INT index);
native function OnTournamentTreeItemClick(INT index);
native function OnPowerTreeItemClick(INT index);
native function OnActivityTreeItemClick(INT Index);

native function OnPersonTabClick();
native function OnGuildTabClick();
native function OnTournamentTabClick();
native function OnPowerTabClick();
native function OnActivityTabClick();

native function OnRangeClick(INT index);
native function OnCategoryClick(INT index);

native function OnPrevPageClick();
native function OnNextPageClick();

native function OnRightClick1Menu(INT Id);
native function OnRightClick2Menu(INT Id);

native function OnPeronMasterClick(INT Id);

native function bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

native function BeforeViewUpdate( float DeltaTime );

event CallUpdateActivityListData(GFxObject Provider)
{
	ActionScriptVoid("UCUpdateActiveListData");
}

event CallUpdatePersonListData(GFxObject Provider)
{
	ActionScriptVoid("UCUpdatePersonListData");
}

event CallLoadPersonMenuData(GFxObject Provider)
{
	ActionScriptVoid("UCLoadPersonMenuData");
}

event CallUpdateGuildListData(GFxObject Provider)
{
	ActionScriptVoid("UCUpdateGuildListData");
}

event CallLoadGuildMenuData(GFxObject Provider)
{
	ActionScriptVoid("UCLoadGuildMenuData");
}

event CallUpdateTournamentListData(GFxObject Provider)
{
	ActionScriptVoid("UCUpdateTournamentListData");
}

event CallLoadTournamentMenuData(GFxObject Provider)
{
	ActionScriptVoid("UCLoadTournamentMenuData");
}

event CallLoadActiveMenuData(GFxObject Provider)
{
	ActionScriptVoid("UCLoadActiveMenuData");
}

event CallLoadPowerMenuData(GFxObject Provider)
{
	ActionScriptVoid("UCLoadPowerMenuData");
}

event CallupdatePowerListData(GFxObject Provider)
{
	ActionScriptVoid("UCUpdatePowerListData");
}

event CallUpdatePage(string Page)
{
	ActionScriptVoid("UCUpdatePage");
}

event CallUpdateMyRank(string rank, int currentIndex,int lastIndex)
{
	ActionScriptVoid("UCUpdateMyRank");
}

event CallSetRankPageButton( GFxObject data )
{
	ActionScriptVoid("UCSetRankPageButton");
}

event CallUpdateRangeRdoSelect(int nIndex)
{
	ActionScriptVoid("UCUpdateRangeRdoSelect");
}

event CallUpdateTime(string text)
{
	ActionScriptVoid("UCUpdateTime");
}

event CallUpdateCategoryButton()
{
	ActionScriptVoid("UCUpdateCategoryButton");
}

event CallUpdateActivityRdo(int idx)
{
	ActionScriptVoid("UCUpdateActivityRdo");
}

event CallUCSetMaxLevel(string lv)
{
	ActionScriptVoid("UCSetMaxLevel");
}

event CallUCOnPersonTabClick()
{
	ActionScriptVoid("UCOnPersonTabClick");
}

event CallUCShowRank(bool showRank)
{
	ActionScriptVoid("UCShowRank");
}
event CallShowUCActiveMsg(string msg)
{
	ActionScriptVoid("UCUpdateArenaTips");
}
//-----------------------
function ASPersonTreeItemClick(int index)
{
	OnPersonTreeItemClick(index);
}

function ASGuildTreeItemClick(int index)
{
	OnGuildTreeItemClick(index);
}

function ASTournamentTreeItemClick(int index)
{
	OnTournamentTreeItemClick(index);
}

function ASPowerTreeItemClick(int index)
{
	OnPowerTreeItemClick(index);
}

function ASActiveTreeItemClick(int index)
{
	OnActivityTreeItemClick(index);
}
function ASPersonTabClick()
{
	OnPersonTabClick();
}

function ASGuildTabClick()
{
	OnGuildTabClick();
}

function ASTournamentTabClick()
{
	OnTournamentTabClick();
}

function ASPowerTabClick()
{
	OnPowerTabClick();
}

function ASRangeClick(int index)
{
	OnRangeClick(index);
}

function ASCategoryClick(int index)
{
	OnCategoryClick(index);
}

function ASRightClick1Menu(int Id)
{
	OnRightClick1Menu(Id);
}

function ASRightClick2Menu(int Id)
{
	OnRightClick2Menu(Id);
}

function ASPersonMasterClick(int Id)
{
	OnPeronMasterClick(Id);
}

function ASPrevPageClick()
{
	OnPrevPageClick();
}

function ASNextPageClick()
{
	OnNextPageClick();
}

function ASActivityTabClick()
{
	OnActivityTabClick();
}

DefaultProperties
{
	IsDynamicLoad=true
}
