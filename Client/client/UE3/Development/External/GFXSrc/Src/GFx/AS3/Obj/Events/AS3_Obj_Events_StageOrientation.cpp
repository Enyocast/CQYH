//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_StageOrientation.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_StageOrientation.h"
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
    StageOrientation::StageOrientation(ClassTraits::Traits& t)
    : Class(t)
    , DEFAULT("default")
    , ROTATED_LEFT("rotatedLeft")
    , ROTATED_RIGHT("rotatedRight")
    , UNKNOWN("unknown")
    , UPSIDE_DOWN("upsideDown")
    {
//##protect##"class_::StageOrientation::StageOrientation()"
//##protect##"class_::StageOrientation::StageOrientation()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo StageOrientation::mi[StageOrientation::MemberInfoNum] = {
        {"DEFAULT", OFFSETOF(Classes::StageOrientation, DEFAULT), SlotInfo::BT_ConstChar, 1},
        {"ROTATED_LEFT", OFFSETOF(Classes::StageOrientation, ROTATED_LEFT), SlotInfo::BT_ConstChar, 1},
        {"ROTATED_RIGHT", OFFSETOF(Classes::StageOrientation, ROTATED_RIGHT), SlotInfo::BT_ConstChar, 1},
        {"UNKNOWN", OFFSETOF(Classes::StageOrientation, UNKNOWN), SlotInfo::BT_ConstChar, 1},
        {"UPSIDE_DOWN", OFFSETOF(Classes::StageOrientation, UPSIDE_DOWN), SlotInfo::BT_ConstChar, 1},
    };

    StageOrientation::StageOrientation(VM& vm)
    : Traits(vm, StageOrientationCI)
    {
//##protect##"ClassTraits::StageOrientation::StageOrientation()"
//##protect##"ClassTraits::StageOrientation::StageOrientation()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, StageOrientationCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::StageOrientation(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> StageOrientation::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) StageOrientation(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo StageOrientationCI = {
    ClassInfo::CompileTime,
    "StageOrientation", "flash.events", &ObjectCI,
    ClassTraits::StageOrientation::MakeClassTraits,
    0,
    ClassTraits::StageOrientation::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::StageOrientation::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

