#include "CorePrivate.h"
#include "UnString.h"

#ifdef _DEBUG

UINT64 FDefaultStringAllocator::_AllocCount = 0;
UINT64 FDefaultStringAllocator::_AllocSize = 0;
UINT64 FDefaultStringAllocator::_AllocSizeInMem = 0;


void FDefaultStringAllocator::ForAnyElementType::ResizeAllocation( INT PreviousNumElements,INT NumElements,INT NumBytesPerElement )
{
	// Avoid calling appRealloc( NULL, 0 ) as ANSI C mandates returning a valid pointer which is not what we want.
	if( Data || NumElements )
	{
		++FDefaultStringAllocator::_AllocCount;
		FDefaultStringAllocator::_AllocSize += NumElements * NumBytesPerElement;
		FDefaultStringAllocator::_AllocSizeInMem += NumElements * NumBytesPerElement;
		_NumElements = NumElements;
		_NumBytesPerElement = NumBytesPerElement;
		//checkSlow(((QWORD)NumElements*(QWORD)ElementTypeInfo.GetSize() < (QWORD)INT_MAX));
		Data = (FScriptContainerElement*)appRealloc( Data, NumElements*NumBytesPerElement, DEFAULT_ALIGNMENT );
	}
}
#endif