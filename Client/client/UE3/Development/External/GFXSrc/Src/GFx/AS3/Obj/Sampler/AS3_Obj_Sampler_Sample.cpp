//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Sampler_Sample.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Sampler_Sample.h"
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
    Sample::Sample(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , stack()
    , time()
//##protect##"instance::Sample::Sample()$data"
//##protect##"instance::Sample::Sample()$data"
    {
//##protect##"instance::Sample::Sample()$code"
//##protect##"instance::Sample::Sample()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo Sample::mi[Sample::MemberInfoNum] = {
        {"stack", OFFSETOF(Instances::Sample, stack), SlotInfo::BT_ObjectCpp, 1},
        {"time", OFFSETOF(Instances::Sample, time), SlotInfo::BT_Number, 1},
    };


    Sample::Sample(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Sample::Sample()"
//##protect##"InstanceTraits::Sample::Sample()"
        SetMemSize(sizeof(Instances::Sample));

    }

    Pickable<Instances::Sample> Sample::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Sample>(new(t.Alloc()) Instances::Sample(t));
    }

    void Sample::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    Sample::Sample(VM& vm)
    : Traits(vm, SampleCI)
    {
//##protect##"ClassTraits::Sample::Sample()"
//##protect##"ClassTraits::Sample::Sample()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Sample(vm, SampleCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Sample::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Sample(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SampleCI = {
    ClassInfo::CompileTime,
    "Sample", "flash.sampler", &ObjectCI,
    ClassTraits::Sample::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::Sample::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::Sample::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

