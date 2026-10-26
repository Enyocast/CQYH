class MMOUIHintSceneWidget extends MMOUIBase
	native(UI);

final native function ShowHintSceneMessage( string text, int textSize );
final native function Close();

//===============================================================================================================
//===============================================================================================================
native function bool SkipCaptureInputKey( string key, EInputEvent eIE, string strHoverControllerName, Vector2D ClickPosInMovieSpace);

final native function ShowHintSceneWidget();
final native function CloseHintSceneWidget();
//===============================================================================================================
//===============================================================================================================



DefaultProperties
{
	//FriendlyName=Scene
	CloseOnEsc=false
}
