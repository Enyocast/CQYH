class SeqAct_LevelLoaded extends SequenceAction
	native;

cpptext
{
	virtual void Activated();
}

DefaultProperties
{
	ObjName="LevelLoaded"
	ObjCategory="MMO Client"

	InputLinks.Empty
	InputLinks(0) = (LinkDesc = "In")

	OutputLinks.Empty
	OutputLinks(0) = (LinkDesc="Out")

	VariableLinks.Empty
}

