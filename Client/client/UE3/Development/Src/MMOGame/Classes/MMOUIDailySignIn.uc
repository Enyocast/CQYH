class MMOUIDailySignIn extends MMOUIBase
	native(UI)
	dependson(TypeDefine)
	config(UIVisibleMask);


//
event CallAsSetCurrentSignedIn( string curSignedIn )
{
	ActionScriptVoid( "UCSetCurrentSignedIn" );
}
//===============================================================================================================
//===============================================================================================================
native function ASTryGetSignReward( int signInIdx );
//===============================================================================================================
//===============================================================================================================
event CallAsSetRewardDatas( GFxObject itemsData )
{
	ActionScriptVoid( "UCSetRewardDatas" );
}
event CallAsSetCurSignInDay( int dayIdx )
{
	ActionScriptVoid( "UCSetCurSignInDay" );
}
event CallAsInitSignInRewardSlot( int slotType )
{
	ActionScriptVoid( "UCInitSignInRewardSlot" );
}
event CallAsSetSignInRequires( string requires )
{
	ActionScriptVoid( "UCSetSignInRequires" );
}


DefaultProperties
{
	//FriendlyName=Vip
	IsDynamicLoad=true
	CloseOnEsc=true
}
