class MMOUIQuestItemCollectionPanel extends MMOUIBaseSlotContainer
	dependson(Quest)
	native(UI)
	config(UIVisibleMask);

var GFxObject _ItemSlot;
var OperationItemBagPos _ItemBagPos;
var int _ItemTempId;

native function ItemChange(int ContainerID, int SlotID);
native function ItemDelete(int ContainerID, int SlotID);

native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject srcSlotMC, GFxObject destSlotMC, ESlotPanelType srcSlotType, ECONTAINER_SLOT srcContainerID, int SrcSlotID, ESlotPanelType destSlotType, ECONTAINER_SLOT destContainerID, int destSlotID);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event CallSetWindowTitle(string title)
{
	ActionScriptVoid("UCSetWindowTitle");
}

event CallUpdateQuestData(GFxObject questData)
{
	ActionScriptVoid("UCUpdateQuestData");
}

event CallUpdateItemData(GFxObject itemData)
{
	ActionScriptVoid("UCUpdateItemData");
}

native final function ASSubmitItem(int questId, int itemId, int itemIndex);

DefaultProperties
{	
	IsDynamicLoad=true
}
