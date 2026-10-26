/**************************************************************************

Filename    :   AS3_GC.h
Content     :   
Created     :   Jan, 2010
Last rev    :   April 29, 2011
Authors     :   Artem Bolgar, Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_AS3_GC_H
#define INC_AS3_GC_H

#include "AS3_Value.h" // Because of ValueArray
#include "Kernel/SF_ArrayPaged.h"

// Uncomment the line below to enable recursionless Release. This will avoid recursions
// during execution of Release but will make it slower.
//#define SF_USE_RECURSIONLESS_RELEASE

namespace Scaleform { namespace GFx { namespace AS3 {

///////////////////////////////////////////////////////////////////////////
#ifdef GFC_GC_DO_TRACE
    #define GFC_GC_DEBUG_PARAMS         int level
    #define GFC_GC_DEBUG_2ND_PARAM      ,int level
    #define GFC_GC_DEBUG_PARAMS_DEF     int level=0
    #define GFC_GC_DEBUG_PASS_PARAMS    level+1
    #define GFC_GC_DEBUG_PASS_PARAM     ,level+1
    #define GFC_GC_TRACE(s)             Trace(level, s)
    #define GFC_GC_COND_TRACE(c,s)      do { if(c) Trace(level, s); } while(0)
    #define GFC_GC_PRINT(s)             printf("%s\n", s)
    #define GFC_GC_PRINTF(s,p1)         printf(s, p1)
    #define GFC_GC_PARAM_START_VAL      0
    #define GFC_GC_PARAM_VAL            ,0
#else
    #define GFC_GC_DEBUG_PARAMS
    #define GFC_GC_DEBUG_2ND_PARAM
    #define GFC_GC_DEBUG_PARAMS_DEF
    #define GFC_GC_DEBUG_PASS_PARAMS
    #define GFC_GC_DEBUG_PASS_PARAM
    #define GFC_GC_TRACE(s)
    #define GFC_GC_COND_TRACE(c,s)
    #define GFC_GC_PRINT(s)
    #define GFC_GC_PRINTF(s,p1)
    #define GFC_GC_PARAM_START_VAL
    #define GFC_GC_PARAM_VAL
#endif

template <int Stat> class RefCountCollector;
template <typename T> class APtr;
class STPtr;

template <int Stat = Stat_Default_Mem>
class RefCountBaseGC : public NewOverrideBase<Stat>
{
    friend class RefCountCollector<Stat>;
    friend class Value;
    friend class STPtr;
    template <typename T> friend class SPtr;
    template <typename T> friend class APtr;
#if _MSC_VER > 1400
    // There is a bug in MSVC 2005 related to friend template classes.
    template <typename T> friend class Scaleform::Pickable;
#endif

public:
    typedef class RefCountCollector<Stat> Collector;

    enum OperationGC
    {
        Operation_Release,
        Operation_MarkInCycle,
        Operation_ScanInUse,
        Operation_Disable,
        Operation_ScanTempInUse,

        Operation_Collect // used by ObjCollector
    };

    typedef void (*GcOp)(Collector* prcc, const RefCountBaseGC<Stat>** pchild SF_DEBUG_ARG(const RefCountBaseGC<Stat>&));
    
private:
    enum
    {
        Flag_Buffered       = 0x80000000u,
        Mask_State          = 0x7,
        Shift_State         = 28,
        Mask_DeleteLast     = 0x8000000,
        Mask_HasWeakRef     = 0x4000000,
        Mask_HasFinalize    = 0x2000000,
        Flag_InList         = 0x1000000, // if set, pNext/pPrev are in use.
        Flag_DelayedRelease = 0x0800000,
        Flag_ToBeFinalized  = 0x0400000,
        Mask_RefCount       = 0x03FFFFF
    };

    enum States
    {
        State_InUse     = 0,
        State_InCycle   = 1,
        State_Garbage   = 2,
        State_Root      = 3,
        State_Removed   = 4,
        State_TempInUse = 5
    };

    union
    {
        mutable Collector*            pRCC;
        mutable const RefCountBaseGC* pNext;
    };

    // Ref counter takes bits 27-0 lower bytes.
    // The most significant bit (bit 31) is flag "buffered".
    // Bits 30-28 - color (7 values)
    mutable UInt32                    RefCount;
    union
    {
        // 0x80000000 bit may be set to 1 to indicate this is a root for finalization.
        // Use GetRootIndex() to get actual value of root index.
        mutable UInt32                RootIndex;
        mutable const RefCountBaseGC* pPrev;
    };

    void Increment(GFC_GC_DEBUG_PARAMS) const
    {
        SF_ASSERT((RefCount & Mask_RefCount) < Mask_RefCount);
        ++RefCount;
        GFC_GC_TRACE("Incremented ");
    }
    unsigned Decrement(GFC_GC_DEBUG_PARAMS) const
    {
        SF_ASSERT((RefCount & Mask_RefCount) > 0);
        GFC_GC_TRACE("Decrementing ");
        return ((--RefCount) & Mask_RefCount);
    }

    void MarkInCycle(Collector* prcc GFC_GC_DEBUG_PARAMS) const;

public:
    static void ReleaseCall(Collector* prcc, const RefCountBaseGC<Stat>** pchild SF_DEBUG_ARG(const RefCountBaseGC<Stat>&))
    {
        SF_ASSERT(pchild);
        SF_ASSERT(*pchild);

        SF_ASSERT(!(*pchild)->IsRefCntZero());
        if ((*pchild)->Decrement() == 0)
        {
            // if refcnt == 1 then we can't call Release since it will cause recursive calls
            // (for each child). Just add to a list.
            prcc->RemoveFromRoots(*pchild);
            (*pchild)->SetDelayedRelease();
            prcc->AddToList(*pchild);
        }
        else
            (*pchild)->ReleaseInternal();
    }
    static void MarkInCycleCall(Collector* prcc, const RefCountBaseGC<Stat>** pchild SF_DEBUG_ARG(const RefCountBaseGC<Stat>&))
    {
        SF_ASSERT(pchild);
        SF_ASSERT(*pchild);
        (*pchild)->Decrement();
        prcc->AddToList(*pchild);
    }
    static void ScanInUseCall(Collector* prcc, const RefCountBaseGC<Stat>** pchild SF_DEBUG_ARG(const RefCountBaseGC<Stat>&))
    {
        SF_ASSERT(pchild);
        SF_ASSERT(*pchild);
        (*pchild)->Increment();
        if (!(*pchild)->IsInState(State_InUse))
        {
            (*pchild)->SetState(State_InUse);
            prcc->ReinsertToList(*pchild); // to reinsert
        }
    }
    static void ScanTempInUseCall(Collector* prcc, const RefCountBaseGC<Stat>** pchild SF_DEBUG_ARG(const RefCountBaseGC<Stat>&))
    {
        SF_ASSERT(pchild);
        SF_ASSERT(*pchild);
        (*pchild)->Increment();
        if (!(*pchild)->IsInState(State_TempInUse) && !(*pchild)->IsInState(State_InUse))
        {
            (*pchild)->SetState(State_TempInUse);
            prcc->ReinsertToList(*pchild); // to reinsert
        }
    }
    static void DisableCall(Collector*, const RefCountBaseGC<Stat>** pchild SF_DEBUG_ARG(const RefCountBaseGC<Stat>&))
    {
        SF_ASSERT(pchild);
        SF_ASSERT(*pchild);
        *pchild = (RefCountBaseGC<Stat>*)((UPInt)(*pchild) + 1);
    }
    
private:
    virtual void ForEachChild_GC(Collector* prcc, GcOp op) const = 0;
    
    void ExecuteForEachChild_GC(Collector* prcc, OperationGC op) const
    {
        switch(op)
        {
        case Operation_Release: 
            ForEachChild_GC(prcc, ReleaseCall); 
            break;
        case Operation_MarkInCycle: 
            ForEachChild_GC(prcc, MarkInCycleCall); 
            break;
        case Operation_ScanInUse: 
            ForEachChild_GC(prcc, ScanInUseCall); 
            break;
        case Operation_ScanTempInUse: 
            ForEachChild_GC(prcc, ScanTempInUseCall); 
            break;
        case Operation_Disable: 
            ForEachChild_GC(prcc, DisableCall); 
            break;

        case Operation_Collect:
            ForEachChild_GC(prcc, prcc->CollectorFunc); 
            break;
        }
    }

    bool IsRefCntZero() const { return (RefCount & Mask_RefCount) == 0; }

    void SetBuffered(UInt32 rootIndex) const
    { 
        RefCount |= Flag_Buffered; RootIndex = rootIndex; 
    }
    void ClearBuffered() const   
    { 
        RefCount &= ~Flag_Buffered; 
        if (!IsInList()) 
            RootIndex = ~0u; 
    }
    bool IsBuffered() const { return (RefCount & Flag_Buffered) != 0; }

    SF_INLINE void SetInList() const
    { 
        RefCount |= Flag_InList;
    }
    SF_INLINE void ClearInList(Collector* prcc) const
    { 
        RefCount &= ~Flag_InList; 
        pRCC      = prcc;
        ClearBuffered();
    }
    SF_INLINE bool IsInList() const { return (RefCount & Flag_InList) != 0; }

    SF_INLINE void SetDelayedRelease() const 
    { 
        RefCount |= Flag_DelayedRelease;
    }
    SF_INLINE void ClearDelayedRelease() const
    { 
        RefCount &= ~Flag_DelayedRelease; 
    }
    SF_INLINE bool IsDelayedRelease() const { return (RefCount & Flag_DelayedRelease) != 0; }
    SF_INLINE bool HasFinalize() const { return (RefCount & Mask_HasFinalize) != 0; }
    SF_INLINE void ClearFinalize() const { RefCount &= ~(Mask_HasFinalize | Flag_ToBeFinalized); }
    
    SF_INLINE UInt32 GetRootIndex() const { return RootIndex; }
    SF_INLINE bool   ToBeFinalized() const { return (RefCount & Flag_ToBeFinalized) != 0; }
    SF_INLINE void   MarkToBeFinalized() const { RefCount |= Flag_ToBeFinalized; }

    void SetState(States c) const
    { 
        SF_ASSERT(!IsInState(State_Removed) || c == State_Removed);
        RefCount = (RefCount & ~(Mask_State << Shift_State)) | 
                   (((UInt32)c & Mask_State) << Shift_State); 
    }
    States GetState() const  { return (States)((RefCount >> Shift_State) & Mask_State); }
    bool IsInState(States c) const { return GetState() == c; }

    void Free_GC(Collector* prcc GFC_GC_DEBUG_2ND_PARAM) const
    {
        // the const cast is pretty safe here, since anyway 'delete' is 
        // going to be called later.
        //const_cast<RefCountBaseGC<Stat>*>(this)->Finalize_GC();

        GFC_GC_TRACE("Freeing ");
        ExecuteForEachChild_GC(prcc, Operation_Disable);
        delete this;
    }

    void RemoveFromList() const
    {
        SF_ASSERT(IsInList());
        pPrev->pNext = pNext;
        pNext->pPrev = pPrev;
        RefCount &= ~Flag_InList; 
        pRCC = NULL;
        ClearBuffered();
    }
    void ReleaseInternal(GFC_GC_DEBUG_PARAMS_DEF) const;
    void FreeThis(Collector* prcc GFC_GC_DEBUG_2ND_PARAM) const;
public:
    RefCountBaseGC(class RefCountCollector<Stat>* prcc) : pRCC(prcc), RefCount(1) 
    { 
        /*SF_ASSERT(pRCC);*/ 
    }

    RefCountCollector<Stat>* GetCollector() const { return pRCC; }

    // Dangerous AddRef/Release that should be used with care.
    // They receive separate names so that they don't accidentally assigned to Ptr<>
    void    AddRef_Unsafe() const { AddRef(); }
    void    Release_Unsafe() const { Release(); }
    bool    HasWeakRef() const { return (RefCount & Mask_HasWeakRef) != 0; }
    bool    IsDeleteLast() const { return (RefCount & Mask_DeleteLast) != 0; }

#ifdef GFX_AS3_VERBOSE
    // returns 'true' if 'this' is an instance of AS3::Object.
    // Needed for ObjectCollector (not garbage collector).
    virtual bool IsAS3Object() const { return false; }
    virtual const char* GetAS3ObjectType() const { return "<unknown>"; }
    virtual Scaleform::String GetAS3ObjectName() const { return Scaleform::String(""); }
#endif

public:
    UInt32  GetRefCount() const { return (RefCount & Mask_RefCount); }

protected:
    virtual ~RefCountBaseGC() // virtual to avoid gcc -Wall warnings
    {
    }
    virtual void Finalize_GC() {}

    void SetWeakRef() const { RefCount |= Mask_HasWeakRef; }
    void SetNotWeakRef() const { RefCount &= ~Mask_HasWeakRef; }
    void SetDeleteLast() const { RefCount |= Mask_DeleteLast; }
    void SetHasFinalize() const { RefCount |= Mask_HasFinalize; }

#if _MSC_VER < 1500
    // There is a bug in MSVC 2005 related to friend template classes.
public:
#else
private:
#endif

    void AddRef() const 
    { 
        SF_ASSERT(pRCC);
        Increment(GFC_GC_PARAM_START_VAL);
        SetState(State_InUse);
        RefCount &= ~Flag_ToBeFinalized;
    }

private:
    void Release(GFC_GC_DEBUG_PARAMS_DEF) const;

    // copying is prohibited
    RefCountBaseGC(const RefCountBaseGC&) { }
    RefCountBaseGC& operator=(const RefCountBaseGC&) { return *this; }

#ifdef GFC_GC_DO_TRACE
    void Trace(int level, const char* text)
    {
        char s[1024] = {0};
        for (int i = 0; i < level; ++i)
            G_strcat(s, sizeof(s), "  ");
        printf ("%s%s %p, state %d, refcnt = %d\n", s, text, this, GetState(), 
            (RefCount & RefCountBaseGC<Stat>::Mask_RefCount));
}
#endif // GFC_GC_DO_TRACE
}; // RefCountBaseGC

class WeakProxy;
class GASRefCountBase;

template <int Stat = Stat_Default_Mem>
struct PtrReleaseProxy : public RefCountBase<PtrReleaseProxy<Stat>, Stat>
{
    Ptr<RefCountNTSImpl>    Data;
    SPtr<GASRefCountBase>   Data2;
    Ptr<PtrReleaseProxy>    pNext;
};

template <int Stat = Stat_Default_Mem>
class RefCountCollector : public RefCountBase<RefCountCollector<Stat>, Stat>
{
    friend class RefCountBaseGC<Stat>;
    friend class GASRefCountBase; // Because of WProxyHash.

protected:
    enum
    {
        Flags_Collecting = 0x1, // ON while collecting roots; OFF, while processing killlist
        Flags_AddingRoot = 0x2,
        Flags_InCollect  = 0x4, // unlike Flags_Collecting, this flag is ON while in Collect
        Flags_MarkInCycle= 0x8,
        Flags_RequireMoreCollect = 0x10
    };

    ArrayPagedLH_POD<const RefCountBaseGC<Stat> *, 10, 5> Roots;
    UPInt                       FirstFreeRootIndex;
    typename RefCountBaseGC<Stat>::GcOp  CollectorFunc;

    class Root : public RefCountBaseGC<Stat>
    {
    public:
        Root() : RefCountBaseGC<Stat>(0) {}
        virtual void ForEachChild_GC(RefCountCollector<Stat>* , typename RefCountBaseGC<Stat>::GcOp ) const {}
    }                           ListRoot;
    const RefCountBaseGC<Stat>* pLastPtr;

    Hash<GASRefCountBase*, WeakProxy*> WProxyHash;
    UInt8 Flags;

    Ptr<PtrReleaseProxy<Stat> > HeadDelayedPtrRelease;

    void CleanDelayedReleaseProxies();

    void AddRoot(const RefCountBaseGC<Stat>* root);

public: // shouldn't be public but some compilers (such as ps3) complain
    void AddToList(const RefCountBaseGC<Stat>* proot);
    void ReinsertToList(const RefCountBaseGC<Stat>* proot);
    void RemoveFromRoots(const RefCountBaseGC<Stat>* root);
public:
    struct Stats
    {
        unsigned RootsNumber;
        unsigned RootsFreedTotal;

        Stats() { RootsNumber = RootsFreedTotal = 0; }
    };

public:
    RefCountCollector()
        : FirstFreeRootIndex(SF_MAX_UPINT)
        , Flags(0) 
    { pLastPtr = &ListRoot; }
    ~RefCountCollector() { Collect(); }

    // Perform collection. Returns 'true' if collection process was 
    // executed.
    bool Collect(Stats* pstat = NULL);

    // Returns number of roots; might be used to determine necessity
    // of call to Collect.
    UPInt GetRootsCount() const { return Roots.GetSize(); }

    // Shrinks the array for roots to a minimal possible size
    void ShrinkRoots();

    // true while collecting roots; OFF, while processing killlist
    bool IsCollecting() const { return (Flags & Flags_Collecting) != 0; }
    bool IsAddingRoot() const { return (Flags & Flags_AddingRoot) != 0; }
    bool IsMarkInCycle() const { return (Flags & Flags_MarkInCycle) != 0; }
    // unlike IsCollecting, returns true while in Collect
    bool IsInCollect() const  { return (Flags & Flags_InCollect) != 0; }

    bool DoesRequireAdditionalCollect() const  { return (Flags & Flags_RequireMoreCollect) != 0; }

    void AddDelayedReleaseProxy(PtrReleaseProxy<Stat>* preleaseProxy);

    // helper funcs
    static bool IsDisableOp(typename RefCountBaseGC<Stat>::GcOp op) 
    {
        return op == RefCountBaseGC<Stat>::DisableCall;
    }
    static bool IsReleaseOp(typename RefCountBaseGC<Stat>::GcOp op) 
    {
        return op == RefCountBaseGC<Stat>::ReleaseCall;
    }

    // used by ObjectCollector to collect all the object (not for garbage collection).
    void CollectChildren(const RefCountBaseGC<Stat>* pch)
    {
        SF_ASSERT(CollectorFunc);
        pch->ForEachChild_GC(this, CollectorFunc);
    }
private:
    void HandleWeakRef(const RefCountBaseGC<Stat>* pcur);

private:
    RefCountCollector(const RefCountCollector&) {}
    RefCountCollector& operator=(const RefCountCollector&) { return *this; }
}; // RefCountCollector

/////////////////////////////////////////////////////
// Implementations
//
template <int Stat>
inline
void RefCountBaseGC<Stat>::Release(GFC_GC_DEBUG_PARAMS) const
{
    if (IsRefCntZero())
        return;
    SF_ASSERT(!IsDelayedRelease());

    Decrement(GFC_GC_DEBUG_PASS_PARAMS);
    ReleaseInternal(GFC_GC_DEBUG_PARAMS);
}

template <int Stat>
inline
void RefCountBaseGC<Stat>::FreeThis(Collector* prcc GFC_GC_DEBUG_2ND_PARAM) const
{
    SF_UNUSED(prcc);
    SetState(State_InUse);

    if (!IsBuffered())
    {
        if (IsInList())
            RemoveFromList();
#ifndef SF_USE_RECURSIONLESS_RELEASE
        delete this;
#else
        Free_GC(prcc GFC_GC_DEBUG_PASS_PARAM);
#endif //SF_USE_RECURSIONLESS_RELEASE
    }
    else
    {
        if (!IsInList())
        {
            SF_ASSERT(pRCC && pRCC->Roots.GetSize() == pRCC->Roots.GetSize());
            pRCC->RemoveFromRoots(this);
        }
        else
            RemoveFromList();

#ifndef SF_USE_RECURSIONLESS_RELEASE
        delete this;
#else
        Free_GC(prcc GFC_GC_DEBUG_PASS_PARAM);
#endif //SF_USE_RECURSIONLESS_RELEASE
    }
}

template <int Stat>
inline
void RefCountBaseGC<Stat>::ReleaseInternal(GFC_GC_DEBUG_PARAMS) const
{
    if (IsRefCntZero())
    {
        GFC_GC_TRACE("Releasing ");

        if (HasFinalize())
            const_cast<RefCountBaseGC<Stat>*>(this)->Finalize_GC();

        // Release all children. We can't perform recursive calls here.
        if (IsInList())
        {
            // It is already in list, just set flag "DelayedRelease". 
            // pRCC is invalid here.
            // This may happen when Release is called from Collect.
            SetDelayedRelease();
            return; // finish for now
        }
#ifdef SF_USE_RECURSIONLESS_RELEASE
        else
        {
            // pRCC is valid here.
            SF_ASSERT(!pRCC->IsCollecting());

            // Check if the list is already in use...
            if (!pRCC->ListRoot.IsInList())
            {
                // ... no: we need to iterate through the list until all children are released
                pRCC->pLastPtr = &pRCC->ListRoot;
                pRCC->ListRoot.pNext = pRCC->ListRoot.pPrev = &pRCC->ListRoot;
                pRCC->ListRoot.SetInList();

                // add children to the list with flag DelayedRelease
                ExecuteForEachChild_GC(pRCC, Operation_Release); 

                // need to save a pointer to collector since "this" might be freed
                // (see FreeThis call below)
                Collector* prcc = pRCC; 
                int cnt = 0;
                // two iterations: for regular and "deletelast" objs
                do 
                {
                    const RefCountBaseGC<Stat>* cur = prcc->ListRoot.pNext;
                    while(cur != &prcc->ListRoot)
                    {
                        SF_ASSERT(cur->IsInList());
                        const RefCountBaseGC<Stat>* next = cur->pNext;
                        if (cnt != 0 || !cur->IsDeleteLast())
                        {
                            cur->RemoveFromList();
                            cur->ClearInList(prcc);
                            SF_ASSERT(cur->IsDelayedRelease());
                            cur->ClearDelayedRelease();
                            prcc->pLastPtr = prcc->ListRoot.pPrev;
                            cur->ReleaseInternal(GFC_GC_DEBUG_PASS_PARAMS);
                        }
                        cur = next;
                    }
                    // second pass maybe required to remove "delete last" objs
                    ++cnt;
                    //SF_ASSERT(cnt <= 2 || prcc->ListRoot.pNext == &prcc->ListRoot);
                    if (cnt == 1)
                    {
                        // Free "this" between iterations. The next iteration will free "DeleteLast"
                        // objects if any. 
                        FreeThis(prcc GFC_GC_DEBUG_PASS_PARAM);
                        // "this" became invalid since now!
                    }
                } while (prcc->ListRoot.pNext != &prcc->ListRoot);

                prcc->ListRoot.ClearInList(NULL);
                return;
            }
            else
            {
                // ... yes: just add children to the list with flag DelayedRelease
                ExecuteForEachChild_GC(pRCC, Operation_Release); 
            }
        }
#endif //SF_USE_RECURSIONLESS_RELEASE

        // Release all children
        // Old logic.
        //ExecuteForEachChild_GC(pRCC, Operation_Release);

        FreeThis(pRCC GFC_GC_DEBUG_PASS_PARAM);

        // Old logic.
        //Free_GC(GFC_GC_DEBUG_PASS_PARAMS);

        // New logic.
        //delete this;
    }
    else
    {
        SF_ASSERT(!IsInState(State_Removed));
        // Possible root
        if (!IsInState(State_Root))
        {
            //SF_ASSERT(!pRCC->IsCollecting());
            // Add to the array of roots, if not buffered yet
            GFC_GC_COND_TRACE(!IsBuffered(), "Adding possible root");
            SetState(State_Root);
            // If the obj is in list this means it is being released during the collection.
            // In this case, just mark it as root and it will be added into "Roots" later, by 
            // Collect.
            if (!IsInList() && !IsBuffered())
            {
                pRCC->AddRoot(this);
            }
        }
    }
}

template <int Stat>
inline
void RefCountBaseGC<Stat>::MarkInCycle(Collector* prcc GFC_GC_DEBUG_PARAMS) const
{
    if (!IsInState(State_InCycle))
    {
        GFC_GC_TRACE("Marking 'incycle' ");
        SF_ASSERT(prcc);
        SetState(State_InCycle);

        ExecuteForEachChild_GC(prcc, Operation_MarkInCycle);
    }
}

template <int Stat>
void RefCountCollector<Stat>::ReinsertToList(const RefCountBaseGC<Stat>* pchild)
{
    if (pchild->IsInList())
    {
        // first, remove
        pchild->pPrev->pNext = pchild->pNext;
        pchild->pNext->pPrev = pchild->pPrev;
        SF_ASSERT(pLastPtr != pchild);

        SF_ASSERT(pLastPtr);
        pchild->pPrev          = pLastPtr->pNext->pPrev; // this
        pchild->pNext          = pLastPtr->pNext;
        pLastPtr->pNext->pPrev = pchild;
        pLastPtr->pNext        = pchild;  
    }
}

template <int Stat>
void RefCountCollector<Stat>::AddToList(const RefCountBaseGC<Stat>* pchild)
{
    if (!pchild->IsInList())
    {
//         if (strcmp(pchild->GetAS3ObjectType(), "VMAbcFile") == 0)
//         {
//             printf("!!! %s\n", pchild->GetAS3ObjectName().ToCStr());
//         }
        SF_ASSERT(pLastPtr);
        pchild->pPrev          = pLastPtr->pNext->pPrev; // this
        pchild->pNext          = pLastPtr->pNext;
        pLastPtr->pNext->pPrev = pchild;
        pLastPtr->pNext        = pchild;  
        pLastPtr  = pchild;
        pchild->SetInList();
    }
}

template <int Stat>
inline
void RefCountCollector<Stat>::AddDelayedReleaseProxy(PtrReleaseProxy<Stat>* preleaseProxy)
{
    if (preleaseProxy)
    {
        SF_ASSERT(!preleaseProxy->pNext && HeadDelayedPtrRelease != preleaseProxy);
        if (!HeadDelayedPtrRelease)
        {
            HeadDelayedPtrRelease = preleaseProxy;
            preleaseProxy->pNext  = NULL;
        }
        else
        {
            preleaseProxy->pNext  = HeadDelayedPtrRelease;
            HeadDelayedPtrRelease = preleaseProxy;
        }
    }
}

template <int Stat>
inline
void RefCountCollector<Stat>::CleanDelayedReleaseProxies()
{
    Ptr<PtrReleaseProxy<Stat> > pcur = HeadDelayedPtrRelease;
    HeadDelayedPtrRelease = NULL;
    if (pcur)
        Flags |= Flags_RequireMoreCollect;

    while(pcur)
    {
        Ptr<PtrReleaseProxy<Stat> > pnext = pcur->pNext;
        pcur->pNext = NULL;
        // if collectable ptr is being released, we might need an additional collection later.
        //if (pcur->Data || pcur->Data2)
        //    Flags |= Flags_RequireMoreCollect;
        pcur = pnext;
    }
}

template <int Stat>
void RefCountCollector<Stat>::AddRoot(const RefCountBaseGC<Stat>* root)
{
    // AddRoot can't be executed from inside MarkInCycle stage.
    // However, it might be called by a Dictionary (with weak refs), so
    // check and do nothing.
    if (IsMarkInCycle())
        return;

    SF_ASSERT(!root->IsDelayedRelease());
    // check if we have free roots; if so - reuse first of it.
    if (FirstFreeRootIndex != SF_MAX_UPINT)
    {
        root->SetBuffered((UInt32)FirstFreeRootIndex);

        // update the FirstFreeRootIndex
        union
        {
            const RefCountBaseGC<Stat>* Ptr;
            UPInt                       UPtrValue;
            SPInt                       SPtrValue;
        } u;
        u.Ptr = Roots[FirstFreeRootIndex];
        SF_ASSERT(u.UPtrValue & 1);
        u.SPtrValue >>= 1; // keep the most significant bit, needed to get 
        // 0xFFFFFFFF if shifting the 0xFFFFFFFF (~0u).
        Roots[FirstFreeRootIndex] = root;
        FirstFreeRootIndex = u.UPtrValue;
    }
    else
    {
        // no free roots, just append.
        root->SetBuffered((UInt32)Roots.GetSize()); // save root index for 
        // fast access from Release
        // Append to roots
        Flags |= Flags_AddingRoot;
        if (!Roots.PushBackSafe(root))
        {
            // can't allocate memory for roots.
            Flags &= ~Flags_AddingRoot;

            // call Collect since Collect was disabled during the PushBack...
            bool collected = Collect();

            // try to PushBack again
            Flags |= Flags_AddingRoot;
            if (!collected || !Roots.PushBackSafe(root))
            {
                // well, still no luck... Clear "buffered", set state "InUse".
                root->ClearBuffered();
                root->SetState(RefCountBaseGC<Stat>::State_InUse);
            }
            Flags &= ~Flags_AddingRoot;
        }
        else
            Flags &= ~Flags_AddingRoot;
    }
}

template <int Stat>
void RefCountCollector<Stat>::RemoveFromRoots(const RefCountBaseGC<Stat>* root)
{
    if (root->IsBuffered() && !root->IsInList())
    {
        GFC_GC_TRACE("bufferred, find it roots and free.");
        UInt32 rootIndex = root->GetRootIndex();

        // We are going to free a buffered root. We already have stored the index of 
        // element in Roots array, lets make sure it is valid by the following ASSERT...
        SF_ASSERT(Roots[rootIndex] == root);

        if (rootIndex + 1 != Roots.GetSize())
        {
            // Now, need to make kind of "free-list". pRCC stores the index of the first
            // free root (not necessary to be physically first). This index points to
            // the element in Roots which is free. This element contains an index of the next 
            // free root, encoded by the following way: bits 31-1 contain the index, bit 0 
            // is set to 1 as an indicator that this is an index and not a pointer.
            union
            {
                RefCountBaseGC<Stat>*   Ptr;
                UPInt                   PtrValue;
            } u;

            // lowest bit (bit 0) set to 1 means this is an index rather than a real ptr.
            // Since all ptrs suppose to be aligned on boundary of 4, it is safe to
            // do so.
            u.PtrValue = (FirstFreeRootIndex << 1) | 1;

            Roots[rootIndex]   = u.Ptr;
            FirstFreeRootIndex = rootIndex;
        }
        else
        {
            // no need in adding root to free list since this is the last one, just
            // resize.
            Roots.Resize(rootIndex); 
        }
        root->ClearBuffered();
    }
}

template <int Stat>
inline
bool RefCountCollector<Stat>::Collect(Stats* pstat)
{
    Flags &= ~Flags_RequireMoreCollect;

    // It is forbidden to call collection if the collector is already
    // collecting or if new root is being added. So, do nothing in 
    // this case.
    if (IsInCollect() || IsAddingRoot() || Roots.GetSize() == 0)
    {
        // already collecting - do nothing.
        if (pstat)
        {
            memset(pstat, 0, sizeof(*pstat));
        }
        return false;
    }
    Flags |= Flags_InCollect;

    GFC_GC_PRINT("++++++++ Starting collecting");
    UPInt  initialNRoots     = 0;
    UPInt  totalKillListSize = 0;
//    Array<const RefCountBaseGC<Stat>* > fin;
    
    // In most cases this loop will make only one iteration per call.
    // But in some cases, processing of kill list may produce new roots
    // to collect. This may happen, for example, when collectible object (A)
    // contains a strong ptr to non-collectible one (B), and that non-collectible
    // object has a Ptr to another collectible object (C) with refcnt > 1.
    // When dtor for A is called, it releases the ptr on B and this cause
    // invocation of Release for C. Release for C will add the pointer to Roots,
    // since refcnt is not 1. In this case the second pass will be required.
    do 
    {
        Flags |= Flags_Collecting;
        
        UPInt i, nroots = Roots.GetSize();
        initialNRoots += (unsigned)nroots;

        pLastPtr = &ListRoot;
        ListRoot.pNext = ListRoot.pPrev = &ListRoot;
        ListRoot.SetInList();

        Flags |= Flags_MarkInCycle;
        // Mark roots stage.
        // For each root from Roots array:
        //   1) if not marked as root - skip (clear "buffered" flag);
        //   2) otherwise, add the object in a doubly-linked list, pFirstPtr is the pointer to the first node,
        //      pLastPtr is the pointer to the last node (or, to the node where a new node should be inserted).
        //   3) simultaneously, mark the root as "in cycle" and add all of its children to the list 
        //      decrementing their refcnt; if a child is already in the list then just decrement refcnt
        //      and mark it as "in cycle".
        //   4) repeat steps 1-4 until end of the list.
        for (i = 0; i < nroots; ++i)
        {
            union
            {
                const RefCountBaseGC<Stat>* Ptr;
                UPInt                       PtrValue;
            } u;
            u.Ptr = Roots[i];
            if (u.PtrValue & 1) 
                continue; // free root, skip
            const RefCountBaseGC<Stat>* cur = u.Ptr;

            if (cur->IsInState(RefCountBaseGC<Stat>::State_Root))
            {
                AddToList(cur);
                while(cur != &ListRoot)
                {
                    SF_ASSERT(!cur->IsDelayedRelease());
                    cur->MarkInCycle(this GFC_GC_PARAM_START_VAL);
                    cur = cur->pNext;
                }
            }
            else
            {
                cur->ClearBuffered();
                if (cur->IsInState(RefCountBaseGC<Stat>::State_InUse) && cur->IsRefCntZero())
                {
                    // shouldn't get here, since Release frees immediately now
                    SF_ASSERT(0);
                }
            }
        }
        Flags &= ~Flags_MarkInCycle;

        FirstFreeRootIndex = SF_MAX_UPINT;
        // cleanup roots, we don't need them anymore
        Roots.Resize(0);

        // Scan objects in the list and determine if they are garbage or not. If not - restore refcnt.
        // Each object might be visited several times, as well as incrementing may occur as many times
        // as many references to the particular object exists. The very same object might be marked 
        // as "garbage" first but later it might be re-marked as "in use" if a reference to is found.
        // The algorithm in general is as follows:
        // For each object in the list do:
        // 1) if refcnt zero - mark the object as "garbage"
        // 2) otherwise, mark the current object as "in use and for each child do
        //      a) increment refcnt
        //      b) if the child is not marked as "in use" yet then mark it and re-insert after the 
        //         current object thus it will be revisited later (to scan its children too).
        // 3) proceed to the next object in the list; this might be an object recently re-inserted at
        //    step 2b. If this is happening then this object is already marked as "in use" and refcnt > 0,
        //    thus its children will be visited as well (at step 2 of next iteration).
        const RefCountBaseGC<Stat>* cur = ListRoot.pNext;
        bool hasFinalize = false;
        while(cur != &ListRoot)
        {
            if ((cur->RefCount & RefCountBaseGC<Stat>::Mask_RefCount) > 0)
            {
                cur->SetState(RefCountBaseGC<Stat>::State_InUse);
                pLastPtr = cur; // to perform reinserting after cur
                cur->ExecuteForEachChild_GC(this, RefCountBaseGC<Stat>::Operation_ScanInUse);
            }
            else
            {
                if (cur->HasFinalize())
                    hasFinalize = true;
                cur->SetState(RefCountBaseGC<Stat>::State_Garbage);
                GFC_GC_TRACE("Marking garbage ");
            }

            cur = cur->pNext;
        }

        // Pre-process for Finalize. If we have a node, marked as Garbage (i.e. refcnt == 0 at this
        // point, after MarkInCycle execution), and this node has Finalize_GC then we need
        // to restore refcounters of all its children and mark the node 'ToBeFinalized'. Later on,
        // it will be added as a root and Finalize_GC will be called. Once it is called, the flags
        // 'HasFinalize' and 'ToBeFinalized' will be cleaned up and the node will be collected as
        // usual.
        if (hasFinalize)
        {
            cur = ListRoot.pNext;
            pLastPtr = &ListRoot;
            while(cur != &ListRoot)
            {
                if (cur->IsInState(RefCountBaseGC<Stat>::State_Garbage))
                {
                    if (cur->HasFinalize())
                    {
                        cur->SetState(RefCountBaseGC<Stat>::State_InUse);
                        pLastPtr = cur; // to perform reinserting after cur
                        cur->ExecuteForEachChild_GC(this, RefCountBaseGC<Stat>::Operation_ScanTempInUse);
                        cur->MarkToBeFinalized();
                    }
                }
                else if (cur->IsInState(RefCountBaseGC<Stat>::State_TempInUse))
                {
                    cur->SetState(RefCountBaseGC<Stat>::State_InUse);
                    pLastPtr = cur; // to perform reinserting after cur
                    cur->ExecuteForEachChild_GC(this, RefCountBaseGC<Stat>::Operation_ScanTempInUse);
                }
                cur = cur->pNext;
            }
        }

        // process the list, clean it up, free garbage.
        cur = ListRoot.pNext;
        pLastPtr = &ListRoot;
        while(cur != &ListRoot)
        {
            const RefCountBaseGC<Stat>* next = cur->pNext;
            if (cur->IsInState(RefCountBaseGC<Stat>::State_Garbage))
            {
                // If "delete last" - do not remove, will be processed later.
                if (!cur->IsDeleteLast())
                {
                    cur->RemoveFromList();
                    // This Free may cause adding DelayedRelease nodes in the list
                    // so will need to check for them
                    HandleWeakRef(cur);
                    cur->Free_GC(this GFC_GC_PARAM_VAL);
                    ++totalKillListSize;
                }
                //else
                //    SF_ASSERT(1); // dbg code
            }
            else 
            {
                cur->RemoveFromList();
                cur->ClearInList(this);
                if (cur->IsDelayedRelease())
                {
                    // if DelayedRelease then Decrement was already called.
                    // Just clear the flag and call ReleaseInternal.
                    cur->ClearDelayedRelease();
                    cur->ReleaseInternal();
                }
                else
                {
                    if (cur->ToBeFinalized())
                    {
                        // Add as root again, if it has finalize. These roots will be
                        // processed below, at the end of the loop.
                        AddRoot(cur);
                    }
                    else
                    {
                        if (cur->IsInState(RefCountBaseGC<Stat>::State_Root))
                            // delayed root addition, see Release
                            AddRoot(cur);
                        else
                            cur->ClearBuffered();
                    }
                }
            }

            cur = next;
        }

        // second pass to remove "delete last" ones
        cur = ListRoot.pNext;
        while(cur != &ListRoot)
        {
            SF_ASSERT(cur->IsDeleteLast());
            const RefCountBaseGC<Stat>* next = cur->pNext;

            // This Free may cause adding DelayedRelease nodes in the list
            // so will need to check for them
            HandleWeakRef(cur);
            cur->Free_GC(this GFC_GC_PARAM_VAL);
            ++totalKillListSize;

            cur = next;
        }

        pLastPtr = &ListRoot;
        ListRoot.ClearInList(NULL);

        Flags &= ~Flags_Collecting;
        FirstFreeRootIndex = SF_MAX_UPINT;

        // Here we execute Finalize_GC for 
        if (hasFinalize)
        {
            nroots = Roots.GetSize();
            for (i = 0; i < nroots; ++i)
            {
                union
                {
                    const RefCountBaseGC<Stat>* Ptr;
                    UPInt                       PtrValue;
                } u;
                u.Ptr = Roots[i];
                if (u.PtrValue & 1) 
                    continue; // skip
                const RefCountBaseGC<Stat>* cur = u.Ptr;
                
                if (cur->ToBeFinalized())
                {
                    SF_ASSERT(cur->HasFinalize());
                    cur->ClearFinalize(); // avoid the second finalization
                    cur->Increment(); // avoid releasing during Finalize
                    const_cast<RefCountBaseGC<Stat>* >(cur)->Finalize_GC();
                    cur->Decrement();
                    
                    // Make sure, the node is still in Root state to process it 
                    // at next iteration as usual. It must have 'Buffered' flag set.
                    SF_ASSERT(cur->IsBuffered());
                    cur->SetState(RefCountBaseGC<Stat>::State_Root);
                }
            }
        }
    } while (Roots.GetSize() > 0);
    
    if (pstat)
    {
        // save stats. Note totalKillListSize might be greater than initialNRoots,
        // since it might free some non-root elements as well. So, just correct RootsFreedTotal
        // to avoid negative difference between RootsNumber and RootsFreedTotal.
        pstat->RootsNumber              = (unsigned)initialNRoots;
        pstat->RootsFreedTotal          = Alg::Min((unsigned)initialNRoots, (unsigned)totalKillListSize);
    }
    Flags &= ~Flags_InCollect;
    CleanDelayedReleaseProxies();
    GFC_GC_PRINT("-------- Finished collecting\n");
    return true;
}

template <int Stat>
inline
void RefCountCollector<Stat>::ShrinkRoots()
{
     if (Roots.GetSize() == 0)
         Roots.ClearAndRelease();
}

class ASRefCountCollector : public RefCountCollector<Mem_Stat>
{
    unsigned    FrameCnt;
    unsigned    MaxRootCount;
    unsigned    PeakRootCount;
    unsigned    LastRootCount;
    unsigned    LastCollectedRoots;
    unsigned    LastPeakRootCount;
    unsigned    TotalFramesCount;
    unsigned    LastCollectionFrameNum;

    unsigned    PresetMaxRootCount;
    unsigned    MaxFramesBetweenCollections;

    bool        CollectionScheduledFlag;

    void Collect(Stats* pstat = NULL)
    {
        RefCountCollector<Mem_Stat>::Collect(pstat);
    }

public:
    ASRefCountCollector();

    void SetParams(unsigned frameBetweenCollections, unsigned maxRootCount);

    // This method should be called every frame (every full advance). 
    // It evaluates necessity of collection and performs it if necessary.
    void AdvanceFrame(unsigned* movieFrameCnt, unsigned* movieLastCollectFrame);

    // Forces collection.
    void ForceCollect();
    
    // Forces emergency collect. This method is called when memory heap cap is 
    // reached. It tries to free as much memory as possible.
    void ForceEmergencyCollect();

    void ScheduleCollect() { CollectionScheduledFlag = true; }
    void CollectIfScheduled()
    {
        if (CollectionScheduledFlag)
        {
            CollectionScheduledFlag = false;
            // ForceCollect may set CollectionScheduledFlag back to true.
            ForceCollect();
        }
    }

#if defined(SF_BUILD_DEBUG) || defined(SF_BUILD_DEBUGOPT)
    void CollectRoots(class ObjectCollector&);
#endif
};

typedef RefCountBaseGC<Mem_Stat> GASRefCountBaseType;

class GASRefCountBase;

// Helper for making objects that can have WEAK POINTERS.
class WeakProxy : public NewOverrideBase<Mem_Stat>
{
public:
    WeakProxy(GASRefCountBase* pobject) : RefCount(1), pObject(pobject) {}

public:
    // WeakPtr calls this to determine if its pointer is valid or not
    bool IsAlive() const { return (pObject != 0); }

    // Objects call this to inform of their death
    void NotifyObjectDied() { pObject = NULL; }

    GASRefCountBase* GetObject() const { return pObject; }

    void AddRef() const
    {   
        ++RefCount; 
    }

    void Release() const
    {
        if (--RefCount == 0)
            delete this;
    }    

private:
    WeakProxy(const WeakProxy& other);
    void operator=(const WeakProxy& other);

private:
    mutable int      RefCount;
    GASRefCountBase* pObject;
}; // class WeakProxy

template <int Stat>
inline
void RefCountCollector<Stat>::HandleWeakRef(const RefCountBaseGC<Stat>* pcur)
{
    // Handle weak references.
    if (pcur->HasWeakRef()) {
        // We shouldn't handle weak pointers in a destructor of pcur.
        pcur->SetNotWeakRef();

        WeakProxy* wp = NULL;

        if (WProxyHash.Get((GASRefCountBase*)pcur, &wp) && wp)
        {
            wp->NotifyObjectDied();
            wp->Release();
            WProxyHash.Remove((GASRefCountBase*)pcur);
        }
    }
}

class GASRefCountBase : public GASRefCountBaseType 
{
public:
    GASRefCountBase(ASRefCountCollector* pcc) :
      GASRefCountBaseType(pcc) {}
    ~GASRefCountBase();

public:
    Pickable<WeakProxy> CreateWeakProxy();

private:
    GASRefCountBase(const GASRefCountBase&);
}; // class GASRefCountBase

///////////////////////////////////////////////////////////////////////////
void ForEachChild_GC(RefCountCollector<Mem_Stat>*, const ValueArray& v, RefCountBaseGC<Mem_Stat>::GcOp op SF_DEBUG_ARG(const RefCountBaseGC<Mem_Stat>&));
void ForEachChild_GC(RefCountCollector<Mem_Stat>*, const ValueArrayDH& v, RefCountBaseGC<Mem_Stat>::GcOp op SF_DEBUG_ARG(const RefCountBaseGC<Mem_Stat>&));

void ForEachChild_GC_Internal(RefCountCollector<Mem_Stat>*, const Value& v, RefCountBaseGC<Mem_Stat>::GcOp op SF_DEBUG_ARG(const RefCountBaseGC<Mem_Stat>&));

inline
void ForEachChild_GC(RefCountCollector<Mem_Stat>* prcc,  
                     const Value& v, RefCountBaseGC<Mem_Stat>::GcOp op 
                     SF_DEBUG_ARG(const RefCountBaseGC<Mem_Stat>& parent))
{
    if (v.IsGarbageCollectable() && !v.IsWeakRef())
        ForEachChild_GC_Internal(prcc, v, op SF_DEBUG_ARG(parent));
}

template <typename T, int Stat>   
inline
void ForEachChild_GC(RefCountCollector<Stat>* prcc, 
                     const SPtr<T>& v, typename RefCountBaseGC<Stat>::GcOp op 
                     SF_DEBUG_ARG(const RefCountBaseGC<Stat>& parent))
{
    if (v)
        (*op)(prcc, const_cast<const AS3::RefCountBaseGC<Stat>**>(reinterpret_cast<AS3::RefCountBaseGC<Stat>**>(v.GetRawPtr())) SF_DEBUG_ARG(parent));
}

template <typename T, int Stat>   
inline
void ForEachChild_GC_Const(RefCountCollector<Stat>* prcc, 
                           const SPtr<const T>& v, typename RefCountBaseGC<Stat>::GcOp op
                           SF_DEBUG_ARG(const RefCountBaseGC<Stat>& parent))
{
    if (v)
        (*op)(prcc, reinterpret_cast<const AS3::RefCountBaseGC<Stat>**>(v.GetRawPtr()) SF_DEBUG_ARG(parent));
}

template <typename T, int Stat>   
inline
void ForEachChild_GC(RefCountCollector<Stat>* prcc, const Ptr<T>& v, typename RefCountBaseGC<Stat>::GcOp op)
{
    if (v)
        v->ForEachChild_GC(prcc, op);
}

template <typename T, int Stat>   
inline
void ForEachChild_GC_Const(RefCountCollector<Stat>* prcc, const Ptr<const T>& v, typename RefCountBaseGC<Stat>::GcOp op)
{
    if (v)
        v->ForEachChild_GC(prcc, op);
}

/////////////////////////////////////////////////////////////////////////// 
// APtr is similar to SPtr, except it can behave as a raw pointer ( no
// AddRef/Release called )

template <typename T>
class APtr
{
public:
    typedef T       ObjType;
    typedef APtr<T> SelfType;
    enum Type {Strong, Raw};

public:
    // Constructors.

    APtr(const SPtr<T>& sptr, Type t = Strong)
        : ptr((sptr.AddRef(), sptr.Get()))
        , PtrType(t)
    {
    }
    APtr(T* p = NULL, Type t = Strong)
        : ptr(p ? p->AddRef(), p : p)
        , PtrType(t)
    {
        SF_ASSERT(p == NULL || (Scaleform::UPInt)p > 4);
    }
    // Copy constructor.
    APtr(const APtr& other)
        : ptr((other.AddRef(), other.ptr))
        , PtrType(other.PtrType)
    {
    }
    ~APtr()
    {
        Release();
    }

public:
    Type GetType() const
    {
        return PtrType;
    }
    void SetTypeStrong()
    {
        if (PtrType != Strong)
        {
            PtrType = Strong;

            // Make it a strong pointer
            AddRef();
        }
    }
    void SetTypeRaw()
    {
        if (PtrType != Raw)
        {
            // Make it a raw pointer
            Release();

            PtrType = Raw;
        }
    }

public:
    SelfType& operator =(T* p)
    {
        return SetPtr(p);
    }
    SelfType& operator =(const SelfType& other)
    {
        return Set(other);
    }
    template <typename OT>
    SelfType& operator =(const SPtr<OT>& sptr)
    {
        return Set(sptr);
    }
    SelfType& SetPtr(T* p)
    {
        if (p != ptr)
        {
            SF_ASSERT(p == NULL || (Scaleform::UPInt)p > 4);

            Release();
            if (p && PtrType == Strong)
                p->AddRef();

            ptr = p;
        }

        return *this;
    }
    SelfType& Set(const SelfType& other)
    {
        if (&other != this)
        {
            Release();
            other.AddRef();

            ptr = other.ptr;
            PtrType = other.PtrType;
        }

        return *this;
    }
    template <typename OT>
    SelfType& Set(const SPtr<OT>& sptr)
    {
        if (sptr.GetPtr() != ptr)
        {
            Release();
            // !!! This call should be here.
            //sptr.AddRef().

            ptr = sptr.GetPtr();
            AddRef();
        }

        return *this;
    }

    T* operator->() const
    {
        return ptr;
    }
    T& operator*() const
    {
        SF_ASSERT(ptr);
        return *ptr;
    }

    // Obtain pointer reference directly, for D3D interfaces
    T*& GetRawRef() { return ptr; }
    T** GetRawPtr() const { return &ptr; }
    T* Get() const
    {
        return ptr;
    }
    // Conversion
    operator T*() const
    {
        return ptr;
    }

private:
    void AddRef() const
    {
        if (ptr && PtrType == Strong)
            ptr->AddRef();
    }
    void Release()
    {
        if (ptr && PtrType == Strong)
        {
            if ((Scaleform::UPInt)ptr & 1)
                ptr = (T*)((Scaleform::UPInt)ptr - 1);
            else
                ptr->Release();
        }
    }
private:
    mutable T*      ptr;
    mutable Type    PtrType;
};


}}} // namespace Scaleform { namespace GFx { namespace AS3 {

#endif // INC_AS3_GC_H

