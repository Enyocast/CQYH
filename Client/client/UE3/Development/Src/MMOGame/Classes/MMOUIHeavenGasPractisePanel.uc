class MMOUIHeavenGasPractisePanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

event CallUpdatePractisePhrase(int nIndex,int nShowState)
{
	ActionScriptVoid("UCSetCurPractiseBtnState");
}

event CallSetXiuLianValue(int data)
{
	ActionScriptVoid( "UCSetXiuLianValue");
}

event CallSetWindowTitle(string title)
{
	ActionScriptVoid("SetWindowTitle");
}

event CallUCUpdateGasMoney(int nGasMoney)
{
	ActionScriptVoid("UCUpdateGasMoney");
}
event CallUCPlayPractiseAnimation(int nGasMoney)
{
	ActionScriptVoid("UCPlayPractiseAnimation");
}

final native function UpdateHeavenGasPractisePanel();
native function PlayerMoneyChange(EMONEY_TYPE MoneyType, int DeltaMoney);

//===============================================================================================================
//===============================================================================================================
final native function ASClickBtnPractiseGas(int nBtnIndex);
final native function ASClickOneKeyPractise();
final native function ASClickOpenExchangePanel();

//final native function ASClickOpenGasPractisePanel();
//final native function ASClickOneKeyMergeGas();
//final native function ASShowTips_HeavenGasSlot(GFxObject mc);
//final native function ASHideTips_HeavenGasSlot();
//final native function ASShowTips_HeavenGasPower(GFxObject mc);
//final native function ASHideTips_HeavenGasPower();
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{	
	IsDynamicLoad=true
}
