class SeqAct_UpdateMatineeSubtitle extends SequenceAction
	native;

var() edittextbox string Subtitle   <Edit="TextEdit_Nouse">;

cpptext
{
	virtual void Activated();
}

DefaultProperties
{
	ObjName="Update Matinee Subtitle"
	ObjCategory="MMO UI"

	InputLinks.Empty
	InputLinks(0)=(LinkDesc = "In")

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	VariableLinks.Empty
}

