class MMOUIOptionQuit extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

var int _ReturnType;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event UCInitQuitTimer( string head, int length, string tail )
{
	ActionScriptVoid( "UCInitQuitTimer" );
}

native function ASOptionQuitImmed();


DefaultProperties
{
	IsDynamicLoad=true
}
