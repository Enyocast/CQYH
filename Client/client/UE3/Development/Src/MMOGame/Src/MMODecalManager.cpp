/**
*	MMODecalManager.cpp
*/

#include "stdafx.h"

IMPLEMENT_CLASS(AMMODecalManager)

void AMMODecalManager::UpdateSelectionDecalRotation( AMMOActor* actor )
{
// 	if( actor && SelectionDecal)
// 	{
// 		FVector e = actor->Rotation.Euler();
// 		SelectionDecal->DecalRotation = e.Z;
// 	}
}

void AMMODecalManager::TickSpecial( FLOAT DeltaTime )
{
	Super::TickSpecial( DeltaTime );

// 	if( SelectedActor && SelectionDecal )
// 	{
// 		if (SelectedActor->bDead)
// 		{
// 			if (!SelectionDecal->HiddenGame)
// 			{
// 				SelectionDecal->SetHiddenGame(TRUE);
// 			}
// 		}
// 		else
// 		{
// 			if (SelectionDecal->HiddenGame)
// 			{
// 				SelectionDecal->SetHiddenGame(FALSE);
// 			}
// 			UpdateSelectionDecalRotation( SelectedActor );
// 		}
// 		
// 	}
}