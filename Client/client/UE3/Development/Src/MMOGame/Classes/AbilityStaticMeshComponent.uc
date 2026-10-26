class AbilityStaticMeshComponent extends AbilityComponent
	hidecategories(Object)
	editinlinenew
	native;


var() StaticMesh    MeshRes;
var() array<MaterialInstance> OverrideMaterials;
var() ESourceType   SourceType;
var() bool          bAttach;
var() name AttachSocketName <DynamicList="SocketList">;
var() float Scale;
var() Vector RelativeLocation;
var() Rotator RelativeRotation;

var() bool bVisibleToEveryone;

// movement
var() Vector MoveSpeed;
var() float MoveTime;

var() Rotator RotatoSpeed;
var() float RotatoTime;

var() Vector ScaleSpeed;
var() float ScaleTime;

var() bool bUseForShowEffectArea;

var() name Parameter1Name;
var() float Parameter1Value;

var() name Parameter2Name;
var() float Parameter2Value;


cpptext
{
	virtual struct BaseComponent* CreateCplusplusNode();
	FMatrix GetSocketMatrix(AActor* InActor, FVector& InTargetPoint, UBOOL bTarget);
}



DefaultProperties
{
	Duration = 1.0
	LineColor=(R=1.0,G=0.5,B=0.1,A=1.0)
	ScaleSpeed=(X=1.0,Y=1.0,Z=1.0)
	TitleString="StaticMesh"
	bHaveTrail=true
	Scale=1.0
	bVisibleToEveryone=false
	Parameter1Name=Type
	Parameter2Name=Param1

}
