class MMOUIMyInfo extends MMOUIBase
	native(UI);

var int CurrentPkMode;
var bool bFirstOpen;
event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);

	//GetObject("PlayerInfoIcon_mc").GotoAndStopI( MMOActor(GetPC().pawn).NPCIcon + 2 );
	
}

function AddBuff(int buffSlotID,string buffIcon, int buffMaxTime, int buffCurTime, int stackCount, int ownerID, int buffID, int showTimeUp,bool debuff)
{
	local array<ASValue> args;
	local ASValue asval;

	asval.Type = AS_Number;
	asval.n = buffSlotID;
	args[0] = asval;
	asval.Type = AS_String;
	asval.s = buffIcon;
	args[1] = asval;
	asval.Type = AS_Number;
	asval.n = buffMaxTime;
	args[2] = asval;
	asval.Type = AS_Number;
	asval.n = buffCurTime;
	args[3] = asval;
	asval.Type = AS_Number;
	asval.n = stackCount;
	args[4] = asval;
	asval.Type = AS_Number;
	asval.n = ownerID;
	args[5] = asval;
	asval.Type = AS_Number;
	asval.n = buffID;
	args[6] = asval;
	asval.Type = AS_Number;
	asval.n = showTimeUp;
	args[7] = asval;
	asval.Type = AS_Boolean;
	asval.B = debuff;
	args[8] = asval;
	Invoke("ShowBuff",args);
}

function DeleteBuff(int buffSlotID)
{
	local array<ASValue> args;
	local ASValue asval;
	asval.Type = AS_Number;
	asval.n = buffSlotID;
	args[0] = asval;
	Invoke("HideBuff",args);
}

event DeleteAllBuff()
{
	local array<ASValue> args;
	args.Length = 0;
	Invoke("HideAllBuff",args);
}

event SetHpFx(int curHp, int maxHp)
{
	ActionScriptVoid("root.SetHp");
}

native final function PlayerHPChange(int NewHP, int MaxHP);
native function PlayerLevelChange( int lastLv , int newLv );
native function PlayerPkModeChange( int PkMode );
native function PlayerBaseInfoChange();
native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

event CallAsSetVipLevel( int curVipLevel )
{
	ActionScriptVoid( "UCVipShow" );
}

native function ASMyInfoRightClick( int x , int y );
native function ASSetPkMode(int PkMode);
native function ASPkModeChange();

//
final native function ASVIPRightClick();
final native function ASVIPShowTips( GFxObject hintMc );
final native function ASVIPHideTips();

event AddFunctionBuffPanel(int buffSlotID,string buffIcon,int buffMaxTime,int buffCurTime, int stackCount, int ownerID,int buffID,int showTimeUp,bool debuff)
{
	if(IsVisible)
	{
		AddBuff( buffSlotID, buffIcon,  buffMaxTime, buffCurTime,stackCount,ownerID,buffID,showTimeUp, debuff);
	}
}
event DeleteFunctionBuffPanel(int buffSlotID)
{
	DeleteBuff( buffSlotID );
}

DefaultProperties
{
	DefaultVisible=true
	CloseOnEsc=false
	bFirstOpen=true
}
