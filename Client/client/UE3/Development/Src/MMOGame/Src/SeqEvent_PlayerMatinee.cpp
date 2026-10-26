#include "..\stdafx.h"
#include "MMOFacade.h"


IMPLEMENT_CLASS(USeqEvent_PlayerMatineeStop);


void USeqEvent_PlayerMatineeStop::Activated()
{
    if (!GWorld || !GWorld->CurrentLevel)
        return;

	TArray<USeqAct_Interp*> objList = MMO::FindObjectInKisemetByType<USeqAct_Interp>();

	for (INT i = 0; i < objList.Num(); ++i)
	{
        USeqAct_Interp* seqAct = objList(i);

        if (!seqAct->bIsPlaying)
            continue;

        if (!seqAct->bIsSkippable)
            continue;

        const FLOAT RightBeforeEndTime = 0.1f;  // 剩余时间
        const FLOAT InitialNoSkipTime = 0;      // 至少要播放
        if ((seqAct->Position < seqAct->InterpData->InterpLength - RightBeforeEndTime) && 
            (seqAct->Position >= InitialNoSkipTime))
        {
            seqAct->SetPosition(seqAct->InterpData->InterpLength - RightBeforeEndTime, TRUE);

			seqAct->bCanceled = TRUE;//fangruyi
        }
    }
    Super::Activated();
}