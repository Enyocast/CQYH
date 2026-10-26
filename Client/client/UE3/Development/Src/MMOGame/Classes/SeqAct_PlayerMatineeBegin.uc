class SeqAct_PlayerMatineeBegin extends SequenceAction
	native;

var() bool bHideWeapon;

cpptext
{
	virtual void Activated();
}

DefaultProperties
{
	ObjName = "Player Matinee Begin"
	ObjCategory = "MMO Client Matinee"

	bHideWeapon=true

	InputLinks.Empty
	InputLinks(0) = ( LinkDesc = "In" )

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	VariableLinks.Empty	
	VariableLinks(0)=(ExpectedType=class'SeqVar_Object',LinkDesc="Replace Target")
}

