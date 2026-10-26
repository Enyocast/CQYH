//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeWindowType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_NativeWindowType.h"
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
    NativeWindowType::NativeWindowType(ClassTraits::Traits& t)
    : Class(t)
    , LIGHTWEIGHT("lightweight")
    , NORMAL("normal")
    , UTILITY("utility")
    {
//##protect##"class_::NativeWindowType::NativeWindowType()"
//##protect##"class_::NativeWindowType::NativeWindowType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo NativeWindowType::mi[NativeWindowType::MemberInfoNum] = {
        {"LIGHTWEIGHT", OFFSETOF(Classes::NativeWindowType, LIGHTWEIGHT), SlotInfo::BT_ConstChar, 1},
        {"NORMAL", OFFSETOF(Classes::NativeWindowType, NORMAL), SlotInfo::BT_ConstChar, 1},
        {"UTILITY", OFFSETOF(Classes::NativeWindowType, UTILITY), SlotInfo::BT_ConstChar, 1},
    };

    NativeWindowType::NativeWindowType(VM& vm)
    : Traits(vm, NativeWindowTypeCI)
    {
//##protect##"ClassTraits::NativeWindowType::NativeWindowType()"
//##protect##"ClassTraits::NativeWindowType::NativeWindowType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, NativeWindowTypeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::NativeWindowType(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeWindowType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeWindowType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeWindowTypeCI = {
    ClassInfo::CompileTime,
    "NativeWindowType", "flash.display", &ObjectCI,
    ClassTraits::NativeWindowType::MakeClassTraits,
    0,
    ClassTraits::NativeWindowType::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::NativeWindowType::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

