
class SeqEvent_DayTimeChanged extends SequenceEvent
	native;

cpptext
{
	virtual void Activated();

	void ActivatePlan();
	void ActivateDay();
	void ActivateDayToNight();
	void ActivateNight();
	void ActivateNightToDay();
}

DefaultProperties
{
	ObjName="Day Time Changed"
	OutputLinks(0)=(LinkDesc="Plan")
	OutputLinks(1)=(LinkDesc="Day")
	OutputLinks(2)=(LinkDesc="DayToNight")
	OutputLinks(3)=(LinkDesc="Night")
	OutputLinks(4)=(LinkDesc="NightToDay")
	VariableLinks(0)=(ExpectedType=class'SeqVar_Int', LinkDesc="PlanTime")
	bPlayerOnly=false
	MaxTriggerCount=0
}
