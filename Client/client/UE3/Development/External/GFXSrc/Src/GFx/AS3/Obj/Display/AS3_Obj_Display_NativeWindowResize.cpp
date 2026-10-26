//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeWindowResize.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_NativeWindowResize.h"
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
    NativeWindowResize::NativeWindowResize(ClassTraits::Traits& t)
    : Class(t)
    , BOTTOM("B")
    , BOTTOM_LEFT("BL")
    , BOTTOM_RIGHT("BR")
    , LEFT("L")
    , NONE("")
    , RIGHT("R")
    , TOP("T")
    , TOP_LEFT("TL")
    , TOP_RIGHT("TR")
    {
//##protect##"class_::NativeWindowResize::NativeWindowResize()"
//##protect##"class_::NativeWindowResize::NativeWindowResize()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo NativeWindowResize::mi[NativeWindowResize::MemberInfoNum] = {
        {"BOTTOM", OFFSETOF(Classes::NativeWindowResize, BOTTOM), SlotInfo::BT_ConstChar, 1},
        {"BOTTOM_LEFT", OFFSETOF(Classes::NativeWindowResize, BOTTOM_LEFT), SlotInfo::BT_ConstChar, 1},
        {"BOTTOM_RIGHT", OFFSETOF(Classes::NativeWindowResize, BOTTOM_RIGHT), SlotInfo::BT_ConstChar, 1},
        {"LEFT", OFFSETOF(Classes::NativeWindowResize, LEFT), SlotInfo::BT_ConstChar, 1},
        {"NONE", OFFSETOF(Classes::NativeWindowResize, NONE), SlotInfo::BT_ConstChar, 1},
        {"RIGHT", OFFSETOF(Classes::NativeWindowResize, RIGHT), SlotInfo::BT_ConstChar, 1},
        {"TOP", OFFSETOF(Classes::NativeWindowResize, TOP), SlotInfo::BT_ConstChar, 1},
        {"TOP_LEFT", OFFSETOF(Classes::NativeWindowResize, TOP_LEFT), SlotInfo::BT_ConstChar, 1},
        {"TOP_RIGHT", OFFSETOF(Classes::NativeWindowResize, TOP_RIGHT), SlotInfo::BT_ConstChar, 1},
    };

    NativeWindowResize::NativeWindowResize(VM& vm)
    : Traits(vm, NativeWindowResizeCI)
    {
//##protect##"ClassTraits::NativeWindowResize::NativeWindowResize()"
//##protect##"ClassTraits::NativeWindowResize::NativeWindowResize()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, NativeWindowResizeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::NativeWindowResize(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeWindowResize::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeWindowResize(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeWindowResizeCI = {
    ClassInfo::CompileTime,
    "NativeWindowResize", "flash.display", &ObjectCI,
    ClassTraits::NativeWindowResize::MakeClassTraits,
    0,
    ClassTraits::NativeWindowResize::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::NativeWindowResize::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

