#include "..\stdafx.h"
#include "..\MMOFacade.h"
#include "net/message_handler.h"
#include "attribute_def.h"
#include "EnginePrivate.h"
#include "MMOGameClasses.h"
#include "MMOGameUIClasses.h"

IMPLEMENT_CLASS(UMount)


//void UMount::InitMount(class UAvatarData* Mount)
//{
//}
//void UMount::AttachActor(class AMMOActor* InActor)
//{
//
//}

void UMount::RefreshMountAnimSet(class UAvatarData* MountAvatar)
{
	if(MountAvatar != NULL)
	{

		for(INT i = 0; i < MountAvatar->WeaponAnimSetPairs.Num(); ++i)
		{
			if(EWT_Weapon_0 == MountAvatar->WeaponAnimSetPairs(i).WeaponType)
			{
				if(SkelMeshComponent != NULL && MountAvatar->WeaponAnimSetPairs(i).AnimSets.Num() > 0)
				{
					SkelMeshComponent->AnimSets.Remove(0, SkelMeshComponent->AnimSets.Num());
					for(INT j = 0; j < MountAvatar->WeaponAnimSetPairs(i).AnimSets.Num(); ++j)
					{	
						SkelMeshComponent->AnimSets.AddItem(MountAvatar->WeaponAnimSetPairs(i).AnimSets(j));
					}
					SkelMeshComponent->UpdateAnimations();
				}
				break;
			}
		}
	}
}