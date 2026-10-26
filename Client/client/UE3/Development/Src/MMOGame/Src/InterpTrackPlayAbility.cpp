#include "stdafx.h"
#include "UnInterpolationHitProxy.h"
#include "AbilityProcessor.h"

IMPLEMENT_CLASS(UInterpTrackPlayAbility);
IMPLEMENT_CLASS(UInterpTrackInstPlayAbility);


STRUCTTRACK_GETNUMKEYFRAMES(UInterpTrackPlayAbility, AbilityTrack)
STRUCTTRACK_GETTIMERANGE(UInterpTrackPlayAbility, AbilityTrack, Time)
STRUCTTRACK_GETTRACKENDTIME(UInterpTrackPlayAbility, AbilityTrack, Time)
STRUCTTRACK_GETKEYFRAMETIME(UInterpTrackPlayAbility, AbilityTrack, Time)
STRUCTTRACK_SETKEYFRAMETIME(UInterpTrackPlayAbility, AbilityTrack, Time, FAbilityTrackKey )
STRUCTTRACK_REMOVEKEYFRAME(UInterpTrackPlayAbility, AbilityTrack )
STRUCTTRACK_DUPLICATEKEYFRAME(UInterpTrackPlayAbility, AbilityTrack, Time, FAbilityTrackKey )
STRUCTTRACK_GETCLOSESTSNAPPOSITION(UInterpTrackPlayAbility, AbilityTrack, Time)

/** Add a new keyframe at the speicifed time. Returns index of new keyframe. */
INT UInterpTrackPlayAbility::AddKeyframe(FLOAT Time, UInterpTrackInst* TrInst, EInterpCurveMode InitInterpMode)
{
	FAbilityTrackKey NewEventKey(EC_EventParm);
	NewEventKey.KeyName = NAME_None;
	NewEventKey.Time = Time;

	// Find the correct index to insert this key.
	INT i=0; for( i=0; i<AbilityTrack.Num() && AbilityTrack(i).Time < Time; i++);
	AbilityTrack.Insert(i);
	AbilityTrack(i) = NewEventKey;

	return i;
}

void UInterpTrackPlayAbility::PreviewUpdateTrack(FLOAT NewPosition, UInterpTrackInst* TrInst)
{
	UInterpGroupInst* GrInst = CastChecked<UInterpGroupInst>( TrInst->GetOuter() );
	USeqAct_Interp* Seq = CastChecked<USeqAct_Interp>( GrInst->GetOuter() );

	// Dont play sounds unless we are preview playback (ie not scrubbing).
	UBOOL bJump = !(Seq->bIsPlaying);
	UpdateTrack(NewPosition, TrInst, bJump);
}


/** 
*	Function which actually updates things based on the new position in the track. 
*  This is called in the game, when USeqAct_Interp is ticked
*  @param bJump	Indicates if this is a sudden jump instead of a smooth move to the new position.
*/
void UInterpTrackPlayAbility::UpdateTrack(FLOAT NewPosition, UInterpTrackInst* TrInst, UBOOL bJump)
{
	UInterpTrackInstPlayAbility* EventInst = CastChecked<UInterpTrackInstPlayAbility>(TrInst);
	UInterpGroupInst* GrInst = CastChecked<UInterpGroupInst>( EventInst->GetOuter() );
	USeqAct_Interp* Seq = CastChecked<USeqAct_Interp>( GrInst->GetOuter() );
	UInterpGroup* Group = CastChecked<UInterpGroup>( GetOuter() );
	UInterpData* IData = CastChecked<UInterpData>( Group->GetOuter() );

	// We'll consider playing events in reverse if we're either actively playing in reverse or if
	// we're in a paused state but forcing an update to an older position (scrubbing backwards in editor.)
	UBOOL bIsPlayingBackwards =
		( Seq->bIsPlaying && Seq->bReversePlayback ) ||
		( bJump && !Seq->bIsPlaying && NewPosition < EventInst->LastUpdatePosition );

	// Find the interval between last update and this to check events with.
	UBOOL bFireEvents = true;

// 	if(bJump)
// 	{
// 		// If we are playing forwards, and the flag is set, fire events even if we are 'jumping'.
// // 		if(bFireEventsWhenJumpingForwards && !bIsPlayingBackwards)
// 		{
// 			bFireEvents = true;
// 		}
// // 		else
// // 		{
// // 			bFireEvents = false;
// // 		}
// 	}

	// If playing sequence forwards.
	FLOAT MinTime, MaxTime;
	if(!bIsPlayingBackwards)
	{
		MinTime = EventInst->LastUpdatePosition;
		MaxTime = NewPosition;

		// Slight hack here.. if playing forwards and reaching the end of the sequence, force it over a little to ensure we fire events actually on the end of the sequence.
		if(MaxTime == IData->InterpLength)
		{
			MaxTime += (FLOAT)KINDA_SMALL_NUMBER;
		}

// 		if(!bFireEventsWhenForwards)
// 		{
// 			bFireEvents = false;
// 		}
	}
	// If playing sequence backwards.
	else
	{
		MinTime = NewPosition;
		MaxTime = EventInst->LastUpdatePosition;

		// Same small hack as above for backwards case.
		if(MinTime == 0.f)
		{
			MinTime -= (FLOAT)KINDA_SMALL_NUMBER;
		}

// 		if(!bFireEventsWhenBackwards)
// 		{
// 			bFireEvents = false;
// 		}
	}

	// If we should be firing events for this track...
	if(bFireEvents)
	{
		// See which events fall into traversed region.
		for(INT i=0; i<AbilityTrack.Num(); i++)
		{
			FLOAT EventTime = AbilityTrack(i).Time;

			// Need to be slightly careful here and make behavior for firing events symmetric when playing forwards of backwards.
			UBOOL bFireThisEvent = false;
// 			if(!bIsPlayingBackwards)
// 			{
// 				if( EventTime >= MinTime && EventTime < MaxTime )
// 				{
// 					bFireThisEvent = true;
// 				}
// 			}
// 			else
			{
				if( EventTime > MinTime && EventTime <= MaxTime )
				{
					bFireThisEvent = true;
				}
			}

			if( bFireThisEvent )
			{
				if(AbilityTrack(i).AbilityTemplate)
				{
					//warnf(NAME_Warning, TEXT("Play Ability:%s"), *AbilityTrack(i).AbilityTemplate->GetMainSpeciality());

					AMMOActorCinematicActor* actor = Cast<AMMOActorCinematicActor>(TrInst->GetGroupActor());
					if (actor)
					{
						// hack: ability weapontype
						actor->CurrentCinematicWeaponType = AbilityTrack(i).WeaponType;
						MMOFacade::getSingleton().GetAbilityProcessor()->PlayClientAbility(actor->ServerID, AbilityTrack(i).AbilityTemplate);
					}
				}
				//Seq->NotifyEventTriggered(this, i);
			}
		}
	}

	// Update LastUpdatePosition.
	EventInst->LastUpdatePosition = NewPosition;
}

/** Get the name of the class used to help out when adding tracks, keys, etc. in UnrealEd.
* @return	String name of the helper class.*/
const FString UInterpTrackPlayAbility::GetEdHelperClassName() const
{
	return FString( TEXT("UnrealEd.InterpTrackPlayAbilityHelper") );
}


void UInterpTrackPlayAbility::DrawTrack( FCanvas* Canvas, UInterpGroup* Group, const FInterpTrackDrawParams& Params )
{
	Super::DrawTrack( Canvas, Group, Params );

#if WITH_EDITORONLY_DATA
	const UBOOL bHitTesting = Canvas->IsHitTesting();
	const UBOOL bAllowTextSelection = bHitTesting && Params.bAllowKeyframeTextSelection;
	
	const FColor NormalBlockColor(0,100,200);
	const INT	KeyVertOffset = 3;
	const FColor KeyLabelColor(225,225,225);

	for(INT i=0; i<AbilityTrack.Num(); i++)
	{
		FLOAT KeyTime = AbilityTrack(i).Time;
		INT PixelPos = appTrunc((KeyTime - Params.StartTime) * Params.PixelsPerSec);

		INT XL, YL;
		FString Str = AbilityTrack(i).KeyName.ToString();
		
		if(AbilityTrack(i).AbilityTemplate)
		{
			//Str += TEXT(" -> ");
			Str += AbilityTrack(i).AbilityTemplate->GetMainSpeciality();
		}
		else
		{
			Str += TEXT("N/A");
		}

		StringSize( GEngine->SmallFont, XL, YL, *Str );

		if ( bAllowTextSelection )
		{
			Canvas->SetHitProxy( new HInterpTrackKeypointProxy( Group, this, i ) );
		}

		FLOAT  SeqStartTime = KeyTime;
		FLOAT SeqEndTime = SeqStartTime;

		if(AbilityTrack(i).AbilityTemplate)
		{
			SeqEndTime = KeyTime + AbilityTrack(i).AbilityTemplate->GetAbilitySpellTime();

			INT StartPixelPos = appTrunc((SeqStartTime - Params.StartTime) * Params.PixelsPerSec);
			INT EndPixelPos = appTrunc((SeqEndTime - Params.StartTime) * Params.PixelsPerSec);

 			DrawTile(Canvas, StartPixelPos+1, KeyVertOffset+1, EndPixelPos - StartPixelPos - 1,
 				appTrunc(Params.TrackHeight - 2.f*KeyVertOffset) - 2, 0.f, 0.f, 1.f, 1.f,  NormalBlockColor);
 
 			DrawLine2D(Canvas, FVector2D((FLOAT)EndPixelPos, KeyVertOffset+1),
 				FVector2D((FLOAT)EndPixelPos, (FLOAT)appTrunc(Params.TrackHeight - 2.f*KeyVertOffset)), FLinearColor(0, 0, 0));

			FLOAT SeqStartTime2 = SeqEndTime;
			FLOAT SeqEndTime2 = SeqStartTime2 + AbilityTrack(i).AbilityTemplate->GetAbilityCastTime();

			StartPixelPos = appTrunc((SeqStartTime2 - Params.StartTime) * Params.PixelsPerSec);
			EndPixelPos = appTrunc((SeqEndTime2 - Params.StartTime) * Params.PixelsPerSec);

			DrawTile(Canvas, StartPixelPos+1, KeyVertOffset+1, EndPixelPos - StartPixelPos - 1,
				appTrunc(Params.TrackHeight - 2.f*KeyVertOffset) - 2, 0.f, 0.f, 1.f, 1.f,  NormalBlockColor);
		}

		DrawShadowedString(Canvas, PixelPos + 2, Params.TrackHeight - YL - KeyVertOffset, *Str, GEngine->SmallFont, KeyLabelColor );
		if ( bAllowTextSelection )
		{
			Canvas->SetHitProxy( NULL );
		}
	}
#endif // WITH_EDITORONLY_DATA
}

/** Get the icon to draw for this track in Matinee. */
UMaterial* UInterpTrackPlayAbility::GetTrackIcon() const
{
	return (UMaterial*)StaticLoadObject( UMaterial::StaticClass(), NULL, TEXT("EditorMaterials.MatineeGroups.MAT_Groups_Event_Mat"), NULL, LOAD_None, NULL );
}

/*-----------------------------------------------------------------------------
	UInterpTrackInstPlayAbility
-----------------------------------------------------------------------------*/

/** Initialise this Track instance. Called in-game before doing any interpolation. */
void UInterpTrackInstPlayAbility::InitTrackInst(UInterpTrack* Track)
{
	Super::InitTrackInst( Track );

	UInterpGroupInst* GrInst = CastChecked<UInterpGroupInst>( GetOuter() );
	USeqAct_Interp* Seq = CastChecked<USeqAct_Interp>( GrInst->GetOuter() );

	LastUpdatePosition = Seq->Position;

	AMMOActorCinematicActor* cinActor = Cast<AMMOActorCinematicActor>(GetGroupActor());
	if(cinActor)
	{
		cinActor->RegistToCharacterMap(TRUE);
		cinActor->GpDataManager = UGamePlayDataManager::GetSingleton();
	}
}

void UInterpTrackInstPlayAbility::TermTrackInst(UInterpTrack* Track)
{
	Super::TermTrackInst(Track);

	AMMOActorCinematicActor* cinActor = Cast<AMMOActorCinematicActor>(GetGroupActor());
	if(cinActor)
	{
		cinActor->RegistToCharacterMap(FALSE);
	}
}