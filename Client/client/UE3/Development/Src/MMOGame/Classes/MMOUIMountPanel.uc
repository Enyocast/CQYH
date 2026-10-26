class MMOUIMountPanel extends MMOUIBaseSlotContainer
native(UI)
config(UIVisibleMask);


var int  SelectMountID;

native function UpdateEquipedMount();
native function UpdateMount();

native function int GetSlotType();


native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject SrcSlotMC, GFxObject DestSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, ESlotPanelType DestSlotType, ECONTAINER_SLOT DestContainerID, int DestSlotID);


event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}



event InitOnce()
{
	super.InitOnce();

}

event CallUpdateMount(GFxObject MountArray)
{
	ActionScriptVoid("UpdateMount");
}

event CallSelectMount(int nSlotID)
{
	ActionScriptVoid("SelectMount");
}

event CallSetEquipedMount(int nSlotID)
{
	ActionScriptVoid("SetEquipedMount");
}

function RefreshMount()
{
	UpdateMount();
}

function RefreshEquipedMount()
{
	UpdateEquipedMount();
}

native function ASUnEquipMount();
native function ASEquipMount(int MountID);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=true
	SelectMountID=-1
}
