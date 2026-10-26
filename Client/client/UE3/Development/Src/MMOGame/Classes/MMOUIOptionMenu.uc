class MMOUIOptionMenu extends MMOUIBase
	native(UI)
	config(UIVisibleMask);


var GFxObject ConfirmMsgBox;
var int _ReturnType;


event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event UCShowExitDuplicateButton( bool isShow, string btnStr )
{
	ActionScriptVoid( "UCShowExitDuplicateButton" );
}

native function ShowMapLineList();
event UCUpdateLine( string mapName, GFxObject lineData )
{
	ActionScriptVoid( "UCUpdateLine" );
}

native function NativeInitOnce();
native function ReqExitDuplicate(EENUM_SCENE_VA type);
native function ReqExitDuplicate_Ok(GFxObject mc);
native function ReqExitDuplicate_Cancel(GFxObject mc);

function ASOptionConfig()
{
	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");
    class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionConfig,true, "");
    //_OptionMenu.SetVisible(false);
}

function ASReturnSelect()
{
	//NativeReturnSelect();
	//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionQuit,true, "");
   	//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");

    class'MMOUIManager'.static.SendReturnSelRole();
   	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");

}

native function NativeReturnLogin();
function ASReturnLogin()
{
	_ReturnType =1;
	NativeReturnLogin();
   	//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");

	//class'MMOUIManager'.static.SendReturnLogin();
   	//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");
}

native function ASShowMapLineListToChange();
native function ASChangeSceneLineByOptionMenu( int maplineCombinedID );


function ASReqExitGame()
{
	_ReturnType = 0;
//	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_ActivityQuit,true, "");
	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_OptionMenu,false, "");

	class'MMOUIManager'.static.SendQuitGame();

    //_OptionMenu.SetVisible(false);
}

native final function ASExitDuplicate();
native final function ASShowTips_Option(GFxObject mc,string strName);
native final function ASHideTips_Option(GFxObject mc);
native final function ASOpenAssist();


DefaultProperties
{
	IsDynamicLoad=true
}
