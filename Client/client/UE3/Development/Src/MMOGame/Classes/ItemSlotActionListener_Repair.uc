//
// ItemSlotActionListener_Repair
//
class ItemSlotActionListener_Repair extends Object implements(IItemSlotActionListener)
	dependson(TypeDefine)
	native(UI);

//var IItemSlotActionListener LastItemActionListener;

native function int  GetSlotType();
native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject SrcSlotMC, GFxObject DestSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, ESlotPanelType DestSlotType, ECONTAINER_SLOT DestContainerID, int DestSlotID);
native function bool OnDoubleClickSlot(GFxObject SrcSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, bool bDefault);

native function NativeOnSubscribeItemSlotAction();
native function NativeOnUnSubscribeItemSlotAction();

native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);

event OnSubscribeItemSlotAction()
{
	//LastItemActionListener = class'MMOUIManager'.static.GetCurrentItemSlotActionListener();
	NativeOnSubscribeItemSlotAction();
}

event OnUnSubscribeItemSlotAction()
{
	NativeOnUnSubscribeItemSlotAction();
}

