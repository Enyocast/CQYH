//
// PlayerActionEx_MoveNearTo，靠近到点
//
class PlayerActionEx_Interact extends PlayerActionEx_Base
	native;

var IInteractableActor target;
var int TemplateID;
var float InteractRange;
var bool IsDoodad;

cpptext
{
	virtual FString Dump();

	virtual void Update(FLOAT DeltaTime);
	virtual void ResetAction(UPlayerActionEx_Base* InAction);
	virtual void OnAction(UBOOL bOn);
	virtual UBOOL IsComplete();
	virtual UBOOL IsLatenAction();
}


defaultproperties
{
//	target=nullptr
}