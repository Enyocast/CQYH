//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_PixelSnapping.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_PixelSnapping.h"
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
    PixelSnapping::PixelSnapping(ClassTraits::Traits& t)
    : Class(t)
    , ALWAYS("always")
    , AUTO("auto")
    , NEVER("never")
    {
//##protect##"class_::PixelSnapping::PixelSnapping()"
//##protect##"class_::PixelSnapping::PixelSnapping()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo PixelSnapping::mi[PixelSnapping::MemberInfoNum] = {
        {"ALWAYS", OFFSETOF(Classes::PixelSnapping, ALWAYS), SlotInfo::BT_ConstChar, 1},
        {"AUTO", OFFSETOF(Classes::PixelSnapping, AUTO), SlotInfo::BT_ConstChar, 1},
        {"NEVER", OFFSETOF(Classes::PixelSnapping, NEVER), SlotInfo::BT_ConstChar, 1},
    };

    PixelSnapping::PixelSnapping(VM& vm)
    : Traits(vm, PixelSnappingCI)
    {
//##protect##"ClassTraits::PixelSnapping::PixelSnapping()"
//##protect##"ClassTraits::PixelSnapping::PixelSnapping()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, PixelSnappingCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::PixelSnapping(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> PixelSnapping::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) PixelSnapping(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo PixelSnappingCI = {
    ClassInfo::CompileTime,
    "PixelSnapping", "flash.display", &ObjectCI,
    ClassTraits::PixelSnapping::MakeClassTraits,
    0,
    ClassTraits::PixelSnapping::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::PixelSnapping::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

