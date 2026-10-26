class MMOUITargetInfo extends MMOUIBase
	native(UI)
	;

var int HPx;
var int MPx;
var int HPlenth;
var int MPlenth;
var int InfoType;

var int LastHP;

var GFxObject AffixText;
var MMOActor DesiredMMOActor;
var MMOActor CurrentMMOActor;
var MMOActor LastMMOActor;

var float DisappearTime;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
	AffixText = GetObject("affixText");
}

native function OnLeave();
native function TargetActorChange( BYTE type, MMOActor actor );
native function NPCHpChange( NPC npc , int hp );
native function OtherPlayerHpChange( MMOPlayer pl ,int hp );

native function string GetAffixString( Ai_Affix aff );
native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

native function  UpdateNPCInfo ( MMOActor Actor , bool Direct,int hp) ;
native function TickTime            ( float tickTime );

event CallSetTargetInfo( GFxObject data )
{
	ActionScriptVoid("SetTargetInfo");
}

event CallSetAlpha( float InAlpha )
{
	ActionScriptVoid("SetAlpha");
}

function AddBuff(int buffSlotID,string buffIcon, int buffMaxTime, int buffCurTime, int stackCount, int ownerID,int buffID,int showTimeUp,bool debuff)
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

native function PostAdvance(float DeltaTime );

native function ASRightClickTargetInfo2( int x , int y , String RoleName );
event AddTargetBuffPanel(int buffSlotID,string buffIcon,int buffMaxTime,int buffCurTime, int stackCount, int ownerID,int buffID,int showTimeUp,bool debuff)
{
	AddBuff( buffSlotID, buffIcon,  buffMaxTime, buffCurTime,stackCount,ownerID,buffID,showTimeUp, debuff);
}
event DeleteTargetBuffPanel(int buffSlotID)
{
	DeleteBuff( buffSlotID );
}

DefaultProperties
{
	CloseOnEsc=false
	DesiredMMOActor =none
	CurrentMMOActor =none
	LastMMOActor    =none
	DisappearTime   =-1.0f
}
