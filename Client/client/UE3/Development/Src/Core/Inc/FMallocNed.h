/*=============================================================================
	FMallocNed.h: Pooling memory allocator.
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __FMALLOCNED_H__
#define __FMALLOCNED_H__

class FMallocNed : public FMalloc
{
public:
	// FMalloc interface.
	FMallocNed();
	virtual ~FMallocNed();

	/** 
	 * Malloc
	 */
	virtual void* Malloc( DWORD Size, DWORD Alignment );

	/** 
	 * Realloc
	 */
	virtual void* Realloc( void* InPtr, DWORD NewSize, DWORD Alignment );

	/** 
	 * Free
	 */
	virtual void Free( void* InPtr );

	virtual void GetAllocationInfo( FMemoryAllocationStats& MemStats );

protected:

	void OnMalloc(void* p, DWORD Size, DWORD Alignment);
	void OnFree(void* p);

#if STATS
	DWORD		OsCurrent;
	DWORD		OsPeak;
	DWORD		WasteCurrent;
	DWORD		WastePeak;
	DWORD		UsedCurrent;
	DWORD		UsedPeak;
	DWORD		CurrentAllocs;
	DWORD		TotalAllocs;
	DOUBLE		MemTime;
#endif

};

#endif
