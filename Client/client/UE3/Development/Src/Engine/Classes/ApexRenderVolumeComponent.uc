/**
 * Copyright 1998-2010 Epic Games, Inc. All Rights Reserved.
 */
class ApexRenderVolumeComponent extends PrimitiveComponent
	native
	collapsecategories
	hidecategories(Object)
	editinlinenew;

var   native pointer                            	ApexRenderVolume;
var	  native pointer								ViewRelevance;
	
cpptext
{
	public:
	
	// UPrimitiveComponent interface.
	/**
	 * Creates a proxy to represent the primitive to the scene manager in the rendering thread.
	 * @return The proxy object.
	 */
	virtual FPrimitiveSceneProxy* CreateSceneProxy();
	virtual void UpdateBounds();

	/** 
	 * Retrieves the materials used in this component 
	 * 
	 * @param OutMaterials	The list of used materials.
	 */
	virtual void GetUsedMaterials( TArray<UMaterialInterface*>& OutMaterials ) const; 
	
	void InitRenderVolume(void *apexDestructibleActor,void *apexScene,UBOOL isCrumble);
	void ReleaseRenderVolume(void);
	physx::apex::NxApexRenderable *GetApexRenderable(void) const;
	/** Accesses the scene relevance information for the materials applied to the mesh. */
	FMaterialViewRelevance GetMaterialViewRelevance() const;
	
	virtual void Tick(FLOAT DeltaTime);
	
	virtual UBOOL IsValidComponent() const;
	virtual UBOOL ShouldComponentAddToScene() const;

	
	private:
}
	

defaultproperties
{
	HiddenGame=True
}
