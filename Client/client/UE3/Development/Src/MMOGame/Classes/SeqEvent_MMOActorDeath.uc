class SeqEvent_MMOActorDeath extends SequenceEvent;

event Activated()
{
	ActivateOutputLink(0);
}

DefaultProperties
{	
	ObjName="Actor Died"
	ObjCategory="MMO Client Old"
	bPlayerOnly=false
}
