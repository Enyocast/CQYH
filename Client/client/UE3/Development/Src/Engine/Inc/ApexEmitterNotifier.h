// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
#ifndef APEX_EMITTER_NOTIFIER_H
#define APEX_EMITTER_NOTIFIER_H

#include "NvApexManager.h"

class ApexEmitterNotifier
#if WITH_APEX_PARTICLES
	: public ApexEditNotify
#endif
{
public:
	ApexEmitterNotifier(class UParticleModuleTypeDataApex &TypeData);
	virtual ~ApexEmitterNotifier();
#if WITH_APEX_PARTICLES
	NxParameterized::Interface * GetNxParameterized(void);

	virtual UBOOL  OnPostPropertyEdit(NxParameterized::Interface *iface,NxParameterized::Handle &handle,const char *tweakable);
	virtual UBOOL  NotifyEditorClosed(NxParameterized::Interface *iface);

	void SetEmitterInstance(class FParticleApexEmitterInstance*	EInst) {EmitterInstance = EInst;}
	void RemoveEmitterInstance() {EmitterInstance = NULL;}
#endif // WITH_APEX_PARTICLES

private:
	class UParticleModuleTypeDataApex &ApexTypeData;
#if WITH_APEX_PARTICLES
	class FParticleApexEmitterInstance*	EmitterInstance;
#endif
};

#endif // APEX_EMITTER_NOTIFIER_H
// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade