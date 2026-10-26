class MMOUIEquipEnhance extends MMOUIBaseSlotContainer
	native(UI)
	config(UIVisibleMask);

//
var GFxObject MakeEnhancePanel;
var GFxObject MakeEnhanceSuccessAnim_mc;
var GFxObject MakeEnhanceItem_mc;
var const int ENHANCE_MAT_ICON_MAX;//3
var GFxObject MakeEnhanceMatCsm_mc[3];
var GFxObject MakeEnhanceMnyCsm_tf;
var GFxObject MakeEnhanceMnyType_mc;
var GFxObject MakeEnhanceCurDgr_tf;
var GFxObject MakeEnhanceMaxDgr_tf;
//
var const int ENHANCE_PROP_MAX;//3
var GFxObject CurEnhanceProp_tf[3];
//var GFxObject CurEnhancePropValue_tf[3];
var GFxObject MakeEnhanceProp_tf[3];
//var GFxObject MakeEnhancePropValue_tf[3];
var GFxObject MakeEnhance_btn;
//
var GFxObject TransEnhancePanel;
var GFxObject TransEnhanceFromItem_mc;
var GFxObject TransEnhanceToItem_mc;
var GFxObject TransEnhanceMnyCsm_tf;
var GFxObject TransEnhanceCurDgr_tf;
var GFxObject TransEnhance_btn;

//当前强化（转移强化）插槽中的物品所在包裹中的位置(-1为空)
var int CurWorkingItemBagID;
var int CurWorkingItemContainID;
//当前需转移强化至物品插槽中，该物品所在包裹中的位置(-1为空)
var int CurTransEnhanceToItemBagID;
var int CurTransEnhanceToItemContainID;

//条件是否满足，可以开始强化（取消强化）
var bool IsMatOK;
var bool IsMnyOK;
var bool IsDegreeOK;
var bool IsTransToItemOK;

enum enumEquipEnhanceMode
{
	EEQPEHC_MakeEnhance,
	EEQPEHC_TransEnhance
};

enum enumEquipSlotID
{
	EEHCSLT_MakeEnhanceSlot,
	EEHCSLT_TransEnhanceSlot,
	EEHCSLT_TransTargetSlot
};

var enumEquipEnhanceMode EnumCurEnhanceMode;

//监控事件，以实时更新条件
native function BagSlotChange( INT BagId,INT SlotId );
native function PlayerMoneyChange(EMONEY_TYPE MoneyType, int DeltaMoney);
//
native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject SrcSlotMC, GFxObject DestSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, ESlotPanelType DestSlotType, ECONTAINER_SLOT DestContainerID, int DestSlotID);
event OnSubscribeItemSlotAction()
{
}

event OnUnSubscribeItemSlotAction()
{
}

native function Equip GetBagEquip( int bagSlotCon, int bagSlotID );
//检查是否为可以强化（取消强化）
native function bool CheckCanGo();
//检查是否为此界面正在使用的物品
native function bool CheckInUse( int ItemInBagID );
//通过取回已经设置的UI值来判定是否所有材料齐全，避免每次都轮询背包所有材料格
native function ReChkMatCondtionByUI();
//检查是否可做转移
native function bool CheckCanTransEnhance( int bagSlotCon, int bagSlotIdx );

//放入强化（取消强化）的装备
native function SetWorkingSlotData( int bagSlotCon, int bagSlotID, Item slotItem );
native function SetTransSlotTarget(  int bagSlotCon, int bagSlotID, Item slotItem);
native function int CurBagIdxOfTargetEquip();
native function int CurBagIdxOfTransTargetEquip();
native function int CurContainOfTargetEquip();
native function int CurContainOfTransTargetEquip();
//更新
native function UpdatePanel();
//
native function UpdateMakeEnhanceInfo();
//
native function UpdateTransEnhanceInfo();
//更新所需耗材信息
native function UpdateMaterialConsume();
//更新某个耗材数量
native function int UpdateMaterialCnt( GFxObject TfCurHave, GFxObject TfCnt, int itemID, int MatCsmNeed );
//更新（转移）强化金钱耗费
native function UpdateFee();
//更新（转移）强化物品当前强化等级，最大强化等级，强化属性
native function UpdateEquipInfo();

//

//清空解锁放入的装备
native function ResetEnhanceItems();
//AS调用，用于回复默认界面
native function ShowDefaultContent( int mode);
//
native function ResetUIMode();
//清空界面内容
native function ResetPanelInfo();
//
native function ResetMakeEnhanceInfo();
//
native function ResetTransEnhanceInfo();
//清空耗材slot
native function ResetMaterialConsume( int startIdx );
//回复到默认标签页,通知Flash
event ChangeContentTabBtn( int tabIdx )
{
	ActionScriptVoid( "UCShowContent" );
}
//
native function ResetCondition();
//检查状态，设置界面按钮提示等
native function CheckOperation();

//操作响应
native function MakeEnhanceItem();
native function NotifyMakeEnhanceItemResult( bool isSucceed );
//
native function TransferEnhanceItem();
//控制操作可行性
native function SetOkBtn();

//===============================================================================================================
//===============================================================================================================
function ASHideEquipEnhance()
{
	NativeShow( false );
}

//
function ASMakeEnhanceItem()
{
	MakeEnhanceItem();
}

//
function ASTransferEnhanceItem()
{
	TransferEnhanceItem();
}

//
function ASUpdateEquipEnhancePanel( int iTab )
{
	ShowDefaultContent( iTab );
}
//===============================================================================================================
//===============================================================================================================

defaultproperties
{
	//FriendlyName=EquipEnhance
	IsDynamicLoad=true
	ENHANCE_MAT_ICON_MAX=3
	ENHANCE_PROP_MAX=3
	IsMatOK=false
	IsMnyOK=false
	IsDegreeOK=false
	IsTransToItemOK=true
	IsTargetOutDistanceClose = true
}
////
//event bool CheckAuxlMatOK( int itemSlotID )
//{
//	local Item auxiliaryItem;
//	//auxiliaryItem = Player.ItemManager.BagMaterialList[SrcSlotID];
//	auxiliaryItem = Player.ItemManager.BagItemList[itemSlotID];
//	if( auxiliaryItem == none ){
//		return false;
//	}
//	//
//	if( UnEnhcAxulMat[0] == auxiliaryItem.ItemId ){
//		return true;
//	}
//	if( UnEnhcAxulMat[1] == auxiliaryItem.ItemId ){
//		return true;
//	}
//	return false;
//}