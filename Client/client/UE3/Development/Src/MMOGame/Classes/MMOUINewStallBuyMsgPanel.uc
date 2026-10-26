class MMOUINewStallBuyMsgPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

var int _SrcBag;
var int _SrcSlot;
var int _Price;
var int _Count;
var int _MaxCount;
var int _StallSlot;

var GFxObject _ConfirmBuyBox;

native function SetStallBuyMsgPanelData(int stallSlot, int bag, int slot, int price, int count, int maxCount);
native function UpdatePanel();

native function ConfirmBuyItem(int stallSlot, int count);
native function AgreeBuyNow(GFxObject mc);
native function RefuseBuyNow(GFxObject mc);

//----------------moved---------------------
native function ASStallBuyYes(int stallSlot, int count);
native function ASStallBuyNo();

event CallInitPanel(GFxObject data)
{
	ActionScriptVoid("InitPanel");
}