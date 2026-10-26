//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_ClipboardTransferMode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_ClipboardTransferMode.h"
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
    ClipboardTransferMode::ClipboardTransferMode(ClassTraits::Traits& t)
    : Class(t)
    , CLONE_ONLY("cloneOnly")
    , CLONE_PREFERRED("clonePreferred")
    , ORIGINAL_ONLY("originalOnly")
    , ORIGINAL_PREFERRED("originalPreferred")
    {
//##protect##"class_::ClipboardTransferMode::ClipboardTransferMode()"
//##protect##"class_::ClipboardTransferMode::ClipboardTransferMode()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo ClipboardTransferMode::mi[ClipboardTransferMode::MemberInfoNum] = {
        {"CLONE_ONLY", OFFSETOF(Classes::ClipboardTransferMode, CLONE_ONLY), SlotInfo::BT_ConstChar, 1},
        {"CLONE_PREFERRED", OFFSETOF(Classes::ClipboardTransferMode, CLONE_PREFERRED), SlotInfo::BT_ConstChar, 1},
        {"ORIGINAL_ONLY", OFFSETOF(Classes::ClipboardTransferMode, ORIGINAL_ONLY), SlotInfo::BT_ConstChar, 1},
        {"ORIGINAL_PREFERRED", OFFSETOF(Classes::ClipboardTransferMode, ORIGINAL_PREFERRED), SlotInfo::BT_ConstChar, 1},
    };

    ClipboardTransferMode::ClipboardTransferMode(VM& vm)
    : Traits(vm, ClipboardTransferModeCI)
    {
//##protect##"ClassTraits::ClipboardTransferMode::ClipboardTransferMode()"
//##protect##"ClassTraits::ClipboardTransferMode::ClipboardTransferMode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, ClipboardTransferModeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::ClipboardTransferMode(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ClipboardTransferMode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClipboardTransferMode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ClipboardTransferModeCI = {
    ClassInfo::CompileTime,
    "ClipboardTransferMode", "flash.desktop", &ObjectCI,
    ClassTraits::ClipboardTransferMode::MakeClassTraits,
    0,
    ClassTraits::ClipboardTransferMode::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::ClipboardTransferMode::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

