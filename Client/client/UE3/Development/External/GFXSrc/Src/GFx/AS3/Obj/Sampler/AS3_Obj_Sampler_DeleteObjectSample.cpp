//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Sampler_DeleteObjectSample.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Sampler_DeleteObjectSample.h"
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
    DeleteObjectSample::DeleteObjectSample(InstanceTraits::Traits& t)
    : Instances::Sample(t)
    , id()
    , size()
//##protect##"instance::DeleteObjectSample::DeleteObjectSample()$data"
//##protect##"instance::DeleteObjectSample::DeleteObjectSample()$data"
    {
//##protect##"instance::DeleteObjectSample::DeleteObjectSample()$code"
//##protect##"instance::DeleteObjectSample::DeleteObjectSample()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo DeleteObjectSample::mi[DeleteObjectSample::MemberInfoNum] = {
        {"id", OFFSETOF(Instances::DeleteObjectSample, id), SlotInfo::BT_Number, 1},
        {"size", OFFSETOF(Instances::DeleteObjectSample, size), SlotInfo::BT_Number, 1},
    };


    DeleteObjectSample::DeleteObjectSample(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::DeleteObjectSample::DeleteObjectSample()"
//##protect##"InstanceTraits::DeleteObjectSample::DeleteObjectSample()"
        SetMemSize(sizeof(Instances::DeleteObjectSample));

    }

    Pickable<Instances::DeleteObjectSample> DeleteObjectSample::MakeInstance(Traits& t)
    {
        return Pickable<Instances::DeleteObjectSample>(new(t.Alloc()) Instances::DeleteObjectSample(t));
    }

    void DeleteObjectSample::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    DeleteObjectSample::DeleteObjectSample(VM& vm)
    : Traits(vm, DeleteObjectSampleCI)
    {
//##protect##"ClassTraits::DeleteObjectSample::DeleteObjectSample()"
//##protect##"ClassTraits::DeleteObjectSample::DeleteObjectSample()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::DeleteObjectSample(vm, DeleteObjectSampleCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> DeleteObjectSample::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DeleteObjectSample(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo DeleteObjectSampleCI = {
    ClassInfo::CompileTime,
    "DeleteObjectSample", "flash.sampler", &SampleCI,
    ClassTraits::DeleteObjectSample::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::DeleteObjectSample::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::DeleteObjectSample::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

