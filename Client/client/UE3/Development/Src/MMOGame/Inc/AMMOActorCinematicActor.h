

#if WITH_EDITOR
virtual void CheckForErrors();
virtual void EditorReplacedActor (AActor* OldActor);
#endif

virtual void GetAnimControlSlotDesc(TArray<struct FAnimSlotDesc>& OutSlotDescs);
virtual void PreviewBeginAnimControl(class UInterpGroup* InInterpGroup);
virtual void PreviewSetAnimPosition(FName SlotName, INT ChannelIndex, FName InAnimSeqName, FLOAT InPosition, UBOOL bLooping, UBOOL bFireNotifies, UBOOL bEnableRootMotion, FLOAT DeltaTime);
virtual void PreviewSetAnimWeights(TArray<FAnimSlotInfo>& SlotInfos);
virtual void PreviewFinishAnimControl(class UInterpGroup* InInterpGroup);
virtual void PreviewSetMorphWeight(FName MorphNodeName, FLOAT MorphWeight);
virtual void PreviewSetSkelControlScale(FName SkelControlName, FLOAT Scale);
virtual void SetSkelControlStrength(FName SkelControlName, FLOAT ControlStrength);

virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

// ming@snda
// fix recording movie bug
virtual void MAT_BeginAnimControl(class UInterpGroup* InInterpGroup);
virtual void MAT_FinishAnimControl(class UInterpGroup* InInterpGroup);

/** Called each from while the Matinee action is running, to set the animation weights for the actor. */
virtual void SetAnimWeights( const TArray<struct FAnimSlotInfo>& SlotInfos );

virtual void AdjustInterpTrackMove(FVector& Pos, FRotator& Rot, FLOAT DeltaTime, UBOOL bIgnoreRotation = FALSE);

virtual void SetVisibleByAbility(UBOOL InVisible);
