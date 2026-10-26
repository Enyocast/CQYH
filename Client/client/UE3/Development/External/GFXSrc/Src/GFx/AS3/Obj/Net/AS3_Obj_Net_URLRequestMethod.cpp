//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLRequestMethod.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_URLRequestMethod.h"
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
    URLRequestMethod::URLRequestMethod(ClassTraits::Traits& t)
    : Class(t)
    , DELETE("DELETE")
    , GET("GET")
    , HEAD("HEAD")
    , OPTIONS("OPTIONS")
    , POST("POST")
    , PUT("PUT")
    {
//##protect##"class_::URLRequestMethod::URLRequestMethod()"
//##protect##"class_::URLRequestMethod::URLRequestMethod()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo URLRequestMethod::mi[URLRequestMethod::MemberInfoNum] = {
        {"DELETE", OFFSETOF(Classes::URLRequestMethod, DELETE), SlotInfo::BT_ConstChar, 1},
        {"GET", OFFSETOF(Classes::URLRequestMethod, GET), SlotInfo::BT_ConstChar, 1},
        {"HEAD", OFFSETOF(Classes::URLRequestMethod, HEAD), SlotInfo::BT_ConstChar, 1},
        {"OPTIONS", OFFSETOF(Classes::URLRequestMethod, OPTIONS), SlotInfo::BT_ConstChar, 1},
        {"POST", OFFSETOF(Classes::URLRequestMethod, POST), SlotInfo::BT_ConstChar, 1},
        {"PUT", OFFSETOF(Classes::URLRequestMethod, PUT), SlotInfo::BT_ConstChar, 1},
    };

    URLRequestMethod::URLRequestMethod(VM& vm)
    : Traits(vm, URLRequestMethodCI)
    {
//##protect##"ClassTraits::URLRequestMethod::URLRequestMethod()"
//##protect##"ClassTraits::URLRequestMethod::URLRequestMethod()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, URLRequestMethodCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::URLRequestMethod(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> URLRequestMethod::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) URLRequestMethod(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo URLRequestMethodCI = {
    ClassInfo::CompileTime,
    "URLRequestMethod", "flash.net", &ObjectCI,
    ClassTraits::URLRequestMethod::MakeClassTraits,
    0,
    ClassTraits::URLRequestMethod::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::URLRequestMethod::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

