//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextFormatAlign.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_TextFormatAlign.h"
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
    TextFormatAlign::TextFormatAlign(ClassTraits::Traits& t)
    : Class(t)
    , CENTER("center")
    , JUSTIFY("justify")
    , LEFT("left")
    , RIGHT("right")
    {
//##protect##"class_::TextFormatAlign::TextFormatAlign()"
//##protect##"class_::TextFormatAlign::TextFormatAlign()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo TextFormatAlign::mi[TextFormatAlign::MemberInfoNum] = {
        {"CENTER", OFFSETOF(Classes::TextFormatAlign, CENTER), SlotInfo::BT_ConstChar, 1},
        {"JUSTIFY", OFFSETOF(Classes::TextFormatAlign, JUSTIFY), SlotInfo::BT_ConstChar, 1},
        {"LEFT", OFFSETOF(Classes::TextFormatAlign, LEFT), SlotInfo::BT_ConstChar, 1},
        {"RIGHT", OFFSETOF(Classes::TextFormatAlign, RIGHT), SlotInfo::BT_ConstChar, 1},
    };

    TextFormatAlign::TextFormatAlign(VM& vm)
    : Traits(vm, TextFormatAlignCI)
    {
//##protect##"ClassTraits::TextFormatAlign::TextFormatAlign()"
//##protect##"ClassTraits::TextFormatAlign::TextFormatAlign()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, TextFormatAlignCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::TextFormatAlign(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextFormatAlign::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextFormatAlign(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextFormatAlignCI = {
    ClassInfo::CompileTime,
    "TextFormatAlign", "flash.text", &ObjectCI,
    ClassTraits::TextFormatAlign::MakeClassTraits,
    0,
    ClassTraits::TextFormatAlign::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::TextFormatAlign::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

