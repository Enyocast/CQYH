/*=============================================================================
	UnStaticMesh.cpp: Static mesh class implementation.
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "EnginePrivate.h"
// #include "EngineDecalClasses.h"
#include "EngineMeshClasses.h"
// #include "EngineParticleClasses.h"
// #include "EngineSoundClasses.h"

#if WITH_EDITOR

extern void AddToRefResList( UObject* obj, TSet<FString>& outResList);
extern void _CollectReferencedResource(UObject* obj, TSet<FString>& outResList);
// 
// void AActor::CollectReferencedResource(TSet<FString>& outResList)
// {
// 	for (INT Index = 0; Index < Components.Num(); Index++)
// 	{
// 		UActorComponent* Component = Components(Index);
// 		if( Component != NULL )
// 		{
// 			Component->CollectReferencedResource(outResList);
// 		}
// 	}
// 	// Iterate over AllComponents array and mark entries as pending kill.
// 	for (INT Index = 0; Index < AllComponents.Num(); Index++)
// 	{
// 		UActorComponent* Component = AllComponents(Index);
// 		if( Component != NULL )
// 		{
// 			Component->CollectReferencedResource(outResList);
// 		}
// 	}
// }
// 
// void UMaterialInterface::CollectReferencedResource(TSet<FString>& outResList)
// {
// 	outResList.Add(this->GetFullName());
// 
// 	TArray<UTexture*> texs;
// 	GetUsedTextures(texs);
// 
// 	for (INT i = 0; i < texs.Num(); ++i)
// 	{
// 		texs(i)->CollectReferencedResource(outResList);
// 	}
// }
// 
// 
// void UPrimitiveComponent::CollectReferencedResource(TSet<FString>& outResList)
// {
// 	TArray<UMaterialInterface*> mats;
// 	GetUsedMaterials(mats);
// 
// 	for (INT i = 0; i < mats.Num(); ++i)
// 	{
// 		if(mats(i))
// 		{
// 			mats(i)->CollectReferencedResource(outResList);
// 		}
// 	}
// }

// void UParticleModuleTypeDataMesh::CollectReferencedResource(TSet<FString>& outResList)
// {
// 	if(Mesh)
// 	{
// 		Mesh->CollectReferencedResource(outResList);
// 	}
// }

void UStaticMesh::CollectReferencedResource(TSet<FString>& outResList)
{
	AddToRefResList(this, outResList);
	for (INT i = 0; i < LODInfo.Num(); ++i)
	{
		for (INT j = 0; j < LODInfo(i).Elements.Num(); ++j)
		{
			UMaterialInterface*	Material = LODInfo(i).Elements(j).Material;
			if(Material)
			{
				//AddToRefResList(Material, outResList);
				_CollectReferencedResource(Material, outResList);
			}
		}
	}
}

void USkeletalMesh::CollectReferencedResource(TSet<FString>& outResList)
{
	AddToRefResList(this, outResList);
	for (INT i = 0; i < Materials.Num(); ++i)
	{
		UMaterialInterface*	Material = Materials(i);
		if(Material)
		{
			//Material->CollectReferencedResource(outResList);
			_CollectReferencedResource(Material, outResList);
		}
	}
}
// 
// void UParticleSystem::CollectReferencedResource(TSet<FString>& outResList)
// {
// 	outResList.Add(this->GetFullName());
// 	for (INT i = 0; i < Emitters.Num(); ++i)
// 	{
// 		UParticleEmitter*	emiter = Emitters(i);
// 		if(emiter)
// 		{
// 			emiter->CollectReferencedResource(outResList);
// 		}
// 	}
// }

// void UParticleSystemComponent::CollectReferencedResource(TSet<FString>& outResList)
// {
// 	if(Template)
// 	{
// 		Template->CollectReferencedResource(outResList);
// 	}
// }
// 
// void USoundNode::CollectReferencedResource(TSet<FString>& outResList)
// {
// 	for (INT i = 0; i < ChildNodes.Num(); ++i)
// 	{
// 		USoundNode*	res = ChildNodes(i);
// 		if(res)
// 		{
// 			res->CollectReferencedResource(outResList);
// 		}
// 	}
// }
// 
// void USoundNodeWave::CollectReferencedResource(TSet<FString>& outResList)
// {
// 	outResList.Add(this->GetFullName());
// }

// void USoundCue::CollectReferencedResource(TSet<FString>& outResList)
// {
// 	if(FirstNode)
// 	{
// 		FirstNode->CollectReferencedResource(outResList);
// 	}
// }

// void USkeletalMeshComponent::CollectReferencedResource(TSet<FString>& outResList)
// {
// 	if(SkeletalMesh)
// 	{
// 		SkeletalMesh->CollectReferencedResource(outResList);
// 	}
// }
// 
// void UStaticMeshComponent::CollectReferencedResource(TSet<FString>& outResList)
// {
// 	if(StaticMesh)
// 	{
// 		StaticMesh->CollectReferencedResource(outResList);
// 	}
// }

// void UTexture::CollectReferencedResource(TSet<FString>& outResList)
// {
// 	outResList.Add(GetFullName());
// }

#endif