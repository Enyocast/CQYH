
class ParticleModuleTypeDataApex extends ParticleModuleTypeDataBase
	native(Particle)
	editinlinenew
	collapsecategories
	hidecategories(Object);

// Embedded IOFX asset...
var() ApexGenericAsset			ApexIOFX;
var() ApexGenericAsset			ApexEmitter;
var() array<MaterialInterface>	Materials;
var() array<StaticMesh>			Meshes;
var() bool						SubUVBlend;
var() int						SubUVStart;
var() int						SubUVCount;
var() int						SubImagesHorizontal;
var() int						SubImagesVertical;
// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
//var native pointer EmitterInstance {struct FParticleEmitterInstance};
var native pointer EmitterNotifier {class ApexEmitterNotifier};
// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade

// NVCHANGE_BEGIN: JCAO - Apex Emitter Asset work with LODs
struct native ApexLODAsset
{
	var() ApexGenericAsset IOFXAsset;
	var() ApexGenericAsset EmitterAsset;
};

var() array<ApexLODAsset> ApexLODAssets;
// NVCHANGE_END: JCAO - Apex Emitter Asset work with LODs

cpptext
{
	virtual FParticleEmitterInstance *CreateInstance(UParticleEmitter *InEmitterParent, UParticleSystemComponent *InComponent);

// NVCHANGE_BEGIN: HL - Apex Emitter Asset Copy
	virtual void CopyAndReplaceApexRefs();
// NVCHANGE_END: HL - Apex Emitter Asset Copy

	virtual void SetToSensibleDefaults(UParticleEmitter* Owner);
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
	virtual void PreEditChange(UProperty* PropertyAboutToChange);
	virtual void FinishDestroy();
	virtual UBOOL IsSprite() { return FALSE; };
	// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
	//virtual FParticleEmitterInstance * GetEmitterInstance() { return EmitterInstance; };
	virtual ApexEmitterNotifier * GetEmitterNotifier() { return EmitterNotifier; };
	// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
	void ConditionalInitialize(void);

	// NVCHANGE_BEGIN: JCAO - Apex Emitter Asset work with LODs
	virtual UParticleModule* GenerateLODModule(UParticleLODLevel* SourceLODLevel, UParticleLODLevel* DestLODLevel, FLOAT Percentage, 
		UBOOL bGenerateModuleData, UBOOL bForceModuleConstruction = FALSE);
	void RemoveLODAsset(INT LODLevelIndex);
	UApexGenericAsset* GetApexLODEmitterAsset(INT LODLevelIndex);
	UApexGenericAsset* GetApexLODIOFXAsset(INT LODLevelIndex);
	// NVCHANGE_END: JCAO - Apex Emitter Asset work with LODs
private:
	void GenerateLODAsset(INT SrcLevel, INT DestLevel);
}

defaultproperties
{
	SubUVBlend = FALSE
	SubUVStart = 0
	SubUVCount = 1
	SubImagesHorizontal = 1
	SubImagesVertical = 1
	EmitterInstance {NULL}
}
