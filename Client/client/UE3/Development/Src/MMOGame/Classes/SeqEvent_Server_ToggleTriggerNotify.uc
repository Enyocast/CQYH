//ToggleTrigger 服务器通知Event
//关联MMOServerToggleActor 设置State
class SeqEvent_Server_ToggleTriggerNotify extends SequenceEvent;

function bool IsDesiredInstigator(Actor obj)
{

	return false;
}

DefaultProperties
{	
	ObjName="Toggle Trigger Notify"
	ObjCategory="MMO Server To Client"
	bPlayerOnly=false

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Open")
	OutputLinks(1)=(LinkDesc="Close")

}