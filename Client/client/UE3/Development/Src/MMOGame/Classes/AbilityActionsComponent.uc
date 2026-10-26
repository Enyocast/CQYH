class AbilityActionsComponent extends AbilityComponent
	dependson(TypeDefine)
	dependson(MMOAbility)
	editinlinenew
	native;

var() array<ComponentNode> ActionsComponentList;

cpptext
{
	virtual FString GetResName() { return TitleString; }
	virtual struct BaseComponent* CreateCplusplusNode();
}


defaultproperties
{
	Duration = 1.5
	LineColor=(R=0.5059,G=0.0392,B=0.0627,A=1.0)
	TitleString="Actions"
	bHaveTrail=true
}
