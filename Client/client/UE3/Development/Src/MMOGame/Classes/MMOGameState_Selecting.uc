class MMOGameState_Selecting extends MMOGameState
	native;

var name IdleAnimName;
var name LoginIdleAnimName;

function Init()
{
	super.Init();
}

native function EGameState GetID();
native function OnEnter();
native function OnLeave();

DefaultProperties
{
	LoginIdleAnimName="SelectModel"
}
