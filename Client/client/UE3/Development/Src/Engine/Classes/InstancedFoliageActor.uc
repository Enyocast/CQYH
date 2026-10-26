/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
class InstancedFoliageActor extends Actor
	native(Foliage)
	hidecategories(Object);

var	const native Map_Mirror FoliageMeshes{TMap<class UStaticMesh*, struct FFoliageMeshInfo>};

/** The static mesh type that will be used to show the widget */
var const transient StaticMesh SelectedMesh;

/* Used during gameplay to simplify RTGC */
var const transient array<InstancedStaticMeshComponent> InstancedStaticMeshComponents;

// [ming@snda
var(Wind) bool	AcceptInteractWind;

/* components further than this distance don't get updated */
var(Wind) float MaxUpdateDistance;

var const int	TickCount;
var const int	SkipUpdateRate;

var const INT	MaxWindFieldSize;

struct native WindFieldData
{
	var array<vector4>	WindField;
	var array<vector4>	WindPower;
	
	var INT	OwnerInstance;

	structcpptext
	{
		FWindFieldData( /*INT totalSize*/ )
		{
			Reset();
		}

		void Reset()
		{
			// must be the same as InstancedFoliageActor::MaxWindFieldSize ( currently 15 )
			INT totalSize = 15 * 15;//MaxWindFieldSize * MaxWindFieldSize;

			if( WindField.Num() != totalSize )
			{
				WindField.Empty();
				WindField.Add( totalSize );
			}
			FVector4 initValue( 0.f, 0.f, 1.f, 0.f );
			for( INT i = 0; i < totalSize; ++i )
			{
				WindField(i) = initValue;
			}

			if( WindPower.Num() != totalSize )
			{
				WindPower.Empty();
				WindPower.Add( totalSize );
			}
			FVector zero( 0.f, 0.f, 0.f );
			for( INT i = 0; i < totalSize; ++i )
			{
				WindPower(i) = zero;
			}

			OwnerInstance = -1;
		}

		~FWindFieldData()
		{
			WindField.Remove( 0, WindField.Num() );
			WindPower.Remove( 0, WindPower.Num() );
		}
	}
};

var transient WindFieldData	WindFieldCache[100]; 

var transient array<vector4> EmptyWindField;
// ming@snda]

native function ChackHideFoliage();
cpptext
{
	// UObject interface
	virtual void Serialize(FArchive& Ar);
	virtual void PostLoad();

	// AActor interface
	virtual void UpdateComponentsInternal(UBOOL bCollisionUpdate = FALSE);
	virtual void ClearComponents();

	// [ming@snda
	virtual UBOOL Tick( FLOAT DeltaTime, enum ELevelTick TickType );

	void ResetComponents( FFoliageMeshInfo& MeshInfo );

	void SetFire( const FVector& Center, FLOAT Radius );

	INT		GetFreeDataFromCache();
	void	FreeDataToCache( INT i );
	// ming@snda]

	// AInstancedFoliageActor interface
#if WITH_EDITOR
	// Called from editor code to manage instances for components
	void SnapInstancesForLandscape( class ULandscapeHeightfieldCollisionComponent* InComponent, const FBox& InInstanceBox );
	void MoveInstancesForComponentToCurrentLevel( class UActorComponent* InComponent );
	void MoveInstancesForMovedComponent( class UActorComponent* InComponent );
	TMap<class UStaticMesh*,TArray<const struct FFoliageInstancePlacementInfo*> > GetInstancesForComponent( class UActorComponent* InComponent );
	void DeleteInstancesForComponent( class UActorComponent* InComponent );

	// Addition, removal and selection
	struct FFoliageMeshInfo* AddMesh( class UStaticMesh* InMesh );
	void RemoveMesh( class UStaticMesh* InMesh );
	void SelectInstance( class UInstancedStaticMeshComponent* InComponent, INT InComponentInstanceIndex, UBOOL bToggle );
	void ApplySelectionToComponents( UBOOL bApply );
	void CheckSelection();
	FVector GetSelectionLocation();

	// Get the instanced foliage actor for the current streaming level.
	static AInstancedFoliageActor* GetInstancedFoliageActor(UBOOL bCreateIfNone=TRUE);
	// Get the instanced foliage actor for the specified streaming level. Never creates a new IFA.
	static AInstancedFoliageActor* GetInstancedFoliageActorForLevel(ULevel* Level);

	// ming@snda
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	//shanling@snda
	void ReBluildFoliagBaseComponent( UBOOL bFilterLandscape,
	UBOOL bFilterStaticMesh,
	UBOOL bFilterBSP,
	UBOOL bFilterTerrain );
#endif
}

defaultproperties
{
	// ming@snda
	bStatic=false
	//bStatic=true

	// [ming@snda
	AcceptInteractWind=true
	MaxUpdateDistance=4000
	TickCount=0
	SkipUpdateRate=1
	MaxWindFieldSize=15
	// ming@snda]
}