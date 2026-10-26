
#ifndef _MMOENGINEUTIL_HEADER_
#define _MMOENGINEUTIL_HEADER_

#if M_DEBUG_RENDER_CALLSTACK

#define M_RES_LOADING_FILE TEXT("resloading.callstack")
#define M_RENDER_COMMAND_CALLSTACK_FILE TEXT("rendering.callstack")

extern bool g_enableResLoadingCallStackTrace;
extern bool g_enableRenderingCallStackTrace;
extern INT g_capRenderCallStackCount;

extern bool g_enableRenderingDrawCallStackTrace;
extern INT g_capRenderDrawCallStackCount;

enum EResLoadingCallStackType
{
	ERLCST_Resource,
	ERLCST_ResourceFunction,
	ERLCST_Count,
	ERLCST_CountFunction
};

struct FResLoadingCallStack
{
	TArray<FResLoadingCallStack*> Links;
	EResLoadingCallStackType ResLoadingCallStackType;
	FString DisplayText;
	FString ResTypeName;
	INT ResSize;
	INT Deepth;

	FResLoadingCallStack()
		: ResSize(0)
		, Deepth(0)
	{
	}

	FString GetDisplayText() const
	{
		if((ResLoadingCallStackType == ERLCST_Count) || (ResLoadingCallStackType == ERLCST_CountFunction))
		{
			return FString::Printf(TEXT("%d - %s %s   %d"), Deepth, *ResTypeName, *DisplayText, ResSize);
		}

		if(ResSize > 1024 * 1024)
		{
			return FString::Printf(TEXT("%d - %s %s   %d MB"), Deepth, *ResTypeName, *DisplayText, ResSize / 1024 / 1024);
		}

		if(ResSize > 1024)
		{
			return FString::Printf(TEXT("%d - %s %s   %d KB"), Deepth, *ResTypeName, *DisplayText, ResSize / 1024);
		}

		return FString::Printf(TEXT("%d - %s %s   %d Byte"), Deepth, *ResTypeName, *DisplayText, ResSize);
	}

	FResLoadingCallStack* FindChildren(const FString& DisplayText)
	{
		for (INT i = 0; i < Links.Num(); ++i)
		{
			FResLoadingCallStack* cstk = Links(i);
			if(cstk->DisplayText == DisplayText)
			{
				return cstk;
			}
		}

		return NULL;
	}

	void Serialze(FArchive& Ar)
	{		
		Ar << DisplayText;
	
		if(Ar.IsSaving())
		{
			INT tmpType = (INT)ResLoadingCallStackType;
			Ar << tmpType;

			tmpType = Links.Num();
			Ar << tmpType;
			for (INT i = 0; i < Links.Num(); ++i)
			{
				Links(i)->Serialze(Ar);
			}
		}
		else
		{
			INT tmpType = 0;
			Ar << tmpType;

			ResLoadingCallStackType = (EResLoadingCallStackType)tmpType;

			INT sz = 0;
			Ar << sz;
			for (INT i = 0; i < sz; ++i)
			{
				FResLoadingCallStack* stk = new FResLoadingCallStack();
				stk->Serialze(Ar);
				Links.AddItem(stk);
			}
		}

		if(ResLoadingCallStackType == ERLCST_Resource || ResLoadingCallStackType == ERLCST_Count)
		{
			Ar << ResSize;
			Ar << ResTypeName;
		}
	}
};

void _RecordResLoadingCallStack(const FString& resPath, const FString& resTypeName, INT resSz, FResLoadingCallStack* rootCallStack, EResLoadingCallStackType dataType, EResLoadingCallStackType funType);
void _SaveResourceLoadingCallStack(FResLoadingCallStack* rootCallStack, const TCHAR* fileName);
FResLoadingCallStack* _LoadResourceLoadingCallStack(const TCHAR* fileName);
void _ResetLoadingCallStackRecord(FResLoadingCallStack* rootCallStack);


void RecordCallStack_ResLoading( const FString& resPath, const FString& resTypeName, INT resSz);
void SaveCallStack_ResLoading();
void ResetCallStack_ResLoading();


#define RecordResLoadingCallStack RecordCallStack_ResLoading
#define SaveResourceLoadingCallStack SaveCallStack_ResLoading
#define ResetLoadingCallStackRecord ResetCallStack_ResLoading



void RecordCallStack_Rendering( const FString& resPath, const FString& resTypeName, INT resSz);
void SaveCallStack_Rendering();
void ResetCallStack_Rendering();

#define RecordRenderingCallStack RecordCallStack_Rendering
#define SaveRenderingCallStack SaveCallStack_Rendering
#define ResetRenderingCallStack ResetCallStack_Rendering

void RecordCallStack_DrawCall( const FString& resPath, const FString& resTypeName, INT resSz);
void SaveCallStack_DrawCall();
void ResetCallStack_DrawCall();

#define RecordDrawCallStack RecordCallStack_DrawCall
#define SaveDrawCallStack SaveCallStack_DrawCall
#define ResetDrawCallStack ResetCallStack_DrawCall

#else
#	define RecordResLoadingCallStack(...)
#	define SaveResourceLoadingCallStack(...)
#	define ResetLoadingCallStackRecord(...)

#	define RecordRenderingCallStack(...)
#	define SaveRenderingCallStack(...)
#	define ResetRenderingCallStack(...)

#	define RecordDrawCallStack(...)
#	define SaveDrawCallStack(...)
#	define ResetDrawCallStack(...)
#endif

////////////////////////////zhaojun@snda////////////////////////////
class UMemPerformanceProfiler
{
public:
	enum eMemPerformanceProfilerType
	{
		MPPT_TEXTURE,
		MPPT_MESH,
		MPPT_ANIMATION,

		MPPT_COUNT,
	};

public:
	virtual void OnEntryCreate(eMemPerformanceProfilerType type, const FString& filename, UINT size) = 0;
	virtual void OnEntryDestroy(eMemPerformanceProfilerType type, const FString& filename, UINT size) = 0;
	virtual INT RenderToScreen(FViewport* Viewport, FCanvas* Canvas, INT X, INT Y, 
		UMemPerformanceProfiler::eMemPerformanceProfilerType etype) = 0;
	virtual void RenderToFile() = 0;
};

extern void SetMemPerformanceProfiler(UMemPerformanceProfiler* v);
extern UMemPerformanceProfiler* GetMemPerformanceProfiler();

#if !SHIPPING_PC_GAME // oscar@snda
#define MMOPERFORMANCE(express)	if (GetMemPerformanceProfiler() != NULL)	GetMemPerformanceProfiler()->express;
#else
#define MMOPERFORMANCE(express) ;
#endif

//////////////////////////zhaojun@snda/////////////////////////////////

#endif	//#ifndef _MMOENGINEUTIL_HEADER_