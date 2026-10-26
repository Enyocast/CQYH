//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_NativeDragActions.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_NativeDragActions.h"
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
    NativeDragActions::NativeDragActions(ClassTraits::Traits& t)
    : Class(t)
    , COPY("copy")
    , LINK("link")
    , MOVE("move")
    , NONE("none")
    {
//##protect##"class_::NativeDragActions::NativeDragActions()"
//##protect##"class_::NativeDragActions::NativeDragActions()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo NativeDragActions::mi[NativeDragActions::MemberInfoNum] = {
        {"COPY", OFFSETOF(Classes::NativeDragActions, COPY), SlotInfo::BT_ConstChar, 1},
        {"LINK", OFFSETOF(Classes::NativeDragActions, LINK), SlotInfo::BT_ConstChar, 1},
        {"MOVE", OFFSETOF(Classes::NativeDragActions, MOVE), SlotInfo::BT_ConstChar, 1},
        {"NONE", OFFSETOF(Classes::NativeDragActions, NONE), SlotInfo::BT_ConstChar, 1},
    };

    NativeDragActions::NativeDragActions(VM& vm)
    : Traits(vm, NativeDragActionsCI)
    {
//##protect##"ClassTraits::NativeDragActions::NativeDragActions()"
//##protect##"ClassTraits::NativeDragActions::NativeDragActions()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, NativeDragActionsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::NativeDragActions(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeDragActions::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeDragActions(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeDragActionsCI = {
    ClassInfo::CompileTime,
    "NativeDragActions", "flash.desktop", &ObjectCI,
    ClassTraits::NativeDragActions::MakeClassTraits,
    0,
    ClassTraits::NativeDragActions::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::NativeDragActions::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

