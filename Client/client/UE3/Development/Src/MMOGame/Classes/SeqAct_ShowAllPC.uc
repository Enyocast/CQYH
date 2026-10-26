class SeqAct_ShowAllPC extends SequenceAction
	native;

cpptext
{
	virtual void Activated();
}


DefaultProperties
{
	ObjName = "Show All Player Character"
	ObjCategory = "MMO Client"

	InputLinks.Empty
	InputLinks(0) = ( LinkDesc = "Show" )
	InputLinks(1) = ( LinkDesc = "Hide" )

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	VariableLinks.Empty
}

