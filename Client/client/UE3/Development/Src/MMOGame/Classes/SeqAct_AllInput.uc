class SeqAct_AllInput extends SequenceAction
	native;

//var() bool bDisableESC;
//var() bool bDisableTheOtherInput;

cpptext
{
	virtual void Activated();
}

DefaultProperties
{
	ObjName = "All Input"
	ObjCategory = "MMO Client"

	InputLinks.Empty
	InputLinks(0) = ( LinkDesc = "On" )
	InputLinks(1) = ( LinkDesc = "Off" )

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	VariableLinks.Empty
}

