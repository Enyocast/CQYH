class SeqAct_HideSDOLogin extends SequenceAction
	native;

cpptext
{
	virtual void Activated();
}

DefaultProperties
{
	ObjName="Hide SDO Login"
	ObjCategory="MMO UI"

	InputLinks.Empty
	InputLinks(0)=(LinkDesc="In")

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	VariableLinks.Empty
}

