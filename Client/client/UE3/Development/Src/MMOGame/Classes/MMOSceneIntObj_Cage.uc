class MMOSceneIntObj_Cage extends MMOSceneInteractableObj;

var( MMOCage )  InterpActor         StandPad;
var( MMOCage )  name                PadSocket <DynamicList="SocketList">;

var( MMOCage )  array< NPC >        MonstersInCage;

state Prepare
{
	function LockMonsters( )
	{
		local NPC itr;
		foreach MonstersInCage( itr )
		{
			NPCController( itr.Controller ).PushState( 'WaitInCage' );
		}
	}

Begin:
	LockMonsters( );
	// code copy from parent
	Sleep( PlayAnimation( AnimNamePrepare ) );
	GotoState( 'Activate' );
}

state Activate
{
	event Tick( float DeltaTime )
	{
		local Vector loc;
		super.Tick( DeltaTime );
		if( StandPad != none && PadSocket != '' )
		{
			SceneObj.GetSocketWorldLocationAndRotation( PadSocket, loc );
			StandPad.SetLocation( loc );
		}
	}

	function FreeMonsters( )
	{
		local NPC itr;
		foreach MonstersInCage( itr )
		{
			NPCController( itr.Controller ).PopState( false );
		}
	}

Begin:
	if( RefVolume != none )
		RefVolume.EnableVolume( );
	Sleep( PlayAnimation( AnimNameActivate ) );
	FreeMonsters( );
	GotoState( 'Stand' );
}

DefaultProperties
{
}
