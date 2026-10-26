
class SeqAct_BeginMovieCapture extends SequenceAction
	native;

var(MMO) bool ShowUI;
var(MMO) bool DisableInput;
var(MMO) bool ShowPlayerSelf;
var(MMO) int MovieCaptureFPS;

cpptext
{
	virtual void Activated();
}

DefaultProperties
{
	ObjName="Begin Movie Capture"
	ObjCategory="MMO Client Matinee"

	InputLinks.Empty
	InputLinks(0)=(LinkDesc="In")

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	ShowUI=false
	DisableInput=true
	ShowPlayerSelf=false
	MovieCaptureFPS=30
}
