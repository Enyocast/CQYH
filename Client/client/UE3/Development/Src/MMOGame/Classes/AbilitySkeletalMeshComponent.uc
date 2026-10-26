class AbilitySkeletalMeshComponent extends AbilityComponent
	hidecategories(Object)
	editinlinenew
	native;


var() SkeletalMesh  SkeletalMeshRes;
var() name          AnimName;
var() int           StartFrame;
var() float         Rate;
var() bool          bLoop;
var() AnimSet       AnimSet;
var  AnimTree      AnimTreeTemplate;
var() ESourceType   SourceType;
var() bool          bAttach;
var() name AttachSocketName <DynamicList="SocketList">;
var() float Scale;
var() Vector RelativeLocation;
var() Rotator RelativeRotation;
var() array<MaterialInterface> Materials;



cpptext
{
	virtual FString GetResName();
	virtual struct BaseComponent* CreateCplusplusNode();
	FMatrix GetSocketMatrix(AActor* InActor, FVector& InTargetPoint, UBOOL bTarget);
}



DefaultProperties
{
	Duration = 1.0
	LineColor=(R=0.24,G=0.282,B=0.8,A=1.0)
	TitleString="SkeletalMesh"
	bHaveTrail=true
	Scale=1.0
	Rate=1.0
	AnimTreeTemplate=AnimTree'AT_Common.Weapon'
}
