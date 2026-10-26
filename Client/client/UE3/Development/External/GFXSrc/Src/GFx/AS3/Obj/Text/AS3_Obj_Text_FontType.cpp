//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_FontType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_FontType.h"
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
    FontType::FontType(ClassTraits::Traits& t)
    : Class(t)
    , DEVICE("device")
    , EMBEDDED("embedded")
    {
//##protect##"class_::FontType::FontType()"
//##protect##"class_::FontType::FontType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo FontType::mi[FontType::MemberInfoNum] = {
        {"DEVICE", OFFSETOF(Classes::FontType, DEVICE), SlotInfo::BT_ConstChar, 1},
        {"EMBEDDED", OFFSETOF(Classes::FontType, EMBEDDED), SlotInfo::BT_ConstChar, 1},
    };

    FontType::FontType(VM& vm)
    : Traits(vm, FontTypeCI)
    {
//##protect##"ClassTraits::FontType::FontType()"
//##protect##"ClassTraits::FontType::FontType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, FontTypeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::FontType(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> FontType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FontType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo FontTypeCI = {
    ClassInfo::CompileTime,
    "FontType", "flash.text", &ObjectCI,
    ClassTraits::FontType::MakeClassTraits,
    0,
    ClassTraits::FontType::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::FontType::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

