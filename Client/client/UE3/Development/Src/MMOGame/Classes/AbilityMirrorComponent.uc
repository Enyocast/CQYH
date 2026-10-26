class AbilityMirrorComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;

var() float Interval;
var() float MirrorLifeSpan;
var() LinearColor ColorValue;
var() int MaxCount;

var MaterialInstanceTimeVarying DefaultMaterial;
var() MaterialInstanceTimeVarying CustomMaterial;

var AnimTree AnimTreeTemplate;


cpptext
{
	virtual FString GetResName() { return TitleString; }
	virtual struct BaseComponent* CreateCplusplusNode();
}



DefaultProperties
{
	LineColor=(R=1.0,G=0788,B=0.0549,A=1.0)
	TitleString="Mirror"
	bHaveTrail=true
	Interval=0.3
	ColorValue=(R=1.0, B=1.0, G=1.0, A=1.0)
	MaxCount=5
	MirrorLifeSpan=1.5
	DefaultMaterial=MaterialInstanceTimeVarying'Mirror_Mat.M_Mirror_001_INST'
	AnimTreeTemplate=AnimTree'AT_Common.Weapon'
}

