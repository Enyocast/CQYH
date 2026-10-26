#include "stdafx.h"
#include "MMOUtil.h"

IMPLEMENT_CLASS(ANPCNewSpawnPoint)

FVector ANPCNewSpawnPoint::GetServerPosition()
{
	FVector result = Location;
	ConvertCoordC2S(result);
	result.X = (INT32)result.X / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
	result.Y = (INT32)result.Y / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
	return result;
}

void ANPCNewSpawnPoint::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

#if WITH_EDITOR
void ANPCNewSpawnPoint::CheckForErrors()
{
	Super::CheckForErrors();
	
	for(TObjectIterator<AMMOVolume_Blocking> it; it; ++it)
	{
		AMMOVolume_Blocking* blockVol = *it;
		if(blockVol->BlockMove)
		{
			if(blockVol->Encompasses(Location))
			{
				GWarn->MapCheck_Add(MCTYPE_ERROR, this, 
					*FString::Printf(LocalizeSecure(LocalizeUnrealEdMMO(TEXT("CheckError_SpawnPointInsideBlockingVolume")), *blockVol->GetFullName())),
					NULL);
				//break;
			}
		}
	}
}
#endif