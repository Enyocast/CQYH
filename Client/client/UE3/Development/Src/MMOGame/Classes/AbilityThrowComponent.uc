class AbilityThrowComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;

var() ESourceType   SourceType;
var() name          AttachSocketName <DynamicList="SocketList">;
var() Vector        RelativeLocation;
var() Rotator       RelativeRotation;
var() Vector        T0;
var() Vector        T1;
var() float         Exp;


cpptext
{
	virtual FString GetResName();
	virtual struct BaseComponent* CreateCplusplusNode();
}



DefaultProperties
{
	LineColor=(R=0.7227,G=0.4767,B=0.3398,A=1.0)
	TitleString="Throw"
	bHaveTrail=true
	T0=(X=0, Y=0, Z=1200)
	T1=(X=0, Y=0, Z=-1000)
	Exp=0.3
}

