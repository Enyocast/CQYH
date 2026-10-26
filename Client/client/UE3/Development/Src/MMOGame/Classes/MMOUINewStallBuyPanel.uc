class MMOUINewStallBuyPanel extends MMOUIBaseSlotContainer
	native(UI)
	config(UIVisibleMask);

var int _CurSlotId;
var GFxObject _ConfirmBuyBox;
var GFxObject _ConfirmBuyExerciseBox;

native final function UpdateSlot(int stallSlot, int itemId, int count, int price);
native function BuyItem(int stallSlot);
native function BuyItemReal(int stallSlot);

native  function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native  function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native  function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native  function bool OnDragDrop(GFxObject SrcSlotMC, GFxObject DestSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, ESlotPanelType DestSlotType, ECONTAINER_SLOT DestContainerID, int DestSlotID);

native function InitUI();
native function ClearUI();

native function ConfirmBuyItem(int stallSlot, int count);
native function AgreeBuyNow(GFxObject mc);
native function RefuseBuyNow(GFxObject mc);

native function ConfirmBuyExercise(int stallSlot);
native function AgreeBuyExercise(GFxObject mc);
native function RefuseBuyExercise(GFxObject mc);

event UpdateStallBuyWidget(GFxObject obj)
{
	ActionScriptVoid("UpdateStallBuyWidget");
}

event UpdateStallInfo(string stallName, int ownerId)
{
	ActionScriptVoid("UCSetOwnerData");
}

event UpdateFollowState(bool follow)
{
	ActionScriptVoid("UCSetButtonState");
}

event CheckSettingItem(int slot)
{
	ActionScriptVoid("UCCheckSettingItem");
}

native function ASOnCallOwner(int ownerId);
native function ASOnFollowOwner(int ownerId);
native function ASCancelFollowOwner(int ownerId);
native function ASOnBuyItem();

DefaultProperties
{
	_CurSlotId=-1
}