/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
class LandscapeProxy extends Info implements (IPickableActor, IPickablePoint) // song@snda
	native(Terrain)
	//shanling@snda
	//hidecategories(Display, Attachment, Physics, Debug, Lighting, LOD);
	hidecategories(Display, Attachment, Physics, Debug, Lighting, LOD, Movement);

var EPickPriority PickPriority;	// song@snda
var EPickPointPriority PickPointPriority;	// song@snda

/** Guid for LandscapeEditorInfo **/
var const Guid LandscapeGuid;

/** Max LOD level to use when rendering */
var(LOD) int MaxLODLevel;

/** Default physical material, used when no per-layer values physical materials */
var(Landscape) PhysicalMaterial DefaultPhysMaterial;

/**
 * Allows artists to adjust the distance where textures using UV 0 are streamed in/out.
 * 1.0 is the default, whereas a higher value increases the streamed-in resolution.
 */
var(Landscape) const float	StreamingDistanceMultiplier;

/** Combined material used to render the landscape */
var(Landscape) MaterialInterface	LandscapeMaterial;
var(LOD) float	LODDistanceFactor;

/** The array of LandscapeComponent that are used by the landscape */
var const array<LandscapeComponent>	LandscapeComponents;

/** Array of LandscapeHeightfieldCollisionComponent */
var const array<LandscapeHeightfieldCollisionComponent>	CollisionComponents;

// [ming@snda
/** Structure storing channel usage for weightmap textures */
/*
struct native LandscapeWeightmapUsage
{
	var LandscapeComponent ChannelUsage[4];

	structcpptext
	{
		// tor
		FLandscapeWeightmapUsage()
		{
			ChannelUsage[0] = NULL;
			ChannelUsage[1] = NULL;
			ChannelUsage[2] = NULL;
			ChannelUsage[3] = NULL;
		}

		// Serializer
		friend FArchive& operator<<( FArchive& Ar, FLandscapeWeightmapUsage& U );

		INT FreeChannelCount() const
		{
			return	((ChannelUsage[0] == NULL) ? 1 : 0) + 
					((ChannelUsage[1] == NULL) ? 1 : 0) + 
					((ChannelUsage[2] == NULL) ? 1 : 0) + 
					((ChannelUsage[3] == NULL) ? 1 : 0);
		}
	}
};
*/
struct native LandscapeWeightmapUsage
{
	var LandscapeComponent ChannelUsage[4];
	var LandscapeComponent ChannelUsage2[4];

	structcpptext
	{
		FLandscapeWeightmapUsage()
		{
			ChannelUsage[0] = NULL;
			ChannelUsage[1] = NULL;
			ChannelUsage[2] = NULL;
			ChannelUsage[3] = NULL;
			ChannelUsage2[0] = NULL;
			ChannelUsage2[1] = NULL;
			ChannelUsage2[2] = NULL;
			ChannelUsage2[3] = NULL;
		}

		friend FArchive& operator<<( FArchive& Ar, FLandscapeWeightmapUsage& U );

		INT FreeChannelCount() const
		{
			return	((ChannelUsage[0] == NULL) ? 1 : 0) + 
					((ChannelUsage[1] == NULL) ? 1 : 0) + 
					((ChannelUsage[2] == NULL) ? 1 : 0) + 
					((ChannelUsage[3] == NULL) ? 1 : 0);
		}

		INT FreeChannelCount2() const
		{
			return	((ChannelUsage2[0] == NULL) ? 1 : 0) + 
					((ChannelUsage2[1] == NULL) ? 1 : 0) + 
					((ChannelUsage2[2] == NULL) ? 1 : 0) + 
					((ChannelUsage2[3] == NULL) ? 1 : 0);
		}

		INT FreeChannelCountTotal() const
		{
			return FreeChannelCount() + FreeChannelCount2();
		}

		ULandscapeComponent* GetChannelUsage( INT idx ) const
		{
			if( idx < 0 || idx > 7 )
				return NULL;
			if( idx < 4 )
				return ChannelUsage[idx];
			else
				return ChannelUsage2[idx - 4];
		}

		void SetChannelUsage( INT idx, ULandscapeComponent* comp )
		{
			if( idx < 0 || idx > 7 )
				return;
			if( idx < 4 )
				ChannelUsage[idx] = comp;
			else
				ChannelUsage2[idx-4] = comp;
		}
	}
};
// ming@snda]

/** Map of material instance constants used to for the components. Key is generated with ULandscapeComponent::GetLayerAllocationKey() */
var const native map{FString ,class UMaterialInstanceConstant*} MaterialInstanceConstantMap;

/** Map of weightmap usage */
var const native map{UTexture2D*,struct FLandscapeWeightmapUsage} WeightmapUsageMap;

/**
 *	The resolution to cache lighting at, in texels/patch.
 *	A separate shadow-map is used for each terrain component, which is up to
 *	(MaxComponentSize * StaticLightingResolution + 1) pixels on a side.
 *	Must be a power of two, 1 <= StaticLightingResolution <= MaxTesselationLevel.
 */
var(Lighting) float				StaticLightingResolution;

// NVCHANGE_BEGIN_JC - Landscape ( Light Channel )
var(Lighting) const editconst LightingChannelContainer	LightingChannels;
// NVCHANGE_END_JC - Landscape ( Light Channel )

var(LandscapeProxy) transient Landscape LandscapeActor;
var const bool bIsProxy;
var editoronly transient bool bIsSetup;
var editoronly transient bool bResetup;
var editoronly transient bool bIsMovingToLevel; // Check for the Move to Current Level case

/** The Lightmass settings for this object. */
var(Lightmass) LightmassPrimitiveSettings	LightmassSettings <ScriptOrder=true>;

/** The landscape LOD level to use when generating collision data */
var(LOD) int CollisionMipLevel;

// NVCHANGE_BEGIN_JC - TESSELLATION ( Landscape Adaptive Tessellation )
var(LOD) float	DistToCamForFullTessFactor;
var(LOD) float	RadiusToFadeOutTessFactor;
var(LOD) float	MaterialTessFactor;
// NVCHANGE_END_JC - TESSELLATION ( Landscape Adaptive Tessellation )

// ming@snda
var(LOD) float	MaxDrawDistance;

/** The first landscape LOD level to use on mobile platforms */
var(LOD) int MobileLODBias;

struct native LandscapeLayerStruct
{
	var() LandscapeLayerInfoObject LayerInfoObj;

	var editoronly MaterialInstanceConstant ThumbnailMIC;
	var editoronly LandscapeProxy Owner;
	var editoronly transient int DebugColorChannel;
	var editoronly transient bool bSelected;
	var editoronly string SourceFilePath;

	structcpptext
	{
		FLandscapeLayerStruct(ULandscapeLayerInfoObject* InLayerInfo, class ALandscapeProxy* InProxy, const TCHAR* InFilePath)
#if WITH_EDITORONLY_DATA
		: SourceFilePath(E_ForceInit)
#endif
		{
			LayerInfoObj = InLayerInfo;
#if WITH_EDITORONLY_DATA
			ThumbnailMIC = NULL;
			DebugColorChannel = 0;
			bSelected = FALSE;
			Owner = InProxy;
			SourceFilePath = InFilePath;
#endif
		}
	}
};

var(Landscape) array<LandscapeLayerStruct> LayerInfoObjs;

/** Data set at creation time */
var const int ComponentSizeQuads;		// Total number of quads in each component
var const int SubsectionSizeQuads;		// Number of quads for a subsection of a component. SubsectionSizeQuads+1 must be a power of two.
var const int NumSubsections;			// Number of subsections in X and Y axis

native function EPickPriority GetPickPriority();	//song@snda
native function EPickPointPriority GetPickPointPriority();	//song@snda
native function EMMOCursorType GetMouseCursor(); // oscar@snda

cpptext
{
	// AActor interface
	virtual UBOOL ShouldTrace(UPrimitiveComponent* Primitive,AActor *SourceActor, DWORD TraceFlags);
	virtual void UpdateComponentsInternal(UBOOL bCollisionUpdate = FALSE);
	virtual void ClearComponents();
	virtual void InitRBPhys();

	virtual class ALandscape* GetLandscapeActor();

	virtual FGuid* GetGuid() { return &LandscapeGuid; }

	// Cross level things...
	virtual void ClearCrossLevelReferences();

#if WITH_EDITOR
	ULandscapeLayerInfoObject* GetLayerInfo(const TCHAR* LayerName, UPackage* Package = NULL, const TCHAR* SourceFilePath = NULL);
	ULandscapeInfo* GetLandscapeInfo(UBOOL bSpawnNewActor = TRUE);

	virtual void PostScriptDestroyed();
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
	virtual void PreSave();
	virtual void InitRBPhysEditor();

	virtual void PreEditUndo();
	virtual void PostEditUndo();
	virtual void PostEditMove(UBOOL bFinished);
	virtual void PostEditImport();

	virtual UMaterialInterface* GetLandscapeMaterial() const;

	// Called before editor copy, TRUE allow export
	virtual UBOOL ShouldExport();
	// Called before editor paste, TRUE allow import
	virtual UBOOL ShouldImport(FString* ActorPropString, UBOOL IsMovingLevel);
	virtual UBOOL GetSelectedComponents(TArray<UObject*>& SelectedObjects);

	void RemoveInvalidWeightmaps();
	void ChangedPhysMaterial();

	virtual void UpdateLandscapeActor(class ALandscape* Landscape, UBOOL bSearchForActor = TRUE);
	UBOOL IsValidLandscapeActor(class ALandscape* Landscape);
	void GetSharedProperties(class ALandscape* Landscape);

	static void RestoreLandscapeAfterSave();

	// [ming@snda
	void PackWeightmaps();
	// ming@snda]
#endif

	virtual FBox GetComponentsBoundingBox(UBOOL bNonColliding=0) const; // oscar@snda

	// UObject interface
	virtual void Serialize(FArchive& Ar);
	virtual void BeginDestroy();
	virtual void PostLoad();

#if !PS3
	void ChangeLODDistanceFactor(FLOAT InLODDistanceFactor);
#endif
}

defaultproperties
{
	Begin Object Name=Sprite
		Sprite=Texture2D'EditorResources.S_Terrain'
	End Object

	DrawScale3D=(X=128.0,Y=128.0,Z=256.0)
	StaticLightingResolution=1.0
	StreamingDistanceMultiplier=1.0
	bEdShouldSnap=True
	bCollideActors=True
	bBlockActors=True
	bWorldGeometry=True
	bStatic=True
	bNoDelete=True
	bHidden=False
	bMovable=False
	bIsProxy=True
	bLockLocation=True
	MaxLODLevel=-1
	bIsSetup=False
	bResetup=False
	bIsMovingToLevel=False
	LODDistanceFactor=1.f
	CollisionMipLevel=0
// NVCHANGE_BEGIN_JC - TESSELLATION ( Landscape Adaptive Tessellation )
	DistToCamForFullTessFactor = 500
	RadiusToFadeOutTessFactor = 800
	MaterialTessFactor = 32
// NVCHANGE_END_JC - TESSELLATION ( Landscape Adaptive Tessellation )
// NVCHANGE_BEGIN_JC - Landscape ( Light Channel )
	// ming@snda
	MaxDrawDistance=6000
	LightingChannels=(Landscape=TRUE,bInitialized=TRUE)
// NVCHANGE_END_JC - Landscape ( Light Channel )

	PickPriority=EPP_Floor	//song@snda
	PickPointPriority=EPPP_Landscape	//song@snda
}
 