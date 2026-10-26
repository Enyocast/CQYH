/**
 *	PerformanceBalancer.cpp: auto adjust the options to improve user experience
 *	Copyright 1998-2014 Shanda Games, Inc. All Rights Reserved.
 */
#include "stdafx.h"
#include "MMOPerformance.h"
#include "MMOChatManager.h"

extern FLOAT GAverageFPS, GUnit_RenderThreadTime, GUnit_GPUFrameTime, GUnit_GameThreadTime, GUnit_FrameTime;

MMOPerformanceBalancer* Singleton<MMOPerformanceBalancer>::ms_Singleton = NULL;

extern void ClearBloomRenderTarget();

void ResetRenderTarget()
{
	ENQUEUE_UNIQUE_RENDER_COMMAND(
		SceneRenderTargetsUpdateRHICommand,
	{
		GSystemSettings.UpdateSceneRenderTargetsRHI();
	});

	ClearBloomRenderTarget();
}

void AutoLowScaleLevel(bool downScale)
{
#if 1
	
	//if(downScale)
	//{
	//	GSystemSettings.AutoFPSLevel = Clamp(GSystemSettings.AutoFPSLevel - 1, 1, 5);
	//}
	//else
	//{
	//	GSystemSettings.AutoFPSLevel = Clamp(GSystemSettings.AutoFPSLevel + 1, 1, 5);
	//}
	INT newLv = GetFPSLevel(GAverageFPS);

	FString msg;

	if(newLv < GSystemSettings.AutoFPSLevel)
	{
		msg = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.AutoFPS.ScaleDown"));
		downScale = true;
	}
	else if(newLv > GSystemSettings.AutoFPSLevel)
	{
		msg = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.AutoFPS.ScaleUp"));
		downScale = false;
	}

	if(newLv != GSystemSettings.AutoFPSLevel)
	{	
		FlushRenderingCommands();
		GSystemSettings.AutoFPSLevel = newLv;

		ResetRenderTarget();

		SET_WARN_COLOR(COLOR_GREEN);
		warnf(NAME_Log, TEXT("%s [AutoFPS] AvgFPS:%.2f AutoFPSLevel:%d"), (downScale ? TEXT("---") : TEXT("+++")), GAverageFPS, GSystemSettings.AutoFPSLevel);
		CLEAR_WARN_COLOR();

		msg = msg.Replace(TEXT("[XX]"), *appItoa(newLv));
		MMOChatManager::getSingleton().AddChatMessage(ECC_System, msg, TEXT(""));
	}

#else
	INT lowerLv = Clamp(GSystemSettings.CompatLevelComposite - 2, 1, 5);
	GSystemSettings.CompatLevelComposite = lowerLv;
	//GConfig->SetInt(TEXT("AppCompat"), TEXT("CompatLevelComposite"), lowerLv, GEngineIni);
	FString cmdLv = FString(TEXT("SCALE LEVEL")) + appItoa(lowerLv);
	SET_WARN_COLOR(COLOR_GREEN);
	warnf(*(FString(TEXT("Auto adjust:")) + cmdLv));
	CLEAR_WARN_COLOR();
	GEngine->Exec(*cmdLv);
#endif
}

/////////////////////////GameThread///////////////////////////////
// if v < 0, return the original value
INT AdjustSkeletalUpdate(INT v)
{
	return v;
}

INT AdjustLineCheck(INT v)
{
	return v;
}

INT AdjustParticleUpdate(INT v)
{
	return v;
}

INT AdjustSceneLOD(INT v)
{
	return v;
}

INT AdjustMaterialQuality(INT v)
{
	return v;
}

INT AdjustAll(INT v)
{
	if (v == -1)
	{
		return 4;
	}
	else
	{
		FString strConfig(TEXT("Bucket"));
		strConfig += (v + '0');
		GSystemSettings.LoadFromIni(strConfig);
		return v;
	}
}

/////////////////////////RenderThread/////////////////////////////////////


/////////////////////////////GPU///////////////////////////////////////


void MMOPerformanceBalancer::Initialize()
{
	// 1. push all the entry into the _ArrayAllEntry by the order of enum;

	_pArrayAllEntry = new EntryData[BN_COUNT];
	//////////////////////////////////////////////////////////////////////////
	_pArrayAllEntry[SKELETAL_UPDATE].Init(SKELETAL_UPDATE, AdjustSkeletalUpdate);
	_pArrayAllEntry[LINECHECK].Init(LINECHECK, AdjustLineCheck);
	_pArrayAllEntry[PARTICLE_UPDATE].Init(PARTICLE_UPDATE, AdjustParticleUpdate);

	_pArrayAllEntry[SCENE_LOD].Init(SCENE_LOD, NULL);
	_pArrayAllEntry[MATERIAL_QUALITY].Init(MATERIAL_QUALITY, NULL);

	_pArrayAllEntry[BN_ALL].Init(BN_ALL, AdjustAll);


	//////////////////////////////////////////////////////////////////////////
	_ArrayBottleNeckEntry[BOTTLENECK_GAMETHREAD].AddItem(_pArrayAllEntry+SKELETAL_UPDATE);
	_ArrayBottleNeckEntry[BOTTLENECK_GAMETHREAD].AddItem(_pArrayAllEntry+LINECHECK);
	_ArrayBottleNeckEntry[BOTTLENECK_GAMETHREAD].AddItem(_pArrayAllEntry+PARTICLE_UPDATE);
	_ArrayBottleNeckEntry[BOTTLENECK_GAMETHREAD].AddItem(_pArrayAllEntry+BN_ALL);

	//////////////////////////////////////////////////////////////////////////

	_ArrayBottleNeckEntry[BOTTLENECK_RENDERTHREAD].AddItem(_pArrayAllEntry+BN_ALL);

	//////////////////////////////////////////////////////////////////////////
	_ArrayBottleNeckEntry[BOTTLENECK_GPU].AddItem(_pArrayAllEntry+BN_ALL);
}

void MMOPerformanceBalancer::Finalize()
{
	delete [] _pArrayAllEntry;
}


void MMOPerformanceBalancer::OnOptionChanged()
{
	// to do:
}

void MMOPerformanceBalancer::Tick( FLOAT delta )
{
	CTRL_TICK("MMOPerformanceBalancer::Tick");

	if (IsEnable() && EGameState_InGame == MMO::GetCurrentGameState())
	{
		UINT nGameThread = 0;
		UINT nRenderThread = 0;
		UINT nGPU = 0;

		LocateBottleNeck(nGameThread, nRenderThread, nGPU);

		eRankEnum eRanks[BOTTLENECK_COUNT];

		eRanks[BOTTLENECK_GAMETHREAD] = _fpsRecorder[BOTTLENECK_GAMETHREAD].Update((eRankEnum)nGameThread, delta);
		eRanks[BOTTLENECK_RENDERTHREAD] = _fpsRecorder[BOTTLENECK_RENDERTHREAD].Update((eRankEnum)nRenderThread, delta);
		eRanks[BOTTLENECK_GPU] = _fpsRecorder[BOTTLENECK_GPU].Update((eRankEnum)nGPU, delta);

		if (eRanks[BOTTLENECK_GAMETHREAD] != RANK_COUNT || eRanks[BOTTLENECK_RENDERTHREAD] != RANK_COUNT || eRanks[BOTTLENECK_GPU] != RANK_COUNT)
		{
			// sorting ugly
			INT nEntryIndex[BOTTLENECK_COUNT];

			if (eRanks[BOTTLENECK_GAMETHREAD] < eRanks[BOTTLENECK_RENDERTHREAD] && eRanks[BOTTLENECK_GAMETHREAD] < eRanks[BOTTLENECK_GPU])
			{
				nEntryIndex[2] = BOTTLENECK_GAMETHREAD;

				if (eRanks[BOTTLENECK_RENDERTHREAD] < eRanks[BOTTLENECK_GPU])
				{
					nEntryIndex[1] = BOTTLENECK_RENDERTHREAD;
					nEntryIndex[0] = BOTTLENECK_GPU;
				}
				else
				{
					nEntryIndex[0] = BOTTLENECK_RENDERTHREAD;
					nEntryIndex[1] = BOTTLENECK_GPU;
				}
			}
			else if (eRanks[BOTTLENECK_RENDERTHREAD] < eRanks[BOTTLENECK_GPU])
			{
				nEntryIndex[2] = BOTTLENECK_RENDERTHREAD;

				if (eRanks[BOTTLENECK_GAMETHREAD] < eRanks[BOTTLENECK_GPU])
				{
					nEntryIndex[1] = BOTTLENECK_GAMETHREAD;
					nEntryIndex[0] = BOTTLENECK_GPU;
				}
				else
				{
					nEntryIndex[0] = BOTTLENECK_GAMETHREAD;
					nEntryIndex[1] = BOTTLENECK_GPU;
				}
			}
			else
			{
				nEntryIndex[2] = BOTTLENECK_GPU;

				if (eRanks[BOTTLENECK_GAMETHREAD] < eRanks[BOTTLENECK_RENDERTHREAD])
				{
					nEntryIndex[1] = BOTTLENECK_GAMETHREAD;
					nEntryIndex[0] = BOTTLENECK_RENDERTHREAD;
				}
				else
				{
					nEntryIndex[0] = BOTTLENECK_GAMETHREAD;
					nEntryIndex[1] = BOTTLENECK_RENDERTHREAD;
				}
			}

			for (int i = 0; i < BOTTLENECK_COUNT; ++i)
			{
				INT index = nEntryIndex[0];
				Adjust(_ArrayBottleNeckEntry[index], eRanks[index]);
			}

			Apply(_pArrayAllEntry, BN_COUNT);
			
		}
	}
}

void MMOPerformanceBalancer::LocateBottleNeck(UINT& nGameThread, UINT& nRenderThread, UINT& nGPU)
{
	const UINT nRankCount = 4;
	const FLOAT fFeqs[nRankCount] = {1000.0f/20.0f, 1000.0f/30.0f, 1000.0f/45.0f, 1000.0f/60.0f};	// in millisecond

	// gpu
	nGPU = 0;
	for (; nGPU < nRankCount; ++nGPU)
	{
		if (GUnit_GPUFrameTime > fFeqs[nGPU])
			break;
	}

	// game thread
	nGameThread = 0;
	for (; nGameThread < nRankCount; ++nGameThread)
	{
		if (GUnit_GameThreadTime > fFeqs[nGameThread])
			break;
	}

	// render thread
	nRenderThread = 0;
	for (; nRenderThread < nRankCount; ++nRenderThread)
	{
		if (GUnit_RenderThreadTime > fFeqs[nRenderThread])
			break;
	}
}

void MMOPerformanceBalancer::ResetToUserDefine()
{
	RestorDefault(_pArrayAllEntry, BN_COUNT);
}

MMOPerformanceBalancer g_mmoPerfBalancer;


//////////////////////////////////////////////////////////////////////////

MMOMemPerformanceProfiler g_mmoTexturePerfProfiler;

FString GetFolderKey(const FString& filename)
{
	INT n = filename.InStr(TEXT("MMOContent"));
	INT nMaps = filename.InStr(TEXT("Maps"));
	INT nEngine = filename.InStr(TEXT("Engine"));
	if (n >= 0 && filename.Len() > (n + 11))
	{
		FString right = filename.Right(filename.Len() - n - 11);

		n = right.InStr(TEXT("\\"));

		FString key = right.Left(n);

		return key;
	}
	else if(nMaps != INDEX_NONE)
	{		
		return TEXT("Maps");
	}
	else if(nEngine != INDEX_NONE)
	{		
		return TEXT("Engine");
	}
	else
	{		
		return TEXT("Unknown");
	}
}

void MMOMemPerformanceProfiler::OnEntryCreate( eMemPerformanceProfilerType type, const FString& filename, UINT size )
{
	check(type < MPPT_COUNT);
	TMapMemPerf& m = m_memSize[type];

	FString key = GetFolderKey(filename);

	UINT* pSize = m.Find(key);

	if (pSize != NULL)
	{
		*pSize = *pSize + size;
	}
	else
	{
		m.Set(key, size);
	}
}

void MMOMemPerformanceProfiler::OnEntryDestroy( eMemPerformanceProfilerType type, const FString& filename, UINT size )
{
	check(type < MPPT_COUNT);
	TMapMemPerf& m = m_memSize[type];

	FString key = GetFolderKey(filename);

	UINT* pSize = m.Find(key);

	if (pSize != NULL)
	{
		*pSize = *pSize - size;
	}
	else
	{
		//appDebugBreak();
	}
}

INT MMOMemPerformanceProfiler::RenderToScreen(FViewport* Viewport, FCanvas* Canvas, 
	INT X, INT Y, 
	UMemPerformanceProfiler::eMemPerformanceProfilerType type)
{
#if CONSOLE
	UFont* Font = GEngine->MediumFont;
#else
	UFont* Font = GEngine->SmallFont;
#endif

	const INT RowHeight = appTrunc( Font->GetMaxCharHeight() * 1.1f );
	FLOAT totalSz = 0.0f;

	check(type < MPPT_COUNT);
	TMapMemPerf& m = m_memSize[type];

	const INT XTextOffset = 150;
	const INT XPercentTextOffset = 250;

	for(TMapMemPerf::TConstIterator PairIt(m); PairIt; ++PairIt)
	{
		const FString& Name = PairIt.Key();
		UINT Var = PairIt.Value();
		totalSz += Var;
	}

	for(TMapMemPerf::TConstIterator PairIt(m); PairIt; ++PairIt)
	{
		const FString& Name = PairIt.Key();
		UINT Var = PairIt.Value();

		DrawShadowedString(
			Canvas,
			X,
			Y,
			*FString::Printf(TEXT("%-30s"), *Name),
			Font,
			FColor(30,144,255)
			);

		DrawShadowedString(
			Canvas,
			X + XTextOffset,
			Y,
			*FString::Printf(TEXT("%-7.2f MB"), FLOAT(Var) / 1024.0f / 1024.0f),
			Font,
			FColor(30,144,255)
			);

		DrawShadowedString(
			Canvas,
			X + XPercentTextOffset,
			Y,
			*FString::Printf(TEXT("%3.2f%%"), FLOAT(Var) / totalSz * 100.0f),
			Font,
			FColor(30,144,255)
			);

		Y += RowHeight;
	}

	DrawShadowedString(
		Canvas,
		X,
		Y,
		*FString::Printf(TEXT("%-30s"), TEXT("Total")),
		Font,
		FColor(30,144,255)
		);

	DrawShadowedString(
		Canvas,
		X + XTextOffset,
		Y,
		*FString::Printf(TEXT("%7.2f MB"), FLOAT(totalSz) / 1024.0f / 1024.0f),
		Font,
		FColor(30,144,255)
		);

	// Draw the memory summary stats.
	
	return Y;
}
