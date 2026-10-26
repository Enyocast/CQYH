//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_KeyLocation.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Ui_KeyLocation.h"
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
    KeyLocation::KeyLocation(ClassTraits::Traits& t)
    : Class(t)
    , LEFT(1)
    , NUM_PAD(3)
    , RIGHT(2)
    , STANDARD(0)
    {
//##protect##"class_::KeyLocation::KeyLocation()"
//##protect##"class_::KeyLocation::KeyLocation()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo KeyLocation::mi[KeyLocation::MemberInfoNum] = {
        {"LEFT", OFFSETOF(Classes::KeyLocation, LEFT), SlotInfo::BT_UInt, 1},
        {"NUM_PAD", OFFSETOF(Classes::KeyLocation, NUM_PAD), SlotInfo::BT_UInt, 1},
        {"RIGHT", OFFSETOF(Classes::KeyLocation, RIGHT), SlotInfo::BT_UInt, 1},
        {"STANDARD", OFFSETOF(Classes::KeyLocation, STANDARD), SlotInfo::BT_UInt, 1},
    };

    KeyLocation::KeyLocation(VM& vm)
    : Traits(vm, KeyLocationCI)
    {
//##protect##"ClassTraits::KeyLocation::KeyLocation()"
//##protect##"ClassTraits::KeyLocation::KeyLocation()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, KeyLocationCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::KeyLocation(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> KeyLocation::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) KeyLocation(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo KeyLocationCI = {
    ClassInfo::CompileTime,
    "KeyLocation", "flash.ui", &ObjectCI,
    ClassTraits::KeyLocation::MakeClassTraits,
    0,
    ClassTraits::KeyLocation::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::KeyLocation::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

