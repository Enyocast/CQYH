/**************************************************************************

Filename    :   AS3_Abc_ConstPool.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "AS3_Abc_ConstPool.h"
#include "AS3_Abc.h"

namespace Scaleform { namespace GFx { namespace AS3 { namespace Abc 
{

///////////////////////////////////////////////////////////////////////////
ConstPool::ConstPool()
: any_namespace(NS_Public, "")
, any_type(MN_QName, 0, 0)
{
    // We do not need to initialize zero records of all arrays in const_pool.
    // That will be done by Stream& operator >>(Stream& s, ConstPool& obj)
}


///////////////////////////////////////////////////////////////////////////
const UInt8 StringView::Empty = 0;

StringDataPtr StringView::ToStringDataPtr() const
{
    const UInt8* d = Data;
    const int size = ReadU30(d);
    return ReadStringPtr(d, size);
}

///////////////////////////////////////////////////////////////////////////
double ConstPool::GetDouble(UPInt ind) const
{
    SF_ASSERT(ind < DoubleCount);

    if (ind)
    {
        const UInt8* d = Doubles;

        --ind;
        d += ind * 8;

        return ReadDouble(d);
    }

    // if ind == 0.
    return 0.0;
}

UPInt NamespaceSetInfo::GetSize() const
{
    UInt32 result;
    const UInt8* ptr = Data;

    Read(ptr, result);

    return result;
}

}}}} // namespace Scaleform { namespace GFx { namespace AS3 { namespace Abc {


