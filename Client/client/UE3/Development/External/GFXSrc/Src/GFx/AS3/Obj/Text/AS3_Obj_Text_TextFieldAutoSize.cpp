//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextFieldAutoSize.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_TextFieldAutoSize.h"
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
    TextFieldAutoSize::TextFieldAutoSize(ClassTraits::Traits& t)
    : Class(t)
    , CENTER("center")
    , LEFT("left")
    , NONE("none")
    , RIGHT("right")
    {
//##protect##"class_::TextFieldAutoSize::TextFieldAutoSize()"
//##protect##"class_::TextFieldAutoSize::TextFieldAutoSize()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo TextFieldAutoSize::mi[TextFieldAutoSize::MemberInfoNum] = {
        {"CENTER", OFFSETOF(Classes::TextFieldAutoSize, CENTER), SlotInfo::BT_ConstChar, 1},
        {"LEFT", OFFSETOF(Classes::TextFieldAutoSize, LEFT), SlotInfo::BT_ConstChar, 1},
        {"NONE", OFFSETOF(Classes::TextFieldAutoSize, NONE), SlotInfo::BT_ConstChar, 1},
        {"RIGHT", OFFSETOF(Classes::TextFieldAutoSize, RIGHT), SlotInfo::BT_ConstChar, 1},
    };

    TextFieldAutoSize::TextFieldAutoSize(VM& vm)
    : Traits(vm, TextFieldAutoSizeCI)
    {
//##protect##"ClassTraits::TextFieldAutoSize::TextFieldAutoSize()"
//##protect##"ClassTraits::TextFieldAutoSize::TextFieldAutoSize()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, TextFieldAutoSizeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::TextFieldAutoSize(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextFieldAutoSize::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextFieldAutoSize(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextFieldAutoSizeCI = {
    ClassInfo::CompileTime,
    "TextFieldAutoSize", "flash.text", &ObjectCI,
    ClassTraits::TextFieldAutoSize::MakeClassTraits,
    0,
    ClassTraits::TextFieldAutoSize::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::TextFieldAutoSize::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

