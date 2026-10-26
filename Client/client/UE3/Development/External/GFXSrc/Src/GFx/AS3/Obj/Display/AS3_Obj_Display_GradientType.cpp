//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_GradientType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_GradientType.h"
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
    GradientType::GradientType(ClassTraits::Traits& t)
    : Class(t)
    , LINEAR("linear")
    , RADIAL("radial")
    {
//##protect##"class_::GradientType::GradientType()"
//##protect##"class_::GradientType::GradientType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo GradientType::mi[GradientType::MemberInfoNum] = {
        {"LINEAR", OFFSETOF(Classes::GradientType, LINEAR), SlotInfo::BT_ConstChar, 1},
        {"RADIAL", OFFSETOF(Classes::GradientType, RADIAL), SlotInfo::BT_ConstChar, 1},
    };

    GradientType::GradientType(VM& vm)
    : Traits(vm, GradientTypeCI)
    {
//##protect##"ClassTraits::GradientType::GradientType()"
//##protect##"ClassTraits::GradientType::GradientType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, GradientTypeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::GradientType(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> GradientType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) GradientType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo GradientTypeCI = {
    ClassInfo::CompileTime,
    "GradientType", "flash.display", &ObjectCI,
    ClassTraits::GradientType::MakeClassTraits,
    0,
    ClassTraits::GradientType::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::GradientType::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

