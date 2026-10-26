
class MMOGameState extends Object
	native;

enum EGameState
{
	EGameState_None,
	EGameState_Login,
	EGameState_Selecting,
	EGameState_Loading,
	EGameState_InGame
};


function Init()
{
	NativeInit();
}

native function NativeInit();

native function EGameState GetID();
native function ActiveState(EGameState sta);
native function EGameState GetCurrentGameState();

native function OnPreEnter();
native function OnEnter();
native function OnLeave();
native function OnAftLeave();
native function OnUpdate();

DefaultProperties
{
}
