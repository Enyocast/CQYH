//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextDisplayMode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_TextDisplayMode.h"
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
    TextDisplayMode::TextDisplayMode(ClassTraits::Traits& t)
    : Class(t)
    , CRT("crt")
    , DEFAULT("default")
    , LCD("lcd")
    {
//##protect##"class_::TextDisplayMode::TextDisplayMode()"
//##protect##"class_::TextDisplayMode::TextDisplayMode()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo TextDisplayMode::mi[TextDisplayMode::MemberInfoNum] = {
        {"CRT", OFFSETOF(Classes::TextDisplayMode, CRT), SlotInfo::BT_ConstChar, 1},
        {"DEFAULT", OFFSETOF(Classes::TextDisplayMode, DEFAULT), SlotInfo::BT_ConstChar, 1},
        {"LCD", OFFSETOF(Classes::TextDisplayMode, LCD), SlotInfo::BT_ConstChar, 1},
    };

    TextDisplayMode::TextDisplayMode(VM& vm)
    : Traits(vm, TextDisplayModeCI)
    {
//##protect##"ClassTraits::TextDisplayMode::TextDisplayMode()"
//##protect##"ClassTraits::TextDisplayMode::TextDisplayMode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, TextDisplayModeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::TextDisplayMode(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextDisplayMode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextDisplayMode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextDisplayModeCI = {
    ClassInfo::CompileTime,
    "TextDisplayMode", "flash.text", &ObjectCI,
    ClassTraits::TextDisplayMode::MakeClassTraits,
    0,
    ClassTraits::TextDisplayMode::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::TextDisplayMode::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

