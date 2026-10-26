//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_NativeDragOptions.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_NativeDragOptions.h"
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
    NativeDragOptions::NativeDragOptions(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , allowCopy(true)
    , allowLink(true)
    , allowMove(true)
//##protect##"instance::NativeDragOptions::NativeDragOptions()$data"
//##protect##"instance::NativeDragOptions::NativeDragOptions()$data"
    {
//##protect##"instance::NativeDragOptions::NativeDragOptions()$code"
//##protect##"instance::NativeDragOptions::NativeDragOptions()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo NativeDragOptions::ti[NativeDragOptions::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };
    const MemberInfo NativeDragOptions::mi[NativeDragOptions::MemberInfoNum] = {
        {"allowCopy", OFFSETOF(Instances::NativeDragOptions, allowCopy), SlotInfo::BT_Boolean, 0},
        {"allowLink", OFFSETOF(Instances::NativeDragOptions, allowLink), SlotInfo::BT_Boolean, 0},
        {"allowMove", OFFSETOF(Instances::NativeDragOptions, allowMove), SlotInfo::BT_Boolean, 0},
    };


    NativeDragOptions::NativeDragOptions(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::NativeDragOptions::NativeDragOptions()"
//##protect##"InstanceTraits::NativeDragOptions::NativeDragOptions()"
        SetMemSize(sizeof(Instances::NativeDragOptions));

    }

    Pickable<Instances::NativeDragOptions> NativeDragOptions::MakeInstance(Traits& t)
    {
        return Pickable<Instances::NativeDragOptions>(new(t.Alloc()) Instances::NativeDragOptions(t));
    }

    void NativeDragOptions::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    NativeDragOptions::NativeDragOptions(VM& vm)
    : Traits(vm, NativeDragOptionsCI)
    {
//##protect##"ClassTraits::NativeDragOptions::NativeDragOptions()"
//##protect##"ClassTraits::NativeDragOptions::NativeDragOptions()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::NativeDragOptions(vm, NativeDragOptionsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeDragOptions::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeDragOptions(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeDragOptionsCI = {
    ClassInfo::CompileTime,
    "NativeDragOptions", "flash.desktop", &ObjectCI,
    ClassTraits::NativeDragOptions::MakeClassTraits,
    0,
    0,
    InstanceTraits::NativeDragOptions::ThunkInfoNum,
    InstanceTraits::NativeDragOptions::MemberInfoNum,
    NULL,
    NULL,
    InstanceTraits::NativeDragOptions::ti,
    InstanceTraits::NativeDragOptions::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

