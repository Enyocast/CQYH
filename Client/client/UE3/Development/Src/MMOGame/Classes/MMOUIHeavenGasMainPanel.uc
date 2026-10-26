class MMOUIHeavenGasMainPanel extends GFxObject
	native(UI)
	config(UIVisibleMask);

const GasEquipSlotMaxNum = 9;
const GasBagSlotMaxNum = 32;
const GasBankSlotMaxNum = 16;

var array<GFxObject> EquipGasItemSlotList;
var array<GFxObject> BagGasItemSlotList;
var array<GFxObject> BankGasItemSlotList;
var GFxObject        GasTargetSlot;

var GFxObject	HeavenMergeConfirmBox;
var GFxObject	HeavenMergePurpleConfirmBox;

native function ConfirmHeavenMerge(GFxObject mc);
native function CancelHeavenMerge(GFxObject mc);
native function ConfirmHeavenMergePurpleGas(GFxObject mc);
native function CancelHeavenMergePurpleGas(GFxObject mc);

native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject SrcSlotMC, GFxObject DestSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, ESlotPanelType DestSlotType, ECONTAINER_SLOT DestContainerID, int DestSlotID);

native function GasItemDelete(int ContainerID, int SlotID);
native function LockGasItem(int nContainerID , int SlotID);

native function NativeOnShow(bool v);

native function ExpandGasBagOk( GFxObject mc );
native function ExpandGasBankOk( GFxObject mc );
native function ExpandGasEquipOk( GFxObject mc );

event UpdateSetGasIconState(int nContainerID, int nSlotID,bool bShow,int nIconType,int nLevel,string icon0,string icon1)
{
	ActionScriptVoid("UCSetGasIconState");
}

event UpdateSetSelectedIconTarget(int nContainerID, int nSlotID)
{
	ActionScriptVoid("UCSetSelectedIconTarget");
}

event PlayAnimationGas(int nType,int nContainerID, int nSlotID)
{
	ActionScriptVoid("UCPlayAnimationGas");
}
event UpdateEquipGasPower(int nPower)
{
	ActionScriptVoid("UCUpdateEquipGasPower");
}
event UpdateEquipGasSlot(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateEquipGasSlot");
}
event UpdateEquipGasSingleSlot(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateEquipGasSingleSlot");
}

event InitHeavenGasMain()
{
	local int i;
	local GFxObject ItemSlot;

	for( i =0 ;i< GasEquipSlotMaxNum ;++i )
	{
		ItemSlot = GetObject("GasEquip"$i$"");
		if(ItemSlot != none)
		{
			ItemSlot.SetFloat("itemid",i); 
			EquipGasItemSlotList.AddItem( ItemSlot );
		}
	}
	for( i =0 ;i< GasBagSlotMaxNum ;++i )
	{
		ItemSlot = GetObject("GasBagIndex"$i$"");
		if(ItemSlot != none)
		{
			ItemSlot.SetFloat("itemid",i); 
			BagGasItemSlotList.AddItem( ItemSlot );
		}
	}
	for( i =0 ;i< GasBankSlotMaxNum ;++i )
	{
		ItemSlot = GetObject("GasBankIndex"$i$"");
		if(ItemSlot != none)
		{
			ItemSlot.SetFloat("itemid",i); 
			BankGasItemSlotList.AddItem( ItemSlot );
		}
	}
	GasTargetSlot =  GetObject("GasBagTarget");
}
