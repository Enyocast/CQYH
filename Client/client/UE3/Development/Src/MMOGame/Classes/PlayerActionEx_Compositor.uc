//
// PlayerActionEx_Compositor
//
class PlayerActionEx_Compositor extends Object implements(IPlayerActionEx)
	native;

var array<IPlayerActionEx> PlayerActionList;

native function Update(float DeltaTime);
native function bool IsCompleted();
native function Cancel();
native function bool IsMoveAction();

function Add(IPlayerActionEx action)
{
	PlayerActionList.AddItem(action);
}