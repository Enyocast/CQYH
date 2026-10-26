//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_StageQuality.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_StageQuality.h"
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
    StageQuality::StageQuality(ClassTraits::Traits& t)
    : Class(t)
    , BEST("best")
    , HIGH("high")
    , LOW("low")
    , MEDIUM("medium")
    {
//##protect##"class_::StageQuality::StageQuality()"
//##protect##"class_::StageQuality::StageQuality()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo StageQuality::mi[StageQuality::MemberInfoNum] = {
        {"BEST", OFFSETOF(Classes::StageQuality, BEST), SlotInfo::BT_ConstChar, 1},
        {"HIGH", OFFSETOF(Classes::StageQuality, HIGH), SlotInfo::BT_ConstChar, 1},
        {"LOW", OFFSETOF(Classes::StageQuality, LOW), SlotInfo::BT_ConstChar, 1},
        {"MEDIUM", OFFSETOF(Classes::StageQuality, MEDIUM), SlotInfo::BT_ConstChar, 1},
    };

    StageQuality::StageQuality(VM& vm)
    : Traits(vm, StageQualityCI)
    {
//##protect##"ClassTraits::StageQuality::StageQuality()"
//##protect##"ClassTraits::StageQuality::StageQuality()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, StageQualityCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::StageQuality(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> StageQuality::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) StageQuality(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo StageQualityCI = {
    ClassInfo::CompileTime,
    "StageQuality", "flash.display", &ObjectCI,
    ClassTraits::StageQuality::MakeClassTraits,
    0,
    ClassTraits::StageQuality::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::StageQuality::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

