/**
 * Silhouette Effect
 * ming@snda
 */

#include "EnginePrivate.h"
#include "ScenePrivate.h"
#include "SceneFilterRendering.h"

IMPLEMENT_CLASS(USilhouetteEffect);

// vertex shader
class FSilhouettePostProcessVertexShader : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FSilhouettePostProcessVertexShader,Global);

	static UBOOL ShouldCache(EShaderPlatform platform )
	{
		return TRUE;
	}
	static void ModifyCompilationEnvironment(EShaderPlatform platform, FShaderCompilerEnvironment& OutEnvironment)
	{
	}

	FSilhouettePostProcessVertexShader() {}

public:
	FSilhouettePostProcessVertexShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer )
		: FGlobalShader(Initializer)
	{
	}

	virtual UBOOL Serialize(FArchive& Ar)
	{
		return FGlobalShader::Serialize(Ar);
	}
};

IMPLEMENT_SHADER_TYPE(,FSilhouettePostProcessVertexShader,TEXT("SilhouettePostProcessShader"),TEXT("VertexMain"),SF_Vertex,0,0);


//Pixel Down Sample
// class FSilhouettePostProcessDownSamplePixelShader : public FGlobalShader
// {
// 	DECLARE_SHADER_TYPE( FSilhouettePostProcessDownSamplePixelShader, Global );
// 
// 	static UBOOL ShouldCache(EShaderPlatform platform)
// 	{
// 		return TRUE;
// 	}
// 
// 	static void ModifyCompilationEnvironment(EShaderPlatform platform, FShaderCompilerEnvironment& OutEnvironment)
// 	{
// 	}
// 
// 	FSilhouettePostProcessDownSamplePixelShader() {}
// 
// 	FShaderResourceParameter	SilhouetteTex;
// public:
// 	FSilhouettePostProcessDownSamplePixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
// 		: FGlobalShader(Initializer)
// 	{
// 		SilhouetteTex.Bind( Initializer.ParameterMap, TEXT("SilhouetteColorTex"), FALSE ); 
// 	}
// 
// 	virtual UBOOL Serialize(FArchive& Ar)
// 	{
// 		UBOOL bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
// 		Ar << SilhouetteTex;
// 		return bShaderHasOutdatedParameters;
// 	}
// 
// 	void SetParameters( FViewInfo& View )
// 	{
// 		SetTextureParameterDirectly( GetPixelShader(), SilhouetteTex, 
// 			TStaticSamplerState<SF_Point>::GetRHI(), GSceneRenderTargets.GetSilhouetteColorTexture() );
// 	}
// };
// 
// IMPLEMENT_SHADER_TYPE(,FSilhouettePostProcessDownSamplePixelShader,TEXT("SilhouettePostProcessShader"),TEXT("PixelMain"),SF_Pixel,0,0);


//Pixel Blur X Direction
class FSilhouettePostProcessBlurXPixelShader : public FGlobalShader
{
	DECLARE_SHADER_TYPE( FSilhouettePostProcessBlurXPixelShader, Global );

	static UBOOL ShouldCache(EShaderPlatform platform)
	{
		return TRUE;
	}

	static void ModifyCompilationEnvironment(EShaderPlatform platform, FShaderCompilerEnvironment& OutEnvironment)
	{
	}

	FSilhouettePostProcessBlurXPixelShader() {}

	FShaderParameter			InvTex;
	FShaderResourceParameter	SilhouetteTex;
public:
	FSilhouettePostProcessBlurXPixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
		SilhouetteTex.Bind( Initializer.ParameterMap, TEXT("SilhouetteColorTex"), FALSE );
		InvTex.Bind( Initializer.ParameterMap, TEXT("InvTex"), FALSE ); 
	}

	virtual UBOOL Serialize(FArchive& Ar)
	{
		UBOOL bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
		Ar << SilhouetteTex;
		Ar << InvTex;
		return bShaderHasOutdatedParameters;
	}

	void SetParameters( FViewInfo& View )
	{
		SetTextureParameterDirectly( GetPixelShader(), SilhouetteTex, 
			TStaticSamplerState<SF_Bilinear>::GetRHI(), GSceneRenderTargets.GetSilhouetteColorTexture() );

		float invx = 1.f / GSceneRenderTargets.GetSilhouetteBufferSizeX();
		float invy = 1.f / GSceneRenderTargets.GetSilhouetteBufferSizeY();

		FVector2D invTexVec( invx, invy );
		SetShaderValue( GetPixelShader(), InvTex, invTexVec );
	}
};

IMPLEMENT_SHADER_TYPE(,FSilhouettePostProcessBlurXPixelShader,TEXT("SilhouettePostProcessShader"),TEXT("PixelBlurX"),SF_Pixel,0,0);


//Pixel Blur Y Direction
class FSilhouettePostProcessBlurYPixelShader : public FGlobalShader
{
	DECLARE_SHADER_TYPE( FSilhouettePostProcessBlurYPixelShader, Global );

	static UBOOL ShouldCache(EShaderPlatform platform)
	{
		return TRUE;
	}

	static void ModifyCompilationEnvironment(EShaderPlatform platform, FShaderCompilerEnvironment& OutEnvironment)
	{
	}

	FSilhouettePostProcessBlurYPixelShader() {}

	FShaderParameter			InvTex;
	FShaderResourceParameter	SilhouetteTex;
public:
	FSilhouettePostProcessBlurYPixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
		SilhouetteTex.Bind( Initializer.ParameterMap, TEXT("SilhouetteColorTex"), FALSE );
		InvTex.Bind( Initializer.ParameterMap, TEXT("InvTex"), FALSE ); 
	}

	virtual UBOOL Serialize(FArchive& Ar)
	{
		UBOOL bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
		Ar << SilhouetteTex;
		Ar << InvTex;
		return bShaderHasOutdatedParameters;
	}

	void SetParameters( FViewInfo& View )
	{
		SetTextureParameterDirectly( GetPixelShader(), SilhouetteTex, 
			TStaticSamplerState<SF_Bilinear>::GetRHI(),  GSceneRenderTargets.GetSilhouetteBlurColorTexture() );

		float invx = 1.f / GSceneRenderTargets.GetSilhouetteBlurBufferSizeX();
		float invy = 1.f / GSceneRenderTargets.GetSilhouetteBlurBufferSizeY();

		FVector2D invTexVec( invx, invy );
		SetShaderValue( GetPixelShader(), InvTex, invTexVec );
	}
};

IMPLEMENT_SHADER_TYPE(,FSilhouettePostProcessBlurYPixelShader,TEXT("SilhouettePostProcessShader"),TEXT("PixelBlurY"),SF_Pixel,0,0);

// pixel shader
class FSilhouettePostProcessPixelShader : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FSilhouettePostProcessPixelShader,Global);

	static UBOOL ShouldCache(EShaderPlatform platform)
	{
		return TRUE;
	}
	static void ModifyCompilationEnvironment(EShaderPlatform platform, FShaderCompilerEnvironment& OutEnvironment)
	{
	}

	FSilhouettePostProcessPixelShader() {}

	FShaderResourceParameter	SilhouetteTex;
	FShaderResourceParameter	SilhouetteBlurTex;
public:
	FSilhouettePostProcessPixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
		SilhouetteTex.Bind( Initializer.ParameterMap, TEXT("SilhouetteColorTex"), FALSE );
		SilhouetteBlurTex.Bind( Initializer.ParameterMap, TEXT("SilhouetteColorBlurTex"), FALSE );
	}

	virtual UBOOL Serialize(FArchive& Ar)
	{
		UBOOL bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
		Ar << SilhouetteTex;
		Ar << SilhouetteBlurTex;
		return bShaderHasOutdatedParameters;
	}

	void SetParameters( FViewInfo& View )
	{
		SetTextureParameterDirectly( GetPixelShader(), SilhouetteTex, 
			TStaticSamplerState<SF_Bilinear>::GetRHI(), GSceneRenderTargets.GetSilhouetteColorTexture() );

		SetTextureParameterDirectly( GetPixelShader(), SilhouetteBlurTex, 
			TStaticSamplerState<SF_Bilinear>::GetRHI(), GSceneRenderTargets.GetSilhouetteBlurColorTexture() );
	}
};

IMPLEMENT_SHADER_TYPE(,FSilhouettePostProcessPixelShader,TEXT("SilhouettePostProcessShader"),TEXT("PixelMain"),SF_Pixel,0,0);

// scene proxy
class FSilhouettePostProcessSceneProxy : public FPostProcessSceneProxy
{
public:
	FSilhouettePostProcessSceneProxy( const USilhouetteEffect* InEffect )
		:	FPostProcessSceneProxy(InEffect)
	{
		TShaderMapRef<FSilhouettePostProcessVertexShader> vs( GetGlobalShaderMap() );
		TShaderMapRef<FSilhouettePostProcessPixelShader> ps( GetGlobalShaderMap() );
		//TShaderMapRef<FSilhouettePostProcessDownSamplePixelShader> psDownSample( GetGlobalShaderMap() );
		TShaderMapRef<FSilhouettePostProcessBlurXPixelShader> psBlurX( GetGlobalShaderMap() );
		TShaderMapRef<FSilhouettePostProcessBlurYPixelShader> psBlurY( GetGlobalShaderMap() );

		VertexShader = *vs;
		PixelShader = *ps;
		PixelBlurXShader = *psBlurX;
		PixelBlurYShader = *psBlurY;
		//PixelDownSampleShader = *psDownSample;
	}

	UBOOL Render( const FScene* Scene, UINT InDepthPriorityGroup, FViewInfo& View, const FMatrix& CanvasTransform, FSceneColorLDRInfo& LDRInfo )
	{
		SCOPED_DRAW_EVENT(Event)(DEC_SCENE_ITEMS,TEXT("SilhouettePostProcess"));

		if( VertexShader == NULL || PixelShader == NULL || PixelBlurXShader == NULL || PixelBlurYShader == NULL )//|| PixelDownSampleShader == NULL )
			return FALSE;

		if( !View.bRenderedToSilhouetteBuffer )
			return FALSE;

		//begin Down Sample
// 		GSceneRenderTargets.BeginRenderingSilhouettesBlurX();
// 
// 		RHISetViewport( 0.f, 0.f, 0.0f,
// 			GSceneRenderTargets.GetSilhouetteBlurBufferSizeX(), GSceneRenderTargets.GetSilhouetteBlurBufferSizeY(), 1.0f );
// 
// 		RHIClear( TRUE, FLinearColor( 0.f, 0.f, 0.f, 0.f ), FALSE, 1.f, FALSE, 0 );
// 
// 		// set render states
// 		RHISetBlendState( TStaticBlendState<BO_Add,BF_SourceAlpha,BF_InverseSourceAlpha,BO_Add,BF_One,BF_Zero,CF_GreaterEqual,1>::GetRHI() );
// 		RHISetDepthState( TStaticDepthState<FALSE,CF_Always>::GetRHI() );
// 		RHISetColorWriteMask( CW_RGBA );
// 
// 		static FGlobalBoundShaderState BoundShaderStateDownSmaple;
// 		SetGlobalBoundShaderState( BoundShaderStateDownSmaple, GFilterVertexDeclaration.VertexDeclarationRHI, 
// 			VertexShader, PixelDownSampleShader, sizeof( FFilterVertex ) );
// 		PixelDownSampleShader->SetParameters( View );
// 
// 		DrawDenormalizedQuad(
// 			0, 0, GSceneRenderTargets.GetSilhouetteBlurBufferSizeX(), GSceneRenderTargets.GetSilhouetteBlurBufferSizeY(),
// 			0, 0, GSceneRenderTargets.GetSilhouetteBufferSizeX(), GSceneRenderTargets.GetSilhouetteBufferSizeY(), 
// 			GSceneRenderTargets.GetSilhouetteBlurBufferSizeX(), GSceneRenderTargets.GetSilhouetteBlurBufferSizeY(),
// 			GSceneRenderTargets.GetSilhouetteBufferSizeX(),  GSceneRenderTargets.GetSilhouetteBufferSizeY());
// 
// 		GSceneRenderTargets.FinishRenderingSilhouettesBlurX();


		//begin blur X
		GSceneRenderTargets.BeginRenderingSilhouettesBlurX();
		
		RHISetViewport( 0.f, 0.f, 0.0f,
			GSceneRenderTargets.GetSilhouetteBlurBufferSizeX(), GSceneRenderTargets.GetSilhouetteBlurBufferSizeY(), 1.0f );

		RHIClear( TRUE, FLinearColor( 0.f, 0.f, 0.f, 0.f ), FALSE, 1.f, FALSE, 0 );

		// set render states
		RHISetBlendState( TStaticBlendState<BO_Add,BF_SourceAlpha,BF_InverseSourceAlpha,BO_Add,BF_One,BF_Zero,CF_GreaterEqual,1>::GetRHI() );
		RHISetDepthState( TStaticDepthState<FALSE,CF_Always>::GetRHI() );
		RHISetColorWriteMask( CW_RGBA );

		static FGlobalBoundShaderState BoundShaderStateBlurX;
		SetGlobalBoundShaderState( BoundShaderStateBlurX, GFilterVertexDeclaration.VertexDeclarationRHI, 
			VertexShader, PixelBlurXShader, sizeof( FFilterVertex ) );
		PixelBlurXShader->SetParameters( View );

		DrawDenormalizedQuad(
			0, 0, GSceneRenderTargets.GetSilhouetteBlurBufferSizeX(), GSceneRenderTargets.GetSilhouetteBlurBufferSizeY(),
			0, 0, GSceneRenderTargets.GetSilhouetteBufferSizeX(), GSceneRenderTargets.GetSilhouetteBufferSizeY(), 
			GSceneRenderTargets.GetSilhouetteBlurBufferSizeX(), GSceneRenderTargets.GetSilhouetteBlurBufferSizeY(),
			GSceneRenderTargets.GetSilhouetteBufferSizeX(),  GSceneRenderTargets.GetSilhouetteBufferSizeY());

		GSceneRenderTargets.FinishRenderingSilhouettesBlurX();

		//begin blur Y
		GSceneRenderTargets.BeginRenderingSilhouettesBlurY();

		RHISetViewport( 0.f, 0.f, 0.0f,
			GSceneRenderTargets.GetSilhouetteBlurBufferSizeX(), GSceneRenderTargets.GetSilhouetteBlurBufferSizeY(), 1.0f );

		RHIClear( TRUE, FLinearColor( 0.f, 0.f, 0.f, 0.f ), FALSE, 1.f, FALSE, 0 );

		// set render states
		RHISetBlendState( TStaticBlendState<BO_Add,BF_SourceAlpha,BF_InverseSourceAlpha,BO_Add,BF_One,BF_Zero,CF_GreaterEqual,1>::GetRHI() );
		RHISetDepthState( TStaticDepthState<FALSE,CF_Always>::GetRHI() );
		RHISetColorWriteMask( CW_RGBA );

		static FGlobalBoundShaderState BoundShaderStateBlurY;
		SetGlobalBoundShaderState( BoundShaderStateBlurY, GFilterVertexDeclaration.VertexDeclarationRHI, 
			VertexShader, PixelBlurYShader, sizeof( FFilterVertex ) );
		PixelBlurYShader->SetParameters( View );

		DrawDenormalizedQuad(
			0, 0, GSceneRenderTargets.GetSilhouetteBlurBufferSizeX(), GSceneRenderTargets.GetSilhouetteBlurBufferSizeY(),
			0, 0, GSceneRenderTargets.GetSilhouetteBlurBufferSizeX(), GSceneRenderTargets.GetSilhouetteBlurBufferSizeY(),
			GSceneRenderTargets.GetSilhouetteBlurBufferSizeX(),GSceneRenderTargets.GetSilhouetteBlurBufferSizeY(), 
			GSceneRenderTargets.GetSilhouetteBlurBufferSizeX(), GSceneRenderTargets.GetSilhouetteBlurBufferSizeY() );

		GSceneRenderTargets.FinishRenderingSilhouettesBlurY();
		//finish blur~~!!!!

		UBOOL bDirty = TRUE;
		// set render target and viewport
		if( View.bUseLDRSceneColor )
		{
			DWORD UsageFlags = RTUsage_FullOverwrite;
			if( LDRInfo.bAdjustPingPong && (LDRInfo.NumPingPongsRemaining & 1 ) )
			{
				UsageFlags |= RTUsage_DontSwapBuffer;
			}
			if( FinalEffectInGroup && !GSystemSettings.NeedsUpscale() )
			{
				GSceneRenderTargets.BeginRenderingBackBuffer( UsageFlags );
				RHISetViewport( appTrunc( View.X ), appTrunc( View.Y ), 0.0f, 
					appTrunc( View.X + View.SizeX ), appTrunc( View.Y + View.SizeY ), 1.0f );
			}
			else
			{
				GSceneRenderTargets.BeginRenderingSceneColorLDR( UsageFlags );
				RHISetViewport( View.RenderTargetX, View.RenderTargetY, 0.0f, 
					View.RenderTargetX + View.RenderTargetSizeX, View.RenderTargetY + View.RenderTargetSizeY, 1.0f );
			}
		}
		else
		{
			GSceneRenderTargets.BeginRenderingSceneColor( RTUsage_FullOverwrite );
			RHISetViewport( View.RenderTargetX, View.RenderTargetY, 0.0f,
				View.RenderTargetX + View.RenderTargetSizeX, View.RenderTargetY + View.RenderTargetSizeY, 1.0f );
		}

		// set render states
		RHISetBlendState( TStaticBlendState<BO_Add,BF_SourceAlpha,BF_InverseSourceAlpha,BO_Add,BF_One,BF_Zero,CF_GreaterEqual,1>::GetRHI() );
		RHISetDepthState( TStaticDepthState<FALSE,CF_Always>::GetRHI() );
		RHISetColorWriteMask( CW_RGB );

		static FGlobalBoundShaderState BoundShaderState;
		SetGlobalBoundShaderState( BoundShaderState, GFilterVertexDeclaration.VertexDeclarationRHI, 
			VertexShader, PixelShader, sizeof( FFilterVertex ) );
		PixelShader->SetParameters( View );

		const UINT bufSizeX = GSceneRenderTargets.GetBufferSizeX();
		const UINT bufSizeY = GSceneRenderTargets.GetBufferSizeY();

		// draw rect
		DrawDenormalizedQuad(
			View.RenderTargetX, View.RenderTargetY, View.RenderTargetSizeX, View.RenderTargetSizeY,
			0, 0, View.RenderTargetSizeX, View.RenderTargetSizeY,
			View.RenderTargetSizeX, View.RenderTargetSizeY, 
			GSceneRenderTargets.GetSilhouetteBlurBufferSizeX(), GSceneRenderTargets.GetSilhouetteBlurBufferSizeY() );

		RHISetColorWriteMask( CW_RGBA );

		// resolve color
		if( View.bUseLDRSceneColor )
		{
			if( !FinalEffectInGroup || GSystemSettings.NeedsUpscale() )
			{
				GSceneRenderTargets.FinishRenderingSceneColorLDR();
			}
		}
		else
		{
			GSceneRenderTargets.FinishRenderingSceneColor();
		}

		return bDirty;
	}

private:
	FSilhouettePostProcessVertexShader*	VertexShader;
	FSilhouettePostProcessPixelShader* PixelShader;
	//FSilhouettePostProcessDownSamplePixelShader* PixelDownSampleShader;
	FSilhouettePostProcessBlurXPixelShader* PixelBlurXShader;
	FSilhouettePostProcessBlurYPixelShader* PixelBlurYShader;
};

// effect
FPostProcessSceneProxy* USilhouetteEffect::CreateSceneProxy(const FPostProcessSettings* WorldSettings)
{
	return new FSilhouettePostProcessSceneProxy( this );
}

UBOOL USilhouetteEffect::IsShown(const FSceneView* View) const
{
	return GSystemSettings.bDrawSilhouettes && Super::IsShown( View );
}

void USilhouetteEffect::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}