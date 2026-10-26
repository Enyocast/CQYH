/*=============================================================================
	D3D9DrvPrivate.h: Private D3D RHI definitions.
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __D3D9DRVPRIVATE_H__
#define __D3D9DRVPRIVATE_H__

// Definitions.
#define DEBUG_SHADERS 0

// Dependencies
#include "Engine.h"
#include "D3D9Drv.h"

/**
 * The D3D RHI stats.
 */
enum ED3D9RHIStats
{
	STAT_D3D9PresentTime = STAT_D3D9RHIFirstStat,
	STAT_D3D9DrawPrimitiveCalls,
	// oscar@snda
	STAT_D3D9DrawPrimitiveCalls_Particles,
	STAT_D3D9DrawPrimitiveCalls_StaticMesh,
	STAT_D3D9DrawPrimitiveCalls_SkeletalMesh,
	STAT_D3D9DrawPrimitiveCalls_UI,
	STAT_D3D9DrawPrimitiveCalls_OcclusionTest,
	STAT_D3D9DrawPrimitiveCalls_Distortion,
	STAT_D3D9DrawPrimitiveCalls_BinkVideo,
	STAT_D3D9DrawPrimitiveCalls_PostProcess,
	STAT_D3D9DrawPrimitiveCalls_Other,
	// oscar@snda
	STAT_D3D9Triangles,
	// oscar@snda
	STAT_D3D9Triangles_Particles,
	STAT_D3D9Triangles_StaticMesh,
	STAT_D3D9Triangles_SkeletalMesh,
	STAT_D3D9Triangles_UI,
	STAT_D3D9Triangles_OcclusionTest,
	STAT_D3D9Triangles_Distortion,
	STAT_D3D9Triangles_BinkVideo,
	STAT_D3D9Triangles_PostProcess,
	STAT_D3D9Triangles_Other,
	// oscar@snda
	STAT_D3D9Lines,
};

/**
 * Allow for vendor-specific checks for GPU workaround
 */
const DWORD GGPUVendorATI = 0x1002;
const DWORD GGPUVendorNVIDIA = 0x10DE;

extern D3DADAPTER_IDENTIFIER9 GGPUAdapterID;

#endif
