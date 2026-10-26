class SeqAct_ShowMatineeSubtitle extends SequenceAction
	native;


cpptext
{
	virtual void Activated();
}

DefaultProperties
{
	ObjName="Show Matinee Subtitle"
	ObjCategory="MMO UI"

	InputLinks.Empty
	InputLinks(0) = ( LinkDesc = "Show" )
	InputLinks(1) = ( LinkDesc = "Hide" )

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	VariableLinks.Empty
}

