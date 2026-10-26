class MMOUIArenaHint extends MMOUIBase
	native(UI);

enum ArenaHintStep
{
	ArenaHintStepWaiting,
	ArenaHintStepFighting,
	ArenaHintStepOver,
};

//var array<GFxObject> MyTeamItem;
//var GFxObject ArenaMode;
//var GFxObject ArenaSize;

//var GFxObject MsgboxWindow;


//var int ArenaModeValue;
//var int ArenaSizeValue;
var float TickTime;
var float ArenaTime;
var float LastTime;
////var bool StartEnterCoolDown;
////var bool StartQueue;
//var float QueueTime;
//var GFxObject QueueTimeTextField;

//var const int TeamMemberNum;
//var const int EnterCoolDownTime;

var ArenaHintStep Step;



//event InitOnce()
//{
	

//	super.InitOnce();

//}


////native function OpenArenaQueue( int mode , int size );

//native function ClickLeave();
//native function ClickIcon();
//native function Leave();
////native function Minimize();


////native function EnterArenaConfirm( GFxObject mc );
////native function EnterArenaCancel( GFxObject mc );
//native function UpdateTime( float dt );

////native function AskEnterArena();
//native function ClearUI();

//event CallSetHintText( GFxObject data )
//{
//	ActionScriptVoid("SetHintText");
//}

////event CallSetPanelText( GFxObject data )
////{
////	ActionScriptVoid("SetPanelText");
////}

////event CallShowLeaveButton( bool show )
////{
////	ActionScriptVoid("ShowLeaveButton");
////}

//event CallToggleLeaveButton()
//{
//	ActionScriptVoid( "ToggleLeaveButton" );
//}

DefaultProperties
{
	IsDynamicLoad=true
	
	ArenaTime=300
	TickTime=0.0f
	LastTime=0

	CloseOnEsc=false
}
