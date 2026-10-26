//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_StageAlign.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_StageAlign.h"
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
    StageAlign::StageAlign(ClassTraits::Traits& t)
    : Class(t)
    , BOTTOM("B")
    , BOTTOM_LEFT("BL")
    , BOTTOM_RIGHT("BR")
    , LEFT("L")
    , RIGHT("R")
    , TOP("T")
    , TOP_LEFT("TL")
    , TOP_RIGHT("TR")
    {
//##protect##"class_::StageAlign::StageAlign()"
//##protect##"class_::StageAlign::StageAlign()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo StageAlign::mi[StageAlign::MemberInfoNum] = {
        {"BOTTOM", OFFSETOF(Classes::StageAlign, BOTTOM), SlotInfo::BT_ConstChar, 1},
        {"BOTTOM_LEFT", OFFSETOF(Classes::StageAlign, BOTTOM_LEFT), SlotInfo::BT_ConstChar, 1},
        {"BOTTOM_RIGHT", OFFSETOF(Classes::StageAlign, BOTTOM_RIGHT), SlotInfo::BT_ConstChar, 1},
        {"LEFT", OFFSETOF(Classes::StageAlign, LEFT), SlotInfo::BT_ConstChar, 1},
        {"RIGHT", OFFSETOF(Classes::StageAlign, RIGHT), SlotInfo::BT_ConstChar, 1},
        {"TOP", OFFSETOF(Classes::StageAlign, TOP), SlotInfo::BT_ConstChar, 1},
        {"TOP_LEFT", OFFSETOF(Classes::StageAlign, TOP_LEFT), SlotInfo::BT_ConstChar, 1},
        {"TOP_RIGHT", OFFSETOF(Classes::StageAlign, TOP_RIGHT), SlotInfo::BT_ConstChar, 1},
    };

    StageAlign::StageAlign(VM& vm)
    : Traits(vm, StageAlignCI)
    {
//##protect##"ClassTraits::StageAlign::StageAlign()"
//##protect##"ClassTraits::StageAlign::StageAlign()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, StageAlignCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::StageAlign(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> StageAlign::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) StageAlign(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo StageAlignCI = {
    ClassInfo::CompileTime,
    "StageAlign", "flash.display", &ObjectCI,
    ClassTraits::StageAlign::MakeClassTraits,
    0,
    ClassTraits::StageAlign::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::StageAlign::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

