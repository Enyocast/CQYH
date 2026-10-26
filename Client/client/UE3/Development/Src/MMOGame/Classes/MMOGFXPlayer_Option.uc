class MMOGFXPlayer_Option extends MMOGFXPlayer
	dependson(MMOUIBase)
	native(UI)
	config(MMOGame);


//var MMOUIOptionMenu     _OptionMenu;
//var MMOUIOptionConfig   _OptionConfig;
//var MMOUIOptionQuit     _OptionQuit;
var int _ReturnType;


function ASRegisterOptionMenu(MMOUIOptionMenu mc)
{
	//_OptionMenu = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_OptionMenu);
}
function ASRegisterOptionConfig(MMOUIOptionConfig mc)
{
	//_OptionConfig = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_OptionConfig);
}
function ASRegisterOptionQuit(MMOUIOptionQuit mc)
{
    //_OptionQuit = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_OptionQuit);
}


// function ASOptionConfig()
// {
// 	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");
//     class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionConfig,true, "");
//     //_OptionMenu.SetVisible(false);
// }
// function ASReturnSelect()
// {
// 	//NativeReturnSelect();
// 	//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionQuit,true, "");
//    	//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");
// 
//     class'MMOUIManager'.static.SendReturnSelRole();
//    	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");
// 
// }
// 
// native function NativeReturnLogin();
// function ASReturnLogin()
// {
// 	_ReturnType =1;
// 	NativeReturnLogin();
//    	//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");
// 
// 	//class'MMOUIManager'.static.SendReturnLogin();
//    	//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");
// }
// native function ASShowMapLineListToChange();
// native function ASChangeSceneLine( int maplineCombinedID );
// 
// function ASReqExitGame()
// {
// 	_ReturnType = 0;
// 	//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_ActivityQuit,true, "");
// 	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");
// 
// 	class'MMOUIManager'.static.SendQuitGame();
// 
//     //_OptionMenu.SetVisible(false);
// }
// 
// function ASApplyConfig(GFxObject dt)
// {
// 	local MMOUIOptionConfig _OptionConfig;
// 	_OptionConfig = MMOUIOptionConfig( class'MMOUIManager'.static.FindUIPanel(class'MMOUIManager'.default.Panel_OptionConfig) );
// 	if(_OptionConfig!=none){
// 		_OptionConfig.ApplyByUI(dt);
// 	}
// }
// function ASConfigClose(GFxObject compt)
// {
// 	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionConfig,false, "");
// 
// 	//local MMOUIOptionConfig _OptionConfig;
// 	//_OptionConfig = MMOUIOptionConfig( class'MMOUIManager'.static.FindUIPanel(class'MMOUIManager'.default.Panel_OptionConfig) );
// 	//if(_OptionConfig!=none){
// 	//	_OptionConfig.SetVisible(false);
// 	//}
// }
// function ASConfigVideoReq(int n)
// {
// 	local MMOUIOptionConfig _OptionConfig;
// 	_OptionConfig = MMOUIOptionConfig( class'MMOUIManager'.static.FindUIPanel(class'MMOUIManager'.default.Panel_OptionConfig) );
// 	if(_OptionConfig!=none){
// 		_OptionConfig.ASConfigVideoReq(n);
// 	}
// }

// native function ASOptionQuitImmed();
//{
//	if(_ReturnType==1)
//	{
//		class'MMOUIManager'.static.ImmReturnLogin();//SendReturnLogin();
//   		//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");
//	}
//	else{
//	    class'MMOUIManager'.static.ImmQuitGame();
//	}
//}

// function ASMdfFunction(int func)
// {
//     class'MMOKeyManager'.static.ASMdfFunction(func);
// }
// 
// function ASDefaultInput(int input_config)
// {
//     class'MMOKeyManager'.static.ASDefaultInput(input_config);
// }
// 
// function ASSetContralType(int ctrlType)
// {
//     class'MMOKeyManager'.static.ASSetContralType(ctrlType);
// }

// function ShowKeyWarning(bool bShow)
// {
// 	local MMOUIOptionConfig _OptionConfig;
// 	_OptionConfig = MMOUIOptionConfig( class'MMOUIManager'.static.FindUIPanel(class'MMOUIManager'.default.Panel_OptionConfig) );
// 	if(_OptionConfig!=none){
// 		_OptionConfig.ShowKeyWarning(bShow);
// 	}
// }


// native final function ASExitDuplicate();
// native final function ASShowTips_Option(GFxObject mc,string strName);
// native final function ASHideTips_Option(GFxObject mc);

DefaultProperties
{
	MovieInfoStr="UI_OptionWidget.OptionWidget"
	bCloseOnLevelChange=FALSE
	Priority=7
	_ReturnType=0
}