//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_StageScaleMode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_StageScaleMode.h"
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
    StageScaleMode::StageScaleMode(ClassTraits::Traits& t)
    : Class(t)
    , EXACT_FIT("exactFit")
    , NO_BORDER("noBorder")
    , NO_SCALE("noScale")
    , SHOW_ALL("showAll")
    {
//##protect##"class_::StageScaleMode::StageScaleMode()"
//##protect##"class_::StageScaleMode::StageScaleMode()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo StageScaleMode::mi[StageScaleMode::MemberInfoNum] = {
        {"EXACT_FIT", OFFSETOF(Classes::StageScaleMode, EXACT_FIT), SlotInfo::BT_ConstChar, 1},
        {"NO_BORDER", OFFSETOF(Classes::StageScaleMode, NO_BORDER), SlotInfo::BT_ConstChar, 1},
        {"NO_SCALE", OFFSETOF(Classes::StageScaleMode, NO_SCALE), SlotInfo::BT_ConstChar, 1},
        {"SHOW_ALL", OFFSETOF(Classes::StageScaleMode, SHOW_ALL), SlotInfo::BT_ConstChar, 1},
    };

    StageScaleMode::StageScaleMode(VM& vm)
    : Traits(vm, StageScaleModeCI)
    {
//##protect##"ClassTraits::StageScaleMode::StageScaleMode()"
//##protect##"ClassTraits::StageScaleMode::StageScaleMode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, StageScaleModeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::StageScaleMode(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> StageScaleMode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) StageScaleMode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo StageScaleModeCI = {
    ClassInfo::CompileTime,
    "StageScaleMode", "flash.display", &ObjectCI,
    ClassTraits::StageScaleMode::MakeClassTraits,
    0,
    ClassTraits::StageScaleMode::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::StageScaleMode::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

