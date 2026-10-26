//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_LoaderContext.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_System_LoaderContext.h"
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
    LoaderContext::LoaderContext(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , allowLoadBytesCodeExecution(false)
    , applicationDomain()
    , checkPolicyFile(false)
    , securityDomain()
//##protect##"instance::LoaderContext::LoaderContext()$data"
//##protect##"instance::LoaderContext::LoaderContext()$data"
    {
//##protect##"instance::LoaderContext::LoaderContext()$code"
//##protect##"instance::LoaderContext::LoaderContext()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo LoaderContext::mi[LoaderContext::MemberInfoNum] = {
        {"allowLoadBytesCodeExecution", OFFSETOF(Instances::LoaderContext, allowLoadBytesCodeExecution), SlotInfo::BT_Boolean, 0},
        {"applicationDomain", OFFSETOF(Instances::LoaderContext, applicationDomain), SlotInfo::BT_ObjectCpp, 0},
        {"checkPolicyFile", OFFSETOF(Instances::LoaderContext, checkPolicyFile), SlotInfo::BT_Boolean, 0},
        {"securityDomain", OFFSETOF(Instances::LoaderContext, securityDomain), SlotInfo::BT_ObjectCpp, 0},
    };


    LoaderContext::LoaderContext(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::LoaderContext::LoaderContext()"
//##protect##"InstanceTraits::LoaderContext::LoaderContext()"
        SetMemSize(sizeof(Instances::LoaderContext));

    }

    Pickable<Instances::LoaderContext> LoaderContext::MakeInstance(Traits& t)
    {
        return Pickable<Instances::LoaderContext>(new(t.Alloc()) Instances::LoaderContext(t));
    }

    void LoaderContext::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    LoaderContext::LoaderContext(VM& vm)
    : Traits(vm, LoaderContextCI)
    {
//##protect##"ClassTraits::LoaderContext::LoaderContext()"
//##protect##"ClassTraits::LoaderContext::LoaderContext()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::LoaderContext(vm, LoaderContextCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> LoaderContext::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) LoaderContext(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo LoaderContextCI = {
    ClassInfo::CompileTime,
    "LoaderContext", "flash.system", &ObjectCI,
    ClassTraits::LoaderContext::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::LoaderContext::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::LoaderContext::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

