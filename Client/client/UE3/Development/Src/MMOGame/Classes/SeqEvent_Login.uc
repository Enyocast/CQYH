class SeqEvent_Login extends SequenceEvent;

event Activated()
{
	ActivateOutputLink(0);
}

DefaultProperties
{	
	ObjName="Login"
	ObjCategory="MMO Client Old"
	bPlayerOnly=false
}
