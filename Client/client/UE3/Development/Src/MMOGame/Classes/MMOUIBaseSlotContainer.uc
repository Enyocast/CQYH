class MMOUIBaseSlotContainer extends MMOUIBase implements(IItemSlotActionListener)
	dependson(TypeDefine)
	native(UI);

var IItemSlotActionListener LastItemActionListener;

native function ClearUI();


// event OnShow(bool show)
// {
// 	OnShowNative(show);
//  	//if(show)
//  	//{
// 		//LastItemActionListener = class'MMOUIManager'.static.GetCurrentItemSlotActionListener();
//  	//	class'MMOUIManager'.static.SetCurrentItemSlotActionListener(self);	
//  	//}
//  	//else
//  	//{
//  	//	class'MMOUIManager'.static.SetCurrentItemSlotActionListener(LastItemActionListener);
//  	//}
// }

native function OnFocusGained();
native function OnFocusLost();
// native function OnShowNative(bool show);
native function int  GetSlotType();
native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject SrcSlotMC, GFxObject DestSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, ESlotPanelType DestSlotType, ECONTAINER_SLOT DestContainerID, int DestSlotID);

native function bool OnDoubleClickSlot(GFxObject SrcSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, bool bDefault);

event OnSubscribeItemSlotAction()
{
}

event OnUnSubscribeItemSlotAction()
{
}


DefaultProperties
{

}
