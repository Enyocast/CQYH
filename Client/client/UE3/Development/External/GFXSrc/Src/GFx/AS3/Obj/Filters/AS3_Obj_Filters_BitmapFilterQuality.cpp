//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_BitmapFilterQuality.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_BitmapFilterQuality.h"
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
    BitmapFilterQuality::BitmapFilterQuality(ClassTraits::Traits& t)
    : Class(t)
    , HIGH(3)
    , LOW(1)
    , MEDIUM(2)
    {
//##protect##"class_::BitmapFilterQuality::BitmapFilterQuality()"
//##protect##"class_::BitmapFilterQuality::BitmapFilterQuality()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo BitmapFilterQuality::mi[BitmapFilterQuality::MemberInfoNum] = {
        {"HIGH", OFFSETOF(Classes::BitmapFilterQuality, HIGH), SlotInfo::BT_Int, 1},
        {"LOW", OFFSETOF(Classes::BitmapFilterQuality, LOW), SlotInfo::BT_Int, 1},
        {"MEDIUM", OFFSETOF(Classes::BitmapFilterQuality, MEDIUM), SlotInfo::BT_Int, 1},
    };

    BitmapFilterQuality::BitmapFilterQuality(VM& vm)
    : Traits(vm, BitmapFilterQualityCI)
    {
//##protect##"ClassTraits::BitmapFilterQuality::BitmapFilterQuality()"
//##protect##"ClassTraits::BitmapFilterQuality::BitmapFilterQuality()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, BitmapFilterQualityCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::BitmapFilterQuality(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> BitmapFilterQuality::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) BitmapFilterQuality(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo BitmapFilterQualityCI = {
    ClassInfo::CompileTime,
    "BitmapFilterQuality", "flash.filters", &ObjectCI,
    ClassTraits::BitmapFilterQuality::MakeClassTraits,
    0,
    ClassTraits::BitmapFilterQuality::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::BitmapFilterQuality::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

