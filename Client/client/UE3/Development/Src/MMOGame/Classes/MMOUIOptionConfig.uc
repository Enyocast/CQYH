class MMOUIOptionConfig extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}
event UCFillToUI(GfxObject dat)
{
	ActionScriptVoid("UCFillToUI");
}
event UCVideoLevelReq(GfxObject dat)
{
	ActionScriptVoid("UCVideoLevelReq");
}
//event UCShowWarning(string warning)
//{
//	ActionScriptVoid("UCShowWarning");
//}
event CallUCSetOptionListData(GfxObject dat)
{
	ActionScriptVoid("UCVideoAdvanceLevelReq");
}
event UCSetCtrlType(int ctrlType)
{
	ActionScriptVoid("UCSetCtrlType");
}

//native function ShowKeyWarning(bool bShow);
native function NativeInitOnce();
native final function FillToUI();
native final function ApplyByUI(GFxObject dt);
native final function ASConfigVideoReq(int lv);
native final function ASTempApplyUI(GFxObject dt);
//native final function FillInputConfig(GFxObject dt, bool mdf_config,int nModfGCTType);
//native final function FillInputToUI(bool mdf_config,int nModfGCTType);



function ASApplyConfig(GFxObject dt)
{
	ApplyByUI(dt);
}

function ASConfigClose(GFxObject compt)
{
	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionConfig,false, "");

	//local MMOUIOptionConfig _OptionConfig;
	//_OptionConfig = MMOUIOptionConfig( class'MMOUIManager'.static.FindUIPanel(class'MMOUIManager'.default.Panel_OptionConfig) );
	//if(_OptionConfig!=none){
	//	_OptionConfig.SetVisible(false);
	//}
}

// function ASConfigVideoReq(int n)
// {
// 	ASConfigVideoReq(n);
// }

//function ASMdfFunction(int func)
//{
//    class'MMOKeyManager'.static.ASMdfFunction(func);
//}

//function ASDefaultInput(int input_config)
//{
//    class'MMOKeyManager'.static.ASDefaultInput(input_config);
//}

//function ASSetContralType(int ctrlType)
//{
//    class'MMOKeyManager'.static.ASSetContralType(ctrlType);
//}

// function ShowKeyWarning(bool bShow)
// {
// 	local MMOUIOptionConfig _OptionConfig;
// 	_OptionConfig = MMOUIOptionConfig( class'MMOUIManager'.static.FindUIPanel(class'MMOUIManager'.default.Panel_OptionConfig) );
// 	if(_OptionConfig!=none){
// 		_OptionConfig.ShowKeyWarning(bShow);
// 	}
// }

DefaultProperties
{
	IsDynamicLoad=true
}
