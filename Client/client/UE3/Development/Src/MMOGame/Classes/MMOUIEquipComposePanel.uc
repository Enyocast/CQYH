class MMOUIEquipComposePanel extends MMOUIBaseSlotContainer
	native(UI)
	config(UIVisibleMask);

native function ClearUI();

native function UpdateUI(int itemId);

native function BagSlotChange( int bagId, int slotId );
native function PlayerMoneyChange( EMONEY_TYPE MoneyType, int DeltaMoney);

native  function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native  function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native  function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native  function bool OnDragDrop(GFxObject SrcSlotMC, GFxObject DestSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, ESlotPanelType DestSlotType, ECONTAINER_SLOT DestContainerID, int DestSlotID);

event CallAStoSetItemName( String itemName )
{
	ActionScriptVoid( "UCSetItemName" );
}

event CallASPlayResultAnim( int animRst )
{
	ActionScriptVoid( "UCPlayResultAnim" );
}

//===============================================================================================================
//===============================================================================================================
native function ASCompose();
native function ASNotifyComposeSuccessAnimPlayedOver();
//===============================================================================================================
//===============================================================================================================

defaultproperties
{
	//FriendlyName=EquipCompose
}