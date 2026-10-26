class AbilityScaleComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;

var() Vector Scale3D;
var() float FadeInTime;
var() float FadeOutTime;


cpptext
{
	virtual FString GetResName() { return TitleString; }
	virtual struct BaseComponent* CreateCplusplusNode();
}



DefaultProperties
{
	LineColor=(R=0.5,G=0.0.5,B=0.0.5,A=1.0)
	TitleString="Scale"
	bHaveTrail=true
	Scale3D=(X=1.5, Y=1.5, Z=1.5)
	FadeInTime=0.2
	FadeOutTime=0.1
}

