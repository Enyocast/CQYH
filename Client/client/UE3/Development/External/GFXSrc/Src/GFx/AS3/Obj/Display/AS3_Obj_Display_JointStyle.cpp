//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_JointStyle.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_JointStyle.h"
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
    JointStyle::JointStyle(ClassTraits::Traits& t)
    : Class(t)
    , BEVEL("bevel")
    , MITER("miter")
    , ROUND("round")
    {
//##protect##"class_::JointStyle::JointStyle()"
//##protect##"class_::JointStyle::JointStyle()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo JointStyle::mi[JointStyle::MemberInfoNum] = {
        {"BEVEL", OFFSETOF(Classes::JointStyle, BEVEL), SlotInfo::BT_ConstChar, 1},
        {"MITER", OFFSETOF(Classes::JointStyle, MITER), SlotInfo::BT_ConstChar, 1},
        {"ROUND", OFFSETOF(Classes::JointStyle, ROUND), SlotInfo::BT_ConstChar, 1},
    };

    JointStyle::JointStyle(VM& vm)
    : Traits(vm, JointStyleCI)
    {
//##protect##"ClassTraits::JointStyle::JointStyle()"
//##protect##"ClassTraits::JointStyle::JointStyle()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, JointStyleCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::JointStyle(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> JointStyle::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) JointStyle(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo JointStyleCI = {
    ClassInfo::CompileTime,
    "JointStyle", "flash.display", &ObjectCI,
    ClassTraits::JointStyle::MakeClassTraits,
    0,
    ClassTraits::JointStyle::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::JointStyle::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

