//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_InterpolationMethod.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_InterpolationMethod.h"
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
    InterpolationMethod::InterpolationMethod(ClassTraits::Traits& t)
    : Class(t)
    , LINEAR_RGB("linearRGB")
    , RGB("rgb")
    {
//##protect##"class_::InterpolationMethod::InterpolationMethod()"
//##protect##"class_::InterpolationMethod::InterpolationMethod()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo InterpolationMethod::mi[InterpolationMethod::MemberInfoNum] = {
        {"LINEAR_RGB", OFFSETOF(Classes::InterpolationMethod, LINEAR_RGB), SlotInfo::BT_ConstChar, 1},
        {"RGB", OFFSETOF(Classes::InterpolationMethod, RGB), SlotInfo::BT_ConstChar, 1},
    };

    InterpolationMethod::InterpolationMethod(VM& vm)
    : Traits(vm, InterpolationMethodCI)
    {
//##protect##"ClassTraits::InterpolationMethod::InterpolationMethod()"
//##protect##"ClassTraits::InterpolationMethod::InterpolationMethod()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, InterpolationMethodCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::InterpolationMethod(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> InterpolationMethod::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) InterpolationMethod(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo InterpolationMethodCI = {
    ClassInfo::CompileTime,
    "InterpolationMethod", "flash.display", &ObjectCI,
    ClassTraits::InterpolationMethod::MakeClassTraits,
    0,
    ClassTraits::InterpolationMethod::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::InterpolationMethod::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

