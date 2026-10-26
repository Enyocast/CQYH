//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_CapsStyle.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_CapsStyle.h"
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
    CapsStyle::CapsStyle(ClassTraits::Traits& t)
    : Class(t)
    , NONE("none")
    , ROUND("round")
    , SQUARE("square")
    {
//##protect##"class_::CapsStyle::CapsStyle()"
//##protect##"class_::CapsStyle::CapsStyle()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo CapsStyle::mi[CapsStyle::MemberInfoNum] = {
        {"NONE", OFFSETOF(Classes::CapsStyle, NONE), SlotInfo::BT_ConstChar, 1},
        {"ROUND", OFFSETOF(Classes::CapsStyle, ROUND), SlotInfo::BT_ConstChar, 1},
        {"SQUARE", OFFSETOF(Classes::CapsStyle, SQUARE), SlotInfo::BT_ConstChar, 1},
    };

    CapsStyle::CapsStyle(VM& vm)
    : Traits(vm, CapsStyleCI)
    {
//##protect##"ClassTraits::CapsStyle::CapsStyle()"
//##protect##"ClassTraits::CapsStyle::CapsStyle()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, CapsStyleCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::CapsStyle(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> CapsStyle::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) CapsStyle(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo CapsStyleCI = {
    ClassInfo::CompileTime,
    "CapsStyle", "flash.display", &ObjectCI,
    ClassTraits::CapsStyle::MakeClassTraits,
    0,
    ClassTraits::CapsStyle::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::CapsStyle::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

