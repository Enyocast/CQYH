//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Sampler_NewObjectSample.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Sampler_NewObjectSample.h"
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
    NewObjectSample::NewObjectSample(InstanceTraits::Traits& t)
    : Instances::Sample(t)
    , id()
    , type()
//##protect##"instance::NewObjectSample::NewObjectSample()$data"
//##protect##"instance::NewObjectSample::NewObjectSample()$data"
    {
//##protect##"instance::NewObjectSample::NewObjectSample()$code"
//##protect##"instance::NewObjectSample::NewObjectSample()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo NewObjectSample::ti[NewObjectSample::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, NULL, "object", NULL, CT_Get, 0, 0},
    };
    const MemberInfo NewObjectSample::mi[NewObjectSample::MemberInfoNum] = {
        {"id", OFFSETOF(Instances::NewObjectSample, id), SlotInfo::BT_Number, 1},
        {"type", OFFSETOF(Instances::NewObjectSample, type), SlotInfo::BT_ObjectCpp, 1},
    };


    NewObjectSample::NewObjectSample(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::NewObjectSample::NewObjectSample()"
//##protect##"InstanceTraits::NewObjectSample::NewObjectSample()"
        SetMemSize(sizeof(Instances::NewObjectSample));

    }

    Pickable<Instances::NewObjectSample> NewObjectSample::MakeInstance(Traits& t)
    {
        return Pickable<Instances::NewObjectSample>(new(t.Alloc()) Instances::NewObjectSample(t));
    }

    void NewObjectSample::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    NewObjectSample::NewObjectSample(VM& vm)
    : Traits(vm, NewObjectSampleCI)
    {
//##protect##"ClassTraits::NewObjectSample::NewObjectSample()"
//##protect##"ClassTraits::NewObjectSample::NewObjectSample()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::NewObjectSample(vm, NewObjectSampleCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NewObjectSample::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NewObjectSample(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NewObjectSampleCI = {
    ClassInfo::CompileTime,
    "NewObjectSample", "flash.sampler", &SampleCI,
    ClassTraits::NewObjectSample::MakeClassTraits,
    0,
    0,
    InstanceTraits::NewObjectSample::ThunkInfoNum,
    InstanceTraits::NewObjectSample::MemberInfoNum,
    NULL,
    NULL,
    InstanceTraits::NewObjectSample::ti,
    InstanceTraits::NewObjectSample::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

