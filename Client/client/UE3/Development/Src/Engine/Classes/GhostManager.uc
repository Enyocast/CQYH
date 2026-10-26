
// qin@snda

//class GhostManager extends Actor
//	native;

//var int MaxActiveGhosts;
//var transient Material GhostMaterialTemplate;

//struct native ActiveGhostInfo
//{
//	var int MaxGhosts;
//	var Color GhostColor;
//	var float GhostInterval;
//	var float GhostLife;

//	var float AccumulatedTime;

//	var Actor BaseActor;
//	var SkeletalMeshComponent ParentAnimComponent;
//	var SkeletalMeshComponent BaseMeshComponent;
//	var init array<SkeletalMeshActorSpawnable> ParentActors;
//	var init array<SkeletalMeshActorSpawnable> GhostActors;
//	var init array<float> LifeRemaining;
//};
//var array<ActiveGhostInfo> ActiveGhosts;

//cpptext
//{
//	virtual void AddGhostActor(AActor* Actor, USkeletalMeshComponent* BaseMeshComponent, INT MaxGhosts, const FColor& GhostColor, FLOAT GhostInterval, FLOAT GhostLife);
//	virtual void RemoveGhostActor(AActor* Actor);
//	virtual void ClearGhostActors();

//	virtual void TickSpecial(FLOAT DeltaTime);
//}

//defaultproperties
//{
//	MaxActiveGhosts=5
//	GhostMaterialTemplate=Material'MMO_MaterialTemplate.Character.MT_Ghost'
//}

class GhostManager extends Actor
	native;

var int MaxActiveGhosts;
var transient Material GhostMaterialTemplate;

struct native ActiveGhostInfo
{
	var Color GhostColor;
	var float GhostLife;

	var Actor BaseActor;
	var SkeletalMeshComponent ParentAnimComponent;
	var SkeletalMeshComponent BaseMeshComponent;
	var SkeletalMeshActorSpawnable ParentActor;
	var SkeletalMeshActorSpawnable GhostActor;
	var float LifeRemaining;
};
var array<ActiveGhostInfo> ActiveGhosts;

cpptext
{
	virtual INT AddGhostObject(AActor* Actor, USkeletalMeshComponent* BaseMeshComponent, const FColor& GhostColor, FLOAT GhostLife);
	virtual void RemoveGhostObject(INT Id);
	virtual void ClearGhostObjects();

	virtual void PostBeginPlay();
	virtual void TickSpecial(FLOAT DeltaTime);
}

defaultproperties
{
	MaxActiveGhosts=50
	GhostMaterialTemplate=Material'MMO_MaterialTemplate.Character.MT_Ghost'
}
