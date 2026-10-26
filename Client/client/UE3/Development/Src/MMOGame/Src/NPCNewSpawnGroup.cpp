#include "stdafx.h"
//#include "MMOGameClasses.h"
#include "MMOUtil.h"
#include "MMOFacade.h"
#include "../../Engine/Src/SceneRenderTargets.h"
#include "EditorSelectedDrawLineSceneProxy.h"

IMPLEMENT_CLASS(ANPCNewSpawnGroupActor)
IMPLEMENT_CLASS(ANPCNewSpawnGroupMediumActor)
IMPLEMENT_CLASS(ANPCNewSpawnGroupEditorActor)
IMPLEMENT_CLASS(UIEditorSelectedDrawLine)


#if WITH_EDITOR
void ANPCNewSpawnGroupActor::CheckForErrors()
{
	for(TObjectIterator<ANPCNewSpawnGroupActor> it; it; ++it)
	{
		ANPCNewSpawnGroupActor* act = *it;
		if(act != this)
		{
			for (INT i = 0; i < MediumGroupList.Num(); ++i)
			{
				for (INT j = 0; j < act->MediumGroupList.Num(); ++j)
				{
					if(MediumGroupList(i) && act->MediumGroupList(j))
					{
						if(MediumGroupList(i) == act->MediumGroupList(j))
						{
							FString msg = FString::Printf(LocalizeSecure(LocalizeUnrealEdMMO(TEXT("CheckError_DuplicateMediumGroupRef")),
								*act->GetFullName(), *GetFullName(), *MediumGroupList(i)->GetFullName()));
							
							GWarn->MapCheck_Add(MCTYPE_ERROR, this, *msg, NULL);
							GWarn->MapCheck_Add(MCTYPE_ERROR, act, *msg, NULL);
						}
					}
				}
			}
		}
	}
}
#endif


#if WITH_EDITOR
void ANPCNewSpawnGroupMediumActor::CheckForErrors()
{
	for(TObjectIterator<ANPCNewSpawnGroupMediumActor> it; it; ++it)
	{
		ANPCNewSpawnGroupMediumActor* act = *it;
		if(act != this)
		{
			for (INT i = 0; i < SmallGroupList.Num(); ++i)
			{				
				for (INT m = 0; m < SmallGroupList(i).SpawnPointList.Num(); ++m)
				{
					for (INT j = 0; j < act->SmallGroupList.Num(); ++j)
					{
						for (INT n = 0; n < act->SmallGroupList(j).SpawnPointList.Num(); ++n)
						{
							if(SmallGroupList(i).SpawnPointList(m) && act->SmallGroupList(j).SpawnPointList(n))
							{
								if(SmallGroupList(i).SpawnPointList(m) == act->SmallGroupList(j).SpawnPointList(n))
								{
									FString msg = FString::Printf(LocalizeSecure(LocalizeUnrealEdMMO(TEXT("CheckError_DuplicateSpawnPointRef")),
										*act->GetFullName(), *GetFullName(), *SmallGroupList(i).SpawnPointList(m)->GetFullName()));
									GWarn->MapCheck_Add(MCTYPE_ERROR, this, *msg, NULL);
									GWarn->MapCheck_Add(MCTYPE_ERROR, act, *msg, NULL);
								}
							}
						}						
					}
				}
			}
		}
	}
}
#endif

//------------------------------------------------------------------------
FVector ANPCNewSpawnGroupEditorActor::GetObjectServerPosition()
{
	FVector result = Location;
	ConvertCoordC2S(result);
	result.X = (INT32)result.X / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
	result.Y = (INT32)result.Y / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
	return result;
}
//------------------------------------------------------------------------
void ANPCNewSpawnGroupActor::DrawEditorDynamicElements(FPrimitiveDrawInterface* PDI,const FSceneView* View,UINT DPGIndex,DWORD Flags)
{
	if(IsSelected())
	{		
		for (INT k = 0; k < MediumGroupList.Num(); ++k)
		{
			ANPCNewSpawnGroupMediumActor* medGrp = MediumGroupList(k);
			if( medGrp != NULL )
			{
				PDI->DrawLine(Location, medGrp->Location,
					FColor(255, 255, 0), SDPG_UnrealEdForeground, 3.0f );
			}
		} // for k
	}
}
//-------------------------------------------------------------------
//song@snda.com
void ANPCNewSpawnGroupActor::SetUniqueID(INT id)
{
	ServerUniqueID = id;
}

INT ANPCNewSpawnGroupActor::GetUniqueID()
{
	return ServerUniqueID;
}
void ANPCNewSpawnGroupActor::InitUniqueID()
{
	const int MaxSize = MAX_NPC_LARGE_GROUP_COUNT;
	bool UniqueIDs[MaxSize];
	memset(UniqueIDs, 0, sizeof(bool)*MaxSize);
	for(TObjectIterator<ANPCNewSpawnGroupActor> it; it; ++it)
	{
		if((*it)->ServerUniqueID > 0 && (*it)->ServerUniqueID < MaxSize/* && !(*it)->bDeleteMe && !(*it)->bPendingDelete*/)
		{
			if ( UniqueIDs[(*it)->ServerUniqueID] )
				(*it)->ServerUniqueID = -1;// to re-arrange
			else
				UniqueIDs[(*it)->ServerUniqueID] = true;
		}
	}

	int nLastIndex = 1;
	for(TObjectIterator<ANPCNewSpawnGroupActor> it; it; ++it)
	{
		if((*it)->ServerUniqueID <= 0)
		{
			int i = nLastIndex;
			for(; i < MaxSize; ++i)
			{
				if(!UniqueIDs[i])
				{
					(*it)->ServerUniqueID = i;
					UniqueIDs[i] = true;

					nLastIndex = i+1;

					break;
				}
			}
			if ( i >= MaxSize )
			{
				appErrorf( TEXT("Too Much ANPCNewSpawnGroupActor! name: %s"), *((*it)->GetName()) );
			}
		}
	}
}
//song@snda.com
//------------------------------------------------------------------------
void ANPCNewSpawnGroupMediumActor::DrawEditorDynamicElements(FPrimitiveDrawInterface* PDI,const FSceneView* View,UINT DPGIndex,DWORD Flags)
{
	if(IsSelected())
	{
		for (INT j = 0; j < SmallGroupList.Num(); ++j)
		{
			FSpawnSmallGroup* smg = &SmallGroupList(j);
			for (INT k = 0; k < smg->SpawnPointList.Num(); ++k)
			{
				ANPCNewSpawnPoint* newSpawnPoint = smg->SpawnPointList(k);
				if( newSpawnPoint != NULL )
				{
					PDI->DrawLine(Location, newSpawnPoint->Location,
						DrawLineColors(j % DrawLineColors.Num()), SDPG_UnrealEdForeground, 3.0f );
				}
			} // for k
		} // for j
	}
}
//-----------------------------------------------------------------------------

void ANPCNewSpawnGroupMediumActor::SetUniqueID(INT id)
{
	ServerUniqueID = id;
}

INT ANPCNewSpawnGroupMediumActor::GetUniqueID()
{
	return ServerUniqueID;
}
//song@snda.com
void ANPCNewSpawnGroupMediumActor::InitUniqueID()
{
	const int MaxSize = MAX_NPC_MEDIUM_GROUP_PER_LARGE_GROUP * MAX_NPC_LARGE_GROUP_COUNT;
	bool UniqueIDs[MaxSize];
	memset(UniqueIDs, 0, sizeof(bool)*MaxSize);
	for(TObjectIterator<ANPCNewSpawnGroupMediumActor> it; it; ++it)
	{
		if((*it)->ServerUniqueID > 0 && (*it)->ServerUniqueID < MaxSize/* && !(*it)->bDeleteMe && !(*it)->bPendingDelete*/)
		{
			if ( UniqueIDs[(*it)->ServerUniqueID] )
				(*it)->ServerUniqueID = -1;// to re-arrange
			else
				UniqueIDs[(*it)->ServerUniqueID] = true;
		}
	}

	int nLastIndex = 1;
	for(TObjectIterator<ANPCNewSpawnGroupMediumActor> it; it; ++it)
	{
		if((*it)->ServerUniqueID <= 0)
		{
			int i = nLastIndex;
			for(; i < MaxSize; ++i)
			{
				if(!UniqueIDs[i])
				{
					(*it)->ServerUniqueID = i;
					UniqueIDs[i] = true;

					nLastIndex = i+1;

					break;
				}
			}
			if ( i >= MaxSize )
			{
				appErrorf( TEXT("Too Much ANPCNewSpawnGroupMediumActor! name: %s"), *((*it)->GetName()) );
			}
		}
	}
}
//song@snda.com
//------------------------------------------------------------------------
// UEditorSelectedDrawLineComponent
//------------------------------------------------------------------------
IMPLEMENT_CLASS(UEditorSelectedDrawLineComponent);


FPrimitiveSceneProxy* UEditorSelectedDrawLineComponent::CreateSceneProxy()
{
	return new EditorSelectedDrawLineSceneProxy(this);
}
//------------------------------------------------------------------------
void UEditorSelectedDrawLineComponent::UpdateBounds()
{
	const FLOAT NewScale = (Owner ? Owner->DrawScale : 1.0f) * 512;
	Bounds = FBoxSphereBounds(GetOrigin(),FVector(NewScale,NewScale,NewScale),appSqrt(3.0f * Square(NewScale)));
}
//------------------------------------------------------------------------