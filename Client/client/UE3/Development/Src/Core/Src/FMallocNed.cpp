/*=============================================================================
	FMallocDebug.h: Debug memory allocator.
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "CorePrivate.h"
#include "FMallocNed.h"

#pragma warning(push)
#pragma warning(disable : 4565 4706)
#include "NedMemoryNedPooling.h"
#pragma warning(pop)

FMallocNed::FMallocNed()
{
#if STATS
	OsCurrent = 0;
	OsPeak = 0;
	WasteCurrent = 0;
	WastePeak = 0;
	UsedCurrent = 0;
	UsedPeak = 0;
	CurrentAllocs = 0;
	TotalAllocs = 0;
	MemTime = 0;
#endif
}

FMallocNed::~FMallocNed()
{

}

void* FMallocNed::Malloc( DWORD Size, DWORD Alignment )
{
	void* pReturn = NedMemory::NedPoolingAlignedPolicyRT::allocateBytes(Size, Alignment);
#if _WIN64
	check((INT64)pReturn % Alignment == 0);
#else
	check((INT)pReturn % Alignment == 0);
#endif

	OnMalloc(pReturn, Size, Alignment);

	return pReturn;
	//return _aligned_malloc(Size, Alignment);
}

/** 
* Realloc
*/
void* FMallocNed::Realloc( void* InPtr, DWORD NewSize, DWORD Alignment )
{
	//FMallocNed::Free( InPtr );
	//return FMallocNed::Malloc(NewSize, Alignment);
	OnFree(InPtr);

	void* pReturn = 
		NedMemory::NedPoolingAlignedPolicyRT::reallocateBytes(InPtr, Alignment, NewSize);

	OnMalloc(pReturn, NewSize, Alignment);

	return pReturn;

	//return _aligned_realloc(InPtr, NewSize, Alignment);
	//return NedMemory::NedAllocPolicy::reallocateBytes(InPtr, NewSize);
	//return NedMemory::NedPoolingImpl::realloc(Alignment, InPtr, NewSize);
	//void* Result = NedMemory::NedPoolingImpl::allocBytesAligned(NewSize, Alignment, "", 0, "");
	//appMemcpy( Result, InPtr, Min<SIZE_T>(Ptr->Size,NewSize) );
	//NedMemory::NedPoolingImpl::deallocBytes(InPtr);
}

/** 
* Free
*/
void FMallocNed::Free( void* InPtr )
{
	OnFree(InPtr);
	NedMemory::NedPoolingAlignedPolicyRT::deallocateBytes(InPtr, 0);
	//return _aligned_free(InPtr);
}

void FMallocNed::OnMalloc(void* p, DWORD Size, DWORD Alignment)
{
#if STATS
	if (p)
	{
		STAT(CurrentAllocs++);
		STAT(TotalAllocs++);

		DWORD ActualSize = NedMemory::NedPoolingImpl::memsize(p);
		
		//check(ActualSize == Size);
		UsedCurrent += ActualSize;
		WasteCurrent += ActualSize - Size;

		UsedPeak = UsedPeak > UsedCurrent ? UsedPeak : UsedCurrent;
	}
#endif
}

void FMallocNed::OnFree(void* p)
{
#if STATS
	if (p)
	{
		STAT(CurrentAllocs--);
		STAT(TotalAllocs--);

		DWORD ActualSize = NedMemory::NedPoolingImpl::memsize(p);

		UsedCurrent -= ActualSize;
	}

#endif
}

void FMallocNed::GetAllocationInfo( FMemoryAllocationStats& MemStats )
{
	//nedalloc::nedmallinfo();
	// determine how much memory has been allocated from the OS
#if STATS
	MemStats.TotalUsed = UsedCurrent;//MemStats.TotalAllocated = MemStats.OSReportedUsed = BinnedGetTotalMemoryAllocatedFromOS();
	MemStats.OSReportedFree = 0;//BinnedGetAvailableMemoryFromOS();
	MemStats.CPUUsed = UsedCurrent;//UsedCurrent;
	MemStats.CPUWaste = 0;//WasteCurrent;
	MemStats.CPUSlack = 0;//OsCurrent - WasteCurrent - UsedCurrent;
	MemStats.CPUWaste = 0;//( DWORD )Waste;
#endif
}
