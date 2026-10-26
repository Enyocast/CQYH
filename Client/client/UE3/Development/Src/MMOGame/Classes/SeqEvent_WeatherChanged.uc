
class SeqEvent_WeatherChanged extends SequenceEvent
	native;

cpptext
{
	virtual void Activated();
}

DefaultProperties
{
	ObjName="Weather Changed"
	VariableLinks.Empty
	OutputLinks(0)=(LinkDesc="Normal")
	OutputLinks(1)=(LinkDesc="Fog")
	OutputLinks(2)=(LinkDesc="Thunder")
	OutputLinks(3)=(LinkDesc="Rain")
	OutputLinks(4)=(LinkDesc="Snow")
	OutputLinks(5)=(LinkDesc="Storm")
	OutputLinks(6)=(LinkDesc="Eclipse")
	bPlayerOnly=false
	MaxTriggerCount=0
}
