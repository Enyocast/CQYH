//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_SoundLoaderContext.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Media_SoundLoaderContext.h"
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
    SoundLoaderContext::SoundLoaderContext(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , bufferTime(1000)
    , checkPolicyFile(false)
//##protect##"instance::SoundLoaderContext::SoundLoaderContext()$data"
//##protect##"instance::SoundLoaderContext::SoundLoaderContext()$data"
    {
//##protect##"instance::SoundLoaderContext::SoundLoaderContext()$code"
//##protect##"instance::SoundLoaderContext::SoundLoaderContext()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo SoundLoaderContext::mi[SoundLoaderContext::MemberInfoNum] = {
        {"bufferTime", OFFSETOF(Instances::SoundLoaderContext, bufferTime), SlotInfo::BT_Number, 0},
        {"checkPolicyFile", OFFSETOF(Instances::SoundLoaderContext, checkPolicyFile), SlotInfo::BT_Boolean, 0},
    };


    SoundLoaderContext::SoundLoaderContext(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::SoundLoaderContext::SoundLoaderContext()"
//##protect##"InstanceTraits::SoundLoaderContext::SoundLoaderContext()"
        SetMemSize(sizeof(Instances::SoundLoaderContext));

    }

    Pickable<Instances::SoundLoaderContext> SoundLoaderContext::MakeInstance(Traits& t)
    {
        return Pickable<Instances::SoundLoaderContext>(new(t.Alloc()) Instances::SoundLoaderContext(t));
    }

    void SoundLoaderContext::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    SoundLoaderContext::SoundLoaderContext(VM& vm)
    : Traits(vm, SoundLoaderContextCI)
    {
//##protect##"ClassTraits::SoundLoaderContext::SoundLoaderContext()"
//##protect##"ClassTraits::SoundLoaderContext::SoundLoaderContext()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::SoundLoaderContext(vm, SoundLoaderContextCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SoundLoaderContext::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SoundLoaderContext(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SoundLoaderContextCI = {
    ClassInfo::CompileTime,
    "SoundLoaderContext", "flash.media", &ObjectCI,
    ClassTraits::SoundLoaderContext::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::SoundLoaderContext::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::SoundLoaderContext::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

