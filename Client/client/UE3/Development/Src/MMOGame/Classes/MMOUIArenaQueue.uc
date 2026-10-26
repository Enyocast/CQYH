class MMOUIArenaQueue extends MMOUIBase
	native(UI);

enum ArenaQueueStep
{
	ArenaQueueStepNone,
	ArenaQueueStepQueuing,
	ArenaQueueStepWaitingEnter,
};

var array<GFxObject> MyTeamItem;
var GFxObject ArenaMode;
var GFxObject ArenaSize;

var GFxObject MsgboxWindow;


var int ArenaModeValue;
var int ArenaSizeValue;
//var float TickTime;
//var float LastTime;
//var bool StartEnterCoolDown;
//var bool StartQueue;
//var float QueueTime;
var GFxObject QueueTimeTextField;

var const int TeamMemberNum;
var const int EnterCoolDownTime;

var ArenaQueueStep Step;

event InitOnce()
{
	//local int i;

	super.InitOnce();
	//MyTeamItem.Add(TeamMemberNum);

	//for( i = 0 ; i < TeamMemberNum ; i++)	
	//{
	//	MyTeamItem[i] = GetObject( "MyTeamItem"$i );
	//}

	//ArenaMode = GetObject("ArenaMode");
	//ArenaSize = GetObject("ArenaSize");
	//QueueTimeTextField = GetObject("QueneTime");
	

	//class'MMOUIManager'.static.SetOpenArenaQueueDelegate(OpenArenaQueue);
	//class'MMOUIManager'.static.SetLeaveArenaQueueDelegate(Leave);
	//class'MMOUIManager'.static.SetAskEnterArenaDelegate(AskEnterArena);
}

//native function NativeInitOnce();

//native function OpenArenaQueue( int mode , int size );

//native function ClickLeave();
//native function ClickIcon();
//native function Leave();
//native function Minimize();


//native function EnterArenaConfirm( GFxObject mc );
//native function EnterArenaCancel( GFxObject mc );
//native function UpdateTime( float dt );

//native function AskEnterArena();
//native function ClearUI();

event CallSetHintText( GFxObject data )
{
	ActionScriptVoid("SetHintText");
}

event CallSetPanelText( GFxObject data )
{
	ActionScriptVoid("SetPanelText");
}

event CallShowLeaveButton( bool show )
{
	ActionScriptVoid("ShowLeaveButton");
}

event CallToggleLeaveButton()
{
	ActionScriptVoid( "ToggleLeaveButton" );
}

DefaultProperties
{
	IsDynamicLoad=true
	TeamMemberNum=5
	EnterCoolDownTime=60
	//TickTime=0.0f
	//LastTime=0
	//StartEnterCoolDown=false
	//StartQueue=false
	//QueueTime=0.0
	CloseOnEsc=false
}
