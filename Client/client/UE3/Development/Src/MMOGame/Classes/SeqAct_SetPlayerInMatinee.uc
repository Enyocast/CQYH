class SeqAct_SetPlayerInMatinee extends SequenceAction
	native;

cpptext
{
	virtual void Activated();
}

DefaultProperties
{
	ObjName = "Set Player In Matinee"
	ObjCategory = "MMO Client Matinee"

	InputLinks.Empty
	InputLinks(0) = ( LinkDesc = "On" )
	InputLinks(1) = ( LinkDesc = "Off" )

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	VariableLinks.Empty
}

