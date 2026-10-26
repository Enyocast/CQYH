class MMOUISoulLevelUp extends MMOUIBaseSlotContainer
	native(UI)
	dependson(TypeDefine)
	dependson(MMOUISoulEmbed)
	config(UIVisibleMask);

//struct native LevelUpSoulBagPos
//{
//	var int _ConID;
//	var int _SlotID;
//	var bool _IsValid;
//};

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
var GFxObject _ResetBtn;

//
native function NativeInitLoad();
native function ClearUI();
native function BagSlotChange( int bagId, int slotId );
//native function OnItemDeleted( int containerID, int slotID );
native function PlayerMoneyChange( EMONEY_TYPE MoneyType, int DeltaMoney);
//
native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject srcSlotMC, GFxObject destSlotMC, ESlotPanelType srcSlotType, ECONTAINER_SLOT srcContainerID, int SrcSlotID, ESlotPanelType destSlotType, ECONTAINER_SLOT destContainerID, int destSlotID);

//
final native function ResetUI();

//soul level up
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
//var MMOUISoulLevelUp _SoulLevelUpPanel;
////
//function RegisterSoulLevelUp( MMOUISoulLevelUp mc )
//{
//	_SoulLevelUpPanel = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_SoulLevelUp);
//}


//soul level up
final native function ASConfirmSoulLevelUp();
final native function ASResetSoulLevelUp();

//===============================================================================================================
//===============================================================================================================
DefaultProperties
{
	//FriendlyName=SoulLevelUp
	MAX_SacrificeSoul=5
}
