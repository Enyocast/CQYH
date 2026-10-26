/**************************************************************************

Filename    :   HeapPT_SysAllocMMAP.cpp
Platform    :   Unix, Linux, MacOS
Content     :   MMAP based System Allocator
Created     :   2009
Authors     :   Maxim Shemanarev, Boris Rayskiy

Notes       :   System Allocator that uses regular malloc/free

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "HeapPT_SysAllocMMAP.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>


namespace Scaleform {

//------------------------------------------------------------------------
SysAllocMMAP::SysAllocMMAP(UPInt granularity) :
#ifdef SF_MEMORY_FORCE_SYSALLOC
    Granularity(MinGranularity),
#else
    Granularity((granularity + MinGranularity-1) / MinGranularity * MinGranularity),
#endif
    Footprint(0)
{
    SF_ASSERT(Granularity >= MinGranularity);

    Alignment = sysconf(_SC_PAGESIZE);
}

//------------------------------------------------------------------------
void SysAllocMMAP::GetInfo(Info* i) const
{
    i->MinAlign     = Alignment;
    i->MaxAlign     = Alignment;
    i->Granularity  = Granularity;
    i->HasRealloc   = true;
}


//------------------------------------------------------------------------
void* SysAllocMMAP::Alloc(UPInt size, UPInt) 
{ 
    void* ptr = mmap((void *)NULL, size, PROT_READ | PROT_WRITE, 
                     MAP_ANONYMOUS | MAP_PRIVATE, NULL, NULL);

    if (ptr != (void *)-1)
    {
        Footprint += size;
        return ptr;
    }
    
    return NULL;
}


//------------------------------------------------------------------------
bool SysAllocMMAP::ReallocInPlace(void* oldPtr, UPInt oldSize, UPInt newSize, UPInt)
{
    void* ptr = mremap(oldPtr, oldSize, newSize, NULL);

    if (ptr != oldPtr)
    {
        return false;
    }

    Footprint -= oldSize;
    Footprint += newSize;

    return true;
}


//------------------------------------------------------------------------
bool SysAllocMMAP::Free(void* ptr, UPInt size, UPInt)
{
    munmap(ptr, size);
  
    Footprint -= size;

    return true;
}

} // Scaleform
