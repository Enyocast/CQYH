//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLRequestHeader.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_URLRequestHeader.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace Instances
{
    URLRequestHeader::URLRequestHeader(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , name(AS3::DefaultValue<ASString>(GetStringManager()))
    , value(AS3::DefaultValue<ASString>(GetStringManager()))
//##protect##"instance::URLRequestHeader::URLRequestHeader()$data"
//##protect##"instance::URLRequestHeader::URLRequestHeader()$data"
    {
//##protect##"instance::URLRequestHeader::URLRequestHeader()$code"
//##protect##"instance::URLRequestHeader::URLRequestHeader()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo URLRequestHeader::mi[URLRequestHeader::MemberInfoNum] = {
        {"name", OFFSETOF(Instances::URLRequestHeader, name), SlotInfo::BT_String, 0},
        {"value", OFFSETOF(Instances::URLRequestHeader, value), SlotInfo::BT_String, 0},
    };


    URLRequestHeader::URLRequestHeader(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::URLRequestHeader::URLRequestHeader()"
//##protect##"InstanceTraits::URLRequestHeader::URLRequestHeader()"
        SetMemSize(sizeof(Instances::URLRequestHeader));

    }

    Pickable<Instances::URLRequestHeader> URLRequestHeader::MakeInstance(Traits& t)
    {
        return Pickable<Instances::URLRequestHeader>(new(t.Alloc()) Instances::URLRequestHeader(t));
    }

    void URLRequestHeader::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    URLRequestHeader::URLRequestHeader(VM& vm)
    : Traits(vm, URLRequestHeaderCI)
    {
//##protect##"ClassTraits::URLRequestHeader::URLRequestHeader()"
//##protect##"ClassTraits::URLRequestHeader::URLRequestHeader()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::URLRequestHeader(vm, URLRequestHeaderCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> URLRequestHeader::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) URLRequestHeader(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo URLRequestHeaderCI = {
    ClassInfo::CompileTime,
    "URLRequestHeader", "flash.net", &ObjectCI,
    ClassTraits::URLRequestHeader::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::URLRequestHeader::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::URLRequestHeader::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

