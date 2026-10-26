//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_SpreadMethod.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_SpreadMethod.h"
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
    SpreadMethod::SpreadMethod(ClassTraits::Traits& t)
    : Class(t)
    , PAD("pad")
    , REFLECT("reflect")
    , REPEAT("repeat")
    {
//##protect##"class_::SpreadMethod::SpreadMethod()"
//##protect##"class_::SpreadMethod::SpreadMethod()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo SpreadMethod::mi[SpreadMethod::MemberInfoNum] = {
        {"PAD", OFFSETOF(Classes::SpreadMethod, PAD), SlotInfo::BT_ConstChar, 1},
        {"REFLECT", OFFSETOF(Classes::SpreadMethod, REFLECT), SlotInfo::BT_ConstChar, 1},
        {"REPEAT", OFFSETOF(Classes::SpreadMethod, REPEAT), SlotInfo::BT_ConstChar, 1},
    };

    SpreadMethod::SpreadMethod(VM& vm)
    : Traits(vm, SpreadMethodCI)
    {
//##protect##"ClassTraits::SpreadMethod::SpreadMethod()"
//##protect##"ClassTraits::SpreadMethod::SpreadMethod()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, SpreadMethodCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::SpreadMethod(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SpreadMethod::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SpreadMethod(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SpreadMethodCI = {
    ClassInfo::CompileTime,
    "SpreadMethod", "flash.display", &ObjectCI,
    ClassTraits::SpreadMethod::MakeClassTraits,
    0,
    ClassTraits::SpreadMethod::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::SpreadMethod::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

