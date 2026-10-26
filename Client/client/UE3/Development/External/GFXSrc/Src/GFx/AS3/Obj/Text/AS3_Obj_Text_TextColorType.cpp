//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextColorType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_TextColorType.h"
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
    TextColorType::TextColorType(ClassTraits::Traits& t)
    : Class(t)
    , DARK_COLOR("dark")
    , LIGHT_COLOR("light")
    {
//##protect##"class_::TextColorType::TextColorType()"
//##protect##"class_::TextColorType::TextColorType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo TextColorType::mi[TextColorType::MemberInfoNum] = {
        {"DARK_COLOR", OFFSETOF(Classes::TextColorType, DARK_COLOR), SlotInfo::BT_ConstChar, 1},
        {"LIGHT_COLOR", OFFSETOF(Classes::TextColorType, LIGHT_COLOR), SlotInfo::BT_ConstChar, 1},
    };

    TextColorType::TextColorType(VM& vm)
    : Traits(vm, TextColorTypeCI)
    {
//##protect##"ClassTraits::TextColorType::TextColorType()"
//##protect##"ClassTraits::TextColorType::TextColorType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, TextColorTypeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::TextColorType(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextColorType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextColorType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextColorTypeCI = {
    ClassInfo::CompileTime,
    "TextColorType", "flash.text", &ObjectCI,
    ClassTraits::TextColorType::MakeClassTraits,
    0,
    ClassTraits::TextColorType::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::TextColorType::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

