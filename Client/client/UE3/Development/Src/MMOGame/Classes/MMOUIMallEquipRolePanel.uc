class MMOUIMallEquipRolePanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

var transient LevelStreamingUIShow	ShowLevel;
var transient MMOPlayer ShowPlayer;
var transient GFxObject takeBtn;
var bool bEquipIng;
var TurnButtonStats TurnButton;

native function NativeInitLoad();

native function ModelEquip();
native function SysModelEquip();
native function CreateShowLevel();
native function EnableCapture(BOOL b);
native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
	takeBtn = GetObject("onOff_mc");
}

event MMOPlayer ClonePlayer( MMOPlayer Base )
{
	if(ShowPlayer == none)
	{
		ShowPlayer = base.Spawn( class'MMOPlayer', GetPC() );
		ShowPlayer.InitItems();
	}
	ShowPlayer.CloneFrom( base );
	ShowPlayer.SetPhysics( PHYS_None );
	return ShowPlayer;
}
event CallSetWindowTitle(string title)
{
	ActionScriptVoid("SetWindowTitle");
}

final native function ASClickSendToChat();
final native function ASClickTakeOnOff();
final native function ASClickTurnRight();
final native function ASClickTurnLeft();
final native function ASReleasTurn();

DefaultProperties
{
	DefaultVisible=false
}