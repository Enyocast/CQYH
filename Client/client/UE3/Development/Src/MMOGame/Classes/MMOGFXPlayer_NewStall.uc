class MMOGFXPlayer_NewStall extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUINewStallSettingPanel StallSettingPanel;
var MMOUINewStallBuyPanel StallBuyPanel;
var MMOUINewStallMsgPanel StallMsgPanel;

function RegisterStallSetting(MMOUINewStallSettingPanel mc)
{
	//StallSettingPanel = mc;
	//RegisterUI( mc, class'MMOUIManager'.default.Panel_Stall_StallSetting );
}

function RegisterStallBuy(MMOUINewStallBuyPanel mc)
{
	//StallBuyPanel = mc;
	//RegisterUI( mc, class'MMOUIManager'.default.Panel_Stall_StallBuy );
}

function RegisterStallMsgBox(MMOUINewStallMsgPanel mc)
{
	//StallMsgPanel = mc;
	//RegisterUI( mc, class'MMOUIManager'.default.Panel_Stall_StallMsg );
}

native function RequireOpenStall();//moved

native function ASStallSettingSetYes(int stallSlot, int conSlot, int itemSlot, int count, int price);//moved
native function ASStallBuySetYes(int stallSlot, int count);//moved
native function ASStallMsgBoxSetNo();//moved

native function ASStallStart(string inStallName, string inStallAd);//moved
native function ASCloaseStall();//moved
native function ASStallSetNPC();//moved
native function ASOnCloseStallSetting();//moved
native function ASOnPanelClose(string PanelName);//moved

native function CloseStall();//moved

DefaultProperties
{
	MovieInfoStr="UI_StallWidget.StallWidget"
	bCloseOnLevelChange=FALSE
	Priority=5
}
