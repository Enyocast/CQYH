class MMOGFXPlayer_SceneHint extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUISceneHint          SceneHint;

function RegisterSceneHint( MMOUISceneHint mc )
{
	SceneHint = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_SceneHint);
}

event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	if(strHoverControllerName == "btn_Selected")
	{
		return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
	}
	return true;
	////`log( "strHoverControllerName : "$strHoverControllerName );
	////if( strHoverControllerName == "PlayerArraw_mc" || strHoverControllerName == "MapNpcView_mc" ){
	////	return false;
	////}

	//return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}

//native function PostAdvance(float DeltaTime );
//native function UpdateHintText(MMOActor pl);//xx
//native function UpdateHintPos(float DeltaTime);//xx
//native function ShowHintBtn(bool bShow);//xx

//native function ASRightClickTargetInfo(int x,int y,int serverID);//xx

DefaultProperties
{
	MovieInfoStr="UI_SceneHint.SceneHint"
	Priority=1
	bAllowInput=true
	bAllowFocus=false
}
