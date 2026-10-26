class AbilityVisibleComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;

var() bool bVisible;


cpptext
{
	virtual FString GetResName() { return TitleString; }
	virtual struct BaseComponent* CreateCplusplusNode();
}



DefaultProperties
{
	LineColor=(R=0.5,G=0.0.5,B=0.0.5,A=1.0)
	TitleString="Visible"
	bHaveTrail=true
}

