#include "stdafx.h"
#include "MMOGameUIClasses.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_Benchmark)
IMPLEMENT_CLASS(UMMOUIBenchmarkPanel)


struct CpuidResult
{
	// Note: DO NOT CHANGE THE ORDER, some code based on that.
	UINT _eax;
	UINT _ebx;
	UINT _edx;
	UINT _ecx;
};

//---------------------------------------------------------------------
// Detect whether CPU supports CPUID instruction, returns non-zero if supported.
static int _isSupportCpuid(void)
{
	// Visual Studio 2005 & 64-bit compilers always supports __cpuid intrinsic
	// note that even though this is a build rather than runtime setting, all
	// 64-bit CPUs support this so since binary is 64-bit only we're ok
#if _MSC_VER >= 1400 && defined(_M_X64)
	return true;
#else
	// If we can modify flag register bit 21, the cpu is supports CPUID instruction
	__asm
	{
		// Read EFLAG
		pushfd
		pop     eax
		mov     ecx, eax

		// Modify bit 21
		xor     eax, 0x200000
		push    eax
		popfd

		// Read back EFLAG
		pushfd
		pop     eax

		// Restore EFLAG
		push    ecx
		popfd

		// Check bit 21 modifiable
		xor     eax, ecx
		neg     eax
		sbb     eax, eax

		// Return values in eax, no return statement requirement here for VC.
	}
#endif
}

//---------------------------------------------------------------------
// Performs CPUID instruction with 'query', fill the results, and return value of eax.
static UINT _performCpuid(INT query, CpuidResult& result)
{
#if _MSC_VER >= 1400 
	int CPUInfo[4];
	__cpuid(CPUInfo, query);
	result._eax = CPUInfo[0];
	result._ebx = CPUInfo[1];
	result._ecx = CPUInfo[2];
	result._edx = CPUInfo[3];
#else
	__asm
	{
		mov     edi, result
		mov     eax, query
		cpuid
		mov     [edi]._eax, eax
		mov     [edi]._ebx, ebx
		mov     [edi]._edx, edx
		mov     [edi]._ecx, ecx
		// Return values in eax, no return statement requirement here for VC.
	}
#endif
	return result._eax;
}

FString _detectCpuIdentifier(void)
{
	// Supports CPUID instruction ?
	if (_isSupportCpuid())
	{
		CpuidResult result;
		UINT nExIds;
		char CPUString[0x20];
		char CPUBrandString[0x40];

		FString detailedIdentStr;


		// Has standard feature ?
		if (_performCpuid(0, result))
		{
			memset(CPUString, 0, sizeof(CPUString));
			memset(CPUBrandString, 0, sizeof(CPUBrandString));

			*((INT*)CPUString) = result._ebx;
			*((INT*)(CPUString+4)) = result._edx;
			*((INT*)(CPUString+8)) = result._ecx;

			detailedIdentStr += FString(CPUString);

			// Calling _performCpuid with 0x80000000 as the query argument
			// gets the number of valid extended IDs.
			nExIds = _performCpuid(0x80000000, result);

			for (UINT i=0x80000000; i<=nExIds; ++i)
			{
				_performCpuid(i, result);

				// Interpret CPU brand string and cache information.
				if  (i == 0x80000002)
				{
					memcpy(CPUBrandString + 0, &result._eax, sizeof(result._eax));
					memcpy(CPUBrandString + 4, &result._ebx, sizeof(result._ebx));
					memcpy(CPUBrandString + 8, &result._ecx, sizeof(result._ecx));
					memcpy(CPUBrandString + 12, &result._edx, sizeof(result._edx));
				}
				else if  (i == 0x80000003)
				{
					memcpy(CPUBrandString + 16 + 0, &result._eax, sizeof(result._eax));
					memcpy(CPUBrandString + 16 + 4, &result._ebx, sizeof(result._ebx));
					memcpy(CPUBrandString + 16 + 8, &result._ecx, sizeof(result._ecx));
					memcpy(CPUBrandString + 16 + 12, &result._edx, sizeof(result._edx));
				}
				else if  (i == 0x80000004)
				{
					memcpy(CPUBrandString + 32 + 0, &result._eax, sizeof(result._eax));
					memcpy(CPUBrandString + 32 + 4, &result._ebx, sizeof(result._ebx));
					memcpy(CPUBrandString + 32 + 8, &result._ecx, sizeof(result._ecx));
					memcpy(CPUBrandString + 32 + 12, &result._edx, sizeof(result._edx));
				}
			}

			FString brand(CPUBrandString);
			brand.Trim();
			if (!brand.IsEmpty())
			{
				detailedIdentStr += FString(TEXT(": ")) + brand;
			}

			return detailedIdentStr;
		}
	}

	return TEXT("X86");
}

void UMMOUIBenchmarkPanel::PostOnShow(UBOOL show)
{
	Super::PostOnShow(show);

	if(show)
	{
		FLOAT avgFPS, minFPS, maxFPS;
		GetBenchMarkFPS(avgFPS, minFPS, maxFPS);

		FGPUInfo gpuInfo;
		RHIQueryGPUHardWareInfo(gpuInfo);

		// Get memory.
		//MEMORYSTATUSEX M;
		//M.dwLength = sizeof(MEMORYSTATUSEX);
		//GlobalMemoryStatusEx(&M);
		//GPhysicalGBRam = UINT(FLOAT(M.ullTotalPhys/1024.0/1024.0/1024.0)+ .1f);
		//warnf( NAME_Init, TEXT("Memory total: Physical=%.1fGB (%dGB approx) Pagefile=%.1fGB Virtual=%.1fGB"), FLOAT(M.ullTotalPhys/1024.0/1024.0/1024.0),GPhysicalGBRam, FLOAT(M.ullTotalPageFile/1024.0/1024.0/1024.0), FLOAT(M.ullTotalVirtual/1024.0/1024.0/1024.0) );

		FString gpuInfoStr(gpuInfo.DeviceName);
		FString cpuInfoStr = FString::Printf(TEXT("%s"), *_detectCpuIdentifier());
		FString memInfoStr = FString::Printf(TEXT("%.2fGB"), (FLOAT)GPhysicalGBRam);
		FVector2D vpSz;
		GEngine->GameViewport->GetViewportSize(vpSz);
		FString screenRes = FString::Printf(TEXT("%dx%d"), (INT)vpSz.X, (INT)vpSz.Y);

		eventCallUpdateInfo(avgFPS, maxFPS, cpuInfoStr, memInfoStr, gpuInfoStr, screenRes);
	}
}

void UMMOGFXPlayer_Benchmark::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_Benchmark::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Benchmark);
}