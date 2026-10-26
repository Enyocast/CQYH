class MMOUIMallBuyPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

var GFxObject goodsIcon;
var GFxObject textNum;
var GFxObject giveBtn;
var GFxObject buyBtn;

var GFxObject	MallBuyConfirmBox;
var localized string friendName;

native function NativeInitLoad();
native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject SrcSlotMC, GFxObject DestSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, ESlotPanelType DestSlotType, ECONTAINER_SLOT DestContainerID, int DestSlotID);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event InitBuyGoodsIcon()
{
	local GFxObject NumCtl;
	goodsIcon = GetObject("buyGoodsIcon_mc");
	if(goodsIcon != none)
	{
		goodsIcon.SetFloat("itemid",0); 
	}
	NumCtl = GetObject("numInput_mc");
	if(NumCtl != none)
	{
		textNum = NumCtl.GetObject("textField");
	}
	giveBtn = GetObject("btnGiveFriend_mc");
	buyBtn = GetObject("buyGoods_mc");
}

event CallUpdateGoodsData(GFxObject data)
{
	ActionScriptVoid("UCUpdateGoodsData");
}

event CallUpdateGoldMoney(int nMoney)
{
	ActionScriptVoid("UCUpdateGoldMoney");
}

event CallSetBuyAimPlayerName(String playerName)
{
	ActionScriptVoid("UCSetBuyAimPlayerName");
}

final native function ASClickGiveFriend(int nGoodsID, int nNum);
final native function ASClickBuyGoods(int nGoodsID, int nNum);

native function ConfirmMallBuy(GFxObject mc);
native function CancelMallBuy(GFxObject mc);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}