//
// ItemSlotActionListener_SpecRepair
//
class ItemSlotActionListener_SpecRepair extends ItemSlotActionListener_Repair
	dependson(ItemSlotActionListener_Repair, TypeDefine)
	native(UI);

//var IItemSlotActionListener LastItemActionListener;

native function int  GetSlotType();
//native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function NativeOnSubscribeItemSlotAction();
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function NativeOnUnSubscribeItemSlotAction();