/*=============================================================================
	ParticleRainStreakEmitterInstance.cpp
	ming@snda
=============================================================================*/

#include "EnginePrivate.h"
#include "EngineParticleClasses.h"
#include "EngineMaterialClasses.h"
#include "EngineAnimClasses.h"
#include "PrimitiveSceneInfo.h"

IMPLEMENT_PARTICLEEMITTERINSTANCE_TYPE(FParticleRainStreakEmitterInstance);

DECLARE_STATS_GROUP(TEXT("RainParticles"),STATGROUP_RainStreakParticles);

FParticleRainStreakEmitterInstance::FParticleRainStreakEmitterInstance() :
	FParticleEmitterInstance()
{
}

FParticleRainStreakEmitterInstance::~FParticleRainStreakEmitterInstance()
{
}

//void FParticleRainStreakEmitterInstance::InitParameters(
//	UParticleEmitter* InTemplate, 
//	UParticleSystemComponent* InComponent,
//	UBOOL bClearResource )
//{
//	FParticleEmitterInstance::InitParameters( InTemplate, InComponent, bClearResource );
//}

/**
*	Retrieves the dynamic data for the emitter
*/
FDynamicEmitterDataBase* FParticleRainStreakEmitterInstance::GetDynamicData(UBOOL bSelected)
{
	UParticleLODLevel* LODLevel = SpriteTemplate->GetCurrentLODLevel(this);
	if (IsDynamicDataRequired(LODLevel) == FALSE)
	{
		return NULL;
	}

	FDynamicRainStreakEmitterData* NewEmitterData = ::new FDynamicRainStreakEmitterData(
		LODLevel->RequiredModule );
	{
		SCOPE_CYCLE_COUNTER(STAT_ParticleMemTime);
		INC_DWORD_STAT(STAT_DynamicEmitterCount);
		INC_DWORD_STAT(STAT_DynamicRainStreakCount);
		INC_DWORD_STAT_BY(STAT_DynamicEmitterMem, sizeof(FDynamicRainStreakEmitterData));
	}

	// Now fill in the source data
	if( !FillReplayData( NewEmitterData->Source ) )
	{
		delete NewEmitterData;
		return NULL;
	}

	// Setup dynamic render data.  Only call this AFTER filling in source data for the emitter.
	NewEmitterData->Init( bSelected );

	return NewEmitterData;
}

/**
*	Updates the dynamic data for the instance
*
*	@param	DynamicData		The dynamic data to fill in
*	@param	bSelected		TRUE if the particle system component is selected
*/
UBOOL FParticleRainStreakEmitterInstance::UpdateDynamicData(FDynamicEmitterDataBase* DynamicData, UBOOL bSelected)
{
	checkf((DynamicData->GetSource().eEmitterType == DET_RainStreak), TEXT("RainStreak::UpdateDynamicData> Invalid DynamicData type!"));

	if (ActiveParticles <= 0)
	{
		return FALSE;
	}

	UParticleLODLevel* LODLevel = SpriteTemplate->GetCurrentLODLevel(this);
	if ((LODLevel == NULL) || (LODLevel->bEnabled == FALSE))
	{
		return FALSE;
	}
	FDynamicRainStreakEmitterData* RainStreakDynamicData = (FDynamicRainStreakEmitterData*)DynamicData;
	// Now fill in the source data
	if( !FillReplayData( RainStreakDynamicData->Source ) )
	{
		return FALSE;
	}

	// Setup dynamic render data.  Only call this AFTER filling in source data for the emitter.
	RainStreakDynamicData->Init( bSelected );

	return TRUE;
}

/**
*	Retrieves replay data for the emitter
*
*	@return	The replay data, or NULL on failure
*/
FDynamicEmitterReplayDataBase* FParticleRainStreakEmitterInstance::GetReplayData()
{
	if (ActiveParticles <= 0)
	{
		return NULL;
	}

	FDynamicEmitterReplayDataBase* NewEmitterReplayData = ::new FDynamicRainStreakEmitterReplayData();
	check( NewEmitterReplayData != NULL );

	if( !FillReplayData( *NewEmitterReplayData ) )
	{
		delete NewEmitterReplayData;
		return NULL;
	}

	return NewEmitterReplayData;
}

/**
*	Retrieve the allocated size of this instance.
*
*	@param	OutNum			The size of this instance
*	@param	OutMax			The maximum size of this instance
*/
void FParticleRainStreakEmitterInstance::GetAllocatedSize(INT& OutNum, INT& OutMax)
{
	INT nSize = sizeof( FParticleRainStreakEmitterInstance );
	INT nActiveParticleDataSize = (ParticleData != NULL) ? 
		(ActiveParticles * ParticleStride) : 0;
	INT nMaxActiveParticleDataSize = (ParticleData != NULL) ? 
		(MaxActiveParticles * ParticleStride) : 0;
	INT nActiveParticleIndexSize = (ParticleIndices != NULL) ? 
		(ActiveParticles * sizeof(WORD)) : 0;
	INT nMaxActiveParticleIndexSize = (ParticleIndices != NULL) ? 
		(MaxActiveParticles * sizeof(WORD)) : 0;

	OutNum = nActiveParticleDataSize + nActiveParticleIndexSize + nSize;
	OutMax = nMaxActiveParticleDataSize + nMaxActiveParticleIndexSize + nSize;
}

/**
* Returns the size of the object/ resource for display to artists/ LDs in the Editor.
*
*	@param	bInExclusiveResourceSizeMode	UObject::GExclusiveResourceSizeMode value
*
* @return size of resource as to be displayed to artists/ LDs in the Editor.
*/
INT FParticleRainStreakEmitterInstance::GetResourceSize(UBOOL bInExclusiveResourceSizeMode)
{
	INT ResSize = 0;
	if (!bInExclusiveResourceSizeMode ||
		(Component && Component->SceneInfo && Component->SceneInfo->Proxy))
	{
		INT MaxActiveParticleDataSize = (ParticleData != NULL) ? (MaxActiveParticles * ParticleStride) : 0;
		INT MaxActiveParticleIndexSize = (ParticleIndices != NULL) ? (MaxActiveParticles * sizeof(WORD)) : 0;
		// Take dynamic data into account as well
		ResSize = sizeof(FDynamicRainStreakEmitterData);
		ResSize += MaxActiveParticleDataSize;								// Copy of the particle data on the render thread
		ResSize += MaxActiveParticleIndexSize;								// Copy of the particle indices on the render thread
		if (DynamicParameterDataOffset == 0)
		{
			ResSize += MaxActiveParticles * sizeof(FParticleRainStreakVertex);		// The vertex data array
		}
		else
		{
			ResSize += MaxActiveParticles * sizeof(FParticleRainStreakVertexDynamicParameter);
		}
	}
	return ResSize;
}

/**
 * Captures dynamic replay data for this particle system.
 *
 * @param	OutData		[Out] Data will be copied here
 *
 * @return Returns TRUE if successful
 */
UBOOL FParticleRainStreakEmitterInstance::FillReplayData( FDynamicEmitterReplayDataBase& OutData )
{
	if( ActiveParticles <= 0 )
		return FALSE;
	if( !FParticleEmitterInstance::FillReplayData( OutData ) )
		return FALSE;

	UParticleLODLevel* LODLevel = SpriteTemplate->GetCurrentLODLevel( this );
	if( LODLevel == NULL || LODLevel->bEnabled == FALSE )
		return FALSE;

	UMaterialInterface* MaterialInst = CurrentMaterial;
	if( !MaterialInst || !MaterialInst->CheckMaterialUsage(MATUSAGE_RainStreak) )
	{
		MaterialInst = GEngine->DefaultMaterial;
	}
	OutData.eEmitterType = DET_RainStreak;

	FDynamicRainStreakEmitterReplayData* NewReplayData = 
		static_cast<FDynamicRainStreakEmitterReplayData*>( &OutData );
	NewReplayData->MaterialInterface = MaterialInst;

	return TRUE;
}