//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_StageDisplayState.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_StageDisplayState.h"
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
    StageDisplayState::StageDisplayState(ClassTraits::Traits& t)
    : Class(t)
    , FULL_SCREEN("fullScreen")
    , FULL_SCREEN_INTERACTIVE("fullScreenInteractive")
    , NORMAL("normal")
    {
//##protect##"class_::StageDisplayState::StageDisplayState()"
//##protect##"class_::StageDisplayState::StageDisplayState()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo StageDisplayState::mi[StageDisplayState::MemberInfoNum] = {
        {"FULL_SCREEN", OFFSETOF(Classes::StageDisplayState, FULL_SCREEN), SlotInfo::BT_ConstChar, 1},
        {"FULL_SCREEN_INTERACTIVE", OFFSETOF(Classes::StageDisplayState, FULL_SCREEN_INTERACTIVE), SlotInfo::BT_ConstChar, 1},
        {"NORMAL", OFFSETOF(Classes::StageDisplayState, NORMAL), SlotInfo::BT_ConstChar, 1},
    };

    StageDisplayState::StageDisplayState(VM& vm)
    : Traits(vm, StageDisplayStateCI)
    {
//##protect##"ClassTraits::StageDisplayState::StageDisplayState()"
//##protect##"ClassTraits::StageDisplayState::StageDisplayState()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, StageDisplayStateCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::StageDisplayState(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> StageDisplayState::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) StageDisplayState(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo StageDisplayStateCI = {
    ClassInfo::CompileTime,
    "StageDisplayState", "flash.display", &ObjectCI,
    ClassTraits::StageDisplayState::MakeClassTraits,
    0,
    ClassTraits::StageDisplayState::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::StageDisplayState::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

