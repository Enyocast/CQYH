class MMOUIEquipDecomposePanel extends MMOUIBaseSlotContainer
	native(UI)
	config(UIVisibleMask);

native function NativeInitOnce();
native function UpdateResultUI();
native function ClearUI();

event CallResetTimer()
{
	ActionScriptVoid("ResetTimer");
}

native  function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native  function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native  function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native  function bool OnDragDrop(GFxObject SrcSlotMC, GFxObject DestSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, ESlotPanelType DestSlotType, ECONTAINER_SLOT DestContainerID, int DestSlotID);

//===============================================================================================================
//===============================================================================================================
native function ASDecomposeOk();
native function ASDecomposeCancel();
//===============================================================================================================
//===============================================================================================================

defaultproperties
{
	//FriendlyName=EquipDecompose
}