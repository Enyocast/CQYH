/*=============================================================================
	ScenePostProcessing.cpp: Scene post processing implementation.
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "EnginePrivate.h"
#include "ScenePrivate.h"
#include "SceneFilterRendering.h"

/** Initialization constructor. */
FGammaCorrectionPixelShader::FGammaCorrectionPixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
{
	SceneTextureParameter.Bind(Initializer.ParameterMap,TEXT("SceneColorTexture"));
	InverseGammaParameter.Bind(Initializer.ParameterMap,TEXT("InverseGamma"));
	ColorScaleParameter.Bind(Initializer.ParameterMap,TEXT("ColorScale"));
	OverlayColorParameter.Bind(Initializer.ParameterMap,TEXT("OverlayColor"));
}

// FShader interface.
UBOOL FGammaCorrectionPixelShader::Serialize(FArchive& Ar)
{
	UBOOL bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
	Ar << SceneTextureParameter << InverseGammaParameter << ColorScaleParameter << OverlayColorParameter;

	InverseGammaParameter.SetShaderParamName(TEXT("InverseGamma"));
	ColorScaleParameter.SetShaderParamName(TEXT("ColorScale"));
	OverlayColorParameter.SetShaderParamName(TEXT("OverlayColor"));
	return bShaderHasOutdatedParameters;
}

IMPLEMENT_SHADER_TYPE(,FGammaCorrectionPixelShader,TEXT("GammaCorrectionPixelShader"),TEXT("Main"),SF_Pixel,VER_CONTENT_RESAVE_AUGUST_2007_QA_BUILD,0);

// [ming@snda
/** Initialization constructor. */
FGammaCorrectionAndLumPixelShader::FGammaCorrectionAndLumPixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
{
	SceneTextureParameter.Bind(Initializer.ParameterMap,TEXT("SceneColorTexture"));
	InverseGammaParameter.Bind(Initializer.ParameterMap,TEXT("InverseGamma"));
	ColorScaleParameter.Bind(Initializer.ParameterMap,TEXT("ColorScale"));
	OverlayColorParameter.Bind(Initializer.ParameterMap,TEXT("OverlayColor"));
}

// FShader interface.
UBOOL FGammaCorrectionAndLumPixelShader::Serialize(FArchive& Ar)
{
	UBOOL bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
	Ar << SceneTextureParameter << InverseGammaParameter << ColorScaleParameter << OverlayColorParameter;

	InverseGammaParameter.SetShaderParamName(TEXT("InverseGamma"));
	ColorScaleParameter.SetShaderParamName(TEXT("ColorScale"));
	OverlayColorParameter.SetShaderParamName(TEXT("OverlayColor"));
	return bShaderHasOutdatedParameters;
}

IMPLEMENT_SHADER_TYPE(,FGammaCorrectionAndLumPixelShader,TEXT("GammaCorrectionPixelShader"),TEXT("Main"),SF_Pixel,VER_CONTENT_RESAVE_AUGUST_2007_QA_BUILD,0);
// ming@snda]

/** Initialization constructor. */
FGammaCorrectionVertexShader::FGammaCorrectionVertexShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	:	FGlobalShader(Initializer)
{
}

IMPLEMENT_SHADER_TYPE(,FGammaCorrectionVertexShader,TEXT("GammaCorrectionVertexShader"),TEXT("Main"),SF_Vertex,0,0);


extern TGlobalResource<FFilterVertexDeclaration> GFilterVertexDeclaration;

FGlobalBoundShaderState FSceneRenderer::PostProcessBoundShaderState;
// ming@snda
FGlobalBoundShaderState FSceneRenderer::PostProcessWithLumBoundShaderState;

/**
* Finish rendering a view, writing the contents to ViewFamily.RenderTarget.
* @param View - The view to process.
* @param bIgnoreScaling - if true, this will not consider scaling when deciding to early out
*/
void FSceneRenderer::FinishRenderViewTarget(/*const*/ FViewInfo* View, UBOOL bIgnoreScaling, UBOOL bAfterPPResolve)
{
	// If the bUseLDRSceneColor flag is set then that means the final post-processing shader has already renderered to
	// the view's render target and that one of the post-processing shaders has performed the gamma correction,
	// unless the scene needs an upscale in which case LDR scene color needs to be copied to the view's render target.
	if( View->bUseLDRSceneColor 
		&& (!GSystemSettings.NeedsUpscale() || bIgnoreScaling)
		&& !View->Family->bScreenCaptureRenderTarget
		// Also skip the final copy to View.RenderTarget if disabled by the view family
		|| !View->Family->bResolveScene )
	{
		// fix rt resolve bug
		// ming@snda
		// moved to postprocess resolve
		//if( ViewFamily.RenderTarget->GetRenderTargetSurface() == GSceneRenderTargets.GetSceneColorSurface() )
			return;
	}

	//if the shader complexity viewmode is enabled, use that to render to the view's rendertarget
	if (View->Family->ShowFlags & SHOW_ShaderComplexity)
	{
		RenderShaderComplexity(View);
		return;
	}
	//if wireframe viewmode is enabled, attempt to use depth dependent halo post process (perspective view only)
	if ((View->Family->ShowFlags & SHOW_Wireframe) && (View->ViewOrigin.W > 0.0f))
	{
		RenderDepthDependentHalo(View);
	}

	// [ming@snda
	UBOOL OutputLum = FALSE;

	const FPostProcessAA* ObjAA = FPostProcessAA::GetDeferredObject();

	if( ObjAA && ObjAA->IsEnabled( *View ) && !View->Family->bWriteOpacityToAlpha && !GIsEditor )
	{
		GSceneRenderTargets.BeginRenderingSceneColorLDR( RTUsage_FullOverwrite );

		OutputLum = TRUE;
	}
	else
	{
		// Set the view family's render target/viewport.
		RHISetRenderTarget(ViewFamily.RenderTarget->GetRenderTargetSurface(),FSurfaceRHIRef());
	}
	// ming@snda]

#if WITH_MOBILE_RHI
	// Always do a clear to avoid a rendertarget restore
	if ( ViewFamily.bDeferClear || GUsingMobileRHI )
#else
	// Deferred the clear until here so the garbage left in the non rendered regions by the post process effects do not show up
	if ( ViewFamily.bDeferClear )
#endif
	{
		RHIClear(  TRUE, FLinearColor::Black, FALSE, 0.0f, FALSE, 0 );
		ViewFamily.bDeferClear = FALSE;
	}

	SCOPED_DRAW_EVENT(Event)(DEC_SCENE_ITEMS,TEXT("GammaCorrection"));

	RHISetViewport( 0, 0, 0.0f, ViewFamily.RenderTarget->GetSizeX(), ViewFamily.RenderTarget->GetSizeY(), 1.0f);

	// turn off culling and blending
	RHISetRasterizerState(TStaticRasterizerState<FM_Solid,CM_None>::GetRHI());
	RHISetBlendState(TStaticBlendState<>::GetRHI());
		
	// turn off depth reads/writes
	RHISetDepthState(TStaticDepthState<FALSE,CF_Always>::GetRHI());

	TShaderMapRef<FGammaCorrectionVertexShader> VertexShader(GetGlobalShaderMap());
	TShaderMapRef<FGammaCorrectionPixelShader> PixelShader(GetGlobalShaderMap());

	// ming@snda
	TShaderMapRef<FGammaCorrectionAndLumPixelShader> LumPixelShader(GetGlobalShaderMap());

	if( OutputLum )
		SetGlobalBoundShaderState( PostProcessWithLumBoundShaderState, GFilterVertexDeclaration.VertexDeclarationRHI, *VertexShader, *LumPixelShader, sizeof(FFilterVertex), 0, EGST_GammaCorrection);
	else
		SetGlobalBoundShaderState( PostProcessBoundShaderState, GFilterVertexDeclaration.VertexDeclarationRHI, *VertexShader, *PixelShader, sizeof(FFilterVertex), 0, EGST_GammaCorrection);

	FLOAT InvDisplayGamma = 1.0f / ViewFamily.RenderTarget->GetDisplayGamma();

	// Forcibly disable gamma correction if mobile emulation is enabled
	if( GEmulateMobileRendering && !GUseGammaCorrectionForMobileEmulation )
	{
		InvDisplayGamma = 1.0f;
	}

	if (GSystemSettings.NeedsUpscale() && View->bUseLDRSceneColor)
	{
		//don't gamma correct if we are copying from LDR scene color, since the PP effect that copied it there will have already gamma corrected
		InvDisplayGamma = 1.0f;
	}

	if( OutputLum )
	{
		SetPixelShaderValue(
			LumPixelShader->GetPixelShader(),
			LumPixelShader->InverseGammaParameter,
			InvDisplayGamma
			);
		SetPixelShaderValue(LumPixelShader->GetPixelShader(),LumPixelShader->ColorScaleParameter,View->ColorScale);
		SetPixelShaderValue(LumPixelShader->GetPixelShader(),LumPixelShader->OverlayColorParameter,View->OverlayColor);
	}
	else
	{
		SetPixelShaderValue(
			PixelShader->GetPixelShader(),
			PixelShader->InverseGammaParameter,
			InvDisplayGamma
			);
		SetPixelShaderValue(PixelShader->GetPixelShader(),PixelShader->ColorScaleParameter,View->ColorScale);
		SetPixelShaderValue(PixelShader->GetPixelShader(),PixelShader->OverlayColorParameter,View->OverlayColor);
	}

	const FTexture2DRHIRef DesiredSceneColorTexture = GSceneRenderTargets.GetEffectiveSceneColorTexture();

	if (GSystemSettings.NeedsUpscale())
	{
		INT UnscaledViewX = 0;
		INT UnscaledViewY = 0;
		UINT UnscaledViewSizeX = 0;
		UINT UnscaledViewSizeY = 0;

		//convert view constraints to their unscaled versions
		GSystemSettings.UnScaleScreenCoords(
			UnscaledViewX, UnscaledViewY, 
			UnscaledViewSizeX, UnscaledViewSizeY, 
			View->X, View->Y, 
			View->SizeX, View->SizeY);

		if (View->bUseLDRSceneColor)
		{
			//a PP effect has already copied to LDR scene color, so read from that
			if( OutputLum )
			{
				SetTextureParameterDirectly(
					LumPixelShader->GetPixelShader(),
					LumPixelShader->SceneTextureParameter,
					//use linear filtering to get a smoother upsample
					TStaticSamplerState<SF_Bilinear,AM_Clamp,AM_Clamp,AM_Clamp>::GetRHI(),
					GSceneRenderTargets.GetSceneColorLDRTexture()
					);
			}
			else
			{
				SetTextureParameterDirectly(
					PixelShader->GetPixelShader(),
					PixelShader->SceneTextureParameter,
					//use linear filtering to get a smoother upsample
					TStaticSamplerState<SF_Bilinear,AM_Clamp,AM_Clamp,AM_Clamp>::GetRHI(),
					GSceneRenderTargets.GetSceneColorLDRTexture()
					);
			}
		}
		else
		{
			FSamplerStateRHIParamRef SceneTextureSamplerState = TStaticSamplerState<>::GetRHI();
			// Use linear filtering if supported on floating point scene color
			if (GSupportsFPFiltering)
			{
				SceneTextureSamplerState = TStaticSamplerState<SF_Bilinear,AM_Clamp,AM_Clamp,AM_Clamp>::GetRHI();
			}

			//in this case we are copying from HDR scene color to the view's render target
			if( OutputLum )
			{
				SetTextureParameterDirectly(
					LumPixelShader->GetPixelShader(),
					LumPixelShader->SceneTextureParameter,
					SceneTextureSamplerState,
					DesiredSceneColorTexture
					);
			}
			else
			{
				SetTextureParameterDirectly(
					PixelShader->GetPixelShader(),
					PixelShader->SceneTextureParameter,
					SceneTextureSamplerState,
					DesiredSceneColorTexture
					);
			}
		}
		
		if( OutputLum )
		{
			// Draw a quad mapping scene color to the view's render target
			DrawDenormalizedQuad(
				0,0,
				UnscaledViewSizeX,UnscaledViewSizeY,
				View->RenderTargetX,View->RenderTargetY,
				View->RenderTargetSizeX,View->RenderTargetSizeY,
				ViewFamily.RenderTarget->GetSizeX(),ViewFamily.RenderTarget->GetSizeY(),
				GSceneRenderTargets.GetBufferSizeX(),GSceneRenderTargets.GetBufferSizeY()
				);
		}
		else
		{
			// Draw a quad mapping scene color to the view's render target
			DrawDenormalizedQuad(
				UnscaledViewX,UnscaledViewY,
				UnscaledViewSizeX,UnscaledViewSizeY,
				View->RenderTargetX,View->RenderTargetY,
				View->RenderTargetSizeX,View->RenderTargetSizeY,
				ViewFamily.RenderTarget->GetSizeX(),ViewFamily.RenderTarget->GetSizeY(),
				GSceneRenderTargets.GetBufferSizeX(),GSceneRenderTargets.GetBufferSizeY()
				);
		}
	}
	else
	{
		if( OutputLum )
		{
			SetTextureParameterDirectly(
				LumPixelShader->GetPixelShader(),
				LumPixelShader->SceneTextureParameter,
				TStaticSamplerState<>::GetRHI(),
				DesiredSceneColorTexture
				);

			// Draw a quad mapping scene color to the view's render target
			DrawDenormalizedQuad(
				0,0,
				View->SizeX,View->SizeY,
				View->RenderTargetX,View->RenderTargetY,
				View->RenderTargetSizeX,View->RenderTargetSizeY,
				ViewFamily.RenderTarget->GetSizeX(),ViewFamily.RenderTarget->GetSizeY(),
				GSceneRenderTargets.GetBufferSizeX(),GSceneRenderTargets.GetBufferSizeY()
				);
		}
		else
		{
			SetTextureParameterDirectly(
				PixelShader->GetPixelShader(),
				PixelShader->SceneTextureParameter,
				TStaticSamplerState<>::GetRHI(),
				DesiredSceneColorTexture
				);

			// Draw a quad mapping scene color to the view's render target
			DrawDenormalizedQuad(
				View->X,View->Y,
				View->SizeX,View->SizeY,
				View->RenderTargetX,View->RenderTargetY,
				View->RenderTargetSizeX,View->RenderTargetSizeY,
				ViewFamily.RenderTarget->GetSizeX(),ViewFamily.RenderTarget->GetSizeY(),
				GSceneRenderTargets.GetBufferSizeX(),GSceneRenderTargets.GetBufferSizeY()
				);
		}
	}

	// [ming@snda
	if( ObjAA )
	{
		if( ObjAA->IsEnabled( *View ) && !View->Family->bWriteOpacityToAlpha && !GIsEditor )
		{
			if( View->Family->bResolveScene )
			{
				FResolveRect ResolveRect;
				ResolveRect.X1 = View->RenderTargetX;
				ResolveRect.Y1 = View->RenderTargetY;
				ResolveRect.X2 = View->RenderTargetX + View->RenderTargetSizeX;
				ResolveRect.Y2 = View->RenderTargetY + View->RenderTargetSizeY;

				GSceneRenderTargets.FinishRenderingSceneColorLDR( RTUsage_FullOverwrite, ResolveRect );

				// Indicate that from now on the scene color is in an LDR surface.
				View->bUseLDRSceneColor = TRUE; 
			}
		}

		ObjAA->SetDeferredObject();
	}
	// ming@snda]
}
