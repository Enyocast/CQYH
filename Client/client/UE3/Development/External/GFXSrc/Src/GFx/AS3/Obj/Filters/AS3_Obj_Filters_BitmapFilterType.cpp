//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_BitmapFilterType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_BitmapFilterType.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes
{
    BitmapFilterType::BitmapFilterType(ClassTraits::Traits& t)
    : Class(t)
    , FULL("full")
    , INNER("inner")
    , OUTER("outer")
    {
//##protect##"class_::BitmapFilterType::BitmapFilterType()"
//##protect##"class_::BitmapFilterType::BitmapFilterType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo BitmapFilterType::mi[BitmapFilterType::MemberInfoNum] = {
        {"FULL", OFFSETOF(Classes::BitmapFilterType, FULL), SlotInfo::BT_ConstChar, 1},
        {"INNER", OFFSETOF(Classes::BitmapFilterType, INNER), SlotInfo::BT_ConstChar, 1},
        {"OUTER", OFFSETOF(Classes::BitmapFilterType, OUTER), SlotInfo::BT_ConstChar, 1},
    };

    BitmapFilterType::BitmapFilterType(VM& vm)
    : Traits(vm, BitmapFilterTypeCI)
    {
//##protect##"ClassTraits::BitmapFilterType::BitmapFilterType()"
//##protect##"ClassTraits::BitmapFilterType::BitmapFilterType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, BitmapFilterTypeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::BitmapFilterType(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> BitmapFilterType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) BitmapFilterType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo BitmapFilterTypeCI = {
    ClassInfo::CompileTime,
    "BitmapFilterType", "flash.filters", &ObjectCI,
    ClassTraits::BitmapFilterType::MakeClassTraits,
    0,
    ClassTraits::BitmapFilterType::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::BitmapFilterType::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

