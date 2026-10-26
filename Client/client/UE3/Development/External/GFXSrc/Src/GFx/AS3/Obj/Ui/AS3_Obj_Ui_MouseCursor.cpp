//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_MouseCursor.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Ui_MouseCursor.h"
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
    MouseCursor::MouseCursor(ClassTraits::Traits& t)
    : Class(t)
    , ARROW("arrow")
    , AUTO("auto")
    , BUTTON("button")
    , HAND("hand")
    , IBEAM("ibeam")
    {
//##protect##"class_::MouseCursor::MouseCursor()"
//##protect##"class_::MouseCursor::MouseCursor()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo MouseCursor::mi[MouseCursor::MemberInfoNum] = {
        {"ARROW", OFFSETOF(Classes::MouseCursor, ARROW), SlotInfo::BT_ConstChar, 1},
        {"AUTO", OFFSETOF(Classes::MouseCursor, AUTO), SlotInfo::BT_ConstChar, 1},
        {"BUTTON", OFFSETOF(Classes::MouseCursor, BUTTON), SlotInfo::BT_ConstChar, 1},
        {"HAND", OFFSETOF(Classes::MouseCursor, HAND), SlotInfo::BT_ConstChar, 1},
        {"IBEAM", OFFSETOF(Classes::MouseCursor, IBEAM), SlotInfo::BT_ConstChar, 1},
    };

    MouseCursor::MouseCursor(VM& vm)
    : Traits(vm, MouseCursorCI)
    {
//##protect##"ClassTraits::MouseCursor::MouseCursor()"
//##protect##"ClassTraits::MouseCursor::MouseCursor()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, MouseCursorCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::MouseCursor(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> MouseCursor::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) MouseCursor(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo MouseCursorCI = {
    ClassInfo::CompileTime,
    "MouseCursor", "flash.ui", &ObjectCI,
    ClassTraits::MouseCursor::MakeClassTraits,
    0,
    ClassTraits::MouseCursor::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::MouseCursor::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

