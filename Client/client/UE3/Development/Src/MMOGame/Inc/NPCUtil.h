#pragma once

#if WITH_EDITOR

class NPCUtil
{
public:

	static TArray<ANPCNewSpawnPoint*> FindNpcSiblingSpawnPointActors(ANPCNewSpawnPoint* spawnPoint);
	static TArray<ANPCNewSpawnPoint*> FindNpcSpawnPointActorsInMedGroup(ANPCNewSpawnPoint* spawnPoint);
	static ANPCNewSpawnGroupMediumActor* FindNpcMedSpawnGroupActor(ANPCNewSpawnPoint* spawnPoint);
	static ANPCNewSpawnGroupActor* FindNpcSpawnGroupActor(ANPCNewSpawnPoint* spawnPoint);
	
	static ANPCNewSpawnGroupActor* FindNpcSpawnGroupActor(ANPCNewSpawnGroupMediumActor* spawnMedGroup);
	static TArray<ANPCNewSpawnGroupMediumActor*> FindNpcSiblingMedSpawnGroupActors(ANPCNewSpawnGroupMediumActor* spawnMedGroup);
	static TArray<ANPCNewSpawnPoint*> FindNpcSpawnPointActorsInMedGroup(ANPCNewSpawnGroupMediumActor* spawnMedGroup);

	static TArray<ANPCNewSpawnGroupMediumActor*> FindNpcChildMedSpawnGroupActors(ANPCNewSpawnGroupActor* spawnGroup);


	static ADoodadSpawnGroup* FindDoodadSpawnGroupActor(ADoodadSpawnPoint* doodadSpawnPoint);
	static TArray<ADoodadSpawnPoint*> FindDoodadSiblingSpawnPointActors(ADoodadSpawnPoint* doodadSpawnPoint);
	static TArray<ADoodadSpawnPoint*> FindDoodadChildSpawnPointActors(ADoodadSpawnGroup* doodadSpawnGroup);
};

#endif