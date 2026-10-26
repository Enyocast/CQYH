//=============================================================================
// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
// Confidential.
//=============================================================================
#include "UDKBase.h"

IMPLEMENT_CLASS(AMobileHUDExt);

void AMobileHUDExt::UpdateBenchmarkInformation()
{
#if ANDROID
	extern EAndroidPerformanceLevel GAndroidPerformanceLevel;
	BenchmarkFeatureLevel = (INT) GAndroidPerformanceLevel;
	extern FLOAT GAndroidResolutionScale;
	BenchmarkResolutionScale = GAndroidResolutionScale;
#endif
}

void AMobileHUDExt::SetEngineBenchmarkingMode(UBOOL bIsBenchmarking)
{
	// disable frame rate limiter if benchmarking
	GEngine->bSmoothFrameRate = !bIsBenchmarking;
}

void AMobileHUDExt::UpdateBenchmarkAnalyticsInformation()
{
#if ANDROID
	extern FString GAndroidDeviceModel;
	DeviceModel = GAndroidDeviceModel;
	extern FString GGraphicsRenderer;
	DeviceGPU = GGraphicsRenderer;
	extern FString GGraphicsVendor;
	DeviceGPUVendor = GGraphicsVendor;
#endif
}

// Sets flag that the game will be handling the back button key press
void AMobileHUDExt::NotifyEngineOfBackButtonHandling()
{
#if ANDROID
	extern UBOOL GAndroidHandlesBackButton;
	GAndroidHandlesBackButton = TRUE;
#endif
}

// Checks to see if there is a pending back request, and resets flag if so
UBOOL AMobileHUDExt::HandleBackButtonPressed()
{
#if ANDROID
	extern UBOOL GAndroidBackButtonPressed;
	if (GAndroidBackButtonPressed)
	{
		GAndroidBackButtonPressed = FALSE;
		return TRUE;
	}
#endif
	return FALSE;
}

// Calls JNI function to prompt closure of app
void AMobileHUDExt::RequestExitDialog()
{
#if ANDROID
	extern void CallJava_ShowExitDialog();
	CallJava_ShowExitDialog();
	debugf(TEXT("TRYING TO SHOW EXIT DIALOG"));
#endif
}