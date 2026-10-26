//
// trails for ability
//
class AnimNotify_AbilityTrails extends AnimNotify_Trails
	native;

var AnimSet AnimSetData;
var bool bEnable;

cpptext
{
	// AnimNotify interface.
	virtual void Notify(class UAnimNodeSequence* NodeSeq);
	virtual void NotifyTick(class UAnimNodeSequence* NodeSeq, FLOAT AnimCurrentTime, FLOAT AnimTimeStep, FLOAT InTotalDuration);
	virtual void NotifyEnd(class UAnimNodeSequence* NodeSeq, FLOAT AnimCurrentTime);

	void RebuildTrailData(class UAnimNodeSequence* Seq);
}



DefaultProperties
{
	bEnable=false
}
