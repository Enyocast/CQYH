class MMOGameState_Login extends MMOGameState
	native;


var int ErrorCodeCauseReturnLogin;
var protected native transient pointer EventAdapter{class IGameEventAdapter};

function Init()
{
	super.Init();
	//CreateLoginMovie();
}

native function NativeInit();

 event CreateLoginMovie()
 {
 	//if( LoginMovie != none)
 	//	return;

	if(class'Engine'.static.IsEditor())
	{
		return;
	}
 
 	
 //	`Log("[MMO]: LoginMovie.SetTimingMode!");
 //	LoginMovie.SetTimingMode(TM_Real);
 
 //	`Log("[MMO]: LoginMovie.Init!");
 //	LoginMovie.Init(class'Engine'.static.GetEngine().GamePlayers[0]);
 
 }

native function EGameState GetID();
native function OnEnter();
native function OnLeave();
native function OnUpdate();

cpptext	
{
	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
}

DefaultProperties
{
}
