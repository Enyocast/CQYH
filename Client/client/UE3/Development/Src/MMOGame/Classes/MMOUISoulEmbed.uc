class MMOUISoulEmbed extends MMOUIBaseSlotContainer
	native(UI)
	dependson(TypeDefine)
	config(UIVisibleMask);

enum SoulPanelEmbedType
{
	ESOLPT_Embed,
	ESOLPT_Unembed,
	ESOLPT_LevelUp
};
var SoulPanelEmbedType _CurType;

enum SoulEmbedPanelSlotType
{
	ESolEbd_EmbedSoulInvalid,
	ESolEbd_EquipToEmbed,
	ESolEbd_EmbedSoul1,
	ESolEbd_EmbedSoul2,
	ESolEbd_EmbedSoul3,
	ESolEbd_EquipToUnEmbed,
	ESolEbd_UnEmbedSoul1,
	ESolEbd_UnEmbedSoul2,
	ESolEbd_UnEmbedSoul3,
};

//
var OperationItemBagPos _ToEmbedEquip;
var const int MAX_EmbedSoul;// = 3;
var OperationItemBagPos _ToEmbedSoul[3];

var native Map_Mirror _EmbedEquipPropSoulAdd{TMap< FString, INT >};
var native Map_Mirror _EmbedEquipPropBase{TMap< FString, INT >};
var native Map_Mirror _ToEmbeSoulPropAdd{TMap< FString, INT >};

var GFxObject _EmbedTabBtn;
var GFxObject _UnEmbedTabBtn;
//Embed
var GFxObject _EmbedSoulPanel;

var GFxObject _ToEmbedEquipMc;
struct native StcSoulMc
{
	var GFxObject _Slot;
	var GFxObject _Bg;
};
var StcSoulMc _EmbedSoulMc[3];
var GFxObject _OriginalPropTf;
var GFxObject _ResultPropTf;
var GFxObject _TotalSoulPropTf;

var GFxObject _ConfirmBtn;
var GFxObject _ResetBtn;
var bool _IsWaitReult;

//UnEmbed
var GFxObject _UnEmbedSoulPanel;
var OperationItemBagPos _ToUnEmbedEquip;
var int _ToUnEmbedSoulIdx;
//
var GFxObject _ToUnEmbedEquipMc;
var StcSoulMc _UnEmbedSoulMc[3];
var GFxObject _OriginalPropInUnEmbedTf;
var GFxObject _ResultPropInUnEmbedTf;
var GFxObject _TotalSoulPropInUnEmbedTf;
var GFxObject _SoulEmbedHintTf;

var GFxObject _UnEmbedFeeTf;
var GFxObject _UnEmbedConfirmBtn;
var GFxObject _UnEmbedCancelBtn;

//soul level up
enum SoulLevelUpPanelSlotType
{
	ESOLPST_LvUpSoulInvalid,
	ESOLPST_LvUpSoul,
	ESOLPST_LvUpScrificSoul1,
	ESOLPST_LvUpScrificSoul2,
	ESOLPST_LvUpScrificSoul3,
	ESOLPST_LvUpScrificSoul4,
	ESOLPST_LvUpScrificSoul5,
	ESOLPST_LvUpHelpItem
};

var GFxObject _LvUpSoulPanel;
var OperationItemBagPos _ToLvUpSoul;
var OperationItemBagPos _HelpLvUpSoulItem;
var const int MAX_SacrificeSoul;// = 5;
var OperationItemBagPos _SacrificeSoul[5];

var GFxObject _ToLvUpSoulMc;
var GFxObject _SacrificeSoulMc[5];
var GFxObject _HelpLvUpSoulItemMc;
var GFxObject _SuccessRitoTf;
var GFxObject _CurLevelSoulPropTf;
var GFxObject _NextLevelSoulPropTf;
var GFxObject _ConfirmLevelUpBtn;
var GFxObject _ResetLevelUpBtn;

//
native function NativeInitLoad();
native function ClearUI();
native function ResetPanel(int tabIdx);
native function BagSlotChange( int bagId, int slotId );
//native function OnItemDeleted( int containerID, int slotID );
native function PlayerMoneyChange( EMONEY_TYPE MoneyType, int DeltaMoney);
//
native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject srcSlotMC, GFxObject destSlotMC, ESlotPanelType srcSlotType, ECONTAINER_SLOT srcContainerID, int SrcSlotID, ESlotPanelType destSlotType, ECONTAINER_SLOT destContainerID, int destSlotID);

//
final native function SetTitleName();
final native function UpdatePanelTab();
final native function UpdatePanel();
final native function OnTabBtnClick( int tabIdx );
//event ChangeContentTabBtn( int tabIdx )
//{
//	ActionScriptVoid( "UCShowContent" );
//}
//
final native function ResetUI();

event CallUCGraySlot( GFxObject slot , bool gray)
{
	ActionScriptVoid("UCGraySlot");
}

//soul embed
native function BagSlotChangeOnSoulEmbed( int bagId, int slotId );
native function bool OnRightMouseClickEmbed(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDropEmbed(GFxObject srcSlotMC, GFxObject destSlotMC, ESlotPanelType srcSlotType, ECONTAINER_SLOT srcContainerID, int SrcSlotID, ESlotPanelType destSlotType, ECONTAINER_SLOT destContainerID, int destSlotID);

final native function ResetSoulEmbed();

final native function UpdateSoulEmbed();
final native function UpdateSoulEmbedProp();

final native function int UpdateEquipSoulSlot();

final native function UpdateEquipPropData( int conID, int slotID );
final native function UpdateToEmbedSoulPropData();

final native function UpdateEquipOrigSoulProp();
final native function string FormatEquipOrigSoulProp();

final native function UpdateEquipSoulResultProp();
final native function string FormatEquipSoulResultProp();

final native function UpdateEquipSoulTotalProp();

final native function bool SetSoulEmbedEquip( int containerID, int slotID );
final native function bool SetSoulToEmbeInEquip( int containerID, int slotID, int targetSlotID );

final native function INT AutoSetSoulToEmbeInEquip( int containerID, int slotID );
final native function bool UnSetSoulEmbedEquip();
final native function bool UnSetSoulToEmbeInEquip( int targetSlotID );

final native function ConfirmSoulEmbed();
final native function OnNotifySoulEmbed( int result );

event CallASSoulEmbedSuccessAnim( int animiMask )
{
	ActionScriptVoid( "UCSetEmbedResult" );
}

event CallASSoulUnEmbedAnim( int result )
{
	ActionScriptVoid( "UCSetUnEmbedResult" );
}

//soul unembed
native function BagSlotChangeOnSoulUnEmbed( int bagId, int slotId );
native function bool OnRightMouseClickUnEmbed(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDropUnEmbed(GFxObject srcSlotMC, GFxObject destSlotMC, ESlotPanelType srcSlotType, ECONTAINER_SLOT srcContainerID, int SrcSlotID, ESlotPanelType destSlotType, ECONTAINER_SLOT destContainerID, int destSlotID);

final native function ResetSoulUnEmbed();

final native function InitSoulUnEmbedMc();
final native function UpdateSoulUnEmbed();

final native function bool SetSoulUnEmbedEquip( int containerID, int slotID );
final native function bool UnSetSoulUnEmbedEquip();

final native function UpdateUnEmbedSlot();
final native function UpdateToUnEmbedSoulPropData();
final native function bool UpdateSoulUnEmbedFee();
final native function UpdateSoulEmbedPropInUnEmbed();

final native function UpdateEquipOrigSoulPropInUnEmbed();
final native function UpdateEquipResultPropInUnEmbed();

final native function ConfirmSoulUnEmbed();
final native function OnNotifySoulUnEmbed( int result );
final native function SelectSoulToUnEmbed( int idx );

//soul level up
native function BagSlotChangeOnSoulLvUp( int bagId, int slotId );
native function bool OnRightMouseClickLvUp(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDropLvUp(GFxObject srcSlotMC, GFxObject destSlotMC, ESlotPanelType srcSlotType, ECONTAINER_SLOT srcContainerID, int SrcSlotID, ESlotPanelType destSlotType, ECONTAINER_SLOT destContainerID, int destSlotID);

final native function ResetSoulLevelUp();

final native function UpdateSoulLevelUp();
final native function UpdateSoulInfo();
final native function int UpdateSuccessRatio();

final native function bool SetLevelUpSoul( int containerID, int slotID );
final native function bool UnSetLevelUpSoul();

final native function int AutoSetLevelUpSoulSacrifice( int containerID, int slotID );
final native function bool SetLevelUpSoulSacrifice( int containerID, int slotID, int targetSlotID );
final native function bool UnSetLevelUpSoulSacrifice( int targetSlotID );
final native function int AutoUnSetPackedSoulScrifice( INT conID, INT slotID );

final native function bool SetLevelUpSoulSuccessHelp( int containerID, int slotID );
final native function bool UnSetLevelUpSoulSuccessHelp();

final native function ConfirmSoulLevelUp();
final native function OnNotifySoulLevelUpResult( int result );

final native function bool IsEnoughSoulsCanAddMoreScrifice( INT conID, INT slotID );
final native function bool IsInScrificeSoulSlot( INT conID, INT slotID );
final native function bool IsInLevelUpSoulSlot( INT conID, INT slotID );

//===============================================================================================================
//===============================================================================================================
//function RegisterSoulEmbed( MMOUISoulEmbed mc )
//{
//	_SoulEmbedPanel = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_SoulEmbed);
//}

//soul embed
final native function ASOnEmbedPanelTabBtnClick( int tabIdx );

final native function ASConfirmSoulEmbed();
final native function ASResetSoulEmbed();
//soul unembed
final native function ASConfirmUnEmbed();
final native function ASCancelUnEmbed();
final native function ASSelectUnEmbedSoul( int idx );
//soul level up
final native function ASConfirmSoulLevelUp();
final native function ASResetSoulLevelUp();
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=SoulEmbed
	MAX_EmbedSoul=3
	MAX_SacrificeSoul=5
}
