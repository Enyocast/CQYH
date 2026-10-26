// ming@snda

class ParticleModuleTypeDataRainStreak extends ParticleModuleTypeDataBase
	native(Particle)
	editinlinenew
	collapsecategories
	hidecategories(Object);

cpptext
{
	virtual FParticleEmitterInstance* CreateInstance(UParticleEmitter* InEmitterParent, UParticleSystemComponent* InComponent);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
}