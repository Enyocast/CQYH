class MMOUISkillSettingPanel extends MMOUIBase
	dependson(UIKeyMapManager)
	native(UI)
	config(UIVisibleMask);

var int SkillLevelUpLimitLv;

//active skills
var bool IsShowAllActiveSkills;

var bool IsAutoCheckSkillStyle;

var GFxObject ActiveSkillsListPanel;
var GFxObject ActiveSkillsDetailListPanel;
var int ActiveSkillsDetaiListPanelWidth;
var int ActiveSkillsDetaiListPanelHeight;
var GFxObject ActiveDetailSkillListPanelArrowMc;
var int ListArrowMcWidth;
var int ListArrowMcHeight;
var GFxObject CurActiveDetalSkillMainSkillMc;

var GFxObject ShowSkillSettingBtn;
var GFxObject ShowLearnedActiveSkillsChkBtn;
var GFxObject ShowAllActiveSkillsChkBtn;

var const int ActiveSkillsListItemHalfHeight;
var const int ActiveSkillsListItemWidth;

var const int ListArrowOffsetX;
var const int ListArrowOffsetY;
//-----------------------------------------------------------------------------------------

native function PostOnShow(bool v);
final native function UpdatePanel( int panelIdx );
final native function HidePanel();

event ShowPanelOf( int tabIdx )
{
	ActionScriptVoid( "UCShowContent" );
}

event SetTabVisible(bool skillPanel,bool heavenMain,bool gasMain,bool bloodPanel)
{
	ActionScriptVoid( "UCSetSkillTabVisibleState" );
}
//----------------------------------------------------------------------------------------
//active skills
final native function UpdateActiveSkillPanel();
final native function UpdateActiveSkillList();

final native function ShowActiveSkillDetailOf( GFxObject mc, int skillUniqueID, int showPosX, int showPosY );
final native function UpdateActiveSkillDetail( int skillUniqueID );
final native function HideActiveSkillDetail();

final native function ShowLearnedActiveSkills();
final native function ShowAllActiveSkills();

//
event SetActiveSkillList( GFxObject Provider )
{
	ActionScriptVoid( "UCSetActiveSkillList" );
}
//
event SetDetailActiveSkillList( GFxObject Provider )
{
	ActionScriptVoid( "UCSetDetailActiveSkillList" );
}

//----------------------------------------------------------------------------------------
//special skills
native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject srcSlotMC, GFxObject destSlotMC, ESlotPanelType srcSlotType, ECONTAINER_SLOT srcContainerID, int SrcSlotID, ESlotPanelType destSlotType, ECONTAINER_SLOT destContainerID, int destSlotID);
//
final native function UpdateSpecialSkillPanel();
final native function UpdateSpecialSkillList();
//
//native function BagSlotChange( INT BagId,INT SlotId );

event SetSpecialSkillList( GFxObject Provider )
{
	ActionScriptVoid( "UCSetSpecialSkillList" );
}
event CallSetWindowTitle(string title)
{
	ActionScriptVoid("SetWindowTitle");
}
event CallSetSkillTabState(int nIndex)
{
	ActionScriptVoid("UCSetSkillTabState");
}
//----------------------------------------------------------------------------------------
//===============================================================================================================
//===============================================================================================================
//function RegisterSkillSetting( MMOUISkillSettingPanel mc )
//{
//	_SkillSetting = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_SkillSetting);
//}

//native function PostAdvance(float DeltaTime);
native function ASStartDrag(GFxObject SrcItemSlot, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID);

final native function ASLevelUpSkill( int uniqueSkillID );
final native function ASShowTips_SkillLvUpBtn( GFxObject mc, int uniqueSkillID );
final native function ASHideTips_SkillLvUpBtn();

final native function ASShowTips_SkillTreeActiveSkill( GFXObject mc );
final native function ASHideTips_SkillTreeActiveSkill();

final native function ASShowTips_SkillTreeRuneSkill( GFXObject mc );
final native function ASHideTips_SkillTreeRuneSkill();

final native function ASShowSkillDetail( GFxObject mc, int skillUniqueID, int showPosX, int showPosY );
final native function ASOnScroolingActiveSkillList();

final native function ASShowLearnedActiveSkills();
final native function ASShowAllActiveSkills();
final native function ASShowSkillSetting();

final native function ASHideActiveDetailSkillsListPanel();

final native function ASSetSkill( INT skillSetIdx, INT uniqueSkillID );

final native function ASClickTab(int nIndex);
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=SkillSetting
	SkillLevelUpLimitLv=10
	ActiveSkillsListItemWidth=184
	ActiveSkillsListItemHalfHeight=31
	ListArrowOffsetX=15
	ListArrowOffsetY=34
}

