class MMOUINewStallMsgPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

var int _SrcBag;
var int _SrcSlot;
var int _Price;
var int _Count;
var int _MaxCount;
var int _StallSlot;
var float _Tax;

native function SetStallMsgPanelData(int stallSlot, int bag, int slot, int price, int count, int maxCount, int tax);
native function UpdatePanel();

//----------------moved---------------------
native function ASStallSettingMsgBoxYes(int stallSlot, int conSlot, int iSlot, int count, int price);
native function ASStallSettingMsgBoxNo();

event CallInitPanel(GFxObject data)
{
	ActionScriptVoid("InitPanel");
}