/*=============================================================================
	RenderResource.cpp: Render resource implementation.
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "EnginePrivate.h"
#include "TessellationRendering.h"

TLinkedList<FRenderResource*>*& FRenderResource::GetResourceList()
{
	static TLinkedList<FRenderResource*>* FirstResourceLink = NULL;
	return FirstResourceLink;
}

void FRenderResource::InitResource()
{
	check(IsInRenderingThread());
	if(!bInitialized)
	{
		ResourceLink = TLinkedList<FRenderResource*>(this);
		ResourceLink.Link(GetResourceList());
		if(GIsRHIInitialized)
		{
			InitDynamicRHI();
			InitRHI();
		}
		bInitialized = TRUE;
	}
}

void FRenderResource::ReleaseResource()
{
	if ( !GIsCriticalError )
	{
		check(IsInRenderingThread());
		if(bInitialized)
		{
			if(GIsRHIInitialized)
			{
				ReleaseRHI();
				ReleaseDynamicRHI();
			}
			ResourceLink.Unlink();
			bInitialized = FALSE;
		}
	}
}

void FRenderResource::UpdateRHI()
{
	check(IsInRenderingThread());
	if(bInitialized && GIsRHIInitialized)
	{
		ReleaseRHI();
		ReleaseDynamicRHI();
		InitDynamicRHI();
		InitRHI();
	}
}

FRenderResource::~FRenderResource()
{
	if (bInitialized && !GIsCriticalError)
	{
		// Deleting an initialized FRenderResource will result in a crash later since it is still linked
		appErrorf(TEXT("An FRenderResource was deleted without being released first!"));
	}
}

void BeginInitResource(FRenderResource* Resource)
{
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
		InitCommand,
		FRenderResource*,Resource,Resource,
		{
			Resource->InitResource();
		});
}

void BeginUpdateResourceRHI(FRenderResource* Resource)
{
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
		UpdateCommand,
		FRenderResource*,Resource,Resource,
		{
			Resource->UpdateRHI();
		});
}

void BeginReleaseResource(FRenderResource* Resource)
{
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
		ReleaseCommand,
		FRenderResource*,Resource,Resource,
		{
			Resource->ReleaseResource();
		});
}

void ReleaseResourceAndFlush(FRenderResource* Resource)
{
	// Send the release message.
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
		ReleaseCommand,
		FRenderResource*,Resource,Resource,
		{
			Resource->ReleaseResource();
		});

	FlushRenderingCommands();
}

/** The global null color vertex buffer, which is set with a stride of 0 on meshes without a color component. */
TGlobalResource<FNullColorVertexBuffer> GNullColorVertexBuffer;

/** The global null shadowmap vertex buffer, which is set with a stride of 0 when needed. */
TGlobalResource<FNullShadowmapVertexBuffer> GNullShadowmapVertexBuffer;

// [ NVCHANGE_BEGIN_JC - TESSELLATION
#if NV_SMOOTH_NORMALS
#define GEOMETRY_TEXTURE_FORMAT  (PF_B32G32R32F)
void FBarycenticsRenderResource::InitDynamicRHI()
{
	UINT elementsNum = (UINT)SmoothNormals.Num();
	if (elementsNum)
	{
		UINT width = Min(elementsNum, (UINT)DISPLACEMENT_NORMALS_TEXTURE_CAPACITY);
		check(width <= 4096);
		UINT height = (UINT)ceil((double)elementsNum / DISPLACEMENT_NORMALS_TEXTURE_CAPACITY);
		check(height <= 4096);

		SmoothNormalsTextureRHIRef = RHICreateTexture2D(
			width, height,
			GEOMETRY_TEXTURE_FORMAT,
			1,
			TexCreate_Uncooked,
			NULL);

		UINT stride = 0;
		void* pData = RHILockTexture2D(SmoothNormalsTextureRHIRef, 0, TRUE, stride, TRUE);
		check(pData);

		if (pData)
		{
			check(stride == (DISPLACEMENT_NORMALS_TEXTURE_CAPACITY * sizeof(FVector)) || (height == 1));
			memcpy(pData, SmoothNormals.GetData(), elementsNum * sizeof(FVector));
			RHIUnlockTexture2D(SmoothNormalsTextureRHIRef, 0, FALSE);
		}
	}

	elementsNum = (UINT)NeighbouringCoords.Num();
	if (elementsNum)
	{
		UINT width = Min(elementsNum, (UINT)NEIGHBOURING_COORDS_TEXTURE_CAPACITY) * 2;
		check(width <= 4096);
		UINT height = (UINT)ceil((double)elementsNum / NEIGHBOURING_COORDS_TEXTURE_CAPACITY);
		check(height <= 4096);

		NeighbouringCoordsTextureRHIRef = RHICreateTexture2D(
			width, height,
			GEOMETRY_TEXTURE_FORMAT,
			1,
			TexCreate_Uncooked,
			NULL);

		UINT stride = 0;
		void* pData = RHILockTexture2D(NeighbouringCoordsTextureRHIRef, 0, TRUE, stride, TRUE);
		check(pData);

		if (pData)
		{
			check(stride == (NEIGHBOURING_COORDS_TEXTURE_CAPACITY * sizeof(FVector) * 2) || (height == 1));
			memcpy(pData, NeighbouringCoords.GetData(), elementsNum * sizeof(FVector));
			RHIUnlockTexture2D(NeighbouringCoordsTextureRHIRef, 0, FALSE);
		}
	}
}

void FBarycenticsRenderResource::ReleaseDynamicRHI()
{
	SmoothNormalsTextureRHIRef.SafeRelease();
	SmoothNormalsTextureRHIRef = 0;
	NeighbouringCoordsTextureRHIRef.SafeRelease();
	NeighbouringCoordsTextureRHIRef = 0;
}
#endif // WITH_D3D11_TESSELLATION
// NVCHANGE_END_JC - TESSELLATION ]