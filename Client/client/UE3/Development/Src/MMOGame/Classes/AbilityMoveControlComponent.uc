class AbilityMoveControlComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;

var() name OverrideIdleAnim;
var() name OverrideMoveAnim;

cpptext
{
	virtual FString GetResName();
	virtual struct BaseComponent* CreateCplusplusNode();
}


DefaultProperties
{
	LineColor=(R=1.0,G=0.5,B=0.1523,A=1.0)
	TitleString="Movement"
	bHaveTrail=true
}

