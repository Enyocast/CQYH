#include "EnginePrivate.h"
#include "MMOEngineUtil.h"

#if M_DEBUG_RENDER_CALLSTACK

#ifdef _DEBUG
#	define M_DEBUG_SIZE_CALC 0
#	define M_TRACE_RES 0
#else
#	define M_DEBUG_SIZE_CALC 0
#	define M_TRACE_RES 0
#endif

FResLoadingCallStack g_resLoadingCallStackTrace;
FResLoadingCallStack g_renderingCallStackTrace;

#if M_DEBUG_SIZE_CALC
FResLoadingCallStack* g_debugStack = NULL;
#endif

bool g_enableResLoadingCallStackTrace = false;
bool g_enableRenderingCallStackTrace = false;
INT g_capRenderCallStackCount = 1;

bool g_enableRenderingDrawCallStackTrace = false;
INT g_capRenderDrawCallStackCount = 1;


void __CalcResSize(FResLoadingCallStack* parent);

//------------------------------------------------------------------------------------------------
// Resource loading call stack
//------------------------------------------------------------------------------------------------
void RecordCallStack_ResLoading( const FString& resPath, const FString& resTypeName, INT resSz)
{
	if(!g_enableResLoadingCallStackTrace)
	{
		return;
	}

	_RecordResLoadingCallStack(resPath, resTypeName, resSz, &g_resLoadingCallStackTrace, ERLCST_Resource, ERLCST_ResourceFunction);
}

void SaveCallStack_ResLoading()
{
	_SaveResourceLoadingCallStack(&g_resLoadingCallStackTrace, M_RES_LOADING_FILE);
}

void ResetCallStack_ResLoading()
{
	_ResetLoadingCallStackRecord(&g_resLoadingCallStackTrace);
}

//------------------------------------------------------------------------------------------------
// Render command commit call stack
//------------------------------------------------------------------------------------------------
void RecordCallStack_Rendering( const FString& resPath, const FString& resTypeName, INT resSz)
{
	if(!g_enableRenderingCallStackTrace)
	{
		return;
	}

	_RecordResLoadingCallStack(resPath, resTypeName, resSz, &g_renderingCallStackTrace, ERLCST_Count, ERLCST_CountFunction);
}

void SaveCallStack_Rendering()
{
	if(g_enableRenderingCallStackTrace)
	{
		FString fileName = FString::Printf(TEXT("%d.%s"), g_capRenderCallStackCount, M_RENDER_COMMAND_CALLSTACK_FILE);

		_SaveResourceLoadingCallStack(&g_renderingCallStackTrace, *fileName);
		ResetCallStack_Rendering();

		if(--g_capRenderCallStackCount <= 0)
		{
			g_enableRenderingCallStackTrace = false;
		}
	}
}

void ResetCallStack_Rendering()
{
	_ResetLoadingCallStackRecord(&g_renderingCallStackTrace);
}

//------------------------------------------------------------------------------------------------
// Draw Call callstack
//------------------------------------------------------------------------------------------------
void RecordCallStack_DrawCall( const FString& resPath, const FString& resTypeName, INT resSz)
{
	if(!g_enableRenderingDrawCallStackTrace)
	{
		return;
	}

	_RecordResLoadingCallStack(resPath, resTypeName, resSz, &g_renderingCallStackTrace, ERLCST_Count, ERLCST_CountFunction);
}

void SaveCallStack_DrawCall()
{
	if(g_enableRenderingDrawCallStackTrace)
	{
		FString fileName = FString::Printf(TEXT("%d.%s"), g_capRenderDrawCallStackCount, M_RENDER_COMMAND_CALLSTACK_FILE);

		_SaveResourceLoadingCallStack(&g_renderingCallStackTrace, *fileName);
		ResetCallStack_Rendering();

		if(--g_capRenderDrawCallStackCount <= 0)
		{
			g_enableRenderingDrawCallStackTrace = false;
		}
	}
}

void ResetCallStack_DrawCall()
{
	_ResetLoadingCallStackRecord(&g_renderingCallStackTrace);
}

//------------------------------------------------------------------------------------------------

void __RecordResLoadingCallStack( const FString& resPath, const FString& resTypeName, INT resSz, const TArray<FString>& src, INT curIdx, FResLoadingCallStack* parent, FResLoadingCallStack* rootCallStack, EResLoadingCallStackType dataType, EResLoadingCallStackType funType )
{
	if(curIdx == 0)
	{
		FResLoadingCallStack* resNode = new FResLoadingCallStack();
		resNode->DisplayText = resPath;
		resNode->ResLoadingCallStackType = dataType;
		resNode->ResSize = resSz;
		resNode->ResTypeName = resTypeName;
		parent->Links.AddItem(resNode);
		return;
	}

	const FString& callStackStr = src(curIdx);
	FResLoadingCallStack* thisNode = parent->FindChildren(callStackStr);
	if(!thisNode)
	{
		thisNode = new FResLoadingCallStack();
		thisNode->DisplayText = callStackStr;
		thisNode->ResLoadingCallStackType = funType;
		parent->Links.AddItem(thisNode);
	}

	__RecordResLoadingCallStack(resPath, resTypeName, resSz, src, curIdx - 1, thisNode, rootCallStack, dataType, funType);
}

void _RecordResLoadingCallStack( const FString& resPath, const FString& resTypeName, INT resSz, FResLoadingCallStack* rootCallStack, EResLoadingCallStackType dataType, EResLoadingCallStackType funType )
{
#if M_DEBUG_SIZE_CALC
	_LoadResourceLoadingCallStack(M_RES_LOADING_FILE);
#endif

#if M_TRACE_RES
	if(resPath == TEXT("UI_Texture.Img_WindowNormal"))
	{
		appDebugBreak();
	}
#endif

	// Initialize stack walking... loads up symbol information.
	appInitStackWalking();

	// Capture C++ callstack
	const UINT MaxDepth = 200;
	QWORD FullBackTrace[MaxDepth];
	memset( FullBackTrace, 0, sizeof(FullBackTrace) );
	appCaptureStackBackTrace( FullBackTrace, MaxDepth );

	TArray<FString> CallStackList;

	FString tmpStr;

	// Iterate over all addresses in the callstack to look up symbol name. Skipping 2 first entries.
	for( INT AddressIndex=1; AddressIndex<ARRAY_COUNT(FullBackTrace) && FullBackTrace[AddressIndex]; AddressIndex++ )
	{
		ANSICHAR AddressInformation[512];
		AddressInformation[0] = 0;
		appProgramCounterToHumanReadableString( FullBackTrace[AddressIndex], AddressInformation, ARRAY_COUNT(AddressInformation)-1, VF_DISPLAY_BASIC );
		FString CallStackString = FString(AddressInformation);
		if(!CallStackString.IsEmpty())
		{
			CallStackList.AddItem(CallStackString);
			tmpStr += CallStackString + TEXT("\r\n");
		}
	}

	//debugf(TEXT("%s\r\n%s"), *resPath, *tmpStr);

	__RecordResLoadingCallStack(resPath, resTypeName, resSz, CallStackList, CallStackList.Num() - 1, rootCallStack, rootCallStack, dataType, funType);
}

void __CalcResSize(FResLoadingCallStack* parent)
{
#if M_DEBUG_SIZE_CALC
	if(parent == g_debugStack)
	{
		appDebugBreak();
	}
#endif

	if(parent->Links.Num())
	{
		for (INT i = 0; i < parent->Links.Num(); ++i)
		{
			__CalcResSize(parent->Links(i));
			parent->ResSize += parent->Links(i)->ResSize;
		}
	}
}

void _SaveResourceLoadingCallStack(FResLoadingCallStack* rootCallStack, const TCHAR* fileName)
{
	FString path = appGameLogDir() + fileName;
	FArchive* ar = GFileManager->CreateFileWriter(*path);
	rootCallStack->Serialze(*ar);
	ar->Flush();
	ar->Close();
	delete ar;

	SET_WARN_COLOR(COLOR_PURPLE);
	warnf(TEXT("Saved callstack file:%s"), *path);
	CLEAR_WARN_COLOR();
}

bool CompareResLoadingCallStack(FResLoadingCallStack* lhs, FResLoadingCallStack* rhs)
{
	if(lhs->ResSize > rhs->ResSize)
	{
		return true;
	}

	return false;
}


void __SortResLoadingCallStack(FResLoadingCallStack* stk)
{
	for (INT i = 0; i < stk->Links.Num(); ++i)
	{
		__SortResLoadingCallStack(stk->Links(i));
	}

	if(stk->Links.Num() > 1)
	{
		std::sort(&stk->Links(0), &stk->Links(stk->Links.Num() - 1), CompareResLoadingCallStack);
	}
}

void __SetupResLoadingCallStackDeepth(FResLoadingCallStack* stk, INT deepth)
{
	stk->Deepth = deepth;

	for (INT i = 0; i < stk->Links.Num(); ++i)
	{
		__SetupResLoadingCallStackDeepth(stk->Links(i), deepth + 1);
	}
}


FResLoadingCallStack* _LoadResourceLoadingCallStack(const TCHAR* fileName)
{
	FResLoadingCallStack* stk = new FResLoadingCallStack();
	FString path = appGameLogDir() + fileName;
	FArchive* ar = GFileManager->CreateFileReader(*path);
	stk->Serialze(*ar);
	ar->Close();
	delete ar;

#if M_DEBUG_SIZE_CALC
	g_debugStack = stk;
#endif
	__CalcResSize(stk);
	__SortResLoadingCallStack(stk);
	__SetupResLoadingCallStackDeepth(stk, 0);

	return stk;
}

void _ResetLoadingCallStackRecord(FResLoadingCallStack* rootCallStack)
{
	rootCallStack->Links.Empty();
}

#endif

///////////////////////zhaojun@snda////////////////////////////

UMemPerformanceProfiler* g_MemPerformanceProfiler = NULL;

void SetMemPerformanceProfiler(UMemPerformanceProfiler* v)
{
	g_MemPerformanceProfiler = v;
}

UMemPerformanceProfiler* GetMemPerformanceProfiler()
{
	return g_MemPerformanceProfiler;
}


///////////////////////zhaojun@snda////////////////////////////