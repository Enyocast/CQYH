class SeqAct_PlayerMatineeEnd extends SequenceAction
	native;

cpptext
{
	virtual void Activated();
}

DefaultProperties
{
	ObjName = "Player Matinee End"
	ObjCategory = "MMO Client Matinee"

	InputLinks.Empty
	InputLinks(0) = ( LinkDesc = "In" )

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	VariableLinks.Empty	
	VariableLinks(0)=(ExpectedType=class'SeqVar_Object',LinkDesc="Replace Target")
	//VariableLinks(1)=(ExpectedType=class'SeqVar_Object',LinkDesc="Temp Target")
}

