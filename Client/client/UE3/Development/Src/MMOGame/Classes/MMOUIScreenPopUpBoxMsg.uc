class MMOUIScreenPopUpBoxMsg extends MMOUIBase
	dependson(TypeDefine)
	native(UI);

//播放获得技能提示
native function PlayScreenPopUpBoxMsg( int msgId , EScreenMsgType type );
native function PlayScreenPopUpBoxMsgByString( EScreenMsgType type, String title, String content, String iconPath, String extraString );

//获得技能提示播放完毕通知 
native function MsgPlayEnd();

//===============================================================================================================
//===============================================================================================================
native function ASScreenPopUpBoxMsgPlayEnd();
//===============================================================================================================
//===============================================================================================================
native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);


DefaultProperties
{
	//FriendlyName=ScreenPopUpBoxMsg
}
