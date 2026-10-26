class AbilityPhysicSimulateComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;

enum ESimulateType
{
	SimulateType_Ragdoll,
	SimulateType_Fully,
	SimulateType_PartialSimulate,
	SimulateType_CustomSimulate,
};

var() ESimulateType Type;
var() float PhysicWeight;
var(CustomSimulate) array<name> SimulateRootBones;

cpptext
{
	virtual FString GetResName() { return TitleString; }
	virtual struct BaseComponent* CreateCplusplusNode();
}



DefaultProperties
{
	LineColor=(R=0.9255,G=0.7176.5,B=0.0,A=1.0)
	TitleString="PhysicSimulate"
	bHaveTrail=true
}

