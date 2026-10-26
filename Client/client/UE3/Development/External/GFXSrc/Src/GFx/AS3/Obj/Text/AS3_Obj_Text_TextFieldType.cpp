//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextFieldType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_TextFieldType.h"
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
    TextFieldType::TextFieldType(ClassTraits::Traits& t)
    : Class(t)
    , DYNAMIC("dynamic")
    , INPUT("input")
    {
//##protect##"class_::TextFieldType::TextFieldType()"
//##protect##"class_::TextFieldType::TextFieldType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo TextFieldType::mi[TextFieldType::MemberInfoNum] = {
        {"DYNAMIC", OFFSETOF(Classes::TextFieldType, DYNAMIC), SlotInfo::BT_ConstChar, 1},
        {"INPUT", OFFSETOF(Classes::TextFieldType, INPUT), SlotInfo::BT_ConstChar, 1},
    };

    TextFieldType::TextFieldType(VM& vm)
    : Traits(vm, TextFieldTypeCI)
    {
//##protect##"ClassTraits::TextFieldType::TextFieldType()"
//##protect##"ClassTraits::TextFieldType::TextFieldType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, TextFieldTypeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::TextFieldType(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextFieldType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextFieldType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextFieldTypeCI = {
    ClassInfo::CompileTime,
    "TextFieldType", "flash.text", &ObjectCI,
    ClassTraits::TextFieldType::MakeClassTraits,
    0,
    ClassTraits::TextFieldType::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::TextFieldType::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

