
class SeqAct_EndMovieCapture extends SequenceAction
	native;


cpptext
{
	virtual void Activated();
}


DefaultProperties
{
	ObjName="End Movie Capture"
	ObjCategory="MMO Client Matinee"

	InputLinks.Empty
	InputLinks(0)=(LinkDesc="In")

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")
}
