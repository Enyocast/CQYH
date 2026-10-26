#include "stdafx.h"
#include "NPCUtil.h"

#if WITH_EDITOR

TArray<ANPCNewSpawnPoint*> NPCUtil::FindNpcSiblingSpawnPointActors( ANPCNewSpawnPoint* spawnPoint )
{
	TArray<ANPCNewSpawnPoint*> outArr;

	ANPCNewSpawnGroupMediumActor* medGrp = NPCUtil::FindNpcMedSpawnGroupActor(spawnPoint);
	if(medGrp)
	{
		INT siblingIdx = -1;
		for (INT i = 0; i < medGrp->SmallGroupList.Num(); ++i)
		{
			TArrayNoInit<ANPCNewSpawnPoint*>& spawnPoints = medGrp->SmallGroupList(i).SpawnPointList;
			for (INT j = 0; j < spawnPoints.Num(); ++j)
			{
				if(spawnPoints(j) == spawnPoint)
				{
					siblingIdx = i;
					break;
				}
			}
		}

		if(siblingIdx >= 0)
		{
			outArr = medGrp->SmallGroupList(siblingIdx).SpawnPointList;
		}
	}

	return outArr;
}



TArray<ANPCNewSpawnPoint*> NPCUtil::FindNpcSpawnPointActorsInMedGroup( ANPCNewSpawnPoint* spawnPoint )
{
	TArray<ANPCNewSpawnPoint*> outArr;

	ANPCNewSpawnGroupMediumActor* medGrp = NPCUtil::FindNpcMedSpawnGroupActor(spawnPoint);
	if(medGrp)
	{
		for (INT i = 0; i < medGrp->SmallGroupList.Num(); ++i)
		{
			TArrayNoInit<ANPCNewSpawnPoint*>& spawnPoints = medGrp->SmallGroupList(i).SpawnPointList;
			outArr += spawnPoints;
		}
	}

	return outArr;
}

TArray<ANPCNewSpawnPoint*> NPCUtil::FindNpcSpawnPointActorsInMedGroup( ANPCNewSpawnGroupMediumActor* spawnMedGroup )
{
	TArray<ANPCNewSpawnPoint*> outArr;

	for (INT i = 0; i < spawnMedGroup->SmallGroupList.Num(); ++i)
	{
		TArrayNoInit<ANPCNewSpawnPoint*>& spawnPoints = spawnMedGroup->SmallGroupList(i).SpawnPointList;
		outArr += spawnPoints;
	}

	return outArr;
}


ANPCNewSpawnGroupMediumActor* NPCUtil::FindNpcMedSpawnGroupActor( ANPCNewSpawnPoint* spawnPoint )
{
	TObjectIterator<ANPCNewSpawnGroupMediumActor> It;
	for (; It; ++It)
	{
		ANPCNewSpawnGroupMediumActor* medGrp = *It;
		for (INT i = 0; i < medGrp->SmallGroupList.Num(); ++i)
		{
			TArrayNoInit<ANPCNewSpawnPoint*>& spawnPoints = medGrp->SmallGroupList(i).SpawnPointList;
			for (INT j = 0;j < spawnPoints.Num(); ++j)
			{
				if(spawnPoints(j) == spawnPoint)
				{
					return medGrp;
				}
			}
		}
	}

	return NULL;
}

ANPCNewSpawnGroupActor* NPCUtil::FindNpcSpawnGroupActor( ANPCNewSpawnPoint* spawnPoint )
{
	ANPCNewSpawnGroupMediumActor* medGrp = NPCUtil::FindNpcMedSpawnGroupActor(spawnPoint);
	if(medGrp)
	{
		return NPCUtil::FindNpcSpawnGroupActor(medGrp);
	}

	return NULL;
}

ANPCNewSpawnGroupActor* NPCUtil::FindNpcSpawnGroupActor( ANPCNewSpawnGroupMediumActor* spawnMedGroup )
{
	TObjectIterator<ANPCNewSpawnGroupActor> It;
	for (; It; ++It)
	{
		ANPCNewSpawnGroupActor* grp = *It;
		for (INT i = 0; i < grp->MediumGroupList.Num(); ++i)
		{			
			if(grp->MediumGroupList(i) == spawnMedGroup)
			{
				return grp;
			}
		}
	}

	return NULL;
}

TArray<ANPCNewSpawnGroupMediumActor*> NPCUtil::FindNpcSiblingMedSpawnGroupActors( ANPCNewSpawnGroupMediumActor* spawnMedGroup )
{
	TArray<ANPCNewSpawnGroupMediumActor*> outArr;
	ANPCNewSpawnGroupActor* grp = NPCUtil::FindNpcSpawnGroupActor(spawnMedGroup);
	if(grp)
	{
		outArr = grp->MediumGroupList;
	}

	return outArr;
}

TArray<ANPCNewSpawnGroupMediumActor*> NPCUtil::FindNpcChildMedSpawnGroupActors( ANPCNewSpawnGroupActor* spawnGroup )
{
	TArray<ANPCNewSpawnGroupMediumActor*> outArr;
	if(spawnGroup)
	{
		outArr = spawnGroup->MediumGroupList;
	}

	return outArr;
}

ADoodadSpawnGroup* NPCUtil::FindDoodadSpawnGroupActor( ADoodadSpawnPoint* doodadSpawnPoint )
{
	TObjectIterator<ADoodadSpawnGroup> It;
	for (; It; ++It)
	{
		ADoodadSpawnGroup* grp = *It;
		for (INT i = 0; i < grp->DoodadSpawnPoints.Num(); ++i)
		{			
			if(grp->DoodadSpawnPoints(i) == doodadSpawnPoint)
			{
				return grp;
			}
		}
	}
	return NULL;
}

TArray<ADoodadSpawnPoint*> NPCUtil::FindDoodadSiblingSpawnPointActors( ADoodadSpawnPoint* doodadSpawnPoint )
{
	TArray<ADoodadSpawnPoint*> outArr;

	ADoodadSpawnGroup* grp = NPCUtil::FindDoodadSpawnGroupActor(doodadSpawnPoint);
	if(grp)
	{
		outArr = grp->DoodadSpawnPoints;
	}
	return outArr;
}

TArray<ADoodadSpawnPoint*> NPCUtil::FindDoodadChildSpawnPointActors( ADoodadSpawnGroup* doodadSpawnGroup )
{
	TArray<ADoodadSpawnPoint*> outArr;

	if(doodadSpawnGroup)
	{
		outArr = doodadSpawnGroup->DoodadSpawnPoints;
	}
	return outArr;
}

#endif // WITH_EDITOR