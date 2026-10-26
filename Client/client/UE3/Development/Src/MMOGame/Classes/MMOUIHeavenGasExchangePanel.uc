class MMOUIHeavenGasExchangePanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

event CallUpdateHeavenGasItemList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateHeavenGasItemList");
}

event CallSetWindowTitle(string title)
{
	ActionScriptVoid("SetWindowTitle");
}

//===============================================================================================================
//===============================================================================================================
final native function ASClickExchangeGasItem(int nGasID);
//===============================================================================================================
//===============================================================================================================
DefaultProperties
{	
	IsDynamicLoad=true
}
