class AbilityPostProcessComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;


var() editinline PostProcessEffect PostEffect;

var() bool bPlayInThirdPersonView;

cpptext
{
	virtual FString GetResName();
	virtual struct BaseComponent* CreateCplusplusNode();
}


DefaultProperties
{
	LineColor=(R=0.8118,G=0.1529,B=0.3216,A=1.0)
	TitleString="PostProcess"
	bHaveTrail=true
	bPlayInThirdPersonView=true
}

