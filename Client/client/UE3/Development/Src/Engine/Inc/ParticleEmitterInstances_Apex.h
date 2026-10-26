
#ifndef PARTICLE_EMITTER_INSTANCES_APEX_H
#define PARTICLE_EMITTER_INSTANCES_APEX_H

#if WITH_APEX_PARTICLES

#include "NvApexManager.h"

class FParticleApexEmitterInstance : public FParticleEmitterInstance, public ApexEditNotify
{
	friend class FDynamicApexEmitterDataBase;
public:
	DECLARE_PARTICLEEMITTERINSTANCE_TYPE(FParticleApexEmitterInstance, FParticleEmitterInstance);

	/** Constructor	*/
	FParticleApexEmitterInstance(class UParticleModuleTypeDataApex &TypeData);

	/** Destructor	*/
	virtual ~FParticleApexEmitterInstance(void);

	virtual void Tick(FLOAT DeltaTime, UBOOL bSuppressSpawning);

	/** Forwards call to correspnding FParticleMeshPhysXEmitterRenderInstance object. */
	virtual FDynamicEmitterDataBase* GetDynamicData(UBOOL bSelected);

	class FApexEmitter * GetApexEmitter(void) const { return ApexEmitter; };
	// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
	//NxParameterized::Interface * GetNxParameterized(void);
	// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade

	virtual void RemovedFromScene();

	void UpdateBoundingBox(FLOAT DeltaTime);

	virtual void Init();

	virtual UBOOL  OnPostPropertyEdit(NxParameterized::Interface *iface,NxParameterized::Handle &handle,const char *tweakable);
	virtual UBOOL  NotifyEditorClosed(NxParameterized::Interface *iface);
	// NVCHANGE_BEGIN: JCAO - Apex Emitter Asset work with LODs
	virtual void SetCurrentLODIndex(INT InLODIndex, UBOOL bInFullyProcess);
	// NVCHANGE_END: JCAO - Apex Emitter Asset work with LODs
	virtual UBOOL HasCompleted();
	// NVCHANGE_BEGIN: JCAO - Add interface to control the rate of Apex Emitter
	virtual void SetRate(FLOAT MinRate, FLOAT MaxRate);
	// NVCHANGE_END: JCAO - Add interface to control the rate of Apex Emitter
	FCriticalSection& GetCriticalSection()
	{
		return CriticalSection;
	}

private:

	void InitDependencies(UBOOL IsChangeEvent);

	FRBPhysScene *GetScene(void);

	class UParticleModuleTypeDataApex &ApexTypeData;

	class FApexEmitter                *ApexEmitter;

	class FRBPhysScene                *CascadeScene;

	// NVCHANGE_BEGIN: LRR - Update APEX Scene with the view and projection matrices when in cascade
	FMatrix                            ViewMatrix;
	FMatrix                            ProjectionMatrix;
	FLOAT                              FOV;
	FLOAT                              SizeX;
	FLOAT                              SizeY;
	// NVCHANGE_END: LRR - Update APEX Scene with the view and projection matrices when in cascade
	// NVCHANGE_BEGIN: JCAO - Fix safe release Apex Emitter
	UINT								DeferredActions;
	class FIApexScene					*ApexSceneHolder;
	enum
	{
		DEFERRED_RELEASE_EMITTER = 0x01,
		DEFERRED_RELEASE_SCENE = 0x02,
	};
	// NVCHANGE_END: JCAO - Fix safe release Apex Emitter

	FCriticalSection					CriticalSection;
};




#endif // #if WITH_APEX_PARTICLES

#endif
