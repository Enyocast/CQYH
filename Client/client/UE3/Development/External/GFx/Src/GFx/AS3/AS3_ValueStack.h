/**************************************************************************

Filename    :   AS3_ValueStack.h
Content     :   
Created     :   Mar, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_AS3_ValueArray_H
#define INC_AS3_ValueArray_H

#include "AS3_Value.h"

namespace Scaleform { namespace GFx { namespace AS3 
{

class ValueStack
{
    friend class Value;
    friend class CallFrame;

public:
    typedef Value ValueType;
    enum {DefPageSize = 64};

    // Page structure. This structure is SF_ALLOC'ed and NOT new'd because 
    // we need to manage construction/cleanup of T values manually.    
    struct Page
    {
        UInt16      ReservationNum; // Number of reservations.
        UInt16      PageSize; // Total number of values
        // Last pFirst value before switching to a new page.
        SF_DEBUG_CODE(ValueType* pFirst;)
        // Last pCurrent value before switching to a new page.
        ValueType*  pCurrent;
        Page*       pNext;
        Page*       pPrev;
        ValueType   Values[1]; // Actual values.
    };

public:
    ValueStack();
    ~ValueStack();

public:
    void Reserve(UInt16 n);
    void ReleaseReserved(SF_DEBUG_CODE(UInt16 prevReservNum) SF_DEBUG_ARG(ValueType* first));
    // Pop values in case of exception.
    void PopReserved(ValueType* current);

    // ***** High-performance Stack Access

    SF_INLINE Value* GetCurrent() const { return pCurrent; }
    SF_DEBUG_CODE(SF_INLINE bool IsValid() const { return GetSize() <= GetNumOfReservedElem(); })

    SF_DEBUG_CODE(SF_INLINE Value* GetFirst() const { return pFirst; } )
    SF_DEBUG_CODE(SF_INLINE UPInt GetSize() const { return pCurrent + 1 - pFirst; } )
    SF_DEBUG_CODE(UInt16 GetNumOfReservedElem() const { return NumOfReservedElem; } )

    // Top0() and Top1() are used most commonly to access the stack.
    // Inline and optimize them as much as possible.

    SF_INLINE Value&   Top0() const
    {        
        SF_ASSERT(pFirst <= pCurrent);
        return *pCurrent;
    }

    SF_INLINE Value&   Top1() const
    {
        SF_ASSERT(pFirst <= pCurrent - 1);
        return *(pCurrent - 1);     
    }
    SF_INLINE Value&   TopN(UInt16 n) const
    {     
        SF_ASSERT(pFirst <= pCurrent - n);
        return *(pCurrent - n);     
    }

    // Methods below are for compatibility with GFx Array.
    SF_INLINE const Value& Back() const
    {        
        SF_ASSERT(pFirst <= pCurrent);
        return *pCurrent;
    }
    SF_INLINE Value& Back()
    {        
        SF_ASSERT(pFirst <= pCurrent);
        return *pCurrent;
    }

    // Get primitive value from the top of the stack
    template <typename T>
    SF_INLINE T PopPrimitive()
    {
        SF_ASSERT(pFirst <= pCurrent);
        // Get result and forget the value.
        return *pCurrent--;
    }

    // Push default value.
    SF_INLINE void PushBack()
    {
        SF_ASSERT(GetSize() < NumOfReservedElem);
        ++pCurrent;
        Construct<ValueType>(pCurrent);
    }

    SF_INLINE void PushBack(const ValueType& val)
    {
        SF_ASSERT(GetSize() < NumOfReservedElem);
        ++pCurrent;
        // Use copy constructor to initialize stack top.
        Construct(pCurrent, val);
    }

    SF_INLINE void PickPushBack(ValueType& val)
    {
        SF_ASSERT(GetSize() < NumOfReservedElem);
        ++pCurrent;
        // Use pick constructor to initialize stack top.
        ::new(pCurrent) ValueType(val, PickValue);
    }

    // Push back not reference counted value.
    SF_INLINE void PushBackNRC(ValueType& val)
    {
        SF_ASSERT(GetSize() < NumOfReservedElem);
        ++pCurrent;
        ::new(pCurrent) ValueType(val, ValueType::NotRefCounted);
    }

    // Pop one element from stack. 
    SF_INLINE void PopBack()
    {
        Scaleform::Destruct(pCurrent);
        SF_ASSERT(pFirst <= pCurrent);
        --pCurrent;
    }

    SF_INLINE void PopBack2()
    {
        Scaleform::Destruct(pCurrent);
        SF_ASSERT(pFirst <= pCurrent);
        --pCurrent;
        Scaleform::Destruct(pCurrent);
        SF_ASSERT(pFirst <= pCurrent);
        --pCurrent;
    }

    void    PopBack3()
    {
        Scaleform::Destruct(pCurrent);
        SF_ASSERT(pFirst <= pCurrent);
        --pCurrent;
        Scaleform::Destruct(pCurrent);
        SF_ASSERT(pFirst <= pCurrent);
        --pCurrent;
        Scaleform::Destruct(pCurrent);
        SF_ASSERT(pFirst <= pCurrent);
        --pCurrent;
    }

    // General Pop(number) implementation.
    void    PopBack(unsigned n)
    {
        while(n-- > 0)
            PopBack();
    }

    // General Push(number) implementation.
    // Push default values.
    void    PushBack(unsigned n)
    {
        while(n-- > 0)
            PushBack();
    }

    void    Release0()
    {
        SF_ASSERT(pFirst <= pCurrent);
        --pCurrent;
    }

    void    ReleaseN(UPInt n)
    {
        SF_ASSERT(n <= GetSize());
        pCurrent -= n;
    }

    void    Acquire1()
    {
        SF_ASSERT(GetSize() < NumOfReservedElem);
        ++pCurrent;
        *(UPInt*)pCurrent = 0;
    }

    void    SwapTop()
    {
        Value _1(Top0(), PickValue);
        Top0().PickUnsafe(Top1());
        Top1().PickUnsafe(_1);
    }

private:
    // *** Page allocator.
    Page*   AllocPage(UInt16 pageSize);
    Page*   NewPage(UInt16 pageSize);

private:
    // State stack value pointers for fast access.

    SF_DEBUG_CODE(UInt16     NumOfReservedElem;)
    // Pointer to the current element.
    // In case of a stack initial value should point to an element previous
    // to a first valid pointer so we can safely increase it in Push().
    ValueType*  pCurrent; 
    SF_DEBUG_CODE(ValueType* pFirst;) // First valid value. We need it to trace stack.
    Page*       pCurrentPage; // Pointer to the current page.
    Page*       pReserved; // Already allocated pages in a linked list.
};

///////////////////////////////////////////////////////////////////////////
class ValueRegisterFile
{
    friend class Value;

public:
    typedef Value ValueType;
//     enum {DefPageSize = 128};
    enum {DefPageSize = 64};

    // Page structure. This structure is SF_ALLOC'ed and NOT new'd because 
    // we need to manage construction/cleanup of T values manually.    
    struct Page
    {
        UInt16      CurrPos;
        UInt16      PageSize; // Total number of values
        UInt16      ReservedNum; // Number of already reserved values.
        ValueType*  pCurrent; // Stored current value.
        Page*       pNext;
        Page*       pPrev;
        ValueType   Values[1]; // Actual values.

        // We can have up to sizeof(UInt16) registers.
        UInt16 PopSize()
        {
            SF_ASSERT(CurrPos > 0 && CurrPos <= PageSize);
            return *(reinterpret_cast<const UInt16*>(Values + PageSize) + --CurrPos);
        }
        void PushSize(UInt16 size)
        {
            SF_ASSERT(CurrPos < PageSize);
            *(reinterpret_cast<UInt16*>(Values + PageSize) + CurrPos++) = size;
        }
    };

public:
    ValueRegisterFile();
    ~ValueRegisterFile();

public:
    void Reserve(UInt16 n);
    void ReleaseReserved(UInt16 n);

public:
    // Operators.

    const ValueType& operator [] (UPInt i) const
    {
        return pCurrent[i];
    }

    ValueType& operator [] (UPInt i)
    {
        return pCurrent[i];
    }

    const ValueType& At(UPInt i) const
    { 
        return pCurrent[i];
    }

    ValueType& At(UPInt i) 
    { 
        return pCurrent[i];
    }

    UInt16 GetSize() const { return static_cast<UInt16>(ReservedNum - (pCurrent - pCurrentPage->Values)); }

private:
    // *** Page allocator.
    Page*   AllocPage(UInt16 pageSize);
    Page*   NewPage(UInt16 pageSize);

private:
    UInt16      ReservedNum; // Total number of reserved elements in the current page.
    UInt16      MaxReservedPageSize;
    UInt16      MaxAllocatedPageSize;

    // State stack value pointers for fast access.

    // Pointer to the current element.
    // In case of an array initial value points to an actual first element.
    ValueType*  pCurrent; 
    Page*       pCurrentPage; // Pointer to the current page.
    Page*       pReserved; // Already allocated pages in a linked list.
};

///////////////////////////////////////////////////////////////////////////////
SF_INLINE
Value::Value(ValueStack& v)
: Flags(v.pCurrent->Flags)
, Bonus(v.pCurrent->Bonus)
, value(v.pCurrent->value)
{
    v.Release0();
}

SF_INLINE
void Value::Pick(ValueStack& v)
{
    Release();

    Value& other = v.Top0();
    Flags = other.Flags;
    Bonus = other.Bonus;
    value = other.value;

    v.Release0();
}

SF_INLINE
void Value::PickUnsafe(ValueStack& v)
{
    Value& other = v.Top0();
    Flags = other.Flags;
    Bonus = other.Bonus;
    value = other.value;

    v.Release0();
}

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif // INC_AS3_ValueArray_H

