//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeWindowSystemChrome.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_NativeWindowSystemChrome.h"
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
    NativeWindowSystemChrome::NativeWindowSystemChrome(ClassTraits::Traits& t)
    : Class(t)
    , NONE("none")
    , STANDARD("standard")
    {
//##protect##"class_::NativeWindowSystemChrome::NativeWindowSystemChrome()"
//##protect##"class_::NativeWindowSystemChrome::NativeWindowSystemChrome()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo NativeWindowSystemChrome::mi[NativeWindowSystemChrome::MemberInfoNum] = {
        {"NONE", OFFSETOF(Classes::NativeWindowSystemChrome, NONE), SlotInfo::BT_ConstChar, 1},
        {"STANDARD", OFFSETOF(Classes::NativeWindowSystemChrome, STANDARD), SlotInfo::BT_ConstChar, 1},
    };

    NativeWindowSystemChrome::NativeWindowSystemChrome(VM& vm)
    : Traits(vm, NativeWindowSystemChromeCI)
    {
//##protect##"ClassTraits::NativeWindowSystemChrome::NativeWindowSystemChrome()"
//##protect##"ClassTraits::NativeWindowSystemChrome::NativeWindowSystemChrome()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, NativeWindowSystemChromeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::NativeWindowSystemChrome(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeWindowSystemChrome::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeWindowSystemChrome(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeWindowSystemChromeCI = {
    ClassInfo::CompileTime,
    "NativeWindowSystemChrome", "flash.display", &ObjectCI,
    ClassTraits::NativeWindowSystemChrome::MakeClassTraits,
    0,
    ClassTraits::NativeWindowSystemChrome::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::NativeWindowSystemChrome::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

