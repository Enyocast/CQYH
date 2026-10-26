class MMOUIVSState extends MMOUIBase
	native(UI);

//
final native function UpdatePanel();

//
event CallAsSetRoundTime( int milliSec )
{
	ActionScriptVoid( "UCSetRoundTime" );
}
//
event CallAsSetVSSideInfo( GFxObject datas )
{
	ActionScriptVoid( "UCSetVSSideInfo" );
}
event CallAsSetVSSideName( int sideIdx, string sideName )
{
	ActionScriptVoid( "UCSetVSSideName" );
}

DefaultProperties
{
	CloseOnEsc=false
}
