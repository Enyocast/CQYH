#include "stdafx.h"
#include "MMOFacade.h"
#include "MMOUtil.h" 

IMPLEMENT_CLASS(AMMOServerToggleActor)
IMPLEMENT_CLASS(AMMOServerToggleDoorActor)
//IMPLEMENT_CLASS(AMMOServerToggleDoorTrigger)

void  AMMOServerToggleActor::TriggerEvent( )
{
    TArray<USequenceObject*> AllSeqEvents;
    USequence* GameSeq;
    USeqEvent_S2C_DoorChange* eventObj;

    for(INT i = 0; i < GWorld->Levels.Num(); ++i )
    {
        GameSeq = GWorld->GetGameSequence( GWorld->Levels( i ) );
        if( GameSeq != NULL )
        {
            for(INT j = 0; j < GameSeq->SequenceObjects.Num(); ++j )
            {
                eventObj = ( USeqEvent_S2C_DoorChange* )  GameSeq->SequenceObjects( j );
                if( eventObj->IsA( USeqEvent_S2C_DoorChange::StaticClass() ) )
                {
                    //eventObj = ( USeqEvent_S2C_DoorChange* ) (AllSeqEvents(i));
                    eventObj->ForceActivateOutput( CurState );
                }
            }

            GameSeq->FindSeqObjectsByClass( USeqEvent_S2C_DoorChange::StaticClass(), AllSeqEvents);
            for ( INT k = 0; k < AllSeqEvents.Num() ; ++k )
            {
                eventObj = ( USeqEvent_S2C_DoorChange* ) ( AllSeqEvents( k ) );
                eventObj->ForceActivateOutput( CurState );
            }
        }
    }

}

void  AMMOServerToggleActor::IniData()
{    
    bool hasAnim = false;

    if( SkeletalMeshComponent == NULL )
        return ;
    if( SkeletalMeshComponent->AnimSets.Num() <= 0 || !SkeletalMeshComponent->AnimSets(0) )
        return;
    for( int i =0; i< SkeletalMeshComponent->AnimSets(0)->Sequences.Num(); ++i )
    {
        AnimSeq = SkeletalMeshComponent->AnimSets(0)->Sequences( i );
        if( AnimSeq->SequenceName == AnimName )
        {
            hasAnim = true;
            break;
        }
    }
    if( !hasAnim )
        return ;

    //Cast<UAnimNodeSequence>( SkeletalMeshComponent->FindAnimNode(TEXT("Action") )
    AnimNodeSeq = Cast<UAnimNodeSequence>( SkeletalMeshComponent->Animations );
	if (AnimNodeSeq == NULL)
	{
		return ;	
	}

    AnimNodeSeq->SetAnim( AnimName );
    /*if ( AnimNodeSeq == NULL && SkeletalMeshComponent->Animations->IsA('AnimTree') )
    {
        AnimNodeSeq = UAnimNodeSequence( UAnimTree( SkeletalMeshComponent->Animations )->Children(0)->Anim);
    }*/

    AnimTime = AnimNodeSeq->GetAnimPlaybackLength();
}

void  AMMOServerToggleActor::SetState( BYTE inState )
{
    //TriggerEvent( );

    CurState = inState;
    
    if( !AnimNodeSeq )
        return;

    switch( inState )
    {
    case ETAS_Closed:
        AnimNodeSeq->SetPosition( 0, true );

        SkeletalMeshComponent->SetRBChannel(RBCC_Pawn);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_Default,TRUE);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_Pawn,TRUE);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_Vehicle,TRUE);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_Untitled1,TRUE);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_Untitled2,TRUE);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_Untitled3,TRUE);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_BlockingVolume,TRUE);

        /*AnimNodeSeq->SetPosition( AnimTime, true );
        AnimNodeSeq->PlayAnim( false,-1.0f, 0.f );*/
        break;
    case ETAS_Opening:
        AnimNodeSeq->SetPosition( 0, true );
        AnimNodeSeq->PlayAnim( false, 1.0f, 0.f );

        break;
    case ETAS_Opened:
        AnimNodeSeq->SetPosition( AnimTime, true );

        SkeletalMeshComponent->SetRBChannel(RBCC_Pawn);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_Default,FALSE);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_Pawn,FALSE);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_Vehicle,FALSE);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_Untitled1,FALSE);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_Untitled2,FALSE);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_Untitled3,FALSE);
        SkeletalMeshComponent->SetRBCollidesWithChannel(RBCC_BlockingVolume,FALSE);

        /*AnimNodeSeq->SetPosition( 0, true );
        AnimNodeSeq->PlayAnim( false, 1.0f, 0.f );*/
        break;
    case ETAS_Closing:

        AnimNodeSeq->SetPosition( AnimTime, true );
        AnimNodeSeq->PlayAnim( false,-1.0f, 0.f );
        //PlayAnim( AnimName,  false, -1.0f, 0.f );
        break;
    default:
        break;
    }
}

