/**
 *
 *
 */
class SeqAct_PauseBgMusic extends SequenceAction
	native;

var() bool bPause;

cpptext
{
	virtual void Activated();
}

defaultproperties
{
	ObjName="Pause BG Music"
	ObjCategory="Sound"
	VariableLinks.Empty
}
