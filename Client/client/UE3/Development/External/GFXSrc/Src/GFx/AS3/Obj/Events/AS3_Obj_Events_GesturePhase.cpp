//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_GesturePhase.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_GesturePhase.h"
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
    GesturePhase::GesturePhase(ClassTraits::Traits& t)
    : Class(t)
    , ALL("all")
    , BEGIN("begin")
    , END("end")
    , UPDATE("update")
    {
//##protect##"class_::GesturePhase::GesturePhase()"
//##protect##"class_::GesturePhase::GesturePhase()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo GesturePhase::mi[GesturePhase::MemberInfoNum] = {
        {"ALL", OFFSETOF(Classes::GesturePhase, ALL), SlotInfo::BT_ConstChar, 1},
        {"BEGIN", OFFSETOF(Classes::GesturePhase, BEGIN), SlotInfo::BT_ConstChar, 1},
        {"END", OFFSETOF(Classes::GesturePhase, END), SlotInfo::BT_ConstChar, 1},
        {"UPDATE", OFFSETOF(Classes::GesturePhase, UPDATE), SlotInfo::BT_ConstChar, 1},
    };

    GesturePhase::GesturePhase(VM& vm)
    : Traits(vm, GesturePhaseCI)
    {
//##protect##"ClassTraits::GesturePhase::GesturePhase()"
//##protect##"ClassTraits::GesturePhase::GesturePhase()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, GesturePhaseCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::GesturePhase(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> GesturePhase::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) GesturePhase(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo GesturePhaseCI = {
    ClassInfo::CompileTime,
    "GesturePhase", "flash.events", &ObjectCI,
    ClassTraits::GesturePhase::MakeClassTraits,
    0,
    ClassTraits::GesturePhase::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::GesturePhase::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

