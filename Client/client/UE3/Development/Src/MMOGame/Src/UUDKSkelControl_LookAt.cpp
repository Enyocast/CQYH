#include "stdafx.h"

IMPLEMENT_CLASS(UUDKSkelControl_LookAt)

UBOOL UUDKSkelControl_LookAt::ApplyLookDirectionLimits(FVector& DesiredLookDir, const FVector &CurrentLookDir, INT BoneIndex, USkeletalMeshComponent* SkelComp)
{
	const FRotator BaseLookDirRot = CurrentLookDir.Rotation();
	FRotator DesiredLookDirRot = DesiredLookDir.Rotation();
	FRotator DeltaRot = (DesiredLookDirRot - BaseLookDirRot).GetNormalized();	

	// clamp the delta
	if (bLimitPitch)
	{
		const INT PitchLimitUnr = appTrunc(Abs(PitchLimit) * (65536.f/360.f));
		DeltaRot.Pitch = Clamp(DeltaRot.Pitch, -PitchLimitUnr, PitchLimitUnr);
	}
	if (bLimitYaw)
	{
		const INT YawLimitUnr = appTrunc(Abs(YawLimit) * (65536.f/360.f));
		DeltaRot.Yaw = Clamp(DeltaRot.Yaw, -YawLimitUnr, YawLimitUnr);
	}
	if (bLimitRoll)
	{
		const INT RollLimitUnr = appTrunc(Abs(RollLimit) * (65536.f/360.f));
		DeltaRot.Roll = Clamp(DeltaRot.Roll, -RollLimitUnr, RollLimitUnr);
	}

	// re-apply the clamped delta
	DesiredLookDirRot = BaseLookDirRot + DeltaRot;
	DesiredLookDir = DesiredLookDirRot.Vector();

	// let super do any limiting it wants to as well
	return Super::ApplyLookDirectionLimits(DesiredLookDir, CurrentLookDir, BoneIndex, SkelComp);
}


void UUDKSkelControl_LookAt::DrawSkelControl3D(const FSceneView* View, FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* SkelComp, INT BoneIndex)
{
	if (bShowPerAxisLimits && (bLimitYaw || bLimitPitch || bLimitRoll) )
	{
		// Calculate transform for cone.
		FVector YAxis, ZAxis;
		LimitLookDir.FindBestAxisVectors(YAxis, ZAxis);
		const FVector	ConeOrigin		= SkelComp->SpaceBases(BoneIndex).GetOrigin();
		const FLOAT		MaxAngle1Radians = YawLimit * ((FLOAT)PI/180.f);
		const FLOAT		MaxAngle2Radians = PitchLimit * ((FLOAT)PI/180.f);
		const FMatrix	ConeToWorld		= FScaleMatrix(FVector(30.f)) * FMatrix(LimitLookDir, YAxis, ZAxis, ConeOrigin) * SkelComp->LocalToWorld;

		UMaterialInterface* LimitMaterial = LoadObject<UMaterialInterface>(NULL, TEXT("EditorMaterials.PhAT_JointLimitMaterial"), NULL, LOAD_None, NULL);

		DrawCone(PDI, ConeToWorld, MaxAngle1Radians, MaxAngle2Radians, 40, TRUE, FColor(64,255,64), LimitMaterial->GetRenderProxy(FALSE), SDPG_World);
	}

	Super::DrawSkelControl3D(View, PDI, SkelComp, BoneIndex);
}

void UUDKSkelControl_LookAt::TickSkelControl(FLOAT DeltaSeconds, USkeletalMeshComponent* SkelComp)
{
	// UT version automatically does interpolation
	TargetLocation = VInterpTo(TargetLocation, DesiredTargetLocation, TargetLocationInterpSpeed, DeltaSeconds);

	Super::TickSkelControl(DeltaSeconds, SkelComp);
}