//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_ClipboardFormats.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_ClipboardFormats.h"
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
    ClipboardFormats::ClipboardFormats(ClassTraits::Traits& t)
    : Class(t)
    , HTML_FORMAT("air:html")
    , TEXT_FORMAT("air:text")
    {
//##protect##"class_::ClipboardFormats::ClipboardFormats()"
//##protect##"class_::ClipboardFormats::ClipboardFormats()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo ClipboardFormats::mi[ClipboardFormats::MemberInfoNum] = {
        {"HTML_FORMAT", OFFSETOF(Classes::ClipboardFormats, HTML_FORMAT), SlotInfo::BT_ConstChar, 1},
        {"TEXT_FORMAT", OFFSETOF(Classes::ClipboardFormats, TEXT_FORMAT), SlotInfo::BT_ConstChar, 1},
    };

    ClipboardFormats::ClipboardFormats(VM& vm)
    : Traits(vm, ClipboardFormatsCI)
    {
//##protect##"ClassTraits::ClipboardFormats::ClipboardFormats()"
//##protect##"ClassTraits::ClipboardFormats::ClipboardFormats()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, ClipboardFormatsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::ClipboardFormats(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ClipboardFormats::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClipboardFormats(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ClipboardFormatsCI = {
    ClassInfo::CompileTime,
    "ClipboardFormats", "flash.desktop", &ObjectCI,
    ClassTraits::ClipboardFormats::MakeClassTraits,
    0,
    ClassTraits::ClipboardFormats::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::ClipboardFormats::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

