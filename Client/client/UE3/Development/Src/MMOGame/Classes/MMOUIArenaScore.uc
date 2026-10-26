class MMOUIArenaScore extends MMOUIBase
	native(UI);

event InitOnce()
{
	

	//class'MMOUIManager'.static.SetOpenArenaScoreSingleDelegate(OpenArenaScoreSingle);
	class'MMOUIManager'.static.SetCloseArenaScoreDelegate(CloseArenaScore);

	super.InitOnce();
}
native function NativeInitOnce();
//native function OpenArenaScoreSingle( int winID , int LoseID , int score );

native function CloseArenaScore(  );

event CallSetScoreData( GFxObject data )
{
	ActionScriptVoid("SetScoreData");
}
//native function SetMemberNumber( int num , bool winner );
//native function SetMemberInfo( bool winner , int index , int sex , String roleName , int classId , bool alive , int lv , int kill , int oriScore , int getScore );

DefaultProperties
{
	IsDynamicLoad=true
	//CloseOnEsc=false
}
