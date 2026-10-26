//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLLoaderDataFormat.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_URLLoaderDataFormat.h"
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
    URLLoaderDataFormat::URLLoaderDataFormat(ClassTraits::Traits& t)
    : Class(t)
    , BINARY("binary")
    , TEXT("text")
    , VARIABLES("variables")
    {
//##protect##"class_::URLLoaderDataFormat::URLLoaderDataFormat()"
//##protect##"class_::URLLoaderDataFormat::URLLoaderDataFormat()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo URLLoaderDataFormat::mi[URLLoaderDataFormat::MemberInfoNum] = {
        {"BINARY", OFFSETOF(Classes::URLLoaderDataFormat, BINARY), SlotInfo::BT_ConstChar, 1},
        {"TEXT", OFFSETOF(Classes::URLLoaderDataFormat, TEXT), SlotInfo::BT_ConstChar, 1},
        {"VARIABLES", OFFSETOF(Classes::URLLoaderDataFormat, VARIABLES), SlotInfo::BT_ConstChar, 1},
    };

    URLLoaderDataFormat::URLLoaderDataFormat(VM& vm)
    : Traits(vm, URLLoaderDataFormatCI)
    {
//##protect##"ClassTraits::URLLoaderDataFormat::URLLoaderDataFormat()"
//##protect##"ClassTraits::URLLoaderDataFormat::URLLoaderDataFormat()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, URLLoaderDataFormatCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::URLLoaderDataFormat(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> URLLoaderDataFormat::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) URLLoaderDataFormat(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo URLLoaderDataFormatCI = {
    ClassInfo::CompileTime,
    "URLLoaderDataFormat", "flash.net", &ObjectCI,
    ClassTraits::URLLoaderDataFormat::MakeClassTraits,
    0,
    ClassTraits::URLLoaderDataFormat::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::URLLoaderDataFormat::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

