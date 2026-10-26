class MMOUIMallPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);


var array<GFxObject> mallGoodsList;
var array<GFxObject> mallHotList;
var GFxObject prePageBtn;
var GFxObject nextPageBtn;
var int  GoodsID;
var int  GoodsNum;

native function NativeInitLoad();
native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject SrcSlotMC, GFxObject DestSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, ESlotPanelType DestSlotType, ECONTAINER_SLOT DestContainerID, int DestSlotID);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}
event InitMallGoodsIcon()
{
	local int i;
	local GFxObject ItemSlotCtl;
	local GFxObject ItemSlot;
	local GFxObject PageBtn;
	
	local GFxObject mallGoodsPanel;
	mallGoodsPanel = GetObject("mallGoodsPanel_mc");
	
	if(mallGoodsPanel == none)
		return;
	
	for( i =0 ;i< 15 ;++i )
	{
		ItemSlotCtl = mallGoodsPanel.GetObject("goods"$i$"_mc");
		if(ItemSlotCtl != none)
			ItemSlot = ItemSlotCtl.GetObject("ItemIcon_mc");
		if(ItemSlot != none)
		{
			ItemSlot.SetFloat("itemid",i); 
			mallGoodsList.AddItem( ItemSlot );
		}
	}

	for( i =0 ;i< 5 ;++i )
	{
		ItemSlotCtl = GetObject("hotGoods"$i$"_mc");
		if(ItemSlotCtl != none)
			ItemSlot = ItemSlotCtl.GetObject("ItemIcon_mc");
		if(ItemSlot != none)
		{
			ItemSlot.SetFloat("itemid",i); 
			mallHotList.AddItem( ItemSlot );
		}
	}
	PageBtn = mallGoodsPanel.GetObject("pagectrl_mc");
	if(PageBtn != none)
	{
		prePageBtn = PageBtn.GetObject("btn_prev");
		nextPageBtn = PageBtn.GetObject("btn_next");
	}
}

event CallSetWindowTitle(string title)
{
	ActionScriptVoid("SetWindowTitle");
}
event CallUCSetMallTab(int nIndex)
{
	ActionScriptVoid("UCSetMallTab");
}


event CallUpdateGoodsList(GFxObject data)
{
	ActionScriptVoid("UCUpdateGoodsList");
}

event CallUpdateMoney(int nMoney)
{
	ActionScriptVoid("UCMallUpdateGoldMoney");
}

event CallUpdatePageNum(String nPage)
{
	ActionScriptVoid("UCUpdatePageNum");
}

event CallInitDropMenuList(int nIndex,GFxObject data)
{
	ActionScriptVoid("UCInitDropMenuList");
}

event CallUpdateMallHotList(GFxObject data)
{
	ActionScriptVoid("UCUpdateMallHotList");
}

event CallUCUpdateMallHomeShowData(GFxObject data)
{
	ActionScriptVoid("UCUpdateMallHomeShowData");
}

event CallUCUpdateNewNotice(GFxObject data)
{
	ActionScriptVoid("UCUpdateNewNotice");
}

event CallAddNewNotice(String str)
{
	ActionScriptVoid("AddNewNotice");
}

final native function ASClickDropMenuHotType(int nType);
final native function ASClickDropMenuAvaibleType(int nType);
final native function ASClickBtnBuyVip();
final native function ASClickBtnCheckIn();
final native function ASAddGoldMoney();
final native function ASClickMallTap(int nIndex);
final native function ASClickMallGoods(int nGoodsID);
final native function ASClickPrePage();
final native function ASClickNextPage();

DefaultProperties
{
	GoodsID = 0
	GoodsNum = 0
	IsDynamicLoad=true
	DefaultVisible=false
}