//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_FocusDirection.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_FocusDirection.h"
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
    FocusDirection::FocusDirection(ClassTraits::Traits& t)
    : Class(t)
    , BOTTOM("bottom")
    , NONE("none")
    , TOP("top")
    {
//##protect##"class_::FocusDirection::FocusDirection()"
//##protect##"class_::FocusDirection::FocusDirection()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo FocusDirection::mi[FocusDirection::MemberInfoNum] = {
        {"BOTTOM", OFFSETOF(Classes::FocusDirection, BOTTOM), SlotInfo::BT_ConstChar, 1},
        {"NONE", OFFSETOF(Classes::FocusDirection, NONE), SlotInfo::BT_ConstChar, 1},
        {"TOP", OFFSETOF(Classes::FocusDirection, TOP), SlotInfo::BT_ConstChar, 1},
    };

    FocusDirection::FocusDirection(VM& vm)
    : Traits(vm, FocusDirectionCI)
    {
//##protect##"ClassTraits::FocusDirection::FocusDirection()"
//##protect##"ClassTraits::FocusDirection::FocusDirection()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, FocusDirectionCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::FocusDirection(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> FocusDirection::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FocusDirection(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo FocusDirectionCI = {
    ClassInfo::CompileTime,
    "FocusDirection", "flash.display", &ObjectCI,
    ClassTraits::FocusDirection::MakeClassTraits,
    0,
    ClassTraits::FocusDirection::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::FocusDirection::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

