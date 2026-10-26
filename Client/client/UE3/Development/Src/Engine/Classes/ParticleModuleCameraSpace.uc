/**
 * ParticleModuleCameraOffset.uc
 * for camera(view) space particle effects
 * ming@snda
 */
class ParticleModuleCameraSpace extends ParticleModuleCameraBase
	native(Particle)
	editinlinenew
	hidecategories(Object);

/** 
 *	The camera-relative bound size(x==y) to apply to sprite location
 */
var(Camera)	float	BoundSize;

/**
*  The quad offset from the camera
*/
var(Camera) float	QuadOffset;

cpptext
{
	/**
	 *	Called on a particle that is freshly spawned by the emitter.
	 *	
	 *	@param	Owner		The FParticleEmitterInstance that spawned the particle.
	 *	@param	Offset		The modules offset into the data payload of the particle.
	 *	@param	SpawnTime	The time of the spawn.
	 */
	virtual void	Spawn(FParticleEmitterInstance* Owner, INT Offset, FLOAT SpawnTime);

	/**
	 *	Called on a particle that is being updated by its emitter.
	 *	
	 *	@param	Owner		The FParticleEmitterInstance that 'owns' the particle.
	 *	@param	Offset		The modules offset into the data payload of the particle.
	 *	@param	DeltaTime	The time since the last update.
	 */
	virtual void	Update(FParticleEmitterInstance* Owner, INT Offset, FLOAT DeltaTime);

	/**
	 *	Returns the number of bytes that the module requires in the particle payload block.
	 *
	 *	@param	Owner		The FParticleEmitterInstance that 'owns' the particle.
	 *
	 *	@return	UINT		The number of bytes the module needs per particle.
	 */
	virtual UINT	RequiredBytes(FParticleEmitterInstance* Owner = NULL);
}

defaultproperties
{
	bSpawnModule=true
	bUpdateModule=true

	BoundSize=3000
	QuadOffset=800
}
