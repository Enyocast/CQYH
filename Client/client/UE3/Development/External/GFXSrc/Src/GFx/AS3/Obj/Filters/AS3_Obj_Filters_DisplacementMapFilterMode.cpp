//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_DisplacementMapFilterMode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_DisplacementMapFilterMode.h"
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
    DisplacementMapFilterMode::DisplacementMapFilterMode(ClassTraits::Traits& t)
    : Class(t)
    , CLAMP("clamp")
    , COLOR("color")
    , IGNORE("ignore")
    , WRAP("wrap")
    {
//##protect##"class_::DisplacementMapFilterMode::DisplacementMapFilterMode()"
//##protect##"class_::DisplacementMapFilterMode::DisplacementMapFilterMode()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo DisplacementMapFilterMode::mi[DisplacementMapFilterMode::MemberInfoNum] = {
        {"CLAMP", OFFSETOF(Classes::DisplacementMapFilterMode, CLAMP), SlotInfo::BT_ConstChar, 1},
        {"COLOR", OFFSETOF(Classes::DisplacementMapFilterMode, COLOR), SlotInfo::BT_ConstChar, 1},
        {"IGNORE", OFFSETOF(Classes::DisplacementMapFilterMode, IGNORE), SlotInfo::BT_ConstChar, 1},
        {"WRAP", OFFSETOF(Classes::DisplacementMapFilterMode, WRAP), SlotInfo::BT_ConstChar, 1},
    };

    DisplacementMapFilterMode::DisplacementMapFilterMode(VM& vm)
    : Traits(vm, DisplacementMapFilterModeCI)
    {
//##protect##"ClassTraits::DisplacementMapFilterMode::DisplacementMapFilterMode()"
//##protect##"ClassTraits::DisplacementMapFilterMode::DisplacementMapFilterMode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, DisplacementMapFilterModeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::DisplacementMapFilterMode(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> DisplacementMapFilterMode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DisplacementMapFilterMode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo DisplacementMapFilterModeCI = {
    ClassInfo::CompileTime,
    "DisplacementMapFilterMode", "flash.filters", &ObjectCI,
    ClassTraits::DisplacementMapFilterMode::MakeClassTraits,
    0,
    ClassTraits::DisplacementMapFilterMode::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::DisplacementMapFilterMode::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

