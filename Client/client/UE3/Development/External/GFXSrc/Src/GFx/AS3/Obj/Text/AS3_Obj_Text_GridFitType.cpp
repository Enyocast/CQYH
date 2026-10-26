//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_GridFitType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_GridFitType.h"
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
    GridFitType::GridFitType(ClassTraits::Traits& t)
    : Class(t)
    , NONE("none")
    , PIXEL("pixel")
    , SUBPIXEL("subpixel")
    {
//##protect##"class_::GridFitType::GridFitType()"
//##protect##"class_::GridFitType::GridFitType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo GridFitType::mi[GridFitType::MemberInfoNum] = {
        {"NONE", OFFSETOF(Classes::GridFitType, NONE), SlotInfo::BT_ConstChar, 1},
        {"PIXEL", OFFSETOF(Classes::GridFitType, PIXEL), SlotInfo::BT_ConstChar, 1},
        {"SUBPIXEL", OFFSETOF(Classes::GridFitType, SUBPIXEL), SlotInfo::BT_ConstChar, 1},
    };

    GridFitType::GridFitType(VM& vm)
    : Traits(vm, GridFitTypeCI)
    {
//##protect##"ClassTraits::GridFitType::GridFitType()"
//##protect##"ClassTraits::GridFitType::GridFitType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, GridFitTypeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::GridFitType(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> GridFitType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) GridFitType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo GridFitTypeCI = {
    ClassInfo::CompileTime,
    "GridFitType", "flash.text", &ObjectCI,
    ClassTraits::GridFitType::MakeClassTraits,
    0,
    ClassTraits::GridFitType::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::GridFitType::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

