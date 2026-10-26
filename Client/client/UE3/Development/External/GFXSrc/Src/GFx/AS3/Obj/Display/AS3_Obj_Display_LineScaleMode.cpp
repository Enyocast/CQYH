//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_LineScaleMode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_LineScaleMode.h"
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
    LineScaleMode::LineScaleMode(ClassTraits::Traits& t)
    : Class(t)
    , HORIZONTAL("horizontal")
    , NONE("none")
    , NORMAL("normal")
    , VERTICAL("vertical")
    {
//##protect##"class_::LineScaleMode::LineScaleMode()"
//##protect##"class_::LineScaleMode::LineScaleMode()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo LineScaleMode::mi[LineScaleMode::MemberInfoNum] = {
        {"HORIZONTAL", OFFSETOF(Classes::LineScaleMode, HORIZONTAL), SlotInfo::BT_ConstChar, 1},
        {"NONE", OFFSETOF(Classes::LineScaleMode, NONE), SlotInfo::BT_ConstChar, 1},
        {"NORMAL", OFFSETOF(Classes::LineScaleMode, NORMAL), SlotInfo::BT_ConstChar, 1},
        {"VERTICAL", OFFSETOF(Classes::LineScaleMode, VERTICAL), SlotInfo::BT_ConstChar, 1},
    };

    LineScaleMode::LineScaleMode(VM& vm)
    : Traits(vm, LineScaleModeCI)
    {
//##protect##"ClassTraits::LineScaleMode::LineScaleMode()"
//##protect##"ClassTraits::LineScaleMode::LineScaleMode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, LineScaleModeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::LineScaleMode(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> LineScaleMode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) LineScaleMode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo LineScaleModeCI = {
    ClassInfo::CompileTime,
    "LineScaleMode", "flash.display", &ObjectCI,
    ClassTraits::LineScaleMode::MakeClassTraits,
    0,
    ClassTraits::LineScaleMode::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::LineScaleMode::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

