class ParticleModuleLocationCrowdSystem extends ParticleModuleLocationBase
	native(Particle)
	editinlinenew
	hidecategories(Object);

var array<Vector>	ParticleLocations;
var array<Vector>	ParticleRotations;

cpptext
{
	virtual void	Update(FParticleEmitterInstance* Owner, INT Offset, FLOAT DeltaTime);
	virtual UINT	RequiredBytes(FParticleEmitterInstance* Owner = NULL);
	virtual void	PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
}

defaultproperties
{
	bSpawnModule=true
	bUpdateModule=true
}