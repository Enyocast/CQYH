//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_MultitouchInputMode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Ui_MultitouchInputMode.h"
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
    MultitouchInputMode::MultitouchInputMode(ClassTraits::Traits& t)
    : Class(t)
    , GESTURE("gesture")
    , NONE("none")
    , TOUCH_POINT("touchPoint")
    {
//##protect##"class_::MultitouchInputMode::MultitouchInputMode()"
//##protect##"class_::MultitouchInputMode::MultitouchInputMode()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo MultitouchInputMode::mi[MultitouchInputMode::MemberInfoNum] = {
        {"GESTURE", OFFSETOF(Classes::MultitouchInputMode, GESTURE), SlotInfo::BT_ConstChar, 1},
        {"NONE", OFFSETOF(Classes::MultitouchInputMode, NONE), SlotInfo::BT_ConstChar, 1},
        {"TOUCH_POINT", OFFSETOF(Classes::MultitouchInputMode, TOUCH_POINT), SlotInfo::BT_ConstChar, 1},
    };

    MultitouchInputMode::MultitouchInputMode(VM& vm)
    : Traits(vm, MultitouchInputModeCI)
    {
//##protect##"ClassTraits::MultitouchInputMode::MultitouchInputMode()"
//##protect##"ClassTraits::MultitouchInputMode::MultitouchInputMode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, MultitouchInputModeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::MultitouchInputMode(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> MultitouchInputMode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) MultitouchInputMode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo MultitouchInputModeCI = {
    ClassInfo::CompileTime,
    "MultitouchInputMode", "flash.ui", &ObjectCI,
    ClassTraits::MultitouchInputMode::MakeClassTraits,
    0,
    ClassTraits::MultitouchInputMode::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::MultitouchInputMode::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

