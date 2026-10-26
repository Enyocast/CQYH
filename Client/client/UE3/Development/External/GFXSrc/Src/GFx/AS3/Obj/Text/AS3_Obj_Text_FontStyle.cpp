//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_FontStyle.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_FontStyle.h"
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
    FontStyle::FontStyle(ClassTraits::Traits& t)
    : Class(t)
    , BOLD("bold")
    , BOLD_ITALIC("boldItalic")
    , ITALIC("italic")
    , REGULAR("regular")
    {
//##protect##"class_::FontStyle::FontStyle()"
//##protect##"class_::FontStyle::FontStyle()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo FontStyle::mi[FontStyle::MemberInfoNum] = {
        {"BOLD", OFFSETOF(Classes::FontStyle, BOLD), SlotInfo::BT_ConstChar, 1},
        {"BOLD_ITALIC", OFFSETOF(Classes::FontStyle, BOLD_ITALIC), SlotInfo::BT_ConstChar, 1},
        {"ITALIC", OFFSETOF(Classes::FontStyle, ITALIC), SlotInfo::BT_ConstChar, 1},
        {"REGULAR", OFFSETOF(Classes::FontStyle, REGULAR), SlotInfo::BT_ConstChar, 1},
    };

    FontStyle::FontStyle(VM& vm)
    : Traits(vm, FontStyleCI)
    {
//##protect##"ClassTraits::FontStyle::FontStyle()"
//##protect##"ClassTraits::FontStyle::FontStyle()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, FontStyleCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::FontStyle(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> FontStyle::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FontStyle(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo FontStyleCI = {
    ClassInfo::CompileTime,
    "FontStyle", "flash.text", &ObjectCI,
    ClassTraits::FontStyle::MakeClassTraits,
    0,
    ClassTraits::FontStyle::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::FontStyle::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

