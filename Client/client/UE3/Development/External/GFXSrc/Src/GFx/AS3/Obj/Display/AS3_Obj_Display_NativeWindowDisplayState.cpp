//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeWindowDisplayState.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_NativeWindowDisplayState.h"
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
    NativeWindowDisplayState::NativeWindowDisplayState(ClassTraits::Traits& t)
    : Class(t)
    , MAXIMIZED("maximized")
    , MINIMIZED("minimized")
    , NORMAL("normal")
    {
//##protect##"class_::NativeWindowDisplayState::NativeWindowDisplayState()"
//##protect##"class_::NativeWindowDisplayState::NativeWindowDisplayState()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo NativeWindowDisplayState::mi[NativeWindowDisplayState::MemberInfoNum] = {
        {"MAXIMIZED", OFFSETOF(Classes::NativeWindowDisplayState, MAXIMIZED), SlotInfo::BT_ConstChar, 1},
        {"MINIMIZED", OFFSETOF(Classes::NativeWindowDisplayState, MINIMIZED), SlotInfo::BT_ConstChar, 1},
        {"NORMAL", OFFSETOF(Classes::NativeWindowDisplayState, NORMAL), SlotInfo::BT_ConstChar, 1},
    };

    NativeWindowDisplayState::NativeWindowDisplayState(VM& vm)
    : Traits(vm, NativeWindowDisplayStateCI)
    {
//##protect##"ClassTraits::NativeWindowDisplayState::NativeWindowDisplayState()"
//##protect##"ClassTraits::NativeWindowDisplayState::NativeWindowDisplayState()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, NativeWindowDisplayStateCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::NativeWindowDisplayState(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeWindowDisplayState::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeWindowDisplayState(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeWindowDisplayStateCI = {
    ClassInfo::CompileTime,
    "NativeWindowDisplayState", "flash.display", &ObjectCI,
    ClassTraits::NativeWindowDisplayState::MakeClassTraits,
    0,
    ClassTraits::NativeWindowDisplayState::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::NativeWindowDisplayState::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

