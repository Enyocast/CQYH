class MMOUIFBTask extends MMOUIBase
	native(UI);

//
var GFxObject FBTitleTf;
var GFxObject FBTaskScrollListMc;

var int PanelWidth;
var int PanelHeight;

native function UpdateFBTaskList( int fbMainTargetIdx );
event UCFlashFBTaskList( GFxObject Provider )
{
	ActionScriptVoid( "UpdateFBTaskScrollList" );
}

//===============================================================================================================
//===============================================================================================================
native function bool SkipCaptureInputKey( string key, EInputEvent eIE, string strHoverControllerName, Vector2D ClickPosInMovieSpace);
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=FBTask
	CloseOnEsc=false
	IsDynamicLoad=true
}
