/**************************************************************************

Filename    :   AS3_GC.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Artem Bolgar, Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "AS3_GC.h"

namespace Scaleform { namespace GFx { namespace AS3
{

///////////////////////////////////////////////////////////////////////////
//
ASRefCountCollector::ASRefCountCollector()
{
    FrameCnt            = 0;
    PeakRootCount       = 0;
    LastRootCount       = 0;
    LastCollectedRoots  = 0;
    LastPeakRootCount   = 0;
    TotalFramesCount    = 0;
    LastCollectionFrameNum = 0;
    CollectionScheduledFlag = false;
    
    SetParams(~0u, ~0u);
}

void ASRefCountCollector::SetParams(unsigned frameBetweenCollections, unsigned maxRootCount)
{
    // max num of roots before collection
    if (frameBetweenCollections != ~0u)
        MaxFramesBetweenCollections = frameBetweenCollections;
    else
        MaxFramesBetweenCollections = 0; // off by default
    
    // force collection for every N-frames
    if (maxRootCount != ~0u)
        PresetMaxRootCount  = MaxRootCount = maxRootCount;
    else
        PresetMaxRootCount  = MaxRootCount = 7000; //change default value form 1000 to 7000,tangbinjie
}

//////////////////////////////////////////////////////////////////////////
// GASRefCountCollection
//
#ifdef SF_BUILD_DEBUG
//#define SF_TRACE_COLLECTIONS
#endif

void ASRefCountCollector::AdvanceFrame(unsigned* movieFrameCnt, unsigned* movieLastCollectFrame, class Scaleform::AmpStats* ampStat)
{
    // Is this the first advance since a collection by a different MovieView?
    if (*movieLastCollectFrame != LastCollectionFrameNum)
    {
        *movieLastCollectFrame = LastCollectionFrameNum;
        *movieFrameCnt = 1;
        return;
    }

    // Make sure we don't collect multiple times per frame
    // in the case where several views share the same GC
    if (*movieFrameCnt < FrameCnt)
    {
        // the calling MovieView is advancing the GC during a frame where
        // the GC has already been advanced more times by different MovieView
        ++(*movieFrameCnt);
        return;
    }

    unsigned curRootCount = (unsigned)GetRootsCount();
    // Do collection only every 10th frame for now
    ++TotalFramesCount;
    ++FrameCnt;
    PeakRootCount = Alg::Max(PeakRootCount, curRootCount);

    // Collection occurs if:
    // 1) if number of root exceeds currently set MaxRootCount;
    // 2) if MaxFramesBetweenCollections is set to value higher than 0 and the
    //    frame counter (FrameCnt) exceeds this value, and number of roots
    //    exceeds PresetMaxRootCount.
    if ((PresetMaxRootCount != 0 && curRootCount > MaxRootCount) || 
        (MaxFramesBetweenCollections != 0 && 
        FrameCnt >= MaxFramesBetweenCollections && 
        curRootCount > PresetMaxRootCount))
    {
		SF_AMP_SCOPE_TIMER(ampStat, "ASRefCountCollector::AdvanceFrame.Collect", Amp_Profile_Level_Low);
        ASRefCountCollector::Stats stats;
        Collect(&stats, ampStat);

#ifdef SF_TRACE_COLLECTIONS        
        printf("Collect! Roots %d, MaxRoots %d, Peak %d, Roots collected %d, frames between %d ", 
            curRootCount, MaxRootCount, PeakRootCount, stats.RootsFreedTotal,
            TotalFramesCount - LastCollectionFrameNum);
#endif

        // If number of roots exceeds the preset max root count then we need to reset the PeakRootCount
        // in order to decrease currently set MaxRootCount.
        if (stats.RootsFreedTotal > PresetMaxRootCount)
        {
            PeakRootCount = curRootCount; // reset peak count
            MaxRootCount = PresetMaxRootCount;
        }

        // MaxRootCount has been updated every collection event
        //MaxRootCount = Alg::Max(PresetMaxRootCount, PeakRootCount - stats.RootsFreedTotal);
        MaxRootCount = Alg::Max(MaxRootCount, curRootCount - stats.RootsFreedTotal);

        if (PeakRootCount < (unsigned)(MaxRootCount * 0.7))
            MaxRootCount = (unsigned)(MaxRootCount * 0.7);

#ifdef SF_TRACE_COLLECTIONS        
        SF_ASSERT((int)MaxRootCount >= 0);
        printf("new maxroots %d\n", MaxRootCount);
#endif

        LastCollectionFrameNum = TotalFramesCount;

        FrameCnt          = 0;
        LastPeakRootCount = PeakRootCount;
        LastCollectedRoots= stats.RootsFreedTotal;
    }
    LastRootCount = curRootCount;
    *movieFrameCnt = FrameCnt;
    *movieLastCollectFrame = LastCollectionFrameNum;
}

void ASRefCountCollector::ForceCollect()
{
    unsigned curRootCount = (unsigned)GetRootsCount();

    ASRefCountCollector::Stats stats;
    Collect(&stats);

#ifdef SF_TRACE_COLLECTIONS        
    printf("Forced collect! Roots %d, MaxRoots %d, Peak %d, Roots collected %d\n", 
        curRootCount, MaxRootCount, PeakRootCount, stats.RootsFreedTotal);
#endif
    FrameCnt  = 0;
    PeakRootCount = Alg::Max(PeakRootCount, curRootCount);
    LastRootCount = curRootCount;

    if (DoesRequireAdditionalCollect())
        ScheduleCollect();
}

void ASRefCountCollector::ForceEmergencyCollect()
{
    ForceCollect();

    // DO NOT shrink roots, if this was called while in adding roots in Release
    if (!IsAddingRoot())
        ShrinkRoots();

    // Reset peak and max root counters.
    PeakRootCount = 0;
    MaxRootCount  = PresetMaxRootCount;
}


///////////////////////////////////////////////////////////////////////////////
void ForEachChild_GC_Internal(RefCountCollector<Mem_Stat>* prcc, 
                              const Value& v, RefCountBaseGC<Mem_Stat>::GcOp op
                              SF_DEBUG_ARG(const RefCountBaseGC<Mem_Stat>& owner))
{
    switch(v.GetKind())
    {
    case Value::kFunction:  // = 6
    case Value::kObject:    // = 8
    case Value::kClass:     // = 9
    case Value::kThunkFunction: // = 12
    case Value::kNamespace:
        // We do not use GetObject here because we handle kNamespace.
        if (v.GetGASRefCountBase())
            (*op)(prcc, (const AS3::RefCountBaseGC<Mem_Stat>**)v.AsGASRefCountBasePtrPtr() SF_DEBUG_ARG(owner));

        break;
    case Value::kThunkClosure:
    case Value::kVTableIndClosure:
        if (v.GetClosure())
            (*op)(prcc, (const AS3::RefCountBaseGC<Mem_Stat>**)v.AsClosurePtrPtr() SF_DEBUG_ARG(owner));

        break;
    default:
        SF_ASSERT(false);
        break;
    }
}

void ForEachChild_GC(RefCountCollector<Mem_Stat>* prcc, 
                     const ValueArray& v, RefCountBaseGC<Mem_Stat>::GcOp op
                     SF_DEBUG_ARG(const RefCountBaseGC<Mem_Stat>& owner))
{
    for(UPInt i = 0; i < v.GetSize(); ++i)
        AS3::ForEachChild_GC(prcc, v[i], op SF_DEBUG_ARG(owner));
}

void ForEachChild_GC(RefCountCollector<Mem_Stat>* prcc, 
                     const ValueArrayDH& v, RefCountBaseGC<Mem_Stat>::GcOp op
                     SF_DEBUG_ARG(const RefCountBaseGC<Mem_Stat>& owner))
{
    for(UPInt i = 0; i < v.GetSize(); ++i)
        AS3::ForEachChild_GC(prcc, v[i], op SF_DEBUG_ARG(owner));
}


///////////////////////////////////////////////////////////////////////////
GASRefCountBase::~GASRefCountBase()
{
    if (HasWeakRef())
    {
        // This code shouldn't be called when this object is in a kill list.
        RefCountCollector<Mem_Stat>* rcc = GetCollector();
        WeakProxy* wp = NULL;

        // We should always have WeakProxy here.
        if (rcc->WProxyHash.Get(this, &wp) && wp)
        {
            wp->NotifyObjectDied();
            wp->Release();
            rcc->WProxyHash.Remove(this);
        }
    }
}

}}} // namespace Scaleform { namespace GFx { namespace AS3 {


