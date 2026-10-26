class SeqAct_ShowUI extends SequenceAction
	;

var(MMO) name PanelName;
var(MMO) bool Show;

event Activated()
{	
	class'MMOUIManager'.static.ShowPanelEx(PanelName, Show, "");
}



DefaultProperties
{
	ObjName="Show UI"
	ObjCategory="MMO UI"

	InputLinks.Empty
	InputLinks(0)=(LinkDesc="In")

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	VariableLinks.Empty
}

