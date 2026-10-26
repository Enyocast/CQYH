class MMOGameState_InGame extends MMOGameState
	native;

function Init()
{
	super.Init();
}

native function EGameState GetID();
native function OnEnter();
native function OnLeave();

DefaultProperties
{
}
